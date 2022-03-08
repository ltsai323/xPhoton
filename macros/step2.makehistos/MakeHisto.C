#define MakeHisto_cxx
#include "MakeHisto.h"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>
#include <iostream>
#include <TLorentzVector.h>
#define NUMBIN_PHOETA 2
#define NUMBIN_JETETA 3
#define NUMBIT_HLT 9 // 0~8
#define NUMBIN_ISOVAR 4
#define NUMBIN_MATCHEDPHOTONSTATUS 5
#define NUMBIN_JETFLVR 3
#define NUM_BTAGVAR 4
#define NUM_PARITY 2

std::vector<float> ptbin_ranges()
{
    // for 2016
    //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
    std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
    return vec_ptcut;
}

void MakeHisto::Loop(Int_t extracut = 0)
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();
    //   In a ROOT session, you can do:
    //      Root > .L MakeHisto.C
    //      Root > MakeHisto t
    //      Root > t.GetEntry(12); // Fill t data members with entry number 12
    //      Root > t.Show();       // Show values of entry 12
    //      Root > t.Show(16);     // Read and show values of entry 16
    //      Root > t.Loop();       // Loop on all entries
    //

    //     This is the loop skeleton where:
    //    jentry is the global entry number in the chain
    //    ientry is the entry number in the current Tree
    //  Note that the argument to GetEntry must be:
    //    jentry for TChain::GetEntry
    //    ientry for TTree::GetEntry and TBranch::GetEntry
    //
    //       To read only selected branches, Insert statements like:
    // METHOD1:
    //    fChain->SetBranchStatus("*",0);  // disable all branches
    //    fChain->SetBranchStatus("branchname",1);  // activate branchname
    // METHOD2: replace line
    //    fChain->GetEntry(jentry);       //read all branches
    //by  b_branchname->GetEntry(ientry); //read only this branch
    if (fChain == 0) return;
    TRandom3 *trd = new TRandom3();

    TFile *fout = new TFile( Form("makehisto_%s.root", outputlabel_),"recreate");

    //ebee, jetbin, ptbin, true/fake;
    TH1F *h_BDT_all [NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2];
    TH1F *h_BDT     [NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2];
    TH1F *h_Pt_all  [NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2];
    TH1F *h_Pt      [NUMBIN_PHOETA]                             [2];
    TH1F *h_Ptspec  [NUMBIN_PHOETA]                             [2];
    TH2F *h_IsovsBDT[NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2][NUMBIN_ISOVAR];


    for(int pEtaIdx=0; pEtaIdx<NUMBIN_PHOETA; pEtaIdx++) {
    for(int jEtaIdx=0; jEtaIdx<NUMBIN_JETETA; jEtaIdx++) {
    for(int pPtIdx=0; pPtIdx<NUMBIN_PHOPT ; pPtIdx++) {
    for(int isFakePho=0; isFakePho<2; isFakePho++) {
        h_BDT_all[pEtaIdx][jEtaIdx][pPtIdx][isFakePho] = new TH1F(
            Form("h_BDT_all_%d_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho),
            Form("BDT all  EBEE_%d_Jet_%d_ptbin_%d_true_%d", pEtaIdx,jEtaIdx,pPtIdx,isFakePho),
            100,-1.,1.);
        h_BDT[pEtaIdx][jEtaIdx][pPtIdx][isFakePho] = new TH1F(
            Form("h_BDT_%d_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho),
            Form("BDT selected EBEE_%d_Jet_%d_ptbin_%d_true_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho),
            100,-1.,1.);

        for(int varIsoIdx=0; varIsoIdx<NUMBIN_ISOVAR; varIsoIdx++)
        {
            h_IsovsBDT[pEtaIdx][jEtaIdx][pPtIdx][isFakePho][varIsoIdx] = new TH2F(
                Form("h_IsovsBDT_%d_%d_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho,varIsoIdx),
                Form("Iso vs BDT EBEE_%d_Jet_%d_ptbin_%d_true_%d_Iso_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho,varIsoIdx),
                100, -1., 1., 30, 0., 15);
                h_IsovsBDT[pEtaIdx][jEtaIdx][pPtIdx][isFakePho][varIsoIdx]->Sumw2();
        }


        h_Pt_all[pEtaIdx][jEtaIdx][pPtIdx][isFakePho] = new TH1F(
            Form("h_Pt_all_%d_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho),
            Form("Pt all  EBEE_%d_Jet_%d_ptbin_%d_true_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho),
            2000, 0., 2000.);
    } } } }

    for(int pEtaIdx=0; pEtaIdx<NUMBIN_PHOETA; pEtaIdx++) {
    for(int isFakePho=0; isFakePho<2; isFakePho++) {
        h_Ptspec[pEtaIdx][isFakePho] = new TH1F(
            Form("h_Pt_spec_%d_%d",pEtaIdx,isFakePho),
            Form("Pt EBEE_%d_true_%d",pEtaIdx,isFakePho),
            200, 0., 2000.);
        h_Ptspec[pEtaIdx][isFakePho]->Sumw2();

        h_Pt[pEtaIdx][isFakePho] = new TH1F(
            Form("h_Pt_%d_%d",pEtaIdx,isFakePho),
            Form("Pt EBEE_%d_true_%d",pEtaIdx,isFakePho),
            200, 0., 2000.);
        h_Pt[pEtaIdx][isFakePho]->Sumw2();
    } }
    TH1F *h_EB_HLTall = new TH1F("h_EB_HLTall","all HLT photon", 1000, 0., 1000.);
    TH1F *h_EE_HLTall = new TH1F("h_EE_HLTall","all HLT photon", 1000, 0., 1000.);

    TH1F *h_chiso_sg = new TH1F("h_chiso_sg","chiso signal region", 150, 0., 30);
    TH1F *h_chworst_sg = new TH1F("h_chworst_sg","chworst signal region", 150, 0., 30);


    TH1F *h_HLT[NUMBIN_PHOETA][NUMBIT_HLT][2];
    for (int pEtaIdx=0; pEtaIdx<NUMBIN_PHOETA; pEtaIdx++) {
    for (int HLTIdx=0; HLTIdx<NUMBIT_HLT; HLTIdx++) {
        h_HLT[pEtaIdx][HLTIdx][0] = new TH1F(
                Form("h_HLT_ebee_%d_bit%d",pEtaIdx, HLTIdx),
                Form("HLT ebee %d bit %d all",pEtaIdx, HLTIdx),
                2000, 0., 2000.);
        h_HLT[pEtaIdx][HLTIdx][1] = new TH1F(
                Form("h_HLT_ebee_%d_bit%d_pass",pEtaIdx, HLTIdx),
                Form("HLT ebee %d bit %d pass",pEtaIdx, HLTIdx),
                2000, 0., 2000.);
    } }

    // EBEE ; recoPt ; isMatched ; jetflvr ; tagger
    // EBEE      : 0 for EB ; 1 for EE
    // recoPt    : 
    // isMatched : 0 for matched, 1 for not-matched, 2 for matched(qcd-sideband), 3 for matched(qcd-signal), 4 for not-matched(qcd) 
    // jetflv    : 0 for light ; 1 for c ; 2 for b
    // tagger    : 0 for bvsall ; 1 for cvsl ; 2 for cvsb ; 3 for svxmass
    // parity	 : 0 for even entries ; 1 for odd entries
    // yi-shou's variables
    TH1F *h_jettag     [NUMBIN_PHOETA][NUMBIN_PHOPT][NUMBIN_MATCHEDPHOTONSTATUS][NUMBIN_JETFLVR][NUM_BTAGVAR][NUM_PARITY];
    TH1F *h_jettag_up  [NUMBIN_PHOETA][NUMBIN_PHOPT][NUMBIN_MATCHEDPHOTONSTATUS][NUMBIN_JETFLVR][NUM_BTAGVAR][NUM_PARITY];
    TH1F *h_jettag_down[NUMBIN_PHOETA][NUMBIN_PHOPT][NUMBIN_MATCHEDPHOTONSTATUS][NUMBIN_JETFLVR][NUM_BTAGVAR][NUM_PARITY];
    const int varBTagIdx_svxmass=3;


    const std::vector< const char* > jetFlvrNames = { "sigma", "alpha", "beta" };
    for(int pEtaIdx=0; pEtaIdx<NUMBIN_PHOETA; pEtaIdx++) {
    for(int pPtIdx=0; pPtIdx<NUMBIN_PHOPT; pPtIdx++) {
    for(int phoMatchStatIdx=0; phoMatchStatIdx<NUMBIN_MATCHEDPHOTONSTATUS; phoMatchStatIdx++) {
    for(int jFlvrIdx=0; jFlvrIdx<NUMBIN_JETFLVR; jFlvrIdx++) {
    for(int varBTagIdx=0; varBTagIdx<NUM_BTAGVAR; varBTagIdx++) {
    for(int parityIdx=0; parityIdx<NUM_PARITY; parityIdx++) {
        float upperboundary = varBTagIdx == varBTagIdx_svxmass ? 5. : 1.; // idx goes to svxmass, change upper boundary.

        h_jettag[pEtaIdx][pPtIdx][phoMatchStatIdx][jFlvrIdx][varBTagIdx][parityIdx] = new TH1F(
                Form("h_jettag_%d_%d_%d_%d_%d_%d", pEtaIdx, pPtIdx, phoMatchStatIdx, jFlvrIdx, varBTagIdx, parityIdx),
                Form("h_jettag_%d_%d_%d_%d_%d_%d", pEtaIdx, pPtIdx, phoMatchStatIdx, jFlvrIdx, varBTagIdx, parityIdx),
                10, 0., upperboundary);
        h_jettag_up[pEtaIdx][pPtIdx][phoMatchStatIdx][jFlvrIdx][varBTagIdx][parityIdx] = new TH1F(
                Form("h_jettag_%sUp_%d_%d_%d_%d_%d_%d", jetFlvrNames[jFlvrIdx], pEtaIdx, pPtIdx, phoMatchStatIdx, jFlvrIdx, varBTagIdx, parityIdx),
                Form("h_jettag_%sUp_%d_%d_%d_%d_%d_%d", jetFlvrNames[jFlvrIdx], pEtaIdx, pPtIdx, phoMatchStatIdx, jFlvrIdx, varBTagIdx, parityIdx),
                10, 0., upperboundary);
        h_jettag_down[pEtaIdx][pPtIdx][phoMatchStatIdx][jFlvrIdx][varBTagIdx][parityIdx] = new TH1F(
                Form("h_jettag_%sDown_%d_%d_%d_%d_%d_%d", jetFlvrNames[jFlvrIdx], pEtaIdx, pPtIdx, phoMatchStatIdx, jFlvrIdx, varBTagIdx, parityIdx),
                Form("h_jettag_%sDown_%d_%d_%d_%d_%d_%d", jetFlvrNames[jFlvrIdx], pEtaIdx, pPtIdx, phoMatchStatIdx, jFlvrIdx, varBTagIdx, parityIdx),
                10, 0., upperboundary);
    } } } } } }

    Long64_t nentries = fChain->GetEntries();   
    printf("nentries %lli \n", nentries);
    printf("HLT option %d \n", HLTOPTION);

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        Float_t eventweight = IsMC() ? mcweight * puwei : 1.;
        Float_t photonpt = recoPtCalib;

        // if (Cut(ientry) < 0) continue;
        if(TMath::Abs(recoEta)>1.4442 && TMath::Abs(recoEta)<1.566) continue;
        if(TMath::Abs(recoEta)>2.5) continue;

        if(MET/photonpt > 0.7) continue;

        //test new mva with isolation smearing
        //if(isData!=1) 
        Float_t bdt_score = mva;// norminall
        // bdt_score = mva + trd->Gaus(0.025,0.05); //extra smearing for signal sys
        // bdt_score = mva - trd->Gaus(0.025,0.05);
        // float tmp_shift = 0.015; if(TMath::Abs(recoSCEta)>1.5) tmp_shift=0.03;
        // bdt_score = mva - tmp_shift;// - trd->Gaus(0.025,0.05);

        //jetY =jetEta;

        //printf("photon eta %.2f, bin %d,  pt %.2f, bin %d , hltbit %d\n", recoEta, EBEE(recoEta), photonpt, Ptbin(photonpt) , HLTbit(photonpt));
        int ebee = EBEE(recoEta);
        //if(recoEta>-1.8 && recoEta<-1.5) printf("ebee bin %d \n", ebee);
        int ptbin = Ptbin(photonpt);
        //int ptbin = Ptbin(photonpt*0.99); //playing with photon energy scale
        int hltbit = HLTbit(photonpt);
        int jetbin = JetEtaBin(jetY);

        //smearing due to gain switching (G6->G1)    
        TLorentzVector phoP4Orig;
        TLorentzVector *phop4 = &phoP4Orig;
        phop4->SetPtEtaPhiM(photonpt, recoEta, recoPhi,0.);



        if(eleVeto==1 && bdt_score>0.35 && chIsoRaw<2.){
            if(ebee==1 && HoverE > 0.01) continue;
            /*  asdf Modified needed !!!! asdf */
            for(int ibit=0; ibit<NUMBIT_HLT; ibit++){
                int basebit=ibit-1;
                //if(basebit==7) basebit=6;
                if(ibit>=4) basebit=3;
                if(ibit==6) basebit=5;
                if(ibit>=7) basebit=6;
                if(ibit>=9) basebit=8;
                if( (phoFiredTrgs >>basebit) & 1 ) {
                    h_HLT[ebee][ibit][0]->Fill(phop4->Et());
                    if( (phoFiredTrgs >>(ibit)) & 1 ) {
                        h_HLT[ebee][ibit][1]->Fill(phop4->Et());
                    }
                }	  
            }	
            if(phoFiredTrgs>0) {
                if(ebee==0) h_EB_HLTall->Fill(photonpt);
                else h_EE_HLTall->Fill(photonpt);
            }
        }
        /*  asdf Modified needed !!!! asdf */



        if(ptbin<0) continue;
        //if(photon_jetID==1) continue;
        // if(isData==1 && ((phoFiredTrgs>>triggerbit(ptbin))&1)==0) continue;
        // if(isData==1 && !(((phoFiredTrgs>>8)&1)==1 || MTm>0) ) continue;
        //if(!(((phoFiredTrgs>>8)&1)==1 || MTm>0) ) continue;
        if(HLTOPTION==1 && (((phoFiredTrgs>>8)&1)==0) ) continue;
        //float dr_wg = TMath::Sqrt(deta_wg*deta_wg+dphi_wg*dphi_wg);// deta_wg
        // if(MTm>0. && ebee==0 &&dr_wg<0.4) continue;
        // if(MTm>0. && ebee==1 &&dr_wg<1.) continue;
        // if(MTm>0. && dr_wg<0.4) continue;

        int isfakephoton = 0;
        if( IsMC() &&  isMatched!=1 && isConverted!=1 && isMatchedEle!=1) isfakephoton=1; //fake

        h_BDT_all[ebee][jetbin][ptbin][isfakephoton]->Fill(bdt_score, eventweight); //<-default 
        h_Pt_all[ebee][jetbin][ptbin][isfakephoton]->Fill(photonpt, eventweight);

        // asdf selections
        if ( TMath::Abs(recoEta)<1.5 && sieieFull5x5 > 0.015 ) continue;
        if ( TMath::Abs(recoEta)>1.5 && sieieFull5x5 > 0.045 ) continue;

        // jet selections
        if ( jetPt < 30. ) continue;
        if ( fabs(jetEta) > 2.5 ) continue;
        if ( jetDeepCSVTags_c < -0.99 ) continue;
        if ( jetID != 1 ) continue;
        if ( jetPUIDbit != 7 ) continue;

	//if ( mcweight>3000. ) continue;
	if ( extracut == 1 ){
	  if ( jetSubVtxMass == 0 ) continue;
	}else if ( extracut == 2 ){
	  if ( jetDeepCSVDiscriminatorTags_CvsL < 0.155) continue;
	}
	//if ( mcweight>3000. ) continue;
	//if ( jetSubVtxMass==0 ) continue;  
	//if ( jetDeepCSVDiscriminatorTags_CvsL < 0.155 ) continue;

        h_BDT[ebee][jetbin][ptbin][isfakephoton]->Fill(bdt_score, eventweight);
        h_IsovsBDT[ebee][jetbin][ptbin][isfakephoton][0]->Fill(bdt_score, chIsoRaw, eventweight);
        h_IsovsBDT[ebee][jetbin][ptbin][isfakephoton][1]->Fill(bdt_score, phoIsoRaw, eventweight);
        h_IsovsBDT[ebee][jetbin][ptbin][isfakephoton][2]->Fill(bdt_score, chIsoRaw+phoIsoRaw, eventweight);
        h_IsovsBDT[ebee][jetbin][ptbin][isfakephoton][3]->Fill(bdt_score, chWorstRaw, eventweight);


        h_Pt[ebee][isfakephoton]->Fill(photonpt, eventweight);
        h_Ptspec[ebee][isfakephoton]->Fill( phop4->Et(), eventweight);

        if ( TMath::Abs(recoEta)<1.4442 )
            if(isfakephoton==1&&photonpt>100.){
                h_chiso_sg->Fill(chIsoRaw);
                h_chworst_sg->Fill(chWorstRaw+phoIsoRaw);
            }
        //jetflvr
        int jetflvBin = JetFlavourBin(jetHadFlvr);
        int phoMatchStatIdx = 0;
	int parityIdx = ( jentry % 2 == 0 ) ? 0 : 1;
        // need to be modified asdf
        if ( isQCD )
        {
            if ( isMatched==-99 && chIsoRaw < 2.0 ) phoMatchStatIdx = 2;
            else if ( isMatched==-99 && chIsoRaw > 5.0 && chIsoRaw < 10.0 ) phoMatchStatIdx = 3;
            else    phoMatchStatIdx = 4;
        }
        else
        {
            if ( isMatched==1 && chIsoRaw<2.0   ) phoMatchStatIdx = 0;
            else    phoMatchStatIdx = 1;
        }
	

        float evtws=0.;
        float evtws_up=0.;
        float evtws_down=0.;

        if(jetflvBin==0){
            evtws      =  mcweight* jetSF_DeepCSV_central;
            evtws_up   =  mcweight* jetSF_DeepCSV_up_lf;
            evtws_down =  mcweight* jetSF_DeepCSV_down_lf;
        }else if(jetflvBin==1){
            evtws      =  mcweight* jetSF_DeepCSV_central;
            evtws_up   =  mcweight* jetSF_DeepCSV_up_cferr1;
            evtws_down =  mcweight* jetSF_DeepCSV_down_cferr1;
        }else {
            evtws      =  mcweight* jetSF_DeepCSV_central;
            evtws_up   =  mcweight* jetSF_DeepCSV_up_lf;  
            evtws_down =  mcweight* jetSF_DeepCSV_down_lf;
        }

        h_jettag     [ebee][ptbin][phoMatchStatIdx][jetflvBin][0][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_BvsAll,evtws);
        h_jettag_up  [ebee][ptbin][phoMatchStatIdx][jetflvBin][0][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_BvsAll,evtws_up);
        h_jettag_down[ebee][ptbin][phoMatchStatIdx][jetflvBin][0][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_BvsAll,evtws_down);

        h_jettag     [ebee][ptbin][phoMatchStatIdx][jetflvBin][1][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_CvsL,evtws);
        h_jettag_up  [ebee][ptbin][phoMatchStatIdx][jetflvBin][1][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_CvsL,evtws_up);
        h_jettag_down[ebee][ptbin][phoMatchStatIdx][jetflvBin][1][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_CvsL,evtws_down);

        h_jettag     [ebee][ptbin][phoMatchStatIdx][jetflvBin][2][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_CvsB,evtws);
        h_jettag_up  [ebee][ptbin][phoMatchStatIdx][jetflvBin][2][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_CvsB,evtws_up);
        h_jettag_down[ebee][ptbin][phoMatchStatIdx][jetflvBin][2][parityIdx]->Fill(jetDeepCSVDiscriminatorTags_CvsB,evtws_down);

        h_jettag     [ebee][ptbin][phoMatchStatIdx][jetflvBin][3][parityIdx]->Fill(jetSubVtxMass);

    }

    fout->cd();

    for(int pEtaIdx=0; pEtaIdx<NUMBIN_PHOETA; pEtaIdx++) {
    for(int jEtaIdx=0; jEtaIdx<NUMBIN_JETETA; jEtaIdx++) {
    for(int pPtIdx=0; pPtIdx<NUMBIN_PHOPT; pPtIdx++) {
    for(int isFakePho=0; isFakePho<2; isFakePho++) {
        h_BDT     [pEtaIdx][jEtaIdx][pPtIdx][isFakePho]->Write();
        h_IsovsBDT[pEtaIdx][jEtaIdx][pPtIdx][isFakePho][0]->Write();
        h_IsovsBDT[pEtaIdx][jEtaIdx][pPtIdx][isFakePho][1]->Write();
        h_IsovsBDT[pEtaIdx][jEtaIdx][pPtIdx][isFakePho][2]->Write();
        h_IsovsBDT[pEtaIdx][jEtaIdx][pPtIdx][isFakePho][3]->Write();
        h_BDT_all [pEtaIdx][jEtaIdx][pPtIdx][isFakePho]->Write();
        h_Pt_all  [pEtaIdx][jEtaIdx][pPtIdx][isFakePho]->Write();
    } } } }
    for(int pEtaIdx=0; pEtaIdx<NUMBIN_PHOETA; pEtaIdx++) {
    for(int isFakePho=0; isFakePho<2; isFakePho++) {
        h_Pt    [pEtaIdx][isFakePho]->Write();
        h_Ptspec[pEtaIdx][isFakePho]->Write();
    } }

    h_EB_HLTall->Write();
    h_EE_HLTall->Write();

    for (int pEtaIdx=0; pEtaIdx<NUMBIN_PHOETA; pEtaIdx++){
    for (int HLTIdx=0; HLTIdx<NUMBIT_HLT; HLTIdx++){
            h_HLT[pEtaIdx][HLTIdx][0]->Write();
            h_HLT[pEtaIdx][HLTIdx][1]->Write();
    } }

    h_chiso_sg->Write();
    h_chworst_sg->Write();

    for(int pEtaIdx=0; pEtaIdx<NUMBIN_PHOETA; pEtaIdx++) {
    for(int pPtIdx=0; pPtIdx<NUMBIN_PHOPT; pPtIdx++) {
    for(int phoMatchStatIdx=0; phoMatchStatIdx<NUMBIN_MATCHEDPHOTONSTATUS; phoMatchStatIdx++) {
    for(int jFlvrIdx=0; jFlvrIdx<NUMBIN_JETFLVR; jFlvrIdx++) {
    for(int varBTagIdx=0; varBTagIdx<NUM_BTAGVAR; varBTagIdx++) {
    for(int parityIdx=0; parityIdx<NUM_PARITY; parityIdx++) {
        h_jettag     [pEtaIdx][pPtIdx][phoMatchStatIdx][jFlvrIdx][varBTagIdx][parityIdx]->Write();
        h_jettag_up  [pEtaIdx][pPtIdx][phoMatchStatIdx][jFlvrIdx][varBTagIdx][parityIdx]->Write();
        h_jettag_down[pEtaIdx][pPtIdx][phoMatchStatIdx][jFlvrIdx][varBTagIdx][parityIdx]->Write();
    } } } } } }


    fout->Close();
}


Int_t MakeHisto::EBEE(Float_t eta)
{
    if ( TMath::Abs(eta)<1.4442 ) return 0;
    else                          return 1;
}
Int_t MakeHisto::Ptbin(Float_t pt)
{
    std::vector<float> ptcut = ptbin_ranges();
    int ibin = ptcut.size();

    // returned ibin = 0 to size-1
    while ( ibin-- )
    { if ( pt >= ptcut[ibin] ) return ibin; }

    // nothing found.
    return -1;
}

// unused
Int_t MakeHisto::HLTbit(Float_t pt){

    float ptcut[30] = {22, 30, 36, 50, 75, 90, 120, 165, 175 };

    for(int ibin=0; ibin<8; ibin++){
        if(pt>=ptcut[ibin] && pt<ptcut[ibin+1] ) return ibin;
    }
    if(pt>175) return 8;
    if(pt<22.) return -1;
    return -1;
}

Int_t MakeHisto::JetEtaBin(Float_t eta) {  
    if(jetPt==0) return 2;
    if(TMath::Abs(eta)<1.5) return 0;
    return 1;
}
Int_t MakeHisto::triggerbit(Int_t ptbin){
    if ( ptbin == 0 ) return 0;  //  25- 34
    if ( ptbin == 1 ) return 1;  //  34- 40
    if ( ptbin == 2 ) return 2;  //  40- 55
    if ( ptbin == 3 ) return 3;  //  55- 70
    if ( ptbin == 4 ) return 3;  //  70- 85
    if ( ptbin == 5 ) return 4;  // 85-100
    if ( ptbin == 6 ) return 5;  // 100-115
    if ( ptbin == 7 ) return 5;  // 115-136
    if ( ptbin == 8 ) return 6;  // 135-155
    if ( ptbin == 9 ) return 6;  // 155-175
    if ( ptbin ==10 ) return 6;  // 175-190
    if ( ptbin ==11 ) return 7;  // 190-200
    if ( ptbin ==12 ) return 7;  // 200-220
    if ( ptbin ==13 ) return 7;  // 220-250
    if ( ptbin ==14 ) return 7;  // 250-300
    if ( ptbin ==15 ) return 7;  // 300-inf
    return 0;
}
Int_t MakeHisto::JetFlavourBin( int jethadflvr )
{
    if     (fabs(jethadflvr)==5) return 2;
    else if(fabs(jethadflvr)==4) return 1;
    return 0;
}
