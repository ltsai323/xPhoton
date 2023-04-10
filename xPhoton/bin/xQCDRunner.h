#ifndef __xQCDRunner_h__
#define __xQCDRunner_h__
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// this file execute in QCD MC only
// Photon pre-selection is abandoned to preserve jet behaviour.

std::vector<std::string> GetFileName(int argc, char* argv[]);
int         GetOption  (int argc, char* argv[]);
int         IntTranslater(char* val);
int main(int argc, char* argv[]);
#endif
