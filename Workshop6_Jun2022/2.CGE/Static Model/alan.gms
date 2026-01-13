$title A Quadratic Programming Model for Portfolio Analysis (ALAN,SEQ=124)

$onText
This is a mini mean-variance portfolio selection problem described in
'GAMS/MINOS: Three examples' by Alan S. Manne, Department of Operations
Research, Stanford University, May 1986.

Integer variables have been added to restrict the number of securities
selected. The resulting MINLP problem is solved with different option
settings to demonstrate some DICOPT features. Finally, the model is
solved by complete enumeration using GAMS procedural facilities.


Manne, A S, GAMS/MINOS: Three examples. Tech. rep., Department of
Operations Research, Stanford University, 1986.

Keywords: mixed integer nonlinear programming, portfolio optimization,
          complete enumeration, finance
$offText

Set i 'securities' / hardware, software, show-biz, t-bills /;

Alias (i,j);

Scalar target     'target mean annual return on portfolio       (%)' / 10 /;

Parameter mean(i) 'mean annual returns on individual securities (%)'
                  / hardware 8, software 9, show-biz 12, t-bills 7 /;

Table v(i,j) 'variance-covariance array   (%-squared annual return)'
              hardware  software  show-biz  t-bills
   hardware          4         3        -1        0
   software          3         6         1        0
   show-biz         -1         1        10        0
   t-bills           0         0         0        0;

Variable
   x(i)     'fraction of portfolio invested in asset i'
   variance 'variance of portfolio';

Positive Variable x;

Equation
   fsum  'fractions must add to 1.0'
   dmean 'definition of mean return on portfolio'
   dvar  'definition of variance';

fsum..  sum(i, x(i))                    =e= 1.0;

dmean.. sum(i, mean(i)*x(i))            =e= target;

dvar..  sum(i, x(i)*sum(j,v(i,j)*x(j))) =e= variance;

Model portfolio / fsum, dmean, dvar /;

solve portfolio using nlp minimizing variance;

* now allow only three assets in our portfolio
Scalar maxassets 'max assets in portfolio' / 3 /;

Binary Variable active(i) 'indicator: if 1 then asset is in portfolio';

Equation
   setindic(i) 'if active is 0 then not in portfolio'
   maxactive   'defines max number of assets in portfolio';

setindic(i).. x(i) =l= active(i);

maxactive..   sum(i, active(i)) =l= maxassets;

Model p1 / fsum, dmean, dvar, setindic, maxactive /;

solve p1 using minlp minimizing variance;

* now we change the solution options for dicopt
File opt /dicopt.opt/;
putClose opt 'stop 1';

p1.optFile = 1;
option limCol = 0, limRow = 0;

solve p1 using minlp minimizing variance;

if(    p1.modelStat <> %modelStat.optimal%
   and p1.modelStat <> %modelStat.locallyOptimal%
   and p1.modelStat <> %modelStat.feasibleSolution%
   and p1.modelStat <> %modelStat.integerSolution%,
   abort 'Could not solve p1 minimizing variance';
);

* just to be sure we also do complete enumeration and put results
* on a separate file.
Set b / zero, one /;

Parameter boole(b) / zero 0, one 1 /;

Alias (b,b1,b2,b3,b4);

File res / results.put /;
put  res;

Scalar min / 1.0e10 /;

p1.solPrint = %solPrint.Summary%;
p1.optFile  = 0;

loop(i, put ' ',i.tl:4 );
put '  variance';
loop((b1,b2,b3,b4),
   active.fx('hardware') = boole(b1);
   active.fx('software') = boole(b2);
   active.fx('show-biz') = boole(b3);
   active.fx('t-bills')  = boole(b4);

   solve p1 minimizing variance using rminlp;
   put / boole(b1):5:0 boole(b2):5:0 boole(b3):5:0 boole(b4):5:0;

   if(p1.solveStat <> %solveStat.normalCompletion%,
      put '            *** failed solveStat=' p1.solveStat:0:0 ' modelStat=', p1.modelStat:0:0;
      display 'Solver failed', p1.solveStat, p1.modelStat;
   else
      if(p1.modelStat <= %modelStat.locallyOptimal% or p1.modelStat = %modelStat.feasibleSolution%,
         put variance.l:15:5;
         if(variance.l < min,
            put ' *';
            min = variance.l;
         );
      else
         put '    infeas, etc';
      );
   );
);
