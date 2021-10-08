#!/usr/bin/env sh

root -b > log.execfile <<EOF
.L step7.ClosureTest/FakeDataCreation.C+
FakeDataCreation()
EOF
