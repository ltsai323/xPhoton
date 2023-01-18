#!/usr/bin/env python2


DATACARD_TEMPLATE='''imax *
jmax *
kmax *
---------------
shapes obs cat_BDT {file_obs} {histname_obs}
shapes sig cat_BDT {file_sig} {histname_sig}
shapes bkg cat_BDT {file_bkg} {histname_bkg}
---------------
bin          cat_BDT
observation  -1
------------------------------
bin          cat_BDT cat_BDT
process      sig     bkg
process      0       1
rate         1       1
--------------------------------
'''
''' "rate" and "observation" using? '''
''' No shape error put '''

class TemplateFactory(object):
    def __init__(self):
        self.datas=()
        self.signs=()
        self.fakes=()
    def SetExp(self, hName, filename):
        self.datas=(hName, filename)
    def SetSig(self, hName, filename):
        self.signs=(hName, filename)
    def SetBkg(self, hName, filename):
        self.fakes=(hName, filename)
    def WriteTo(self,filename):
        with open(filename, 'w') as fout:
            fout.write(
                    DATACARD_TEMPLATE.format(
                        file_obs = self.datas[1],
                        file_sig = self.signs[1],
                        file_bkg = self.fakes[1],
                        histname_obs = self.datas[0],
                        histname_sig = self.signs[0],
                        histname_bkg = self.fakes[0],
                        ) )
            print 'output name : %s' % filename



if __name__ == "__main__":
    out = TemplateFactory()
    out.SetExp( 'hi', 'a.root' )
    out.SetSig( 'hi', 'a.root' )
    out.SetBkg( 'hi', 'a.root' )
    out.WriteTo( 'datacard.txt' )
    
