#!/usr/bin/env sh

file1=$1
file2=$2

root -b $file1 > log1 2>&1 <<EOF
for ( int i = 0; i< 100; ++i ) t->Show(i*10);
EOF
root -b $file2 > log2 2>&1 <<EOF
for ( int i = 0; i< 100; ++i ) t->Show(i*10);
EOF

diff log1 log2
