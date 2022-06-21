#!/usr/bin/env python
import os

str0 = "mkdir -p ./plots_threecomp"
print(str0)
os.system(str0)

for ptbin in range(0, 1):
    str1 = "root.exe -q 'ThreeComparison.C("+str(ptbin)+")'"
    print(str1)
    os.system(str1)
