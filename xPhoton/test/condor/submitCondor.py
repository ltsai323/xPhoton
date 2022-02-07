#!/usr/bin/env python2
import os
def PrintHelp():
    raise IOError( '''--- This code needs 3 arguments ---
        1. time period option (int value). [{timestamp}]
        2. input executable command.
        3. input a text file containing file pathes.
        '''.format(timestamp=workperiod)
        )
templateSH_DownloadFirst='''#!/usr/bin/env sh

textPath=$1

outputDir=$PWD
if [ "$textPath" == "" ]; then
    echo "you need to input a text file"
    exit
fi
filenameOnly=`extractfilename.sh $textPath`
mydir=$filenameOnly


mkdir -p $outputDir/$mydir
idx=0
cd $outputDir/$mydir
for file in `cat $outputDir/$textPath`;
do
    xrdcp -f $file running.root
    exec_xPhotonRunnerUL2018 running.root $idx
    let "idx=idx+1"
    /bin/rm running.root
done

hadd ../$mydir.root output*.root
'''

template_condorScript='''universe = vanilla
Executable = {script}
+JobFlavour={period}
should_transfer_files = NO
use_x509userproxy = true
Output = /home/ltsai/condorlogs/log_job_$(Process)_output
Error  = /home/ltsai/condorlogs/log_job_$(Process)_error
Log    = /home/ltsai/condorlogs/log_job_$(Process)_log
RequestCpus = 1

max_retries = 1
Arguments  = $(filepath) {PWD}
Queue filepath from {pathlist}
'''
def checkexist(file):
    if not os.path.isfile(file):
        raise IOError('input file "%s" does not exist'%file)

workperiod={ 0:'espresso', 1:'longlunch', 2:'workday', 3:'tomorrow', 4:'testmatch', 5:'nextweek'}
def GetBashScript(argv):
    if len(argv) < 4: PrintHelp()

    nameSH='/tmp/ltsaiCondorSubmit.sh'
    fSH=open(nameSH,'w')
    fSH.write('#!/usr/bin/env sh\n')
    fSH.write( templateSH_DownloadFirst.format(exeFile=argv[2]) )
    fSH.close()
    return nameSH

def GetTimePeriod(argv):
    if len(argv) < 4: PrintHelp()
    return workperiod[ int(argv[1]) ]

def GetPathList(argv):
    if len(argv) < 4: PrintHelp()
    return argv[3]

###### simplified
template_condorScript_simplified='''universe = vanilla
Executable = {script}
+JobFlavour={period}
should_transfer_files = NO
use_x509userproxy = true
Output = /home/ltsai/condorlogs/log_job_$(Process)_output
Error  = /home/ltsai/condorlogs/log_job_$(Process)_error
Log    = /home/ltsai/condorlogs/log_job_$(Process)_log
RequestCpus = 1

max_retries = 1
Arguments  = {PWD}
queue
'''
templateSH_DownloadFirst_simplified='''#!/usr/bin/env sh

outputDir=$1
textPath={pathlist}

pwd
if [ "$textPath" == "" ]; then
    echo "you need to input a text file"
    exit
fi
filenameOnly=`extractfilename.sh $textPath`
mydir=$filenameOnly


mkdir -p $outputDir/$mydir
idx=0
for file in `cat $textPath`;
do
    xrdcp -f $file running.root
    {exeFile} running.root $idx
    let "idx=idx+1"
    mv output*.root $outputDir/$mydir/
done

hadd $outputDir/$mydir.root $outputDir/$mydir/output*.root
'''
def GetBashScript_simplified(argv):
    if len(argv) < 4: PrintHelp()

    nameSH='/tmp/ltsaiCondorSubmit.sh'
    fSH=open(nameSH,'w')
    fSH.write('#!/usr/bin/env sh\n')
    fSH.write( templateSH_DownloadFirst_simplified.format(exeFile=argv[2],pathlist=argv[3]) )
    fSH.close()
    return nameSH
if __name__ == '__main__':
    import sys
    #name_runningScript=GetBashScript(sys.argv)
    name_runningScript=GetBashScript_simplified(sys.argv)
    timestamp=GetTimePeriod(sys.argv)
    name_pathList=GetPathList(sys.argv)

    nameCondor='/tmp/condorSubmitScript.SUB'
    condorscript=open(nameCondor, 'w')
    #condorscript.write( template_condorScript.format(period=timestamp,pathlist=mypaths, script=name_runningScript, PWD=os.getcwd()) )
    condorscript.write( template_condorScript_simplified.format(period=timestamp, script=name_runningScript, PWD=os.getcwd()) )
    condorscript.close()
    os.system('condor_submit %s'%nameCondor)
