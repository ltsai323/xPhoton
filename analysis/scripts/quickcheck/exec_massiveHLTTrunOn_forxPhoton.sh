#!/usr/bin/env sh

execCmd=Triggercheck.py
for b in {0..8};
do
    for (( n=$(($b+1)); n<=8; n++ ));
    do
        #sh triggercheck_ggtree_102X.sh  $b $n;
        python Triggercheck.py  $b $n;
    done;
done
