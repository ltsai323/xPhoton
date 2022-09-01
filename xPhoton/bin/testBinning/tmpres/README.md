# checking with new code
* [ ] GetEntries is the same as makehisto + Drawisovsbdt code. But Integral is not.
   - checknewmakehisto.sh : check TDataframe get the same result with old code or not. The result shows integral value is not exactly the same. Almost all of them gives 0.00% difference but it still have 0.03% difference at some bin. And most of diviated bin are low pt bin. (0~9)
   - checknewoldRScodes.sh : To understand why GetEntries gives a fractional number in DrawIsovsBDT. Add manual signal region selection hist. And this code is the analyzer.

   - checkqcd.sh
   - check.sh
   - checksignal.sh
