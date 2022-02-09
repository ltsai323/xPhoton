{
  //TFile *origin = new TFile("./output_nor_mc1.root");
TFile *mc  = new TFile("../step2_makehisto/makehisto_sig_madgraph.root");
TFile *qcd = new TFile("../step2_makehisto/makehisto_QCD_madgraph.root");

TH1F *mc_jettag[2][24][5][3][4][2];
TH1F *mc_jettag_up[2][24][5][3][4][2];
TH1F *mc_jettag_down[2][24][5][3][4][2];

TH1F *qcd_jettag[2][24][5][3][4][2];
TH1F *qcd_jettag_up[2][24][5][3][4][2];
TH1F *qcd_jettag_down[2][24][5][3][4][2];

TH1F *h_jettag[2][24][5][1][4][2];
TH1F *h_jettag_up[2][24][5][1][4][2];
TH1F *h_jettag_down[2][24][5][1][4][2];

char hname[50];
int Nbin = 10;

   for(int ii=0; ii<2; ii++){
     for(int jj=0; jj<24; jj++){
       for(int kk=0; kk<5; kk++){
	 for(int mm=0; mm<3; mm++){
	   for(int nn=0; nn<3; nn++){
	     for(int qq=0; qq<2; qq++){
	        sprintf(hname,"h_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		h_jettag[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"mc_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		mc_jettag[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
		sprintf(hname,"qcd_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		qcd_jettag[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);

	     	sprintf(hname,"h_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     	mc_jettag[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
		qcd_jettag[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);
		
	     if(mm == 0){
	        sprintf(hname,"h_jettag_sigmaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		h_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"mc_jettag_sigmaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		mc_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"qcd_jettag_sigmaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		qcd_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	       
		sprintf(hname,"h_jettag_sigmaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	    	mc_jettag_up[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
		qcd_jettag_up[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);


		sprintf(hname,"h_jettag_sigmaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		h_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"mc_jettag_sigmaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		mc_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"qcd_jettag_sigmaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		qcd_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);

             	sprintf(hname,"h_jettag_sigmaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             	mc_jettag_down[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
		qcd_jettag_down[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);
	     }else if(mm == 1){
	        sprintf(hname,"h_jettag_alphaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		h_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"mc_jettag_alphaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		mc_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"qcd_jettag_alphaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		qcd_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);

		sprintf(hname,"h_jettag_alphaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
                mc_jettag_up[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
		qcd_jettag_up[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);

		sprintf(hname,"h_jettag_alphaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		h_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"mc_jettag_alphaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		mc_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"qcd_jettag_alphaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		qcd_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);

                sprintf(hname,"h_jettag_alphaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
                mc_jettag_down[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
		qcd_jettag_down[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);
	     }else if(mm == 2){
	        sprintf(hname,"h_jettag_betaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		h_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"mc_jettag_betaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		mc_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"qcd_jettag_betaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		qcd_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);

                sprintf(hname,"h_jettag_betaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
                mc_jettag_up[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
		qcd_jettag_up[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);


		sprintf(hname,"h_jettag_betaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		h_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"mc_jettag_betaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		mc_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);
	        sprintf(hname,"qcd_jettag_betaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		qcd_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, Nbin, 0., 1.);

                sprintf(hname,"h_jettag_betaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
                mc_jettag_down[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
		qcd_jettag_down[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);
             }

	   }
	   for(int nn=3; nn<4; nn++){ //secondary vertex mass
	     sprintf(hname,"h_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     h_jettag[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     sprintf(hname,"mc_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     mc_jettag[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     sprintf(hname,"qcd_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     qcd_jettag[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     
	     sprintf(hname,"h_jettag_up_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             h_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     sprintf(hname,"mc_jettag_up_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             mc_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     sprintf(hname,"qcd_jettag_up_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             qcd_jettag_up[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);

	     sprintf(hname,"h_jettag_down_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             h_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     sprintf(hname,"mc_jettag_down_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             mc_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);
	     sprintf(hname,"qcd_jettag_down_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             qcd_jettag_down[ii][jj][kk][mm][nn] = new TH1F(hname, hname, 20, 0., 5.);


	     sprintf(hname,"h_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     mc_jettag[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
	     qcd_jettag[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);
	     sprintf(hname,"h_jettag_up_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     mc_jettag_up[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
	     qcd_jettag_up[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);
	     sprintf(hname,"h_jettag_down_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     mc_jettag_down[ii][jj][kk][mm][nn] = (TH1F*)mc->Get(hname);
	     qcd_jettag_down[ii][jj][kk][mm][nn] = (TH1F*)qcd->Get(hname);

	     }
	   }
	 }
       }
     }
   }

   float SF;
char hname0[50];
//b+bb
//mc_jettag[0][7][0][0][0]->Draw("h");
//

SF = -1* ( qcd_jettag[0][7][2][0][0]->Integral() + qcd_jettag[0][7][2][1][0]->Integral() + qcd_jettag[0][7][2][2][0]->Integral() )
	/ (qcd_jettag[0][7][3][0][0]->Integral() + qcd_jettag[0][7][3][1][0]->Integral() + qcd_jettag[0][7][3][2][0]->Integral() );
printf("the sf is %f \n", qcd_jettag[0][7][2][0][0]->Integral() + qcd_jettag[0][7][2][1][0]->Integral() + qcd_jettag[0][7][2][2][0]->Integral());
qcd_jettag[0][7][2][0][0]->Draw("h");
/*
h_jettag[0][7][0][0][0]->Add(mc_jettag[0][7][0][0][0]);
h_jettag[0][7][0][0][0]->Add(mc_jettag[0][7][0][1][0]);
h_jettag[0][7][0][0][0]->Add(mc_jettag[0][7][0][2][0]);
h_jettag[0][7][0][0][0]->Add(qcd_jettag[0][7][2][0][0]);
h_jettag[0][7][0][0][0]->Add(qcd_jettag[0][7][2][1][0]);
h_jettag[0][7][0][0][0]->Add(qcd_jettag[0][7][2][2][0]);
//qcd_jettag[0][7][3][0][0]->Scale(SF);
h_jettag[0][7][0][0][0]->Add(qcd_jettag[0][7][3][0][0]);
h_jettag[0][7][0][0][0]->Add(qcd_jettag[0][7][3][1][0]);
h_jettag[0][7][0][0][0]->Add(qcd_jettag[0][7][3][2][0]);
*/
//h_jettag[0][7][0][0][0]->Add(qcd_jettag[0][7][2][0][0]);
///h_jettag[0][7][0][0][0]->Draw("h");
//h_jettag_0_7_0_0_0 = mc_jettag_0_7_0_0_0 + mc_jettag_0_7_0_1_0 + mc_jettag_0_7_0_2_0; 
//h_jettag_0_7_0_0_0->Add(mc_jettag_0_7_0_0_0);
//h_jettag_0_7_0_0_0 ->Draw("h");
   for(int ii=0; ii<2; ii++){
     for(int jj=0; jj<24; jj++){
       for(int kk=0; kk<1; kk++){
	 for(int mm=0; mm<1; mm++){
	   for(int nn=0; nn<3; nn++){
	        SF = qcd_jettag[ii][jj][2][mm][nn]->Integral() / qcd_jettag[ii][jj][3][mm][nn]->Integral();
//		printf("the sf is %f \n", SF);
		sprintf(hname,"mc_jettag_%d_%d_%d_%d_%d", ii, jj, 0, mm, nn);
		sprintf(hname0,"h_jettag_%d_%d_%d_%d_%d", ii, jj, 0, mm, nn);
//		printf("i'm okay %d%d%d%d%d \n", ii,jj,kk,mm,nn);
		//h_jettag[ii][jj][kk][mm][nn]->Add(hname);  
	    
//		printf("i'm okay %d%d%d%d%d \n", ii,jj,kk,mm,nn);
	        //*h_jettag[ii][jj][kk][mm][nn] = *mc_jettag[ii][jj][0][mm][nn] + *qcd_jettag[ii][jj][2][mm][nn] - SF*(*qcd_jettag[ii][jj][3][mm][nn]);
	     	sprintf(hname,"h_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
		//h_jettag[ii][jj][kk][mm][nn] ->Draw("h");
	     if(mm == 0){
		sprintf(hname,"h_jettag_sigmaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             	sprintf(hname,"h_jettag_sigmaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             
	     }else if(mm == 1){
		sprintf(hname,"h_jettag_alphaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
                sprintf(hname,"h_jettag_alphaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     }else if(mm == 2){
                sprintf(hname,"h_jettag_betaUp_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
                sprintf(hname,"h_jettag_betaDown_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
             }

	   }
	   for(int nn=3; nn<4; nn++){ //secondary vertex mass
	     sprintf(hname,"h_jettag_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     sprintf(hname,"h_jettag_up_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	     sprintf(hname,"h_jettag_down_%d_%d_%d_%d_%d_%d", ii, jj, kk, mm, nn, qq);
	   }
	 }
       }
     }
   }


TFile *f = new TFile("./toy.root","recreate");

/*
   btag->Write();
   cvsl->Write();
   cvsb->Write();
   svxmass->Write();
*/

      f->Close();
}
