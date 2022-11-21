fileTrg=$2
fileOrg=isovsbdt_template.root
fileCmp=newfile.root
inword=$1

if [ "$inword" == "sig" ]; then
    nameTrg=sig
    nameCmp=sign
    nameOrg=gjet
    echo 'signal sample!'
elif [ "$inword" == "qcd" ]; then
    nameTrg=qcd
    nameCmp=fake
    nameOrg=qcd
    echo 'qcd sample!'
elif [ "$inword" == "exp" ]; then
    nameTrg=exp
    nameCmp=data
    nameOrg=data
    echo 'data!'
fi



echo 'showing signal region status...'
root -b <<EOF
TFile* fTrg = TFile::Open("$fileTrg");
TFile* fOrg = TFile::Open("$fileOrg");

for ( int pEtaBin = 0; pEtaBin < 2; ++pEtaBin ) {
for ( int jEtaBin = 0; jEtaBin < 2; ++jEtaBin ) {
for ( int pPtBin = 0; pPtBin < 21; ++pPtBin ) {
TH1F* hTrg = (TH1F*) fTrg->Get( Form("testBDT${nameTrg}_signalRegion/testBDT${nameTrg}_signalRegion.%d_%d_%d",pEtaBin,jEtaBin,pPtBin) );
TH1F* hOrg = (TH1F*) fOrg->Get( Form("${nameOrg}_%d_%d_%d_px1_chIso",pEtaBin,jEtaBin,pPtBin) );

Double_t nTrg = hTrg->Integral(1, hTrg->GetNbinsX()+1);
Double_t nOrg = hOrg->Integral(1, hOrg->GetNbinsX()+1);
Double_t diff = nTrg-nOrg;
if ( fabs(diff) > 1e-1 ) {
printf("At bin (%d,%d,%2d) : trg = %10.2f and orig= %10.2f. Diff = %8.2f in %4.2f%%\n",pEtaBin,jEtaBin,pPtBin, nTrg,nOrg,diff, 100. * diff / nTrg);
}
delete hTrg;
delete hOrg;
} } }
EOF
echo '==============================='
