#!/usr/bin/env sh
newcomermesg=kkk

newpath=`echo $PWD/*/bin | sed 's/ /:/'`


export PATH=$PATH:$newpath

if [ "$newcomermesg" != "" ]; then
    echo 'This is a gentle reminder that "root" command is needed to use this repository. Please check before use it'
fi

if ! type "root" > /dev/null; then
    echo "--- Warning --- : No 'root' command found, please install root before use this repository"
fi
