from argparse import ArgumentParser, FileType, RawDescriptionHelpFormatter
from time import sleep
from sys import stdout

from . import doc_split, usage, version
from .simple_rpc import Interface


def _describe_method(method):
    """Make a human readable description of a method.

    :arg dict method: Method object.

    :returns str: Method data in readable form.
    """
    description = method['name']

    for parameter in method['parameters']:
        description += ' {}'.format(parameter['name'])

    if method['doc']:
        description += '\n    {}'.format(method['doc'])

    if method['parameters']:
        description += '\n'
    for parameter in method['parameters']:
        description += '\n    {} {}'.format(
            parameter['typename'], parameter['name'])
        if parameter['doc']:
            description += ': {}'.format(parameter['doc'])

    if method['return']['fmt']:
        description += '\n\n    returns {}'.format(
            method['return']['typename'])
        if method['return']['doc']:
            description += ': {}'.format(method['return']['doc'])

    return description


def rpc_list(handle, device, baudrate, wait):
    """List the device methods.

    :arg stream handle: Output handle.
    :arg str device: Serial device.
    :arg int baudrate: Baud rate.
    :arg int wait: Time in seconds before communication starts.
    """
    with Interface(device, baudrate, wait) as interface:
        for method in interface.methods.values():
            handle.write(_describe_method(method) + '\n\n\n')


def rpc_call(handle, device, baudrate, wait, name, args):
    """Execute a method.

    :arg stream handle: Output handle.
    :arg str device: Serial device.
    :arg int baudrate: Baud rate.
    :arg int wait: Time in seconds before communication starts.
    :arg str name: Method name.
    :arg list args: Method parameters.
    """
    with Interface(device, baudrate, wait) as interface:
        result = interface.call_method(name, *args)

        if result != None:
            handle.write('{}\n'.format(result))


def main():
    """Main entry point."""
    common_parser = ArgumentParser(add_help=False)
    common_parser.add_argument(
        '-d', dest='device', type=str, default='/dev/ttyACM0',
        help='serial device (%(type)s default="%(default)s")')
    common_parser.add_argument(
        '-b', dest='baudrate', type=int, default=9600,
        help='baud rate (%(type)s default=%(default)s)')
    common_parser.add_argument(
        '-w', dest='wait', type=int, default=1,
        help='time before communication starts (%(type)s default=%(default)s)')
    common_parser.add_argument(
        '-o', dest='handle', metavar='OUTPUT', type=FileType('w'),
        default=stdout, help='output file')

    parser = ArgumentParser(
        formatter_class=RawDescriptionHelpFormatter,
        description=usage[0], epilog=usage[1])
    parser.add_argument(
        '-v', action='version', version=version(parser.prog))
    subparsers = parser.add_subparsers(dest='subcommand')
    subparsers.required = True

    subparser = subparsers.add_parser(
        'list', parents=[common_parser], description=doc_split(rpc_list))
    subparser.set_defaults(func=rpc_list)

    subparser = subparsers.add_parser(
        'call', parents=[common_parser], description=doc_split(rpc_call))
    subparser.set_defaults(func=rpc_call)
    subparser.add_argument(
        'name', metavar='NAME', type=str, help='command name')
    subparser.add_argument(
        'args', metavar='ARG', type=str, nargs='*', help='command parameter')

    try:
        args = parser.parse_args()
    except IOError as error:
        parser.error(error)

    try:
        args.func(**{k: v for k, v in vars(args).items()
            if k not in ('func', 'subcommand')})
    except (IOError, TypeError, ValueError) as error:
        parser.error(error)


if __name__ == '__main__':
    main()
