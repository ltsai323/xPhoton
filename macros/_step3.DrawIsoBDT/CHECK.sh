#!/usr/bin/env sh
root -b iso_0_2_13.root   <<EOF
for ( int ibin = gjetChecking_0_2_13_px1_chIso->GetNbinsX() +1; ibin != 0 ; --ibin ) printf("bin num %d : raw err %.1f --- updated err %.1f\n", ibin, gjetChecking_0_2_13_px1_chIso->GetBinError(ibin), gjet_0_2_13_px1_chIso->GetBinError(ibin) );
EOF
