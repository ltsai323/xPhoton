#/bin/csh -f

### i = [0,3]       : is EB or EE
### j = 2           : jet bin
### n = [10,22]     : photon pt bin
### rebinoption = 1 : 
#@ n = 10
@ phoPtBin = 0
while ( $phoPtBin < 16 )
  foreach phoEtaIdx(0 1)
    foreach jetEtaIdx(0 1 2)
	root.exe -l -b -q Draw_IsovsBDT.C\(${phoEtaIdx},${jetEtaIdx},${phoPtBin},1\)
	mv isovsbdt.root iso_${phoEtaIdx}_${jetEtaIdx}_${phoPtBin}.root
    end
  end
@ phoPtBin += 1
end

hadd -f isovsbdt_template.root iso_*.root
rm -f iso_*.root
