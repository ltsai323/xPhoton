
theDIR='data/UL2016PreVFP_cutIdx4_mergeBin5_*CSV.yaml'
oFOLDER=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/DeepFlavour_gjetPythia_cutIdx4_mergeBin_5/cross_sections

for a in `ls $theDIR`;do echo $a; python3 PhotonCrossSection_inputCSV.py $a;done 
#for a in `ls $theDIR`;do echo $a; python3 PhotonCrossSection_inputCSV_nojEtaBin.py $a; done

mkdir -p $oFOLDER
mv *.csv $oFOLDER
echo outputs : $oFOLDER
