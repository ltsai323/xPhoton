fileTrg=isovsbdt_template.root
fileCmp=$1

#root -b <<EOF
#TFile* fTrg = TFile::Open("$fileTrg");
#TFile* fCmp = TFile::Open("$fileCmp");
#
#for ( int pEtaBin = 1; pEtaBin < 2; ++pEtaBin ) {
#for ( int jEtaBin = 1; jEtaBin < 2; ++jEtaBin ) {
#for ( int pPtBin = 1; pPtBin < 2; ++pPtBin ) {
#TH1D* hTrg = (TH1D*) fTrg->Get( Form("data_%d_%d_%d_px2_chIso",pEtaBin,jEtaBin,pPtBin) );
#TH1D* hCmp = (TH1D*) fCmp->Get( Form("photonFit_%d_%d_%d/data_sidebandRegion",pEtaBin,jEtaBin,pPtBin) );
#
#printf("checking integral of data in signal region (%d,%d,%d)\n",pEtaBin,jEtaBin,pPtBin);
#printf("  -- trg = %16.2f\n  -- cmp = %16.2f\n",hTrg->Integral(), hCmp->Integral() );
#printf("==========================\n");
#delete hTrg;
#delete hCmp;
#} } }
#EOF
#TH2F* hTrg = (TH2F*) fTrg->Get( Form("data_%d_%d_%d_all",pEtaBin,jEtaBin,pPtBin) );
#TH2F* hCmp = (TH2F*) fCmp->Get( Form("photonFit_%d_%d_%d/data_allRegion",pEtaBin,jEtaBin,pPtBin) );

root -b <<EOF
TFile* fTrg = TFile::Open("$fileTrg");
TFile* fCmp = TFile::Open("$fileCmp");

for ( int pEtaBin = 0; pEtaBin < 2; ++pEtaBin ) {
for ( int jEtaBin = 0; jEtaBin < 2; ++jEtaBin ) {
for ( int pPtBin = 0; pPtBin < 2; ++pPtBin ) {
TH1F* hTrg = (TH1F*) fTrg->Get( Form("data_%d_%d_%d_px1_chIso",pEtaBin,jEtaBin,pPtBin) );
Double_t nTrg = hTrg->GetEntries();
printf("At bin (%d,%d,%2d) : trg = %10.2f\n",pEtaBin,jEtaBin,pPtBin, nTrg);
delete hTrg;
} } }
EOF
