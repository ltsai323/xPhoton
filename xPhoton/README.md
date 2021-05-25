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
