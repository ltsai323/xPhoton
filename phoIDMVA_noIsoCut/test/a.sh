#!/usr/bin/env sh

name=MyTrainRes
root -b mvaUpdated.$name.root <<EOF
// t->Draw("mva", "isMatched == 1" );
// c1->SaveAs( Form("%s_%s.png","sigPho", "$name") );
// t->Draw("mva", "isMatched != 1" );
// c1->SaveAs( Form("%s_%s.png","bkgPho", "$name") );
t->Draw("mva", "isMatched == 1 && fabs(recoEta) > 1.5 && recoEta < 0" )
c1->SaveAs( Form("%s_%s.png","sigPho_MEta", "$name") )
t->Draw("mva", "isMatched == 1  && fabs(recoEta) > 1.5&& recoEta > 0" )
c1->SaveAs( Form("%s_%s.png","sigPho_PEta", "$name") )
EOF
echo 'To show the plot, you need to execute '
echo "icat sigPho_PEta_$name.png sigPho_MEta_$name.png"

