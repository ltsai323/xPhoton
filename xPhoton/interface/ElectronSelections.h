#include "/home/ltsai/Work/workspaceGammaPlusJet/interface/usefulFuncs.h"
#include <vector>
using namespace std;

std::vector<int> ElectronIDCutBased2015(TreeReader &data, Int_t WP, vector<int> &accepted) {

   accepted.clear();

   Int_t  nEle        = data.GetInt("nEle");
   float* elePt       = data.GetPtrFloat("elePt");
   float* eleSCEta    = data.GetPtrFloat("eleSCEta");
   UShort_t* eleIDbit = (UShort_t*) data.GetPtrShort("eleIDbit");
   std::vector<int> selRes;
   selRes.clear();
   selRes.reserve(nEle);

   for (Int_t i=0; i<nEle; ++i) {
      bool rejected = false;
      selRes.push_back(0);
      int& candRes=selRes.back();
      candRes+=usefulFuncs::SetBoolIntoInt(0);

      if (elePt[i] < 15){ rejected = true; candRes += usefulFuncs::SetBoolIntoInt(1); }
      if (fabs(eleSCEta[i]) > 2.5) { rejected = true; candRes += usefulFuncs::SetBoolIntoInt(2); }

      if (fabs(eleSCEta[i]) > 1.4442 && fabs(eleSCEta[i]) < 1.566) { rejected = true; candRes += usefulFuncs::SetBoolIntoInt(3); }


      if ((eleIDbit[i] >> WP & 1) == 0){ rejected = true; candRes += usefulFuncs::SetBoolIntoInt(4); }


      if ( !rejected )
      {
         accepted.push_back(i);
         candRes+=usefulFuncs::SetBoolIntoInt(5);
      }
   }
   return selRes;
}
