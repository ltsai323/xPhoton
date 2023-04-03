#include "xPhoton/xPhoton/bin/xElectronsRunner.h"
#include "xPhoton/xPhoton/interface/xElectrons.h"
#include <iostream>
#include <sstream>


void PrintHelp()
{
    std::cerr << "This executable needs 2 arguments : 'inputfile.root' and output ID" << std::endl;
}
std::vector<std::string> GetFileName(int argc, char* argv[])
{
    std::string infile(argv[1]);
    if ( infile.find(",") == std::string::npos ) return {infile};
    std::vector<std::string> out;
    
    std::size_t startidx = 0;
    while ( true )
    {
        std::size_t endedidx = infile.find(",", startidx);
        out.push_back(infile.substr(startidx,endedidx-startidx));
        startidx=endedidx+1;
        if ( endedidx == std::string::npos ) break;
    }

    return out;
}
int         GetOption  (int argc, char* argv[])
{
    return FromCharToInt(argv[2]);
}
int FromCharToInt(char* val)
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
    //std::cout << "in file: " << GetFileName(argc, argv) << std::endl;
    std::cout << "output file ID: " << GetOption  (argc, argv) << std::endl;

    xElectrons(
            GetFileName(argc,argv),
            GetOption  (argc,argv),
            "UL2016PreVFP"
            );
}
