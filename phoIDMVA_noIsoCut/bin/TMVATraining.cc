// @(#)root/tmva $Id: TMVAnalysis.cxx 38719 2011-04-04 12:22:28Z evt $
/**********************************************************************************
 * Project   : TMVA - a ROOT-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAnalysis                                                 *
 *                                                                                *
 * This executable provides examples for the training and testing of the          *
 * TMVA classifiers.                                                              *
 *                                                                                *
 * As input data is used a toy-MC sample consisting of four Gaussian-distributed  *
 * and linearly correlated input variables.                                       *
 *                                                                                *
 * The methods to be used can be switched on and off by means of booleans.        *
 *                                                                                *
 * Compile and run the example with the following commands                        *
 *                                                                                *
 *    make                                                                        *
 *    ./TMVAnalysis <Methods>                                              *
 *                                                                                *
 * where: <Methods> = "method1 method2"                                           *
 *        are the TMVA classifier names                                           *
 *                                                                                *
 * example:                                                                       *
 *    ./TMVAnalysis Fisher LikelihoodPCA BDT                               *
 *                                                                                *
 * If no method given, a default set is of classifiers is used                    *
 *                                                                                *
 * The output file "TMVA.root" can be analysed with the use of dedicated          *
 * macros (simply say: root -l <../macros/macro.C>), which can be conveniently    *
 * invoked through a GUI launched by the command                                  *
 *                                                                                *
 *    root -l ./TMVAGui.C                                                         *
 **********************************************************************************/

// Switching to ROOT6
// 1. No TMVA::Factory::AddVariable()
//      -> Use TMVA::DataLoader
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMath.h"
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#include "TMVA/DataLoader.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;
 
//Int_t isEndcap=1; //0 for EB ; 1 for EE
//Int_t useIsoVars=0;
//Int_t USESHAPE=1;

// read input data file with ascii format (otherwise ROOT) ?
//Bool_t ReadDataFromAsciiIFormat = kFALSE;

void PrintHelp()
{
    fprintf(stderr, "############### Usage ###############\n");
    fprintf(stderr, "## Input a json file to configure  ##\n");
    fprintf(stderr, "## this file. To check the format, ##\n");
    fprintf(stderr, "## check $CMSSW_BASE/src/xPhoton/  ##\n");
    fprintf(stderr, "## phoIDMVA_noIsoCut/python/       ##\n");
    fprintf(stderr, "## TMVATrainingJsonSample.json     ##\n");
    fprintf(stderr, "#####################################\n");
    throw "";
}
const char* GetJsonFromArg( int argc, char** argv )
{ 
    std::cout << " this code argc = " << argc << std::endl;
    if ( argc != 2 ) PrintHelp();
    // .json checker needed!
    return argv[1];
}
int main( int argc, char** argv )
{
    pt::ptree root;
    pt::read_json(GetJsonFromArg(argc,argv), root);
    bool isEndcap = root.get<bool>("isEndcap", false);
    bool useIsoVars = root.get<bool>("useIsoVars", false);
    bool useShapeVars = root.get<bool>("useShapeVars", true);
    std::vector<std::string> usedAlgorithm;
    for ( pt::ptree::value_type& algo : root.get_child("UsedAlgorithm") )
        usedAlgorithm.emplace_back( algo.second.data() );
    std::string outputtemplate = root.get<std::string>("OutputTemplate", "");
    std::string inputfile = root.get<std::string>("InputFile");


   ROOT::EnableImplicitMT(30);
   printf("Using %d thread for this training\n", ROOT::GetImplicitMTPoolSize() );

   //---------------------------------------------------------------
   // Default MVA methods to be trained + tested
   // List of supported algorithms.
   std::map<std::string,int> Use;

   // --- Cut optimisation
   Use["Cuts"]            = 0;
   Use["CutsD"]           = 0;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   // 
   // --- 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 0;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 0; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
//    Use["PDERS"]           = 0;
//    Use["PDERSD"]          = 0;
//    Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 0;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 0; // k-nearest neighbour method
   //
   // --- Linear Discriminant Analysis
   Use["LD"]              = 0; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 0; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 0; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   //
   // --- Support Vector Machine 
   Use["SVM"]             = 0;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 0; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting 
   // 
   // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 0;
   // ---------------------------------------------------------------

   std::cout << std::endl << "==> Start TMVAnalysis" << std::endl;
   if(isEndcap==0) {
	   std::cout << std::endl << "==>     look for EB photons" << std::endl;
   }else {
           std::cout << std::endl << "==>     look for EE photons" << std::endl;
   }

   // use json file to configure what algorithm needed.
    for ( auto a : usedAlgorithm )
        if ( Use.find( a ) != Use.end() ) Use[a] = 1;




   // --------------------------------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   //TString outfileName( "/data4/rslu/work/TMVA-v4.2.0_2017/TMVA-v4.2.0/summer16_80x/TMVA.root" );
   TString outfileName( Form( (outputtemplate+".root").c_str(), isEndcap?"EE":"EB" ) );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is 
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
//    TMVA::Factory *factory = new TMVA::Factory( "TMVAnalysis", outputFile,
//                                                "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   TMVA::Factory *factory = new TMVA::Factory( "TMVAnalysis", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification" );

   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]
//    factory->AddVariable( "myvar1 := var1+var2", 'F' );
//    factory->AddVariable( "myvar2 := var1-var2", "Expression 2", "", 'F' );
//    factory->AddVariable( "var3",                "Variable 3", "units", 'F' );
//    factory->AddVariable( "var4",                "Variable 4", "units", 'F' );

   //TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   TMVA::DataLoader *dataloader=new TMVA::DataLoader( Form(outputtemplate.c_str(), isEndcap ? "EE":"EB") );
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]

   //mcphoton
   if(useShapeVars == 1){
   dataloader->AddVariable( "r9Full5x5",   'F' );   
     dataloader->AddVariable( "sieieFull5x5",   'F' );   
     dataloader->AddVariable( "sieipFull5x5",   'F' );   
     dataloader->AddVariable( "s4Full5x5",  'F' );   
   }
   dataloader->AddVariable( "rawE",   'F' );   
   if(useShapeVars == 1){
     dataloader->AddVariable( "scEtaWidth",   'F' );   
     dataloader->AddVariable( "scPhiWidth",   'F' );   
   }

   if(isEndcap == 1 && useShapeVars==1 ) {
     dataloader->AddVariable( "esEnergyOverSCRawEnergy",   'F' );   
     dataloader->AddVariable( "esRR",   'F' );   
   }

   //to get corelation matrix
   if(useIsoVars == 1){
     dataloader->AddVariable( "phoIsoRaw",   'F' );   
     dataloader->AddVariable( "chIsoRaw",   'F' );   
     dataloader->AddVariable( "chWorstRaw",   'F' );   
   }
   dataloader->AddVariable( "recoPhi", "recoPhi", "none",   'F' );
   dataloader->AddVariable( "recoSCEta", "recoSCEta", "none",   'F' );   
   dataloader->AddVariable( "rho",  "rho", "GeV", 'F' );




   //TFile* photon = TFile::Open("/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/testing/AllPhoton_SigPythia.root");
   //TFile* photon = TFile::Open("/home/ltsai/Work/github/xPhoton/TMVAenv/ReweightMC/rw_out.root");
   //TFile* photon = TFile::Open("/home/ltsai/Work/github/xPhoton/TMVAenv/ReweightMC/rrr.root");
   TFile* photon = TFile::Open( inputfile.c_str() );
   // --- Register the training and test trees
   
   TTree *tt        = (TTree*)photon->Get("tt");    
   TTree *tfake     = (TTree*)photon->Get("tt");
   
   dataloader->AddSignalTree    ( tt,  1. );      
   dataloader->AddBackgroundTree( tfake,  1.);


   // To give different trees for training and testing, do as follows:
   //    factory->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
   //    factory->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );
   
   // Use the following code instead of the above two or four lines to add signal and background
   // training and test events "by hand"
   // NOTE that in this case one should not give expressions (such as "var1+var2") in the input
   //      variable definition, but simply compute the expression before adding the event
   //
   //     // --- begin ----------------------------------------------------------
   //     std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
   //     Float_t  treevars[4], weight;
   //     
   //     // Signal
   //     for (UInt_t ivar=0; ivar<4; ivar++) signal->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   //     for (UInt_t i=0; i<signal->GetEntries(); i++) {
   //        signal->GetEntry(i);
   //        for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //        // add training and test events; here: first half is training, second is testing
   //        // note that the weight can also be event-wise
   //        if (i < signal->GetEntries()/2.0) factory->AddSignalTrainingEvent( vars, signalWeight );
   //        else                              factory->AddSignalTestEvent    ( vars, signalWeight );
   //     }
   //   
   //     // Background (has event weights)
   //     background->SetBranchAddress( "weight", &weight );
   //     for (UInt_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   //     for (UInt_t i=0; i<background->GetEntries(); i++) {
   //        background->GetEntry(i);
   //        for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //        // add training and test events; here: first half is training, second is testing
   //        // note that the weight can also be event-wise
   //        if (i < background->GetEntries()/2) factory->AddBackgroundTrainingEvent( vars, backgroundWeight*weight );
   //        else                                factory->AddBackgroundTestEvent    ( vars, backgroundWeight*weight );
   //     }
         // --- end ------------------------------------------------------------
   //
   // --- end of tree registration 

   // Set individual event weights (the variables must exist in the original TTree)
   //    for signal    : factory->SetSignalWeightExpression    ("weight1*weight2");
   //    for background: factory->SetBackgroundWeightExpression("weight1*weight2");
      //factory->SetBackgroundWeightExpression("weight");
   // //    for signal    : 
   //    dataloader->SetSignalWeightExpression    ("puwei*mcweight*weight2d");
   // //    for background: 
   //    dataloader->SetBackgroundWeightExpression("puwei*mcweight*weight2d");





   //  use weight2d only due to prevent increase statistics of hight energy particle.
   //    for signal    : 
      dataloader->SetSignalWeightExpression    ("weight2d");
   //    for background: 
      dataloader->SetBackgroundWeightExpression("weight2d");

   // Apply additional cuts on the signal and background samples (can be different)
   
//    TCut mycuts = "mcphoton==1&&TMath::Abs(SCEta)<1.5&&phoEt<30.";
//    TCut mycutb = "mcphoton==0&&TMath::Abs(SCEta)<1.5&&phoEt<30.";

   TCut mycuts = " (isMatched==1||isConverted==1)&&isMatchedEle!=1&&TMath::Abs(recoSCEta)<1.5";
   TCut mycutb = "!(isMatched==1||isConverted==1)&&isMatchedEle!=1&&TMath::Abs(recoSCEta)<1.5";
   if (isEndcap == 1) {
     mycuts =    " (isMatched==1||isConverted==1)&&isMatchedEle!=1&&TMath::Abs(recoSCEta)>1.5";
     mycutb =    "!(isMatched==1||isConverted==1)&&isMatchedEle!=1&&TMath::Abs(recoSCEta)>1.5";
   }

   // for high pt photon
//    mycuts = "isMatched==1&&isMatchedEle==-1&&TMath::Abs(recoEta)<1.5&&recoPt>200.";
//    mycutb = "isMatched!=1&&isMatchedEle==-1&&TMath::Abs(recoEta)<1.5&&recoPt>200.";



   // Tell the factory how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used 
   // for training, and the other half for testing:
   //    factory->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   // To also specify the number of testing events, use:
   //factory->PrepareTrainingAndTestTree( mycuts, mycutb,
   //				"NSigTrain=1962260:NBkgTrain=135000:NSigTest=1962260:NBkgTest=40000:SplitMode=Random:!V" );
   //factory->PrepareTrainingAndTestTree( mycuts, mycutb,
   // 					"nTrain_Signal=1000000:nTrain_Background=1000000:nTest_Signal=1000000:nTest_Background=1000000:SplitMode=Random:SplitSeed=100:NormMode=NumEvents");
   //factory->PrepareTrainingAndTestTree( mycuts, mycutb,
   //"nTrain_Signal=60000:nTrain_Background=80000:nTest_Signal=60000:nTest_Background=80000:SplitMode=Random:SplitSeed=100:NormMode=NumEvents");

   //factory->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Alternate:nTrain_Signal=20000000" );  
   //factory->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Alternate");  
   //factory->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Random:SplitSeed=100" );  
   // factory->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Random:SplitSeed=100:nTrain_Signal=20000000:nTest_Signal=20000000");  //for EB TMVA420 summer16 all vertex

   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb, "SplitMode=Random");
   
   // ---- Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   if (Use["CutsGA"]) {
//      factory->BookMethod( TMVA::Types::kCuts, "CutsGA",
//   			  "H:!V:FitMethod=GA:CutRangeMax[0]=0.3:CutRangeMax[1]=0.011:CutRangeMax[2]=0.25:CutRangeMax[3]=0.1:CutRangeMax[4]=0.015:CutRangeMax[5]=0.06:CutRangeMax[6]=0.2:CutRangeMax[7]=0.2:CutRangeMax[8]=1.0:VarProp=FMin:EffSel:Steps=30:Cycles=3:PopSize=800:SC_steps=5:SC_rate=5:SC_factor=0.95" );

     factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsGA",
  			  "H:!V:FitMethod=GA:CutRangeMax[0]=0.011:CutRangeMax[1]=0.2:CutRangeMax[2]=0.2:CutRangeMax[3]=1.0:VarProp=FMin:EffSel:Steps=30:Cycles=3:PopSize=800:SC_steps=5:SC_rate=5:SC_factor=0.95" );
   }

   // Cut optimisation
   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );
   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );


   if (Use["BDT"]) {
     factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT","!H:!V:NTrees=2000:BoostType=Grad:Shrinkage=0.10:!UseBaggedGrad:nCuts=2000:UseNvars=4:PruneStrength=5:PruneMethod=CostComplexity:MaxDepth=6:NegWeightTreatment=IgnoreNegWeightsInTraining");
   }

   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=1000:BoostType=Grad:Shrinkage=0.10:UseBaggedGrad:GradBaggingFraction=0.5:nCuts=20:NNodesMax=5" );



   // For an example of the category classifier, see: TMVAnalysisCategory

   // For an example of the category classifier usage, see: TMVAnalysisCategory

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can optimize the setting (configuration) of the MVAs using the set of training events

   // factory->OptimizeAllMethods("SigEffAt001","Scan");
   // factory->OptimizeAllMethods("ROCIntegral","GA");

   // --------------------------------------------------------------------------------------------------

   // ---- Now you can tell the factory to train, test, and evaluate the MVAs

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl
             << "==> TMVAnalysis is done!" << std::endl
             << std::endl
             << "==> To view the results, launch the GUI: \"root -l ./TMVAGui.C\"" << std::endl
             << std::endl;

   // Clean up
   delete factory;
   delete dataloader;
}
