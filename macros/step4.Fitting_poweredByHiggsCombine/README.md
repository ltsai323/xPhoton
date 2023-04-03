BDT score fitting bin by bin.
| Fitting component | description | example |
| - | - |
| Fit target | data in signal region | bin_0_0_0/BDT_data_signalRegion |
| signal | signal MC in signal region | bin_0_0_0/BDT_gjet_signalRegion_norm |
| signal shape uncertainties | shape uncertainty comes from shower shape correction. Corrected value is central value and original value goes to 1 sigma uncertainty. | bin_0_0_0/BDT_gjet_signalRegion_shapeUncUp_norm |
| background | data in data sideband. This uses data driven method. | bin_0_0_0/BDT_data_dataSideband_norm |

### Notification before process codes
Here we used Higgs Combine package. Please check the combine package is well installed or not.
All python code is written in python3 so a CMSSW_11 or above version environment is required.


* run_higgscombine.sh
Main script to this code. Input argument 1. output label 2. input root file from step2.
Execute **run_single.sh** bin by bin. **run_single.sh** runs higgs combine in 1 bin.

 * **run_single.sh** 

output label is only used for compressed file.

* checkERR.sh
Check data entries is normal and draw shape uncertainties to check quality.
main function is **checkERR.C**.




collect_result.sh
extractFitValue.sh
testPLOT.sh
extractNumber.py
py_GetDataDetail_.py
py_GetDataDetail.py
py_makedatacard.py
plot.C
