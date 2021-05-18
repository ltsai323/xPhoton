.PHONY: all clean check

# compiler setting
MAINCOMPILER=g++
USEROOT=`root-config --libs --cflags`
USEROOFIT=-lRooFitCore -lRooFit -lMinuit
MYLIB=../../

RootCOMPILER=$(MAINCOMPILER) $(USEROOT) -I$(MYLIB)
RooFitCOMPILER=$(MAINCOMPILER) $(USEROOFIT) -I$(MYLIB)
Compiler=$(RootCOMPILER)



# input files dependency
dirobj=obj
dirbin=bin
dirsrc=src

sources_src=$(wildcard src/*.cc)
sources_bin=$(wildcard bin/*.cc)



objfile_src=$(sources_src:src/%.cc=obj/%.o)
objfile_bin=$(sources_bin:bin/%.cc=obj/%.o)
#libfile_src=$(sources_src:src/%.cc=lib/%.so)
#libfile_bin=$(sources_bin:bin/%.cc=lib/%.so)
#allexecfile=$(sources_bin:bin/%.cc=bin/exe.%)
allexecfile=bin/exe.ParHistFormatter


all: $(allexecfile)
	@echo $(allexecfile)
	@echo '---- compile completed! ---'
	

################ Main Targets Here #########################3
bin/exe.ParHistFormatter: obj/ParHistFormatter.o $(objfile_src)
	$(Compiler) -o $@ $< $(objfile_src)
bin/exe.RooFit_ParFit_Pythia: obj/RooFit_ParFit_Pythia.o $(objfile_src)
	$(Compiler) -o $@ $< $(objfile_src)

################ Main Targets Ends #########################3


$(dirobj)/%.o: $(dirsrc)/%.cc
	@mkdir -p $(dir $@)
	$(Compiler) -o $@ -c $<
$(dirobj)/%.o: $(dirbin)/%.cc
	@mkdir -p $(dir $@)
	$(Compiler) -o $@ -c $<

check:
	@echo $(objfile_src)

clean:
	@echo "cleaning"
	-rm -r $(dirobj)
	-rm $(allexecfile)
	@echo "rm finished"

