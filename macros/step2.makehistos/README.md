### histogram naming 
| description | histogram name |
|--|--|
| BDT score | bin\_%d\_%d\_%d/BDT\_{sample}\_{CR} |
| normalized BDT score | bin\_%d\_%d\_%d/BDT\_{sample}\_{CR}\_norm |
| BDT shape uncertainty | bin\_%d\_%d\_%d/BDT\_{sample}\_{CR}\_shapeUncUp |
| normalized BDT shape uncertainty Up | bin\_%d\_%d\_%d/BDT\_{sample}\_{CR}\_shapeUncUp\_norm |
| normalized BDT shape uncertainty Down | bin\_%d\_%d\_%d/BDT\_{sample}\_{CR}\_shapeUncDown\_norm |
|-|-|
| jet tagging variable | {varname}\_{sample}\_{genPho}{QF}\_{CR}\_{unc} |
|-|-|
| b score              | jettag0\_{sample}\_{genPho}{QF}\_{CR}\_{unc} |
| CvsL                 | jettag1\_{sample}\_{genPho}{QF}\_{CR}\_{unc} |
| CvsB                 | jettag2\_{sample}\_{genPho}{QF}\_{CR}\_{unc} |
| sub jet vertex mass  | jettag3\_{sample}\_{genPho}{QF}\_{CR}\_{unc} |
|-|-|
| normalized b score              | jettag0\_{sample}\_{genPho}{QF}\_{CR}\_{unc}\_norm |
| normalized CvsL                 | jettag1\_{sample}\_{genPho}{QF}\_{CR}\_{unc}\_norm |
| normalized CvsB                 | jettag2\_{sample}\_{genPho}{QF}\_{CR}\_{unc}\_norm |
| normalized sub jet vertex mass  | jettag3\_{sample}\_{genPho}{QF}\_{CR}\_{unc}\_norm |


### binning descriptions
* bin\_%d\_%d\_%d is photon eta bin \- jet eta bin \- photon pt bin.
    - photon eta bin 0 \: photon in barrel region.
    - photon eta bin 1 \: photon in endcap region.
    - jet eta bin 0 \: jet in barrel region.
    - jet eta bin 1 \: jet in endcap region.
    - jet eta bin 2 \: no jet in this category. Single photon only.
    - photon pt bin 0~24 (Maximum value is forgot.)
* sample \: "data", "gjet" and "QCD".
* genPho (is generated photon) \: "GJets" and "DiJet". This comes from MC gen matching.
    - GJets \: Not a fake photon.
    - DiJet \: is fake photon.
* QF (Quark Flavour) \: "L", "C" and "B". This comes from jetHadFlvr code in MC sample.
    - L \: jetHadFlvr \= 0
    - C \: jetHadFlvr \= 4
    - B \: jetHadFlvr \= 5
* CR (Control Region) \: "signalRegion" and "dataSideband".
    - signal region \: barrel \= chIso\<2. endcap \= chIso\<1.5.
    - data sideband \: blah.
* unc \: uncertainties, every uncertainty has Up and Down.
    * "shapeUnc" \: Only in BDT score. Which is derived form Difference "calib_mva" and "mva".
    * "central" \: Only in jettags. Mean value. No Up and Down.
    * "PUweight" \: Only in jettags. Pile-up weight.
    * "Stat" \: Only in jettags. statistical uncertaintes.
    * Note that no any uncertainties in jetSecVtxMass.


### Samples of histogram names.
* lists
    * bin\_0\_1\_13/BDT\_data\_signalRegion
    * bin\_1\_0\_18/BDT\_gjet\_signalRegion\_norm
    * bin\_1\_0\_18/BDT\_gjet\_signalRegion\_shapeUncUp
    * bin\_1\_0\_18/BDT\_gjet\_signalRegion\_shapeUncUp\_norm
    * bin\_1\_2\_18/BDT\_QCD\_dataSideband\_shapeUncDown
    * bin\_1\_2\_18/BDT\_QCD\_dataSideband\_shapeUncDown\_norm


    * bin\_1\_0\_3/jettag0_data_dataSideband
    * bin\_1\_0\_3/jettag0_gjet_GJetsL_signalRegion_central
    * bin\_1\_0\_3/jettag0_gjet_DiJetL_dataSideband_PUweightUp
    * bin\_1\_0\_3/jettag0_gjet_GJetsL_signalRegion_PUweightUp_norm
    * bin\_1\_0\_3/jettag1_gjet_DiJetC_dataSideband_PUweightDown
    * bin\_1\_0\_3/jettag1_gjet_GJetsC_signalRegion_PUweightDown_norm
    * bin\_1\_0\_3/jettag1_QCD_GJetsC_dataSideband_StatUp
    * bin\_1\_0\_3/jettag2_QCD_DiJetB_signalRegion_StatUp_norm
    * bin\_1\_0\_3/jettag2_QCD_GJetsB_dataSideband_StatDown
    * bin\_1\_0\_3/jettag2_QCD_DiJetB_signalRegion_StatDown_norm
    * bin\_1\_0\_3/jettag3_gjet_DiJetB_signalRegion > \(No any uncertainty at jettag3\)

### photon pt bin and HLT bin definition
| pt bin | HLT bin | pt range |
| - | - |
| 0 | 0|  25-34  |
| 1 | 1|  34-40  |
| 2 | 2|  41-56  |
| 3 | 3|  56-70  |
| 4 | 3|  70-85  |
| 5 | 4|  85-100 |
| 6 | 5| 100-115 |
| 7 | 5| 115-135 |
| 8 | 6| 135-155 |
| 9 | 6| 155-175 |
|10 | 6| 175-190 |
|11 | 7| 190-200 |
|12 | 7| 200-220 |
|13 | 7| 220-250 |
|14 | 7| 250-300 |
|15 | 7| 300-350 |
|16 | 7| 350-400 |
|17 | 8| 400-500 |
|18 | 8| 500-750 |
|19 | 8| 750-1000|
|20 | 8|1000-inf |
