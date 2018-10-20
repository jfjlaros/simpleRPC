from argparse import ArgumentParser, FileType, RawDescriptionHelpFormatter
from time import sleep
from sys import stdout

from . import doc_split, usage, version
from .simple_rpc import Interface


def _describe_parameters(method):
    """Make parameter data (types and documentation) human readable.

    :arg dict method: Method dictionary.

    :returns str: Parameter data in readable form.
    """
    args = []
    description = []

    for index, parameter in enumerate(method['parameters']):
        args.append('arg{}'.format(index))
        description.append('    arg{} (type {}): {}'.format(
            index, parameter, method['doc']['parameters'][index]))

    return args, description


def _describe_method(method):
    """Make a human readable description of a method.

    :arg dict method: Method dictionary.

    :returns str: Method data in readable form.
    """
    description = '{}'.format(method['name'])

    args, parameter_description = _describe_parameters(method)
    if (args):
        description += ' {}'.format(' '.join(args))

    description += '\n    {}'.format(method['doc']['name'])
    if (args):
        description += '\n\n{}'.format('\n'.join(parameter_description))

    if method['type']:
        description += '\n\n    returns (type {}): {}'.format(
            method['type'], method['doc']['type'])

    return description


def rpc_list(handle, device):
    """List the device methods.

    :arg stream handle: Output handle.
    :arg str device: Serial device.
    """
    interface = Interface(device)

    handle.write('Available methods:\n\n\n')
    for method in interface.methods.values():
        handle.write(_describe_method(method) + '\n\n\n')


def rpc_call(handle, device, name, args):
    """Execute a method.

    :arg stream handle: Output handle.
    :arg str device: Serial device.
    :arg str name: Method name.
    :arg list args: Method parameters.
    """
    interface = Interface(device)

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
        'list', parents=[common_parser],
        description=doc_split(rpc_list))
    subparser.set_defaults(func=rpc_list)

    subparser = subparsers.add_parser(
        'call', parents=[common_parser],
        description=doc_split(rpc_call))
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
    except ValueError as error:
        parser.error(error)


if __name__ == '__main__':
    main()
