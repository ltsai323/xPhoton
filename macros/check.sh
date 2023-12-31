function the_exit() { echo $1; exit; }

cd step2.makehistos/                           && sh check.sh || the_exit "step2 failed"
cd ../step4.Fitting_poweredByHiggsCombine/     && sh check.sh || the_exit "step3 failed"
cd ../step41.CTagSimultaneousFit_higgsCombine/ && sh check.sh || the_exit "step41 failed"
