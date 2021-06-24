ifile=$1
idx=$2

root -b <<EOF
.L xPhotonHFJet_origversion.C+
xPhotonHFJet("${ifile}", ${idx})
EOF


