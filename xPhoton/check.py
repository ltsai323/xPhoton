#!/usr/bin/env python2
import ROOT

fin=ROOT.TFile.Open("/home/ltsai/ReceivedFile/GJet/data/Run2016B_94X.root")
t=fin.Get('t')


canv=ROOT.TCanvas('c1','c1')

t.Draw('jetDeepFlavourTags_b+jetDeepFlavourTags_c+jetDeepFlavourTags_g+jetDeepFlavourTags_lepb+jetDeepFlavourTags_bb+jetDeepFlavourTags_uds')
canv.SaveAs('hitotDeepFlavour.pdf')
t.Draw('jetDeepFlavourTags_b+jetDeepFlavourTags_c+jetDeepFlavourTags_g+jetDeepFlavourTags_lepb+jetDeepFlavourTags_bb+jetDeepFlavourTags_uds',
       'jetDeepFlavourTags_b+jetDeepFlavourTags_c+jetDeepFlavourTags_g+jetDeepFlavourTags_lepb+jetDeepFlavourTags_bb+jetDeepFlavourTags_uds < 0.5')
canv.SaveAs('hitotDeepFlavour_Not1.pdf')

t.Draw('jetDeepCSVDiscriminatorTags_BvsAll+jetDeepCSVDiscriminatorTags_CvsB+jetDeepCSVDiscriminatorTags_CvsL')
canv.SaveAs('hitotDeepCSVDiscriminator.pdf')
t.Draw('                                   jetDeepCSVDiscriminatorTags_CvsB+jetDeepCSVDiscriminatorTags_CvsL',
       '                                   jetDeepCSVDiscriminatorTags_CvsB+jetDeepCSVDiscriminatorTags_CvsL' )
canv.SaveAs('hitotDeepCSVDiscriminator_CvsB_CvsL.pdf')
t.Draw('jetDeepCSVDiscriminatorTags_BvsAll+jetDeepCSVDiscriminatorTags_CvsB+jetDeepCSVDiscriminatorTags_CvsL',
       'jetDeepCSVDiscriminatorTags_BvsAll+jetDeepCSVDiscriminatorTags_CvsB+jetDeepCSVDiscriminatorTags_CvsL > -0.5' )
canv.SaveAs('hitotDeepCSVDiscriminator_0Plus.pdf')
t.Draw('jetDeepCSVDiscriminatorTags_BvsAll+jetDeepCSVDiscriminatorTags_CvsB+jetDeepCSVDiscriminatorTags_CvsL',
       'jetDeepCSVDiscriminatorTags_BvsAll+jetDeepCSVDiscriminatorTags_CvsB+jetDeepCSVDiscriminatorTags_CvsL < 0' )
canv.SaveAs('hitotDeepCSVDiscriminator_0Minus.pdf')


t.Draw('jetDeepCSVTags_b+jetDeepCSVTags_bb+jetDeepCSVTags_c+jetDeepCSVTags_udsg')
canv.SaveAs('hitotDeepCSV.pdf')
t.Draw('jetDeepCSVTags_b+jetDeepCSVTags_bb+jetDeepCSVTags_c+jetDeepCSVTags_udsg',
       'jetDeepCSVTags_b+jetDeepCSVTags_bb+jetDeepCSVTags_c+jetDeepCSVTags_udsg < -0.005')
canv.SaveAs('hitotDeepCSV_0Minus.pdf')
t.Draw('jetDeepCSVTags_b+jetDeepCSVTags_bb+jetDeepCSVTags_c+jetDeepCSVTags_udsg',
       'jetDeepCSVTags_b+jetDeepCSVTags_bb+jetDeepCSVTags_c+jetDeepCSVTags_udsg > 0.005')
canv.SaveAs('hitotDeepCSV_NoMinus.pdf')
