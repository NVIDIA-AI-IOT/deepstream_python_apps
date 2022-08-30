# SPDX-FileCopyrightText: Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
# SPDX-License-Identifier: Apache-2.0
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# http://www.sphinx-doc.org/en/master/config

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#


# -- Project information -----------------------------------------------------
import os
import sys
import recommonmark

sys.path.insert(0, os.path.abspath('.'))
import pyds

project = 'Deepstream'
copyright = '2019-2022, NVIDIA.'
author = 'NVIDIA'
version = 'Deepstream Version: 6.1.1'
release = version


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    'sphinx.ext.autosummary',
    'sphinx.ext.autodoc',
    'sphinx.ext.intersphinx',
    'sphinx.ext.todo',
    'sphinx.ext.coverage',
    'sphinx.ext.ifconfig',
    'recommonmark',
    'breathe'
]

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = ['_build', 'Thumbs.db', '.DS_Store', 'manuals/py/**']

#source_parsers = { '.md': 'recommonmark.parser.CommonMarkParser',}



source_suffix = {'.rst': 'restructuredtext', '.md':'markdown'}

# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.
#
import sphinx_rtd_theme

html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]

html_theme = "sphinx_rtd_theme"
html_logo = os.path.join('content', 'nv_logo.png')

html_theme_options = {
    'logo_only': True,
    'display_version': True,
    'prev_next_buttons_location': 'bottom',
    'style_external_links': False,
    'style_nav_header_background': '#000000',
    # Toc options
    'collapse_navigation': False,
    'sticky_navigation': False,
    # 'navigation_depth': 10,
    'includehidden': True,
    'titles_only': False
}


# html_theme = 'alabaster'

# Add any paths that contain custom static files (such as style sheets) here,
# relative to this directory. They are copied after the builtin static files,
# so a file named "default.css" will overwrite the builtin "default.css".

html_favicon = 'Nvidia.ico'

html_static_path = []

html_last_updated_fmt = ''

def setup(app):
    app.add_css_file('custom.css')

html_js_files = [
    'pk_scripts.js',
]

# -- Options for Breathe extension
current_path=os.getcwd()
breathe_default_project = "Deepstream"
breathe_projects = {
                "Deepstream" : "/home/manojy/Desktop/DS_DOCUMENTATION/sphinx_documentation/deepstream_html_xml/"
}
