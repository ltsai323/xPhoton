#!/usr/bin/env sh

lightcut=1      #0 for no-cut; 1 for svxmass-cut; 2 for cvsl-cut        
mcweightcut=1   #0 for no-cut; 1 for mcweight-cut
if [ ${mcweightcut} -eq 0 ]
then
  weicut=off
else
  weicut=on
fi
outputdir=./storeroot_mcweightcut_${weicut}_lightcut_${lightcut}
output_data=${outputdir}/makehisto_data.root
output_mc=${outputdir}/makehisto_sig_madgraph.root
output_qcd=${outputdir}/makehisto_QCD_madgraph.root

mkdir -p ${outputdir}

root -b <<EOF
.L MakeHisto.C+
MakeHisto t(1)
t.Loop(${lightcut})
EOF
mv output.root ${output_data}

root -b <<EOF
.L MakeHisto.C+
MakeHisto t(2)
t.Loop(${lightcut})
EOF
mv output.root ${output_mc}

root -b <<EOF
.L MakeHisto.C+
MakeHisto t(3)
t.Loop(${lightcut})
EOF
mv output.root ${output_qcd}
