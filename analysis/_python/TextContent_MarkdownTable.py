#!/usr/bin/env python2
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
logger=GetLogger(__name__)
FLOAT_DIGIT=6
# note exception need to be specified

class TextContent_MarkdownTable(object):
    def __init__(self):
        self._evtcontent=[]
        self._evtstruct=[]
        self._outformat=None

    def __del__(self):
        pass
    def __iter__(self):
        # only for read in formation.
        index=-1
        while index < len(self._evtcontent):
            recContent_=None
            if index == -1:
                recContent_=self._evtstruct
            else:
                recContent_=self._evtcontent[index]
            logger.debug('generator got : {0}'.format(recContent_))
            print recContent_
            yield self.formattedoutput(recContent_)
            index+=1
    #  def __next__(self):
    #      pass


    def Fill(self, *extcontent):
        if self.checkfillstructure(extcontent):
            self._evtcontent.append(extcontent)
            '''
            if self._outformat:
                self._evtcontent.append(
                        [ strformat % (content) for strformat, content in zip(self._outformat,extcontent) ]
                        )
            else:
                self._evtcontent.append(extcontent)
            '''


    def SetEvtStructure(self, *contents):
        hasInnerStruct_=self.checkevtstructure(contents)
        if hasInnerStruct_:
            self._evtstruct=[ evtstruct for evtstruct,outformat in contents ]
            self._outformat=[ outformat for evtstruct,outformat in contents ]
        else:
            self._evtstruct=[ evtstruct for evtstruct in contents ]
            self._outformat=None


    ##def SetContent(self, content):
    ##    pass #asdf
    def WriteTo(self, newfile):
        for line in iter(self):
            print line
            newfile.write(line+'\n')

    def checkevtstructure(self, extcontent):
        if not isinstance(extcontent, (tuple,list)):
            raise Exception('you need to input a list or tuple to build format in TextContent plugin')
        if len(extcontent)<1:
            raise Exception('Put a VALID structure format!')
        check_=0
        for extC in extcontent:
            if   isinstance(extC, str):                           pass
            elif isinstance(extC, (tuple,list)) and len(extC)==2: check_+=1
            else: raise Exception('Put a VALID inner structure format!')
        if   check_== 0:                return False
        elif check_ == len(extcontent): return True
        else: raise Exception('You need to promise the format in the same expression')

    def checkfillstructure(self, extcontent):
        if len(extcontent) != len(self._evtstruct):
            raise Exception('input content has mismatched length with evtstruct')

    def formattedoutput(self,content,SEPARATOR='|'):
        logger.debug('output format is {0}'.format(self._outformat))
        print self._outformat
        print content
        newcontent=[ self._outformat[idx] % (cont) if self._outformat else str(cont) for idx,cont in enumerate(content) ]
        return SEPARATOR + SEPARATOR.join(newcontent) + SEPARATOR


if __name__ == '__main__':
    from xPhoton.analysis.TextIOMgr import TextIOMgr
    outputcontent=TextContent_MarkdownTable()
    #outputcontent.SetEvtStructure( 'a', 'b' ) # also workable
    outputcontent.SetEvtStructure(
                ('a', '%.3f'),
                ('b', '%s'),
            )
    mycontent=[
            { 'a': 3 , 'b': 5 },
            { 'a': 7 , 'b':10 },
            ]
    for content in mycontent:
        outputcontent.Fill( content['a'], content['b'] )

    textio=TextIOMgr()
    textio.SetContent(outputcontent)
    textio.Export('myrecord.md')

