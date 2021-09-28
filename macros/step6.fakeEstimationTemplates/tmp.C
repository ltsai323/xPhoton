// sig
        sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
        printf(hname);
        //if(ebee==1 && jetbin==1 && ptbin==21)     sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, 20);
        //hsig=(TH1F*)ff->Get(hname);
        hsig=(TH1F*)fhisto_sig->Get(hname);

        // bkg
        sprintf(hname,"data_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
        if(ptbin >=20) sprintf(hname,"data_%d_%d_%d_px2_chIso",ebee, jetbin, 19);
        hbkg=(TH1F*)ff->Get(hname);      

        // data Use px1 only
    TH1F *hEGdata;
    {
        sprintf(hname,"data_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
        hEGdata=(TH1F*)ff->Get(hname);
    }


{ // negtive value is not allowed.
    hsig->Rebin(10);
    hbkg->Rebin(10);
    hEGdata->Rebin(10);
    if(fit_data==0 || fit_data==5){  
        hsig_toymc->Rebin(10);
        hbkg_toymc->Rebin(10);
    }

    //----------------------------------------------------------------------------  
    //not allowing negative contribution
    for(int ibin=0; ibin<hbkg->GetNbinsX(); ibin++){
        if(hbkg->GetBinContent(ibin+1)<1e-6){
            printf("set bkg bin %d, content %f to 0. \n", ibin+1, hbkg->GetBinContent(ibin+1));
            hbkg->SetBinContent(ibin+1,1e-6);
        }
        if(hsig->GetBinContent(ibin+1)<1e-6){
            printf("set sig bin %d, content %f to 0. \n", ibin+1, hsig->GetBinContent(ibin+1));
            hsig->SetBinContent(ibin+1,1e-6);
        }
    }

    //adding systematcis error on template
    for(int ibin=0; ibin<hbkg->GetNbinsX(); ibin++){
        float tmperr = 0.04*0.04;
        if(ebee==1) tmperr = 0.06*0.06;
        tmperr += hbkg->GetBinError(ibin+1)/hbkg->GetBinContent(ibin+1)*hbkg->GetBinError(ibin+1)/hbkg->GetBinContent(ibin+1);
        tmperr = TMath::Sqrt(tmperr)*hbkg->GetBinContent(ibin+1);
        //printf("ibin %d, err %f, new err %f \n", ibin, hbkg->GetBinError(ibin+1), tmperr);    
        if(hbkg->GetBinContent(ibin+1)>0.) hbkg->SetBinError(ibin+1, tmperr);
    }

}
