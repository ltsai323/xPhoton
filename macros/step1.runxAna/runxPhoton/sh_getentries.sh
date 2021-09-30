ent=$1
echo $ent
root -b output_job_PhotonHFJet_${ent}.root <<EOF
t->GetEntries()
t->Draw("recoPt","recoPt<180")
EOF
