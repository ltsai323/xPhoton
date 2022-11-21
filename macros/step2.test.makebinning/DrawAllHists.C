void PrintHist(TH1* h)
{
    printf( "1D %30s : mean(%.6f) error(%.6f) integral(%.6f) entries(%f)\n", h->GetName(), h->GetMean(), h->GetMeanError(), h->Integral(), h->GetEntries() );
}
void ShowDirItems(TDirectoryFile* _file0)
{
    TIter next_item( _file0->GetListOfKeys() );
    TKey* key;
    while ( (key = (TKey*) next_item()) )
    {
        TClass* cl = gROOT->GetClass(key->GetClassName());
        if ( cl->InheritsFrom("TDirectoryFile") ) ShowDirItems( (TDirectoryFile*)key->ReadObj() );
        if ( cl->InheritsFrom("TH1") ) PrintHist( (TH1*) key->ReadObj() );
    }
}
void DrawAllHists(const char* ifile)
{
    TFile* inputfile = TFile::Open(ifile);
    ShowDirItems(inputfile);
}
