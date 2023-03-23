
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
hadd makehisto.root makehisto_*.root

mv makehisto.root $outputfolder/
mv makehisto_*.root $outputfolder/
}


exec_code 0 makehistoDeepFlavour.C DeepFlavour_cutIdx0
#exec_code 0 makehistoDeepCSV.C deepflavour_CUT_NOCUT

