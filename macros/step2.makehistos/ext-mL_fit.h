
void fcn(
        Int_t &npar,
        Double_t *gin,
        Double_t &f,
        Double_t *par,
        Int_t iflag);
Int_t ptbin_index(
        float ptbin);
Int_t ptbin_lowedge(
        float ptbin);
Double_t* Ifit(float ptbin=13,
        char EBEE[10]="EB",
        int fit_data=1,
        int jetbin=0);
void pulltest(
        int ptbin=13,
        char EBEE[10]="EB",
        int jetbin=0,
        int sig=400, int bkg=400)
void Draw_yield_treeeff(
        char EBEE[20]="EB",
        int jetbin=0);
void Draw_XS(
        char EBEE[20]="EB",
        int jetbin=0);
