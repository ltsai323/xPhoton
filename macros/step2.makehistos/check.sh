
function exec_code()
{
num=$1
inputcode=$2
outputfolder=$3
mkdir -p $outputfolder
root -b <<EOF
.L $inputcode
Loop($num, "2016ReReco", "testdata", "/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/Run2016_Legacy_ctagReshape.root");
Loop($num, "2016ReReco", "testgjet", "/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/sigMC_madgraph_ctagReshaped.root");
Loop($num, "2016ReReco", "testQCD", "/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/QCD_madgraph_ctagReshape.root");
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

