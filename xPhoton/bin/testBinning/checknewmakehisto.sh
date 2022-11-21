fileTrg=$2
fileCmp=newfiles.root
inword=$1

if [ "$inword" == "sig" ]; then
    nameTrg=sig
    nameCmp=sign
    echo 'signal sample!'
elif [ "$inword" == "qcd" ]; then
    nameTrg=qcd
    nameCmp=fake
    echo 'qcd sample!'
elif [ "$inword" == "exp" ]; then
    nameTrg=exp
    nameCmp=data
    echo 'data!'
fi



echo 'showing signal region status...'
root -b <<EOF
TFile* fTrg = TFile::Open("$fileTrg");
TFile* fCmp = TFile::Open("$fileCmp");

for ( int pEtaBin = 0; pEtaBin < 2; ++pEtaBin ) {
for ( int jEtaBin = 0; jEtaBin < 2; ++jEtaBin ) {
for ( int pPtBin = 0; pPtBin < 21; ++pPtBin ) {
TH1F* hTrg = (TH1F*) fTrg->Get( Form("testBDT${nameTrg}_signalRegion/testBDT${nameTrg}_signalRegion.%d_%d_%d",pEtaBin,jEtaBin,pPtBin) );
TH1F* hCmp = (TH1F*) fCmp->Get( Form("photonFit_%d_%d_%d/${nameCmp}_signalRegion",pEtaBin,jEtaBin,pPtBin) );

Double_t nTrg = hTrg->Integral(1, hTrg->GetNbinsX()+1);
Double_t nCmp = hCmp->Integral(1, hCmp->GetNbinsX()+1);
Double_t diff = nTrg-nCmp;
if ( fabs(diff) > 1e-1 ) {
printf("At bin (%d,%d,%2d) : trg = %10.2f and cmp = %10.2f. Diff = %8.2f in %4.2f%%\n",pEtaBin,jEtaBin,pPtBin, nTrg,nCmp,diff, 100. * diff / nTrg);
}
delete hTrg;
delete hCmp;
} } }
EOF
echo '==============================='
