#include <iostream> 
#include <fstream> 
void pull_info(float mu1=+3130.952, float mu2=+5474.130, float mu3=+37987.613){


  TFile *f = new TFile("postfit.root");

  TH1F *h1[20];
  TH1F *hdata[3];
  char hname[100];
  char fname[100];  
  
  Int_t ci_cyan = TColor::GetFreeColorIndex();
  TColor *color = new TColor(ci_cyan, 0.6275, 0.9255, 0.8471);
  Int_t ci_red = TColor::GetFreeColorIndex();
  TColor *color1 = new TColor(ci_red, 0.9059, 0.1961, 0.1373);    
  Int_t ci_yellow = TColor::GetFreeColorIndex(); 
  TColor *color2 = new TColor(ci_yellow, 0.95804, 0.8902, 0.5569);

  int nalgo=3;

  for(int nn=0; nn<nalgo; nn++){ //tagalgo                                                                                                                               
    sprintf(hname,"cat%d_postfit/data_obs",nn);
    hdata[nn] = (TH1F*)f->Get(hname);
    hdata[nn]->SetMarkerStyle(8);
    hdata[nn]->SetTitle("");
    hdata[nn]->SetMaximum(hdata[nn]->GetMaximum()*1.1);
    hdata[nn]->SetNdivisions(505,"XY");
    hdata[nn]->GetXaxis()->SetLabelOffset(1.);

    sprintf(hname,"cat%d_postfit/bkgL",nn);
    h1[nn*3]=(TH1F*)f->Get(hname);
    h1[nn*3]->SetFillColor(ci_yellow);
    h1[nn*3]->SetLineColor(1);    

    sprintf(hname,"cat%d_postfit/sigC",nn);
    h1[1+nn*3]=(TH1F*)f->Get(hname);
    h1[1+nn*3]->SetFillColor(ci_cyan);
    h1[1+nn*3]->Add(h1[nn*3]);
    h1[1+nn*3]->SetLineColor(1);    

    sprintf(hname,"cat%d_postfit/sigB",nn);
    h1[2+nn*3]=(TH1F*)f->Get(hname);
    h1[2+nn*3]->SetFillColor(ci_red);
    h1[2+nn*3]->Add(h1[1+nn*3]);
    h1[2+nn*3]->SetLineColor(1);    

  }
  
printf("%f, %f, %f \n", h1[0]->Integral(), h1[1]->Integral()-h1[0]->Integral(), h1[2]->Integral()-h1[1]->Integral());
float frac_L = h1[0]->Integral() / h1[2]->Integral();
float frac_C = ( h1[1]->Integral()-h1[0]->Integral() ) / h1[2]->Integral();
float frac_B = ( h1[2]->Integral()-h1[1]->Integral() ) / h1[2]->Integral();

char filename[30]="./frac.dat";

std::fstream file;
    file.open(filename, ios::app);
    if(!file) {
        cout << "*** Open fails: " << filename << endl;
    }

    file << frac_L << " " << frac_C << " " << frac_B << endl;

}
