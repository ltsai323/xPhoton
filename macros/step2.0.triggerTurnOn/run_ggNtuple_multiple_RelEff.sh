#!/usr/bin/env sh
in_file=$1
file_path=`realpath $1`
#file_path=$1


if [ "$file_path" == "" ]; then
    echo input a text file recording root file paths. Abort
    exit
fi

function thechdir() {
 working_dir=$1
 touch $working_dir ; /bin/rm -rf $working_dir
 mkdir $working_dir ; cd $working_dir
 for a in ../TriggerTurnOn*.py ;do ln -s $a;done
 for a in ../py_pt_ranges_definition.py ; do ln -s $a;done
}


 tot_num=`grep root $file_path | wc -l`
 num_jobs=$(( $tot_num / 5 ))


thechdir `basename $in_file .txt`

idx=0
#for rootfile in `cat $file_path`;do
for rootfiles in `cat5LinesWithComma.sh $file_path`;do
    bkgjob_submit_with_limitation_Nminus3.sh
    ((idx++))
    echo executing job $idx in $num_jobs
    python3 TriggerTurnOnGGNtupleMaterials_Relative.py $rootfiles result_${idx}.root > log_$idx 2>&1 &
done
echo 'all job submitted'
wait
echo 'all job finished'
hadd -f result.root result_*.root
#touch frags; /bin/rm -r frags
mkdir frags; mv result_*.root frags/; mv log* frags/

python3 turnon_curve_calculator.py results.root results_turn_on_curve.root
