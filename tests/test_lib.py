from simple_rpc import Interface
from simple_rpc.simple_rpc import _version


_interface = Interface('/dev/ttyACM0')


class TestLib(object):
    def test_version(self):
        assert _interface.version() == _version

    def test_ping(self):
        assert _interface.ping(3) == 3

    def test_type_1(self):
        assert _interface.methods['version']['return']['typename'] == 'str'

    def test_type_2(self):
        assert _interface.methods['ping']['return']['typename'] == 'int'

    def test_fmt_1(self):
        assert _interface.methods['version']['return']['fmt'] == 's'

    def test_fmt_2(self):
        assert _interface.methods['ping']['return']['fmt'] == 'B'

    def test_param_1(self):
        assert _interface.methods['version']['parameters'] == []

    def test_param_2(self):
        assert _interface.methods['ping']['parameters'][0]['typename'] == 'int'

    def test_param_3(self):
        assert _interface.methods['ping']['parameters'][0]['fmt'] == 'B'

    def test_param_4(self):
        assert _interface.methods['ping']['parameters'][0]['name'] == 'data'

    def test_doc_1(self):
        assert _interface.methods['version']['doc'] == 'Protocol version.'

    def test_doc_2(self):
        assert (
            _interface.methods['version']['return']['doc'] ==
            'Version string.')

    def test_doc_3(self):
        assert _interface.methods['ping']['doc'] == 'Echo a value.'

    def test_doc_4(self):
        assert _interface.methods['ping']['parameters'][0]['doc'] == 'Value.'
