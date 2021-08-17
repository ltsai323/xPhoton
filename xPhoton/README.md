- [x] this repository is CMSSW ready.
- [x] This repository is building for makefile.
- [x] Check what's the reason that too much .o makes multiple definition in g++ compiling
- [ ] (Posponed) Build shared library

## makefile linking procedure
``` bash
g++ -c src/parts.cc -o obj/parts.o        -I../.. `root-config --cflags --libs`
g++ -c bin/main.cc  -o obj/main.o         -I../.. `root-config --cflags --libs`
g++ obj/parts.o main.o  -o bin/exec.mybin -I../.. `root-config --cflags --libs`
```


folder illustration : <br/>
bin           : executables for this subrepository<br/>
src\interface : stable codes and used codes put .cc and .h files<br/>
data          : put text files<br/>
python        : python library can be imported<br/>
scripts       : Some bash or python scripts can be directly executed.<br/>
test          : test region. Do anything in this.<br/>
dev           : developing codes. Compile by makefile only<br/>

# data/pythonparser
Use it to analyze the log file of getXsec.py.

# bin/allexecutefiles
* ./bin/exe.AppendEventInfo 3.14e1 in.root out.root
Append information into events. Currently xs weight (31.4 as example) and BTagging corrections are appended in event.

* ./bin/exe.xElectronsRunner inputggNtuple.root 3
input a ggNtuple and run all events. The output name will be append a number "3". For electron. Zee event.
* ./bin/exe.xPhotonRunner inputggNtuple.root 3
input a ggNtuple and run all events. The output name will be append a number "3". For photon

## some variables in xPhoton outputs
JetID : 1 = passed and 0 = fail
PUJetIDbit : 1<<0 : loose, 1<<1), tight(1<<2)
phoIDbit : loose(1<<0), medium(1<<1), tight(1<<2)

(Only valid after AppendEventInfo.cc)
genWeight = gen weight from MC
xsweight = xs or -1 * xs
crossSection = xs
integratedLuminosity = lumi in data
integratedGenWeight = sum of all gen weight in this primary dataset. Note that this result merges the extended MC sample and standard samples.

mcweight = cross section * data lumi * genweight / (Integrated genweight)


TNtuple nt_sumupgenweight records the integration of gen weight at each job. So once you need to get the full integrated gen weight, you need to sum up all events. ( The number of entries is the number of jobs)

