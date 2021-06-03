#/bin/sh -f


for (( n=0; n<=29; n++ ))
do
    for j in 0 1 2
    do 
	root.exe -l -b -q Draw_IsovsBDT.C\(\"EB\",${j},${n},1\)
	mv isovsbdt.root iso_EB_${j}_${n}.root
	root.exe -l -b -q Draw_IsovsBDT.C\(\"EE\",${j},${n},1\)
	mv isovsbdt.root iso_EE_${j}_${n}.root
    done
done

hadd -f isovsbdt_template.root iso_E*.root
rm -f iso_E*.root
