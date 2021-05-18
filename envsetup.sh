#!/usr/bin/env sh

newpath=`echo $PWD/*/bin | sed 's/ /:/'`
echo $newpath


export PATH=$PATH:$newpath
if ! type "root" > /dev/null; then
    echo "No 'root' command found, please install root before use thi repository"
fi
