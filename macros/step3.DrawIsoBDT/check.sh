#!/usr/bin/env sh

root -b <<EOF
TFile* fold = TFile::Open("isovsbdt_template.root");
TFile* fnew = TFile::Open("new.root");
TH1* HOLD = (TH1*) fold->Get("gjet_0_2_13_px1_chIso");
TH1* HNEW = (TH1*) fnew->Get("gjet_0_2_13_px1_chIso");

printf("comparison entries old and new : %.1f --- %.1f. diff = %.1f\n", HOLD->GetEntries(), HNEW->GetEntries(), HOLD->GetEntries()-HNEW->GetEntries() );
printf("comparison mean    old and new : %.1f --- %.1f. diff = %.1f\n", HOLD->GetMean   (), HNEW->GetMean   (), HOLD->GetMean   ()-HNEW->GetMean   () );
EOF
