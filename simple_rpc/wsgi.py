from flask import Flask
from flask_restplus import Resource, Api

from simple_rpc import Interface


app = Flask(__name__)
api = Api(app)

_types = {'str': 'string'}

code = '''
@api.route('/{name}/{params}')
class {name}(Resource):
    def get(self{args}):
        """{doc}"""
        return interface.call_method('{name}'{args})
'''


def _convert_type(t):
    if t in _types:
        return _types[t]
    return t


def add_call(method):
    exec(code.format(
        name=method['name'],
        doc=method['doc'],
        params='/'.join(map(
            lambda x: '<{}:{}>'.format(
                _convert_type(x['typename']), x['name']),
            method['parameters'])),
        args=''.join(map(lambda x: ', ' + x['name'], method['parameters']))))


if __name__ == '__main__':
    interface = Interface('/dev/ttyACM0')

    for method in interface.methods.values():
        add_call(method)

    app.run(debug=True)
