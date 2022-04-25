#ifndef __DrawYield_h__
#define __DrawYield_h__
struct NewHistInSquareMatrix // This is a virtual class that cannot be directly used.
{
    NewHistInSquareMatrix( const char* nameTemplate, std::vector<int> maxIdxs ) :
        _nTemplate(nameTemplate), _MIdxs(maxIdxs) {}
    const std::vector<unsigned> DecodeIdx(unsigned idx) const
    {
        std::vector<unsigned> outputidxs;
        for ( unsigned int i = 0; i < _MIdxs.size(); ++i )
        {
            int lPosition = IdxMultiplier(i);
            int rPosition = IdxMultiplier(i+1);
            outputidxs.emplace_back( (idx%lPosition) / rPosition );
        }
        /*
        std::cout << " input digit : " << idx << ". And outputs are ";
        for  ( auto k : outputidxs ) std::cout << k << ", ";
        std::cout << std::endl;
        */
        return outputidxs;
    }
    const char* GetTitle( const std::vector<unsigned int>& iI ) const
    {
        switch ( _MIdxs.size() ) {
        case 0: throw "histogram failed to interpret\n"; return "";
        case 1: return Form(_nTemplate, iI[0]);
        case 2: return Form(_nTemplate, iI[0], iI[1]);
        case 3: return Form(_nTemplate, iI[0], iI[1], iI[2]);
        case 4: return Form(_nTemplate, iI[0], iI[1], iI[2], iI[3]);
        case 5: return Form(_nTemplate, iI[0], iI[1], iI[2], iI[3], iI[4]);
        case 6: return Form(_nTemplate, iI[0], iI[1], iI[2], iI[3], iI[4], iI[5]);
        case 7: return Form(_nTemplate, iI[0], iI[1], iI[2], iI[3], iI[4], iI[5], iI[6]);
        }
        throw "_MIdxs size exceeds the size provided from GetTitle(), please extend this function\n";
                return "";
    }
    int indexing( const std::vector<int>& inIdxs ) const
    {
        int idx = 0;
        for ( unsigned int i = 0; i < _MIdxs.size(); ++i )
        { idx += inIdxs[i] * IdxMultiplier(i+1); }

        /*
        std::cout << "input idxs : ";
        for ( auto a : inIdxs ) std::cout << a << ", ";
        std::cout << " and final index is : " << idx << std::endl;
        */
        return idx;
    }
    int IdxMultiplier( int fromIdx ) const
    {
        int idxMultiplier = 1;
        for ( unsigned int jdx = fromIdx; jdx < _MIdxs.size(); ++jdx )
            idxMultiplier *= _MIdxs.at(jdx);
        return idxMultiplier;
    }
    int TotalSize() const
    { return IdxMultiplier(0); }

    TDirectory* MakeDirectory( TDirectory* origdir )
    {
        char kk[200];
        int i=0;
        while ( _nTemplate[i] != '\0' )
        {
            char k = _nTemplate[i];
            if ( k == '.' )
            { kk[i] = '\0'; break; }
            kk[i] = k;
            ++i;
        }
        return origdir->mkdir( kk );
    }

    virtual unsigned size() const  = 0;
    //virtual TH1F* at(unsigned i)   = 0;

    std::vector<int> _MIdxs;
    const char* _nTemplate;
    char tmpnaming[200];
};
struct NewHistInSquareMatrix1D : public NewHistInSquareMatrix
{
    NewHistInSquareMatrix1D( const char* nameTemplate, std::vector<int> maxIdxs ) : NewHistInSquareMatrix(nameTemplate,maxIdxs)
    {
        hists.reserve( TotalSize() );
        for ( int i=0; i< TotalSize(); ++i ) hists.emplace_back(nullptr);
    }
    //~NewHistInSquareMatrix1D() { for ( auto h : hists ) delete h; }
    void SetXaxis( int nbin, float xmin, float xmax )
    {
        for ( unsigned int idx = 0; idx < TotalSize(); ++idx )
        {
            //std::cout << "setxaxis00 input idx : " << idx << "\n";
            hists[idx] = new TH1F( GetTitle( DecodeIdx(idx) ), "", nbin, xmin, xmax );
            //std::cout << "setxaxis01 decoded name : " << GetTitle(DecodeIdx(idx)) << "\n";
            //std::cout << "setxaxis011decoded indexes : ";
            //for ( auto v : DecodeIdx(idx) ) std::cout << v << ", ";
            //std::cout << std::endl;
            hists[idx]->Sumw2();
        }
    }
    void SetXaxis( int narr, float* xarr )
    {
        for ( unsigned int idx = 0; idx < TotalSize(); ++idx )
        {
            hists[idx] = new TH1F( GetTitle( DecodeIdx(idx) ), "", narr, xarr );
            hists[idx]->Sumw2();
        }
    }

    TH1F* const Get ( const std::vector<int>& idxs ) const
    { return hists[ indexing(idxs) ]; }
    unsigned size() const  override { return hists.size(); }
    TH1F* const at(unsigned i) const{ return hists.at(i); }
    //TH1F* at(unsigned i) { return hists.at(i); }
    void Write( TDirectory* dir = nullptr )
    { if ( dir != nullptr ) dir->cd(); for ( auto h : hists ) h->Write(); }

//private:
    TH1F* get ( const std::vector<int>& idxs )
    { return hists[ indexing(idxs) ]; }

    std::vector<TH1F*> hists;
};
struct NewHistInSquareMatrix2D : public NewHistInSquareMatrix
{
    NewHistInSquareMatrix2D( const char* nameTemplate, std::vector<int> maxIdxs ) : NewHistInSquareMatrix(nameTemplate,maxIdxs)
    {
        hists.reserve( TotalSize() );
        for ( int i=0; i< TotalSize(); ++i ) hists.emplace_back(nullptr);
    };
    //~NewHistInSquareMatrix2D() { for ( auto h : hists ) delete h; }
    void SetXYaxis( int nbinx, float xmin, float xmax, int nbiny, float ymin, float ymax )
    {
        for ( unsigned int idx = 0; idx < TotalSize(); ++idx )
        {
            hists[idx] = new TH2F( GetTitle( DecodeIdx(idx) ), "", nbinx, xmin, xmax, nbiny, ymin, ymax );
            hists[idx]->Sumw2();
        }
    }
    TH2F* const Get ( const std::vector<int>& idxs ) const
    { return hists[ indexing(idxs) ]; }
    unsigned size() const  override { return hists.size(); }
    //TH2F* const at(unsigned i) const{ return hists.at(i); }
    TH2F* at(unsigned i) { return hists.at(i); }

    void Write( TDirectory* dir = nullptr )
    { if ( dir != nullptr ) dir->cd(); for ( auto h : hists ) h->Write(); }
//private:
    TH2F* get( const std::vector<int>& idxs )
    { return hists[ indexing(idxs) ]; }

    std::vector<TH2F*> hists;
};
#endif
