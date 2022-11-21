#define LOG(format, args...)     fprintf(stderr, "---------------------debug-    %s  \n  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)
const int NMCSEP = 9; // QCD madgraph samples are separated into 9 HT slices.
const int NUMBIN = 25;
const int colors[] = {2,46,42,49,32,8,3,4,38};
const int marks[] = {33,34, 26,27,28,30, 24,25};
static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000});
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
int jetptBin_100CUT[NMCSEP] = {7,16,16,18,20,21,22,23,24};
int jetptBin_10CUT[NMCSEP] = {11,20,20,21,22,23,24,24,24};
int jetptBin_tenToMinusFiveCut[NMCSEP] = {10,10,15,17,20,20,22,23,24};

enum quarks { b,c,L, totNum };
