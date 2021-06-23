#ifndef __xElectrons_h__
#define __xElectrons_h__
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <TTree.h>
#include <TFile.h>


void xElectrons(
        std::vector<std::string> pathes,
        char oname[200]);

void xElectrons(std::string ipath, int outID);
#endif
