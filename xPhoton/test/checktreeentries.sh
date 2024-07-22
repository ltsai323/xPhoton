#!/usr/bin/env sh

ifile=$1

root -b $ifile <<EOF
t->Draw("recoPt", "isMatched==1")
EOF
