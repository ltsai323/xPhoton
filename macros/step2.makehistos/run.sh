datafile=$1
signfile=$2
fakefile=$3



cutIdx=1 # 0: no extra cut. 1: subJetVtxMass > 0. 2: CvsL > 0.155
inputcode=makehistoDeepFlavour.C
#inputcode=makehistoDeepCSV.C
outputfolder=myoutput
mkdir -p $outputfolder
root -b <<EOF
.L $inputcode
Loop($cutIdx, "2016ReReco", "data", "$datafile");
Loop($cutIdx, "2016ReReco", "sig" , "$signfile");
Loop($cutIdx, "2016ReReco", "QCD" , "$fakefile");
EOF
mv makehisto_*.root $outputfolder/
