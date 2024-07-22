#!/usr/bin/env python3

import csv
def key_translater(theKEY:str):
    if theKEY == 'ptbin':   return 'pPtBin'
    if theKEY == 'EBEE':    return 'pEtaBin'
    if theKEY == 'jetbin':  return 'jEtaBin'
    return theKEY


if __name__ == "__main__":
    import sys
    inFILE = sys.argv[1]

    recs = []
    keys = []

    with open(inFILE,'r') as ifile:
        for line in ifile.readlines():
            if len(keys) == 0:
                # ptbin/I:EBEE/I:jetbin/I:efficiency/F:error/F
                values = line.strip().split(':')
                for value in values:
                    key = value[:value.find('/')]
                    keys.append( key_translater(key) )
            else:
                # 0 0 0 0.0434105992 0.0000000000
                values = line.strip().split(' ')
                rec = { keys[idx]:value for idx,value in enumerate(values) }
                recs.append(rec)


    outFILE = inFILE[:-4]+'.csv'
    with open(outFILE, 'w') as outFile:
        import csv
        csv_writer = csv.DictWriter(outFile, fieldnames = keys)
        csv_writer.writeheader()
        csv_writer.writerows(recs)
