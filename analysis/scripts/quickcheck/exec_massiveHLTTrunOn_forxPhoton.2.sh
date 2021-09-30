#!/usr/bin/env sh
inputfile=$1

pythonexec=HLTTurnOn_forxPhoton.finalplot.py
for b in {0..8};
do
    n=$(($b+1))
   python $pythonexec $inputfile $b $n;
done
