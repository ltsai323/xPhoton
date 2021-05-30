ifile=$1
idx=$2

root -b <<EOF
.L xPhotonHFJet_origversion.C+
xPhotonHFJet("${ifile}", ${idx})
EOF


#   0 : for loop for all photon_list  --> 1018
#   1 : for loop for 1 photon only    --> 1040
#  10 : for loop for 1 photon only, with photon_list size check --> 1018
#   2 : accept all photon in preselection --> 5175  <180: 96
#   3 : disable leading photon button --> 5175.   <180: 96
# 103 : init photon_list vector after it declared->5175  <180: 96
#   4 : disable if analyze in (useGJetNotUsed && noPhoHLT ) --> 5175 <180: 96
#   5 : disable else @1109 to pass ++nphofiredtrgs
#  50 : same as 5 but use original code. (Disable all histroy modification
# 150 : Add photon_list empty check when filling
#   7 : test for speed (orig) without compile:16s, with compile 8s

