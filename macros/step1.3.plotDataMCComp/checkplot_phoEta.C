void checkplot_phoEta()
{
//=========Macro generated from canvas: canv/hi
//=========  (Fri Jul 12 14:58:09 2024) by ROOT version 6.22/09
   TCanvas *canv = new TCanvas("canv", "hi",0,0,800,1000);
   canv->SetHighLightColor(2);
   canv->Range(0,0,1,1);
   canv->SetFillColor(0);
   canv->SetBorderMode(0);
   canv->SetBorderSize(2);
   canv->SetLogy();
   canv->SetLeftMargin(0.12);
   canv->SetBottomMargin(0.3);
   canv->SetFrameBorderMode(0);
   TLatex *   tex = new TLatex(0.9,0.92,"36.33 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.136,0.872,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(61);
   tex->SetTextSize(0.075);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.136,0.782,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.057);
   tex->SetLineWidth(2);
   tex->Draw();
  
// ------------>Primitives in pad: upper_pad
   TPad *upper_pad = new TPad("upper_pad", "",0.0025,0.3,0.9975,0.9975);
   upper_pad->Draw();
   upper_pad->cd();
   upper_pad->Range(-3.125,2.819415,3.125,7.057133);
   upper_pad->SetFillColor(0);
   upper_pad->SetBorderMode(0);
   upper_pad->SetBorderSize(2);
   upper_pad->SetLogy();
   upper_pad->SetBottomMargin(0.05);
   upper_pad->SetFrameBorderMode(0);
   upper_pad->SetFrameBorderMode(0);
   
   THStack *hs = new THStack();
   hs->SetName("hs");
   hs->SetTitle("\chi^2/DoF = 1.5");
   hs->SetMaximum(2686836);
   
   TH1F *hs_stack_1 = new TH1F("hs_stack_1","\\chi^2/DoF = 1.5",40,-2.5,2.5);
   hs_stack_1->SetMinimum(1074.734);
   hs_stack_1->SetMaximum(4298938);
   hs_stack_1->SetDirectory(0);
   hs_stack_1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hs_stack_1->SetLineColor(ci);
   hs_stack_1->GetXaxis()->SetRange(1,40);
   hs_stack_1->GetXaxis()->SetLabelFont(42);
   hs_stack_1->GetXaxis()->SetTitleOffset(1);
   hs_stack_1->GetXaxis()->SetTitleFont(42);
   hs_stack_1->GetYaxis()->SetLabelFont(42);
   hs_stack_1->GetYaxis()->SetTitleFont(42);
   hs_stack_1->GetZaxis()->SetLabelFont(42);
   hs_stack_1->GetZaxis()->SetTitleOffset(1);
   hs_stack_1->GetZaxis()->SetTitleFont(42);
   hs->SetHistogram(hs_stack_1);
   
   
   TH1F *phoEta_stack_1 = new TH1F("phoEta_stack_1","recoEta",40,-2.5,2.5);
   phoEta_stack_1->SetBinContent(9,32514.72);
   phoEta_stack_1->SetBinContent(10,46993.23);
   phoEta_stack_1->SetBinContent(11,50442.4);
   phoEta_stack_1->SetBinContent(12,54667.94);
   phoEta_stack_1->SetBinContent(13,43090.22);
   phoEta_stack_1->SetBinContent(14,45140.28);
   phoEta_stack_1->SetBinContent(15,49532.35);
   phoEta_stack_1->SetBinContent(16,47313.98);
   phoEta_stack_1->SetBinContent(17,43516.98);
   phoEta_stack_1->SetBinContent(18,42337.46);
   phoEta_stack_1->SetBinContent(19,45505.92);
   phoEta_stack_1->SetBinContent(20,44537.64);
   phoEta_stack_1->SetBinContent(21,49417.48);
   phoEta_stack_1->SetBinContent(22,46106.45);
   phoEta_stack_1->SetBinContent(23,49136.93);
   phoEta_stack_1->SetBinContent(24,46894.04);
   phoEta_stack_1->SetBinContent(25,46581.75);
   phoEta_stack_1->SetBinContent(26,47931.91);
   phoEta_stack_1->SetBinContent(27,45333.37);
   phoEta_stack_1->SetBinContent(28,46099.29);
   phoEta_stack_1->SetBinContent(29,44823.26);
   phoEta_stack_1->SetBinContent(30,50538.81);
   phoEta_stack_1->SetBinContent(31,48246.61);
   phoEta_stack_1->SetBinContent(32,30773.04);
   phoEta_stack_1->SetBinError(9,2224.12);
   phoEta_stack_1->SetBinError(10,2183.659);
   phoEta_stack_1->SetBinError(11,2544.893);
   phoEta_stack_1->SetBinError(12,3069.11);
   phoEta_stack_1->SetBinError(13,2146.75);
   phoEta_stack_1->SetBinError(14,2389.904);
   phoEta_stack_1->SetBinError(15,2638.372);
   phoEta_stack_1->SetBinError(16,2594.048);
   phoEta_stack_1->SetBinError(17,2413.928);
   phoEta_stack_1->SetBinError(18,2226.226);
   phoEta_stack_1->SetBinError(19,2464.782);
   phoEta_stack_1->SetBinError(20,2370.264);
   phoEta_stack_1->SetBinError(21,2607.954);
   phoEta_stack_1->SetBinError(22,2513.866);
   phoEta_stack_1->SetBinError(23,2702.453);
   phoEta_stack_1->SetBinError(24,2715.828);
   phoEta_stack_1->SetBinError(25,2647.983);
   phoEta_stack_1->SetBinError(26,4179.87);
   phoEta_stack_1->SetBinError(27,2544.598);
   phoEta_stack_1->SetBinError(28,2538.532);
   phoEta_stack_1->SetBinError(29,2424.682);
   phoEta_stack_1->SetBinError(30,2473.943);
   phoEta_stack_1->SetBinError(31,2452.157);
   phoEta_stack_1->SetBinError(32,1998.044);
   phoEta_stack_1->SetEntries(60066);
   phoEta_stack_1->SetFillColor(14);
   phoEta_stack_1->SetLineColor(0);
   phoEta_stack_1->GetXaxis()->SetTitle("phoEta");
   phoEta_stack_1->GetXaxis()->SetLabelFont(42);
   phoEta_stack_1->GetXaxis()->SetTitleOffset(1);
   phoEta_stack_1->GetXaxis()->SetTitleFont(42);
   phoEta_stack_1->GetYaxis()->SetLabelFont(42);
   phoEta_stack_1->GetYaxis()->SetTitleFont(42);
   phoEta_stack_1->GetZaxis()->SetLabelFont(42);
   phoEta_stack_1->GetZaxis()->SetTitleOffset(1);
   phoEta_stack_1->GetZaxis()->SetTitleFont(42);
   hs->Add(phoEta_stack_1,"");
   
   TH1F *phoEta_stack_2 = new TH1F("phoEta_stack_2","recoEta",40,-2.5,2.5);
   phoEta_stack_2->SetBinContent(9,5935.431);
   phoEta_stack_2->SetBinContent(10,10441.95);
   phoEta_stack_2->SetBinContent(11,10377.55);
   phoEta_stack_2->SetBinContent(12,10847.11);
   phoEta_stack_2->SetBinContent(13,10342.27);
   phoEta_stack_2->SetBinContent(14,10112.42);
   phoEta_stack_2->SetBinContent(15,10181.51);
   phoEta_stack_2->SetBinContent(16,10517.56);
   phoEta_stack_2->SetBinContent(17,10146.48);
   phoEta_stack_2->SetBinContent(18,10341.69);
   phoEta_stack_2->SetBinContent(19,10124.4);
   phoEta_stack_2->SetBinContent(20,9985.09);
   phoEta_stack_2->SetBinContent(21,10179.56);
   phoEta_stack_2->SetBinContent(22,10227.27);
   phoEta_stack_2->SetBinContent(23,10489.47);
   phoEta_stack_2->SetBinContent(24,10477.75);
   phoEta_stack_2->SetBinContent(25,10380.48);
   phoEta_stack_2->SetBinContent(26,10764.08);
   phoEta_stack_2->SetBinContent(27,10200.45);
   phoEta_stack_2->SetBinContent(28,10208.85);
   phoEta_stack_2->SetBinContent(29,10303.84);
   phoEta_stack_2->SetBinContent(30,10361.72);
   phoEta_stack_2->SetBinContent(31,10329.86);
   phoEta_stack_2->SetBinContent(32,5369.175);
   phoEta_stack_2->SetBinError(9,107.67);
   phoEta_stack_2->SetBinError(10,154.1218);
   phoEta_stack_2->SetBinError(11,149.4783);
   phoEta_stack_2->SetBinError(12,157.5021);
   phoEta_stack_2->SetBinError(13,147.9899);
   phoEta_stack_2->SetBinError(14,152.167);
   phoEta_stack_2->SetBinError(15,126.913);
   phoEta_stack_2->SetBinError(16,153.4527);
   phoEta_stack_2->SetBinError(17,156.4229);
   phoEta_stack_2->SetBinError(18,146.8782);
   phoEta_stack_2->SetBinError(19,135.8275);
   phoEta_stack_2->SetBinError(20,151.1787);
   phoEta_stack_2->SetBinError(21,149.9199);
   phoEta_stack_2->SetBinError(22,129.7918);
   phoEta_stack_2->SetBinError(23,158.807);
   phoEta_stack_2->SetBinError(24,170.0688);
   phoEta_stack_2->SetBinError(25,135.691);
   phoEta_stack_2->SetBinError(26,178.0303);
   phoEta_stack_2->SetBinError(27,127.1324);
   phoEta_stack_2->SetBinError(28,128.8651);
   phoEta_stack_2->SetBinError(29,139.3494);
   phoEta_stack_2->SetBinError(30,135.5484);
   phoEta_stack_2->SetBinError(31,155.3656);
   phoEta_stack_2->SetBinError(32,103.6135);
   phoEta_stack_2->SetEntries(248743);
   phoEta_stack_2->SetFillColor(46);
   phoEta_stack_2->SetLineColor(0);
   phoEta_stack_2->GetXaxis()->SetTitle("phoEta");
   phoEta_stack_2->GetXaxis()->SetLabelFont(42);
   phoEta_stack_2->GetXaxis()->SetTitleOffset(1);
   phoEta_stack_2->GetXaxis()->SetTitleFont(42);
   phoEta_stack_2->GetYaxis()->SetLabelFont(42);
   phoEta_stack_2->GetYaxis()->SetTitleFont(42);
   phoEta_stack_2->GetZaxis()->SetLabelFont(42);
   phoEta_stack_2->GetZaxis()->SetTitleOffset(1);
   phoEta_stack_2->GetZaxis()->SetTitleFont(42);
   hs->Add(phoEta_stack_2,"");
   hs->Draw("ahist");
   
   TH1F *phoEta__1 = new TH1F("phoEta__1","recoEta",40,-2.5,2.5);
   phoEta__1->SetBinContent(9,32060);
   phoEta__1->SetBinContent(10,58402);
   phoEta__1->SetBinContent(11,59127);
   phoEta__1->SetBinContent(12,59526);
   phoEta__1->SetBinContent(13,57522);
   phoEta__1->SetBinContent(14,55647);
   phoEta__1->SetBinContent(15,58297);
   phoEta__1->SetBinContent(16,58640);
   phoEta__1->SetBinContent(17,56523);
   phoEta__1->SetBinContent(18,57833);
   phoEta__1->SetBinContent(19,57822);
   phoEta__1->SetBinContent(20,57139);
   phoEta__1->SetBinContent(21,57838);
   phoEta__1->SetBinContent(22,58646);
   phoEta__1->SetBinContent(23,59121);
   phoEta__1->SetBinContent(24,56099);
   phoEta__1->SetBinContent(25,57715);
   phoEta__1->SetBinContent(26,58547);
   phoEta__1->SetBinContent(27,56257);
   phoEta__1->SetBinContent(28,56280);
   phoEta__1->SetBinContent(29,58028);
   phoEta__1->SetBinContent(30,58999);
   phoEta__1->SetBinContent(31,58697);
   phoEta__1->SetBinContent(32,31357);
   phoEta__1->SetEntries(1336122);
   phoEta__1->SetLineWidth(2);
   phoEta__1->SetMarkerStyle(34);
   phoEta__1->GetXaxis()->SetTitle("phoEta");
   phoEta__1->GetXaxis()->SetLabelFont(42);
   phoEta__1->GetXaxis()->SetTitleOffset(1);
   phoEta__1->GetXaxis()->SetTitleFont(42);
   phoEta__1->GetYaxis()->SetLabelFont(42);
   phoEta__1->GetYaxis()->SetTitleFont(42);
   phoEta__1->GetZaxis()->SetLabelFont(42);
   phoEta__1->GetZaxis()->SetTitleOffset(1);
   phoEta__1->GetZaxis()->SetTitleFont(42);
   phoEta__1->Draw("AEsame");
   
   TPaveText *pt = new TPaveText(0.4786367,0.94,0.5213633,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("\chi^2/DoF = 1.5");
   pt->Draw();
   upper_pad->Modified();
   canv->cd();
  
// ------------>Primitives in pad: lower_pad
   TPad *lower_pad = new TPad("lower_pad", "",0.0025,0.0025,0.9975,0.3);
   lower_pad->Draw();
   lower_pad->cd();
   lower_pad->Range(-3.125,0.0384615,3.125,1.576923);
   lower_pad->SetFillColor(0);
   lower_pad->SetBorderMode(0);
   lower_pad->SetBorderSize(2);
   lower_pad->SetTopMargin(0.05);
   lower_pad->SetBottomMargin(0.3);
   lower_pad->SetFrameBorderMode(0);
   lower_pad->SetFrameBorderMode(0);
   
   Double_t _fx3001[24] = {
   -1.4375,
   -1.3125,
   -1.1875,
   -1.0625,
   -0.9375,
   -0.8125,
   -0.6875,
   -0.5625,
   -0.4375,
   -0.3125,
   -0.1875,
   -0.0625,
   0.0625,
   0.1875,
   0.3125,
   0.4375,
   0.5625,
   0.6875,
   0.8125,
   0.9375,
   1.0625,
   1.1875,
   1.3125,
   1.4375};
   Double_t _fy3001[24] = {
   1.199318,
   0.9834453,
   1.028632,
   1.100612,
   0.9289053,
   0.9929142,
   1.024304,
   0.9862131,
   0.9494094,
   0.9108839,
   0.9620961,
   0.9542123,
   1.030413,
   0.9605722,
   1.008549,
   1.022688,
   0.9869571,
   1.002545,
   0.987145,
   1.0005,
   0.9500086,
   1.03223,
   0.9979464,
   1.152604};
   Double_t _felx3001[24] = {
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625};
   Double_t _fely3001[24] = {
   0.06973698,
   0.03769396,
   0.04330927,
   0.05180424,
   0.03759853,
   0.04322595,
   0.04549267,
   0.04448554,
   0.04296752,
   0.03875129,
   0.04286435,
   0.04174435,
   0.04535294,
   0.04309033,
   0.04596067,
   0.04867924,
   0.04610677,
   0.07151676,
   0.04546254,
   0.04534412,
   0.04202505,
   0.0421973,
   0.04204976,
   0.06410215};
   Double_t _fehx3001[24] = {
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625,
   0.0625};
   Double_t _fehy3001[24] = {
   0.07391719,
   0.03916783,
   0.04517307,
   0.05430284,
   0.03915275,
   0.04515083,
   0.04756027,
   0.0465397,
   0.04495834,
   0.04043671,
   0.04481877,
   0.04361254,
   0.04739526,
   0.04506885,
   0.04810526,
   0.0510543,
   0.04831354,
   0.07681121,
   0.04760696,
   0.04744812,
   0.04392728,
   0.04395936,
   0.0438608,
   0.06777251};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(24,_fx3001,_fy3001,_felx3001,_fehx3001,_fely3001,_fehy3001);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillStyle(1000);
   
   TH1F *Graph_Graph3001 = new TH1F("Graph_Graph3001","",100,-2.5,2.5);
   Graph_Graph3001->SetMinimum(0.5);
   Graph_Graph3001->SetMaximum(1.5);
   Graph_Graph3001->SetDirectory(0);
   Graph_Graph3001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph3001->SetLineColor(ci);
   Graph_Graph3001->GetXaxis()->SetTitle("aasdfasdlf");
   Graph_Graph3001->GetXaxis()->SetRange(1,100);
   Graph_Graph3001->GetXaxis()->SetLabelFont(42);
   Graph_Graph3001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph3001->GetXaxis()->SetTitleFont(42);
   Graph_Graph3001->GetYaxis()->SetLabelFont(42);
   Graph_Graph3001->GetYaxis()->SetTitleFont(42);
   Graph_Graph3001->GetZaxis()->SetLabelFont(42);
   Graph_Graph3001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3001);
   
   grae->Draw("iaap");
   TLine *line = new TLine(-2.5,0.7,2.5,0.7);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(-2.5,1,2.5,1);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(-2.5,1.3,2.5,1.3);
   line->SetLineStyle(2);
   line->Draw();
   lower_pad->Modified();
   canv->cd();
  
// ------------>Primitives in pad: top_pad
   TPad *top_pad = new TPad("top_pad", "",0.0025,0.0025,0.9975,0.9975);
   top_pad->Draw();
   top_pad->cd();
   top_pad->Range(0,0,1,1);
   top_pad->SetFillColor(0);
   top_pad->SetFillStyle(4000);
   top_pad->SetBorderMode(0);
   top_pad->SetBorderSize(2);
   top_pad->SetFrameBorderMode(0);
   TGaxis *gaxis = new TGaxis(0.1,0.335,0.9,0.335,-2.5,2.5,510,"+U");
   gaxis->SetLabelOffset(0.005);
   gaxis->SetLabelSize(0);
   gaxis->SetTickSize(0.03);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(1);
   gaxis->SetTitleSize(0.035);
   gaxis->SetTitleColor(1);
   gaxis->SetTitleFont(42);
   gaxis->SetLabelFont(42);
   gaxis->Draw();
   gaxis = new TGaxis(0.1,0.335,0.1,0.93,1074.734,4298938,510,"SG");
   gaxis->SetLabelOffset(0.005);
   gaxis->SetLabelSize(0.035);
   gaxis->SetTickSize(0.03);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(0);
   gaxis->SetTitleSize(0.035);
   gaxis->SetTitleColor(1);
   gaxis->SetTitleFont(42);
   gaxis->SetLabelFont(42);
   gaxis->Draw();
   gaxis = new TGaxis(0.1,0.09000001,0.9,0.09000001,-2.5,2.5,510,"+S");
   gaxis->SetLabelOffset(0.005);
   gaxis->SetLabelSize(0.035);
   gaxis->SetTickSize(0.03);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(1);
   gaxis->SetTitleSize(0.035);
   gaxis->SetTitleColor(1);
   gaxis->SetTitleFont(42);
   gaxis->SetLabelFont(42);
   gaxis->Draw();
   gaxis = new TGaxis(0.1,0.09000001,0.1,0.285,0.5,1.5,505,"-S");
   gaxis->SetLabelOffset(0.005);
   gaxis->SetLabelSize(0.035);
   gaxis->SetTickSize(0.09153846);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(0);
   gaxis->SetTitleSize(0.035);
   gaxis->SetTitleColor(1);
   gaxis->SetTitleFont(42);
   gaxis->SetLabelFont(42);
   gaxis->Draw();
   top_pad->Modified();
   canv->cd();
//Primitive: TRatioPlot/A ratio of histograms. You must implement TRatioPlot::SavePrimitive
   
   TLegend *leg = new TLegend(0.15,0.8,0.95,0.9,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(ci);
   leg->SetFillStyle(4000);
   TLegendEntry *entry=leg->AddEntry("NULL","k-factor 2.438","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("phoEta","data","p");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(34);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("phoEta_stack_2","signal","f");
   entry->SetFillColor(46);
   entry->SetFillStyle(1001);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("phoEta_stack_1","QCD","f");
   entry->SetFillColor(14);
   entry->SetFillStyle(1001);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   canv->Modified();
   canv->cd();
   canv->SetSelected(canv);
}
