#define step1_create_proto_cxx
#include "step1_create_proto.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void step1_create_proto::Loop(Int_t cut)
{
 if (fChain == 0) return;

   // EBEE ; recoPt ; isMatched ; jetflvr ; tagger
   // EBEE   : 0 for EB ; 1 for EE
   // jetflv : 0 for light ; 1 for c ; 2 for b
   // tagger : 0 for b+bb ; 1 for cvsl ; 2 for cvsb ; 3 for svxmass

   TH1F *h_jettag[2][24][5][3][4];
   TH1F *h_jettag_up[2][24][5][3][4];
   TH1F *h_jettag_down[2][24][5][3][4];

   Float_t Nevts[2][24][5][3][4];

   Float_t ptcut[25]={25, 34, 40, 55, 70, 85, 100, 115, 135, 155, 175, 190, 200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000};
   
   char hname[30];
   int Nbin = 10;

   for(int ii=0; ii<2; ii++){
     for(int jj=0; jj<24; jj++){
       for(int kk=0; kk<5; kk++){
	 for(int mm=0; mm<3; mm++){
	   for(int nn=0; nn<3; nn++){

	     	sprintf(hname,"h_jettag_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
	     	h_jettag[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
		
	     if(mm == 0){
		sprintf(hname,"h_jettag_sigmaUp_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
	    	h_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
             	sprintf(hname,"h_jettag_sigmaDown_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
             	h_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);		
	     }else if(mm == 1){
		sprintf(hname,"h_jettag_alphaUp_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
                h_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
                sprintf(hname,"h_jettag_alphaDown_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
                h_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	     }else if(mm == 2){
                sprintf(hname,"h_jettag_betaUp_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
                h_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
                sprintf(hname,"h_jettag_betaDown_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
                h_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
             }

	   }
	   for(int nn=3; nn<4; nn++){ //secondary vertex mass
	     sprintf(hname,"h_jettag_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
	     h_jettag[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     sprintf(hname,"h_jettag_up_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
	     h_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     sprintf(hname,"h_jettag_down_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn);
	     h_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	   }
	 }
       }
     }
   }
   if(cut==0){
     cout << "No cut" << endl;
   }else if(cut==1){
     cout << "svxmass cut" << endl;
   }else if(cut==2){
     cout << "CvsL cut" << endl;
   }else{
     cout << "[ERROR] Wrong cut-option" << endl;
   }

   Long64_t nentries = fChain->GetEntries();
   Long64_t nbytes = 0, nb = 0;

   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      
      if (jentry % 100000 == 0){
	fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries);
      }
	
      //if(mcweight>3000.) continue;
      //if(jetSubVtxMass==0) continue;	
      //if(jetDeepCSVDiscriminatorTags_CvsL < 0.155) continue;      
      //printf("%d",cut);

      ///cut
      if(mcweight>3000.) continue;
      if(cut==1){
	if(jetSubVtxMass==0) continue;
      }else if(cut==2){
	if(jetDeepCSVDiscriminatorTags_CvsL < 0.155) continue;
      }

      int EBEEBin=0;
      int recoPtBin=0;
      int isMatchedBin=0;
      int jetflvBin=0;
      int tagalgoBin=0;
      
      //EBEE
      if(TMath::Abs(recoEta)<1.5){
	EBEEBin = 0;
      }else{
	EBEEBin = 1;
      }
      
      //recoPt      
      for(int ibin=0; ibin<24; ibin++){
	if(recoPt>=ptcut[ibin] && recoPt<ptcut[ibin+1] ) recoPtBin = ibin;
      }
      
      //isMatched
      if ( isMatched==-99 && chIsoRaw < 2.0 ){
	 isMatchedBin = 2;
      }else if ( isMatched==-99 && chIsoRaw > 5.0 && chIsoRaw < 10.0 ) {
         isMatchedBin = 3;
      }else{    
	isMatchedBin = 4;
      }

      //jetflvr
      if(fabs(jetHadFlvr)==5){
	jetflvBin=2;
      }else if(fabs(jetHadFlvr)==4){
	jetflvBin=1;
      }else{
	jetflvBin=0;
      }



      float evtws=1.0;
      float evtws_up=1.0;
      float evtws_down=1.0;

//      float jetSF_DeepCSV_central=1.0;
//      float jetSF_DeepCSV_up_lf=1.0;
//      float jetSF_DeepCSV_down_lf=1.0;
//      float jetSF_DeepCSV_up_cferr1=1.0;
//      float jetSF_DeepCSV_down_cferr1=1.0;

      if(jetflvBin==0){
	  float tmpws = evtws;
	  evtws      =  mcweight* tmpws* jetSF_DeepCSV_central;
	  evtws_up   =  mcweight* tmpws* jetSF_DeepCSV_up_lf;
	  evtws_down =  mcweight* tmpws* jetSF_DeepCSV_down_lf;
	}else if(jetflvBin==1){
	  float tmpws = evtws;
	  evtws      =  mcweight* tmpws* jetSF_DeepCSV_central;
	  evtws_up   =  mcweight* tmpws* jetSF_DeepCSV_up_cferr1;
	  evtws_down =  mcweight* tmpws* jetSF_DeepCSV_down_cferr1;
	}else {
	  float tmpws = evtws;
	  evtws      =  mcweight* tmpws* jetSF_DeepCSV_central;
	  evtws_up   =  mcweight* tmpws* jetSF_DeepCSV_up_lf;  
	  evtws_down =  mcweight* tmpws* jetSF_DeepCSV_down_lf;
	}      

//      if(jetDeepCSVDiscriminatorTags_CvsL < 0.155) {
//         h_jettag[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][0]->Fill(jetDeepCSVDiscriminatorTags_CvsL, evtws);
//      }else {

      h_jettag[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][0]->Fill(jetDeepCSVDiscriminatorTags_BvsAll, evtws);
      h_jettag_up[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][0]->Fill(jetDeepCSVDiscriminatorTags_BvsAll, evtws_up);
      h_jettag_down[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][0]->Fill(jetDeepCSVDiscriminatorTags_BvsAll,evtws_down);
	
      h_jettag[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][1]->Fill(jetDeepCSVDiscriminatorTags_CvsL,evtws);
      h_jettag_up[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][1]->Fill(jetDeepCSVDiscriminatorTags_CvsL,evtws_up);
      h_jettag_down[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][1]->Fill(jetDeepCSVDiscriminatorTags_CvsL,evtws_down);
	
      h_jettag[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][2]->Fill(jetDeepCSVDiscriminatorTags_CvsB,evtws);
      h_jettag_up[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][2]->Fill(jetDeepCSVDiscriminatorTags_CvsB,evtws_up);
      h_jettag_down[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][2]->Fill(jetDeepCSVDiscriminatorTags_CvsB,evtws_down);
	
      h_jettag[EBEEBin][recoPtBin][isMatchedBin][jetflvBin][3]->Fill(jetSubVtxMass);

//      }

   }
   
   /*
   h_jettag[0][0][0][0][0]->SetBinContent(1, h_jettag[0][0][0][0][0]->GetBinContent(0)
							 +h_jettag[0][0][0][0][0]->GetBinContent(1));
   h_jettag[0][0][0][0][0]->SetBinContent(0, 0);
   h_jettag[0][0][0][0][0]->SetBinContent(10, h_jettag[0][0][0][0][0]->GetBinContent(10)
							 +h_jettag[0][0][0][0][0]->GetBinContent(11));
   h_jettag[0][0][0][0][0]->SetBinContent(11, 0);
   */

   //bin = 0;       underflow bin
   //bin = 1;       first bin with low-edge xlow INCLUDED
   //bin = nbins;   last bin with upper-edge xup EXCLUDED
   //bin = nbins+1; overflow bin
   

   TFile *fout = new TFile("qcd_reduced.root","recreate");
   for(int ii=0; ii<2; ii++){
     for(int jj=0; jj<24; jj++){
       for(int kk=0; kk<5; kk++){
	 for(int mm=0; mm<3; mm++){
	   for(int nn=0; nn<4; nn++){

	     int nbins= h_jettag[ii][jj][kk][mm][nn]->GetNbinsX();

	     h_jettag[ii][jj][kk][mm][nn]->SetBinContent(1, h_jettag[ii][jj][kk][mm][nn]->GetBinContent(0)
							 +h_jettag[ii][jj][kk][mm][nn]->GetBinContent(1));
	     h_jettag[ii][jj][kk][mm][nn]->SetBinContent(0, 0);
	     h_jettag[ii][jj][kk][mm][nn]->SetBinContent(nbins, h_jettag[ii][jj][kk][mm][nn]->GetBinContent(nbins)
							 +h_jettag[ii][jj][kk][mm][nn]->GetBinContent(nbins+1));
	     h_jettag[ii][jj][kk][mm][nn]->SetBinContent(nbins+1, 0);


	     h_jettag_up[ii][jj][kk][mm][nn]->SetBinContent(1, h_jettag_up[ii][jj][kk][mm][nn]->GetBinContent(0)
							    +h_jettag_up[ii][jj][kk][mm][nn]->GetBinContent(1));
	     h_jettag_up[ii][jj][kk][mm][nn]->SetBinContent(0, 0);
	     h_jettag_up[ii][jj][kk][mm][nn]->SetBinContent(nbins, h_jettag_up[ii][jj][kk][mm][nn]->GetBinContent(nbins)
							    +h_jettag_up[ii][jj][kk][mm][nn]->GetBinContent(nbins+1));
	     h_jettag_up[ii][jj][kk][mm][nn]->SetBinContent(nbins+1, 0);


	     h_jettag_down[ii][jj][kk][mm][nn]->SetBinContent(1, h_jettag_down[ii][jj][kk][mm][nn]->GetBinContent(0)
							      +h_jettag_down[ii][jj][kk][mm][nn]->GetBinContent(1));
	     h_jettag_down[ii][jj][kk][mm][nn]->SetBinContent(0, 0);
	     h_jettag_down[ii][jj][kk][mm][nn]->SetBinContent(nbins, h_jettag_down[ii][jj][kk][mm][nn]->GetBinContent(nbins)
							      +h_jettag_down[ii][jj][kk][mm][nn]->GetBinContent(nbins+1));
	     h_jettag_down[ii][jj][kk][mm][nn]->SetBinContent(nbins+1, 0);

	     Nevts[ii][jj][kk][mm][nn] = h_jettag[ii][jj][kk][mm][nn]->Integral();

	     h_jettag[ii][jj][kk][mm][nn]->Write();
	     h_jettag_up[ii][jj][kk][mm][nn]->Write();
	     h_jettag_down[ii][jj][kk][mm][nn]->Write();
	   }
	 }
       }
     }
   }

fout->Close();

TFile *fout2 = new TFile("qcd_reduced_nor.root","recreate");
   for(int ii=0; ii<2; ii++){
     for(int jj=0; jj<24; jj++){
       for(int kk=0; kk<5; kk++){
         for(int mm=0; mm<3; mm++){
           for(int nn=0; nn<4; nn++){


             h_jettag[ii][jj][kk][mm][nn]->Scale(1./h_jettag[ii][jj][kk][mm][nn]->Integral());
             h_jettag_up[ii][jj][kk][mm][nn]->Scale(1./h_jettag_up[ii][jj][kk][mm][nn]->Integral());
             h_jettag_down[ii][jj][kk][mm][nn]->Scale(1./h_jettag_down[ii][jj][kk][mm][nn]->Integral());


             h_jettag[ii][jj][kk][mm][nn]->Write();
             h_jettag_up[ii][jj][kk][mm][nn]->Write();
             h_jettag_down[ii][jj][kk][mm][nn]->Write();
           }
         }
       }
     }
   }
}

