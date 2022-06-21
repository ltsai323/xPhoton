#!/usr/bin/env python
import os

str0 = "mkdir -p ./plots_toydata"
print(str0)
os.system(str0)

str1= "mkdir -p ./plots_toymc"
print(str1)
os.system(str1)

for ptbin in range(0, 20):
    str2 = "root.exe -q 'DrawTemplates.C("+str(ptbin)+")'"
    print(str2)
    os.system(str2)
