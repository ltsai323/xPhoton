This repository is ready for CMSSW.
Also, the shell scripts stored in subrepository/bin folder inform you how to use the exeutables compiled in this repository.

# Installation
```bash
cmsrel CMSSW_11_0_0_pre3
cd CMSSW_11_0_0_pre3/src

git clone https://github.com/ltsai323/xPhoton
git clone https://github.com/youyingli/ShowerShapeCorrection.git
scram b -j8
```

### exec_xPhotonRunner in.root 3
inherited from RS's xPhoton_HFJet.C
Run the whole xPhotonn code.
First argument is input root file from ggAnalyzer and second output is a integer which is only used for output naming.
### exec_AppendEventInfo 3.14e-1 in.root out.root
The code to add additional information in each event.
First argument is the MC cross section, second and third argument are the input and output root file from xPhoton.
### xPhoton/data/pythonparser/mcinfo_EXEC.py
Input the files to massively send crab job and read content to connect primary dataset and text file.
To extract MC informations in primary dataset.
### exec_xElectronsRunner in.root 3
Building...
For Zee.


# Special Note
* macro/step2.test.makehisto/step2_makehisto.C requires ROOT version > 6.14. So Only CMSSW12_0_0 or above version are able to run this code.
* However, lots of xPhoton code are written in python2, which is not compatible for python3.
