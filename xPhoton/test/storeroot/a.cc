{
    TFile* fin = TFile::Open("crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root");
    auto lists = fin->GetListOfKeys();
    for ( int i=0; i<lists->GetSize(); ++i )
    {
        auto obj = lists->At(i);
        if ( std::string(obj->GetName()) == "t" ) std::cout << "shit!\n";
    }
}
