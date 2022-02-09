{
//TFile *origin = new TFile("./output_nor_mc1.root");
TFile *mc  = new TFile("../step2_makehisto/makehisto_sig_madgraph.root");
TFile *qcd = new TFile("../step2_makehisto/makehisto_QCD_madgraph.root");


//fit the 7-th ptbin

//we need (N0+N1) - N2*(N1/N2) = N0

//N0
TH1F *N0L_tag0 = (TH1F*)mc->Get("h_jettag_0_7_0_0_0_1");
TH1F *N0C_tag0 = (TH1F*)mc->Get("h_jettag_0_7_0_1_0_1");
TH1F *N0B_tag0 = (TH1F*)mc->Get("h_jettag_0_7_0_2_0_1");

TH1F *N0L_tag1 = (TH1F*)mc->Get("h_jettag_0_7_0_0_1_1");
TH1F *N0C_tag1 = (TH1F*)mc->Get("h_jettag_0_7_0_1_1_1");
TH1F *N0B_tag1 = (TH1F*)mc->Get("h_jettag_0_7_0_2_1_1");

TH1F *N0L_tag2 = (TH1F*)mc->Get("h_jettag_0_7_0_0_2_1");
TH1F *N0C_tag2 = (TH1F*)mc->Get("h_jettag_0_7_0_1_2_1");
TH1F *N0B_tag2 = (TH1F*)mc->Get("h_jettag_0_7_0_2_2_1");

TH1F *N0L_tag3 = (TH1F*)mc->Get("h_jettag_0_7_0_0_3_1");
TH1F *N0C_tag3 = (TH1F*)mc->Get("h_jettag_0_7_0_1_3_1");
TH1F *N0B_tag3 = (TH1F*)mc->Get("h_jettag_0_7_0_2_3_1");

//N1
TH1F *N1L_tag0 = (TH1F*)qcd->Get("h_jettag_0_7_2_0_0_1");
TH1F *N1C_tag0 = (TH1F*)qcd->Get("h_jettag_0_7_2_1_0_1");
TH1F *N1B_tag0 = (TH1F*)qcd->Get("h_jettag_0_7_2_2_0_1");

TH1F *N1L_tag1 = (TH1F*)qcd->Get("h_jettag_0_7_2_0_1_1");
TH1F *N1C_tag1 = (TH1F*)qcd->Get("h_jettag_0_7_2_1_1_1");
TH1F *N1B_tag1 = (TH1F*)qcd->Get("h_jettag_0_7_2_2_1_1");

TH1F *N1L_tag2 = (TH1F*)qcd->Get("h_jettag_0_7_2_0_2_1");
TH1F *N1C_tag2 = (TH1F*)qcd->Get("h_jettag_0_7_2_1_2_1");
TH1F *N1B_tag2 = (TH1F*)qcd->Get("h_jettag_0_7_2_2_2_1");

TH1F *N1L_tag3 = (TH1F*)qcd->Get("h_jettag_0_7_2_0_3_1");
TH1F *N1C_tag3 = (TH1F*)qcd->Get("h_jettag_0_7_2_1_3_1");
TH1F *N1B_tag3 = (TH1F*)qcd->Get("h_jettag_0_7_2_2_3_1");


//N2
TH1F *N2L_tag0 = (TH1F*)qcd->Get("h_jettag_0_7_3_0_0_1");
TH1F *N2C_tag0 = (TH1F*)qcd->Get("h_jettag_0_7_3_1_0_1");
TH1F *N2B_tag0 = (TH1F*)qcd->Get("h_jettag_0_7_3_2_0_1");

TH1F *N2L_tag1 = (TH1F*)qcd->Get("h_jettag_0_7_3_0_1_1");
TH1F *N2C_tag1 = (TH1F*)qcd->Get("h_jettag_0_7_3_1_1_1");
TH1F *N2B_tag1 = (TH1F*)qcd->Get("h_jettag_0_7_3_2_1_1");

TH1F *N2L_tag2 = (TH1F*)qcd->Get("h_jettag_0_7_3_0_2_1");
TH1F *N2C_tag2 = (TH1F*)qcd->Get("h_jettag_0_7_3_1_2_1");
TH1F *N2B_tag2 = (TH1F*)qcd->Get("h_jettag_0_7_3_2_2_1");

TH1F *N2L_tag3 = (TH1F*)qcd->Get("h_jettag_0_7_3_0_3_1");
TH1F *N2C_tag3 = (TH1F*)qcd->Get("h_jettag_0_7_3_1_3_1");
TH1F *N2B_tag3 = (TH1F*)qcd->Get("h_jettag_0_7_3_2_3_1");

//N0, N1, N2
TH1F N0_tag0 = *N0L_tag0 + *N0C_tag0 + *N0B_tag0;
TH1F N0_tag1 = *N0L_tag1 + *N0C_tag1 + *N0B_tag1;
TH1F N0_tag2 = *N0L_tag2 + *N0C_tag2 + *N0B_tag2;
TH1F N0_tag3 = *N0L_tag3 + *N0C_tag3 + *N0B_tag3;

TH1F N1_tag0 = *N1L_tag0 + *N1C_tag0 + *N1B_tag0;
TH1F N1_tag1 = *N1L_tag1 + *N1C_tag1 + *N1B_tag1;
TH1F N1_tag2 = *N1L_tag2 + *N1C_tag2 + *N1B_tag2;
TH1F N1_tag3 = *N1L_tag3 + *N1C_tag3 + *N1B_tag3;

TH1F N2_tag0 = *N2L_tag0 + *N2C_tag0 + *N2B_tag0;
TH1F N2_tag1 = *N2L_tag1 + *N2C_tag1 + *N2B_tag1;
TH1F N2_tag2 = *N2L_tag2 + *N2C_tag2 + *N2B_tag2;
TH1F N2_tag3 = *N2L_tag3 + *N2C_tag3 + *N2B_tag3;

//float true_L = N0L_tag0->Integral();
//float true_C = N0C_tag0->Integral();
//float true_B = N0B_tag0->Integral();

TH1F h_tag0 = N0_tag0 + N1_tag0 - (N1_tag0.Integral()/N2_tag0.Integral()) * N2_tag0;
TH1F h_tag1 = N0_tag1 + N1_tag1 - (N1_tag1.Integral()/N2_tag1.Integral()) * N2_tag1;
TH1F h_tag2 = N0_tag2 + N1_tag2 - (N1_tag2.Integral()/N2_tag2.Integral()) * N2_tag2;
TH1F h_tag3 = N0_tag3 + N1_tag3 - (N1_tag3.Integral()/N2_tag3.Integral()) * N2_tag3;

printf("%f, %f, %f\n", N0_tag1.Integral(), N1_tag1.Integral(), N2_tag1.Integral());
printf("%f\n", h_tag1.Integral());

TFile *f = new TFile("./Toy_mc2.root","recreate");

   N0_tag0.SetName("h_tag0");
   N0_tag1.SetName("h_tag1");
   N0_tag2.SetName("h_tag2");
   N0_tag3.SetName("h_tag3");

   N0_tag0.Write();
   N0_tag1.Write();
   N0_tag2.Write();
   N0_tag3.Write();

   f->Close();

}
