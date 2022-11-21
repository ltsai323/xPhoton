#ifndef __xQCDRunner2016ReReco_h__
#define __xQCDRunner2016ReReco_h__
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
int         IntTranslater(char* val);
int main(int argc, char* argv[]);
#endif
