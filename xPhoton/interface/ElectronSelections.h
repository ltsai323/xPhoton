#ifndef electronselections
#define electronselections
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include <vector>

std::vector<int> ElectronIDCutBased2015(TreeReader &data, Int_t WP, std::vector<int> &accepted);
#endif
