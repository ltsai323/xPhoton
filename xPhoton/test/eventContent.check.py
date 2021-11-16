#!/usr/bin/env python2
import ROOT

def Photon_PromptFinalStat(event):
    #return [ mompid for pid,mompid,pStat in zip(event.mcPID,event.mcMomPID,event.mcStatusFlag) if pid==22 if pStat>>1&1 ]
    return { idx:event.mcMomPID[idx] for idx,pStat in enumerate(event.mcStatusFlag) if event.mcPID[idx]==22 if pStat>>1&1 }
def Photon_FromHardProcess(event):
    #return [ mompid for pid,mompid,pStat in zip(event.mcPID,event.mcMomPID,event.mcStatusFlag) if pid==22 if pStat>>0&1 ]
    return { idx:event.mcMomPID[idx] for idx,pStat in enumerate(event.mcStatusFlag) if event.mcPID[idx]==22 if pStat>>0&1 }
def Add1(myDict,key):
    if not key in myDict:
        myDict[key]=1
    else:
        myDict[key]+=1

if __name__ == '__main__':
    myfile=ROOT.TFile.Open('ggtree_mc_1.root')
    mytree=myfile.Get('ggNtuplizer/EventTree')

    print 'start'
    i=0

    hgenphoton=ROOT.TH1F('hgenphoton','checking gen photon', 20, 0., 20.)
    hgenphotonSize=ROOT.TH1F('hgenphotonSize','size of gen photon', 20, 0., 20.)
    ofile=ROOT.TFile('results.root', 'recreate')
    newtree=ROOT.TTree('newtree','newtree')

    from array import array
    calIso=array('f', [0.])
    trkIso=array('f', [0.])
    RchIso=array('f', [0.])
    RphIso=array('f', [0.])
    recoId=array('i', [0 ])
    newtree.Branch('calIso', calIso, 'calIso/F')
    newtree.Branch('trkIso', trkIso, 'trkIso/F')
    newtree.Branch('RchIso', RchIso, 'RchIso/F')
    newtree.Branch('RphIso', RphIso, 'RphIso/F')
    newtree.Branch('recoId', recoId, 'recoId/I')

    nPho=0
    hasRecoPho=0
    nMatchedLeadingPho=0
    nMatchedPhoton=0
    matchedRecoPhoIdx={}
    mothers={}
    duplicates={}

    leadingPho_mcCalIso={}
    leadingPho_mcTrkIso={}
    NonLeadPho_mcCalIso={}
    NonLeadPho_mcTrkIso={}
    for event in mytree:
        calIso[0]=0.
        trkIso[0]=0.
        RchIso[0]=0.
        RphIso[0]=0.
        recoId[0]=0
        for photonIdx,photonID in enumerate(event.mcPID):
            if photonID != 22: continue
            if abs(event.mcMomPID[photonIdx]) > 10 and event.mcMomPID[photonIdx] != 21: continue
            statFlag=event.mcStatusFlag[photonIdx]
            stat=event.mcStatus[photonIdx]


            # preselections
            if event.mcPt[photonIdx] < 15.: continue
            abseta=abs(event.mcEta[photonIdx])
            if abseta > 3.0: continue
            if abseta > 1.4442 and abseta < 1.566: continue
            # is final state
            if stat != 1: continue
            if event.mcStatusFlag[photonIdx] >>0&1 == 0: continue
            if event.mcStatusFlag[photonIdx] >>1&1 == 0: continue
            nPho+=1
            if event.mcMomPID[photonIdx] == 21: Add1(mothers, 'gluon')
            else: Add1(mothers, 'quark')

            # has reco photon
            if event.nPho == 0: continue
            hasRecoPho+=1

            genPho=ROOT.TLorentzVector()
            genPho.SetPtEtaPhiE(event.mcPt[photonIdx],event.mcEta[photonIdx],event.mcPhi[photonIdx],event.mcPt[photonIdx])

            duplicateChecking=0
            for recoPhoIdx in range(event.nPho):
                recoPho=ROOT.TLorentzVector()
                recoPho.SetPtEtaPhiE(event.phoEt[recoPhoIdx],event.phoEta[recoPhoIdx],event.phoPhi[recoPhoIdx],event.phoEt[recoPhoIdx])
                if recoPho.DeltaR(genPho) > 0.2: continue
                if (recoPho.Pt()-genPho.Pt())/genPho.Pt() > 0.35: continue
                calIso[0]=event.mcCalIsoDR04[photonIdx]
                trkIso[0]=event.mcTrkIsoDR04[photonIdx]
                RchIso[0]=event.phoPFChIso[recoPhoIdx]
                RphIso[0]=event.phoPFPhoIso[recoPhoIdx]
                recoId[0]=recoPhoIdx
                newtree.Fill()



                if recoPhoIdx == 0:
                    nMatchedLeadingPho+=1
                    Add1(leadingPho_mcTrkIso, 0 if event.mcTrkIsoDR04[photonIdx]==0 else 'Non zero')
                else:
                    Add1(NonLeadPho_mcTrkIso, 0 if event.mcTrkIsoDR04[photonIdx]==0 else 'Non zero')
                nMatchedPhoton+=1
                if duplicateChecking==0:
                    Add1(matchedRecoPhoIdx, recoPhoIdx)
                duplicateChecking+=1
            Add1(duplicates, duplicateChecking)
    ofile.cd()
    newtree.Write()
    ofile.Close()
    print 'total entries = %d' % mytree.GetEntries()
    print '%d gen photon located in fiducial region. And %s events contain reco photon.' % (nPho,hasRecoPho)
    print 'Mothers of selected gen photon are %s ' % repr(mothers)
    print '%d gen photon matched with reco leading photon.' % nMatchedLeadingPho
    print 'And %d gen photon matched with reco photon. Reco photon idx list is %s' % (nMatchedPhoton, repr(matchedRecoPhoIdx))
    print 'Each gen photon matches with %s reco photon.' % repr(duplicates)

    print '--'
    print '--'
    print 'mcTrkIso situation at leading photon : %s. Other : %s' % (repr(leadingPho_mcTrkIso),repr(NonLeadPho_mcTrkIso))
