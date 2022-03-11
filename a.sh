#!/usr/bin/env sh


file1=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/QCDMadgraph.root
file2=xPhoton/bin/mvaUpdated.QCDMadgraph.root

alias ROOT='root -b'
ROOT > loggings<<EOF
TFile* f1 = TFile::Open("$file1");
TFile* f2 = TFile::Open("$file2");

TTree* t1 = (TTree*) f1->Get("t");
TTree* t2 = (TTree*) f2->Get("t");

auto size = t1->GetEntries();
TRandom3 rnd;
std::vector<int> recordedRnds;
for ( int i=0; i<100; ++i ) recordedRnds.push_back( rnd.Uniform(size) );
for ( int i : recordedRnds ) t1->Show(i);
std::cout << "----------------------------\n";
for ( int i : recordedRnds ) t2->Show(i);
EOF
