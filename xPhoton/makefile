.PHONY: all clean check test

# compiler setting
MAINCOMPILER=g++ -O2
USEROOT=`root-config --libs --cflags`
USEROOFIT=-lRooFitCore -lRooFit -lMinuit
USETMVA=-lTMVA
MYLIB=../../

RootCOMPILER=$(MAINCOMPILER) $(USEROOT) -I$(MYLIB)
RooFitCOMPILER=$(MAINCOMPILER) $(USEROOFIT) -I$(MYLIB)
Compiler=$(RootCOMPILER) $(USETMVA)



###### default compiling files setting #####
dirobj=obj
dirbin=bin
dirsrc=src

sources_src=$(wildcard src/*.cc)
sources_bin=$(wildcard bin/*.cc)

objfile_src=$(sources_src:src/%.cc=obj/%.o)
objfile_bin=$(sources_bin:bin/%.cc=obj/%.o)
#libfile_src=$(sources_src:src/%.cc=lib/%.so)
#libfile_bin=$(sources_bin:bin/%.cc=lib/%.so)
allexecfile=$(sources_bin:bin/%.cc=bin/exe.%)
#allexecfile=bin/exe.xPhotonRunner
### default compiling files setting end #####

all: $(allexecfile)
	@echo $(allexecfile)
	@echo '---- compile completed! ---'


###### declare test     ###########
dirdev=dev
sources_dev=$(wildcard    $(dirdev)/*.cc)
objfile_dev=$(sources_dev:$(dirdev)/%.cc=$(dirobj)/test_%.o)
test: dev/exe.test.xPhotonRunner
dev:  dev/exe.test.xElectronsRunner

dev/exe.test.xElectronsRunner: obj/xElectronsRunner.o $(objfile_src) $(objfile_dev)
	$(Compiler) -o $@ $< $(objfile_dev) \
    obj/ElectronSelections.o \
    obj/MuonSelections.o \
    obj/PhotonSelections.o \
    obj/histMgr.o \
    obj/puweicalc.o \
    obj/readMgr.o \
    obj/ExternalFilesMgr.o \
	obj/recoInfo.o \
    obj/untuplizer.o \
    obj/usefulFuncs.o \
	obj/BTagCalibrationStandalone.o \
	obj/BTaggingMgr.o \

	@echo "--- Successfully compiled " $@ " ---"
dev/exe.test.xPhotonRunner: obj/xPhotonRunner.o $(objfile_src) $(objfile_dev)
	$(Compiler) -o $@ $< $(objfile_dev) \
    obj/ElectronSelections.o \
    obj/MuonSelections.o \
    obj/PhotonSelections.o \
    obj/histMgr.o \
    obj/puweicalc.o \
    obj/readMgr.o \
    obj/ExternalFilesMgr.o \
    obj/untuplizer.o \
    obj/usefulFuncs.o \
	obj/BTagCalibrationStandalone.o \
	obj/BTaggingMgr.o
	@echo "--- Successfully compiled " $@ " ---"
###### declare test end ###########
#obj/PreselectionMgr.o \
#obj/mcMatchInfo.o \
#obj/treeMgr.o \



################ Main Targets Here #########################3

bin/exe.ParHistFormatter: obj/ParHistFormatter.o $(objfile_src)
	$(Compiler) -o $@ $< $(objfile_src)
bin/exe.RooFit_ParFit_Pythia: obj/RooFit_ParFit_Pythia.o $(objfile_src)
	$(Compiler) -o $@ $< $(objfile_src)
bin/exe.xPhotonRunner: obj/xPhotonRunner.o $(objfile_src)
	$(Compiler) -o $@ $< $(objfile_src)
bin/exe.xElectronsRunner: obj/xElectronsRunner.o $(objfile_src)
	$(Compiler) -o $@ $< $(objfile_src)
bin/exe.AppendEventInfo: obj/AppendEventInfo.o $(objfile_src)
	$(Compiler) -o $@ $< $(objfile_src)

################ Main Targets Ends #########################3


$(dirobj)/%.o: $(dirsrc)/%.cc
	@mkdir -p $(dir $@)
	$(Compiler) -o $@ -c $<
$(dirobj)/%.o: $(dirbin)/%.cc
	@mkdir -p $(dir $@)
	$(Compiler) -o $@ -c $<
$(dirobj)/test_%.o: $(dirdev)/%.cc
	@mkdir -p $(dir $@)
	$(Compiler) -o $@ -c $<

check:
	@echo $(objfile_src)

clean:
	@echo "cleaning"
	-rm -r $(dirobj)
	-rm $(allexecfile)
	@echo "rm finished"

