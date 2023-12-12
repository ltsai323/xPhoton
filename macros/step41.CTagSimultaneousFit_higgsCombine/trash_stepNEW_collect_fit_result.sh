#!/usr/bin/env sh


echo 'pEtaBin/I:jEtaBin/I:pPtBin/I:frac_L/F:frac_C/F:frac_B/F:fit_yield_L/F:fit_yield_C/F:fit_yield_B/F: chi2_jet0/F:chi2_jet1/F:chi2_jet2/F' > ctag_fitting_result.dat


python3 combineFRAG3_collect_postfit_info.py >> ctag_fitting_result.dat
    
