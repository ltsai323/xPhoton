grep matching logging | sort | uniq -c
echo "totally mismatching : " `grep matching logging -c `
echo `grep candidate logging -c` ' gen electron has 2 gen candidates. Greater pt electron is selected'
