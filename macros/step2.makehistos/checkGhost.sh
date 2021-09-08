root -b /home/ltsai/ReceivedFile/GJet/test/RSpreviousSample/output_MakeHisto.C.root <<EOF
std::cout << h_BDT_all_0_0_12_0->GetEntries() + \
             h_BDT_all_1_0_12_0->GetEntries() + \
             h_BDT_all_0_1_12_0->GetEntries() + \
             h_BDT_all_1_1_12_0->GetEntries() + \
             h_BDT_all_0_2_12_0->GetEntries() + \
             h_BDT_all_1_2_12_0->GetEntries() <<std::endl;
TH1* h = (TH1*)h_BDT_all_0_0_12_0->Clone();
h->Add(h_BDT_all_1_0_12_0);
h->Add(h_BDT_all_0_1_12_0);
h->Add(h_BDT_all_1_1_12_0);
h->Add(h_BDT_all_0_2_12_0);
h->Add(h_BDT_all_1_2_12_0);

std::cout << h_BDT_0_0_12_0->GetEntries() + \
             h_BDT_1_0_12_0->GetEntries() + \
             h_BDT_0_1_12_0->GetEntries() + \
             h_BDT_1_1_12_0->GetEntries() + \
             h_BDT_0_2_12_0->GetEntries() + \
             h_BDT_1_2_12_0->GetEntries() <<std::endl;
TH1* hs = (TH1*)h_BDT_0_0_12_0->Clone();
hs->Add(h_BDT_1_0_12_0);
hs->Add(h_BDT_0_1_12_0);
hs->Add(h_BDT_1_1_12_0);
hs->Add(h_BDT_0_2_12_0);
hs->Add(h_BDT_1_2_12_0);
std::cout << "rs code : " << hs->GetEntries()  << " (cut) " << std::endl;


TFile* fnews = TFile::Open("/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/outputParHists_data_testsample.root");
TH1* mvanews = (TH1*) fnews->Get("mva_past");
std::cout << "my code : " << mvanews->GetEntries() << std::endl;
mvanews->SetLineWidth(0);
mvanews->SetFillColor(3);


h->SetTitle("BDT all EBEE0To1_Jet0To1_ptbin12_true0");
hs->SetTitle("BDT all EBEE0To1_Jet0To1_ptbin12_true0 (cut)");
mvanews->Draw();
hs->Draw("same");
c1->SaveAs("try.png");
EOF
