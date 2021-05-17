# orig file
root -b datasample_xPhotonHFJet_subVtxInfo.C.root >log_data0 <<EOF
t->GetEntry( 3); t->Show()
t->GetEntry(27); t->Show()
t->GetEntry(99); t->Show()
t->GetEntries()
EOF

# new file
root -b datasample_xPhotonHFJet_dev_subVtxInfo.C.root >log_data1 <<EOF
t->GetEntry( 3); t->Show()
t->GetEntry(27); t->Show()
t->GetEntry(99); t->Show()
t->GetEntries()
EOF


diff log_data0 log_data1
echo '<:orig     >:new     (data)'

root -b mcsample_xPhotonHFJet_subVtxInfo.C.root >log_mc0 <<EOF
t->GetEntry( 3); t->Show()
t->GetEntry(27); t->Show()
t->GetEntry(99); t->Show()
t->GetEntries()
EOF

# new file
root -b mcsample_xPhotonHFJet_dev_subVtxInfo.C.root >log_mc1 <<EOF
t->GetEntry( 3); t->Show()
t->GetEntry(27); t->Show()
t->GetEntry(99); t->Show()
t->GetEntries()
EOF


diff log_mc0 log_mc1
echo '<:orig     >:new     (mc)'
