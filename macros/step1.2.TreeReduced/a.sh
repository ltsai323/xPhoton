ifile=$1

root -b $ifile <<EOF
bool IsMC = ((TTree*)_file0->Get("t"))->GetBranch("mcPt") ? kTRUE : kFALSE;
std::cout <<IsMC << std::endl;
EOF
