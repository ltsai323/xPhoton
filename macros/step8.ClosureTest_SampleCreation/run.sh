#!/usr/bin/env sh

root -b > log.execfile <<EOF
  //.L FakeDataCreation.C+
  .L fakedatacreation.C+
  FakeDataCreation()
EOF
python logTranslater.py
