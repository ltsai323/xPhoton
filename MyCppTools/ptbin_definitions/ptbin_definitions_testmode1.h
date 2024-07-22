#include <vector>
#include <string>

static int testmode = 1;

std::vector<float> ptbin_ranges();
Int_t TriggerBit( const std::string& dataera, Int_t ptbin );


// merge binning for more statistics at each bin {{{
std::vector<float> ptbin_ranges_2016_mergedBin()
{ return std::vector<float>({25,34,56,70,100,115,135,175,190,220,250,300,350,400,500,700}); }  // only 0~15 bins

Int_t TriggerBit_2016_mergedBin(Int_t ptbin)
{
    if ( ptbin == 0 ) return 0;  //  25- 34
    if ( ptbin == 1 ) return 1;  //  34- 56
    if ( ptbin == 2 ) return 3;  //  56- 70
    if ( ptbin == 3 ) return 3;  //  70-100
    if ( ptbin == 4 ) return 5;  // 100-115
    if ( ptbin == 5 ) return 5;  // 115-135
    if ( ptbin == 6 ) return 6;  // 135-175
    if ( ptbin == 7 ) return 6;  // 175-190
    if ( ptbin == 8 ) return 7;  // 190-220
    if ( ptbin == 9 ) return 7;  // 220-250
    if ( ptbin ==10 ) return 7;  // 250-300
    if ( ptbin ==11 ) return 7;  // 300-350
    if ( ptbin ==12 ) return 7;  // 350-400
    if ( ptbin ==13 ) return 8;  // 400-500
    if ( ptbin ==14 ) return 8;  // 500-700
    if ( ptbin ==15 ) return 8;  // 700-inf

    return -1; // nothing
}
// merge binning for more statistics at each bin end }}}
// merge bin 175-190 and 190-220. All they used HLT175 {{{
std::vector<float> ptbin_ranges_2016_mergedBin_test1()
{ return std::vector<float>({25,34,56,70,100,115,135,175,220,250,300,350,400,500,700}); }  // only 0~14 bins

Int_t TriggerBit_2016_mergedBin_test1(Int_t ptbin)
{
    if ( ptbin == 0 ) return 0;  //  25- 34
    if ( ptbin == 1 ) return 1;  //  34- 56
    if ( ptbin == 2 ) return 3;  //  56- 70
    if ( ptbin == 3 ) return 3;  //  70-100
    if ( ptbin == 4 ) return 5;  // 100-115
    if ( ptbin == 5 ) return 5;  // 115-135
    if ( ptbin == 6 ) return 6;  // 135-175
    if ( ptbin == 7 ) return 7;  // 175-220
    if ( ptbin == 8 ) return 7;  // 220-250
    if ( ptbin == 9 ) return 7;  // 250-300
    if ( ptbin ==10 ) return 7;  // 300-350
    if ( ptbin ==11 ) return 7;  // 350-400
    if ( ptbin ==12 ) return 8;  // 400-500
    if ( ptbin ==13 ) return 8;  // 500-700
    if ( ptbin ==14 ) return 8;  // 700-inf

    return -1; // nothing
}
// merge bin 175-190 and 190-220. All they used HLT175 }}}
// merge bin 135-175 and 175-190. All they used HLT120 {{{
std::vector<float> ptbin_ranges_2016_mergedBin_test2()
{ return std::vector<float>({25,34,56,70,100,115,135,190,220,250,300,350,400,500,700}); }  // only 0~14 bins

Int_t TriggerBit_2016_mergedBin_test2(Int_t ptbin)
{
    if ( ptbin == 0 ) return 0;  //  25- 34
    if ( ptbin == 1 ) return 1;  //  34- 56
    if ( ptbin == 2 ) return 3;  //  56- 70
    if ( ptbin == 3 ) return 3;  //  70-100
    if ( ptbin == 4 ) return 5;  // 100-115
    if ( ptbin == 5 ) return 5;  // 115-135
    if ( ptbin == 6 ) return 6;  // 135-190
    if ( ptbin == 7 ) return 7;  // 190-220
    if ( ptbin == 8 ) return 7;  // 220-250
    if ( ptbin == 9 ) return 7;  // 250-300
    if ( ptbin ==10 ) return 7;  // 300-350
    if ( ptbin ==11 ) return 7;  // 350-400
    if ( ptbin ==12 ) return 8;  // 400-500
    if ( ptbin ==13 ) return 8;  // 500-700
    if ( ptbin ==14 ) return 8;  // 700-inf

    return -1; // nothing
}
// merge bin 135-175 and 175-190. All they used HLT120 end }}}
// merge bin 135-175 and 175-190. All they used HLT120 . And merge 190-220-250{{{
std::vector<float> ptbin_ranges_2016_mergedBin_test3()
{ return std::vector<float>({25,34,56,70,100,115,135,190,250,300,350,400,500,700}); }  // only 0~14 bins

Int_t TriggerBit_2016_mergedBin_test3(Int_t ptbin)
{
    if ( ptbin == 0 ) return 0;  //  25- 34
    if ( ptbin == 1 ) return 1;  //  34- 56
    if ( ptbin == 2 ) return 3;  //  56- 70
    if ( ptbin == 3 ) return 3;  //  70-100
    if ( ptbin == 4 ) return 5;  // 100-115
    if ( ptbin == 5 ) return 5;  // 115-135
    if ( ptbin == 6 ) return 6;  // 135-190
    if ( ptbin == 7 ) return 7;  // 190-250
    if ( ptbin == 8 ) return 7;  // 250-300
    if ( ptbin == 9 ) return 7;  // 300-350
    if ( ptbin ==10 ) return 7;  // 350-400
    if ( ptbin ==11 ) return 8;  // 400-500
    if ( ptbin ==12 ) return 8;  // 500-700
    if ( ptbin ==13 ) return 8;  // 700-inf

    return -1; // nothing
}
// merge bin 135-175 and 175-190. All they used HLT120 . And merge 190-220-250 }}}
// 2016 binning {{{
std::vector<float> ptbin_ranges_2016()
{ return std::vector<float>({25,34,40,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000}); } // only bin 0~20. size of vector = 21 // stable version
Int_t TriggerBit_2016(Int_t ptbin)
{
    if ( ptbin == 0 ) return 0;  //  25- 34 -> 25-34
    if ( ptbin == 1 ) return 1;  //  34- 40
    if ( ptbin == 2 ) return 2;  //  40- 55 -> 41-56
    if ( ptbin == 3 ) return 3;  //  55- 70 -> 56-70?
    if ( ptbin == 4 ) return 3;  //  70- 85
    if ( ptbin == 5 ) return 4;  // 85-100
    if ( ptbin == 6 ) return 5;  // 100-115
    if ( ptbin == 7 ) return 5;  // 115-135
    if ( ptbin == 8 ) return 6;  // 135-155
    if ( ptbin == 9 ) return 6;  // 155-175
    if ( ptbin ==10 ) return 6;  // 175-190
    if ( ptbin ==11 ) return 7;  // 190-200
    if ( ptbin ==12 ) return 7;  // 200-220
    if ( ptbin ==13 ) return 7;  // 220-250
    if ( ptbin ==14 ) return 7;  // 250-300
    if ( ptbin ==15 ) return 7;  // 300-350
    if ( ptbin ==16 ) return 7;  // 350-400
    if ( ptbin ==17 ) return 8;  // 400-500 // start to use SinglePho300 
    if ( ptbin ==18 ) return 8;  // 500-750
    if ( ptbin ==19 ) return 8;  // 750-1000
    if ( ptbin ==20 ) return 8;  //1000-1500 -> 1000-inf
    //if ( ptbin ==21 ) return 8;  //1500-2000
    //if ( ptbin ==22 ) return 8;  //2000-3000
    //if ( ptbin ==23 ) return 8;  //3000-10000
    //if ( ptbin ==24 ) return 8;  //10000-inf

    return -1; // nothing
}
// 2016 binning end }}}

// test definition for unprescaled HLT only {{{
std::vector<float> ptbin_ranges_Unprescaled()
{ return std::vector<float>({190,200,220,250,300,350,400,500,750,1000}); } // only bin 0~20. size of vector = 21 // stable version
Int_t TriggerBit_UnPrescaled(Int_t ptbin)
{
    if ( ptbin == 0 ) return 7;  // 190-200
    if ( ptbin == 1 ) return 7;  // 200-220
    if ( ptbin == 2 ) return 7;  // 220-250
    if ( ptbin == 3 ) return 7;  // 250-300
    if ( ptbin == 4 ) return 7;  // 300-350
    if ( ptbin == 5 ) return 7;  // 350-400
    if ( ptbin == 6 ) return 8;  // 400-500 // start to use SinglePho300 
    if ( ptbin == 7 ) return 8;  // 500-750
    if ( ptbin == 8 ) return 8;  // 750-1000
    if ( ptbin == 9 ) return 8;  //1000-1500 -> 1000-inf

    return -1; // nothing
}
// 2016 binning end }}}

std::vector<float> ptbin_ranges()
{
    if ( testmode == -1 ) return ptbin_ranges_2016();
    if ( testmode ==  0 ) return ptbin_ranges_2016_mergedBin();
    if ( testmode ==  1 ) return ptbin_ranges_2016_mergedBin_test1(); // merge 190
    if ( testmode ==  2 ) return ptbin_ranges_2016_mergedBin_test2(); // merge 175
    if ( testmode ==  3 ) return ptbin_ranges_2016_mergedBin_test3();
    return std::vector<float>();
    //return ptbin_ranges_Unprescaled();
}

Int_t TriggerBit( const std::string& dataera, Int_t ptbin){
    // used for ptbin_ranges_2016_mergedBin()
    if ( dataera == "2016ReReco" ||
         dataera == "UL2016PreVFP" ||
         dataera == "UL2016PostVFP" )
    {
        if ( testmode == -1 )return TriggerBit_2016(ptbin);
        if ( testmode ==  0 )return TriggerBit_2016_mergedBin(ptbin);
        if ( testmode ==  1 )return TriggerBit_2016_mergedBin_test1(ptbin); // merge 190
        if ( testmode ==  2 )return TriggerBit_2016_mergedBin_test2(ptbin); // merge 175
        if ( testmode ==  3 )return TriggerBit_2016_mergedBin_test3(ptbin); // merge 175
        //return TriggerBit_UnPrescaled(ptbin);
        return -1;
    }
    if ( dataera == "UL2017" )
    {
        return 0;
    }
    if ( dataera == "UL2018" )
    {
        if ( ptbin == 0 ) return 0;  //  25- 34
        if ( ptbin == 1 ) return 0;  //  34- 40
        if ( ptbin == 2 ) return 0;  //  40- 55
        if ( ptbin == 3 ) return 1;  //  55- 70
        if ( ptbin == 4 ) return 1;  //  70- 85
        if ( ptbin == 5 ) return 2;  // 85-100
        if ( ptbin == 6 ) return 3;  // 100-115
        if ( ptbin == 7 ) return 3;  // 115-135
        if ( ptbin == 8 ) return 4;  // 135-155
        if ( ptbin == 9 ) return 5;  // 155-175
        if ( ptbin ==10 ) return 6;  // 175-190
        if ( ptbin ==11 ) return 6;  // 190-200
        if ( ptbin ==13 ) return 7;  // 200-300
        if ( ptbin ==13 ) return 8;  // 300-350
        if ( ptbin ==14 ) return 8;  // 350-400
        if ( ptbin ==15 ) return 8;  // 400-500
        if ( ptbin ==16 ) return 8;  // 500-750
        if ( ptbin ==17 ) return 8;  // 750-1000
        if ( ptbin ==18 ) return 8;  //1000-1500
        if ( ptbin ==19 ) return 8;  //1500-2000
        if ( ptbin ==20 ) return 8;  //2000-3000
        if ( ptbin ==21 ) return 8;  //3000-10000
        if ( ptbin ==22 ) return 8;  // to inf
    }

    throw "\ninput dataera " + dataera + " not found in the TriggerBit()\n\n";
}
