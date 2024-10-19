from subprocess import call


project = 'simpleRPC'
author = 'Jeroen F.J. Laros'
copyright = '2019, {}'.format(author)

extensions = ['breathe']
breathe_projects = {'doxygen': 'xml'}
breathe_default_project = 'doxygen'
breathe_default_members = ('members',)

master_doc = 'index'

highlight_language = 'none'
