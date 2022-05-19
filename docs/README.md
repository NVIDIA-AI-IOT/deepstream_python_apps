Please follow the following steps to build html files

requirements
===================
1. python 3.8 (The default `python --version` should be 3.8)
2. sphinx (>=4.2)
3. breathe extension
4. recommonmark
5. sphinx_rtd_theme

installation
===================
```bash
pip3 install sphinx
pip3 install breathe
pip3 install recommonmark
pip3 install sphinx_rtd_theme
```

1. Run parse_bindings.py to generate rst files for classes and enums
2. Copy the pyds.so from ds_python/bindings/build dir into this (docs) directory
3. Then run
   ```bash
    make html
    ```
4. Copy `custom.css` and `pk_scripts.js` into `_build/html/_static`
