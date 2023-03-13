
function exec_code()
{
num=$1
inputcode=$2
outputfolder=$3


datafile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/Run2016_Legacy_ctagReshape.root
signfile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/sigMC_madgraph_ctagReshaped.root
fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/QCD_madgraph_ctagReshape.root

mkdir -p $outputfolder
root -b <<EOF
.L $inputcode
Loop($num, "2016ReReco", "data", "$datafile");
Loop($num, "2016ReReco", "sig" , "$signfile");
Loop($num, "2016ReReco", "QCD" , "$fakefile");
EOF
mv makehisto_*.root $outputfolder/
}

touch makehisto_aaaa.root; /bin/rm makehisto_*.root # clean up

exec_code 0 makehistoDeepFlavour.C deepflavour_CUT_NOCUT 0
exec_code 1 makehistoDeepFlavour.C deepflavour_CUT_subJetVtxMass 1
exec_code 2 makehistoDeepFlavour.C deepflavour_CUT_CvsL 2

exec_code 0 makehistoDeepCSV.C deepcsv_CUT_NOCUT 0
exec_code 1 makehistoDeepCSV.C deepcsv_CUT_subJetVtxMass 1
exec_code 2 makehistoDeepCSV.C deepcsv_CUT_CvsL 2

