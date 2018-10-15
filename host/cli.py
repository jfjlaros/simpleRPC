from argparse import ArgumentParser, FileType, RawDescriptionHelpFormatter
from time import sleep
from sys import stdout

from simple_rpc import Interface


def rpc_list(handle, device):
    """List the device methods.

    :arg stream handle: Output handle.
    :arg str device: Serial device.
    """
    interface = Interface(device)

    handle.write('Available methods:\n\n')
    for name, values in interface.methods.items():
        handle.write('    {} {}({})\n'.format(
            values['type'], name, ', '.join(values['args'])))
    handle.write('\n')


def rpc_cmd(handle, device, name, args):
    """Execute a method.

    :arg stream handle: Output handle.
    :arg str device: Serial device.
    :arg str name: Method name.
    :arg list args: Method parameters.
    """
    interface = Interface(device)

    result = interface.cmd(name, *args)
    if result != None:
        handle.write('{}\n'.format(result))


def main():
    """Main entry point."""
    usage = ['', '']

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
    subparsers = parser.add_subparsers(dest='subcommand')
    subparsers.required = True

    subparser = subparsers.add_parser(
        'list', parents=[common_parser],
        description='') #doc_split(rpc_list))
    subparser.set_defaults(func=rpc_list)

    subparser = subparsers.add_parser(
        'cmd', parents=[common_parser],
        description='') #doc_split(rpc_cmd))
    subparser.set_defaults(func=rpc_cmd)
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
