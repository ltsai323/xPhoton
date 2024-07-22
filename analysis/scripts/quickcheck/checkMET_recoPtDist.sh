
root -b /home/ltsai/ReceivedFile/GJet/data/crab_data_ResentHLT16_Run2016B_94XReReco_ver2v1.root <<EOF
TCanvas* canv = new TCanvas("canv", "", 1200,1000);
canv->SetFillColor(4000);
canv->SetFillStyle(4000);
t->Draw("MET/recoPt:recoPhi", "(recoEta>-1.4442&&recoEta<1.4442) && phoFiredTrgs>>7&1", "COLZ")
canv->SaveAs("METrecoPtoverPhi_pho175_barrel.pdf")
t->Draw("MET/recoPt:recoPhi", "!(recoEta>-1.4442&&recoEta<1.4442) && phoFiredTrgs>>7&1", "COLZ")
canv->SaveAs("METrecoPtoverPhi_pho175_endcap.pdf")

TCanvas* c1 = new TCanvas("c1", "", 1200,500);
c1->SetFillColor(4000);
c1->SetFillStyle(4000);
c1->Divide(2,1);
TPad* p1 = (TPad*) c1->cd(1);
p1->SetLogy();
p1->SetFillColor(4000);
p1->SetFillStyle(4000);
TPad* p2 = (TPad*) c1->cd(2);
p2->SetFillColor(4000);
p2->SetFillStyle(4000);
p2->SetLogy();

p1->cd();
t->Draw("MET/recoPt", "(recoEta>-1.4442&&recoEta<1.4442)");
p2->cd();
t->Draw("MET/recoPt", "(recoEta>-1.4442&&recoEta<1.4442) && phoFiredTrgs>>7&1");
c1->SaveAs("METrecoPt_barrel.pdf")

p1->cd();
t->Draw("MET/recoPt", "!(recoEta>-1.4442&&recoEta<1.4442)");
p2->cd();
t->Draw("MET/recoPt", "!(recoEta>-1.4442&&recoEta<1.4442) && phoFiredTrgs>>7&1");
c1->SaveAs("METrecoPt_endcap.pdf")
EOF
