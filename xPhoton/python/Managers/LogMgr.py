#!/usr/bin/env python3
# need to do : add path management

import time
import logging
import logging.config
import os
def LoadLoggerConfig(confPath='../data/logger.config',fromCurrentDir=True):
    ''' load config file
        To do : add generalized path
    '''

    if os.path.exists('./log'):
        if not os.path.isdir('./log'):
            raise OSError('./log is not a directory, which is needed to store log files')
    else:
        os.mkdir('./log')

    #print os.path.join(os.getcwd(),fileName)
    #logging.config.fileConfig(os.path.join(os.getcwd(),fileName))
    logPath=confPath
    #logPath=confPath if fromCurrentDir else
    logging.config.fileConfig(os.path.join(logPath))
def GetLogger(logname=__name__):
    return logging.getLogger(logname)

def translatelevel(LEvEL):
    level=LEvEL.lower()
    if level == 'debug'    : return logging.DEBUG
    if level == 'info'     : return logging.INFO
    if level == 'warning'  : return logging.WARNING
    if level == 'error'    : return logging.ERROR
    if level == 'critical' : return logging.CRITICAL

'''
def InitLogger(file=None, level='info'):
    logging.basicConfig(
            level=translatelevel(level),
            format='[%(levelname)-8s] - %(name)s: %(message)s',
            handlers=logging.FileHandler(file,'w') if file else logging.StreamHandler()
            )
'''
def InitLogger(file=None, level='info'):
    logger = logging.getLogger()
    logger.setLevel(translatelevel(level))
    formatter = logging.Formatter(
        #'[%(levelname)1.1s %(asctime)s %(module)s:%(lineno)d] %(message)s',
        '%(levelname).5s #%(name)s @L%(lineno)d -> %(message)s',
        datefmt='%Y%m%d %H:%M:%S')

    ch = logging.StreamHandler()
    ch.setLevel(logging.DEBUG)
    ch.setFormatter(formatter)

    logger.addHandler(ch)

    if file:
        log_filename = datetime.datetime.now().strftime(file+"%Y-%m-%d_%H_%M_%S.log")
        fh = logging.FileHandler(log_filename)
        fh.setLevel(logging.DEBUG)
        fh.setFormatter(formatter)

        logger.addHandler(fh)

def InitFileLogger(file='log', level='debug'):
    InitLogger(file,level)



if __name__ == '__main__':
    # example usage

    #LoadLoggerConfig(confPath='../data/logger_fileConsole.config', fromCurrentDir=True)
    InitLogger(level='debug')
    mylog=GetLogger('LogMgr')

    mylog.debug('this is debug')
    mylog.info('this is info!')
    mylog.warning('thisssssss is warning')
    mylog.error('thisi is error')
    mylog.critical('the critical log')
