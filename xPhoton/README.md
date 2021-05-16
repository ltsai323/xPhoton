- [x] this repository is CMSSW ready.
- [ ] This repository is building for makefile.

## makefile linking procedure
``` bash
g++ -c src/parts.cc -o obj/parts.o
g++ -c bin/main.cc  -o obj/main.o
g++ obj/parts.o main.o  -o bin/exec.mybin
chmod 644 bin/exec.mybin
```

