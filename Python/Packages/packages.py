# packages group modules

# In order to treat a directory as a package there has to be a
# __init__.py file.

# Example module directory structure:
# sound/                          Top-level package
#       __init__.py               Initialize the sound package
#       formats/                  Subpackage for file format conversions
#               __init__.py
#               wavread.py
#               ...
#       effects/                  Subpackage for sound effects
#               __init__.py
#               echo.py
#               ...
#       filters/                  Subpackage for filters
#               __init__.py
#               equalizer.py
#               ...

# import formats
# from module import submodule