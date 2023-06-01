#!/usr/bin/env python2

def DrawCutStr_data_PurifyZ():
    return 'electron_tag.chIsoRaw < 2 && electron_tag.recoPt > 33 && recoPt > 22.'
def DrawCutStr_ZmassWindow():
    return 'fabs( Z.recoMass-90 )<20'
def DrawCutStr_EtaRegion(region):
    if   region.lower() == 'endcap':
        return 'fabs(recoSCEta) > 1.4442 && fabs(recoSCEta) < 3.0'
    elif region.lower() == 'barrel':
        return 'fabs(recoSCEta) < 1.4442'
    raise KeyError('DrawCutStr_EtaRegion() : only "barrel" and "endcap" allowed to be inputed')
