#!/usr/bin/env

ggNtupleList=$1
dataPUfile=$2
# 1. load all MC in ggNtuple
# 2. load PU file at data
# 3. calculate TGraph and import into xPhoton event


hadd -T test.root `cat $ggNtupleList`



