#!/usr/bin/env sh

data1=makehisto_data.root
fake1=makehisto_QCD.root
sign1=makehisto_sig.root
data0=ref/makehisto_data.root
fake0=ref/makehisto_QCD.root
sign0=ref/makehisto_sig.root
root -q -b 'DrawAllHists.C("'$data0'")' > log_data0 2>&1
root -q -b 'DrawAllHists.C("'$sign0'")' > log_sign0 2>&1
root -q -b 'DrawAllHists.C("'$fake0'")' > log_fake0 2>&1

root -q -b 'DrawAllHists.C("'$data1'")' > log_data1 2>&1
root -q -b 'DrawAllHists.C("'$sign1'")' > log_sign1 2>&1
root -q -b 'DrawAllHists.C("'$fake1'")' > log_fake1 2>&1
diff log_data0 log_data1 > kd
diff log_sign0 log_sign1 > ks
diff log_fake0 log_fake1 > kf

cat kd
cat ks
cat kf
echo " left : reference. right : testing"
