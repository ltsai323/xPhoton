#!/usr/bin/env sh

file=$1

root -b $file <<EOF
TH2* H  = (TH2*) _file0->Get("btagDeepCSV/btagDeepCSV.0_0_0__0_0_7__2_1")
TH2* H1 = (TH2*) _file0->Get("btagDeepCSV/btagDeepCSV.0_0_0__0_1_7__2_1")
TH2* H2 = (TH2*) _file0->Get("btagDeepCSV/btagDeepCSV.0_0_0__0_2_7__2_1")

TH1* k = (TH1*) H->ProjectionX()
k->Add( H1->ProjectionX())
k->Add( H2->ProjectionX())
for ( int ibin = k->GetNbinsX()+1 ; ibin != 0 ; --ibin ) { printf(" ibin: %3d = sqrt(val): %15.2f -- err: %15.2f\n",ibin, sqrt(k->GetBinContent(ibin) ), k->GetBinError(ibin) ); }
k->Draw()
c1->SaveAs("hinew.png")

EOF

