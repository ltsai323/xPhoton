#!/usr/bin/env sh
# cleaning workspace
touch makehisto.root; /bin/rm makehisto*.root

cd step2.test.makebinning
# cleaning workspace
touch makehisto.root; /bin/rm makehisto*.root

sh run.sh
mv makehisto*.root ..
