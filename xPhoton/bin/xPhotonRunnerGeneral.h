#ifndef __xPhotonRunnerGeneral_h__
#define __xPhotonRunnerGeneral_h__
#include <iostream>
#include <sstream>
#include <string>

const char* GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
std::string GetDataEra (int argc, char* argv[]);
int         IntTranslater(char* val);
int main(int argc, char* argv[]);
#endif
