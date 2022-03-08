This is the executables for xPhoton.
All of the executables comes from .cc files.
And almost all of them require input arguments,
you can see the related python or bash shell files to get input hint.
Or directly see the source code for hint.

## AppendBTagCalibration.cc
Used for BTagging 
## AppendEventInfo.cc
## checkJetIDRunner.cc
## xElectronsRunner.cc
## xPhotonInfoUpdate2.cc
## xPhotonInfoUpdate.cc

## xPhotonRunnerGeneral.cc
The generalized executable, you can input a string to control the data era.
This string is able to load the co-related BDT weight file, shower shape corrections.

Also, this file executes src/xPhotonBLAHBLAH.cc.
Which loading ggNtuple and select the gamma+jet event.
The event passed single photon HLT in all pt to preserve all leading photon event.
Each event only select leading photon and jet. (jet and photon are separated.)

* xPhotonRunner.cc : old code only for 2016ReReco
* xPhotonRunner2016ReReco.cc
* xPhotonRunner2017ReReco.cc
* xPhotonRunner2018ReReco.cc
* xPhotonRunnerUL2016.cc
* xPhotonRunnerUL2017.cc
* xPhotonRunnerUL2018.cc
