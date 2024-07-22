from types import MethodType
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
logging=GetLogger(__name__)

class ImportAddFunc(object):
    def __init__(self):
        self._func=[]
        self._args=[]
        self._execres=[]
        self.iteridx=-99

    def __iter__(self):
        self.iteridx=0
        return self
    def __next__(self):
        if self.iteridx < len(self._func):
            idx=self.iteridx
            self.iteridx+=1
            return self
        else:
            raise StopIteration
    def next(self): # adapter for python2
        return self.__next__()
    def checkindex(self):
        if self.iteridx<0: logging.error('index check failed!. Initialize index or use for loop')
        return True
    def idx(self):
        logging.debug('idx = %d' % (self.iteridx-1))
        return self.iteridx-1

    def ImportFunction(self, function, **kwargs):
        self._func.append( MethodType(function,self) )
        if 'function' in kwargs: del kwargs['function']
        self._args.append(kwargs)
        self._execres.append(None)

    def ExecuteIteratively(self):
        if self.checkindex():
            self._execres[self.idx()]=self._func[self.idx()](**self._args[self.idx()])
            #return self._func[self.idx()](**self._args[self.idx()])

    def GetArg(self, keyword):
        if self.checkindex():
            if keyword in self._args[self.idx()]:
                return self._args[self.idx()][keyword]
            logging.warning('keyword %s not found!' % keyword)
        return None
    def GetExecRes(self):
        if self.checkindex():
            return self._execres[self.idx()]
    def NeedToExecImoprtedFunc(self):
        return len(self._func) > 0


if __name__ == '__main__':
    class newclass(object):
        def __init__(self):
            self.additionalInfo=ImportAddFunc()
        def AddContent(self, **kwargs):
            self.additionalInfo.ImportFunction(**kwargs)
        def ExecImportedFunc(self, brah):
            if not self.additionalInfo.NeedToExecImportedFunc():
                return None
            for infoMgr in self.additionalInfo:
                infoMgr.ExecuteIteratively()
            for infoMgr in self.additionalInfo:
                a=infoMgr.GetExecRes()
                b=infoMgr.GetArg('hi')


