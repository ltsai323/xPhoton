void bfrac_EB()
{
//=========Macro generated from canvas: canv/
//=========  (Sun Aug 21 03:09:26 2022) by ROOT version6.10/09
   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = 4000;
   TCanvas *canv = new TCanvas("canv", "",0,0,1000,1000);
   canv->Range(0,0,1,1);
   canv->SetFillColor(ci);
   canv->SetFillStyle(4000);
   canv->SetBorderMode(0);
   canv->SetBorderSize(2);
   canv->SetFrameFillColor(0);
   canv->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: primarypad
   TPad *primarypad = new TPad("primarypad", "",0,0,1,0.75);
   primarypad->Draw();
   primarypad->cd();
   primarypad->Range(0,0,1,1);
   primarypad->SetFillColor(ci);
   primarypad->SetFillStyle(4000);
   primarypad->SetBorderMode(0);
   primarypad->SetBorderSize(2);
   primarypad->SetFrameFillColor(0);
   primarypad->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: upper_pad
   TPad *upper_pad = new TPad("upper_pad", "",0.001875,0.3,0.998125,0.9975);
   upper_pad->Draw();
   upper_pad->cd();
   upper_pad->Range(-2.5,-0.01176471,22.5,0.2235294);
   upper_pad->SetFillColor(0);
   upper_pad->SetBorderMode(0);
   upper_pad->SetBorderSize(2);
   upper_pad->SetBottomMargin(0.05);
   upper_pad->SetFrameBorderMode(0);
   upper_pad->SetFrameBorderMode(0);
   
   TH1F *all_EB_SR_bFrac_bin__1 = new TH1F("all_EB_SR_bFrac_bin__1","fraction to all_EB_SR_bFrac",20,0,20);
   all_EB_SR_bFrac_bin__1->SetBinContent(1,0.03129014);
   all_EB_SR_bFrac_bin__1->SetBinContent(2,0.05449816);
   all_EB_SR_bFrac_bin__1->SetBinContent(3,0.06635184);
   all_EB_SR_bFrac_bin__1->SetBinContent(4,0.06256354);
   all_EB_SR_bFrac_bin__1->SetBinContent(5,0.06013834);
   all_EB_SR_bFrac_bin__1->SetBinContent(6,0.0410027);
   all_EB_SR_bFrac_bin__1->SetBinContent(7,0.04513074);
   all_EB_SR_bFrac_bin__1->SetBinContent(8,0.05778266);
   all_EB_SR_bFrac_bin__1->SetBinContent(9,0.03632769);
   all_EB_SR_bFrac_bin__1->SetBinContent(10,0.02622349);
   all_EB_SR_bFrac_bin__1->SetBinContent(11,0.05593386);
   all_EB_SR_bFrac_bin__1->SetBinContent(12,0.05623705);
   all_EB_SR_bFrac_bin__1->SetBinContent(13,0.01091501);
   all_EB_SR_bFrac_bin__1->SetBinContent(14,0.04944044);
   all_EB_SR_bFrac_bin__1->SetBinContent(15,0.05285723);
   all_EB_SR_bFrac_bin__1->SetBinContent(16,0.05233042);
   all_EB_SR_bFrac_bin__1->SetBinContent(17,0.05269135);
   all_EB_SR_bFrac_bin__1->SetBinContent(18,0.04358242);
   all_EB_SR_bFrac_bin__1->SetBinContent(19,0.04951496);
   all_EB_SR_bFrac_bin__1->SetBinContent(20,0.0455791);
   all_EB_SR_bFrac_bin__1->SetBinContent(21,0.04269563);
   all_EB_SR_bFrac_bin__1->SetBinError(1,0.01638406);
   all_EB_SR_bFrac_bin__1->SetBinError(2,0.01843412);
   all_EB_SR_bFrac_bin__1->SetBinError(3,0.01492331);
   all_EB_SR_bFrac_bin__1->SetBinError(4,0.01198648);
   all_EB_SR_bFrac_bin__1->SetBinError(5,0.005034934);
   all_EB_SR_bFrac_bin__1->SetBinError(6,0.005588467);
   all_EB_SR_bFrac_bin__1->SetBinError(7,0.007857305);
   all_EB_SR_bFrac_bin__1->SetBinError(8,0.009254199);
   all_EB_SR_bFrac_bin__1->SetBinError(9,0.01075951);
   all_EB_SR_bFrac_bin__1->SetBinError(10,0.01034468);
   all_EB_SR_bFrac_bin__1->SetBinError(11,0.003204457);
   all_EB_SR_bFrac_bin__1->SetBinError(12,0.003987605);
   all_EB_SR_bFrac_bin__1->SetBinError(13,0.006209005);
   all_EB_SR_bFrac_bin__1->SetBinError(14,0.002651144);
   all_EB_SR_bFrac_bin__1->SetBinError(15,0.002341975);
   all_EB_SR_bFrac_bin__1->SetBinError(16,0.002574146);
   all_EB_SR_bFrac_bin__1->SetBinError(17,0.00167632);
   all_EB_SR_bFrac_bin__1->SetBinError(18,0.004743093);
   all_EB_SR_bFrac_bin__1->SetBinError(19,0.001588815);
   all_EB_SR_bFrac_bin__1->SetBinError(20,0.001900102);
   all_EB_SR_bFrac_bin__1->SetBinError(21,0.002166715);
   all_EB_SR_bFrac_bin__1->SetMinimum(0);
   all_EB_SR_bFrac_bin__1->SetMaximum(0.2);
   all_EB_SR_bFrac_bin__1->SetEntries(21);
   all_EB_SR_bFrac_bin__1->SetStats(0);
   all_EB_SR_bFrac_bin__1->SetLineColor(40);
   all_EB_SR_bFrac_bin__1->SetMarkerColor(40);
   all_EB_SR_bFrac_bin__1->SetMarkerStyle(29);
   all_EB_SR_bFrac_bin__1->SetMarkerSize(0);
   all_EB_SR_bFrac_bin__1->GetXaxis()->SetTitle("jet pt bin");
   all_EB_SR_bFrac_bin__1->GetXaxis()->SetRange(1,20);
   all_EB_SR_bFrac_bin__1->GetXaxis()->SetLabelFont(42);
   all_EB_SR_bFrac_bin__1->GetXaxis()->SetLabelSize(0.035);
   all_EB_SR_bFrac_bin__1->GetXaxis()->SetTitleSize(0.035);
   all_EB_SR_bFrac_bin__1->GetXaxis()->SetTitleFont(42);
   all_EB_SR_bFrac_bin__1->GetYaxis()->SetTitle("b quark fraction in EB");
   all_EB_SR_bFrac_bin__1->GetYaxis()->SetLabelFont(42);
   all_EB_SR_bFrac_bin__1->GetYaxis()->SetLabelSize(0.035);
   all_EB_SR_bFrac_bin__1->GetYaxis()->SetTitleSize(0.035);
   all_EB_SR_bFrac_bin__1->GetYaxis()->SetTitleOffset(0);
   all_EB_SR_bFrac_bin__1->GetYaxis()->SetTitleFont(42);
   all_EB_SR_bFrac_bin__1->GetZaxis()->SetLabelFont(42);
   all_EB_SR_bFrac_bin__1->GetZaxis()->SetLabelSize(0.035);
   all_EB_SR_bFrac_bin__1->GetZaxis()->SetTitleSize(0.035);
   all_EB_SR_bFrac_bin__1->GetZaxis()->SetTitleFont(42);
   all_EB_SR_bFrac_bin__1->Draw("Ahist");
   
   TH1F *all_EB_SB_bFrac_bin__2 = new TH1F("all_EB_SB_bFrac_bin__2","fraction to all_EB_SB_bFrac",20,0,20);
   all_EB_SB_bFrac_bin__2->SetBinContent(1,0.09034526);
   all_EB_SB_bFrac_bin__2->SetBinContent(2,0.08632547);
   all_EB_SB_bFrac_bin__2->SetBinContent(3,0.0605556);
   all_EB_SB_bFrac_bin__2->SetBinContent(4,0.0815186);
   all_EB_SB_bFrac_bin__2->SetBinContent(5,0.0744765);
   all_EB_SB_bFrac_bin__2->SetBinContent(6,0.07404252);
   all_EB_SB_bFrac_bin__2->SetBinContent(7,0.07576111);
   all_EB_SB_bFrac_bin__2->SetBinContent(8,0.05054407);
   all_EB_SB_bFrac_bin__2->SetBinContent(9,0.06325241);
   all_EB_SB_bFrac_bin__2->SetBinContent(10,0.06409301);
   all_EB_SB_bFrac_bin__2->SetBinContent(11,0.0214812);
   all_EB_SB_bFrac_bin__2->SetBinContent(12,0.06147033);
   all_EB_SB_bFrac_bin__2->SetBinContent(13,0.05407986);
   all_EB_SB_bFrac_bin__2->SetBinContent(14,0.05798146);
   all_EB_SB_bFrac_bin__2->SetBinContent(15,0.05724417);
   all_EB_SB_bFrac_bin__2->SetBinContent(16,0.05595386);
   all_EB_SB_bFrac_bin__2->SetBinContent(17,0.05543765);
   all_EB_SB_bFrac_bin__2->SetBinContent(18,0.05313713);
   all_EB_SB_bFrac_bin__2->SetBinContent(19,0.04699022);
   all_EB_SB_bFrac_bin__2->SetBinContent(20,0.04690506);
   all_EB_SB_bFrac_bin__2->SetBinContent(21,0.04465471);
   all_EB_SB_bFrac_bin__2->SetBinError(1,0.03380053);
   all_EB_SB_bFrac_bin__2->SetBinError(2,0.02262756);
   all_EB_SB_bFrac_bin__2->SetBinError(3,0.00786581);
   all_EB_SB_bFrac_bin__2->SetBinError(4,0.008903369);
   all_EB_SB_bFrac_bin__2->SetBinError(5,0.004215618);
   all_EB_SB_bFrac_bin__2->SetBinError(6,0.002661535);
   all_EB_SB_bFrac_bin__2->SetBinError(7,0.00269005);
   all_EB_SB_bFrac_bin__2->SetBinError(8,0.008039045);
   all_EB_SB_bFrac_bin__2->SetBinError(9,0.00172532);
   all_EB_SB_bFrac_bin__2->SetBinError(10,0.001972293);
   all_EB_SB_bFrac_bin__2->SetBinError(11,0.009871081);
   all_EB_SB_bFrac_bin__2->SetBinError(12,0.003201282);
   all_EB_SB_bFrac_bin__2->SetBinError(13,0.002198332);
   all_EB_SB_bFrac_bin__2->SetBinError(14,0.00214907);
   all_EB_SB_bFrac_bin__2->SetBinError(15,0.001490938);
   all_EB_SB_bFrac_bin__2->SetBinError(16,0.001245495);
   all_EB_SB_bFrac_bin__2->SetBinError(17,0.001337778);
   all_EB_SB_bFrac_bin__2->SetBinError(18,0.001248972);
   all_EB_SB_bFrac_bin__2->SetBinError(19,0.001212498);
   all_EB_SB_bFrac_bin__2->SetBinError(20,0.001517442);
   all_EB_SB_bFrac_bin__2->SetBinError(21,0.001869592);
   all_EB_SB_bFrac_bin__2->SetMinimum(0);
   all_EB_SB_bFrac_bin__2->SetMaximum(0.2);
   all_EB_SB_bFrac_bin__2->SetEntries(21);
   all_EB_SB_bFrac_bin__2->SetStats(0);
   all_EB_SB_bFrac_bin__2->SetLineColor(30);
   all_EB_SB_bFrac_bin__2->SetMarkerColor(30);
   all_EB_SB_bFrac_bin__2->SetMarkerStyle(22);
   all_EB_SB_bFrac_bin__2->SetMarkerSize(0);
   all_EB_SB_bFrac_bin__2->GetXaxis()->SetTitle("jet pt bin");
   all_EB_SB_bFrac_bin__2->GetXaxis()->SetLabelFont(42);
   all_EB_SB_bFrac_bin__2->GetXaxis()->SetLabelSize(0.035);
   all_EB_SB_bFrac_bin__2->GetXaxis()->SetTitleSize(0.035);
   all_EB_SB_bFrac_bin__2->GetXaxis()->SetTitleFont(42);
   all_EB_SB_bFrac_bin__2->GetYaxis()->SetTitle("b quark fraction in EB");
   all_EB_SB_bFrac_bin__2->GetYaxis()->SetLabelFont(42);
   all_EB_SB_bFrac_bin__2->GetYaxis()->SetLabelSize(0.035);
   all_EB_SB_bFrac_bin__2->GetYaxis()->SetTitleSize(0.035);
   all_EB_SB_bFrac_bin__2->GetYaxis()->SetTitleOffset(0);
   all_EB_SB_bFrac_bin__2->GetYaxis()->SetTitleFont(42);
   all_EB_SB_bFrac_bin__2->GetZaxis()->SetLabelFont(42);
   all_EB_SB_bFrac_bin__2->GetZaxis()->SetLabelSize(0.035);
   all_EB_SB_bFrac_bin__2->GetZaxis()->SetTitleSize(0.035);
   all_EB_SB_bFrac_bin__2->GetZaxis()->SetTitleFont(42);
   all_EB_SB_bFrac_bin__2->Draw("AEsame");
   
   TPaveText *pt = new TPaveText(0.3141397,0.9336404,0.6858603,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("fraction to all_EB_SR_bFrac");
   pt->Draw();
   upper_pad->Modified();
   primarypad->cd();
  
// ------------>Primitives in pad: lower_pad
   TPad *lower_pad = new TPad("lower_pad", "",0.001875,0.0025,0.998125,0.3);
   lower_pad->Draw();
   lower_pad->cd();
   lower_pad->Range(-2.5,-1.816044,22.5,4.497617);
   lower_pad->SetFillColor(0);
   lower_pad->SetBorderMode(0);
   lower_pad->SetBorderSize(2);
   lower_pad->SetTopMargin(0.05);
   lower_pad->SetBottomMargin(0.3);
   lower_pad->SetFrameBorderMode(0);
   lower_pad->SetFrameBorderMode(0);
   
   Double_t Graph_from_all_EB_SR_bFrac_bin_fx1001[20] = {
   0.5,
   1.5,
   2.5,
   3.5,
   4.5,
   5.5,
   6.5,
   7.5,
   8.5,
   9.5,
   10.5,
   11.5,
   12.5,
   13.5,
   14.5,
   15.5,
   16.5,
   17.5,
   18.5,
   19.5};
   Double_t Graph_from_all_EB_SR_bFrac_bin_fy1001[20] = {
   0.3463395,
   0.6313103,
   1.095718,
   0.7674757,
   0.8074807,
   0.5537724,
   0.5956979,
   1.143213,
   0.5743289,
   0.4091475,
   2.603852,
   0.914865,
   0.2018314,
   0.852694,
   0.9233645,
   0.9352424,
   0.9504613,
   0.8201877,
   1.053729,
   0.9717309};
   Double_t Graph_from_all_EB_SR_bFrac_bin_fex1001[20] = {
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5,
   0.5};
   Double_t Graph_from_all_EB_SR_bFrac_bin_fey1001[20] = {
   0.2228839,
   0.2701543,
   0.2845868,
   0.1692541,
   0.0816051,
   0.0780573,
   0.1058465,
   0.258039,
   0.1708242,
   0.1618914,
   1.20579,
   0.08048724,
   0.1151045,
   0.05558376,
   0.04745692,
   0.0504958,
   0.03795237,
   0.09131945,
   0.04338777,
   0.05127665};
   TGraphErrors *gre = new TGraphErrors(20,Graph_from_all_EB_SR_bFrac_bin_fx1001,Graph_from_all_EB_SR_bFrac_bin_fy1001,Graph_from_all_EB_SR_bFrac_bin_fex1001,Graph_from_all_EB_SR_bFrac_bin_fey1001);
   gre->SetName("Graph_from_all_EB_SR_bFrac_bin");
   gre->SetTitle("");
   gre->SetLineColor(40);
   gre->SetMarkerColor(40);
   gre->SetMarkerStyle(29);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_Graph_from_all_EB_SR_bFrac_bin1001 = new TH1F("Graph_Graph_from_all_EB_SR_bFrac_bin1001","",100,0,20);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->SetMinimum(0.07805413);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->SetMaximum(4.181934);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->SetDirectory(0);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->SetStats(0);

   //Int_t ci;      // for color index setting
   //TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->SetLineColor(ci);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetXaxis()->SetRange(1,100);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetXaxis()->SetLabelFont(42);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetXaxis()->SetLabelSize(0.035);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetXaxis()->SetTitleFont(42);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetYaxis()->SetLabelFont(42);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetYaxis()->SetLabelSize(0.035);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetYaxis()->SetTitleOffset(0);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetYaxis()->SetTitleFont(42);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetZaxis()->SetLabelFont(42);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph_from_all_EB_SR_bFrac_bin1001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_from_all_EB_SR_bFrac_bin1001);
   
   gre->Draw("iaap");
   TLine *line = new TLine(0,0.7,20,0.7);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(0,1,20,1);
   line->SetLineStyle(2);
   line->Draw();
   line = new TLine(0,1.3,20,1.3);
   line->SetLineStyle(2);
   line->Draw();
   lower_pad->Modified();
   primarypad->cd();
  
// ------------>Primitives in pad: top_pad
   TPad *top_pad = new TPad("top_pad", "",0.001875,0.0025,0.998125,0.9975);
   top_pad->Draw();
   top_pad->cd();
   top_pad->Range(0,0,1,1);
   top_pad->SetFillColor(0);
   top_pad->SetFillStyle(4000);
   top_pad->SetBorderMode(0);
   top_pad->SetBorderSize(2);
   top_pad->SetFrameBorderMode(0);
   TGaxis *gaxis = new TGaxis(0.1,0.335,0.9,0.335,0,20,510,"+U");
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
   gaxis = new TGaxis(0.1,0.335,0.1,0.93,0,0.2,510,"S");
   gaxis->SetLabelOffset(0.005);
   gaxis->SetLabelSize(0.035);
   gaxis->SetTickSize(0.03);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(0);
   gaxis->SetTitleSize(0.035);
   gaxis->SetTitleColor(1);
   gaxis->SetTitleFont(42);
   gaxis->SetTitle("b quark fraction in EB");
   gaxis->SetLabelFont(42);
   gaxis->Draw();
   gaxis = new TGaxis(0.1,0.09000001,0.9,0.09000001,0,20,510,"+S");
   gaxis->SetLabelOffset(0.005);
   gaxis->SetLabelSize(0.035);
   gaxis->SetTickSize(0.03);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(1);
   gaxis->SetTitleSize(0.035);
   gaxis->SetTitleColor(1);
   gaxis->SetTitleFont(42);
   gaxis->SetTitle("jet pt bin");
   gaxis->SetLabelFont(42);
   gaxis->Draw();
   gaxis = new TGaxis(0.1,0.09000001,0.1,0.285,0.07805413,4.181934,505,"-S");
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
   primarypad->cd();
//Primitive: TRatioPlot/A ratio of histograms. You must implement TRatioPlot::SavePrimitive
   primarypad->Modified();
   canv->cd();
  
// ------------>Primitives in pad: tlegendpad
   TPad *tlegendpad = new TPad("tlegendpad", "",0,0.75,1,1);
   tlegendpad->Draw();
   tlegendpad->cd();
   tlegendpad->Range(0,0,1,1);
   tlegendpad->SetFillColor(ci);
   tlegendpad->SetFillStyle(4000);
   tlegendpad->SetBorderMode(0);
   tlegendpad->SetBorderSize(2);
   tlegendpad->SetFrameFillColor(0);
   tlegendpad->SetFrameBorderMode(0);
   
   TLegend *leg = new TLegend(0,0,0,0,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("all_EB_SR_bFrac_bin","all MC samples in data sideband","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry=leg->AddEntry("all_EB_SB_bFrac_bin","all MC samples in signal region","lp");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   leg->Draw();
   tlegendpad->Modified();
   canv->cd();
   canv->Modified();
   canv->cd();
   canv->SetSelected(canv);
}
