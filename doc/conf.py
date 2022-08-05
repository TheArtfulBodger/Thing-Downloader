# Configuration file for the Sphinx documentation builder.


# -- Project information -----------------------------------------------------

project = 'Thing Downloader'
copyright = '2022, The Artful Bodger'
author = 'The Artful Bodger'

# The full version, including alpha/beta/rc tags
release = '0.1'


# -- General configuration ---------------------------------------------------

extensions = [
    "breathe"
]

templates_path = ['templates']
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store']


# -- Options for HTML output -------------------------------------------------

html_theme = 'sphinx_rtd_theme'
html_static_path = ['static']

# -- Options for Breathe Plugin ----------------------------------------------
breathe_projects = {"ThingDownloader": "./_xml/"}
breathe_default_project = "ThingDownloader"

# -- Build Doxygen Documentation ---------------------------------------------
import subprocess
subprocess.call('cd .. ; doxygen', shell=True)