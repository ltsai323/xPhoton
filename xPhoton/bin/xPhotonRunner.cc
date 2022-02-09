#include "xPhoton/xPhoton/bin/xPhotonRunner.h"
#include "xPhoton/xPhoton/interface/xPhotonHFJet_subVtxInfo.h"
#include <iostream>
#include <sstream>


void PrintHelp()
{
    std::cerr << "This executable needs 2 arguments : 'inputfile.root' and output ID" << std::endl;
}
const char* GetFileName(int argc, char* argv[])
{
    return argv[1];
}
int         GetOption  (int argc, char* argv[])
{
    return IntTranslater(argv[2]);
}
int IntTranslater(char* val)
{
    std::stringstream s;
    s << val;
    int c;
    s >> c;
    return c;
}

int main(int argc, char* argv[])
{
    if ( argc!=3 ) { PrintHelp(); throw std::invalid_argument("not enough argument\n"); }
    std::cout << "in file: " << GetFileName(argc, argv) << std::endl;
    std::cout << "output file ID: " << GetOption  (argc, argv) << std::endl;

    xPhotonHFJet(
            GetFileName(argc,argv),
            GetOption  (argc,argv),
            "2016ReReco"
            );
}
