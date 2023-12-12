#!/usr/bin/env sh
peta=$1
jeta=$2
ppt=$3

## file loaded makehist.root
## Check the existence of it
root -b -q  "checkERR.C($peta,$jeta,$ppt)"
