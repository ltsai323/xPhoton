using namespace std;

void ElectronIDCutBased2015(TreeReader &data, Int_t WP, vector<int> &accepted) {

  accepted.clear();

  Int_t  nEle        = data.GetInt("nEle");
  float* elePt       = data.GetPtrFloat("elePt");
  float* eleSCEta    = data.GetPtrFloat("eleSCEta");
  UShort_t* eleIDbit = (UShort_t*) data.GetPtrShort("eleIDbit");

  for (Int_t i=0; i<nEle; ++i) {

    if (elePt[i] < 15) continue;
    if (fabs(eleSCEta[i]) > 2.5) continue;
    if (fabs(eleSCEta[i]) > 1.4442 && fabs(eleSCEta[i]) < 1.566) continue;

    if ((eleIDbit[i] >> WP & 1) == 0) continue;

    accepted.push_back(i);
  }
    
}
