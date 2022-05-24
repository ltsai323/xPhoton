#!/usr/bin/env sh

file=$1

#root -b $file <<EOF
#TH2* H  = (TH2*) _file0->Get("btagDeepCSV/btagDeepCSV.0_0_0__0_7_2_1")
#TH1* k = (TH1*) H->ProjectionX()
#for ( int ibin = k->GetNbinsX()+1 ; ibin != 0 ; --ibin ) { printf(" ibin: %3d = sqrt(val): %15.2f -- err: %15.2f\n",ibin, sqrt(k->GetBinContent(ibin) ), k->GetBinError(ibin) ); }
#k->Draw()
#c1->SaveAs("hi.png")
#
#EOF

root -b $file <<EOF
TH1* k  = (TH1*) _file0->Get("btagDeepCSV/btagDeepCSV.0_0_0__0_7_2_1")
for ( int ibin = k->GetNbinsX()+1 ; ibin != 0 ; --ibin ) { printf(" ibin: %3d = sqrt(val): %15.2f -- err: %15.2f\n",ibin, sqrt(k->GetBinContent(ibin) ), k->GetBinError(ibin) ); }
k->Draw()
c1->SaveAs("hiold.png")

EOF
