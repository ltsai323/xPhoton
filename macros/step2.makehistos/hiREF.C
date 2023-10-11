void hi()
{
//=========Macro generated from canvas: c1/
//=========  (Thu Aug 10 15:39:35 2023) by ROOT version 6.22/09
   TCanvas *c1 = new TCanvas("c1", "",0,0,800,900);
   c1->SetHighLightColor(2);
   c1->Range(0,0,1,1);
   c1->SetFillColor(0);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetLogy();
   c1->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: upperpad
   TPad *upperpad = new TPad("upperpad", "upperpad",0,0.245,1,0.98);
   upperpad->Draw();
   upperpad->cd();
   upperpad->Range(-1.335404,-11185.63,1.149068,577531.9);
   upperpad->SetFillColor(0);
   upperpad->SetBorderMode(0);
   upperpad->SetBorderSize(2);
   upperpad->SetTickx(1);
   upperpad->SetTicky(1);
   upperpad->SetLeftMargin(0.135);
   upperpad->SetRightMargin(0.06);
   upperpad->SetTopMargin(0.05);
   upperpad->SetBottomMargin(0.019);
   upperpad->SetFrameBorderMode(0);
   upperpad->SetFrameBorderMode(0);
   
   THStack *hs = new THStack();
   hs->SetName("hs");
   hs->SetTitle("");
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","",10,-1,1);
   hs_stack_1->SetMinimum(0);
   hs_stack_1->SetMaximum(548096);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_1->SetLineColor(ci);
   hs_stack_1->GetXaxis()->SetTitle("BDT score");
   hs_stack_1->GetXaxis()->SetLabelFont(42);
   hs_stack_1->GetXaxis()->SetLabelSize(0.03);
   hs_stack_1->GetXaxis()->SetTitleSize(0.05);
   hs_stack_1->GetXaxis()->SetTitleOffset(1);
   hs_stack_1->GetXaxis()->SetTitleFont(42);
   hs_stack_1->GetYaxis()->SetTitle("Entries / 0.2");
   hs_stack_1->GetYaxis()->SetNdivisions(905);
   hs_stack_1->GetYaxis()->SetLabelFont(42);
   hs_stack_1->GetYaxis()->SetLabelSize(0.03);
   hs_stack_1->GetYaxis()->SetTitleSize(0.04);
   hs_stack_1->GetYaxis()->SetTitleOffset(0.8);
   hs_stack_1->GetYaxis()->SetTitleFont(42);
   hs_stack_1->GetZaxis()->SetLabelFont(42);
   hs_stack_1->GetZaxis()->SetTitleOffset(1);
   hs_stack_1->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_1);
   
   
   TH1F *BDT_gjet_signalRegion_stack_1 = new TH1F("BDT_gjet_signalRegion_stack_1","calib_mva",10,-1,1);
   BDT_gjet_signalRegion_stack_1->SetBinContent(1,393.3437);
   BDT_gjet_signalRegion_stack_1->SetBinContent(2,1017.263);
   BDT_gjet_signalRegion_stack_1->SetBinContent(3,2726.268);
   BDT_gjet_signalRegion_stack_1->SetBinContent(4,5330.255);
   BDT_gjet_signalRegion_stack_1->SetBinContent(5,10579.04);
   BDT_gjet_signalRegion_stack_1->SetBinContent(6,20179.88);
   BDT_gjet_signalRegion_stack_1->SetBinContent(7,41397.64);
   BDT_gjet_signalRegion_stack_1->SetBinContent(8,72058.24);
   BDT_gjet_signalRegion_stack_1->SetBinContent(9,85371.77);
   BDT_gjet_signalRegion_stack_1->SetBinContent(10,54079.27);
   BDT_gjet_signalRegion_stack_1->SetBinError(1,30.50794);
   BDT_gjet_signalRegion_stack_1->SetBinError(2,38.16755);
   BDT_gjet_signalRegion_stack_1->SetBinError(3,63.99921);
   BDT_gjet_signalRegion_stack_1->SetBinError(4,75.44685);
   BDT_gjet_signalRegion_stack_1->SetBinError(5,138.2189);
   BDT_gjet_signalRegion_stack_1->SetBinError(6,177.179);
   BDT_gjet_signalRegion_stack_1->SetBinError(7,256.9881);
   BDT_gjet_signalRegion_stack_1->SetBinError(8,353.305);
   BDT_gjet_signalRegion_stack_1->SetBinError(9,368.8372);
   BDT_gjet_signalRegion_stack_1->SetBinError(10,294.8078);
   BDT_gjet_signalRegion_stack_1->SetEntries(336596);
   BDT_gjet_signalRegion_stack_1->SetStats(0);
   BDT_gjet_signalRegion_stack_1->SetFillColor(2);
   BDT_gjet_signalRegion_stack_1->SetLineWidth(2);
   BDT_gjet_signalRegion_stack_1->SetMarkerStyle(33);
   BDT_gjet_signalRegion_stack_1->SetMarkerSize(0);
   BDT_gjet_signalRegion_stack_1->GetXaxis()->SetLabelFont(42);
   BDT_gjet_signalRegion_stack_1->GetXaxis()->SetTitleOffset(1);
   BDT_gjet_signalRegion_stack_1->GetXaxis()->SetTitleFont(42);
   BDT_gjet_signalRegion_stack_1->GetYaxis()->SetLabelFont(42);
   BDT_gjet_signalRegion_stack_1->GetYaxis()->SetTitleFont(42);
   BDT_gjet_signalRegion_stack_1->GetZaxis()->SetLabelFont(42);
   BDT_gjet_signalRegion_stack_1->GetZaxis()->SetTitleOffset(1);
   BDT_gjet_signalRegion_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(BDT_gjet_signalRegion_stack_1,"HIST");
   
   TH1F *BDT_QCD_signalRegion_shapeUncUp_stack_2 = new TH1F("BDT_QCD_signalRegion_shapeUncUp_stack_2","mva",10,-1,1);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(1,5153.915);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(2,7888.031);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(3,20099.95);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(4,42382.25);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(5,60962.53);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(6,99629.4);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(7,222320);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(8,354144);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(9,436624.4);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinContent(10,345658.9);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(1,1487.725);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(2,1788.207);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(3,3820.461);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(4,9603.715);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(5,7898.16);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(6,6902.097);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(7,18677.6);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(8,21497.01);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(9,26679.44);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetBinError(10,28717.74);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetEntries(13611);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetStats(0);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetFillColor(38);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetLineWidth(2);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetMarkerStyle(33);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->SetMarkerSize(0);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->GetXaxis()->SetLabelFont(42);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->GetXaxis()->SetTitleOffset(1);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->GetXaxis()->SetTitleFont(42);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->GetYaxis()->SetLabelFont(42);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->GetYaxis()->SetTitleFont(42);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->GetZaxis()->SetLabelFont(42);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->GetZaxis()->SetTitleOffset(1);
   BDT_QCD_signalRegion_shapeUncUp_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(BDT_QCD_signalRegion_shapeUncUp_stack_2,"HIST");
   hs->Draw("");
   
   TH1F *BDT_data_signalRegion__1 = new TH1F("BDT_data_signalRegion__1","mva",10,-1,1);
   BDT_data_signalRegion__1->SetBinContent(1,82024);
   BDT_data_signalRegion__1->SetBinContent(2,30712);
   BDT_data_signalRegion__1->SetBinContent(3,31398);
   BDT_data_signalRegion__1->SetBinContent(4,39972);
   BDT_data_signalRegion__1->SetBinContent(5,57440);
   BDT_data_signalRegion__1->SetBinContent(6,93780);
   BDT_data_signalRegion__1->SetBinContent(7,170934);
   BDT_data_signalRegion__1->SetBinContent(8,287587);
   BDT_data_signalRegion__1->SetBinContent(9,355738);
   BDT_data_signalRegion__1->SetBinContent(10,194192);
   BDT_data_signalRegion__1->SetBinError(1,286.3983);
   BDT_data_signalRegion__1->SetBinError(2,175.2484);
   BDT_data_signalRegion__1->SetBinError(3,177.1948);
   BDT_data_signalRegion__1->SetBinError(4,199.93);
   BDT_data_signalRegion__1->SetBinError(5,239.6664);
   BDT_data_signalRegion__1->SetBinError(6,306.2352);
   BDT_data_signalRegion__1->SetBinError(7,413.4417);
   BDT_data_signalRegion__1->SetBinError(8,536.2714);
   BDT_data_signalRegion__1->SetBinError(9,596.4378);
   BDT_data_signalRegion__1->SetBinError(10,440.6722);
   BDT_data_signalRegion__1->SetEntries(1343777);
   BDT_data_signalRegion__1->SetStats(0);
   BDT_data_signalRegion__1->SetFillStyle(1);
   BDT_data_signalRegion__1->SetLineColor(2);
   BDT_data_signalRegion__1->SetLineWidth(0);
   BDT_data_signalRegion__1->SetMarkerStyle(33);
   BDT_data_signalRegion__1->SetMarkerSize(4);
   BDT_data_signalRegion__1->GetXaxis()->SetLabelFont(42);
   BDT_data_signalRegion__1->GetXaxis()->SetTitleOffset(1);
   BDT_data_signalRegion__1->GetXaxis()->SetTitleFont(42);
   BDT_data_signalRegion__1->GetYaxis()->SetLabelFont(42);
   BDT_data_signalRegion__1->GetYaxis()->SetTitleFont(42);
   BDT_data_signalRegion__1->GetZaxis()->SetLabelFont(42);
   BDT_data_signalRegion__1->GetZaxis()->SetTitleOffset(1);
   BDT_data_signalRegion__1->GetZaxis()->SetTitleFont(42);
   BDT_data_signalRegion__1->Draw("E0 P SAME");
   upperpad->Modified();
   c1->cd();
  
// ------------>Primitives in pad: lowerpad
   TPad *lowerpad = new TPad("lowerpad", "lowerpad",0,0,1,0.258);
   lowerpad->Draw();
   lowerpad->cd();
   lowerpad->Range(0,0,1,1);
   lowerpad->SetFillColor(0);
   lowerpad->SetBorderMode(0);
   lowerpad->SetBorderSize(2);
   lowerpad->SetTickx(1);
   lowerpad->SetTicky(1);
   lowerpad->SetLeftMargin(0.135);
   lowerpad->SetRightMargin(0.06);
   lowerpad->SetTopMargin(0);
   lowerpad->SetBottomMargin(0.35);
   lowerpad->SetFrameBorderMode(0);
   lowerpad->Modified();
   c1->cd();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
void hiREF()
{ hi(); }
