#!/usr/bin/env sh

newpath=`echo $PWD/*/bin | sed 's/ /:/'`
echo $newpath


export PATH=$PATH:$newpath
