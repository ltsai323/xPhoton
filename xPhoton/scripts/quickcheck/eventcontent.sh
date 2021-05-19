# orig file
root -b $1 >log_data0 <<EOF
t->GetEntry( 3); t->Show()
t->GetEntry(27); t->Show()
t->GetEntry(99); t->Show()
t->GetEntry(38); t->Show()
t->GetEntry(73); t->Show()
t->GetEntries()
EOF

# new file
root -b $2 >log_data1 <<EOF
t->GetEntry( 3); t->Show()
t->GetEntry(27); t->Show()
t->GetEntry(99); t->Show()
t->GetEntry(38); t->Show()
t->GetEntry(73); t->Show()
t->GetEntries()
EOF


diff log_data0 log_data1
echo '<:log_data0    >:log_data1'


