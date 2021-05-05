#!/usr/bin/env sh

for b in {0..17};
do
    for (( n=$(($b+1)); n<=17; n++ ));
    do
        sh triggercheck_ggtree_102X.sh  $b $n;
    done;
done
