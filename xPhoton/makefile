# all: bin/exec_ParHistFormatter bin/exec_RooFit_ParFit_Pythia
all: bin/exec_ParHistFormatter

MAINCOMPILER=g++
USEROOT=`root-config --libs --cflags`
USEROOFIT=-lRooFitCore -lRooFit -lMinuit
MYLIB=../

RootCOMPILER=$(MAINCOMPILER) $(USEROOT) -I$(MYLIB)
RooFitCOMPILER=$(MAINCOMPILER) $(USEROOFIT) -I$(MYLIB)



srcfiles=$(wildcard src/*.cc) 				 					# src/part1.cc src/part2.cc
src_objs=$(patsubst %.cc, %.cc.o, $(srcfiles)) 					# src/part1.cc -> src/part1.cc.o
srcfiles_nofolder=$(notdir $(srcfiles)) 						# src/part.cc -> part.cc
src_libs=$(patsubst %.cc, lib/lib%.so, $(srcfiles_nofolder)) 	# part.cc ->lib/libpart.so
binfiles=$(wildcard bin/*.cc) 									# bin/main.cc
bin_objs=$(patsubst %.cc, %.cc.o, $(objfiles))
exefiles=$(patsubst bin/%.cc, bin/exec_%, $(binfiles))
# binfiles_nofolder=$(notdir $(binfiles))
#exefiles=$(patsubst %.cc, 

#bin/exec_ParHistFormatter: obj/ParHistFormatter.cc.o $(src_objs)
bin/exec_ParHistFormatter: obj/ParHistFormatter.cc.o $(src_objs)
	echo $(src_objs)
	$(RootCOMPILER) -o $@ $< $(src_objs)

obj/ParHistFormatter.cc.o: bin/ParHistFormatter.cc
	$(RootCOMPILER) -o $@ -c $<


$(src_objs): $(srcfiles)
	$(RootCOMPILER) -o $@ -c $<


clean:
	echo "hi"

## all: usefulFuncs.o
## 
## MYLIB = .
## gccROOTFLAG=`root-config --libs --cflags`
## 
## 
## usefulFuncs.o: interface/usefulFuncs.h src/usefulFuncs.cc
## 	g++ -c src/usefulFuncs.cc -o obj/usefulFuncs.o -I$(MYLIB) $(gccROOTFLAG)
## 
## a: main.o part.o
## 	g++ -o a obj/main.o obj/part.o
## main.o: bin/test.cc
## 	g++ -c bin/test.cc -o obj/main.o  -I$(MYLIB)
## 
## b: main2.o part.o
## 	g++ -o b obj/main2.o obj/part.o
## main2.o: bin/test2.cc
## 	g++ -c bin/test2.cc -o obj/main2.o  -I$(MYLIB)
## 
## part.o: src/part.cc
## 	g++ -c src/part.cc -o obj/part.o -I$(MYLIB)
## 
## clean:
## 	/bin/rm -f a b obj/*
