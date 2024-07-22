def DataFrameMgr( treename, filename ):
    import ROOT
    return ROOT.ROOT.Experimental.TDataFrame(treename,filename)
