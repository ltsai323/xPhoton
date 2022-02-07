#!/usr/bin/env python2
localmesg='Process local files'
localcommand='cd /home/ltsai/Work/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/test ; mkdir -p {fold} && cd {fold} ; python ../xphoton_local.py {file} false'
remotemesg='Download 1 root file from T2 first and process it'
remotecommand='"export X509_USER_PROXY=/home/ltsai/.x509up_u54608; cd /home/ltsai/Work/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/test ; mkdir -p {fold} && cd {fold} ; python ../xphoton_remote.py {file} false"'
import os

if __name__ == '__main__':
    import sys
    mesg=localmesg
    command=localcommand

    print mesg
    flist=[ sys.argv[1] ]
    for f in flist:
        folder=f.split('/')[-1].split('.')[0]
        print folder
        os.system('{command} &'.format(command=command.format(fold=folder,file=f)))
