run.sh : Basic run this code. The output will not be sent into storeroot/
tmprun.sh : If you want to execute run.sh parallelly, you can execute this manually.

fakerun.sh : Process fake sample as data.
fullrun.sh : Process run.sh and send the output into storeroot/ to be used.

created histogram naming :
    const std::vector< const char* > jetFlvrNames = { "sigma", "alpha", "beta" };
    for(int pEtaIdx=0; pEtaIdx<2; pEtaIdx++)
    for(int pPtIdx=0; pPtIdx<(range of pt); pPtIdx++)
    for(int phoMatchStatIdx=0; phoMatchStatIdx<5; phoMatchStatIdx++)
    for(int jFlvrIdx=0; jFlvrIdx<3; jFlvrIdx++)
    for(int varBTagIdx=0; varBTagIdx<4; varBTagIdx++)
    for(int parityIdx=0; parityIdx<2; parityIdx++)
* Form("h_BDT_all_%d_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho)
* Form("h_BDT_%d_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho)
* Form("h_IsovsBDT_%d_%d_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho,varIsoIdx)
* Form("h_Pt_all_%d_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx,isFakePho)
* Form("h_Pt_spec_%d_%d",pEtaIdx,isFakePho)
* Form("h_Pt_%d_%d",pEtaIdx,isFakePho)
* Form("h_HLT_ebee_%d_bit%d",pEtaIdx,HLTIdx)
* Form("h_HLT_ebee_%d_bit%d_pass",pEtaIdx,HLTIdx)
* Form("h_jettag_%d_%d_%d_%d_%d_%d",pEtaIdx,pPtIdx,phoMatchStatIdx,jFlvrIdx,varBTagIdx,parityIdx)
* Form("h_jettag_%sUp_%d_%d_%d_%d_%d_%d",jetFlvrNames[jFlvrIdx],pEtaIdx,pPtIdx,phoMatchStatIdx,jFlvrIdx,varBTagIdx,parityIdx)
* Form("h_jettag_%sDown_%d_%d_%d_%d_%d_%d",jetFlvrNames[jFlvrIdx],pEtaIdx,pPtIdx,phoMatchStatIdx,jFlvrIdx,varBTagIdx,parityIdx)

