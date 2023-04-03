export USER_CXXFLAGS="-Wno-error=unused-variable -Wno-error=unused-but-set-variable -DEDM_ML_DEBUG -g"
cmsrel CMSSW_11_3_4
cd CMSSW_11_3_4/src
cmsevn

git clone https://github.com/ltsai323/xPhoton.git -b main
git clone https://github.com/youyingli/ShowerShapeCorrection.git
