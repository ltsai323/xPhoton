#include "xPhoton/xPhoton/interface/readContent_gganalysis.h"
#include "xPhoton/xPhoton/interface/mcMatchInfo.h"
#include "TMath.h"
#include "xPhoton/xPhoton/interface/logger.h"
mcMatchInfo::mcMatchInfo(histMgr* ptr): importedHists(ptr)
{}

Double_t mcMatchInfo::deltaPhi(Double_t phi1, Double_t phi2) 
{
    Double_t dPhi = phi1 - phi2;
    if (dPhi > TMath::Pi()) dPhi -= 2.*TMath::Pi();
    if (dPhi < -TMath::Pi()) dPhi += 2.*TMath::Pi();
    return dPhi;
}

Double_t mcMatchInfo::deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2) 
{
    Double_t dEta, dPhi ;
    dEta = eta1 - eta2;
    dPhi = deltaPhi(phi1, phi2);
    return sqrt(dEta*dEta+dPhi*dPhi);
}

mcMatchInfo::truthVal mcMatchInfo::findtruthPhoton(readMgr* evtInfo)
{
    LOG_DEBUG("01 : get var");
    mcMatchInfo::truthVal matchedObj;
    Int_t*   mcPID     = evtInfo->PtrInt(var::mcPID);
    Int_t*   mcMomPID  = evtInfo->PtrInt(var::mcMomPID);
    //Int_t*   mcGMomPID = evtInfo->PtrInt(var::mcGMomPID);
    Float_t* mcPt      = evtInfo->PtrFloat(var::mcPt);
    Float_t* mcEta     = evtInfo->PtrFloat(var::mcEta);
    Float_t* mcPhi     = evtInfo->PtrFloat(var::mcPhi);
    // Float_t* mcE       = evtInfo->PtrFloat(var::mcE);
    Float_t* mcMomPt   = evtInfo->PtrFloat(var::mcMomPt);
    Float_t* mcMomEta   = evtInfo->PtrFloat(var::mcMomEta);
    Float_t* mcMomPhi   = evtInfo->PtrFloat(var::mcMomPhi);
    // Short_t* mcStatus = evtInfo->PtrShort(var::mcStatusFlag);
    Float_t*   mcCalIsoDR04 = evtInfo->PtrFloat(var::mcCalIsoDR04);
    Float_t*   mcTrkIsoDR04 = evtInfo->PtrFloat(var::mcTrkIsoDR04);

    Float_t*  phoEt   = evtInfo->PtrFloat(var::phoEt);
    Float_t*  phoEta  = evtInfo->PtrFloat(var::phoEta);
    Float_t*  phoPhi  = evtInfo->PtrFloat(var::phoPhi);

    LOG_DEBUG("02 : get gen photon");
    std::vector<int> mcid;
    for (Int_t k=0; k< evtInfo->Int(var::nMC); ++k)  // get gen photon directly from partons.
    {
        if (mcPID[k] == 22 &&  mcPt[k]>15. && (mcMomPID[k] <= 22 || mcMomPID[k] == 5100039)) 
        {
            mcid.push_back(k);
        }
    }
    LOG_DEBUG("03 : get gen muon");
    std::vector<int> muonmcid;
    for (Int_t k=0;k<evtInfo->Int(var::nMC); ++k)  // get gen muon ( but do nothing )
    {
        if (fabs(mcPID[k])==13 && mcPt[k]>20.)
        { muonmcid.push_back(k); }
    }

    LOG_DEBUG("03 : get gen electron");
    std::vector<int> elemcid;
    for (Int_t k=0; k<evtInfo->Int(var::nMC); ++k)  // get gen electron ( used in converted photon )
    {
        if (fabs(mcPID[k]) == 11 )
        { elemcid.push_back(k); }
    }



    int isMatched;
    int isMatchedEle;
    int isConverted;

    LOG_DEBUG("04 : truth matching for reco::photon");
    for (Int_t i=0; i<evtInfo->Int(var::nPho); ++i)  // truth matching for reco::photon
    {
        importedHists->FillStatus("matchingStatus", 0.);
        int matchPho=0;
        int matchEleFake=0;
        int matchPhoConv=0;
        if(phoEt[i]<15.) continue;
        isMatched    = -1;
        isMatchedEle = -1;
        isConverted = -1;

        float mcPt_ = 0.;
        float mcEta_ = 0.;
        float mcPhi_ = 0.;
        float mcCalIso04_=0.;
        float mcTrkIso04_=0.;
        
        //for (int jj=0; jj<nnMC; ++jj) 
        for ( int k : mcid )
        { // truth matching : genPho & recoPho
            float dr = deltaR(phoEta[i], phoPhi[i], mcEta[k], mcPhi[k]);
            float dpt = fabs((phoEt[i] - mcPt[k])/mcPt[k]);
            importedHists->Fill("TOTdeltaR_recoPhoton_genPhoton", dr);
            importedHists->Fill("TOTdPt_recoPhoton_genPhoton", dpt);


            if (dr  > 0.2 ) continue;
            if (dpt > 0.2 ) continue;

            if( mcCalIsoDR04[k]>5.0 ) continue; //for gammajet photon pythia
            isMatched = 1;
            mcPt_  = mcPt[k];
            mcEta_ = mcEta[k];
            mcPhi_ = mcPhi[k];
            mcCalIso04_ = mcCalIsoDR04[k];
            mcTrkIso04_ = mcTrkIsoDR04[k];
            importedHists->Fill("SIGPhodeltaR_recoPhoton_genPhoton", dr);
            importedHists->Fill("SIGPhodPt_recoPhoton_genPhoton", dpt);
            //break;
            ++matchPho;

        }

        //for (int jj=0; jj<nneleMC; ++jj)
        for ( int k : elemcid )
        { // truth matching : genEle & recoPho
            if(fabs(mcPID[k]) == 11)
            {
                float dr = deltaR(phoEta[i], phoPhi[i], mcEta[k], mcPhi[k]);
                importedHists->Fill("TOTdeltaR_recoPhoton_genElectron", dr);
                importedHists->Fill("TOTdPt_recoPhoton_genElectron", fabs((phoEt[i] -mcPt[k])/mcPt[k]) );
                if ( mcMomPID[k] == 22 ) importedHists->Fill("dPt_recoPhoton_genMomPhoton", fabs((phoEt[i] - mcMomPt[k])/mcMomPt[k]) );
                if ( dr > 0.2 ) continue;

                if (fabs((phoEt[i] -mcPt[k])/mcPt[k]) < 0.2) 
                { // electron is recognized as a photon.
                    isMatchedEle = 1;
                    importedHists->Fill("WRONGRECOPhodeltaR_recoPhoton_genElectron", dr);
                    importedHists->Fill("WRONGRECOPhodPt_recoPhoton_genElectron", fabs((phoEt[i] -mcPt[k])/mcPt[k]) );
                    ++matchEleFake;
                } // fake photon : reco::photon matches a gen::electron
                if ( mcMomPID[k] == 22 && 
                    fabs((phoEt[i] - mcMomPt[k])/mcMomPt[k]) < 0.2 &&
                    ((mcCalIsoDR04[k]+mcTrkIsoDR04[k])<5.0 )//  || doWmn==1)
                    ) // converted photon : reco::photon matches a gen::electron in direction but pt matches with mother.
                {
                    isConverted = 1;
                    mcPt_  = mcMomPt[k];
                    mcEta_ = mcMomEta[k];
                    mcPhi_ = mcMomPhi[k];	      
                    mcCalIso04_ = mcCalIsoDR04[k];
                    mcTrkIso04_ = mcTrkIsoDR04[k];
                    importedHists->Fill("SIGConvPhodeltaR_recoPhoton_genElectron", dr);
                    importedHists->Fill("SIGConvPhodPt_recoPhoton_genElectron", fabs((phoEt[i] -mcPt[k])/mcPt[k]) );
                    ++matchPhoConv;
                }
            }
        }

        if ( isMatched || isMatchedEle || isConverted )
        {
            matchedObj.pt.push_back(mcPt_);
            matchedObj.eta.push_back(mcEta_);
            matchedObj.phi.push_back(mcPhi_);
            matchedObj.calIso04.push_back(mcCalIso04_);
            matchedObj.trkIso04.push_back(mcTrkIso04_);
            matchedObj.isMatched.push_back(isMatched);
            matchedObj.isMatchedEle.push_back(isMatchedEle);
            matchedObj.isConverted.push_back(isConverted);

            if ( isMatched+isMatchedEle+isConverted > 0 )
                LOG_WARNING("truth matching more than 1 result : isMacthed %d, isMatchedEle %d, isConverted %d", isMatched, isMatchedEle, isConverted);
            if ( matchPho )
            {
                importedHists->FillStatus("matchingStatus", 1);
                if ( matchPho>1 ) importedHists->FillStatus("matchingStatus",-1);
            }
            if ( matchEleFake )
            {
                importedHists->FillStatus("matchingStatus", 2);
                if ( matchEleFake>1 ) importedHists->FillStatus("matchingStatus",-2);
            }
            if ( matchPhoConv )
            {
                importedHists->FillStatus("matchingStatus", 3);
                if ( matchPhoConv>1 ) importedHists->FillStatus("matchingStatus",-3);
            }
        }
    }
    LOG_DEBUG("05 : end of truth matching to reco::photon");

    return matchedObj;
}

