# xPhoton
inherited from RS's xPhoton_HFJet.C


current works:
histMgr
treeMgr
logging
readMgr
readgganalysis

histScaler.py : 
'''
  connect cross section - lumi per event - ntuple root file information 
'''

## ToDo 
- [ ] Accomplish histScaler.py and rename it.
- [-] Add version tag in each cross section matching.
- [x] Use CMSSW to compile the separated files.
- [ ] Use makefile and shared library to compile separated files. (Postponed...)
- [ ] .cc files are not protable for scram compiling.
## Meeting from Apr.15 2021 ##
- [ ] $\sigma_{ieie}$ : checks why background sample has strange tail
- [ ] $\sigma_{ieip}$ : why nothing in it?
- [ ] Need to check result after all modification!!!!!!!!!
* [ ] Reproduce HsinYei's result to prove my code is workable. (Use exactly same parameter and same plotting method)
* [x] Check the reason why all photon catched by xPhoton passes HLT_Photon175.
- [ ] MVA fitting : Don't use 100 bins. Use 10 bins only. Too many bins allow barely shape uncertainty.
