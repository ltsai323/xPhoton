- [x] this repository is CMSSW ready.
- [x] This repository is building for makefile.
- [ ] Check what's the reason that too much .o makes multiple definition in g++ compiling

## makefile linking procedure
``` bash
g++ -c src/parts.cc -o obj/parts.o        -I../.. `root-config --cflags --libs`
g++ -c bin/main.cc  -o obj/main.o         -I../.. `root-config --cflags --libs`
g++ obj/parts.o main.o  -o bin/exec.mybin -I../.. `root-config --cflags --libs`
```

