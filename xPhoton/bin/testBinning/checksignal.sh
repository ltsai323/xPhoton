fileTrg=isovsbdt_template.root
fileCmp=$1


## echo 'showing signal region status...'
## root -b <<EOF
## TFile* fTrg = TFile::Open("$fileTrg");
## TFile* fCmp = TFile::Open("$fileCmp");
## 
## for ( int pEtaBin = 0; pEtaBin < 2; ++pEtaBin ) {
## for ( int jEtaBin = 0; jEtaBin < 2; ++jEtaBin ) {
## for ( int pPtBin = 0; pPtBin < 21; ++pPtBin ) {
## TH1F* hTrg = (TH1F*) fTrg->Get( Form("gjet_%d_%d_%d_px1_chIso",pEtaBin,jEtaBin,pPtBin) );
## TH1F* hCmp = (TH1F*) fCmp->Get( Form("photonFit_%d_%d_%d/sign_signalRegion",pEtaBin,jEtaBin,pPtBin) );
## 
## Double_t nTrg = hTrg->Integral(1, hTrg->GetNbinsX()+1);
## Double_t nCmp = hCmp->Integral(1, hCmp->GetNbinsX()+1);
## nTrg=hTrg->GetEntries();
## nCmp = hCmp->GetEntries();
## Double_t diff = nTrg-nCmp;
## if ( fabs(diff) > 1e-1 ) {
## printf("At bin (%d,%d,%2d) : trg = %10.2f and cmp = %10.2f. Diff = %8.2f in %4.2f%%\n",pEtaBin,jEtaBin,pPtBin, nTrg,nCmp,diff, 100. * diff / nTrg);
## }
## delete hTrg;
## delete hCmp;
## } } }
## EOF
## echo '==============================='
## echo 'showing sideband region status.'
## root -b <<EOF
## TFile* fTrg = TFile::Open("$fileTrg");
## TFile* fCmp = TFile::Open("$fileCmp");
## 
## for ( int pEtaBin = 0; pEtaBin < 2; ++pEtaBin ) {
## for ( int jEtaBin = 0; jEtaBin < 2; ++jEtaBin ) {
## for ( int pPtBin = 0; pPtBin < 21; ++pPtBin ) {
## TH1F* hTrg = (TH1F*) fTrg->Get( Form("gjet_%d_%d_%d_px2_chIso",pEtaBin,jEtaBin,pPtBin) );
## TH1F* hCmp = (TH1F*) fCmp->Get( Form("photonFit_%d_%d_%d/sign_sidebandRegion",pEtaBin,jEtaBin,pPtBin) );
## 
## //Double_t nTrg = hTrg->Integral(1, hTrg->GetNbinsX()+1);
## //Double_t nCmp = hCmp->Integral(1, hCmp->GetNbinsX()+1);
## Double_t nTrg = hTrg->GetEntries();
## Double_t nCmp = hCmp->GetEntries();
## Double_t diff = nTrg-nCmp;
## if ( fabs(diff) > 1e-1 ) {
## printf("At bin (%d,%d,%2d) : trg = %10.2f and cmp = %10.2f. Diff = %8.2f in %4.2f%%\n",pEtaBin,jEtaBin,pPtBin, nTrg,nCmp,diff, 100. * diff / nTrg);
## }
## delete hTrg;
## delete hCmp;
## } } }
## EOF
## echo '==============================='
echo 'showing all region status......'
root -b <<EOF
TFile* fTrg = TFile::Open("$fileTrg");
TFile* fCmp = TFile::Open("$fileCmp");

Double_t totEntriesTrg = 0;
Double_t totEntriesCmp = 0;
for ( int pEtaBin = 0; pEtaBin < 2; ++pEtaBin ) {
for ( int jEtaBin = 0; jEtaBin < 2; ++jEtaBin ) {
for ( int pPtBin = 0; pPtBin < 21; ++pPtBin ) {
TH1F* hTrg = (TH1F*) fTrg->Get( Form("gjet_%d_%d_%d_all",pEtaBin,jEtaBin,pPtBin) );
TH1F* hCmp = (TH1F*) fCmp->Get( Form("photonFit_%d_%d_%d/sign_allRegion",pEtaBin,jEtaBin,pPtBin) );

Double_t nTrg = hTrg->Integral(1, hTrg->GetNbinsX()+1);
Double_t nCmp = hCmp->Integral(1, hCmp->GetNbinsX()+1);
nTrg=hTrg->GetEntries();
nCmp = hCmp->GetEntries();
totEntriesTrg+=nTrg;
totEntriesCmp+=nCmp;
Double_t diff = nTrg-nCmp;
if ( fabs(diff) > 1e-1 ) {
printf("At bin (%d,%d,%2d) : trg = %10.2f and cmp = %10.2f. Diff = %8.2f in %4.2f%%\n",pEtaBin,jEtaBin,pPtBin, nTrg,nCmp,diff, 100. * diff / nTrg);
}
delete hTrg;
delete hCmp;
} } }

Double_t totdiff = totEntriesTrg-totEntriesCmp;
printf("tot entries : trg = %10.2f and cmp = %10.2f. Diff = %8.2f in %4.2f%%\n",totEntriesTrg, totEntriesCmp,totdiff, 100. * totdiff / totEntriesTrg);

EOF
echo '==============================='
