#!/usr/bin/env sh

ifile=../step8.ClosureTest_SampleCreation/storeroot/fakesample0.root
#root -b <<EOF
#.L MakeHisto.C
#MakeHisto t("${ifile}", false)
#t.Loop()
#EOF
#mv output.root orig.root
root -b <<EOF
.L origmakehist.C+
MakeHisto t("${ifile}", false)
t.Loop()
EOF
echo 'new file processed'

if [ "$?" != "0" ]; then exit; fi
     
mv output.root new.root

echo 'start checking'
root -b orig.root > log.old <<EOF
char hname[50];

for ( int etabin = 0; etabin < 2; ++etabin ) {
for ( int jetbin = 0; jetbin < 3; ++jetbin ) {
for ( int  ptbin = 0;  ptbin <20; ++ ptbin ) {
    sprintf(hname, "h_BDT_%d_%d_%d_0", etabin,jetbin,ptbin);
    TH1* h = (TH1*)_file0->Get(hname);
    std::cout << "histname : " << h->GetName() << " with " << h->GetEntries() << " entries and mean=" << h->GetMean() << std::endl;
}}}
EOF
root -b new.root > log.new <<EOF
char hname[50];

for ( int etabin = 0; etabin < 2; ++etabin ) {
for ( int jetbin = 0; jetbin < 3; ++jetbin ) {
for ( int  ptbin = 0;  ptbin <20; ++ ptbin ) {
    sprintf(hname, "h_BDT_%d_%d_%d_0", etabin,jetbin,ptbin);
    TH1* h = (TH1*)_file0->Get(hname);
    std::cout << "histname : " << h->GetName() << " with " << h->GetEntries() << " entries and mean=" << h->GetMean() << std::endl;
}}}
EOF
diff log.old log.new

