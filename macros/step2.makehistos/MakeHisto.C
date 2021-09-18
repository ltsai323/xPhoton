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

std::vector<float> ptbin_ranges()
{
  // for 2016
  //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
  std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
  return vec_ptcut;
}

void MakeHisto::Loop()
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

  TFile *fout = new TFile("output.root","recreate");

  TH1F *h_BDT_all[NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2]; //ebee, jetbin, ptbin, true/fake;
  TH1F *h_BDT[NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2];

  //TH1F *h_BDTvar[20][NUMBIN_PHOETA][NUMBIN_PHOPT][2]; // var, ebee, ptbin, true/fake;

  TH1F *h_Pt_all[NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2];
  TH1F *h_Pt[NUMBIN_PHOETA][2];
  TH1F *h_Ptspec[NUMBIN_PHOETA][2];
  //TH1F *h_Wmn_mt[NUMBIN_PHOETA][2]; MTm var

  TH2F *h_IsovsBDT[NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2][4]; //ebee,jetbin, ptbin, truth/fake, isovar;
  TH1F* h_btaggingvar[NUMBIN_PHOETA][NUMBIN_JETETA][NUMBIN_PHOPT][2][4]; // ebee, jetbin, ptbin, truth/fake, vars=[B,CvsL,CvsB,SVmass]


  //printf("eta bins %d \n", 8);
  char txt[100];
  char hname[100];
  //char bjetVars[4]={"
  
  
  for(int ii=0; ii<NUMBIN_PHOETA; ii++){
    for(int mm=0; mm<NUMBIN_JETETA; mm++){
      for(int jj=0; jj<NUMBIN_PHOPT; jj++){
	for(int kk=0; kk<2; kk++){
	  sprintf(txt,"BDT all  EBEE_%d_Jet_%d_ptbin_%d_true_%d",ii,mm,jj,kk);
	  sprintf(hname,"h_BDT_all_%d_%d_%d_%d",ii,mm,jj,kk);
	  h_BDT_all[ii][mm][jj][kk] = new TH1F(hname,txt,100, -1., 1.);
	  sprintf(txt,"BDT selected EBEE_%d_Jet_%d_ptbin_%d_true_%d",ii,mm,jj,kk);
	  sprintf(hname,"h_BDT_%d_%d_%d_%d",ii,mm,jj,kk);
	  h_BDT[ii][mm][jj][kk] = new TH1F(hname,txt,100, -1., 1.);

	  for(int nn=0; nn<4; nn++){
	    sprintf(txt,"Iso vs BDT EBEE_%d_Jet_%d_ptbin_%d_true_%d_Iso_%d",ii,mm,jj,kk,nn);
	    sprintf(hname,"h_IsovsBDT_%d_%d_%d_%d_%d",ii,mm,jj,kk,nn);
	    h_IsovsBDT[ii][mm][jj][kk][nn] = new TH2F(hname,txt,100, -1., 1., 30, 0., 15);
	    //h_IsovsBDT[ii][mm][jj][kk][nn] = new TH2F(hname,txt,90, -0.8, 1., 30, 0., 15);
	    h_IsovsBDT[ii][mm][jj][kk][nn]->Sumw2();

	  }
      TString names, title; // asdf
      names.Format(""); // asdf

	  sprintf(txt,"Pt all  EBEE_%d_Jet_%d_ptbin_%d_true_%d",ii,mm,jj,kk);
	  sprintf(hname,"h_Pt_all_%d_%d_%d_%d",ii,mm,jj,kk);
	  h_Pt_all[ii][mm][jj][kk] = new TH1F(hname,txt, 2000, 0., 2000.);
	  sprintf(txt,"Pt selected EBEE_%d_Jet_%d_ptbin_%d_true_%d",ii,mm,jj,kk);
	
	  h_BDT[ii][mm][jj][kk]->Sumw2(); 
	  h_Pt_all[ii][mm][jj][kk]->Sumw2();
	}
      }
    }
    for(int kk=0; kk<2; kk++){
      sprintf(txt,"Pt EBEE_%d_true_%d",ii,kk);
      sprintf(hname,"h_Pt_spec_%d_%d",ii,kk);
      h_Ptspec[ii][kk] = new TH1F(hname,txt, 200, 0., 2000.);
      h_Ptspec[ii][kk]->Sumw2();

      sprintf(hname,"h_Pt_%d_%d",ii,kk);
      h_Pt[ii][kk] = new TH1F(hname,txt, 200, 0., 2000.);
      h_Pt[ii][kk]->Sumw2();
    }
  }
  TH1F *h_EB_HLTall = new TH1F("h_EB_HLTall","all HLT photon", 1000, 0., 1000.);
  TH1F *h_EE_HLTall = new TH1F("h_EE_HLTall","all HLT photon", 1000, 0., 1000.);

  TH1F *h_chiso_sg = new TH1F("h_chiso_sg","chiso signal region", 150, 0., 30);
  TH1F *h_chworst_sg = new TH1F("h_chworst_sg","chworst signal region", 150, 0., 30);


  TH1F *h_HLT[NUMBIN_PHOETA][NUMBIT_HLT][2];
  for (int jj=0; jj<NUMBIN_PHOETA; jj++){
    for(int ii=0; ii<NUMBIT_HLT; ii++){
      sprintf(txt,"HLT ebee %d bit %d all",jj, ii);
      sprintf(hname,"h_HLT_ebee_%d_bit%d",jj, ii);
      h_HLT[jj][ii][0] = new TH1F(hname,txt, 2000, 0., 2000.);
      sprintf(txt,"HLT ebee %d bit %d pass",jj, ii);
      sprintf(hname,"h_HLT_ebee_%d_bit%d_pass",jj, ii);
      h_HLT[jj][ii][1] = new TH1F(hname,txt, 2000, 0., 2000.);
    }
  }
  float binning[10]={0,200,300, 400, 500, 100000};

  Long64_t nentries = fChain->GetEntries();   
  printf("nentries %li \n", nentries);
  printf("HLT option %d \n", HLTOPTION);

  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    Float_t eventweight = IsMC() ? mcweight * puwei : 1.;
    // if (Cut(ientry) < 0) continue;
    if(TMath::Abs(recoEta)>1.4442 && TMath::Abs(recoEta)<1.566) continue;
    if(TMath::Abs(recoEta)>2.5) continue;
    recoPt = recoPtCalib; // asdf

    if(MET/recoPt > 0.7) continue;

    //test new mva with isolation smearing
    //if(isData!=1) 
    photonIDmva = mva;// norminall
    // photonIDmva = mva + trd->Gaus(0.025,0.05); //extra smearing for signal sys
    // photonIDmva = mva - trd->Gaus(0.025,0.05);
    // float tmp_shift = 0.015; if(TMath::Abs(recoSCEta)>1.5) tmp_shift=0.03;
    // photonIDmva = mva - tmp_shift;// - trd->Gaus(0.025,0.05);

    //jetY =jetEta;

    //printf("photon eta %.2f, bin %d,  pt %.2f, bin %d , hltbit %d\n", recoEta, EBEE(recoEta), recoPt, Ptbin(recoPt) , HLTbit(recoPt));
    int ebee = EBEE(recoEta);
    //if(recoEta>-1.8 && recoEta<-1.5) printf("ebee bin %d \n", ebee);
    int ptbin = Ptbin(recoPt);
    //int ptbin = Ptbin(recoPt*0.99); //playing with photon energy scale

    //smearing due to gain switching (G6->G1)    
    TLorentzVector *phop4 = new TLorentzVector();
    phop4->SetPtEtaPhiM(recoPt, recoEta, recoPhi,0.);

    int hltbit = HLTbit(recoPt);
    int jetbin = JetEtaBin(jetY);


    if(eleVeto==1 && photonIDmva>0.35 && chIsoRaw<2.){
      if(ebee>1 && HoverE > 0.01) continue;
      /*  asdf Modified needed !!!! asdf */
      for(int ibit=0; ibit<NUMBIT_HLT; ibit++){
	int basebit=ibit-1;
	//if(basebit==7) basebit=6;
	if(ibit>=4) basebit=3;
	if(ibit==6) basebit=5;
	if(ibit>=7) basebit=6;
	if(ibit>=9) basebit=8;
	if( (phoFiredTrgs >>basebit) & 1 == 1 ) {
	  h_HLT[ebee][ibit][0]->Fill(phop4->Et());
	  if( (phoFiredTrgs >>(ibit)) & 1 == 1 ) {
	    h_HLT[ebee][ibit][1]->Fill(phop4->Et());
	  }
	}	  
      }	
      if(phoFiredTrgs>0) {
	if(ebee==0) h_EB_HLTall->Fill(recoPt);
	else h_EE_HLTall->Fill(recoPt);
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
    
    int mctruth = 0;
    if(isData!=1 && isMatched!=1 && isConverted!=1 && isMatchedEle!=1) mctruth=1; //fake

    h_BDT_all[ebee][jetbin][ptbin][mctruth]->Fill(photonIDmva, mcweight*puwei); //<-default 
    h_Pt_all[ebee][jetbin][ptbin][mctruth]->Fill(recoPt, mcweight*puwei);

    //if(isData==1 && ((phoFiredTrgs>>8)&1)==0) continue;
    //if(mctruth<0)continue;      
    //dump histogram for BDT fit
    //for all HLT photon
    //if(isData==1&&phoFiredTrgs==0) continue;
    //if(isData==1&&(Mmm<50||Mee<50)) continue;
    //if(Mee>50) continue;
    //use 175 trigger
    //if(isData==0 || (isData==1&&((phoFiredTrgs>>6) &1 ==1) )){ //175 25ns
    //if((isData==0&&phoFiredTrgs>>0 &1 ==1) || (isData==1&&phoFiredTrgs>>8 &1 ==1 )){ //175
    
    if(TMath::Abs(recoEta)<1.4442){
      if(sieieFull5x5 > 0.015) continue;

      h_BDT[ebee][jetbin][ptbin][mctruth]->Fill(photonIDmva, mcweight);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][0]->Fill(photonIDmva, chIsoRaw, mcweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][1]->Fill(photonIDmva, phoIsoRaw, mcweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][2]->Fill(photonIDmva, chIsoRaw+phoIsoRaw, mcweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][3]->Fill(photonIDmva, chWorstRaw, mcweight*puwei);

      h_Pt[ebee][mctruth]->Fill(recoPt, mcweight*puwei);
      h_Ptspec[ebee][mctruth]->Fill( phop4->Et(), mcweight*puwei);
      if(mctruth==1&&recoPt>100.){
	h_chiso_sg->Fill(chIsoRaw);
	h_chworst_sg->Fill(chWorstRaw+phoIsoRaw);
      }
    }else{
      if(sieieFull5x5>0.045)  continue;
      h_BDT[ebee][jetbin][ptbin][mctruth]->Fill(photonIDmva, mcweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][0]->Fill(photonIDmva, chIsoRaw, mcweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][1]->Fill(photonIDmva, phoIsoRaw, mcweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][2]->Fill(photonIDmva, chIsoRaw+phoIsoRaw, mcweight*puwei);
      h_IsovsBDT[ebee][jetbin][ptbin][mctruth][3]->Fill(photonIDmva, chWorstRaw, mcweight*puwei);

      h_Pt[ebee][mctruth]->Fill(recoPt, mcweight*puwei);
      h_Ptspec[ebee][mctruth]->Fill( phop4->Et(), mcweight*puwei);
    }   
  }

  TH1F *h_sf_EB = new TH1F("h_sf_EB","sf EB", 100, -1, 1.);
  TH1F *h_sf_EE = new TH1F("h_sf_EE","sf EE", 100, -1, 1.);

  fout->cd();
   
  for(int ii=0; ii<NUMBIN_PHOETA; ii++){
    for(int mm=0; mm<NUMBIN_JETETA; mm++){
      for(int jj=0; jj<NUMBIN_PHOPT; jj++){
	for(int kk=0; kk<2; kk++){
	  h_BDT[ii][mm][jj][kk]->Write();
	  h_IsovsBDT[ii][mm][jj][kk][0]->Write();
	  h_IsovsBDT[ii][mm][jj][kk][1]->Write();
	  h_IsovsBDT[ii][mm][jj][kk][2]->Write();
	  h_IsovsBDT[ii][mm][jj][kk][3]->Write();
	  h_BDT_all[ii][mm][jj][kk]->Write();
	  h_Pt_all[ii][mm][jj][kk]->Write();
	}
      }
    }
    for(int kk=0; kk<2; kk++){
      h_Pt[ii][kk]->Write();
      h_Ptspec[ii][kk]->Write();
    }
  }
   
  h_EB_HLTall->Write();
  h_EE_HLTall->Write();

  for (int jj=0; jj<NUMBIN_PHOETA; jj++){
    for(int ii=0; ii<NUMBIT_HLT; ii++){
      h_HLT[jj][ii][0]->Write();
      h_HLT[jj][ii][1]->Write();
    }
  }

  h_chiso_sg->Write();
  h_chworst_sg->Write();

  h_sf_EB->Write();
  h_sf_EE->Write();

  TDirectory* dir = (TDirectory*) fout->mkdir("jetVars");
  dir->cd();
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
