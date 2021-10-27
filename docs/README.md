Please follow the following steps to build html files

requirements
===================
1. python 3.6 (The default `python --version` should be 3.6)
2. sphinx (>=4.2)
3. breathe extension
4. recommonmark

installation
===================
```bash
pip install sphinx
pip install breathe
pip install recommonmark
```

1. Run parse_bindings.py to generate rst files for classes and enums
2. Copy the pyds.so from ds_python/bindings/build dir into this (docs) directory
3. Then run
   ```bash
    make html
    ```
4. Copy `custom.css` and `pk_scripts.js` into `_build/html/_static`
