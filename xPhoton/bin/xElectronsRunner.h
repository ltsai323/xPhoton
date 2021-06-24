#ifndef __xElectronsRunner_h__
#define __xElectronsRunner_h__
#include <iostream>
#include <sstream>

const char* GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
int         FromCharToInt(char* val);
int main(int argc, char* argv[]);
#endif
