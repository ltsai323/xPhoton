#!/usr/bin/env python
import os

str0 = "mkdir -p ./plots_twocomp"
print(str0)
os.system(str0)

for ptbin in range(0, 1):
    str1 = "root.exe -q 'TwoComparison.C("+str(ptbin)+")'"
    print(str1)
    os.system(str1)
