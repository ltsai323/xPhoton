#!/usr/bin/env sh

root -b > log.execfile <<EOF
.L FakeDataCreation.C+
FakeDataCreation()
EOF
