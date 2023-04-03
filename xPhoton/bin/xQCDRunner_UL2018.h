#ifndef __xQCDRunnerUL2018_h__
#define __xQCDRunnerUL2018_h__
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
int         IntTranslater(char* val);
int main(int argc, char* argv[]);
#endif
