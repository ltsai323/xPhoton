
for path in `echo crab*`; do
    if [ "`ls $path/running*`" != "" ]; then
        echo "$path still running"
        echo $path >> tmpFile.txt
    else
        echo "$path finished"
        hadd $path.root $path/output*.root
    fi
done
