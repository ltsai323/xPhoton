#!/usr/bin/env python2
import collections
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
logger=GetLogger(__name__)

class TextIOMgr(object):
    def __init__(self):
        self._info=None
        self._importable=None
        self._exportable=None
        self._contentprovider=None

    def __del__(self):
        pass
    def Export(self, filename):
        if self._exportable:
            with open(filename,'w') as F:
                logger.debug('exporting')
                self._contentprovider.WriteTo(F)


    #def Load(self, filename):
    #    pass

    def SetContent(self, content):
        self._contentprovider=content
        self.SetIOStatus( False, True )
    def SetIOStatus(self, importable,exportable):
        self._importable=importable
        self._exportable=exportable
    def CheckIOStatus(self):
        if self._contentprovider == None:
            raise NotImplementedError('%s needs to insert a TextContent module by TextIOMgr.SetContent() function')
        #if self._importable == None:
        #    raise NotImplementedError('import status is not setup. Please check content provider %s' % (type(self._contentprovider)))
        if self._exportable == None:
            raise NotImplementedError('export status is not setup. Please check content provider %s' % (type(self._contentprovider)))
    def exportable(self):
        self.CheckIOStatus()
        return self._exportable
    def GetContents(self):
        return iter(self._contentprovider)

if __name__ == '__main__':
    from xPhoton.analysis.TextContent_MarkdownTable import TextContent_MarkdownTable
    outputcontent=TextContent_MarkdownTable()
    #outputcontent.SetEvtStructure( 'a', 'b' ) # also workable
    outputcontent.SetEvtStructure(
                ('a', '%.3f'),
                ('b', '%s'),
            )
    mycontent=[
            { 'a': 3.23894857 , 'b': 'alsdkjf' },
            { 'a': 7.23894787 , 'b': 'bbbbbbb' },
            ]
    for content in mycontent:
        outputcontent.Fill( content['a'], content['b'] )

    textio=TextIOMgr()
    textio.SetContent(outputcontent)
    textio.Export('myrecord.md')

