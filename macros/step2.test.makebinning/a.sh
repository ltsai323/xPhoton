#!/usr/bin/env sh

data1=makehisto_data.root
data0=ref/makehisto_data.root
root -q -b 'DrawAllHists.C("'$data0'")' > log_data0 2>&1
root -q -b 'DrawAllHists.C("'$data1'")' > log_data1 2>&1
diff log_data0 log_data1 > kd

cat kd
echo " left : reference. right : testing"
