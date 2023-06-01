
for bpe in {0..1}; do
    for bje in {0..1}; do
        for bpp in {0..20}; do

    ifile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/deepcsv_CUT_NOCUT/logs/log_${bpe}_${bje}_${bpp}

    ls $ifile >/dev/null || continue

    sh extractFitValue.sh $ifile $bpe $bje $bpp fityield.dat bkgestimation.dat
done
done
done
