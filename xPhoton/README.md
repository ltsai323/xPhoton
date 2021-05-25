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


folder illustration : 
bin : executables for this subrepository
src\interface : stable codes and used codes put .cc and .h files
data : put text files
python : python library can be imported
scripts : Some bash or python scripts can be directly executed.
test : test region. Do anything in this.
dev : developing codes. Compile by makefile only
