#!/usr/bin/env sh

ifile=$1

root -b $ifile <<EOF
t->Scan("recoPt:mva")
EOF
