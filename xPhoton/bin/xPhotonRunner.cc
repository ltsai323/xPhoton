// #include "xPhoton/xPhoton/interface/xPhotonHFJet_subVtxInfo.h"
#include <iostream>
#include <sstream>

const char* GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
int         IntTranslater(char* val);

int main(int argc, char* argv[])
{
    std::cout << "in file: " << GetFileName(argc, argv) << std::endl;
    std::cout << "file id: " << GetOption  (argc, argv) << std::endl;

  //xPhotonHFJet(fileIn,option);
}
const char* GetFileName(int argc, char* argv[])
{
    if ( argc<2 ) throw std::invalid_argument("not enough argument: input root file needed\n");
    return argv[1];
}
int         GetOption  (int argc, char* argv[])
{
    if ( argc<3 ) throw std::invalid_argument("set a int argument");
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
