#!/usr/bin/env sh

bit1=$2
bit0=$1

#std::vector<const char*> trigpath = { "hltEG22HEFilter", "hltEG30HEFilter", "hltEG36HEFilter", "hltEG50HEFilter", "hltEG75HEFilter", "hltEG90HEFilter", "hltEG120HEFilter", "hltEG175HEFilter", "hltEG300erEtFilter" }; 

root -b ggtree.root <<EOF
ggNtuplizer->cd()

std::vector<const char*> trigpath = { "hltEG22HEFilter", "hltEG30HEFilter", "hltEG36HEFilter", "hltEG50HEFilter", "hltEG75HEFilter", "hltEG90HEFilter", "hltEG120HEFilter", "hltEG175HEFilter", "hltEG300erEtFilter", "hltEG22R9Id90HE10IsoMTrackIsoFilter", "hltEG30R9Id90HE10IsoMTrackIsoFilter", "hltEG36R9Id90HE10IsoMTrackIsoFilter", "hltEG50R9Id90HE10IsoMTrackIsoFilter", "hltEG75R9Id90HE10IsoMTrackIsoFilter", "hltEG90R9Id90HE10IsoMTrackIsoFilter", "hltEG120R9Id90HE10IsoMTrackIsoFilter", "hltEG165R9Id90HE10IsoMTrackIsoFilter", "hltEG250erEtFilter" };

char title1[200];
char title0[200];
sprintf(title1,"@ HLTpath %d:%s (inst)", ${bit1},trigpath[${bit1}]);
sprintf(title0,"@ HLTpath %d:%s (base)", ${bit0},trigpath[${bit0}]);


TH1F* h1 = new TH1F("pt1",title1, 100, 0., 200.);
TH1F* h0 = new TH1F("pt0",title0, 100, 0., 200.);
TH1F* hA = new TH1F("ptA","pt dist at two AND trigger  ", 100, 0., 200.);
TH1F* hE = new TH1F("ptE","turn on at trigger $bit1 / trigger $bit0", 100, 0., 200.);


TCanvas* c1 = new TCanvas("c1","", 1000,1000);
c1->SetFrameFillColor(4000)
c1->SetFrameFillStyle(4000)
c1->SetFillColor(4000)
c1->SetFillStyle(4000)
c1->Divide(2,2);
c1->cd(1);
EventTree->Draw("phoEt>>pt1", "phoFiredSingleTrgs>>${bit1}&1");
EventTree->Draw("phoEt>>pt0", "phoFiredSingleTrgs>>${bit0}&1");
EventTree->Draw("phoEt>>ptA", "phoFiredSingleTrgs>>${bit1}&1 && phoFiredSingleTrgs>>${bit0}&1");

c1->cd(1);
h1->Draw();
c1->cd(2);
h0->Draw();
c1->cd(3);
hA->Draw();
c1->cd(4);

hE->Add(hA);
hE->Divide(h0);
hE->Draw();


c1->SaveAs("checkHLT_${bit1}over${bit0}.pdf")
EOF







