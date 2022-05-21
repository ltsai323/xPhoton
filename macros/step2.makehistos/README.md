run.sh : Basic run this code. The output will not be sent into storeroot/
tmprun.sh : If you want to execute run.sh parallelly, you can execute this manually.

fakerun.sh : Process fake sample as data.
fullrun.sh : Process run.sh and send the output into storeroot/ to be used.

created histogram naming :
* "BDT_all/BDT_all.%d_%d_%d_%d",
    * {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2}
* "BDT/BDT.%d_%d_%d_%d",
    * {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2}
* "Pt_all/Pt_all.%d_%d_%d_%d",
    * {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2}
* "Pt/Pt.%d_%d",
    * {NUMBIN_PHOETA,2}
* "Pt_spec/Pt_spec.%d_%d",
    * {NUMBIN_PHOETA,2}
* "IsovsBDT/IsovsBDT.%d_%d_%d_%d_%d",
    * {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR}
* "HLT_ebee/HLT_ebee.%d_bit%d",
    * {NUMBIN_PHOETA,NUMBIT_HLT}
* "HLT_ebee/HLT_ebee.%d_bit%d_pass",
    * {NUMBIN_PHOETA,NUMBIT_HLT}




*   HistMgr2D h_btagDeepCSV_BvsAll_central    
    * "btagDeepCSV.0_0_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_BvsAll_up         
    * "btagDeepCSV.1_0_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_BvsAll_down       
    * "btagDeepCSV.2_0_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_CvsL_central      
    * "btagDeepCSV.0_1_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_CvsL_up           
    * "btagDeepCSV.1_1_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_CvsL_down         
    * "btagDeepCSV.2_1_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_CvsB_central      
    * "btagDeepCSV.0_2_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_CvsB_up           
    * "btagDeepCSV.1_2_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_CvsB_down         
    * "btagDeepCSV.2_2_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_secVtxMass_central
    * "btagDeepCSV.0_3_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_secVtxMass_up     
    * "btagDeepCSV.1_3_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
*   HistMgr2D h_btagDeepCSV_secVtxMass_down   
    * "btagDeepCSV.2_3_%d__%d_%d_%d__%d_%d",
    * {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} 
