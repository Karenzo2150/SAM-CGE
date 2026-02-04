*Standard SAM aggregation

$setglobal data "0output"
$setglobal result "0output"

$call "gdxxrw i=%data%.xlsx o=%data%.gdx index=index!a35"
$gdxin %data%.gdx

SET
 N               new accounts
 O               old accounts
 MNO(N,O)        mapping
;

$LOAD N O MNO

ALIAS (N,NP), (O,OP);

PARAMETER
 OSAM(O,OP)      old sam
 NSAM(N,NP)      new sam
 ODIFF(O)        old differences
 NDIFF(N)        new differences
;

$LOAD OSAM

 OSAM('TOTAL',O) = 0;
 OSAM(O,'TOTAL') = 0;

 NSAM(N,NP) = SUM((O,OP)$(MNO(N,O) AND MNO(NP,OP)), OSAM(O,OP));

 OSAM('TOTAL',O) = SUM(OP, OSAM(OP,O));
 OSAM(O,'TOTAL') = SUM(OP, OSAM(O,OP));

 NSAM('TOTAL',N) = SUM(NP, NSAM(NP,N));
 NSAM(N,'TOTAL') = SUM(NP, NSAM(N,NP));

 ODIFF(O) = OSAM('TOTAL',O) - OSAM(O,'TOTAL');
 NDIFF(N) = NSAM('TOTAL',N) - NSAM(N,'TOTAL');

 ODIFF(O)$(ABS(ODIFF(O)) LT 1E-6) = 0;
 NDIFF(N)$(ABS(NDIFF(N)) LT 1E-6) = 0;

DISPLAY ODIFF, NDIFF;

execute_unload "%result%.gdx" NSAM
execute 'gdxxrw.exe i=%result%.gdx o=%result%.xlsx index=index!a45'
