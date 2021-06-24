This repository is ready for CMSSW and makefile. Eigher CMSSW or make are able to compile and run code in this repository.
Also, the shell scripts stored in subrepository/bin folder inform you how to use the exeutables compiled in this repository.

# Installation
```bash
git clone https://github.com/ltsai323/xPhoton
cd xPhoton/
source envsetup.sh
cd xPhoton/
make all
```

### xPhoton/bin/exe.xPhotonRunner in.root 3
inherited from RS's xPhoton_HFJet.C
Run the whole xPhotonn code.
First argument is input root file from ggAnalyzer and second output is a integer which is only used for output naming.
### xPhoton/bin/exe.AppendEventInfo 3.14e-1 in.root out.root
The code to add additional information in each event.
First argument is the MC cross section, second and third argument are the input and output root file from xPhoton.
### xPhoton/data/pythonparser/mcinfo_EXEC.py
Input the files to massively send crab job and read content to connect primary dataset and text file.
To extract MC informations in primary dataset.
### xPhoton/bin/exe.xElectronsRunner in.root 3
Building...
For Zee.



current works:
refactorying xPhoton_HFJet_dev_subVtx.C
histScaler.py : 
'''
  connect cross section - lumi per event - ntuple root file information 
'''

## ToDo 
- [ ] Accomplish histScaler.py and rename it.
- [ ] Add version tag in each cross section matching.
- [x] Use CMSSW to compile the separated files.
- [x] Use makefile and shared library to compile separated files. (Postponed...)
- [x] .cc files are not protable for scram compiling.
## Meeting from Apr.15 2021 ##
- [x] $\sigma_{ieie}$ : checks why background sample has strange tail
* It's OK
- [x] $\sigma_{ieip}$ : why nothing in it?
* The variable distributes normally.
- [x] Need to check result after all modification!!!!!!!!!
* [x] Reproduce HsinYei's result to prove my code is workable. (Use exactly same parameter and same plotting method)
* [x] Check the reason why all photon catched by xPhoton passes HLT_Photon175.
- [x] MVA fitting : Don't use 100 bins. Use 10 bins only. Too many bins allow barely shape uncertainty.
