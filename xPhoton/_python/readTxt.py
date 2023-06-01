#!/usr/bin/env python2

import sys
import ROOT

class readTxt(object):
   def __init__(self, filename):
      self.filename=filename
      self.file=open(self.filename,'r')
   def __del__(self):
      self.file.close()
   def __iter__(self):
      self.recData=self.dataParser()
      self.idx=0
      #return iter(self.recData)
      return self
   def __next__(self):
      if self.idx>=len(self.recData): raise StopIteration
      line=self.recData[self.idx]
      self.idx+=1
      return ( float(line[2]),float(line[3]),float(line[4]) )
   next = __next__

   @staticmethod
   def filenameParser(filename):
      sepname=filename.split('/')
      noDir=filename if len(sepname)==1 else sepname[-1]
      splitDotName=noDir.split('/')
      return '.'.join(splitDotName[0:-1]) if len(splitDotName) else noDir
   def dataParser(self):
      if not self.file:raise IOError('{0} not found'.format(self.filename))
      recData=[]
      for line in self.file.readlines():
         loaddata=line.split()
         if len(loaddata)<2: continue
         if loaddata[1] != 'Point': continue
         recData.append(loaddata)
      return recData
   def StoreAsRootFile(self, zMultiplier):
      extraLabel='_zAmplifiered1000' if zMultiplier else ''
      rootname='myrecord_{0}{1}.root'.format( self.filenameParser(self.filename), extraLabel )

      rootfile=ROOT.TFile(rootname, 'recreate')
      rootfile.cd()
      myntuple=ROOT.TNtuple('data','INTT module measurement','x:y:z')

      zmultiplier=1000. if zMultiplier else 1.

      for x,y,z in self:
         myntuple.Fill(x,y,z*zmultiplier)
      myntuple.Write()
      rootfile.Write()
      rootfile.Close()



if __name__ == '__main__':
   import sys
   fname=sys.argv[1]
   zMultiplier1000=sys.argv[2].lower() if len(sys.argv)>2 else False
   if not zMultiplier1000: pass
   elif zMultiplier1000 == 'true':  zMultiplier1000=True
   elif zMultiplier1000 == 'false': zMultiplier1000=False
   else: raise ValueError('You have a wrong input to 2nd argument. The valid argument is true or false')

   print 'z is{0} multiplied by 1000'.format('' if zMultiplier1000 else ' not')


   readObj=readTxt(fname)
   readObj.StoreAsRootFile(zMultiplier1000)
