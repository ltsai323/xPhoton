#!/usr/bin/env python2
import ROOT

def Add1(myDict,key):
    if not key in myDict:
        myDict[key]=1
    else:
        myDict[key]+=1
def inFiducialRegion(pt, eta):
    if pt < 15.: return False
    abseta=abs(eta)
    if abseta > 3.0: return False
    if abseta > 1.4442 and abseta < 1.566: return False
    return True

def selected(event):
    for photonIdx,photonID in enumerate(event.mcPID):
        if photonID != 22: continue
        if abs(event.mcMomPID[photonIdx]) > 10 and event.mcMomPID[photonIdx] != 21: continue
        if not inFiducialRegion(event.mcPt[photonIdx], event.mcEta[photonIdx]): continue

        # is final state
        if event.mcStatus[photonIdx] != 1: continue
        statFlag=event.mcStatusFlag[photonIdx]
        if event.mcStatusFlag[photonIdx] >>0&1 == 0: continue
        if event.mcStatusFlag[photonIdx] >>1&1 == 0: continue

        # has reco photon
        if event.nPho == 0: continue

        genPho=ROOT.TLorentzVector()
        genPho.SetPtEtaPhiE(event.mcPt[photonIdx],event.mcEta[photonIdx],event.mcPhi[photonIdx],event.mcPt[photonIdx])

        for recoPhoIdx in range(event.nPho):
            if not inFiducialRegion(event.phoEt[recoPhoIdx], event.phoEta[recoPhoIdx]): continue
            recoPho=ROOT.TLorentzVector()
            recoPho.SetPtEtaPhiE(event.phoEt[recoPhoIdx],event.phoEta[recoPhoIdx],event.phoPhi[recoPhoIdx],event.phoEt[recoPhoIdx])
            if recoPho.DeltaR(genPho) > 0.2: continue
            if (recoPho.Pt()-genPho.Pt())/genPho.Pt() > 0.35: continue

            # is matched reco photon

            if recoPhoIdx == 0: return False
            return True

    # if no gen photon found
    return False



def CloneTree( itree ):

    itree.SetBranchStatus("*",1);

    newtree=itree.CloneTree(0);

    for evt in itree:
        if not selected(evt): continue
        newtree.Fill()
    return newtree

if __name__ == '__main__':
    myfile=ROOT.TFile.Open('ggtree_mc_1.root')
    mytree=myfile.Get('ggNtuplizer/EventTree')

    ofile=ROOT
    ofile=ROOT.TFile('genPhoMatchedWithNonLeadingRecoPhoton.root', 'recreate')
    ofile.cd()
    otree=CloneTree(mytree)
    otree.Write()
    ofile.Close()


