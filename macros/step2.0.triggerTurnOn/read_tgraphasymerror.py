#!/usr/bin/env python3
import uproot



if __name__ == "__main__":
    f = uproot.open('out.root')
    h = f['Graph']
    print(h.__dir__())

    print('values')
    print(h.values())
    print('errors low')
    print(h.errors('low'))
    print('errors high')
    print(h.errors('high'))
    print('errors mean')
    print(h.errors('mean'))
    print('errors diff')
    print(h.errors('diff'))
