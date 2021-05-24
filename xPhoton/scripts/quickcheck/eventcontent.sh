# orig file
root -b $1 >log_data0 <<EOF
for ( int i=0 ; i<20 ; ++i ) { t->GetEntry(i*10); t->Show(); }
t->GetEntries()
EOF

# new file
root -b $2 >log_data1 <<EOF
for ( int i=0 ; i<20 ; ++i ) { t->GetEntry(i*10); t->Show(); }
t->GetEntries()
EOF


diff log_data0 log_data1
echo '<:log_data0    >:log_data1'

#t->GetEntry( 3); t->Show()
#t->GetEntry(27); t->Show()
#t->GetEntry(99); t->Show()
#t->GetEntry(38); t->Show()
#t->GetEntry(73); t->Show()
#t->GetEntries()
#
