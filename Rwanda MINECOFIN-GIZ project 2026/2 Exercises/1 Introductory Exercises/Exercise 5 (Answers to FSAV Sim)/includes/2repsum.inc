$STITLE Input file:  REPSUM.INC. Summary of simulation reports. Standard CGE modeling system, Version 1.01


PARAMETERS
*This group of parameters are used for various price-index calculations.
 pdwt(C)  weight of commodity c in PD index
 pwewt(C) weight of commodity c in pwe index
 pwmwt(C) weight of commodity c in pwm index
 pwwt(*)  weight of aggregate exports-imports in pw (tradables) index

*These two parameters are used in the computation of EVTAB

 IC(H,SIM)        indirect compensation fn by hhd h and simulation sim
*IC measure the consumption value needed at base prices to generate same welfare
*as under prices and income under sim

 EV(AC,SIM)        equivalent variation by hhd ac and simulation sim
*EV measures the income change that, at base prices, would be
*equivalent to the change simulated for sim.

$ontext
Source for IC and EV formulas (here adapted to fit demand system
with home and market consumption):
Blonigen, Bruce A., Joseph E. Flynn, and Kenneth A. Reinert
(1997) Sector-Focused General Equilibrium Modeling, pp. 189-230
in eds. Joseph F. Francois and Kenneth A. Reinert, Applied Methods
for Trade Policy Analysis. Cambridge, MA: Cambridge University Press
The formulas are on pp. 224-225.
$offtext
 ;

 pdwt(C)  = PDSX(C,'BASE')*QDX(C,'BASE')/SUM(CP, PDSX(CP,'BASE')*QDX(CP,'BASE'));
 pwewt(C) = pweX(C,'BASE')*QEX(C,'BASE')/SUM(CP, pweX(CP,'BASE')*QEX(CP,'BASE'));
 pwmwt(C) = pwmX(C,'BASE')*QMX(C,'BASE')/SUM(CP, pwmX(CP,'BASE')*QMX(CP,'BASE'));
 pwwt('EXP')
  = SUM(CP, pweX(CP,'BASE')*QEX(CP,'BASE'))
    / (SUM(CP, pweX(CP,'BASE')*QEX(CP,'BASE')) + SUM(CP, pwmX(CP,'BASE')*QMX(CP,'BASE')) );
 pwwt('IMP')
  = SUM(CP, pwmX(CP,'BASE')*QMX(CP,'BASE'))
    / (SUM(CP, pweX(CP,'BASE')*QEX(CP,'BASE')) + SUM(CP, pwmX(CP,'BASE')*QMX(CP,'BASE')) );

 IC(H,SIMCUR)
  = (
     ( EHX(H,SIMCUR)
     - SUM(C, PQX(C,SIMCUR)*gammam(C,H))
     - SUM((A,C), PXACX(A,C,SIMCUR)*gammah(A,C,H)) )
      /
     ( PROD(C, PQX(C,SIMCUR)**betam(C,H))
                        *PROD((A,C), PXACX(A,C,SIMCUR)**betah(A,C,H)) )
      )
   *( PROD(C, PQX(C,'BASE')**betam(C,H))
                        *PROD((A,C), PXACX(A,C,'BASE')**betah(A,C,H)) )
     + SUM(C, PQX(C,'BASE')*gammam(C,H)) + SUM((A,C), PXACX(A,C,'BASE')*gammah(A,C,H));


 EV(H,SIMCUR)       = IC(H,SIMCUR) - EHX(H,'BASE');
 EV('TOTAL',SIMCUR) = SUM(H, EV(H,SIMCUR));


DISPLAY
 pdwt, pwewt, pwmwt, pwwt
 IC, EV;


$ontext
Source for formulas (here adapted to fit demand system
with home and market consumption):

Blonigen, Bruce A., Joseph E. Flynn, and Kenneth A. Reinert
(1997) Sector-Focused General Equilibrium Modeling, pp. 189-230
in eds. Joseph F. Francois and Kenneth A. Reinert, Applied Methods
for Trade Policy Analysis. Cambridge, MA: Cambridge University Press
The formulas are on pp. 224-225.

Sadoulet, E., and A. de Janvry (1995). Quantitative Development Policy
Analysis. The Johns Hopkins University Press: Baltimore and London.
Section 1.5.1.3, pp. 13-14

Note:

CV is measured at simulated prices and incomes. It shows:
the maximum payment the consumer would be willing to make to avoid
having the simulated change undone (i.e. the payment after which the
consumer would have been just as well off as without the change).
For positive (negative) welfare change, CV > 0 (< 0).

EV is measured at base prices and incomes. It shows:
the minimum payment that the consumer would require for foregoing a
change (i.e., if the consumer receives this payment, then he/she is as
well off under base prices and income as he/she would have been if the
change had taken place.)
For positive (negative) welfare change, CV > 0 (< 0).

$offtext


PARAMETERS
 BETAAUX(H)      auxiliary term based on marginal spending shares
 PRICEIND(H,SIM) price index
 EXPSUB(H,SIM)   subsistence spending for hhd h under sim'on sim
 INDUTIL(H,SIM)  indirect utility for hhd h under simulation sim
 EXPV0(H,SIM)    base-utility exp'e fn for hhd h under simulation sim
 CV(AC,SIM)      compensating variation for hhd h under sim'on sim
 CV2(AC,SIM)     concise formula for CV
 ;
*"ALPHA"
 BETAAUX(H)
   = PROD(C, betam(C,H)**betam(C,H))*PROD((A,C), betah(A,C,H)**betah(A,C,H));

 PRICEIND(H,SIMCUR)
   = PROD(C, PQX(C,SIMCUR)**betam(C,H))
        *PROD((A,C), PXACX(A,C,SIMCUR)**betah(A,C,H));

 EXPSUB(H,SIMCUR)
 = SUM(C, PQX(C,SIMCUR)*gammam(C,H))
   + SUM((A,C), PXACX(A,C,SIMCUR)*gammah(A,C,H));

*"V"
 INDUTIL(H,SIMCUR)
 = BETAAUX(H) *( EHX(H,SIMCUR) - EXPSUB(H,SIMCUR) )
    / PRICEIND(H,SIMCUR);

*"e(p1,u0)"
 EXPV0(H,SIMCUR)
 = (INDUTIL(H,'BASE')/BETAAUX(H)) * PRICEIND(H,SIMCUR)
   + EXPSUB(H,SIMCUR);

 CV(H,SIMCUR)
  = EHX(H,SIMCUR) - EXPV0(H,SIMCUR);

 CV('TOTAL',SIMCUR) = SUM(H, CV(H,SIMCUR));

*Alternative definition of CV requiring less precalculations.
 CV2(H,SIMCUR)
  =   (EHX(H,SIMCUR) - EXPSUB(H,SIMCUR))
    - (EHX(H,'BASE') - EXPSUB(H,'BASE'))*PRICEIND(H,SIMCUR)/PRICEIND(H,'BASE');

 CV2('TOTAL',SIMCUR) = SUM(H, CV2(H,SIMCUR));


$ONTEXT
Deriving CV2:

CV2 = EH - EXPV0
    = EH - ((V0/BETA) * PIND + EXPSUB);
    = EH - EXPSUB - (V0/BETA) * PIND ;
    = EH - EXPSUB - (1/BETA)*PIND*V0 ;

    = (EH - EXPSUB)
       - (1/BETA)*PIND *BETA*( EH0 - EXPSUB0 ) / PIND0;

    = (EH - EXPSUB)
       - PIND *( EH0 - EXPSUB0 ) / PIND0;

    = (EH - EXPSUB)
       - (EH0 - EXPSUB0) * PIND/PIND0;

*In words: CV =
[current supernumerary spending]
MINUS
[base supernumerary spending adjusted for changes in price index].


*Superfluous parameters for CV2:
 BETAAUX
 INDUTIL
 EXPV0

$OFFTEXT


DISPLAY
 BETAAUX
 PRICEIND
 EXPSUB
 INDUTIL
 EXPV0
 CV
 CV2
 ;



SET
 SIND Macro summary indicators
 /
*Real quantities, exchange rates and price indices
 QABSTOT real absorption (LCU at base prices)
 QHTOT   real household consumption (LCU at base prices)
 QINVTOT real investment (LCU at base prices)
 QGTOT   real government consumption (LCU at base prices)
 QETOT   total real exports (LCU at base prices)
 QMTOT   total real imports (LCU at base prices)
 REXR    PPP real exchange rate (LCUs per FCU)
 NEXR    nominal exchange rate (LCUs per FCU)
 PWEIND  exports price index (FCU -- 100 for base)
 PWMIND  imports price index (FCU -- 100 for base)
 PWIND   world (tradables) price index (FCU -- 100 for base)
 PDIND   domestic (non-tradables) price index (100 for base)
 CPI     consumer price index (100 for base)
 TOFT    terms of trade (ratio pwe index & pwm index) (100 for base)

*Nominal GDP shares
 INVGDP     investment (% of nominal GDP)
 PRVSAVGDP  private (household + enterprise) savings (% of nominal GDP)
 FORSAVGDP  foreign savings (% of nominal GDP)
 TRDDEFGDP  trade deficit (% of nominal GDP)
 GOVSAVGDP  government savings (% of nominal GDP)
 IMPTAXGDP  tariff revenue (% of nominal GDP)
 DIRTAXGDP  direct tax revenue (% of nominal GDP)
 /

SINDDEV(SIND) summary indicators showing deviation from BASE
 /
 INVGDP     investment (% of nominal GDP)
 PRVSAVGDP  private (household + enterprise) savings (% of nominal GDP)
 FORSAVGDP  foreign savings (% of nominal GDP)
 TRDDEFGDP  trade deficit  (% of nominal GDP)
 GOVSAVGDP  government savings (% of nominal GDP)
 IMPTAXGDP  import tax revenue (% of nominal GDP)
 DIRTAXGDP  direct tax revenue (% of nominal GDP)
 /

 SIMNB(SIM) non-base simulations

 SINDP(SIND)  summary indicators showing percent change
 ;

SIMNB(SIM)    = YES;
SIMNB('BASE') = NO;
SINDP(SIND)$(NOT SINDDEV(SIND)) = YES;

DISPLAY SIMNB, SINDP;

PARAMETER
 MACROTAB(SIND,SIM) Macro table
 QHTAB(AC,SIM)      Disaggregated real household consumption
 EVTAB(AC,SIM)      Disaggregated EV
 YFTAB(AC,SIM)      Disaggregated factor income distribution
 QATAB(AC,SIM)      Disaggregated activity production levels
 PATAB(AC,SIM)      Disaggregated activity prices
 ;

*MACROTAB=====================================

MACROTAB('QINVTOT',SIMCUR) = SUM(C, PQX(C,'BASE')*QINVX(C,SIMCUR));
MACROTAB('QGTOT',SIMCUR)   = SUM(C, PQX(C,'BASE')*QGX(C,SIMCUR));
MACROTAB('QHTOT',SIMCUR)   = SUM((C,H), PQX(C,'BASE')*QHX(C,H,SIMCUR))
                             + SUM((A,C,H), PXACX(A,C,'BASE')*QHAX(A,C,H,SIMCUR)) ;
MACROTAB('QABSTOT',SIMCUR)
  = MACROTAB('QINVTOT',SIMCUR) + MACROTAB('QGTOT',SIMCUR)
  + MACROTAB('QHTOT',SIMCUR);

MACROTAB('QETOT',SIMCUR)  = SUM(C, PWEX(C,'BASE')*EXRX('BASE')*QEX(C,SIMCUR));
MACROTAB('QMTOT',SIMCUR)  = SUM(C, PWMX(C,'BASE')*EXRX('BASE')*QMX(C,SIMCUR));
MACROTAB('CPI',SIMCUR)    = 100*cpix(SIMCUR)/cpix('BASE');
MACROTAB('NEXR',SIMCUR)   = 100*EXRX(SIMCUR);
MACROTAB('PDIND',SIMCUR)  = 100*SUM(C, pdwt(C)*PDSX(C,SIMCUR));

MACROTAB('PWEIND',SIMCUR)
  = 100*SUM(C, pwex(C,SIMCUR)*pwewt(C))
    /SUM(C, pwex(C,'BASE')*pwewt(C));
MACROTAB('PWMIND',SIMCUR)
  = 100*SUM(C, pwmx(C,SIMCUR)*pwmwt(C))
    /SUM(C, pwmx(C,'BASE')*pwmwt(C));;

MACROTAB('TOFT',SIMCUR)
  = 100*MACROTAB('PWEIND',SIMCUR)/MACROTAB('PWMIND',SIMCUR);

MACROTAB('PWIND',SIMCUR)
  =  pwwt('EXP')*MACROTAB('PWEIND',SIMCUR)
  +  pwwt('IMP')*MACROTAB('PWMIND',SIMCUR);


MACROTAB('REXR',SIM)$SIMCUR(SIM)
 = MACROTAB('NEXR',SIM)*MACROTAB('PWIND',SIM)/MACROTAB('PDIND',SIM)
  ;

 MACROTAB('INVGDP',SIMCUR)
  = 100*SUM(C, PQX(C,SIMCUR)*QINVX(C,SIMCUR))
    /GDPTAB1('NOMINAL','GDPMP',SIMCUR);

 MACROTAB('PRVSAVGDP',SIMCUR)
  = 100*SUM(INSDNG, SAMBUD('INSDNG',INSDNG,'SPND','S-I',SIMCUR))
    /GDPTAB1('NOMINAL','GDPMP',SIMCUR);

 MACROTAB('FORSAVGDP',SIMCUR)
   = 100*EXRX(SIMCUR)*FSAVX(SIMCUR)
     /GDPTAB1('NOMINAL','GDPMP',SIMCUR);

 MACROTAB('TRDDEFGDP',SIMCUR)
   = 100*(SUM(C, PMX(C,SIMCUR)*QMX(C,SIMCUR))
     - SUM(C, PEX(C,SIMCUR)*QEX(C,SIMCUR)))
     /GDPTAB1('NOMINAL','GDPMP',SIMCUR);

 MACROTAB('GOVSAVGDP',SIMCUR)
   = 100*SAMBUD('GOV','DUM','SPND','S-I',SIMCUR)
     /GDPTAB1('NOMINAL','GDPMP',SIMCUR);

 MACROTAB('IMPTAXGDP',SIMCUR)
   = 100*SAMBUD('GOV','DUM','INC','IMPTAX',SIMCUR)
     /GDPTAB1('NOMINAL','GDPMP',SIMCUR);

 MACROTAB('DIRTAXGDP',SIMCUR)
   = 100*(SAMBUD('GOV','DUM','INC','INSTAX',SIMCUR)
     + SAMBUD('GOV','DUM','INC','FACTAX',SIMCUR))
     /GDPTAB1('NOMINAL','GDPMP',SIMCUR);


*TABLES OTHER THAN MACROTAB===============================

 QHTAB(H,SIMCUR)       = SUM(C, PQX(C,'BASE')*QHX(C,H,SIMCUR))
                         + SUM((A,C), PXACX(A,C,'BASE')*QHAX(A,C,H,SIMCUR));
 QHTAB('TOTAL',SIMCUR) = SUM((C,H), PQX(C,'BASE')*QHX(C,H,SIMCUR))
                         + SUM((A,C,H), PXACX(A,C,'BASE')*QHAX(A,C,H,SIMCUR));

 EVTAB(H,'BASE')       = EHX(H,'BASE');
 EVTAB('TOTAL','BASE') = SUM(H, EHX(H,'BASE'));

 EVTAB(H,SIMNB)        = 100*EV(H,SIMNB)/EHX(H,'BASE');
 EVTAB('TOTAL',SIMNB)  = 100*SUM(H, EV(H,SIMNB))/SUM(H, EHX(H,'BASE'));

 YFTAB(F,SIMCUR)
   = 100*SAMBUD('FAC',F,'INC','TOTAL',SIMCUR)
     /SUM(FP, SAMBUD('FAC',FP,'INC','TOTAL',SIMCUR));
 YFTAB('TOTAL',SIMCUR) = SUM(F, YFTAB(F,SIMCUR));

 QATAB(A,SIMCUR)       = PAX(A,'BASE')*QAX(A,SIMCUR);
 QATAB('TOTAL',SIMCUR) = SUM(A, PAX(A,'BASE')*QAX(A,SIMCUR));

 PATAB(A,SIMCUR)       = 100*PAX(A,SIMCUR);

*==============================================
*Computing %-age change from BASE for QHTAB and
*for selected indicators of MACROTAB (in SINDP)

MACROTAB(SINDP,SIMNB)$SIMCUR(SIMNB)
  = 100*(MACROTAB(SINDP,SIMNB)/MACROTAB(SINDP,'BASE') - 1);

QHTAB(AC,SIMNB)$(SIMCUR(SIMNB)$QHTAB(AC,'BASE'))
  = 100*(QHTAB(AC,SIMNB)/QHTAB(AC,'BASE') - 1);

QATAB(AC,SIMNB)$(SIMCUR(SIMNB)$QATAB(AC,'BASE'))
  = 100*(QATAB(AC,SIMNB)/QATAB(AC,'BASE') - 1);

PATAB(AC,SIMNB)$(SIMCUR(SIMNB)$PATAB(AC,'BASE'))
  = 100*(PATAB(AC,SIMNB)/PATAB(AC,'BASE') - 1);

*==============================================
*Computing deviation from BASE for YFTAB and
*for selected indicators of MACROTAB (in SINDDEV)

MACROTAB(SINDDEV,SIMNB)$SIMCUR(SIMNB)
  = MACROTAB(SINDDEV,SIMNB) - MACROTAB(SINDDEV,'BASE');

YFTAB(AC,SIMNB)$SIMCUR(SIMNB)
  = YFTAB(AC,SIMNB) - YFTAB(AC,'BASE');


*Rounding all values to one decimal point
* MACROTAB(SIND,SIM)   = ROUND(MACROTAB(SIND,SIM),1);
* EVTAB(AC,SIM)        = ROUND(EVTAB(AC,SIM),1);
* QHTAB(AC,SIM)        = ROUND(QHTAB(AC,SIM),1);
* YFTAB(AC,SIM)        = ROUND(YFTAB(AC,SIM),1);
* QATAB(AC,SIM)        = ROUND(QATAB(AC,SIM),1);
* PATAB(AC,SIM)        = ROUND(PATAB(AC,SIM),1);

*Displaying only one decimal point
 OPTION DECIMALS=1;

DISPLAY
 MACROTAB
"In the BASE column, aggregate real indicators are measured"
"at base-year values."
"Exchange rates and price indices are set at 100."
"Items with GDP in name are expressed as % of nominal GDP."
""
"Units for non-BASE columns:"
"% changes from BASE for items not computed as GDP shares;"
"deviation from BASE for items computed as GDP shares."
""

QHTAB
"In the BASE column, quantities are measured at base-year prices."
"The non-BASE columns show % change from BASE."

EVTAB
"In the BASE column, consumption value at base-year prices."
"The non-BASE columns show EV as % of BASE consumption value."

YFTAB
"The BASE column show %-age shares of base factor incomes."
"The non-BASE columns show deviations from BASE."

QATAB
"In the BASE column, quantities are measured at base-year prices."
"The non-BASE columns show % change from BASE."

PATAB
"Base-prices are indexed to 100."
"The non-BASE columns show % change from BASE."
;

*#*#*#*#*# THE END OF REPSUM.INC #*#*#*#*
