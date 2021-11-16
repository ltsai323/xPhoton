ifile=$1
root -b $ifile <<EOF
t->Scan("isMatched:recoPt:photonIDmva")
EOF
