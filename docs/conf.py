import subprocess


project = 'simpleRPC'
author = 'Jeroen F.J. Laros'
copyright = '2019, {}'.format(author)

extensions = ['breathe']
breathe_version = '4.3.1'
breathe_projects = {'doxygen': 'xml'}
breathe_default_project = 'doxygen'
breathe_default_members = ['members']

master_doc = 'index'

highlight_language = 'none'
html_theme = 'sphinx_rtd_theme'


subprocess.call(
    'pip install breathe=={}; doxygen'.format(breathe_version), shell=True)
