#!/usr/bin/env sh

the_path=$PWD/MyPythonTools/:$PWD/MyCommonTools/python/ptbin_definitions/
export PYTHON3PATH=$the_path:$PYTHON3PATH
export PYTHONPATH=$the_path:$PYTHONPATH
