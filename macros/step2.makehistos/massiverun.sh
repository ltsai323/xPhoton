function exec_code()
{
jetCutIdx=$1
inputcode=$2
outputfolder=$3


datafile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/Run2016_Legacy_ctagReshape.root
signfile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/sigMC_madgraph_ctagReshaped.root
fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/QCD_madgraph_ctagReshape.root

mkdir -p $outputfolder
root -b <<EOF
.L $inputcode
Loop($jetCutIdx, "2016ReReco", "data", "$datafile");
Loop($jetCutIdx, "2016ReReco", "gjet", "$signfile");
Loop($jetCutIdx, "2016ReReco", "QCD" , "$fakefile");
EOF

hadd ${outputfolder}.root makehisto_*.root
mv makehisto_*.root $outputfolder/
}

touch makehisto_aaaa.root; /bin/rm makehisto_*.root # clean up

exec_code 0 makehistoDeepFlavour.C newBin_deepflavour_CUT_NOCUT
exec_code 1 makehistoDeepFlavour.C newBin_deepflavour_CUT_subJetVtxMass
exec_code 2 makehistoDeepFlavour.C newBin_deepflavour_CUT_CvsL

exec_code 0 makehistoDeepCSV.C newBin_deepcsv_CUT_NOCUT
exec_code 1 makehistoDeepCSV.C newBin_deepcsv_CUT_subJetVtxMass
exec_code 2 makehistoDeepCSV.C newBin_deepcsv_CUT_CvsL

