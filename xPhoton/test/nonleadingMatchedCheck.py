#!/usr/bin/env python2

import ROOT
def Photon_PromptFinalStat(event):
    return { idx:event.mcMomPID[idx] for idx,pStat in enumerate(event.mcStatusFlag) if event.mcPID[idx]==22 if pStat>>1&1 }
def Photon_FromHardProcess(event):
    return { idx:event.mcMomPID[idx] for idx,pStat in enumerate(event.mcStatusFlag) if event.mcPID[idx]==22 if pStat>>0&1 }

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
def isGenPhoton(event, photonIdx):
    if photonID != 22: return False
    if abs(event.mcMomPID[photonIdx]) > 10 and event.mcMomPID[photonIdx] != 21: return False
    if not inFiducialRegion(event.mcPt[photonIdx], event.mcEta[photonIdx]): return False

    # is final state
    if event.mcStatus[photonIdx] != 1: return False
    statFlag=event.mcStatusFlag[photonIdx]
    if event.mcStatusFlag[photonIdx] >>0&1 == 0: return False
    if event.mcStatusFlag[photonIdx] >>1&1 == 0: return False
    return True
def MatchLeadingPhoton(event):
    recoPho=ROOT.TLorentzVector()
    recoPho.SetPtEtaPhiE(event.phoEt[0],event.phoEta[0],event.phoPhi[0],event.phoEt[0])
    for mcIdx, mcStat in enumerate(event.mcStatus):
        if mcStat != 1: continue

        genPho=ROOT.TLorentzVector()
        genPho.SetPtEtaPhiE(event.mcPt[mcIdx],event.mcEta[mcIdx],event.mcPhi[mcIdx],event.mcPt[mcIdx])
        if recoPho.DeltaR(genPho) < 0.2 and (recoPho.Pt()-genPho.Pt())/genPho.Pt() < 0.35:
            return mcIdx
    return -999

if __name__ == '__main__':
    ifile=ROOT.TFile.Open('genPhoMatchedWithNonLeadingRecoPhoton.root')
    itree=ifile.Get('EventTree')


    leadingGenParticle={}
    GenPhotonDRdist=ROOT.TH1F('dR', 'delta R to leading photon in failed matched sample', 100, 0., 10.)
    GenPhotonDPdist=ROOT.TH1F('dP', 'deltaPt to leading photon in failed matched sample', 100, 0., 10.)
    GenPhotonDRMini=ROOT.TH1F('dr', 'delta R to leading photon in failed matched sample', 100, 0., 0.6)
    GenPhotonDPMini=ROOT.TH1F('dp', 'deltaPt to leading photon in failed matched sample', 100, 0., 0.6)
    GenPhoDPT      =ROOT.TH1F('dPT_genpho', 'delta Pt to leading photon in deltaR < 0.1', 100, 0., 10.)
    GenPhoDPTMini  =ROOT.TH1F('dpt_genpho', 'delta Pt to leading photon in deltaR < 0.1', 100, 0., 2. )
    numGenPho={}
    possiblePID={}
    possibleMPID={}
    possibleGPID={}
    for event in itree:
        if event.phoEt[0] < 10.: continue
        GenIdx=MatchLeadingPhoton(event)
        Add1(leadingGenParticle, event.mcPID[GenIdx] if GenIdx!=-999 else 'nothing')

        recoPho=ROOT.TLorentzVector()
        recoPho.SetPtEtaPhiE(event.phoEt[0],event.phoEta[0],event.phoPhi[0],event.phoEt[0])
        nGenPho=0
        for mcIdx, statFlag in enumerate(event.mcStatusFlag):
            #if event.mcPID[mcIdx] != 22: continue
            if event.mcPt[mcIdx] < 10.: continue
            if event.mcStatus[mcIdx] != 1 : continue
            #if statFlag>>0&1 == 0: continue

            genPho=ROOT.TLorentzVector()
            genPho.SetPtEtaPhiE(event.mcPt[mcIdx],event.mcEta[mcIdx],event.mcPhi[mcIdx],event.mcPt[mcIdx])
            momPho=ROOT.TLorentzVector()
            momPho.SetPtEtaPhiM(event.mcMomPt[mcIdx],event.mcMomEta[mcIdx],event.mcMomPhi[mcIdx],event.mcMomMass[mcIdx])
            nGenPho+=1

            GenPhotonDRdist.Fill( recoPho.DeltaR(genPho) )
            GenPhotonDPdist.Fill( (recoPho.Pt()-genPho.Pt())/genPho.Pt() )
            GenPhotonDRMini.Fill( recoPho.DeltaR(genPho) )
            GenPhotonDPMini.Fill( (recoPho.Pt()-genPho.Pt())/genPho.Pt() )
            if recoPho.DeltaR(genPho) < 0.1:
                Add1(possiblePID, event.mcPID[mcIdx])
                Add1(possibleMPID, event.mcMomPID[mcIdx])
                Add1(possibleGPID, event.mcGMomPID[mcIdx])
                if event.mcPID[mcIdx] == 22:
                    if event.mcMomPID[mcIdx] == 111:
                        GenPhoDPT.Fill( (recoPho.Pt()-momPho.Pt())/momPho.Pt() )
                        GenPhoDPTMini.Fill( (recoPho.Pt()-momPho.Pt())/momPho.Pt() )



        Add1(numGenPho,nGenPho)
    canv=ROOT.TCanvas('c1', '', 1200,1000)
    canv.SetLogy()
    GenPhotonDRMini.Draw()
    canv.SaveAs("dist_deltaR.mini.png")
    GenPhotonDPMini.Draw()
    canv.SaveAs("dist_deltaPt.mini.png")
    GenPhotonDRdist.Draw()
    canv.SaveAs("dist_deltaR.png")
    GenPhotonDPdist.Draw()
    canv.SaveAs("dist_deltaPt.png")
    GenPhoDPT.Draw()
    canv.SaveAs("dist_deltaPt.matchedDRpho.png")
    GenPhoDPTMini.Draw()
    canv.SaveAs("dist_deltaPt.matchedDRpho.mini.png")
    print 'matched gen particles of leading photon are %s' % repr(leadingGenParticle)
    print '%s gen photon in each event.' % repr(numGenPho)
    print 'Reco photons matched with %s' % repr(possiblePID)
    print 'Reco photons matched with mother:'
    for key in sorted(possibleMPID.keys()): print '%s : in number %d' % (key, possibleMPID[key])
    print 'Reco photons matched with grand mother:'
    for key in sorted(possibleGPID.keys()): print '%s : in number %d' % (key, possibleGPID[key])
