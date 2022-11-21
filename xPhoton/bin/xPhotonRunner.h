#ifndef __xPhotonRunner_h__
#define __xPhotonRunner_h__
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//const char* GetFileName(int argc, char* argv[]);
std::vector<std::string> GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
int         IntTranslater(char* val);
int main(int argc, char* argv[]);
#endif
