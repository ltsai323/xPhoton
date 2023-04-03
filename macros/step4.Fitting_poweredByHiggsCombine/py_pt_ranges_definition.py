#!/usr/bin/env python3
def pt_ranges_test_for_merge_bin(dataERA):
    # comes from step2.makehisto ptbin_ranges()
    if dataERA == '2016ReReco' or dataERA == 'UL2016':
        return (25,34,56,70,100,115,135,175,190,220,250,300,350,400,500,700) # bin range = 0~15 (contain 15)

def ptbin_ranges_2016(dataERA):
    # comes from step2.makehisto ptbin_ranges()
    if dataERA == '2016ReReco' or dataERA == 'UL2016':
        return (25,34,40,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000)
