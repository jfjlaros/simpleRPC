_method_template = '''
def {name}(self{args}):
    """{doc}"""
    return self.call_method('{name}'{args})
'''


def _make_docstring(method):
    """Make a docstring for a function.

    :arg dict method: Method object.

    :returns str: Function docstring.
    """
    help_text = ''

    if method['doc']:
        help_text += method['doc']

    if method['parameters']:
        help_text += '\n'

    for parameter in method['parameters']:
        help_text += '\n:arg {} {}:'.format(
            parameter['typename'], parameter['name'])
        if parameter['doc']:
            help_text += ' {}'.format(parameter['doc'])

    if method['return']['fmt']:
        help_text += '\n\n:returns {}:'.format(method['return']['typename'])
        if method['return']['doc']:
            help_text += ' {}'.format(method['return']['doc'])

    return help_text


def _make_function(method):
    """Make a member function for a method.

    :arg dict method: Method object.

    :returns function: New member function.
    """
    context = {}

    exec(
        _method_template.format(
            name=method['name'],
            doc=_make_docstring(method),
            args=''.join(
                map(lambda x: ', ' + x['name'], method['parameters']))),
        context)

    return context[method['name']]
