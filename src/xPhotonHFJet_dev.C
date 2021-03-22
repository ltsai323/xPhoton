#include <vector>
#include <TH1D.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TMath.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
using namespace std;
#include <iostream>
#include <TProfile.h>

#include "/home/ltsai/Work/github/xPhoton/interface/untuplizer.h"
#include "/home/ltsai/Work/github/xPhoton/interface/PhotonSelections.h"
#include "/home/ltsai/Work/github/xPhoton/interface/MuonSelections.h"
#include "/home/ltsai/Work/github/xPhoton/interface/ElectronSelections.h"
#include "/home/ltsai/Work/github/xPhoton/interface/puweicalc.h"
//#include "/home/ltsai/Work/github/xPhoton/interface/usefulFuncs.h"
#include "/home/ltsai/Work/github/xPhoton/src/usefulFuncs.cc"

#include "/home/ltsai/Work/github/xPhoton/interface/logger.h"
#include "/home/ltsai/Work/github/xPhoton/interface/histMgr.h"
#include "/home/ltsai/Work/github/xPhoton/interface/treeMgr.h"
#include "/home/ltsai/Work/github/xPhoton/interface/readMgr.h"
#include "/home/ltsai/Work/github/xPhoton/interface/mcMatchInfo.h"
#include "/home/ltsai/Work/github/xPhoton/interface/recoInfo.h"

// you can only load ONE readBrahBrah.h in the analysis.
#include "/home/ltsai/Work/github/xPhoton/interface/readContent_gganalysis.h"




Int_t MINITREE=1;
Double_t XS=1.;
Bool_t verbose=false;
// Int_t JETPD_PHOTONHLT=0;
Int_t ONLY_LEADINGPHOTON=1;
//flag for w/z tags
Int_t doZee=0;
Int_t doZmm=0;
Int_t doWen=0;
Int_t doWmn=0;
Int_t isMC=0;
Int_t data25ns=1;
Int_t data50ns=0;
Int_t qstar=1;
Int_t gjet15to6000=0;
Int_t genHTcut=0;
Int_t gjetSignal=0;

bool hasSubVtxInfo = true;


int failedpreselection_evt(readMgr* evtInfo);
// used in preselection
Double_t deltaPhi(Double_t phi1, Double_t phi2);
Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);





void xPhotonHFJet(vector<string> pathes, Char_t oname[200])
{
    //TreeReader data(pathes);
    readMgr data(pathes, branchesFromGGAnalysis);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");


    float ptcut[30] = {15, 20, 40, 60, 75, 90, 105,  120, 135, 150, 160, 170, 180,
        190, 200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000}; //22 bins
    //                  13   14   15   16   17   18   19   20   21    22    23    24    25     26
    float etabin[10] = {0., 0.8, 1.5, 2.1, 2.5};


    histMgr::Create("matchingStatus", 8,-3,4);
    histMgr::Create("TOTdeltaR_recoPhoton_genPhoton", 100, 0., 1.);
    histMgr::Create("TOTdPt_recoPhoton_genPhoton", 100, 0., 1.);

    histMgr::Create("TOTdeltaR_recoPhoton_genElectron", 100, 0., 1.);
    histMgr::Create("TOTdPt_recoPhoton_genElectron", 100, 0., 1.);

    histMgr::Create("TOTdPt_recoPhoton_genMomPhoton", 100, 0., 1.);

    histMgr::Create("SIGPhodeltaR_recoPhoton_genPhoton", 100, 0., 1.);
    histMgr::Create("SIGPhodPt_recoPhoton_genPhoton", 100, 0., 1.);

    histMgr::Create("SIGConvPhodeltaR_recoPhoton_genElectron", 100, 0., 1.);
    histMgr::Create("SIGConvPhodPt_recoPhoton_genElectron", 100, 0., 1.);

    histMgr::Create("WRONGRECOPhodeltaR_recoPhoton_genElectron", 100, 0., 1.);
    histMgr::Create("WRONGRECOPhodPt_recoPhoton_genElectron", 100, 0., 1.);

    histMgr::Create("dPt_recoPhoton_genMomPhoton", 100, 0., 1.);



    TDirectory* hdir = (TDirectory*) fout_->mkdir("hists");
    treeMgr otree;
    otree.BuildingTreeStructure("TTt", data.HasMC());



    LOG_INFO("total entries %lli", data.GetEntriesFast());
    // event loop
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) 
    {
        TLorentzVector phoP4, lepP4[2], zllP4, electronP4, wlnP4, nueP4, trigger_jetP4, jetP4;

        if (ev % 10000 == 0)
        { LOG_CRITICAL( "Processing event %lli of %lli  ( %.3f %% )", ev+1, data.GetEntriesFast(), (ev+1)*100./data.GetEntriesFast()); }

        data.GetEntry(ev);
        if ( data.Int(var::nJet) < 1 ) continue;
        if ( failedpreselection_evt(&data) ) continue;

        if ( data.Int(var::nPho) == 0 ) continue;




        LOG_DEBUG("doing mcTruthMatching");
        mcMatchInfo::truthVal truthPhotons;
        if ( data.HasMC() )
            truthPhotons = mcMatchInfo::findtruthPhoton(&data);

        LOG_DEBUG("temporally skiped section");
        /*
        // temporarily skip section {{{ // leptons section for specific channels
        // if(gjet15to6000==1 	&& ntruephoton!=1) continue;
        // if(gjet15to6000==1 	&& nmatch<1) continue;

        //look for 2nd photon back of HLT matched photon

        // ignored code end asdf!
        float* elePt  = data.GetPtrFloat("elePt");
        float* eleEta = data.GetPtrFloat("eleEta");
        float* elePhi = data.GetPtrFloat("elePhi");    

        //check if there is Z    
        Int_t nLep_e = 0;    
        Int_t nLep_m = 0;        
        vector<int> eleID;
        vector<int> muID;
        ElectronIDCutBased2015(data, 3, eleID); //0 veto, 1 loose, 2 medium, 3 tight 
        //h_nele->Fill(eleID.size());
        if(doZee==1)
        {
            //ElectronIDCutBased2015(data, 2, eleID);
            if (eleID.size() <2) continue;
            if (elePt[eleID[0]] >= 20) 
            {
                for (Int_t i=0; i< 2; ++i) { //save electron
                    lepP4[i].SetPtEtaPhiM(elePt[eleID[i]], eleEta[eleID[i]], elePhi[eleID[i]], 0.511*0.001);
                    nLep_e++;
                }
            }    
        } 
        if(doZmm==1)
        {
            TightMuons2015(data, muID);
            if (muID.size() < 2) continue;
            float* muPt  = data.GetPtrFloat("muPt");
            float* muEta = data.GetPtrFloat("muEta");
            float* muPhi = data.GetPtrFloat("muPhi");      
            if (muPt[muID[0]] >= 20 && muID.size() >=2) {    
                for (Int_t i=0; i< 2; ++i) 
                {
                    lepP4[i].SetPtEtaPhiM(muPt[muID[i]], muEta[muID[i]], muPhi[muID[i]], 105.658*0.001);
                    nLep_m++;
                }
            }
        }
        //check if there is W->l neu
        if(doWen==1)
        {
            //ElectronIDCutBased2015(data, 2, eleID);
            if (eleID.size() !=1) continue;
            if (elePt[eleID[0]] >= 20) 
            {
                lepP4[0].SetPtEtaPhiM(elePt[eleID[0]], eleEta[eleID[0]], elePhi[eleID[0]], 0.511*0.001);
                nLep_e++;
            }
        }    
        if(doWmn==1)
        {
            TightMuons2015(data, muID);
            if (muID.size() !=1 ) continue;
            float* muPt  = data.GetPtrFloat("muPt");
            float* muEta = data.GetPtrFloat("muEta");
            float* muPhi = data.GetPtrFloat("muPhi");      
            if (muPt[muID[0]] >= 30)
            {
                lepP4[0].SetPtEtaPhiM(muPt[muID[0]], muEta[muID[0]], muPhi[muID[0]], 105.658*0.001);
                nLep_m++;
            }
        }


        if(doZee==1 && nLep_e>=2) 
        {
            zllP4   = lepP4[0] + lepP4[1];
            //h_Zee_mass->Fill(zllP4.M());
            Mee=zllP4.M();
        }
        if(doZmm==1 && nLep_m>=2)
        {
            zllP4   = lepP4[0] + lepP4[1];
            //h_Zmm_mass->Fill(zllP4.M());      
            Mmm=zllP4.M();
        }
        float mt=0.;
        if(doWen==1 && nLep_e == 1)
        {
            nueP4.SetPtEtaPhiM(pfMET, 0., pfMETPhi, 0.);
            wlnP4 = lepP4[0] + nueP4;
            mt = TMath::Sqrt(2*lepP4[0].Pt()*pfMET*(1-TMath::Cos(lepP4[0].Phi()-pfMETPhi)));
            //if(pfMET >30) h_Wen_mt->Fill(mt);
            MTe = mt;
        }
        if(doWmn==1 && nLep_m == 1)
        {
            nueP4.SetPtEtaPhiM(pfMET, 0., pfMETPhi, 0.);
            wlnP4 = lepP4[0] + nueP4;
            mt = TMath::Sqrt(2*lepP4[0].Pt()*pfMET*(1-TMath::Cos(lepP4[0].Phi()-pfMETPhi)));
            //if(pfMET >30) h_Wmn_mt->Fill(mt,xsweight*genWeight);
            MTm = mt;
        }
        //continue; //for wmass only

        if( doWmn==1 && nLep_m!=1) continue;
        if( doWen==1 && nLep_e!=1) continue;
        if(( doZee==1 || doZmm==1) && (zllP4.M()<50 || zllP4.M()>110.)) continue;
        MET = pfMET;
        METPhi = pfMETPhi;
        //h_MET->Fill(MET);
        if((doZee==1 || doZmm==1) && MET>20.) continue;    
        if((doWen==1 || doWmn==1) && MET<30 ) continue;
        if((doWen==1 || doWmn==1) && (mt<40 || mt>110)) continue;

        int ecandidate=0;
        for(int iele=0; iele<nEle; iele++)
        {
            TLorentzVector tmp_eP4;
            tmp_eP4.SetPtEtaPhiM(elePt[iele], eleEta[iele], elePhi[iele],  0.511*0.001);
            if(doZee==1  && TMath::Abs(tmp_eP4.DeltaPhi(zllP4)) > 1.){ 
                electronP4 = tmp_eP4;
                ecandidate++;
                break;
            }
            else if(doWen==1 &&TMath::Abs(tmp_eP4.DeltaPhi(wlnP4)) > 1.5){ 
                electronP4 = tmp_eP4;
                ecandidate++;
                break;
            }
            else 
            {
                electronP4 = tmp_eP4;
                ecandidate++;
                break;
            }	      
        }
        // if((doZee==1 || doZmm==1 || doWen==1 || doWmn==1) && ecandidate==0) continue;
        if((doZee==1 || doZmm==1 ) && ecandidate==0) continue;
        // temporarily skip section end }}}
        */
        std::vector<int> eleID = recoInfo::electronsInEvt(&data);
        std::vector<int>  muID = recoInfo::    muonsInEvt(&data);
        std::vector<recoInfo::TLorentzDATA> electronpool = recoInfo::buildingCandidates_electron(&data, eleID);
        // std::vector<recoInfo::TLorentzDATA>     muons = recoInfo::buildingCandidates_muon    (&data, eleID);


        LOG_DEBUG("jet info section");
        std::vector<recoInfo::TLorentzDATA> selJets = recoInfo::selectedJets(&data);
        if ( !selJets.size() ) continue;



        LOG_DEBUG("leading photon section");
        std::vector<recoInfo::TLorentzDATA> selPhotons = recoInfo::selectedPhotons(&data);
        if ( !selPhotons.size() ) continue;
        recoInfo::TLorentzDATA leadingphoton = selPhotons[0];




        LOG_DEBUG("converted photon or fake photon ?");
        if ( isElectron(&data,leadingphoton, electronpool) ) continue;
        // define is photon coming from jet or not.
        bool photon_jetID = recoInfo::isjetPhoton(&data,leadingphoton, selJets);

        recoInfo::TLorentzDATA leadingjet = recoInfo::leadingJet(&data, leadingphoton, selJets);

        //        //if(isData==1 && doWmn==0 && nnjet==0) continue;
        //
        //        //main part of photon tree
        //        //HLT decisions V07 04 05 05
        //        //https://github.com/cmkuo/ggAnalysis/blob/master/ggNtuplizer/plugins/ggNtuplizer_trigger.cc    
        //        //   phoFilters["hltEG22HEFilter"]    = 0;
        //        //   phoFilters["hltEG30HEFilter"]    = 1;
        //        //   phoFilters["hltEG36HEFilter"]    = 2;
        //        //   phoFilters["hltEG50HEFilter"]    = 3;
        //        //   phoFilters["hltEG75HEFilter"]    = 4;
        //        //   phoFilters["hltEG90HEFilter"]    = 5;
        //        //   phoFilters["hltEG120HEFilter"]   = 6;
        //        //   phoFilters["hltEG165HE10Filter"] = 7;
        //        //   phoFilters["hltEG175HEFilter"]   = 8;
        //        //   phoFilters["hltEG250erEtFilter"] = 9;
        //        //   phoFilters["hltEG300erEtFilter"] = 10;
        //        //   phoFilters["hltEG500HEFilter"]   = 11;
        //        //   phoFilters["hltEG600HEFilter"]   = 12;
        //
        //        int photon_requested = 1; //only leading photon //photon_list.size();
        //        //int photon_jetID_size = photon_jetID.size();
        //
        //
        //        LOG_DEBUG("composite candidate building");
        //        // composite candidate building section {{{
        //        for (Int_t ii=0; ii<photon_requested; ii++)
        //        {            
        //            int ipho = photon_list[ii];
        //            phoFiredTrgs_ = phoFiredTrgs[ipho];
        //            phoP4.SetPtEtaPhiM(phoEt[ipho], phoEta[ipho], phoPhi[ipho], 0.);
        //
        //            if(jet_index>=0) 
        //            {
        //                jetP4.SetPtEtaPhiE(jetPt[jet_index], jetEta[jet_index], jetPhi[jet_index], jetEn[jet_index]);
        //                //jetP4.SetPtEtaPhiM(jetPt[jet_index], jetEta[jet_index], jetPhi[jet_index],0.);
        //                jetPt_ = jetPt[jet_index];
        //                jetEta_ = jetEta[jet_index];
        //                jetPhi_ = jetPhi[jet_index];
        //                jetY_ = jetP4.Rapidity();
        //                jetJECUnc_ = jetJECUnc[jet_index];
        //                if(isData!=1) 
        //                {
        //                    TLorentzVector jetGenJetP4;
        //                    jetGenJetP4.SetPtEtaPhiE(jetGenJetPt[jet_index], jetGenJetEta[jet_index], jetGenJetPhi[jet_index], jetGenJetEn[jet_index]);   
        //                    jetGenJetPt_ = jetGenJetPt[jet_index];
        //                    jetGenJetEta_ = jetGenJetEta[jet_index];
        //                    jetGenJetPhi_ = jetGenJetPhi[jet_index];
        //                    jetGenJetY_ = jetGenJetP4.Rapidity();
        //                    jetGenPartonID_ = jetGenPartonID[jet_index];		
        //                    //if(jetGenJetPt_ < 0.) printf("event %d, jet Pt %.2f, jet eta %.2f, jet phi %.2f \n", event, jetPt_, jetEta_, jetPhi_);
        //                }else 
        //                {
        //                    jetGenJetPt_ = 0.;
        //                    jetGenJetEta_ = 0.;
        //                    jetGenJetPhi_ = 0.;
        //                    jetGenJetY_ = 0.;
        //                    jetGenPartonID_ = 0;
        //                }
        //            }else
        //            {
        //                jetPt_=0.;
        //                jetEta_=0.;
        //                jetPhi_=0.;
        //                jetY_=0.;
        //                jetJECUnc_=0.;
        //                jetGenJetPt_ = 0.;
        //                jetGenJetEta_ = 0.;
        //                jetGenJetPhi_ = 0.;
        //                jetGenJetY_ = 0.;
        //                jetGenPartonID_ = 0;
        //            }
        //            if (hasSubVtxInfo)
        //
        //            {
        //                jetSubVtxPt_    = jetSubVtxPt   [jet_index];
        //                jetSubVtxMass_  = jetSubVtxMass [jet_index];
        //                jetSubVtx3DVal_ = jetSubVtx3DVal[jet_index];
        //                jetSubVtx3DErr_ = jetSubVtx3DErr[jet_index];
        //                jetSubVtxNtrks_ = jetSubVtxNtrks[jet_index];
        //                h_subVtxPt   ->Fill(jetSubVtxPt_   );
        //                h_subVtxMass ->Fill(jetSubVtxMass_ );
        //                h_subVtx3DVal->Fill(jetSubVtx3DVal_);
        //                h_subVtx3DErr->Fill(jetSubVtx3DErr_);
        //                h_subVtxNtrks->Fill(jetSubVtxNtrks_);
        //            }
        //
        //            jetCSV2BJetTags_ = jetCSV2BJetTags[jet_index];
        //            jetDeepCSVTags_b_ = jetDeepCSVTags_b[jet_index];
        //            jetDeepCSVTags_bb_ = jetDeepCSVTags_bb[jet_index];
        //            jetDeepCSVTags_c_ = jetDeepCSVTags_c[jet_index];
        //            jetDeepCSVTags_udsg_ = jetDeepCSVTags_udsg[jet_index];
        //            // jetJetProbabilityBJetTags_ = jetJetProbabilityBJetTags[jet_index];
        //            // jetpfCombinedMVAV2BJetTags_ = jetpfCombinedMVAV2BJetTags[jet_index];
        //
        //
        //            jetPartonID_ = jetPartonID[jet_index];
        //            jetHadFlvr_ = jetHadFlvr[jet_index];
        //
        //            //for Z+jet events
        //            if((doZmm==1 && nLep_m>=2) || (doZee==1 && nLep_e>=2)) 
        //            {
        //                if(phoP4.DeltaR(lepP4[0]) < 0.3) continue;
        //                if(phoP4.DeltaR(lepP4[1]) < 0.3) continue;
        //                if(phoP4.DeltaR(electronP4)>0.3) continue;
        //            }
        //
        //            if(doWmn==1) 
        //            {
        //                if(isData==1) hdR_pho_lep->Fill(phoP4.DeltaR(lepP4[0]),xsweight*genWeight);
        //                else if(truthmatchedObj.isMatched[ipho]==1) hdR_pho_lep->Fill(phoP4.DeltaR(lepP4[0]),xsweight*genWeight);
        //                else hdR_fake_lep->Fill(phoP4.DeltaR(lepP4[0]),xsweight*genWeight);
        //
        //                //trying other option
        //                //if(phoP4.DeltaR(lepP4[0]) > 0.3) continue; //normal for Wgamma Wjets
        //                //
        //                //if(phoP4.DeltaR(lepP4[0]) < 0.3) continue; //normal for Wgamma Wjets
        //                //if(TMath::Abs(phoSCEta[ipho]>1.556) && phoP4.DeltaR(lepP4[0]) < 0.3) continue; //normal for Wgamma Wjets
        //
        //                //if(phoP4.DeltaR(lepP4[0]) < 0.4) continue; // <<-- for e* 
        //                //if(phoP4.DeltaR(lepP4[0]) <1.0) continue; // <<-- for HZg
        //
        //                deta_wg = lepP4[0].Eta() - phoEta[ipho];
        //                dphi_wg = deltaPhi(lepP4[0].Phi(), phoPhi[ipho]);
        //            }
        //
        //            idLoose      = -1;
        //            idMedium     = -1;
        //            idTight      = -1;
        //
        //            if(!isData)
        //            {
        //                isMatched = truthmatchedObj.isMatched[ipho];
        //                isMatchedEle = truthmatchedObj.isMatchedEle[ipho];
        //                isConverted = truthmatchedObj.isConverted[ipho];
        //                pthat_    = pthat;
        //                mcPt_     = truthmatchedObj.pt[ipho];
        //                mcEta_    = truthmatchedObj.eta[ipho];
        //                mcPhi_    = truthmatchedObj.phi[ipho];
        //                mcCalIso04_ = truthmatchedObj.calIso04[ipho];
        //                mcTrkIso04_ = truthmatchedObj.trkIso04[ipho];
        //                genHT_ = genHT;
        //
        //                h2_mcPID_mcPt->Fill( jetGenJetPt_, jetGenPartonID_+0.01, xsweight);
        //                h2_mcPID_mcPt->Fill( mcPt_, 22.01, xsweight);
        //
        //            }else
        //            {
        //                isMatched = 1;
        //                isMatchedEle = 0;
        //                isConverted = 0;
        //            }
        //
        //            h2_mcPID_mcPt->Fill( jetPt_, 9.01, xsweight);
        //            h2_mcPID_mcPt->Fill( phoEt[ipho], 10.09, xsweight);
        //
        //            recoPt    = phoEt[ipho];
        //            recoEta   = phoEta[ipho];
        //            recoPhi   = phoPhi[ipho];
        //            recoSCEta = phoSCEta[ipho];
        //            r9        = phoR9[ipho];
        //            eleVeto   = phoEleVeto[ipho];
        //            HoverE    = phoHoverE[ipho];
        //            //sieie     = phoSigmaIEtaIEta[ipho];
        //            phohasPixelSeed_ = phohasPixelSeed[ipho];
        //            chIsoRaw   = phoPFChIso[ipho];
        //            phoIsoRaw  = phoPFPhoIso[ipho];
        //            nhIsoRaw   = phoPFNeuIso[ipho];
        //
        //            // sieip      = phoSigmaIEtaIPhi[ipho];
        //            // sipip      = phoSigmaIPhiIPhi[ipho];
        //            // e1x3       = phoE1x3[ipho];
        //            // e2x2       = phoE2x2[ipho];
        //            // e2x5       = phoE2x5Max[ipho];
        //            // e5x5       = phoE5x5[ipho];
        //            rawE       = phoSCRawE[ipho];
        //            scEtaWidth = phoSCEtaWidth[ipho];
        //            scPhiWidth = phoSCPhiWidth[ipho];
        //            esRR       = phoESEffSigmaRR[ipho];
        //            esEn       = phoESEnP1[ipho] +phoESEnP2[ipho];//      esEn       = phoESEn[ipho];
        //            chWorstIso = phoPFChWorstIso[ipho];
        //
        //            sieieFull5x5     = phoSigmaIEtaIEtaFull5x5[ipho];
        //            sieipFull5x5     = phoSigmaIEtaIPhiFull5x5[ipho];
        //            sipipFull5x5     = phoSigmaIPhiIPhiFull5x5[ipho];
        //            r9Full5x5        = phoR9Full5x5[ipho];
        //            // e1x3Full5x5       = phoE1x3Full5x5[ipho];
        //            e2x2Full5x5       = phoE2x2Full5x5[ipho];
        //            // e2x5Full5x5       = phoE2x5MaxFull5x5[ipho];
        //            e5x5Full5x5       = phoE5x5Full5x5[ipho];
        //            photon_jetID_ = photon_jetID[ii];
        //
        //            if(isData==1)
        //            {
        //                // 	SeedTime_ = phoSeedTime[ipho];
        //                SeedEnergy_ = phoSeedEnergy[ipho];
        //                // 	MIPTotEnergy_ = phoMIPTotEnergy[ipho];
        //            }
        //            phoIDbit_ = phoIDbit[ipho];
        //
        //            HggPresel = 0.;
        //            mva = -99.;
        //
        //            // HggPresel= HggPreselection(data, ipho, kTRUE);
        //            // if(TMath::Abs(phoSCEta[ipho])<1.5)  	mva = select_photon_mva(data, ipho, tgr);
        //            // else mva = phoIDMVA[ipho];
        //            mva = select_photon_mvanoIso(data, ipho, tgr);
        //
        //            photonIDmva = phoIDMVA[ipho];
        //
        //            mva_hgg=0.;
        //            //mva_hgg = select_photon_mva_hgg(data, i);
        //
        //            if(isMatched==1)
        //            {
        //                if(TMath::Abs(phoEta[ipho])<1.5) h_EB_bdt->Fill(mva);
        //                else h_EE_bdt->Fill(mva);
        //            }
        //
        //            if(isData==1 && doWmn==0 && qstar==1 && photonIDmva>0.4 && eleVeto==1 && TMath::Abs(phoSCEta[ipho])<1.4442 )
        //            {
        //                //loop jets for photon+jet invarient mass
        //                h_phoEt->Fill(phoEt[ipho]);	
        //                TLorentzVector pjP4;//= new TLorentzVector();	  
        //                //if(jetP4.Eta()>2.4) continue;
        //                //if(jetP4.DeltaR(phoP4)<0.5) continue;
        //                //if(TMath::Abs(jetP4.DeltaPhi(phoP4))<1.5) continue;
        //                // if( jetCHF[j] > 0. && jetNHF[j] < 0.9 && jetCEF[j] < 0.9 && jetNEF[j] < 0.9 &&
        //
        //                pjP4 = phoP4;
        //                pjP4 += jetP4;
        //
        //                h_jetPt->Fill(jetP4.Pt());
        //                h_pjmass->Fill(pjP4.M());
        //                //if(pjP4.M()>3000.) printf("run %d, event %d, phoEt %.1f, jetPt %.1f \n", run, event, phoEt[ipho], jetP4.Pt());
        //                npj++;
        //            }
        //
        //            if(MINITREE==1 ) 	
        //            {
        //                outtree_->Fill();
        //                //if(isData==1 && doWmn==0) break;
        //            }
        //
        //        }
        //        // composite candidate building section end }}}
        //

        LOG_DEBUG("fill output tree content from data section");
        otree.run=data.Int(var::run);
        otree.event=data.Long64(var::event);
        otree.isData=data.Bool(var::isData);
        otree.nVtx=data.Int(var::nVtx);

        if(!data.HasMC())
        {
            otree.HLT=data.Long64(var::HLTPho);
            otree.HLTIsPrescaled=data.Long64(var::HLTPhoIsPrescaled);
            otree.metFilters=data.Int(var::metFilters);
        }

        if(data.HasMC())
        {
            otree.pthat=data.Float(var::pthat);
            otree.nMC=data.Int(var::nMC);
            //otree.mcPID=data.PtrInt(var::mcPID)[0];
            //otree.mcMomPID=data.PtrInt(var::mcMomPID)[0];
            //otree.mcGMomPID=data.PtrInt(var::mcGMomPID)[0];
            otree.mcPt=data.PtrFloat(var::mcPt)[0];
            otree.mcEta=data.PtrFloat(var::mcEta)[0];
            otree.mcPhi=data.PtrFloat(var::mcPhi)[0];
            //otree.mcE=data.PtrFloat(var::mcE)[0];
            //otree.mcMomPt=data.PtrFloat(var::mcMomPt)[0];
            //otree.mcMomEta=data.PtrFloat(var::mcMomEta)[0];
            //otree.mcMomPhi=data.PtrFloat(var::mcMomPhi)[0];
            //otree.mcStatus=data.PtrShort(var::mcStatusFlag)[0];
            otree.genHT=data.Float(var::genHT);
            otree.jetGenJetPt=data.PtrFloat(var::jetGenJetPt)[0];
            //otree.jetGenJetEn=data.PtrFloat(var::jetGenJetEn)[0];
            otree.jetGenJetEta=data.PtrFloat(var::jetGenJetEta)[0];
            otree.jetGenJetPhi=data.PtrFloat(var::jetGenJetPhi)[0];
        }

        /*temporarilydisabled
          {
          nPUInfo=data.Int(var::nPUInfo);
          puBX=data.PtrInt(var::puBX);
          puTrue=data.PtrFloat(var::puTrue);
          for(Int_ti=0;i<nPUInfo;++i){if(puBX[i]==0)nPU=puTrue[i];}
          }
          mcCalIsoDR04=data.PtrFloat(var::mcCalIsoDR04);
          mcTrkIsoDR04=data.PtrFloat(var::mcTrkIsoDR04);
          puwei_=(float)puCalc.GetWeight(run,puTrue[1]);//in-timePU
          */

        // / / / / asdf {
        // / / / / asdf genWeight=data.Float(var::genWeight);
        // / / / / asdf if(genWeight>0.)xsweight=XS;
        // / / / / asdf elsexsweight=XS*-1.;
        // / / / / asdf if(gjet15to6000==1)xsweight=genWeight;
        // / / / / asdf }//notdataend

        //if(hasSubVtxInfo)
        {
            otree.jetSubVtxPt=data.PtrFloat(var::jetSubVtxPt)[0];
            otree.jetSubVtxMass=data.PtrFloat(var::jetSubVtxMass)[0];
            otree.jetSubVtx3DVal=data.PtrFloat(var::jetSubVtx3DVal)[0];
            otree.jetSubVtx3DErr=data.PtrFloat(var::jetSubVtx3DErr)[0];
            otree.jetSubVtxNtrks=data.PtrInt(var::jetSubVtxNtrks)[0];
        }
        {
            otree.MET=data.Float(var::pfMET);
            otree.METPhi=data.Float(var::pfMETPhi);

            otree.jetPt=data.PtrFloat(var::jetPt)[0];
            otree.jetEta=data.PtrFloat(var::jetEta)[0];
            otree.jetPhi=data.PtrFloat(var::jetPhi)[0];
            otree.jetJECUnc=data.PtrFloat(var::jetJECUnc)[0];

            otree.jetCSV2BJetTags=data.PtrFloat(var::jetCSV2BJetTags)[0];
            otree.jetDeepCSVTags_b=data.PtrFloat(var::jetDeepCSVTags_b)[0];
            otree.jetDeepCSVTags_bb=data.PtrFloat(var::jetDeepCSVTags_bb)[0];
            otree.jetDeepCSVTags_c=data.PtrFloat(var::jetDeepCSVTags_c)[0];
            otree.jetDeepCSVTags_udsg=data.PtrFloat(var::jetDeepCSVTags_udsg)[0];
        }

        if(data.HasMC())
        {
            otree.jetPartonID=data.PtrInt(var::jetPartonID)[0];
            otree.jetGenPartonID=data.PtrInt(var::jetGenPartonID)[0];
            otree.jetHadFlvr=data.PtrInt(var::jetHadFlvr)[0];
        }

        {
            otree.recoEta=data.PtrFloat(var::phoEta)[0];
            otree.recoPhi=data.PtrFloat(var::phoPhi)[0];
            otree.recoPt=data.PtrFloat(var::phoEt)[0];
            otree.r9=data.PtrFloat(var::phoR9)[0];
            otree.recoSCEta=data.PtrFloat(var::phoSCEta)[0];
        }

        {
            otree.eleVeto=data.PtrInt(var::phoEleVeto)[0];
            otree.HoverE=data.PtrFloat(var::phoHoverE)[0];
            otree.chIsoRaw=data.PtrFloat(var::phoPFChIso)[0];
            otree.nhIsoRaw=data.PtrFloat(var::phoPFNeuIso)[0];
            otree.phoIsoRaw=data.PtrFloat(var::phoPFPhoIso)[0];
            otree.phohasPixelSeed=data.PtrInt(var::phohasPixelSeed)[0];
        }

        otree.rho=data.Float(var::rho);

        {
            otree.rawE=data.PtrFloat(var::phoSCRawE)[0];
            otree.scEtaWidth=data.PtrFloat(var::phoSCEtaWidth)[0];
            otree.scPhiWidth=data.PtrFloat(var::phoSCPhiWidth)[0];
            otree.esEn=data.PtrFloat(var::phoESEnP1)[0] + data.PtrFloat(var::phoESEnP2)[0];
            otree.esRR=data.PtrFloat(var::phoESEffSigmaRR)[0];
            otree.chWorstIsoRaw=data.PtrFloat(var::phoPFChWorstIso)[0];

            otree.sieieFull5x5=data.PtrFloat(var::phoSigmaIEtaIEtaFull5x5)[0];
            otree.sieipFull5x5=data.PtrFloat(var::phoSigmaIEtaIPhiFull5x5)[0];
            otree.sipipFull5x5=data.PtrFloat(var::phoSigmaIPhiIPhiFull5x5)[0];
            otree.r9Full5x5=data.PtrFloat(var::phoR9Full5x5)[0];
            otree.e2x2Full5x5=data.PtrFloat(var::phoE2x2Full5x5)[0];
            otree.e5x5Full5x5=data.PtrFloat(var::phoE5x5Full5x5)[0];
            otree.photonIDmva=data.PtrFloat(var::phoIDMVA)[0];

            otree.phoFiredTrgs=data.PtrLong64(var::phoFiredSingleTrgs)[0];
            otree.phoIDbit=data.PtrShort(var::phoIDbit)[0];
        }

        if(!data.HasMC())//butSeedEnergyexistsinMC
        {
            otree.SeedEnergy=data.PtrFloat(var::phoSeedEnergy)[0];
        }


        LOG_DEBUG("filling event");
        otree.FillEvt();
    } // event end

    histMgr::WriteTo(hdir);
    otree.WriteTo(fout_);


    // histMgr::ClearAll();
    fout_->Close();

    fprintf(stderr, "Processed all events\n");

}


void xPhotonHFJet(Int_t dataset = 0) 
{
    Char_t fname[200];
    XS=1.;
    vector <string> pathes;


    sprintf(fname, "/home/ltsai/ggtree_mc_%d.root", dataset); 
    pathes.push_back(fname);
    XS = 1.;
    isMC=1;
    gjetSignal=1;
    gjet15to6000=1;

    Char_t oname[200];
    //sprintf(oname, "skim.root");
    sprintf(oname, "output_job_PhotonHFJet_%d.root", dataset);

    xPhotonHFJet(pathes, oname);

}

void xPhotonHFJet(Char_t fname[200], Char_t oname[200], Double_t crosssection=1., int dowmnoption=0)
{
    doWmn = dowmnoption;
    isMC=1;
    vector <string> pathes;
    //sprintf(oname, "output_job_%d.root", dataset);
    pathes.push_back(fname);
    //xPhotonHFJet(fname, oname, XS);
    XS = crosssection;
    xPhotonHFJet(pathes, oname);

}

void xPhotonHFJet(std::string ipath, int outID)
    //void xPhotonHFJet(Char_t ipath[300], int outID)

{
    Char_t fname[200];
    XS=1.;
    vector <string> pathes;

    pathes.push_back(ipath);
    XS = 1.;
    isMC=1;
    gjetSignal=1;
    gjet15to6000=1;
    //return;

    Char_t oname[200];
    //sprintf(oname, "output_job_PhotonHFJet_%d.root", dataset);
    sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

    xPhotonHFJet(pathes, oname);

}

int failedpreselection_evt(readMgr* evtInfo)
{
    Bool_t isdata = evtInfo->Bool(var::isData);

    if ( isdata )
    {
        // if ( !evtInfo->Bool(var::hasGoodVtx) ) return 1;
        if ( !evtInfo->Int(var::nGoodVtx) ) return 1;
        if (  evtInfo->Int(var::metFilters)  ) return 2;
    }
    if ( isdata && doWmn )
        if ( ((evtInfo->Long64(var::HLTEleMuX)>>31)&1) != 1 ) return 3;
    if ( !evtInfo->Int(var::nPho) ) return 4;
    return 0;

}
Double_t deltaPhi(Double_t phi1, Double_t phi2) 
{
    Double_t dPhi = phi1 - phi2;
    if (dPhi > TMath::Pi()) dPhi -= 2.*TMath::Pi();
    if (dPhi < -TMath::Pi()) dPhi += 2.*TMath::Pi();
    return dPhi;
}

Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2) 
{
    Double_t dEta, dPhi ;
    dEta = eta1 - eta2;
    dPhi = deltaPhi(phi1, phi2);
    return sqrt(dEta*dEta+dPhi*dPhi);
}

