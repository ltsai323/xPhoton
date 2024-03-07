#!/usr/bin/env python3
import csv
import uncertainties as unc


if __name__ == "__main__":
    import sys
    inFILE = sys.argv[1]
    with open(inFILE,'r') as ifile:
        contents = csv.DictReader(ifile)

        barrel = {}
        endcap = {}
        for content in contents:
            if content['jEtaBin'] == '1': continue
            the_int = lambda name: int(content[name])
            the_float = lambda name: float(content[name])
            pptbin = the_int('pPtBin')
            petabin = the_int('pEtaBin')

            #fit_and_err = lambda c: unc.ufloat( the_float(f'fit_yield_{c}'),the_float(f'fit_error_{c}') )
            fit_and_err = lambda c: unc.ufloat( the_float(f'fit_yield_{c}'),0. )
            yield_c = fit_and_err('C')
            yield_b = fit_and_err('B')
            yield_l = fit_and_err('L')
            if petabin == 0:
                barrel[pptbin] = yield_c
            else:
                endcap[pptbin] = yield_c
        for idx in range(20):
            if idx in barrel and idx in endcap:
                b = barrel[idx].nominal_value
                e = endcap[idx].nominal_value

                print( f'bin {idx} : barrel {b:.2f} / endcap {e:.2f} = {b/e:.3f}')
