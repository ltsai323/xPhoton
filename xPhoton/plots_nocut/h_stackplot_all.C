void h_stackplot_all()
{
//=========Macro generated from canvas: bigCanvas/
//=========  (Thu Oct  6 16:03:30 2022) by ROOT version6.10/09
   TCanvas *bigCanvas = new TCanvas("bigCanvas", "",0,0,2000,2000);
   bigCanvas->Range(0,0,1,1);
   bigCanvas->SetFillColor(0);
   bigCanvas->SetBorderMode(0);
   bigCanvas->SetBorderSize(2);
   bigCanvas->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: bigCanvas_1
   TPad *bigCanvas_1 = new TPad("bigCanvas_1", "bigCanvas_1",0.01,0.81,0.19,0.99);
   bigCanvas_1->Draw();
   bigCanvas_1->cd();
   bigCanvas_1->Range(0,0,1,1);
   bigCanvas_1->SetFillColor(0);
   bigCanvas_1->SetBorderMode(0);
   bigCanvas_1->SetBorderSize(2);
   bigCanvas_1->SetLogx();
   bigCanvas_1->SetLogy();
   bigCanvas_1->SetFrameBorderMode(0);
   
   THStack *stackplot_0 = new THStack();
   stackplot_0->SetName("stackplot_0");
   stackplot_0->SetTitle("");
   Double_t xAxis1[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *stackplot_0_stack_1 = new TH1F("stackplot_0_stack_1","",18, xAxis1);
   stackplot_0_stack_1->SetMinimum(0.0003966869);
   stackplot_0_stack_1->SetMaximum(1.586748);
   stackplot_0_stack_1->SetDirectory(0);
   stackplot_0_stack_1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   stackplot_0_stack_1->SetLineColor(ci);
   stackplot_0_stack_1->GetXaxis()->SetLabelFont(42);
   stackplot_0_stack_1->GetXaxis()->SetLabelSize(0.035);
   stackplot_0_stack_1->GetXaxis()->SetTitleSize(0.035);
   stackplot_0_stack_1->GetXaxis()->SetTitleFont(42);
   stackplot_0_stack_1->GetYaxis()->SetLabelFont(42);
   stackplot_0_stack_1->GetYaxis()->SetLabelSize(0.035);
   stackplot_0_stack_1->GetYaxis()->SetTitleSize(0.035);
   stackplot_0_stack_1->GetYaxis()->SetTitleOffset(0);
   stackplot_0_stack_1->GetYaxis()->SetTitleFont(42);
   stackplot_0_stack_1->GetZaxis()->SetLabelFont(42);
   stackplot_0_stack_1->GetZaxis()->SetLabelSize(0.035);
   stackplot_0_stack_1->GetZaxis()->SetTitleSize(0.035);
   stackplot_0_stack_1->GetZaxis()->SetTitleFont(42);
   stackplot_0->SetHistogram(stackplot_0_stack_1);
   
   Double_t xAxis2[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_0_stack_1 = new TH1F("weight_0_0_stack_1","",18, xAxis2);
   weight_0_0_stack_1->SetBinContent(17,0.9917173);
   weight_0_0_stack_1->SetBinError(17,0.0009024934);
   weight_0_0_stack_1->SetEntries(1231853);
   weight_0_0_stack_1->SetFillColor(2);
   weight_0_0_stack_1->SetLineColor(2);
   weight_0_0_stack_1->GetXaxis()->SetLabelFont(42);
   weight_0_0_stack_1->GetXaxis()->SetLabelSize(0.035);
   weight_0_0_stack_1->GetXaxis()->SetTitleSize(0.035);
   weight_0_0_stack_1->GetXaxis()->SetTitleFont(42);
   weight_0_0_stack_1->GetYaxis()->SetLabelFont(42);
   weight_0_0_stack_1->GetYaxis()->SetLabelSize(0.035);
   weight_0_0_stack_1->GetYaxis()->SetTitleSize(0.035);
   weight_0_0_stack_1->GetYaxis()->SetTitleOffset(0);
   weight_0_0_stack_1->GetYaxis()->SetTitleFont(42);
   weight_0_0_stack_1->GetZaxis()->SetLabelFont(42);
   weight_0_0_stack_1->GetZaxis()->SetLabelSize(0.035);
   weight_0_0_stack_1->GetZaxis()->SetTitleSize(0.035);
   weight_0_0_stack_1->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_0_stack_1,"");
   Double_t xAxis3[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_1_stack_2 = new TH1F("weight_0_1_stack_2","",18, xAxis3);
   weight_0_1_stack_2->SetBinContent(15,0.008282289);
   weight_0_1_stack_2->SetBinError(15,6.169133e-06);
   weight_0_1_stack_2->SetEntries(1767165);
   weight_0_1_stack_2->SetFillColor(3);
   weight_0_1_stack_2->SetLineColor(3);
   weight_0_1_stack_2->GetXaxis()->SetLabelFont(42);
   weight_0_1_stack_2->GetXaxis()->SetLabelSize(0.035);
   weight_0_1_stack_2->GetXaxis()->SetTitleSize(0.035);
   weight_0_1_stack_2->GetXaxis()->SetTitleFont(42);
   weight_0_1_stack_2->GetYaxis()->SetLabelFont(42);
   weight_0_1_stack_2->GetYaxis()->SetLabelSize(0.035);
   weight_0_1_stack_2->GetYaxis()->SetTitleSize(0.035);
   weight_0_1_stack_2->GetYaxis()->SetTitleOffset(0);
   weight_0_1_stack_2->GetYaxis()->SetTitleFont(42);
   weight_0_1_stack_2->GetZaxis()->SetLabelFont(42);
   weight_0_1_stack_2->GetZaxis()->SetLabelSize(0.035);
   weight_0_1_stack_2->GetZaxis()->SetTitleSize(0.035);
   weight_0_1_stack_2->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_1_stack_2,"");
   Double_t xAxis4[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_2_stack_3 = new TH1F("weight_0_2_stack_3","",18, xAxis4);
   weight_0_2_stack_3->SetFillColor(4);
   weight_0_2_stack_3->SetLineColor(4);
   weight_0_2_stack_3->GetXaxis()->SetLabelFont(42);
   weight_0_2_stack_3->GetXaxis()->SetLabelSize(0.035);
   weight_0_2_stack_3->GetXaxis()->SetTitleSize(0.035);
   weight_0_2_stack_3->GetXaxis()->SetTitleFont(42);
   weight_0_2_stack_3->GetYaxis()->SetLabelFont(42);
   weight_0_2_stack_3->GetYaxis()->SetLabelSize(0.035);
   weight_0_2_stack_3->GetYaxis()->SetTitleSize(0.035);
   weight_0_2_stack_3->GetYaxis()->SetTitleOffset(0);
   weight_0_2_stack_3->GetYaxis()->SetTitleFont(42);
   weight_0_2_stack_3->GetZaxis()->SetLabelFont(42);
   weight_0_2_stack_3->GetZaxis()->SetLabelSize(0.035);
   weight_0_2_stack_3->GetZaxis()->SetTitleSize(0.035);
   weight_0_2_stack_3->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_2_stack_3,"");
   Double_t xAxis5[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_3_stack_4 = new TH1F("weight_0_3_stack_4","",18, xAxis5);
   weight_0_3_stack_4->SetBinContent(14,4.541537e-07);
   weight_0_3_stack_4->SetBinError(14,1.353417e-08);
   weight_0_3_stack_4->SetEntries(1126);
   weight_0_3_stack_4->SetFillColor(8);
   weight_0_3_stack_4->SetLineColor(8);
   weight_0_3_stack_4->GetXaxis()->SetLabelFont(42);
   weight_0_3_stack_4->GetXaxis()->SetLabelSize(0.035);
   weight_0_3_stack_4->GetXaxis()->SetTitleSize(0.035);
   weight_0_3_stack_4->GetXaxis()->SetTitleFont(42);
   weight_0_3_stack_4->GetYaxis()->SetLabelFont(42);
   weight_0_3_stack_4->GetYaxis()->SetLabelSize(0.035);
   weight_0_3_stack_4->GetYaxis()->SetTitleSize(0.035);
   weight_0_3_stack_4->GetYaxis()->SetTitleOffset(0);
   weight_0_3_stack_4->GetYaxis()->SetTitleFont(42);
   weight_0_3_stack_4->GetZaxis()->SetLabelFont(42);
   weight_0_3_stack_4->GetZaxis()->SetLabelSize(0.035);
   weight_0_3_stack_4->GetZaxis()->SetTitleSize(0.035);
   weight_0_3_stack_4->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_3_stack_4,"");
   Double_t xAxis6[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_4_stack_5 = new TH1F("weight_0_4_stack_5","",18, xAxis6);
   weight_0_4_stack_5->SetBinContent(11,1.574346e-09);
   weight_0_4_stack_5->SetBinError(11,3.71077e-10);
   weight_0_4_stack_5->SetEntries(18);
   weight_0_4_stack_5->SetFillColor(32);
   weight_0_4_stack_5->SetLineColor(32);
   weight_0_4_stack_5->GetXaxis()->SetLabelFont(42);
   weight_0_4_stack_5->GetXaxis()->SetLabelSize(0.035);
   weight_0_4_stack_5->GetXaxis()->SetTitleSize(0.035);
   weight_0_4_stack_5->GetXaxis()->SetTitleFont(42);
   weight_0_4_stack_5->GetYaxis()->SetLabelFont(42);
   weight_0_4_stack_5->GetYaxis()->SetLabelSize(0.035);
   weight_0_4_stack_5->GetYaxis()->SetTitleSize(0.035);
   weight_0_4_stack_5->GetYaxis()->SetTitleOffset(0);
   weight_0_4_stack_5->GetYaxis()->SetTitleFont(42);
   weight_0_4_stack_5->GetZaxis()->SetLabelFont(42);
   weight_0_4_stack_5->GetZaxis()->SetLabelSize(0.035);
   weight_0_4_stack_5->GetZaxis()->SetTitleSize(0.035);
   weight_0_4_stack_5->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_4_stack_5,"");
   Double_t xAxis7[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_5_stack_6 = new TH1F("weight_0_5_stack_6","",18, xAxis7);
   weight_0_5_stack_6->SetFillColor(38);
   weight_0_5_stack_6->SetLineColor(38);
   weight_0_5_stack_6->GetXaxis()->SetLabelFont(42);
   weight_0_5_stack_6->GetXaxis()->SetLabelSize(0.035);
   weight_0_5_stack_6->GetXaxis()->SetTitleSize(0.035);
   weight_0_5_stack_6->GetXaxis()->SetTitleFont(42);
   weight_0_5_stack_6->GetYaxis()->SetLabelFont(42);
   weight_0_5_stack_6->GetYaxis()->SetLabelSize(0.035);
   weight_0_5_stack_6->GetYaxis()->SetTitleSize(0.035);
   weight_0_5_stack_6->GetYaxis()->SetTitleOffset(0);
   weight_0_5_stack_6->GetYaxis()->SetTitleFont(42);
   weight_0_5_stack_6->GetZaxis()->SetLabelFont(42);
   weight_0_5_stack_6->GetZaxis()->SetLabelSize(0.035);
   weight_0_5_stack_6->GetZaxis()->SetTitleSize(0.035);
   weight_0_5_stack_6->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_5_stack_6,"");
   Double_t xAxis8[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_6_stack_7 = new TH1F("weight_0_6_stack_7","",18, xAxis8);
   weight_0_6_stack_7->SetFillColor(42);
   weight_0_6_stack_7->SetLineColor(42);
   weight_0_6_stack_7->GetXaxis()->SetLabelFont(42);
   weight_0_6_stack_7->GetXaxis()->SetLabelSize(0.035);
   weight_0_6_stack_7->GetXaxis()->SetTitleSize(0.035);
   weight_0_6_stack_7->GetXaxis()->SetTitleFont(42);
   weight_0_6_stack_7->GetYaxis()->SetLabelFont(42);
   weight_0_6_stack_7->GetYaxis()->SetLabelSize(0.035);
   weight_0_6_stack_7->GetYaxis()->SetTitleSize(0.035);
   weight_0_6_stack_7->GetYaxis()->SetTitleOffset(0);
   weight_0_6_stack_7->GetYaxis()->SetTitleFont(42);
   weight_0_6_stack_7->GetZaxis()->SetLabelFont(42);
   weight_0_6_stack_7->GetZaxis()->SetLabelSize(0.035);
   weight_0_6_stack_7->GetZaxis()->SetTitleSize(0.035);
   weight_0_6_stack_7->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_6_stack_7,"");
   Double_t xAxis9[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_7_stack_8 = new TH1F("weight_0_7_stack_8","",18, xAxis9);
   weight_0_7_stack_8->SetFillColor(46);
   weight_0_7_stack_8->SetLineColor(46);
   weight_0_7_stack_8->GetXaxis()->SetLabelFont(42);
   weight_0_7_stack_8->GetXaxis()->SetLabelSize(0.035);
   weight_0_7_stack_8->GetXaxis()->SetTitleSize(0.035);
   weight_0_7_stack_8->GetXaxis()->SetTitleFont(42);
   weight_0_7_stack_8->GetYaxis()->SetLabelFont(42);
   weight_0_7_stack_8->GetYaxis()->SetLabelSize(0.035);
   weight_0_7_stack_8->GetYaxis()->SetTitleSize(0.035);
   weight_0_7_stack_8->GetYaxis()->SetTitleOffset(0);
   weight_0_7_stack_8->GetYaxis()->SetTitleFont(42);
   weight_0_7_stack_8->GetZaxis()->SetLabelFont(42);
   weight_0_7_stack_8->GetZaxis()->SetLabelSize(0.035);
   weight_0_7_stack_8->GetZaxis()->SetTitleSize(0.035);
   weight_0_7_stack_8->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_7_stack_8,"");
   Double_t xAxis10[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_0_8_stack_9 = new TH1F("weight_0_8_stack_9","",18, xAxis10);
   weight_0_8_stack_9->SetFillColor(49);
   weight_0_8_stack_9->SetLineColor(49);
   weight_0_8_stack_9->GetXaxis()->SetLabelFont(42);
   weight_0_8_stack_9->GetXaxis()->SetLabelSize(0.035);
   weight_0_8_stack_9->GetXaxis()->SetTitleSize(0.035);
   weight_0_8_stack_9->GetXaxis()->SetTitleFont(42);
   weight_0_8_stack_9->GetYaxis()->SetLabelFont(42);
   weight_0_8_stack_9->GetYaxis()->SetLabelSize(0.035);
   weight_0_8_stack_9->GetYaxis()->SetTitleSize(0.035);
   weight_0_8_stack_9->GetYaxis()->SetTitleOffset(0);
   weight_0_8_stack_9->GetYaxis()->SetTitleFont(42);
   weight_0_8_stack_9->GetZaxis()->SetLabelFont(42);
   weight_0_8_stack_9->GetZaxis()->SetLabelSize(0.035);
   weight_0_8_stack_9->GetZaxis()->SetTitleSize(0.035);
   weight_0_8_stack_9->GetZaxis()->SetTitleFont(42);
   stackplot_0->Add(weight_0_8_stack_9,"");
   stackplot_0->Draw("hist");

   TText* text = new TText( 0.13, 1.82, "Pt = 100GeV" );
   text->Draw();
   bigCanvas_1->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_2
   TPad *bigCanvas_2 = new TPad("bigCanvas_2", "bigCanvas_2",0.21,0.81,0.39,0.99);
   bigCanvas_2->Draw();
   bigCanvas_2->cd();
   bigCanvas_2->Range(0,0,1,1);
   bigCanvas_2->SetFillColor(0);
   bigCanvas_2->SetBorderMode(0);
   bigCanvas_2->SetBorderSize(2);
   bigCanvas_2->SetLogx();
   bigCanvas_2->SetLogy();
   bigCanvas_2->SetFrameBorderMode(0);
   
   THStack* stackplot_1 = new THStack();
   stackplot_1->SetName("stackplot_1");
   stackplot_1->SetTitle("");
   Double_t xAxis11[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *stackplot_1_stack_2 = new TH1F("stackplot_1_stack_2","",18, xAxis11);
   stackplot_1_stack_2->SetMinimum(0.0003882);
   stackplot_1_stack_2->SetMaximum(1.5528);
   stackplot_1_stack_2->SetDirectory(0);
   stackplot_1_stack_2->SetStats(0);

   ci = TColor::GetColor("#000099");
   stackplot_1_stack_2->SetLineColor(ci);
   stackplot_1_stack_2->GetXaxis()->SetLabelFont(42);
   stackplot_1_stack_2->GetXaxis()->SetLabelSize(0.035);
   stackplot_1_stack_2->GetXaxis()->SetTitleSize(0.035);
   stackplot_1_stack_2->GetXaxis()->SetTitleFont(42);
   stackplot_1_stack_2->GetYaxis()->SetLabelFont(42);
   stackplot_1_stack_2->GetYaxis()->SetLabelSize(0.035);
   stackplot_1_stack_2->GetYaxis()->SetTitleSize(0.035);
   stackplot_1_stack_2->GetYaxis()->SetTitleOffset(0);
   stackplot_1_stack_2->GetYaxis()->SetTitleFont(42);
   stackplot_1_stack_2->GetZaxis()->SetLabelFont(42);
   stackplot_1_stack_2->GetZaxis()->SetLabelSize(0.035);
   stackplot_1_stack_2->GetZaxis()->SetTitleSize(0.035);
   stackplot_1_stack_2->GetZaxis()->SetTitleFont(42);
   stackplot_1->SetHistogram(stackplot_1_stack_2);
   
   Double_t xAxis12[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_0_stack_1 = new TH1F("weight_1_0_stack_1","",18, xAxis12);
   weight_1_0_stack_1->SetBinContent(17,0.9705001);
   weight_1_0_stack_1->SetBinError(17,0.0007665646);
   weight_1_0_stack_1->SetEntries(1637700);
   weight_1_0_stack_1->SetFillColor(2);
   weight_1_0_stack_1->SetLineColor(2);
   weight_1_0_stack_1->GetXaxis()->SetLabelFont(42);
   weight_1_0_stack_1->GetXaxis()->SetLabelSize(0.035);
   weight_1_0_stack_1->GetXaxis()->SetTitleSize(0.035);
   weight_1_0_stack_1->GetXaxis()->SetTitleFont(42);
   weight_1_0_stack_1->GetYaxis()->SetLabelFont(42);
   weight_1_0_stack_1->GetYaxis()->SetLabelSize(0.035);
   weight_1_0_stack_1->GetYaxis()->SetTitleSize(0.035);
   weight_1_0_stack_1->GetYaxis()->SetTitleOffset(0);
   weight_1_0_stack_1->GetYaxis()->SetTitleFont(42);
   weight_1_0_stack_1->GetZaxis()->SetLabelFont(42);
   weight_1_0_stack_1->GetZaxis()->SetLabelSize(0.035);
   weight_1_0_stack_1->GetZaxis()->SetTitleSize(0.035);
   weight_1_0_stack_1->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_0_stack_1,"");
   Double_t xAxis13[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_1_stack_2 = new TH1F("weight_1_1_stack_2","",18, xAxis13);
   weight_1_1_stack_2->SetBinContent(15,0.0294936);
   weight_1_1_stack_2->SetBinError(15,1.080023e-05);
   weight_1_1_stack_2->SetEntries(9980690);
   weight_1_1_stack_2->SetFillColor(3);
   weight_1_1_stack_2->SetLineColor(3);
   weight_1_1_stack_2->GetXaxis()->SetLabelFont(42);
   weight_1_1_stack_2->GetXaxis()->SetLabelSize(0.035);
   weight_1_1_stack_2->GetXaxis()->SetTitleSize(0.035);
   weight_1_1_stack_2->GetXaxis()->SetTitleFont(42);
   weight_1_1_stack_2->GetYaxis()->SetLabelFont(42);
   weight_1_1_stack_2->GetYaxis()->SetLabelSize(0.035);
   weight_1_1_stack_2->GetYaxis()->SetTitleSize(0.035);
   weight_1_1_stack_2->GetYaxis()->SetTitleOffset(0);
   weight_1_1_stack_2->GetYaxis()->SetTitleFont(42);
   weight_1_1_stack_2->GetZaxis()->SetLabelFont(42);
   weight_1_1_stack_2->GetZaxis()->SetLabelSize(0.035);
   weight_1_1_stack_2->GetZaxis()->SetTitleSize(0.035);
   weight_1_1_stack_2->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_1_stack_2,"");
   Double_t xAxis14[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_2_stack_3 = new TH1F("weight_1_2_stack_3","",18, xAxis14);
   weight_1_2_stack_3->SetFillColor(4);
   weight_1_2_stack_3->SetLineColor(4);
   weight_1_2_stack_3->GetXaxis()->SetLabelFont(42);
   weight_1_2_stack_3->GetXaxis()->SetLabelSize(0.035);
   weight_1_2_stack_3->GetXaxis()->SetTitleSize(0.035);
   weight_1_2_stack_3->GetXaxis()->SetTitleFont(42);
   weight_1_2_stack_3->GetYaxis()->SetLabelFont(42);
   weight_1_2_stack_3->GetYaxis()->SetLabelSize(0.035);
   weight_1_2_stack_3->GetYaxis()->SetTitleSize(0.035);
   weight_1_2_stack_3->GetYaxis()->SetTitleOffset(0);
   weight_1_2_stack_3->GetYaxis()->SetTitleFont(42);
   weight_1_2_stack_3->GetZaxis()->SetLabelFont(42);
   weight_1_2_stack_3->GetZaxis()->SetLabelSize(0.035);
   weight_1_2_stack_3->GetZaxis()->SetTitleSize(0.035);
   weight_1_2_stack_3->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_2_stack_3,"");
   Double_t xAxis15[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_3_stack_4 = new TH1F("weight_1_3_stack_4","",18, xAxis15);
   weight_1_3_stack_4->SetBinContent(14,6.335203e-06);
   weight_1_3_stack_4->SetBinError(14,4.338436e-08);
   weight_1_3_stack_4->SetEntries(21321);
   weight_1_3_stack_4->SetFillColor(8);
   weight_1_3_stack_4->SetLineColor(8);
   weight_1_3_stack_4->GetXaxis()->SetLabelFont(42);
   weight_1_3_stack_4->GetXaxis()->SetLabelSize(0.035);
   weight_1_3_stack_4->GetXaxis()->SetTitleSize(0.035);
   weight_1_3_stack_4->GetXaxis()->SetTitleFont(42);
   weight_1_3_stack_4->GetYaxis()->SetLabelFont(42);
   weight_1_3_stack_4->GetYaxis()->SetLabelSize(0.035);
   weight_1_3_stack_4->GetYaxis()->SetTitleSize(0.035);
   weight_1_3_stack_4->GetYaxis()->SetTitleOffset(0);
   weight_1_3_stack_4->GetYaxis()->SetTitleFont(42);
   weight_1_3_stack_4->GetZaxis()->SetLabelFont(42);
   weight_1_3_stack_4->GetZaxis()->SetLabelSize(0.035);
   weight_1_3_stack_4->GetZaxis()->SetTitleSize(0.035);
   weight_1_3_stack_4->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_3_stack_4,"");
   Double_t xAxis16[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_4_stack_5 = new TH1F("weight_1_4_stack_5","",18, xAxis16);
   weight_1_4_stack_5->SetBinContent(11,1.752527e-08);
   weight_1_4_stack_5->SetBinError(11,1.062623e-09);
   weight_1_4_stack_5->SetEntries(272);
   weight_1_4_stack_5->SetFillColor(32);
   weight_1_4_stack_5->SetLineColor(32);
   weight_1_4_stack_5->GetXaxis()->SetLabelFont(42);
   weight_1_4_stack_5->GetXaxis()->SetLabelSize(0.035);
   weight_1_4_stack_5->GetXaxis()->SetTitleSize(0.035);
   weight_1_4_stack_5->GetXaxis()->SetTitleFont(42);
   weight_1_4_stack_5->GetYaxis()->SetLabelFont(42);
   weight_1_4_stack_5->GetYaxis()->SetLabelSize(0.035);
   weight_1_4_stack_5->GetYaxis()->SetTitleSize(0.035);
   weight_1_4_stack_5->GetYaxis()->SetTitleOffset(0);
   weight_1_4_stack_5->GetYaxis()->SetTitleFont(42);
   weight_1_4_stack_5->GetZaxis()->SetLabelFont(42);
   weight_1_4_stack_5->GetZaxis()->SetLabelSize(0.035);
   weight_1_4_stack_5->GetZaxis()->SetTitleSize(0.035);
   weight_1_4_stack_5->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_4_stack_5,"");
   Double_t xAxis17[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_5_stack_6 = new TH1F("weight_1_5_stack_6","",18, xAxis17);
   weight_1_5_stack_6->SetBinContent(9,1.564654e-11);
   weight_1_5_stack_6->SetBinError(9,9.033533e-12);
   weight_1_5_stack_6->SetEntries(3);
   weight_1_5_stack_6->SetFillColor(38);
   weight_1_5_stack_6->SetLineColor(38);
   weight_1_5_stack_6->GetXaxis()->SetLabelFont(42);
   weight_1_5_stack_6->GetXaxis()->SetLabelSize(0.035);
   weight_1_5_stack_6->GetXaxis()->SetTitleSize(0.035);
   weight_1_5_stack_6->GetXaxis()->SetTitleFont(42);
   weight_1_5_stack_6->GetYaxis()->SetLabelFont(42);
   weight_1_5_stack_6->GetYaxis()->SetLabelSize(0.035);
   weight_1_5_stack_6->GetYaxis()->SetTitleSize(0.035);
   weight_1_5_stack_6->GetYaxis()->SetTitleOffset(0);
   weight_1_5_stack_6->GetYaxis()->SetTitleFont(42);
   weight_1_5_stack_6->GetZaxis()->SetLabelFont(42);
   weight_1_5_stack_6->GetZaxis()->SetLabelSize(0.035);
   weight_1_5_stack_6->GetZaxis()->SetTitleSize(0.035);
   weight_1_5_stack_6->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_5_stack_6,"");
   Double_t xAxis18[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_6_stack_7 = new TH1F("weight_1_6_stack_7","",18, xAxis18);
   weight_1_6_stack_7->SetFillColor(42);
   weight_1_6_stack_7->SetLineColor(42);
   weight_1_6_stack_7->GetXaxis()->SetLabelFont(42);
   weight_1_6_stack_7->GetXaxis()->SetLabelSize(0.035);
   weight_1_6_stack_7->GetXaxis()->SetTitleSize(0.035);
   weight_1_6_stack_7->GetXaxis()->SetTitleFont(42);
   weight_1_6_stack_7->GetYaxis()->SetLabelFont(42);
   weight_1_6_stack_7->GetYaxis()->SetLabelSize(0.035);
   weight_1_6_stack_7->GetYaxis()->SetTitleSize(0.035);
   weight_1_6_stack_7->GetYaxis()->SetTitleOffset(0);
   weight_1_6_stack_7->GetYaxis()->SetTitleFont(42);
   weight_1_6_stack_7->GetZaxis()->SetLabelFont(42);
   weight_1_6_stack_7->GetZaxis()->SetLabelSize(0.035);
   weight_1_6_stack_7->GetZaxis()->SetTitleSize(0.035);
   weight_1_6_stack_7->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_6_stack_7,"");
   Double_t xAxis19[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_7_stack_8 = new TH1F("weight_1_7_stack_8","",18, xAxis19);
   weight_1_7_stack_8->SetFillColor(46);
   weight_1_7_stack_8->SetLineColor(46);
   weight_1_7_stack_8->GetXaxis()->SetLabelFont(42);
   weight_1_7_stack_8->GetXaxis()->SetLabelSize(0.035);
   weight_1_7_stack_8->GetXaxis()->SetTitleSize(0.035);
   weight_1_7_stack_8->GetXaxis()->SetTitleFont(42);
   weight_1_7_stack_8->GetYaxis()->SetLabelFont(42);
   weight_1_7_stack_8->GetYaxis()->SetLabelSize(0.035);
   weight_1_7_stack_8->GetYaxis()->SetTitleSize(0.035);
   weight_1_7_stack_8->GetYaxis()->SetTitleOffset(0);
   weight_1_7_stack_8->GetYaxis()->SetTitleFont(42);
   weight_1_7_stack_8->GetZaxis()->SetLabelFont(42);
   weight_1_7_stack_8->GetZaxis()->SetLabelSize(0.035);
   weight_1_7_stack_8->GetZaxis()->SetTitleSize(0.035);
   weight_1_7_stack_8->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_7_stack_8,"");
   Double_t xAxis20[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_1_8_stack_9 = new TH1F("weight_1_8_stack_9","",18, xAxis20);
   weight_1_8_stack_9->SetFillColor(49);
   weight_1_8_stack_9->SetLineColor(49);
   weight_1_8_stack_9->GetXaxis()->SetLabelFont(42);
   weight_1_8_stack_9->GetXaxis()->SetLabelSize(0.035);
   weight_1_8_stack_9->GetXaxis()->SetTitleSize(0.035);
   weight_1_8_stack_9->GetXaxis()->SetTitleFont(42);
   weight_1_8_stack_9->GetYaxis()->SetLabelFont(42);
   weight_1_8_stack_9->GetYaxis()->SetLabelSize(0.035);
   weight_1_8_stack_9->GetYaxis()->SetTitleSize(0.035);
   weight_1_8_stack_9->GetYaxis()->SetTitleOffset(0);
   weight_1_8_stack_9->GetYaxis()->SetTitleFont(42);
   weight_1_8_stack_9->GetZaxis()->SetLabelFont(42);
   weight_1_8_stack_9->GetZaxis()->SetLabelSize(0.035);
   weight_1_8_stack_9->GetZaxis()->SetTitleSize(0.035);
   weight_1_8_stack_9->GetZaxis()->SetTitleFont(42);
   stackplot_1->Add(weight_1_8_stack_9,"");
   stackplot_1->Draw("hist");
   bigCanvas_2->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_3
   TPad *bigCanvas_3 = new TPad("bigCanvas_3", "bigCanvas_3",0.41,0.81,0.59,0.99);
   bigCanvas_3->Draw();
   bigCanvas_3->cd();
   bigCanvas_3->Range(0,0,1,1);
   bigCanvas_3->SetFillColor(0);
   bigCanvas_3->SetBorderMode(0);
   bigCanvas_3->SetBorderSize(2);
   bigCanvas_3->SetLogx();
   bigCanvas_3->SetLogy();
   bigCanvas_3->SetFrameBorderMode(0);
   
   THStack* stackplot_2 = new THStack();
   stackplot_2->SetName("stackplot_2");
   stackplot_2->SetTitle("");
   Double_t xAxis21[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *stackplot_2_stack_3 = new TH1F("stackplot_2_stack_3","",18, xAxis21);
   stackplot_2_stack_3->SetMinimum(0.0003692231);
   stackplot_2_stack_3->SetMaximum(1.476892);
   stackplot_2_stack_3->SetDirectory(0);
   stackplot_2_stack_3->SetStats(0);

   ci = TColor::GetColor("#000099");
   stackplot_2_stack_3->SetLineColor(ci);
   stackplot_2_stack_3->GetXaxis()->SetLabelFont(42);
   stackplot_2_stack_3->GetXaxis()->SetLabelSize(0.035);
   stackplot_2_stack_3->GetXaxis()->SetTitleSize(0.035);
   stackplot_2_stack_3->GetXaxis()->SetTitleFont(42);
   stackplot_2_stack_3->GetYaxis()->SetLabelFont(42);
   stackplot_2_stack_3->GetYaxis()->SetLabelSize(0.035);
   stackplot_2_stack_3->GetYaxis()->SetTitleSize(0.035);
   stackplot_2_stack_3->GetYaxis()->SetTitleOffset(0);
   stackplot_2_stack_3->GetYaxis()->SetTitleFont(42);
   stackplot_2_stack_3->GetZaxis()->SetLabelFont(42);
   stackplot_2_stack_3->GetZaxis()->SetLabelSize(0.035);
   stackplot_2_stack_3->GetZaxis()->SetTitleSize(0.035);
   stackplot_2_stack_3->GetZaxis()->SetTitleFont(42);
   stackplot_2->SetHistogram(stackplot_2_stack_3);
   
   Double_t xAxis22[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_0_stack_1 = new TH1F("weight_2_0_stack_1","",18, xAxis22);
   weight_2_0_stack_1->SetBinContent(17,0.9230577);
   weight_2_0_stack_1->SetBinError(17,0.001072483);
   weight_2_0_stack_1->SetEntries(752715);
   weight_2_0_stack_1->SetFillColor(2);
   weight_2_0_stack_1->SetLineColor(2);
   weight_2_0_stack_1->GetXaxis()->SetLabelFont(42);
   weight_2_0_stack_1->GetXaxis()->SetLabelSize(0.035);
   weight_2_0_stack_1->GetXaxis()->SetTitleSize(0.035);
   weight_2_0_stack_1->GetXaxis()->SetTitleFont(42);
   weight_2_0_stack_1->GetYaxis()->SetLabelFont(42);
   weight_2_0_stack_1->GetYaxis()->SetLabelSize(0.035);
   weight_2_0_stack_1->GetYaxis()->SetTitleSize(0.035);
   weight_2_0_stack_1->GetYaxis()->SetTitleOffset(0);
   weight_2_0_stack_1->GetYaxis()->SetTitleFont(42);
   weight_2_0_stack_1->GetZaxis()->SetLabelFont(42);
   weight_2_0_stack_1->GetZaxis()->SetLabelSize(0.035);
   weight_2_0_stack_1->GetZaxis()->SetTitleSize(0.035);
   weight_2_0_stack_1->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_0_stack_1,"");
   Double_t xAxis23[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_1_stack_2 = new TH1F("weight_2_1_stack_2","",18, xAxis23);
   weight_2_1_stack_2->SetBinContent(15,0.07685681);
   weight_2_1_stack_2->SetBinError(15,2.576377e-05);
   weight_2_1_stack_2->SetEntries(1.333603e+07);
   weight_2_1_stack_2->SetFillColor(3);
   weight_2_1_stack_2->SetLineColor(3);
   weight_2_1_stack_2->GetXaxis()->SetLabelFont(42);
   weight_2_1_stack_2->GetXaxis()->SetLabelSize(0.035);
   weight_2_1_stack_2->GetXaxis()->SetTitleSize(0.035);
   weight_2_1_stack_2->GetXaxis()->SetTitleFont(42);
   weight_2_1_stack_2->GetYaxis()->SetLabelFont(42);
   weight_2_1_stack_2->GetYaxis()->SetLabelSize(0.035);
   weight_2_1_stack_2->GetYaxis()->SetTitleSize(0.035);
   weight_2_1_stack_2->GetYaxis()->SetTitleOffset(0);
   weight_2_1_stack_2->GetYaxis()->SetTitleFont(42);
   weight_2_1_stack_2->GetZaxis()->SetLabelFont(42);
   weight_2_1_stack_2->GetZaxis()->SetLabelSize(0.035);
   weight_2_1_stack_2->GetZaxis()->SetTitleSize(0.035);
   weight_2_1_stack_2->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_1_stack_2,"");
   Double_t xAxis24[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_2_stack_3 = new TH1F("weight_2_2_stack_3","",18, xAxis24);
   weight_2_2_stack_3->SetFillColor(4);
   weight_2_2_stack_3->SetLineColor(4);
   weight_2_2_stack_3->GetXaxis()->SetLabelFont(42);
   weight_2_2_stack_3->GetXaxis()->SetLabelSize(0.035);
   weight_2_2_stack_3->GetXaxis()->SetTitleSize(0.035);
   weight_2_2_stack_3->GetXaxis()->SetTitleFont(42);
   weight_2_2_stack_3->GetYaxis()->SetLabelFont(42);
   weight_2_2_stack_3->GetYaxis()->SetLabelSize(0.035);
   weight_2_2_stack_3->GetYaxis()->SetTitleSize(0.035);
   weight_2_2_stack_3->GetYaxis()->SetTitleOffset(0);
   weight_2_2_stack_3->GetYaxis()->SetTitleFont(42);
   weight_2_2_stack_3->GetZaxis()->SetLabelFont(42);
   weight_2_2_stack_3->GetZaxis()->SetLabelSize(0.035);
   weight_2_2_stack_3->GetZaxis()->SetTitleSize(0.035);
   weight_2_2_stack_3->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_2_stack_3,"");
   Double_t xAxis25[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_3_stack_4 = new TH1F("weight_2_3_stack_4","",18, xAxis25);
   weight_2_3_stack_4->SetBinContent(14,8.528865e-05);
   weight_2_3_stack_4->SetBinError(14,2.286079e-07);
   weight_2_3_stack_4->SetEntries(139007);
   weight_2_3_stack_4->SetFillColor(8);
   weight_2_3_stack_4->SetLineColor(8);
   weight_2_3_stack_4->GetXaxis()->SetLabelFont(42);
   weight_2_3_stack_4->GetXaxis()->SetLabelSize(0.035);
   weight_2_3_stack_4->GetXaxis()->SetTitleSize(0.035);
   weight_2_3_stack_4->GetXaxis()->SetTitleFont(42);
   weight_2_3_stack_4->GetYaxis()->SetLabelFont(42);
   weight_2_3_stack_4->GetYaxis()->SetLabelSize(0.035);
   weight_2_3_stack_4->GetYaxis()->SetTitleSize(0.035);
   weight_2_3_stack_4->GetYaxis()->SetTitleOffset(0);
   weight_2_3_stack_4->GetYaxis()->SetTitleFont(42);
   weight_2_3_stack_4->GetZaxis()->SetLabelFont(42);
   weight_2_3_stack_4->GetZaxis()->SetLabelSize(0.035);
   weight_2_3_stack_4->GetZaxis()->SetTitleSize(0.035);
   weight_2_3_stack_4->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_3_stack_4,"");
   Double_t xAxis26[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_4_stack_5 = new TH1F("weight_2_4_stack_5","",18, xAxis26);
   weight_2_4_stack_5->SetBinContent(11,1.372189e-07);
   weight_2_4_stack_5->SetBinError(11,4.271478e-09);
   weight_2_4_stack_5->SetEntries(1032);
   weight_2_4_stack_5->SetFillColor(32);
   weight_2_4_stack_5->SetLineColor(32);
   weight_2_4_stack_5->GetXaxis()->SetLabelFont(42);
   weight_2_4_stack_5->GetXaxis()->SetLabelSize(0.035);
   weight_2_4_stack_5->GetXaxis()->SetTitleSize(0.035);
   weight_2_4_stack_5->GetXaxis()->SetTitleFont(42);
   weight_2_4_stack_5->GetYaxis()->SetLabelFont(42);
   weight_2_4_stack_5->GetYaxis()->SetLabelSize(0.035);
   weight_2_4_stack_5->GetYaxis()->SetTitleSize(0.035);
   weight_2_4_stack_5->GetYaxis()->SetTitleOffset(0);
   weight_2_4_stack_5->GetYaxis()->SetTitleFont(42);
   weight_2_4_stack_5->GetZaxis()->SetLabelFont(42);
   weight_2_4_stack_5->GetZaxis()->SetLabelSize(0.035);
   weight_2_4_stack_5->GetZaxis()->SetTitleSize(0.035);
   weight_2_4_stack_5->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_4_stack_5,"");
   Double_t xAxis27[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_5_stack_6 = new TH1F("weight_2_5_stack_6","",18, xAxis27);
   weight_2_5_stack_6->SetBinContent(9,7.534226e-11);
   weight_2_5_stack_6->SetBinError(9,2.847669e-11);
   weight_2_5_stack_6->SetEntries(7);
   weight_2_5_stack_6->SetFillColor(38);
   weight_2_5_stack_6->SetLineColor(38);
   weight_2_5_stack_6->GetXaxis()->SetLabelFont(42);
   weight_2_5_stack_6->GetXaxis()->SetLabelSize(0.035);
   weight_2_5_stack_6->GetXaxis()->SetTitleSize(0.035);
   weight_2_5_stack_6->GetXaxis()->SetTitleFont(42);
   weight_2_5_stack_6->GetYaxis()->SetLabelFont(42);
   weight_2_5_stack_6->GetYaxis()->SetLabelSize(0.035);
   weight_2_5_stack_6->GetYaxis()->SetTitleSize(0.035);
   weight_2_5_stack_6->GetYaxis()->SetTitleOffset(0);
   weight_2_5_stack_6->GetYaxis()->SetTitleFont(42);
   weight_2_5_stack_6->GetZaxis()->SetLabelFont(42);
   weight_2_5_stack_6->GetZaxis()->SetLabelSize(0.035);
   weight_2_5_stack_6->GetZaxis()->SetTitleSize(0.035);
   weight_2_5_stack_6->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_5_stack_6,"");
   Double_t xAxis28[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_6_stack_7 = new TH1F("weight_2_6_stack_7","",18, xAxis28);
   weight_2_6_stack_7->SetFillColor(42);
   weight_2_6_stack_7->SetLineColor(42);
   weight_2_6_stack_7->GetXaxis()->SetLabelFont(42);
   weight_2_6_stack_7->GetXaxis()->SetLabelSize(0.035);
   weight_2_6_stack_7->GetXaxis()->SetTitleSize(0.035);
   weight_2_6_stack_7->GetXaxis()->SetTitleFont(42);
   weight_2_6_stack_7->GetYaxis()->SetLabelFont(42);
   weight_2_6_stack_7->GetYaxis()->SetLabelSize(0.035);
   weight_2_6_stack_7->GetYaxis()->SetTitleSize(0.035);
   weight_2_6_stack_7->GetYaxis()->SetTitleOffset(0);
   weight_2_6_stack_7->GetYaxis()->SetTitleFont(42);
   weight_2_6_stack_7->GetZaxis()->SetLabelFont(42);
   weight_2_6_stack_7->GetZaxis()->SetLabelSize(0.035);
   weight_2_6_stack_7->GetZaxis()->SetTitleSize(0.035);
   weight_2_6_stack_7->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_6_stack_7,"");
   Double_t xAxis29[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_7_stack_8 = new TH1F("weight_2_7_stack_8","",18, xAxis29);
   weight_2_7_stack_8->SetFillColor(46);
   weight_2_7_stack_8->SetLineColor(46);
   weight_2_7_stack_8->GetXaxis()->SetLabelFont(42);
   weight_2_7_stack_8->GetXaxis()->SetLabelSize(0.035);
   weight_2_7_stack_8->GetXaxis()->SetTitleSize(0.035);
   weight_2_7_stack_8->GetXaxis()->SetTitleFont(42);
   weight_2_7_stack_8->GetYaxis()->SetLabelFont(42);
   weight_2_7_stack_8->GetYaxis()->SetLabelSize(0.035);
   weight_2_7_stack_8->GetYaxis()->SetTitleSize(0.035);
   weight_2_7_stack_8->GetYaxis()->SetTitleOffset(0);
   weight_2_7_stack_8->GetYaxis()->SetTitleFont(42);
   weight_2_7_stack_8->GetZaxis()->SetLabelFont(42);
   weight_2_7_stack_8->GetZaxis()->SetLabelSize(0.035);
   weight_2_7_stack_8->GetZaxis()->SetTitleSize(0.035);
   weight_2_7_stack_8->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_7_stack_8,"");
   Double_t xAxis30[19] = {0.15, 0.16, 0.35, 0.38, 2.8, 2.9, 6.4, 6.5, 18, 19, 228, 229, 1050, 1051, 12120, 12130, 2000000, 2200000, 2300000}; 
   
   TH1F *weight_2_8_stack_9 = new TH1F("weight_2_8_stack_9","",18, xAxis30);
   weight_2_8_stack_9->SetFillColor(49);
   weight_2_8_stack_9->SetLineColor(49);
   weight_2_8_stack_9->GetXaxis()->SetLabelFont(42);
   weight_2_8_stack_9->GetXaxis()->SetLabelSize(0.035);
   weight_2_8_stack_9->GetXaxis()->SetTitleSize(0.035);
   weight_2_8_stack_9->GetXaxis()->SetTitleFont(42);
   weight_2_8_stack_9->GetYaxis()->SetLabelFont(42);
   weight_2_8_stack_9->GetYaxis()->SetLabelSize(0.035);
   weight_2_8_stack_9->GetYaxis()->SetTitleSize(0.035);
   weight_2_8_stack_9->GetYaxis()->SetTitleOffset(0);
   weight_2_8_stack_9->GetYaxis()->SetTitleFont(42);
   weight_2_8_stack_9->GetZaxis()->SetLabelFont(42);
   weight_2_8_stack_9->GetZaxis()->SetLabelSize(0.035);
   weight_2_8_stack_9->GetZaxis()->SetTitleSize(0.035);
   weight_2_8_stack_9->GetZaxis()->SetTitleFont(42);
   stackplot_2->Add(weight_2_8_stack_9,"");
   stackplot_2->Draw("hist");
   bigCanvas_3->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_4
   TPad *bigCanvas_4 = new TPad("bigCanvas_4", "bigCanvas_4",0.61,0.81,0.79,0.99);
   bigCanvas_4->Draw();
   bigCanvas_4->cd();
   bigCanvas_4->Range(0,0,1,1);
   bigCanvas_4->SetFillColor(0);
   bigCanvas_4->SetBorderMode(0);
   bigCanvas_4->SetBorderSize(2);
   bigCanvas_4->SetFrameBorderMode(0);
   bigCanvas_4->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_5
   TPad *bigCanvas_5 = new TPad("bigCanvas_5", "bigCanvas_5",0.81,0.81,0.99,0.99);
   bigCanvas_5->Draw();
   bigCanvas_5->cd();
   bigCanvas_5->Range(0,0,1,1);
   bigCanvas_5->SetFillColor(0);
   bigCanvas_5->SetBorderMode(0);
   bigCanvas_5->SetBorderSize(2);
   bigCanvas_5->SetFrameBorderMode(0);
   bigCanvas_5->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_6
   TPad *bigCanvas_6 = new TPad("bigCanvas_6", "bigCanvas_6",0.01,0.61,0.19,0.79);
   bigCanvas_6->Draw();
   bigCanvas_6->cd();
   bigCanvas_6->Range(0,0,1,1);
   bigCanvas_6->SetFillColor(0);
   bigCanvas_6->SetBorderMode(0);
   bigCanvas_6->SetBorderSize(2);
   bigCanvas_6->SetFrameBorderMode(0);
   bigCanvas_6->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_7
   TPad *bigCanvas_7 = new TPad("bigCanvas_7", "bigCanvas_7",0.21,0.61,0.39,0.79);
   bigCanvas_7->Draw();
   bigCanvas_7->cd();
   bigCanvas_7->Range(0,0,1,1);
   bigCanvas_7->SetFillColor(0);
   bigCanvas_7->SetBorderMode(0);
   bigCanvas_7->SetBorderSize(2);
   bigCanvas_7->SetFrameBorderMode(0);
   bigCanvas_7->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_8
   TPad *bigCanvas_8 = new TPad("bigCanvas_8", "bigCanvas_8",0.41,0.61,0.59,0.79);
   bigCanvas_8->Draw();
   bigCanvas_8->cd();
   bigCanvas_8->Range(0,0,1,1);
   bigCanvas_8->SetFillColor(0);
   bigCanvas_8->SetBorderMode(0);
   bigCanvas_8->SetBorderSize(2);
   bigCanvas_8->SetFrameBorderMode(0);
   bigCanvas_8->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_9
   TPad *bigCanvas_9 = new TPad("bigCanvas_9", "bigCanvas_9",0.61,0.61,0.79,0.79);
   bigCanvas_9->Draw();
   bigCanvas_9->cd();
   bigCanvas_9->Range(0,0,1,1);
   bigCanvas_9->SetFillColor(0);
   bigCanvas_9->SetBorderMode(0);
   bigCanvas_9->SetBorderSize(2);
   bigCanvas_9->SetFrameBorderMode(0);
   bigCanvas_9->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_10
   TPad *bigCanvas_10 = new TPad("bigCanvas_10", "bigCanvas_10",0.81,0.61,0.99,0.79);
   bigCanvas_10->Draw();
   bigCanvas_10->cd();
   bigCanvas_10->Range(0,0,1,1);
   bigCanvas_10->SetFillColor(0);
   bigCanvas_10->SetBorderMode(0);
   bigCanvas_10->SetBorderSize(2);
   bigCanvas_10->SetFrameBorderMode(0);
   bigCanvas_10->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_11
   TPad *bigCanvas_11 = new TPad("bigCanvas_11", "bigCanvas_11",0.01,0.41,0.19,0.59);
   bigCanvas_11->Draw();
   bigCanvas_11->cd();
   bigCanvas_11->Range(0,0,1,1);
   bigCanvas_11->SetFillColor(0);
   bigCanvas_11->SetBorderMode(0);
   bigCanvas_11->SetBorderSize(2);
   bigCanvas_11->SetFrameBorderMode(0);
   bigCanvas_11->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_12
   TPad *bigCanvas_12 = new TPad("bigCanvas_12", "bigCanvas_12",0.21,0.41,0.39,0.59);
   bigCanvas_12->Draw();
   bigCanvas_12->cd();
   bigCanvas_12->Range(0,0,1,1);
   bigCanvas_12->SetFillColor(0);
   bigCanvas_12->SetBorderMode(0);
   bigCanvas_12->SetBorderSize(2);
   bigCanvas_12->SetFrameBorderMode(0);
   bigCanvas_12->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_13
   TPad *bigCanvas_13 = new TPad("bigCanvas_13", "bigCanvas_13",0.41,0.41,0.59,0.59);
   bigCanvas_13->Draw();
   bigCanvas_13->cd();
   bigCanvas_13->Range(0,0,1,1);
   bigCanvas_13->SetFillColor(0);
   bigCanvas_13->SetBorderMode(0);
   bigCanvas_13->SetBorderSize(2);
   bigCanvas_13->SetFrameBorderMode(0);
   bigCanvas_13->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_14
   TPad *bigCanvas_14 = new TPad("bigCanvas_14", "bigCanvas_14",0.61,0.41,0.79,0.59);
   bigCanvas_14->Draw();
   bigCanvas_14->cd();
   bigCanvas_14->Range(0,0,1,1);
   bigCanvas_14->SetFillColor(0);
   bigCanvas_14->SetBorderMode(0);
   bigCanvas_14->SetBorderSize(2);
   bigCanvas_14->SetFrameBorderMode(0);
   bigCanvas_14->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_15
   TPad *bigCanvas_15 = new TPad("bigCanvas_15", "bigCanvas_15",0.81,0.41,0.99,0.59);
   bigCanvas_15->Draw();
   bigCanvas_15->cd();
   bigCanvas_15->Range(0,0,1,1);
   bigCanvas_15->SetFillColor(0);
   bigCanvas_15->SetBorderMode(0);
   bigCanvas_15->SetBorderSize(2);
   bigCanvas_15->SetFrameBorderMode(0);
   bigCanvas_15->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_16
   TPad *bigCanvas_16 = new TPad("bigCanvas_16", "bigCanvas_16",0.01,0.21,0.19,0.39);
   bigCanvas_16->Draw();
   bigCanvas_16->cd();
   bigCanvas_16->Range(0,0,1,1);
   bigCanvas_16->SetFillColor(0);
   bigCanvas_16->SetBorderMode(0);
   bigCanvas_16->SetBorderSize(2);
   bigCanvas_16->SetFrameBorderMode(0);
   bigCanvas_16->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_17
   TPad *bigCanvas_17 = new TPad("bigCanvas_17", "bigCanvas_17",0.21,0.21,0.39,0.39);
   bigCanvas_17->Draw();
   bigCanvas_17->cd();
   bigCanvas_17->Range(0,0,1,1);
   bigCanvas_17->SetFillColor(0);
   bigCanvas_17->SetBorderMode(0);
   bigCanvas_17->SetBorderSize(2);
   bigCanvas_17->SetFrameBorderMode(0);
   bigCanvas_17->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_18
   TPad *bigCanvas_18 = new TPad("bigCanvas_18", "bigCanvas_18",0.41,0.21,0.59,0.39);
   bigCanvas_18->Draw();
   bigCanvas_18->cd();
   bigCanvas_18->Range(0,0,1,1);
   bigCanvas_18->SetFillColor(0);
   bigCanvas_18->SetBorderMode(0);
   bigCanvas_18->SetBorderSize(2);
   bigCanvas_18->SetFrameBorderMode(0);
   bigCanvas_18->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_19
   TPad *bigCanvas_19 = new TPad("bigCanvas_19", "bigCanvas_19",0.61,0.21,0.79,0.39);
   bigCanvas_19->Draw();
   bigCanvas_19->cd();
   bigCanvas_19->Range(0,0,1,1);
   bigCanvas_19->SetFillColor(0);
   bigCanvas_19->SetBorderMode(0);
   bigCanvas_19->SetBorderSize(2);
   bigCanvas_19->SetFrameBorderMode(0);
   bigCanvas_19->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_20
   TPad *bigCanvas_20 = new TPad("bigCanvas_20", "bigCanvas_20",0.81,0.21,0.99,0.39);
   bigCanvas_20->Draw();
   bigCanvas_20->cd();
   bigCanvas_20->Range(0,0,1,1);
   bigCanvas_20->SetFillColor(0);
   bigCanvas_20->SetBorderMode(0);
   bigCanvas_20->SetBorderSize(2);
   bigCanvas_20->SetFrameBorderMode(0);
   bigCanvas_20->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_21
   TPad *bigCanvas_21 = new TPad("bigCanvas_21", "bigCanvas_21",0.01,0.01,0.19,0.19);
   bigCanvas_21->Draw();
   bigCanvas_21->cd();
   bigCanvas_21->Range(0,0,1,1);
   bigCanvas_21->SetFillColor(0);
   bigCanvas_21->SetBorderMode(0);
   bigCanvas_21->SetBorderSize(2);
   bigCanvas_21->SetFrameBorderMode(0);
   bigCanvas_21->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_22
   TPad *bigCanvas_22 = new TPad("bigCanvas_22", "bigCanvas_22",0.21,0.01,0.39,0.19);
   bigCanvas_22->Draw();
   bigCanvas_22->cd();
   bigCanvas_22->Range(0,0,1,1);
   bigCanvas_22->SetFillColor(0);
   bigCanvas_22->SetBorderMode(0);
   bigCanvas_22->SetBorderSize(2);
   bigCanvas_22->SetFrameBorderMode(0);
   bigCanvas_22->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_23
   TPad *bigCanvas_23 = new TPad("bigCanvas_23", "bigCanvas_23",0.41,0.01,0.59,0.19);
   bigCanvas_23->Draw();
   bigCanvas_23->cd();
   bigCanvas_23->Range(0,0,1,1);
   bigCanvas_23->SetFillColor(0);
   bigCanvas_23->SetBorderMode(0);
   bigCanvas_23->SetBorderSize(2);
   bigCanvas_23->SetFrameBorderMode(0);
   bigCanvas_23->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_24
   TPad *bigCanvas_24 = new TPad("bigCanvas_24", "bigCanvas_24",0.61,0.01,0.79,0.19);
   bigCanvas_24->Draw();
   bigCanvas_24->cd();
   bigCanvas_24->Range(0,0,1,1);
   bigCanvas_24->SetFillColor(0);
   bigCanvas_24->SetBorderMode(0);
   bigCanvas_24->SetBorderSize(2);
   bigCanvas_24->SetFrameBorderMode(0);
   bigCanvas_24->Modified();
   bigCanvas->cd();
  
// ------------>Primitives in pad: bigCanvas_25
   TPad *bigCanvas_25 = new TPad("bigCanvas_25", "bigCanvas_25",0.81,0.01,0.99,0.19);
   bigCanvas_25->Draw();
   bigCanvas_25->cd();
   bigCanvas_25->Range(0,0,1,1);
   bigCanvas_25->SetFillColor(0);
   bigCanvas_25->SetBorderMode(0);
   bigCanvas_25->SetBorderSize(2);
   bigCanvas_25->SetFrameBorderMode(0);
   bigCanvas_25->Modified();
   bigCanvas->cd();
   bigCanvas->Modified();
   bigCanvas->cd();
   bigCanvas->SetSelected(bigCanvas);
}
