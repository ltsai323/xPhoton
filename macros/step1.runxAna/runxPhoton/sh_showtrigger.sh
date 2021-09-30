ent=$1
echo $ent
root -b output_job_PhotonHFJet_${ent}.root <<EOF
t->GetEntries()
std::cout<<"hltEG22HEFilter  in bit 0\n"; t->Draw("recoPt","(phoFiredTrgs>>0)&1")
std::cout << "               events fired this trigger\n\n";
std::cout<<"hltEG30HEFilter  in bit 1\n"; t->Draw("recoPt","(phoFiredTrgs>>1)&1")
std::cout << "               events fired this trigger\n\n";
std::cout<<"hltEG36HEFilter  in bit 2\n"; t->Draw("recoPt","(phoFiredTrgs>>2)&1")
std::cout << "               events fired this trigger\n\n";
std::cout<<"hltEG50HEFilter  in bit 3\n"; t->Draw("recoPt","(phoFiredTrgs>>3)&1")
std::cout << "               events fired this trigger\n\n";
std::cout<<"hltEG75HEFilter  in bit 4\n"; t->Draw("recoPt","(phoFiredTrgs>>4)&1")
std::cout << "               events fired this trigger\n\n";
std::cout<<"hltEG90HEFilter  in bit 5\n"; t->Draw("recoPt","(phoFiredTrgs>>5)&1")
std::cout << "               events fired this trigger\n\n";
std::cout<<"hltEG120HEFilter in bit 6\n"; t->Draw("recoPt","(phoFiredTrgs>>6)&1")
std::cout << "               events fired this trigger\n\n";
std::cout<<"hltEG175HEFilter in bit 7\n"; t->Draw("recoPt","(phoFiredTrgs>>7)&1")
std::cout << "               events fired this trigger\n\n";
std::cout<<"hltEG300HEFilter in bit 8\n"; t->Draw("recoPt","(phoFiredTrgs>>8)&1")
std::cout << "               events fired this trigger\n\n";
EOF
grep " $ent :" kk | grep '#'
