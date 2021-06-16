#!/usr/bin/env python2
command='"export X509_USER_PROXY=/home/ltsai/.x509up_u54608; cd /home/ltsai/Work/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/test ; mkdir -p {fold} && cd {fold} ; python ../xphoton_path.py {file} true"'
import os
flist=[
'/home/ltsai/Run2016B_94X.txt',
'/home/ltsai/Run2016C_94X.txt',
'/home/ltsai/Run2016D_94X.txt',
'/home/ltsai/Run2016E_94X.txt',
'/home/ltsai/Run2016F_94X.txt',
'/home/ltsai/Run2016G_94X.txt',
'/home/ltsai/Run2016H_94X.txt',
    ]

for f in flist:
    folder=f.split('/')[-1].split('.')[0]
    print folder
    os.system('/home/ltsai/script/qjob/submitJOB.py --command={} --name={}'.format(
        command.format(fold=folder,file=f),
        folder))
