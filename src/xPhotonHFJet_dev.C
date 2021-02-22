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



        mcMatchInfo::truthVal truthPhotons;
        // matchingRes truthmatchedObj;
        // truthmatchedObj.Clean();
        LOG_DEBUG("doing mcTruthMatching");
        if ( data.HasMC() )
            truthPhotons = mcMatchInfo::findtruthPhoton(&data);
        LOG_DEBUG("real mcTruthMatching");

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
        // */

        // int jet_index=-1;

        LOG_DEBUG("jet info section");
        std::vector<recoInfo::TLorentzDATA> selJets = recoInfo::selectedJets(&data);
        if ( !selJets.size() ) continue;
        recoInfo::TLorentzDATA leadingJet = selJets.at(0);


        LOG_DEBUG("leading photon section");

        std::vector<recoInfo::TLorentzDATA> selPhotons = recoInfo::selectedPhotons(&data);
        if ( !selPhotons.size() ) continue;
        recoInfo::TLorentzDATA leadingPhoton = selPhotons.at(0);


        LOG_DEBUG("photon candidate finding section ");

        //        LOG_DEBUG("preselect photon section");

        //        // preselect reco::photon section {{{
        //        for (Int_t i=0; i<nPho; ++i)
        //        {
        //            LOG_DEBUG("for PHSel 01");
        //            if(phoEt[i]<15.) continue;       
        //            LOG_DEBUG("for PHSel 02");
        //            //if(phoEt[i]<100.) continue;
        //            if(TMath::Abs(phoSCEta[i])>1.4442 && TMath::Abs(phoSCEta[i])<1.566) continue;
        //            LOG_DEBUG("for PHSel 03");
        //            if(TMath::Abs(phoSCEta[i])>2.5) continue;
        //            LOG_DEBUG("for PHSel 04");
        //            if(isData==1 && JETPD_PHOTONHLT==0 && phoFiredTrgs==0) continue;
        //            LOG_DEBUG("for PHSel 05");
        //            if(isData==1 && JETPD_PHOTONHLT==0 && doWmn==0)
        //            {
        //            LOG_DEBUG("for PHSel 06.1");
        //                if(phoFiredTrgs[i]==0) continue;
        //            LOG_DEBUG("for PHSel 06.2");
        //                if(((phoFiredTrgs[i]>>8)&1)==1) nphofiredtrgs++; //HLT175
        //                //if(((phoFiredTrgs[i]>>6)&1)==1) nphofiredtrgs++; //HLT120
        //                else 
        //                    continue;       
        //            LOG_DEBUG("for PHSel 06.3");
        //            }
        //            LOG_DEBUG("for PHSel 07");
        //            phoP4.SetPtEtaPhiM(phoEt[i], phoEta[i], phoPhi[i], 0.);
        //            LOG_DEBUG("for PHSel 08");
        //            int pho_presel = 0;
        //            // if(doWmn==1) pho_presel = PhotonPreselection(data, i, kFALSE);
        //            // else pho_presel = PhotonPreselection(data, i, kTRUE);
        //            pho_presel = PhotonPreselection(data, i, kTRUE);
        //            //check CSEV eff vs pt
        //            LOG_DEBUG("for PHSel 09");
        //            if(isData==0) 
        //            {
        //            LOG_DEBUG("for PHSel 10-1");
        //                if(i==0 && truthmatchedObj.isMatched[i]==1)
        //                {
        //
        //            LOG_DEBUG("for PHSel 10");
        //                    if(TMath::Abs(phoSCEta[i])<1.5) hphoEB_pt_presel_den->Fill(phoEt[i]);
        //                    else hphoEE_pt_presel_den->Fill(phoEt[i]);	
        //            LOG_DEBUG("for PHSel 10.1");
        //                    if(pho_presel == 1)
        //                    {
        //            LOG_DEBUG("for PHSel 10.2");
        //                        if(TMath::Abs(phoSCEta[i])<1.5) 
        //                        {
        //                            if(phoPFChIso[i]<2.) hphoEB_pt_presel_num->Fill(phoEt[i]);
        //                        }else 
        //                        {
        //                            if(phoPFChIso[i]<1.5) hphoEE_pt_presel_num->Fill(phoEt[i]);
        //                        }
        //            LOG_DEBUG("for PHSel 10.3");
        //                    }
        //
        //            LOG_DEBUG("for PHSel 10.4");
        //                    if( PhotonPreselection(data, i, kFALSE) ==1)
        //                    {
        //            LOG_DEBUG("for PHSel 10.5");
        //                        if(TMath::Abs(phoSCEta[i])<1.5) hphoEB_pt_presel_nocsev->Fill(phoEt[i]);
        //                        else hphoEE_pt_presel_nocsev->Fill(phoEt[i]);
        //            LOG_DEBUG("for PHSel 10.6");
        //
        //                        if(pho_presel == 1)
        //                        {
        //                            if(TMath::Abs(phoSCEta[i])<1.5) 
        //                            {
        //                                hphoEB_pt_presel_csev->Fill(phoEt[i]);
        //                            }else 
        //                            {
        //                                hphoEE_pt_presel_csev->Fill(phoEt[i]);
        //                            }
        //                        }
        //            LOG_DEBUG("for PHSel 10.7");
        //
        //                    }
        //            LOG_DEBUG("for PHSel 10.8");
        //                }
        //            LOG_DEBUG("for PHSel 10.9");
        //            }
        //
        //            LOG_DEBUG("for PHSel 11");
        //            //get e-pho mass from Z
        //            if( PhotonPreselection(data, i, kFALSE) ==1)
        //            {
        //            LOG_DEBUG("for PHSel 12.1");
        //                for(unsigned int jj=0; jj<eleID.size(); jj++)
        //                {
        //            LOG_DEBUG("for PHSel 12.2");
        //                    TLorentzVector tmp_eP4;
        //                    tmp_eP4.SetPtEtaPhiM(elePt[eleID[jj]], eleEta[eleID[jj]], elePhi[eleID[jj]],  0.511*0.001);
        //            LOG_DEBUG("for PHSel 12.3");
        //                    if(phoP4.DeltaR(tmp_eP4) > 0.5) 
        //                    {
        //            LOG_DEBUG("for PHSel 12.4");
        //                        TLorentzVector tmp_phoele_P4;
        //                        tmp_phoele_P4 = phoP4;
        //                        tmp_phoele_P4 += tmp_eP4;
        //                        h_Zee_mass->Fill(tmp_phoele_P4.M());
        //                        if(tmp_phoele_P4.M()>70. && tmp_phoele_P4.M()<110.) 
        //                            h_phoPt_eta_Z_all->Fill(phoEt[i], TMath::Abs(phoSCEta[i]));
        //                        if(PhotonPreselection(data, i, kTRUE) ==1)
        //                        {
        //                            h_Zee_mass_csev->Fill(tmp_phoele_P4.M());	   
        //                            if(tmp_phoele_P4.M()>70. && tmp_phoele_P4.M()<110.) 
        //                                h_phoPt_eta_Z_csev->Fill(phoEt[i], TMath::Abs(phoSCEta[i]));
        //                        }
        //            LOG_DEBUG("for PHSel 12.5");
        //                    }
        //                }
        //            LOG_DEBUG("for PHSel 12.6");
        //            }	
        //
        //            LOG_DEBUG("for PHSel 13");
        //            if(pho_presel!=1) continue;
        //            LOG_DEBUG("for PHSel 14");
        //            if(JETPD_PHOTONHLT==1 && phoP4.DeltaR(trigger_jetP4)<0.7) continue;
        //            LOG_DEBUG("for PHSel 15");
        //            photon_list.push_back(i); 
        //            if(ONLY_LEADINGPHOTON==1 && photon_list.size()==1) break;
        //            LOG_DEBUG("for PHSel 16");
        //            //skim for TMVA training
        //            //int pho_skim_presel = PhotonSkimPreselection(data, i, kTRUE);
        //            //if(pho_skim_presel==1) photon_list.push_back(i);
        //            // 	break;
        //
        //        }   
        //        // preselect reco::photon section end }}}
        //        h_npho->Fill(photon_list.size());
        //        if(photon_list.size() < 1) continue;
        //        //if(photon_list.size() > 1) continue;
        //        //   printf(" ERROR more than one photon registered in event %d \n", event);
        //        //   continue;
        //
        //        LOG_DEBUG("converted photon or fake photon ?");
        //        // converted photon or fake photon ? section {{{
        //        phoP4.SetPtEtaPhiM(phoEt[photon_list[0]], phoEta[photon_list[0]], phoPhi[photon_list[0]], 0.);
        //        for(unsigned int j=0; j<eleID.size(); j++)
        //        {
        //            if(elePt[eleID[j]]<100) continue;
        //            TLorentzVector tmp_eP4;
        //            tmp_eP4.SetPtEtaPhiM(elePt[eleID[j]], eleEta[eleID[j]], elePhi[eleID[j]],  0.511*0.001);
        //            h_dR_phoele->Fill(phoP4.DeltaR(tmp_eP4));
        //            if(phoP4.DeltaR(tmp_eP4) < 0.3) 
        //            {
        //                // printf("photon_list reset, pt %.2f, eta %.2f, electron pt %.2f  \n", 
        //                //        phoEt[photon_list[0]], phoEta[photon_list[0]], elePt[eleID[j]]);
        //                photon_list.clear(); 
        //            }
        //        }
        //        // converted photon or fake photon ? section end }}}
        //
        //        LOG_DEBUG("sig jet finding");
        //        // find signal jet differ from sig photon section {{{
        //        //find one jet in event
        //        for(int j=0; j<nJet; j++)
        //        {		         
        //            float jetjecunc = 1.;
        //            //float jetjecunc = 1.-jetJECUnc[j]; //1.;
        //            if(TMath::Abs(jetEta[j])<2.4 && jetPt[j]*jetjecunc>30.) 
        //            {
        //                //if( jetPFLooseId[j] ) h_jetID->Fill(1.);	else h_jetID->Fill(0.);
        //                if( jetId[j] ) h_jetIDv->Fill(1.);	else h_jetIDv->Fill(0.);       
        //                jetP4.SetPtEtaPhiE(jetPt[j]*jetjecunc, jetEta[j], jetPhi[j], jetEn[j]);
        //
        //                if(phoP4.DeltaR(jetP4)<0.2 && photon_jetID.size()<1)
        //                {
        //                    float dphojetpt = jetPt[j] / phoP4.Pt();
        //                    h_dpt_phojet->Fill(dphojetpt);
        //                    if( dphojetpt>0.5 || dphojetpt<2.) 
        //                    {
        //                        if(jetId[j] &&jetNHF[j]<0.9 && jetNEF[j]<0.9 ) photon_jetID.push_back(1.);
        //                        else photon_jetID.push_back(0.);
        //                    }
        //                }
        //
        //                if( jetId[j] ) {	  
        //                    h_dR_phojet->Fill(phoP4.DeltaR(jetP4));
        //                    if(phoP4.DeltaR(jetP4)>0.4)
        //                    {
        //                        if(jet_index<0) jet_index = j;
        //                        nnjet++;
        //                        if(nnjet==2) jet2_index = j;
        //                    }	    
        //                }    
        //            }  
        //        }
        //        // find signal jet differ from sig photon section end }}}
        //
        //        LOG_DEBUG("highPT photon checking");
        //        // highPT photon checking section {{{
        //        if(phoEt[photon_list[0]] > 150.) 
        //        {
        //            h_njet->Fill(nnjet, xsweight);
        //            if(nnjet>1)
        //            {
        //                int jet1_eta=0; if(jetEta[jet_index]>1.5) jet1_eta=1;
        //                int jet2_eta=0; if(jetEta[jet2_index]>1.5) jet2_eta=1;	
        //                h_detadpt_jet12->Fill((jet2_eta-jet1_eta), jetPt[jet2_index]/jetPt[jet_index], xsweight);
        //            }
        //        }
        //        // highPT photon checking section end }}}
        //
        //        //swapping jets for systematics SinglePho_miniAOD_Silver_JET12_JETUNC.root
        //        //   float jet1_et = jetPt[jet_index] * (1-jetJECUnc[jet_index]);
        //        //   float jet2_et = jetPt[jet2_index] * (1+jetJECUnc[jet2_index]);
        //        //   if(jet2_et > jet1_et) jet_index = jet2_index;
        //
        //
        //        if(photon_jetID.size()==0) photon_jetID.push_back(0);
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
        //        h_nphoFiredTrgs->Fill(nphofiredtrgs);
        //        h_npj->Fill(npj);
        //        h_npp->Fill(npp);
        //
        LOG_DEBUG("fill output tree content from data section");
        otree.run=data.GetInt("run");
        otree.event=data.GetLong64("event");
        otree.isData=data.GetBool("isData");
        otree.nVtx=data.GetInt("nVtx");
        //otree.nPho=data.GetInt("nPho");
        //otree.nJet=data.GetInt("nJet");
        //Int_tnPho=data.GetInt("nPho");
        //Int_tnJet=data.GetInt("nJet");

        if(!data.HasMC())
        {
            otree.HLT=data.GetLong64("HLTPho");
            otree.HLTIsPrescaled=data.GetLong64("HLTPhoIsPrescaled");
            otree.metFilters=data.GetInt("metFilters");
        }

        if(data.HasMC())
        {
            otree.pthat=data.GetFloat("pthat");
            otree.nMC=data.GetInt("nMC");
            //otree.mcPID=data.GetPtrInt("mcPID")[0];
            //otree.mcMomPID=data.GetPtrInt("mcMomPID")[0];
            //otree.mcGMomPID=data.GetPtrInt("mcGMomPID")[0];
            otree.mcPt=data.GetPtrFloat("mcPt")[0];
            otree.mcEta=data.GetPtrFloat("mcEta")[0];
            otree.mcPhi=data.GetPtrFloat("mcPhi")[0];
            //otree.mcE=data.GetPtrFloat("mcE")[0];
            //otree.mcMomPt=data.GetPtrFloat("mcMomPt")[0];
            //otree.mcMomEta=data.GetPtrFloat("mcMomEta")[0];
            //otree.mcMomPhi=data.GetPtrFloat("mcMomPhi")[0];
            //otree.mcStatus=data.GetPtrShort("mcStatusFlag")[0];
            otree.genHT=data.GetFloat("genHT");
            otree.jetGenJetPt=data.GetPtrFloat("jetGenJetPt")[0];
            //otree.jetGenJetEn=data.GetPtrFloat("jetGenJetEn")[0];
            otree.jetGenJetEta=data.GetPtrFloat("jetGenJetEta")[0];
            otree.jetGenJetPhi=data.GetPtrFloat("jetGenJetPhi")[0];
        }

        /*temporarilydisabled
          {
          nPUInfo=data.GetInt("nPUInfo");
          puBX=data.GetPtrInt("puBX");
          puTrue=data.GetPtrFloat("puTrue");
          for(Int_ti=0;i<nPUInfo;++i){if(puBX[i]==0)nPU=puTrue[i];}
          }
          mcCalIsoDR04=data.GetPtrFloat("mcCalIsoDR04");
          mcTrkIsoDR04=data.GetPtrFloat("mcTrkIsoDR04");
          puwei_=(float)puCalc.GetWeight(run,puTrue[1]);//in-timePU
          */

        // / / / / asdf {
        // / / / / asdf genWeight=data.GetFloat("genWeight");
        // / / / / asdf if(genWeight>0.)xsweight=XS;
        // / / / / asdf elsexsweight=XS*-1.;
        // / / / / asdf if(gjet15to6000==1)xsweight=genWeight;
        // / / / / asdf }//notdataend

        //if(hasSubVtxInfo)
        {
            otree.jetSubVtxPt=data.GetPtrFloat("jetSubVtxPt")[0];
            otree.jetSubVtxMass=data.GetPtrFloat("jetSubVtxMass")[0];
            otree.jetSubVtx3DVal=data.GetPtrFloat("jetSubVtx3DVal")[0];
            otree.jetSubVtx3DErr=data.GetPtrFloat("jetSubVtx3DErr")[0];
            otree.jetSubVtxNtrks=data.GetPtrInt("jetSubVtxNtrks")[0];
        }
        {
            //Float_t MET=data.GetFloat("pfMET");MET=pfMET;
            //Float_t METPhi=data.GetFloat("pfMETPhi");METPhi=pfMETPhi;

            ////Int_tnJet=data.GetInt("nJet");
            //Float_t*jetPt=data.GetPtrFloat("jetPt");
            //Float_t*jetEn=data.GetPtrFloat("jetEn");
            //Float_t*jetEta=data.GetPtrFloat("jetEta");
            //Float_t*jetPhi=data.GetPtrFloat("jetPhi");
            //Long64_t*jetFiredTrgs=data.GetPtrLong64("jetFiredTrgs");
            //Float_t*jetJECUnc=data.GetPtrFloat("jetJECUnc");

            //Float_t*jetCSV2BJetTags=data.GetPtrFloat("jetCSV2BJetTags");
            //Float_t*jetDeepCSVTags_b=data.GetPtrFloat("jetDeepCSVTags_b");
            //Float_t*jetDeepCSVTags_bb=data.GetPtrFloat("jetDeepCSVTags_bb");
            //Float_t*jetDeepCSVTags_c=data.GetPtrFloat("jetDeepCSVTags_c");
            //Float_t*jetDeepCSVTags_udsg=data.GetPtrFloat("jetDeepCSVTags_udsg");

            otree.MET=data.GetFloat("pfMET");
            otree.METPhi=data.GetFloat("pfMETPhi");

            //Int_tnJet=data.GetInt("nJet");
            otree.jetPt=data.GetPtrFloat("jetPt")[0];
            otree.jetEta=data.GetPtrFloat("jetEta")[0];
            otree.jetPhi=data.GetPtrFloat("jetPhi")[0];
            otree.jetJECUnc=data.GetPtrFloat("jetJECUnc")[0];

            otree.jetCSV2BJetTags=data.GetPtrFloat("jetCSV2BJetTags")[0];
            otree.jetDeepCSVTags_b=data.GetPtrFloat("jetDeepCSVTags_b")[0];
            otree.jetDeepCSVTags_bb=data.GetPtrFloat("jetDeepCSVTags_bb")[0];
            otree.jetDeepCSVTags_c=data.GetPtrFloat("jetDeepCSVTags_c")[0];
            otree.jetDeepCSVTags_udsg=data.GetPtrFloat("jetDeepCSVTags_udsg")[0];
        }

        if(data.HasMC())
        {//isMC
            otree.jetPartonID=data.GetPtrInt("jetPartonID")[0];
            otree.jetGenPartonID=data.GetPtrInt("jetGenPartonID")[0];
            otree.jetHadFlvr=data.GetPtrInt("jetHadFlvr")[0];
            //Int_t*jetPartonID=data.GetPtrInt("jetPartonID")[0];
            //Int_t*jetGenPartonID=data.GetPtrInt("jetGenPartonID")[0];
            //Int_t*jetHadFlvr=data.GetPtrInt("jetHadFlvr")[0];
        }

        {
            otree.recoEta=data.GetPtrFloat("phoEta")[0];
            otree.recoPhi=data.GetPtrFloat("phoPhi")[0];
            otree.recoPt=data.GetPtrFloat("phoEt")[0];
            otree.r9=data.GetPtrFloat("phoR9")[0];
            otree.recoSCEta=data.GetPtrFloat("phoSCEta")[0];
            //Float_t*phoEta=data.GetPtrFloat("phoEta");
            //Float_t*phoPhi=data.GetPtrFloat("phoPhi");
            //Float_t*phoEt=data.GetPtrFloat("phoEt");
            //Float_t*phoR9=data.GetPtrFloat("phoR9");
            //Float_t*phoSCEta=data.GetPtrFloat("phoSCEta");
        }

        ////Int_t*phoEleVeto=data.GetPtrInt("phoEleVeto");
        {
            otree.eleVeto=data.GetPtrInt("phoEleVeto")[0];
            otree.HoverE=data.GetPtrFloat("phoHoverE")[0];
            otree.chIsoRaw=data.GetPtrFloat("phoPFChIso")[0];
            otree.nhIsoRaw=data.GetPtrFloat("phoPFNeuIso")[0];
            otree.phoIsoRaw=data.GetPtrFloat("phoPFPhoIso")[0];
            otree.phohasPixelSeed=data.GetPtrInt("phohasPixelSeed")[0];
            //Float_t*recoHoverE=data.GetPtrFloat("phoHoverE");
            //Float_t*recoPFChIso=data.GetPtrFloat("phoPFChIso");
            //Float_t*recoPFNeuIso=data.GetPtrFloat("phoPFNeuIso");
            //Float_t*recoPFPhoIso=data.GetPtrFloat("phoPFPhoIso");
            //Int_t*recohasPixelSeed=data.GetPtrInt("phohasPixelSeed");
        }

        otree.rho=data.GetFloat("rho");

        {
            otree.rawE=data.GetPtrFloat("phoSCRawE")[0];
            otree.scEtaWidth=data.GetPtrFloat("phoSCEtaWidth")[0];
            otree.scPhiWidth=data.GetPtrFloat("phoSCPhiWidth")[0];
            otree.esEn=data.GetPtrFloat("phoESEnP1")[0] + data.GetPtrFloat("phoESEnP2")[0];
            otree.esRR=data.GetPtrFloat("phoESEffSigmaRR")[0];
            otree.chWorstIsoRaw=data.GetPtrFloat("phoPFChWorstIso")[0];

            otree.sieieFull5x5=data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[0];
            otree.sieipFull5x5=data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5")[0];
            otree.sipipFull5x5=data.GetPtrFloat("phoSigmaIPhiIPhiFull5x5")[0];
            otree.r9Full5x5=data.GetPtrFloat("phoR9Full5x5")[0];
            otree.e2x2Full5x5=data.GetPtrFloat("phoE2x2Full5x5")[0];
            otree.e5x5Full5x5=data.GetPtrFloat("phoE5x5Full5x5")[0];
            otree.photonIDmva=data.GetPtrFloat("phoIDMVA")[0];

            otree.phoFiredTrgs=data.GetPtrLong64("phoFiredSingleTrgs")[0];
            otree.phoIDbit=data.GetPtrShort("phoIDbit")[0];
            //Float_t*SCRawE=data.GetPtrFloat("phoSCRawE");
            //Float_t*SCEtaWidth=data.GetPtrFloat("phoSCEtaWidth");
            //Float_t*SCPhiWidth=data.GetPtrFloat("phoSCPhiWidth");
            //Float_t*ESEnP1=data.GetPtrFloat("phoESEnP1");
            //Float_t*ESEnP2=data.GetPtrFloat("phoESEnP2");
            //Float_t*ESEffSigmaRR=data.GetPtrFloat("phoESEffSigmaRR");
            //Float_t*PFChWorstIso=data.GetPtrFloat("phoPFChWorstIso");

            //Float_t*SigmaIEtaIEtaFull5x5=data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
            //Float_t*SigmaIEtaIPhiFull5x5=data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
            //Float_t*SigmaIPhiIPhiFull5x5=data.GetPtrFloat("phoSigmaIPhiIPhiFull5x5");
            //Float_t*R9Full5x5=data.GetPtrFloat("phoR9Full5x5");
            //Float_t*E2x2Full5x5=data.GetPtrFloat("phoE2x2Full5x5");
            //Float_t*E5x5Full5x5=data.GetPtrFloat("phoE5x5Full5x5");
            //Float_t*IDMVA=data.GetPtrFloat("phoIDMVA");

            //Long64_t*FiredTrgs=data.GetPtrLong64("phoFiredSingleTrgs");
            //Short_t*IDbit=data.GetPtrShort("phoIDbit");
        }

        if(!data.HasMC())//butSeedEnergyexistsinMC
        {
            otree.SeedEnergy=data.GetPtrFloat("phoSeedEnergy")[0];
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
        if ( !evtInfo->Bool(var::hasGoodVtx) ) return 1;
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

//matchingRes mcTruthMatching(readMgr* evtInfo)
//{
//    LOG_DEBUG("01 : get var");
//    matchingRes matchedObj;
//    Int_t*   mcPID     = evtInfo->PtrInt(var::mcPID);
//    Int_t*   mcMomPID  = evtInfo->PtrInt(var::mcMomPID);
//    //Int_t*   mcGMomPID = evtInfo->PtrInt(var::mcGMomPID);
//    Float_t* mcPt      = evtInfo->PtrFloat(var::mcPt);
//    Float_t* mcEta     = evtInfo->PtrFloat(var::mcEta);
//    Float_t* mcPhi     = evtInfo->PtrFloat(var::mcPhi);
//    Float_t* mcE       = evtInfo->PtrFloat(var::mcE);
//    Float_t* mcMomPt   = evtInfo->PtrFloat(var::mcMomPt);
//    Float_t* mcMomEta   = evtInfo->PtrFloat(var::mcMomEta);
//    Float_t* mcMomPhi   = evtInfo->PtrFloat(var::mcMomPhi);
//    Short_t* mcStatus = evtInfo->PtrShort(var::mcStatusFlag);
//    Float_t*   mcCalIsoDR04 = evtInfo->PtrFloat(var::mcCalIsoDR04);
//    Float_t*   mcTrkIsoDR04 = evtInfo->PtrFloat(var::mcTrkIsoDR04);
//
//    Float_t*  phoEt   = evtInfo->PtrFloat(var::phoEt);
//    Float_t*  phoEta  = evtInfo->PtrFloat(var::phoEta);
//    Float_t*  phoPhi  = evtInfo->PtrFloat(var::phoPhi);
//
//    LOG_DEBUG("02 : get gen photon");
//    vector<int> mcid;
//    for (Int_t k=0; k< evtInfo->Int(var::nMC); ++k)  // get gen photon directly from partons.
//    {
//        if (mcPID[k] == 22 &&  mcPt[k]>15. && (mcMomPID[k] <= 22 || mcMomPID[k] == 5100039)) 
//        {
//            if(verbose) printf("   true photon in generator pt %.2f, eta %.2f, phi %.2f \n", mcPt[k], mcEta[k], mcPhi[k]);
//            mcid.push_back(k);
//        }
//    }
//    LOG_DEBUG("03 : get gen muon");
//    vector<int> muonmcid;
//    for (Int_t k=0;k<evtInfo->Int(var::nMC); ++k)  // get gen muon ( but do nothing )
//    {
//        if (fabs(mcPID[k])==13 && mcPt[k]>20.)
//        { muonmcid.push_back(k); }
//    }
//
//    LOG_DEBUG("03 : get gen electron");
//    vector<int> elemcid;
//    for (Int_t k=0; k<evtInfo->Int(var::nMC); ++k)  // get gen electron ( used in converted photon )
//    {
//        if (fabs(mcPID[k]) == 11 )
//        { elemcid.push_back(k); }
//    }
//
//
//
//    int isMatched;
//    int isMatchedEle;
//    int isConverted;
//
//    LOG_DEBUG("04 : truth matching for reco::photon");
//    for (Int_t i=0; i<evtInfo->Int(var::nPho); ++i)  // truth matching for reco::photon
//    {
//        histMgr::FillStatus("matchingStatus", 0.);
//        int matchPho=0;
//        int matchEleFake=0;
//        int matchPhoConv=0;
//        if(phoEt[i]<15.) continue;
//        isMatched    = -1;
//        isMatchedEle = -1;
//        isConverted = -1;
//
//        float mcPt_ = 0.;
//        float mcEta_ = 0.;
//        float mcPhi_ = 0.;
//        float mcCalIso04_=0.;
//        float mcTrkIso04_=0.;
//        
//        //for (int jj=0; jj<nnMC; ++jj) 
//        for ( int k : mcid )
//        { // truth matching : genPho & recoPho
//            float dr = deltaR(phoEta[i], phoPhi[i], mcEta[k], mcPhi[k]);
//            float dpt = fabs((phoEt[i] - mcPt[k])/mcPt[k]);
//            histMgr::Fill("TOTdeltaR_recoPhoton_genPhoton", dr);
//            histMgr::Fill("TOTdPt_recoPhoton_genPhoton", dpt);
//
//
//            if (dr  > 0.2 ) continue;
//            if (dpt > 0.2 ) continue;
//
//            if( mcCalIsoDR04[k]>5.0 ) continue; //for gammajet photon pythia
//            isMatched = 1;
//            mcPt_  = mcPt[k];
//            mcEta_ = mcEta[k];
//            mcPhi_ = mcPhi[k];
//            mcCalIso04_ = mcCalIsoDR04[k];
//            mcTrkIso04_ = mcTrkIsoDR04[k];
//            histMgr::Fill("SIGPhodeltaR_recoPhoton_genPhoton", dr);
//            histMgr::Fill("SIGPhodPt_recoPhoton_genPhoton", dpt);
//            if(verbose) printf("  mc matched !!! \n");
//            //break;
//            ++matchPho;
//
//        }
//
//        //for (int jj=0; jj<nneleMC; ++jj)
//        for ( int k : elemcid )
//        { // truth matching : genEle & recoPho
//            if(fabs(mcPID[k]) == 11)
//            {
//                float dr = deltaR(phoEta[i], phoPhi[i], mcEta[k], mcPhi[k]);
//                histMgr::Fill("TOTdeltaR_recoPhoton_genElectron", dr);
//                histMgr::Fill("TOTdPt_recoPhoton_genElectron", fabs((phoEt[i] -mcPt[k])/mcPt[k]) );
//                if ( mcMomPID[k] == 22 ) histMgr::Fill("dPt_recoPhoton_genMomPhoton", fabs((phoEt[i] - mcMomPt[k])/mcMomPt[k]) );
//                if ( dr > 0.2 ) continue;
//
//                if (fabs((phoEt[i] -mcPt[k])/mcPt[k]) < 0.2) 
//                { // electron is recognized as a photon.
//                    isMatchedEle = 1;
//                    histMgr::Fill("WRONGRECOPhodeltaR_recoPhoton_genElectron", dr);
//                    histMgr::Fill("WRONGRECOPhodPt_recoPhoton_genElectron", fabs((phoEt[i] -mcPt[k])/mcPt[k]) );
//                    ++matchEleFake;
//                } // fake photon : reco::photon matches a gen::electron
//                if ( mcMomPID[k] == 22 && 
//                    fabs((phoEt[i] - mcMomPt[k])/mcMomPt[k]) < 0.2 &&
//                    ((mcCalIsoDR04[k]+mcTrkIsoDR04[k])<5.0 || doWmn==1)
//                    ) // converted photon : reco::photon matches a gen::electron in direction but pt matches with mother.
//                {
//                    isConverted = 1;
//                    mcPt_  = mcMomPt[k];
//                    mcEta_ = mcMomEta[k];
//                    mcPhi_ = mcMomPhi[k];	      
//                    mcCalIso04_ = mcCalIsoDR04[k];
//                    mcTrkIso04_ = mcTrkIsoDR04[k];
//                    histMgr::Fill("SIGConvPhodeltaR_recoPhoton_genElectron", dr);
//                    histMgr::Fill("SIGConvPhodPt_recoPhoton_genElectron", fabs((phoEt[i] -mcPt[k])/mcPt[k]) );
//                    ++matchPhoConv;
//                }
//            }
//        }
//
//        if ( isMatched || isMatchedEle || isConverted )
//        {
//            matchedObj.pt.push_back(mcPt_);
//            matchedObj.eta.push_back(mcEta_);
//            matchedObj.phi.push_back(mcPhi_);
//            matchedObj.calIso04.push_back(mcCalIso04_);
//            matchedObj.trkIso04.push_back(mcTrkIso04_);
//            matchedObj.isMatched.push_back(isMatched);
//            matchedObj.isMatchedEle.push_back(isMatchedEle);
//            matchedObj.isConverted.push_back(isConverted);
//
//            if ( isMatched+isMatchedEle+isConverted > 0 )
//                LOG_WARNING("truth matching more than 1 result : isMacthed %d, isMatchedEle %d, isConverted %d", isMatched, isMatchedEle, isConverted);
//            if ( matchPho )
//            {
//                histMgr::FillStatus("matchingStatus", 1);
//                if ( matchPho>1 ) histMgr::FillStatus("matchingStatus",-1);
//            }
//            if ( matchEleFake )
//            {
//                histMgr::FillStatus("matchingStatus", 2);
//                if ( matchEleFake>1 ) histMgr::FillStatus("matchingStatus",-2);
//            }
//            if ( matchPhoConv )
//            {
//                histMgr::FillStatus("matchingStatus", 3);
//                if ( matchPhoConv>1 ) histMgr::FillStatus("matchingStatus",-3);
//            }
//        }
//    }
//    LOG_DEBUG("05 : end of truth matching to reco::photon");
//
//    return matchedObj;
//}

// void BuildingCandidateFromThisPhoton(readMgr* evtInfo, int selPhoIdx)
// {
//     // NNN = each select first NNN photons
//         {            
//             phoFiredTrgs_ = phoFiredTrgs[selPhoIdx];
//             phoP4.SetPtEtaPhiM(phoEt[selPhoIdx], phoEta[selPhoIdx], phoPhi[selPhoIdx], 0.);
// 
//             if(jet_index>=0) 
//             {
//                 jetP4.SetPtEtaPhiE(jetPt[jet_index], jetEta[jet_index], jetPhi[jet_index], jetEn[jet_index]);
//                 //jetP4.SetPtEtaPhiM(jetPt[jet_index], jetEta[jet_index], jetPhi[jet_index],0.);
//                 jetPt_ = jetPt[jet_index];
//                 jetEta_ = jetEta[jet_index];
//                 jetPhi_ = jetPhi[jet_index];
//                 jetY_ = jetP4.Rapidity();
//                 jetJECUnc_ = jetJECUnc[jet_index];
//                 if(isData!=1) 
//                 {
//                     TLorentzVector jetGenJetP4;
//                     jetGenJetP4.SetPtEtaPhiE(jetGenJetPt[jet_index], jetGenJetEta[jet_index], jetGenJetPhi[jet_index], jetGenJetEn[jet_index]);   
//                     jetGenJetPt_ = jetGenJetPt[jet_index];
//                     jetGenJetEta_ = jetGenJetEta[jet_index];
//                     jetGenJetPhi_ = jetGenJetPhi[jet_index];
//                     jetGenJetY_ = jetGenJetP4.Rapidity();
//                     jetGenPartonID_ = jetGenPartonID[jet_index];		
//                     //if(jetGenJetPt_ < 0.) printf("event %d, jet Pt %.2f, jet eta %.2f, jet phi %.2f \n", event, jetPt_, jetEta_, jetPhi_);
//                 }else 
//                 {
//                     jetGenJetPt_ = 0.;
//                     jetGenJetEta_ = 0.;
//                     jetGenJetPhi_ = 0.;
//                     jetGenJetY_ = 0.;
//                     jetGenPartonID_ = 0;
//                 }
//             }else
//             {
//                 jetPt_=0.;
//                 jetEta_=0.;
//                 jetPhi_=0.;
//                 jetY_=0.;
//                 jetJECUnc_=0.;
//                 jetGenJetPt_ = 0.;
//                 jetGenJetEta_ = 0.;
//                 jetGenJetPhi_ = 0.;
//                 jetGenJetY_ = 0.;
//                 jetGenPartonID_ = 0;
//             }
//             if (hasSubVtxInfo)
//             {
//                 jetSubVtxPt_    = jetSubVtxPt   [jet_index];
//                 jetSubVtxMass_  = jetSubVtxMass [jet_index];
//                 jetSubVtx3DVal_ = jetSubVtx3DVal[jet_index];
//                 jetSubVtx3DErr_ = jetSubVtx3DErr[jet_index];
//                 jetSubVtxNtrks_ = jetSubVtxNtrks[jet_index];
//                 h_subVtxPt   ->Fill(jetSubVtxPt_   );
//                 h_subVtxMass ->Fill(jetSubVtxMass_ );
//                 h_subVtx3DVal->Fill(jetSubVtx3DVal_);
//                 h_subVtx3DErr->Fill(jetSubVtx3DErr_);
//                 h_subVtxNtrks->Fill(jetSubVtxNtrks_);
//             }
// 
//             jetCSV2BJetTags_ = jetCSV2BJetTags[jet_index];
//             jetDeepCSVTags_b_ = jetDeepCSVTags_b[jet_index];
//             jetDeepCSVTags_bb_ = jetDeepCSVTags_bb[jet_index];
//             jetDeepCSVTags_c_ = jetDeepCSVTags_c[jet_index];
//             jetDeepCSVTags_udsg_ = jetDeepCSVTags_udsg[jet_index];
//             // jetJetProbabilityBJetTags_ = jetJetProbabilityBJetTags[jet_index];
//             // jetpfCombinedMVAV2BJetTags_ = jetpfCombinedMVAV2BJetTags[jet_index];
// 
// 
//             jetPartonID_ = jetPartonID[jet_index];
//             jetHadFlvr_ = jetHadFlvr[jet_index];
// 
//             //for Z+jet events
//             if((doZmm==1 && nLep_m>=2) || (doZee==1 && nLep_e>=2)) 
//             {
//                 if(phoP4.DeltaR(lepP4[0]) < 0.3) continue;
//                 if(phoP4.DeltaR(lepP4[1]) < 0.3) continue;
//                 if(phoP4.DeltaR(electronP4)>0.3) continue;
//             }
// 
//             if(doWmn==1) 
//             {
//                 if(isData==1) hdR_pho_lep->Fill(phoP4.DeltaR(lepP4[0]),xsweight*genWeight);
//                 else if(truthmatchedObj.isMatched[selPhoIdx]==1) hdR_pho_lep->Fill(phoP4.DeltaR(lepP4[0]),xsweight*genWeight);
//                 else hdR_fake_lep->Fill(phoP4.DeltaR(lepP4[0]),xsweight*genWeight);
// 
//                 //trying other option
//                 //if(phoP4.DeltaR(lepP4[0]) > 0.3) continue; //normal for Wgamma Wjets
//                 //
//                 //if(phoP4.DeltaR(lepP4[0]) < 0.3) continue; //normal for Wgamma Wjets
//                 //if(TMath::Abs(phoSCEta[selPhoIdx]>1.556) && phoP4.DeltaR(lepP4[0]) < 0.3) continue; //normal for Wgamma Wjets
// 
//                 //if(phoP4.DeltaR(lepP4[0]) < 0.4) continue; // <<-- for e* 
//                 //if(phoP4.DeltaR(lepP4[0]) <1.0) continue; // <<-- for HZg
// 
//                 deta_wg = lepP4[0].Eta() - phoEta[selPhoIdx];
//                 dphi_wg = deltaPhi(lepP4[0].Phi(), phoPhi[selPhoIdx]);
//             }
// 
//             idLoose      = -1;
//             idMedium     = -1;
//             idTight      = -1;
// 
//             if(!isData)
//             {
//                 isMatched = truthmatchedObj.isMatched[selPhoIdx];
//                 isMatchedEle = truthmatchedObj.isMatchedEle[selPhoIdx];
//                 isConverted = truthmatchedObj.isConverted[selPhoIdx];
//                 pthat_    = pthat;
//                 mcPt_     = truthmatchedObj.pt[selPhoIdx];
//                 mcEta_    = truthmatchedObj.eta[selPhoIdx];
//                 mcPhi_    = truthmatchedObj.phi[selPhoIdx];
//                 mcCalIso04_ = truthmatchedObj.calIso04[selPhoIdx];
//                 mcTrkIso04_ = truthmatchedObj.trkIso04[selPhoIdx];
//                 genHT_ = genHT;
// 
//                 h2_mcPID_mcPt->Fill( jetGenJetPt_, jetGenPartonID_+0.01, xsweight);
//                 h2_mcPID_mcPt->Fill( mcPt_, 22.01, xsweight);
// 
//             }else
//             {
//                 isMatched = 1;
//                 isMatchedEle = 0;
//                 isConverted = 0;
//             }
// 
//             h2_mcPID_mcPt->Fill( jetPt_, 9.01, xsweight);
//             h2_mcPID_mcPt->Fill( phoEt[selPhoIdx], 10.09, xsweight);
// 
//             recoPt    = phoEt[selPhoIdx];
//             recoEta   = phoEta[selPhoIdx];
//             recoPhi   = phoPhi[selPhoIdx];
//             recoSCEta = phoSCEta[selPhoIdx];
//             r9        = phoR9[selPhoIdx];
//             eleVeto   = phoEleVeto[selPhoIdx];
//             HoverE    = phoHoverE[selPhoIdx];
//             //sieie     = phoSigmaIEtaIEta[selPhoIdx];
//             phohasPixelSeed_ = phohasPixelSeed[selPhoIdx];
//             chIsoRaw   = phoPFChIso[selPhoIdx];
//             phoIsoRaw  = phoPFPhoIso[selPhoIdx];
//             nhIsoRaw   = phoPFNeuIso[selPhoIdx];
// 
//             // sieip      = phoSigmaIEtaIPhi[selPhoIdx];
//             // sipip      = phoSigmaIPhiIPhi[selPhoIdx];
//             // e1x3       = phoE1x3[selPhoIdx];
//             // e2x2       = phoE2x2[selPhoIdx];
//             // e2x5       = phoE2x5Max[selPhoIdx];
//             // e5x5       = phoE5x5[selPhoIdx];
//             rawE       = phoSCRawE[selPhoIdx];
//             scEtaWidth = phoSCEtaWidth[selPhoIdx];
//             scPhiWidth = phoSCPhiWidth[selPhoIdx];
//             esRR       = phoESEffSigmaRR[selPhoIdx];
//             esEn       = phoESEnP1[selPhoIdx] +phoESEnP2[selPhoIdx];//      esEn       = phoESEn[selPhoIdx];
//             chWorstIso = phoPFChWorstIso[selPhoIdx];
// 
//             sieieFull5x5     = phoSigmaIEtaIEtaFull5x5[selPhoIdx];
//             sieipFull5x5     = phoSigmaIEtaIPhiFull5x5[selPhoIdx];
//             sipipFull5x5     = phoSigmaIPhiIPhiFull5x5[selPhoIdx];
//             r9Full5x5        = phoR9Full5x5[selPhoIdx];
//             // e1x3Full5x5       = phoE1x3Full5x5[selPhoIdx];
//             e2x2Full5x5       = phoE2x2Full5x5[selPhoIdx];
//             // e2x5Full5x5       = phoE2x5MaxFull5x5[selPhoIdx];
//             e5x5Full5x5       = phoE5x5Full5x5[selPhoIdx];
//             photon_jetID_ = photon_jetID[ii];
// 
//             if(isData==1)
//             {
//                 // 	SeedTime_ = phoSeedTime[selPhoIdx];
//                 SeedEnergy_ = phoSeedEnergy[selPhoIdx];
//                 // 	MIPTotEnergy_ = phoMIPTotEnergy[selPhoIdx];
//             }
//             phoIDbit_ = phoIDbit[selPhoIdx];
// 
//             HggPresel = 0.;
//             mva = -99.;
// 
//             // HggPresel= HggPreselection(data, selPhoIdx, kTRUE);
//             // if(TMath::Abs(phoSCEta[selPhoIdx])<1.5)  	mva = select_photon_mva(data, selPhoIdx, tgr);
//             // else mva = phoIDMVA[selPhoIdx];
//             mva = select_photon_mvanoIso(data, selPhoIdx, tgr);
// 
//             photonIDmva = phoIDMVA[selPhoIdx];
// 
//             mva_hgg=0.;
//             //mva_hgg = select_photon_mva_hgg(data, i);
// 
//             if(isMatched==1)
//             {
//                 if(TMath::Abs(phoEta[selPhoIdx])<1.5) h_EB_bdt->Fill(mva);
//                 else h_EE_bdt->Fill(mva);
//             }
// 
//             if(isData==1 && doWmn==0 && qstar==1 && photonIDmva>0.4 && eleVeto==1 && TMath::Abs(phoSCEta[selPhoIdx])<1.4442 )
//             {
//                 //loop jets for photon+jet invarient mass
//                 h_phoEt->Fill(phoEt[selPhoIdx]);	
//                 TLorentzVector pjP4;//= new TLorentzVector();	  
//                 //if(jetP4.Eta()>2.4) continue;
//                 //if(jetP4.DeltaR(phoP4)<0.5) continue;
//                 //if(TMath::Abs(jetP4.DeltaPhi(phoP4))<1.5) continue;
//                 // if( jetCHF[j] > 0. && jetNHF[j] < 0.9 && jetCEF[j] < 0.9 && jetNEF[j] < 0.9 &&
// 
//                 pjP4 = phoP4;
//                 pjP4 += jetP4;
// 
//                 h_jetPt->Fill(jetP4.Pt());
//                 h_pjmass->Fill(pjP4.M());
//                 //if(pjP4.M()>3000.) printf("run %d, event %d, phoEt %.1f, jetPt %.1f \n", run, event, phoEt[selPhoIdx], jetP4.Pt());
//                 npj++;
//             }
// 
//             if(MINITREE==1 ) 	
//             {
//                 outtree_->Fill();
//                 //if(isData==1 && doWmn==0) break;
//             }
// 
//         }
// }

