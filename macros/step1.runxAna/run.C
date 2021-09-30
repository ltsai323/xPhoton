#include "TROOT.h"

//void run(int option=1){
//  // gROOT->LoadMacro("xZmmg.C++");
//  // xZmmg(option);
//
//  //gROOT->LoadMacro("xSkim.C+");
//  //gROOT->LoadMacro("xSkim_C.so");
//  // xSkim(option);
//
//  gROOT->LoadMacro("xPhotonHFJet.C++");
//  xPhotonHFJet(option);
//}

//#include "myxPhotonHFJet.C"
//#include "xPhotonHFJet.C"
#include "xPhotonHFJet_subVtxInfo.C"
void run(Char_t fileIn[400],int option=1){
  // gROOT->LoadMacro("xZmmg.C++");
  // xZmmg(option);

  //gROOT->LoadMacro("xSkim.C+");
  //gROOT->LoadMacro("xSkim_C.so");
  // xSkim(option);

    cout << "before\n" ;
  //gROOT->LoadMacro("xPhotonHFJet.C++");
  cout << "end\n";
  xPhotonHFJet(fileIn,option);
}
void tmp(char fname[200], float xs=0.)
{
  TFile *f = new TFile(fname);
  TH1F* h = (TH1F*)f->Get("ggNtuplizer/hEvents");
  printf("fname %s, entries %.2e \n", fname, h->GetBinContent(1)) ;
  printf("weight  %e \n",  xs/h->GetBinContent(1)) ;
}

void tmptmp(){

  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt30to50_25ns.root",   140932000  );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt50to80_25ns.root",   19204300   );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt80to120_25ns.root",  2762530   );  
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt120to170_25ns.root", 471100    );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt170to300_25ns.root", 117276    );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt300to470_25ns.root", 7823      );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt470to600_25ns.root", 648.2     );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt600to800_25ns.root", 186.9     );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt800to1000_25ns.root", 32.293   );	   
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt1000to1400_25ns.root",  9.4183  );	   
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt1400to1800_25ns.root",  0.84265  );	   
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt1800to2400_25ns.root",  0.114943     );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt2400to3200_25ns.root",  0.00682981   );
  tmp("/data6/ggNtuples/V07_04_09_03/job_fall15_qcd_pt3200toInf_25ns.root",   0.000165445  );


// weight  2.842502e+01 
// weight  3.853441e+00 
// weight  7.984742e-01 
// weight  1.362197e-01 
// weight  3.485826e-02 
// weight  2.664843e-03 
// weight  3.345485e-04 
// weight  9.515673e-05 
// weight  1.666980e-05 
// weight  6.333180e-06 
// weight  4.256689e-06 
// weight  5.936893e-07 
// weight  3.512265e-08 
// weight  8.574768e-10 

}
