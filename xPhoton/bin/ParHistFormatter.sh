#!usr/bin/env sh
filedir=/home/ltsai/ReceivedFile/GJet/data/
filetype=data
for name in `ls $filedir | grep 94X`; do exec_parhistformatter $filetype $filedir/$name  `echo $name | cut -d. -f1`; echo $name; done

filedir=/home/ltsai/ReceivedFile/GJet/GJet_pythia/
filetype=mcsig
for name in `ls $filedir`; do exec_parhistformatter $filetype $filedir/$name  `echo $name | cut -d. -f1`; echo $name; done
filetype=mcbkg
for name in `ls $filedir`; do exec_parhistformatter $filetype $filedir/$name  `echo $name | cut -d. -f1`; echo $name; done

