#include "xPhoton/xPhoton/bin/xQCDRunner.h"
#include "xPhoton/xPhoton/interface/xQCDChecker.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <string>


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

    xQCDChecker(
            GetFileName(argc,argv),
            GetOption  (argc,argv),
            "2016ReReco"
            );
}
