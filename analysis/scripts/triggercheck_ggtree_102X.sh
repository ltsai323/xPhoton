#!/usr/bin/env sh

hltbit_goal=$2
hltbit_base=$1

#std::vector<const char*> trigpath = { "hltEG22HEFilter", "hltEG30HEFilter", "hltEG36HEFilter", "hltEG50HEFilter", "hltEG75HEFilter", "hltEG90HEFilter", "hltEG120HEFilter", "hltEG175HEFilter", "hltEG300erEtFilter" }; 

root -b ggtree.root <<EOF
ggNtuplizer->cd()

std::vector<const char*> trigpath = { "hltEG22HEFilter", "hltEG30HEFilter", "hltEG36HEFilter", "hltEG50HEFilter", "hltEG75HEFilter", "hltEG90HEFilter", "hltEG120HEFilter", "hltEG175HEFilter", "hltEG300erEtFilter", "hltEG22R9Id90HE10IsoMTrackIsoFilter", "hltEG30R9Id90HE10IsoMTrackIsoFilter", "hltEG36R9Id90HE10IsoMTrackIsoFilter", "hltEG50R9Id90HE10IsoMTrackIsoFilter", "hltEG75R9Id90HE10IsoMTrackIsoFilter", "hltEG90R9Id90HE10IsoMTrackIsoFilter", "hltEG120R9Id90HE10IsoMTrackIsoFilter", "hltEG165R9Id90HE10IsoMTrackIsoFilter", "hltEG250erEtFilter" };

std::vector<double> xval = { 22, 30, 36, 50, 60, 85, 100, 115, 135, 155, 175, 200, 250, 300, 400, 500, 750, 1000, 99999999 };
std::vector<double> yval_goal(xval.size()-1);
std::vector<double> yval_base(xval.size()-1);
std::vector<double> yval_both(xval.size()-1);



char title1[200];
char title0[200];
sprintf(title1,"@ HLTpath %d:%s (inst)", ${hltbit_goal},trigpath[${hltbit_goal}]);
sprintf(title0,"@ HLTpath %d:%s (base)", ${hltbit_base},trigpath[${hltbit_base}]);


TH1F* h1 = new TH1F("pt1",title1, 100, 0., 200.);
TH1F* h0 = new TH1F("pt0",title0, 100, 0., 200.);
TH1F* hA = new TH1F("ptA","pt dist at two AND trigger  ", 100, 0., 200.);
TH1F* hE = new TH1F("ptE","turn on at trigger $hltbit_goal / trigger $hltbit_base", 100, 0., 200.);


TCanvas* c1 = new TCanvas("c1","", 1000,1000);
c1->SetFrameFillColor(4000)
c1->SetFrameFillStyle(4000)
c1->SetFillColor(4000)
c1->SetFillStyle(4000)
c1->Divide(2,2);
c1->cd(1);
EventTree->Draw("phoEt>>pt1", "phoFiredSingleTrgs>>${hltbit_goal}&1");
EventTree->Draw("phoEt>>pt0", "phoFiredSingleTrgs>>${hltbit_base}&1");
EventTree->Draw("phoEt>>ptA", "phoFiredSingleTrgs>>${hltbit_goal}&1 && phoFiredSingleTrgs>>${hltbit_base}&1");

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


c1->SaveAs("checkHLT_${hltbit_goal}over${hltbit_base}.pdf")
EOF







