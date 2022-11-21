
mainfunc()
{
    tag=$1
    counter1=`cat scripts/RUNbkgSumbit/path_16rereco_QCDmadgraph_getPUpthat/QCD_HT${1}_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.txt | grep -c root `
    counter2=` ls ~/Data/CRABdata/CRABdata_QCDHT${tag}_2016ReReco_PUPtHat_25_10_2022/*.root  | grep root -c `
    echo "at $tag : counter reports $(( ${counter1} == ${counter2} ))"
}

mainfunc 50to100
mainfunc 100to200
mainfunc 200to300
mainfunc 300to500
mainfunc 500to700
mainfunc 700to1000
mainfunc 1000to1500
mainfunc 1500to2000
mainfunc 2000toInf
