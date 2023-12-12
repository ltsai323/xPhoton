#!/usr/bin/env python3

run() {
outfolder=$1
inputfile=$outfolder/out_mergeMG5Result.dat
python3 PhotonCrossSection_RefComp.py $inputfile
mv *.pdf $outfolder
}


outfolder=NLO_loop_sm_no_b_mass_CT14nlo
run $outfolder
outfolder=NLO_loop_sm_no_b_mass_CT14nnlo
run $outfolder
outfolder=NLO_loop_sm_no_b_mass_NNPDF3p1nlo
run $outfolder
outfolder=NLO_loop_sm_no_b_mass_NNPDF3p1nnlo
run $outfolder
