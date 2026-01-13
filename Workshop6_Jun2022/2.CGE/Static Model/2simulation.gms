$TITLE Simulation files. Standard CGE modeling system, Version 1.01 (March 2003)
$STITLE Input file: SIM101.GMS. Standard CGE modeling system, Version 1.01

$OFFSYMLIST OFFSYMXREF

*For a well-tested model that solves without errors and needs no further
*debugging, you may overwrite the options that were specified in the
*file MOD*.GMS by removing the asterisks in the first columns of the
*following two lines.
*OPTIONS ITERLIM=10000, LIMROW=0, LIMCOL=0
*        SOLPRINT=OFF , MCP=PATH, NLP=MINOS;

$ontext
The file contents in outline:
1. SETS FOR SIMULATIONS
2. DEFINING EXPERIMENT PARAMETERS
3. DEFINING NUMERAIRE AND CLOSURES FOR MACRO SYSTEM CONSTRAINTS
4. DEFINING CLOSURES FOR FACTOR MARKETS
5. REPORT SETUP
6. LOOP
7. COMPUTING PERCENTAGE CHANGE FOR REPORT PARAMETERS
8. CHECKING FOR GAP ERROR IN REPORT PARAMETERS
9. DISPLAYING REPORTS
$offtext

*1. SETS FOR SIMULATIONS

SET
 SIM                     simulations
 SIMCUR(SIM)             current simulations
 SIMBASINIT(SIM)         simulations with variable initialized at base level
 SIMMCP(SIM)             simulations solved as MCP problems
 AFIX(SIM)             sectors with fixed production
;

*2. DEFINING EXPERIMENT PARAMETERS

$include includes\2simulation.dat

*Variable initializatiion at base level may provide a better starting
*point for selected simulations (depending on the content of the
*preceding simulation).
 SIMBASINIT(SIM)   = NO;
 SIMBASINIT(SIM)   = YES;

*It is typically preferable to solve the MCP version of the model.
 SIMMCP(SIM)     = YES;

 SIMCUR(SIM)$(ACTIVE(SIM) NE 0) = YES;
 SIMCUR('BASE') = YES;

DISPLAY SIMCUR, SIMBASINIT;


*3. DEFINING NUMERAIRE AND CLOSURES FOR MACRO SYSTEM CONSTRAINTS

PARAMETERS
 NUMERAIRE(SIM)          numeraire
 SICLOS(SIM)             value for savings-investment closure
 ROWCLOS(SIM)            value for rest-of-world closure
 GOVCLOS(SIM)            value for government closure
 MPS01SIM(INS,SIM)       0-1 par for potential flexing of savings rates
 TINS01SIM(INS,SIM)      0-1 par for potential flexing of dir tax rates
;

*NUMERAIRE, SICLOS, ROWCLOS, and GOVCLOS are set at default values
 NUMERAIRE(SIM) = 1;
 GOVCLOS(SIM)   = 1;
 SICLOS(SIM)    = 3;
 ROWCLOS(SIM)   = 1;

*Numeraire
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 1) = SIM1MC('DUM');
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 2) = SIM2MC('DUM');
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 3) = SIM3MC('DUM');
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 4) = SIM4MC('DUM');
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 5) = SIM5MC('DUM');
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 6) = SIM6MC('DUM');
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 7) = SIM7MC('DUM');
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 8) = SIM8MC('DUM');
 NUMERAIRE(SIM)$(SIMORD(SIM) EQ 9) = SIM9MC('DUM');

*Savings-investment account
 SICLOS(SIM)$(SIMORD(SIM) EQ 1) = SIM1MC('S-I');
 SICLOS(SIM)$(SIMORD(SIM) EQ 2) = SIM2MC('S-I');
 SICLOS(SIM)$(SIMORD(SIM) EQ 3) = SIM3MC('S-I');
 SICLOS(SIM)$(SIMORD(SIM) EQ 4) = SIM4MC('S-I');
 SICLOS(SIM)$(SIMORD(SIM) EQ 5) = SIM5MC('S-I');
 SICLOS(SIM)$(SIMORD(SIM) EQ 6) = SIM6MC('S-I');
 SICLOS(SIM)$(SIMORD(SIM) EQ 7) = SIM7MC('S-I');
 SICLOS(SIM)$(SIMORD(SIM) EQ 8) = SIM8MC('S-I');
 SICLOS(SIM)$(SIMORD(SIM) EQ 9) = SIM9MC('S-I');

*Current account
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 1) = SIM1MC('ROW');
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 2) = SIM2MC('ROW');
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 3) = SIM3MC('ROW');
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 4) = SIM4MC('ROW');
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 5) = SIM5MC('ROW');
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 6) = SIM6MC('ROW');
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 7) = SIM7MC('ROW');
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 8) = SIM8MC('ROW');
 ROWCLOS(SIM)$(SIMORD(SIM) EQ 9) = SIM9MC('ROW');

*Government account
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 1) = SIM1MC('GOV');
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 2) = SIM2MC('GOV');
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 3) = SIM3MC('GOV');
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 4) = SIM4MC('GOV');
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 5) = SIM5MC('GOV');
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 6) = SIM6MC('GOV');
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 7) = SIM7MC('GOV');
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 8) = SIM8MC('GOV');
 GOVCLOS(SIM)$(SIMORD(SIM) EQ 9) = SIM9MC('GOV');

$ontext
For closures with flexible savings or direct tax rates, the default is
that the rates of all domestic non-government institutions adjust. If
you deviate from the default, make sure that, for both parameters and
for simulations using the indicated closures, the value of at least one
element in INSDNG is unity. (If not, the parameters ERRMPS01 and
ERRTINS01 will generate errors.)
$offtext

 MPS01SIM(INSDNG,SIM)   = 1;
 TINS01SIM(INSDNG,SIM)  = 1;

*Institutional savings adjustable
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 1) = SIM1HC(INSDNG,'MPS');
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 2) = SIM2HC(INSDNG,'MPS');
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 3) = SIM3HC(INSDNG,'MPS');
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 4) = SIM4HC(INSDNG,'MPS');
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 5) = SIM5HC(INSDNG,'MPS');
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 6) = SIM6HC(INSDNG,'MPS');
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 7) = SIM7HC(INSDNG,'MPS');
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 8) = SIM8HC(INSDNG,'MPS');
 MPS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 9) = SIM9HC(INSDNG,'MPS');

*Institutional tax rate adjustable
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 1) = SIM1HC(INSDNG,'TINS');
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 2) = SIM2HC(INSDNG,'TINS');
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 3) = SIM3HC(INSDNG,'TINS');
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 4) = SIM4HC(INSDNG,'TINS');
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 5) = SIM5HC(INSDNG,'TINS');
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 6) = SIM6HC(INSDNG,'TINS');
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 7) = SIM7HC(INSDNG,'TINS');
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 8) = SIM8HC(INSDNG,'TINS');
 TINS01SIM(INSDNG,SIM)$(SIMORD(SIM) EQ 9) = SIM9HC(INSDNG,'TINS');

PARAMETERS
 ERRMPS01(SIM)  UNDF if MPS01SIM not unity for at least one INSDNG
*In order for SICLOS 1, 2, 4 and 5 to work, MPS01SIM has to have a value of
*unity for at least one element in INSDNG for every SIM. If this is not
*the case, an error is generated. Solution: change the definition if
*MPS01SIM.
 ERRTINS01(SIM)  UNDF if TINS01SIM not unity for at least one INSDNG
*In order for GOVCLOS 2 and 3 to work, TINS01SIM has to have a value of
*unity for at least one element in INSDNG for every SIM. If this is not
*the case, an error is generated. Solution: change the definition if
*TINS01SIM.
 ;

 ERRMPS01(SIM)$(((SICLOS(SIM) EQ 1) OR (SICLOS(SIM) EQ 2) OR (SICLOS(SIM) EQ 4) OR (SICLOS(SIM) EQ 5))
  AND (SUM(INSDNG$(MPS01SIM(INSDNG,SIM) EQ 1), 1) LT 1)) = 1/0;

 ERRTINS01(SIM)$(((GOVCLOS(SIM) EQ 2) OR (GOVCLOS(SIM) EQ 3))
  AND (SUM(INSDNG$(TINS01SIM(INSDNG,SIM) EQ 1), 1) LT 1)) = 1/0;

DISPLAY
 NUMERAIRE, SICLOS, GOVCLOS, ROWCLOS, MPS01SIM, TINS01SIM, ERRMPS01, ERRTINS01
 ;

PARAMETER
 ERRMPSEQ1(INS,SIM) UNDF error if institution with MPS at unity has flexible MPS
$ontext
Savings-investment closures that involve adjustments of the MPS of an
element in INSDNG for which mpsbar is at (or very close) to unity will
not work (since the total spending of such an institution will deviate
from its total income whenever the MPS changes). The user should review
the SAM and other data sources to assess whether an mpsbar of unity is
plausible and change the SAM if it is not. If it is plausible, it would
be necessary to give such an institution a value of zero for MPS01SIM
under savings-investment closures with a flexible MPS for one or more
other institutions.

This parameter is first defined in REPLOOP.INC and redefined after the
LOOP in a manner that generates an UNDF error if the error is present.
$offtext

*4. DEFINING CLOSURES FOR FACTOR MARKETS

PARAMETERS
 FMOBFE(F,SIM)  factor f is fully employed & mobile in sim
 FACTFE(F,SIM)  factor f is fully employed & activity-specific in sim
 FMOBUE(F,SIM)  factor f is unemployed & mobile in sim
 ;

*Fully employed fixed supply
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 1 AND SIM1FC(F) EQ 1) = YES;
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 2 AND SIM2FC(F) EQ 1) = YES;
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 3 AND SIM3FC(F) EQ 1) = YES;
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 4 AND SIM4FC(F) EQ 1) = YES;
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 5 AND SIM5FC(F) EQ 1) = YES;
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 6 AND SIM6FC(F) EQ 1) = YES;
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 7 AND SIM7FC(F) EQ 1) = YES;
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 8 AND SIM8FC(F) EQ 1) = YES;
 FMOBFE(F,SIM)$(SIMORD(SIM) EQ 9 AND SIM9FC(F) EQ 1) = YES;

*Fully employed activity specific
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 1 AND SIM1FC(F) EQ 2) = YES;
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 2 AND SIM2FC(F) EQ 2) = YES;
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 3 AND SIM3FC(F) EQ 2) = YES;
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 4 AND SIM4FC(F) EQ 2) = YES;
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 5 AND SIM5FC(F) EQ 2) = YES;
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 6 AND SIM6FC(F) EQ 2) = YES;
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 7 AND SIM7FC(F) EQ 2) = YES;
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 8 AND SIM8FC(F) EQ 2) = YES;
 FACTFE(F,SIM)$(SIMORD(SIM) EQ 9 AND SIM9FC(F) EQ 2) = YES;

*Unemployed fixed wage
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 1 AND SIM1FC(F) EQ 3) = YES;
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 2 AND SIM2FC(F) EQ 3) = YES;
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 3 AND SIM3FC(F) EQ 3) = YES;
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 4 AND SIM4FC(F) EQ 3) = YES;
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 5 AND SIM5FC(F) EQ 3) = YES;
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 6 AND SIM6FC(F) EQ 3) = YES;
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 7 AND SIM7FC(F) EQ 3) = YES;
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 8 AND SIM8FC(F) EQ 3) = YES;
 FMOBUE(F,SIM)$(SIMORD(SIM) EQ 9 AND SIM9FC(F) EQ 3) = YES;

*If no value is specified for a factor, impose FMOBFE:
 FMOBFE(F,SIM)$(FMOBFE(F,SIM) + FACTFE(F,SIM) + FMOBUE(F,SIM) EQ 0) = 1;

*Checking for errors in factor market closures

PARAMETER
 ERRFCLOS(F,SIM) UNDF error if not exactly one closure by f and sim
*Error if any factor f, in each simulation, does not have a non-zero
*value for exactly one of the three parameters FMOBFE, FACTFE, FMOBUE.
 ;
 ERRFCLOS(F,SIM)$(FMOBFE(F,SIM)+ FACTFE(F,SIM)+ FMOBUE(F,SIM) NE 1) = 1/0;

DISPLAY ERRFCLOS, FMOBFE, FACTFE, FMOBUE;


*5. REPORT SETUP

$INCLUDE includes\2REPSETUP.INC

*--------------------------------------------------------------------
*6. Loop
*--------------------------------------------------------------------
LOOP(SIMCUR,

*This include statement is optional. It may facilitate solver
*performance by providing better starting point.
IF(SIMBASINIT(SIMCUR),
$INCLUDE includes\1VARINIT.INC
);

*IMPOSING PARAMETER  & FIXED VARIABLE VALUES FOR EXPERIMENTS
*In this section, changes in experiment parameters and fixed
*variables are imposed, except for changes in fixed variables related to
*closures, which are handled in the next section.

 alphava(A)       = ALPHAVASIM(A,SIMCUR);
 ta(A)            = TASIM(A,SIMCUR);
 tva(A)           = TVASIM(A,SIMCUR);
 PWM.FX(C)        = PWMSIM(C,SIMCUR);
 PWE.FX(C)        = PWESIM(C,SIMCUR);
 te(C)            = TESIM(C,SIMCUR);
 tm(C)            = TMSIM(C,SIMCUR);
 tq(C)            = TQSIM(C,SIMCUR);
 ice(C,CP)        = ICESIM(C,CP,SIMCUR);
 icm(C,CP)        = ICMSIM(C,CP,SIMCUR);
 icd(C,CP)        = ICDSIM(C,CP,SIMCUR);
 tf(F)            = TFSIM(F,SIMCUR);
 trnsfr(H,'GOV')  = TRNSFRSIM(H,'GOV',SIMCUR);
 trnsfr(H,'ROW')  = TRNSFRSIM(H,'ROW',SIMCUR);

*IMPOSING CLOSURES FOR SYSTEM CONSTRAINTS

*Selecting institutions with potentially flexible savings and direct
*tax rates. This setting only matters for some of the alternative
*savings-investment and government closures.
 mps01(INSDNG)  = MPS01SIM(INSDNG,SIMCUR);
 tins01(INSDNG) = TINS01SIM(INSDNG,SIMCUR);

*-------------
IF(NUMERAIRE(SIMCUR) EQ 1,
 CPI.FX = CPI0;
 DPI.LO = -INF;
 DPI.UP = +INF;
 DPI.L  = DPI0;  );

IF(NUMERAIRE(SIMCUR) EQ 2,
 DPI.FX = DPI0;
 CPI.LO = -INF;
 CPI.UP = +INF;
 CPI.L  = CPI0;  );

IF(NUMERAIRE(SIMCUR) EQ 3,
 DPI.LO = -INF;
 DPI.UP = +INF;
 DPI.L  = DPI0;
 CPI.LO = -INF;
 CPI.UP = +INF;
 CPI.L  = CPI0;  );

*-------------

IF(SICLOS(SIMCUR) EQ 1,
*Investment-driven savings
*Uniform MPS rate point change for selected ins
*Fixed investment demand quantity adjustment factors
*Flexible absorption shares for investment demand
 MPSADJ.FX = MPSADJSIM(SIMCUR);
 DMPS.LO = -INF; DMPS.UP = +INF; DMPS.L = DMPS0;
 IADJ.FX       = IADJSIM(SIMCUR);
 INVSHR.LO = -INF; INVSHR.UP = +INF; INVSHR.L = INVSHR0;
*Fixed government demand quantity adjustment factors
*Flexible absorption share for government demand
 GADJ.FX    = GADJSIM(SIMCUR);
 GOVSHR.LO = -INF; GOVSHR.UP = +INF; GOVSHR.L = GOVSHR0;
 );

IF(SICLOS(SIMCUR) EQ 2,
*Investment-driven savings
*Scaled MPS for selected institutions
*Fixed investment demand quantity adjustment factors
*Flexible absorption shares for investment demand
 MPSADJ.LO = -INF; MPSADJ.UP = +INF; MPSADJ.L = MPSADJ0;
 DMPS.FX = DMPS0;
 IADJ.FX = IADJSIM(SIMCUR);
 INVSHR.LO = -INF; INVSHR.UP = +INF; INVSHR.L = INVSHR0;
*Fixed government demand quantity adjustment factors
*Flexible absorption share for government demand
 GADJ.FX    = GADJSIM(SIMCUR);
 GOVSHR.LO = -INF; GOVSHR.UP = +INF; GOVSHR.L = GOVSHR0;
 );

IF(SICLOS(SIMCUR) EQ 3,
*Savings-driven investment
*Fixed marginal savings propensities
*Flexible investment demand quantity adjustment factors
*Flexible absorption shares for investment demand
 MPSADJ.FX = MPSADJSIM(SIMCUR);
 DMPS.FX = DMPS0;
 IADJ.LO = -INF; IADJ.UP = +INF;  IADJ.L = IADJSIM(SIMCUR);
 INVSHR.LO = -INF; INVSHR.UP = +INF; INVSHR.L = INVSHR0;
*Fixed government demand quantity adjustment factors
*Flexible absorption share for government demand
 GADJ.FX    = GADJSIM(SIMCUR);
 GOVSHR.LO = -INF; GOVSHR.UP = +INF; GOVSHR.L = GOVSHR0;
 );

IF(SICLOS(SIMCUR) EQ 4,
*Balanced closure.
*Uniform MPS rate point change for selected ins
*Flexible investment demand quantity adjustment factors
*Fixed absorption shares for investment demand
 MPSADJ.FX = MPSADJSIM(SIMCUR);
 DMPS.LO = -INF; DMPS.UP = +INF; DMPS.L = DMPS0;
 IADJ.LO = -INF; IADJ.UP = +INF;  IADJ.L = IADJSIM(SIMCUR);
 INVSHR.FX = INVSHR0;
*Flexible government demand quantity adjustment factors
*Fixed absorption share for government demand
 GADJ.LO = -INF; GADJ.UP = +INF;  GADJ.L = GADJSIM(SIMCUR);
 GOVSHR.FX = GOVSHR0;
 );

IF(SICLOS(SIMCUR) EQ 5,
*Balanced closure.
*Scaled MPS for selected institutions
*Flexible investment demand quantity adjustment factors
*Fixed absorption shares for investment demand
 MPSADJ.LO = -INF; MPSADJ.UP = +INF; MPSADJ.L = MPSADJSIM(SIMCUR);
 DMPS.FX = DMPS0;
 IADJ.LO = -INF; IADJ.UP = +INF;  IADJ.L = IADJSIM(SIMCUR);
 INVSHR.FX = INVSHR0;
*Flexible government demand quantity adjustment factors
*Fixed absorption share for government demand
 GADJ.LO = -INF; GADJ.UP = +INF;  GADJ.L = GADJSIM(SIMCUR);
 GOVSHR.FX = GOVSHR0;
 );

*-------------

IF(GOVCLOS(SIMCUR) EQ 1,
*Fixed direct tax rates
*Flexible government savings
 TINSADJ.FX = TINSADJSIM(SIMCUR);
 DTINS.FX = DTINS0;
 GSAV.LO = -INF; GSAV.UP = +INF; GSAV.L = GSAVSIM(SIMCUR);
 );

IF(GOVCLOS(SIMCUR) EQ 2,
*Uniform direct tax rate point change for selected institutions
*Fixed government savings
 TINSADJ.FX = TINSADJSIM(SIMCUR);
 DTINS.LO = -INF; DTINS.UP = +INF; DTINS.L = DTINS0;
 GSAV.FX = GSAVSIM(SIMCUR);
 );

IF(GOVCLOS(SIMCUR) EQ 3,
*Scaled direct tax rates for selected institutions
*Fixed government savings
 TINSADJ.LO = -INF; TINSADJ.UP = +INF; TINSADJ.L = TINSADJSIM(SIMCUR);
 DTINS.FX = DTINS0;
 GSAV.FX = GSAVSIM(SIMCUR);
 );

IF(GOVCLOS(SIMCUR) EQ 4,
*Scaled direct tax rates for selected institutions
*Fixed government savings
 GADJ.LO = -INF; GADJ.UP = +INF;  GADJ.L = GADJSIM(SIMCUR);
 TINSADJ.FX = TINSADJSIM(SIMCUR);
 DTINS.FX = DTINS0;
 GSAV.FX = GSAVSIM(SIMCUR);
 );

*-------------

IF(ROWCLOS(SIMCUR) EQ 1,
*Fixed foreign savings -- flexible exchange rate
 FSAV.FX = FSAVSIM(SIMCUR);
 EXR.LO  = -INF; EXR.UP  = +INF; EXR.L   = EXRSIM(SIMCUR);
 );

IF(ROWCLOS(SIMCUR) EQ 2,
*Fixed exchange rate -- flexible foreign savings
 EXR.FX = EXRSIM(SIMCUR);
 FSAV.LO = -INF; FSAV.UP = +INF; FSAV.L = FSAVSIM(SIMCUR);
 );

IF(ROWCLOS(SIMCUR) EQ 3,
*Fixed exchange rate -- flexible foreign savings
 EXR.FX = EXRSIM(SIMCUR);
 FSAV.FX = FSAVSIM(SIMCUR);
 );

*----------------------------------------------------------------------
*Loop over all factors for alternative factor-market closures.
LOOP(F,

*---
*Factors with FMOBFE(F,SIMCUR) = 1 are fully employed and mobile between
*activities. WF(F) is the market-clearing variable each factor.

IF(FMOBFE(F,SIMCUR) EQ 1,

 WFDIST.FX(F,A)      = WFDIST0(F,A);
 QFS.FX(F)           = QFSSIM(F,SIMCUR);

 WF.LO(F)            = -INF;
 WF.UP(F)            = +INF;
 WF.L(F)             = WFSIM(F,SIMCUR);

 QF.LO(F,A)$QF0(F,A) = -INF;
 QF.UP(F,A)$QF0(F,A) = +INF;
 QF.L(F,A)$QF0(F,A)  = QF0(F,A); );

*---
*Factors with FACTFE(F,SIMCUR) = 1 are fully employed and
*activity-specific. WFDIST(F,A) is the clearing variable, one for each
*segment of the factor market.

IF(FACTFE(F,SIMCUR) EQ 1,

 WF.FX(F)                = WFSIM(F,SIMCUR);
 QF.FX(F,A)              = QF0(F,A);

 WFDIST.LO(F,A)$QF0(F,A) = -INF;
 WFDIST.UP(F,A)$QF0(F,A) = +INF;
 WFDIST.L(F,A)$QF0(F,A)  = WFDIST0(F,A);

 QFS.LO(F)               = -INF;
 QFS.UP(F)               = +INF;
 QFS.L(F)                = QFSSIM(F,SIMCUR) );

*---
*Factors with FMOBUE(F,SIMCUR) = 1 are unemployed and mobile. For each
*activity, the wage, WFDIST(F,A)*WF(F), is fixed. QFS(F) is the
*market-clearing variable for the unified labor market.

IF(FMOBUE(F,SIMCUR) EQ 1,

 WFDIST.FX(F,A)      = WFDIST0(F,A);
 WF.FX(F)            = WFSIM(F,SIMCUR);

 QF.LO(F,A)$QF0(F,A) = -INF;
 QF.UP(F,A)$QF0(F,A) = +INF;
 QF.L(F,A)$QF0(F,A)  = QF0(F,A);

 QFS.LO(F)           = -INF;
 QFS.UP(F)           = +INF;
 QFS.L(F)            = QFSSIM(F,SIMCUR); );
*---
 );

*For nested factors
LOOP(F$FA(F),
 QFS.LO(F)  = -INF ;
 QFS.UP(F)  = +INF ;
 WF.LO(F) = -INF;
 WF.UP(F) = +INF;
 QF.LO(F,A)$QF0(F,A) = -INF;
 QF.UP(F,A)$QF0(F,A) = +INF;
 WFDIST.LO(F,A) = -INF;
 WFDIST.UP(F,A) = +INF;
);
*End loop for factor-market closures.

LOOP(A$AFIX(A,SIMCUR),
 QF.FX(FCAP,A)                 = QF0(FCAP,A);
 WFDIST.LO(FCAP,A)$QF0(FCAP,A) = -INF;
 WFDIST.UP(FCAP,A)$QF0(FCAP,A) = +INF;
 WFDIST.L(FCAP,A)$QF0(FCAP,A)  = WFDIST0(FCAP,A);
 QF.FX(FLND,A)                 = QF0(FLND,A);
 WFDIST.LO(FLND,A)$QF0(FLND,A) = -INF;
 WFDIST.UP(FLND,A)$QF0(FLND,A) = +INF;
 WFDIST.L(FLND,A)$QF0(FLND,A)  = WFDIST0(FLND,A);
);

*SOLVING

IF(SIMMCP(SIMCUR),
 SOLVE STANDCGE USING MCP;
ELSE
 SOLVE NLPCGE MINIMIZING WALRASSQR USING NLP;
 );

$BATINCLUDE includes\2REPLOOP.INC SIMCUR
);

*------------------------------------------------------------------
*7. COMPUTING PERCENTAGE CHANGE FOR REPORT PARAMETERS
*------------------------------------------------------------------

$INCLUDE includes\2REPPERC.INC

*8. CHECKING FOR ERRORS IN SOLUTION AND REPORT PARAMETERS

*If error in the negative price/quantity segment, one or more solution prices
*or quantities are negative.

NEGPWARN(C,SIM)$
 ((PDDX(C,SIM) LT 0) OR (PDSX(C,SIM) LT 0) OR
  (PEX(C,SIM)  LT 0) OR (PMX(C,SIM) LT 0)  OR
  (PQX(C,SIM) LT 0)  OR (PWEX(C,SIM) LT 0) OR
  (PWMX(C,SIM) LT 0) OR (PXX(C,SIM) LT 0) OR
  (SMIN(A, PXACX(A,C,SIM)) LT 0) )
  = 1/0;

NEGQWARN(C,SIM)$
  ((QDX(C,SIM) LT 0) OR (QEX(C,SIM)  LT 0) OR
  (QMX(C,SIM) LT 0)  OR (QQX(C,SIM) LT 0) OR
  (QEX(C,SIM) LT 0)  OR (QXX(C,SIM) LT 0) OR
  (SMIN(A, QXACX(A,C,SIM)) LT 0) )
  = 1/0;

NEGWFWARN(F,SIM)$
 ((WFX(F,SIM) LT 0) OR (SMIN(A, WFDISTX(F,A,SIM)) LT 0) )
  = 1/0;

NEGQFWARN(F,SIM)$
 ((QFSX(F,SIM) LT 0) OR (SMIN(A, QFX(F,A,SIM)) LT 0) )
  = 1/0;


*If error here, check displays of SAMBUDGAP and GDPGAP to find it and
*fix it.
 GAPWARN(SIM)
  $(SUM(SAC, SAMBUDGAP(SAC,'TOTAL',SIM)) + GDPGAP(SIM) GT 0.01) = 1/0;

*If error here, SOLVEREP reports illegal values.
 SOLVEWARN(SOLVEIND,MODTYPE,SIM)
  $(SOLVEREP(SOLVEIND,MODTYPE,SIM) GT SOLVEMAX(SOLVEIND,MODTYPE)) = 1/0;

*If error here, check displays of SAMBUDGAP for hints about the source
 WALRASWARN(SIM)$(ABS(WALRASX(SIM)) GT 0.001) = 1/0;

*If error here, check explanation above where ERRMPSEQ1 is declared.
 ERRMPSEQ1(INSDNG,SIM)$ERRMPSEQ1(INSDNG,SIM) = 1/0;

*------------------------------------------------------------------
*9. DISPLAYING REPORTS
*------------------------------------------------------------------

OPTION
 QFX:3:1:1    , QHX:3:1:1      , QHAX:3:2:1, QINTX:3:1:1  , WFAX:3:1:1
 WFAX:3:1:1   , WFDISTX:3:1:1  , YFX:3:1:1

 QFXP:3:1:1   , QHXP:3:1:1     , QHAXP:3:2:1, QINTXP:3:1:1, WFAXP:3:1:1
 WFAXP:3:1:1  , WFDISTXP:3:1:1 , YFXP:3:1:1

 SAMBUD:3:1:1 , SAMBUDP:3:1:1
 GDPTAB1:3:1:1, GDPTAB1P:3:1:1
 GDPTAB2:3:1:1, GDPTAB2P:3:1:1
 MACCLOS:0,     FACCLOS:0:1:1
 SOLVEREP:0:1:1
 ;


DISPLAY
*Values for all model variables
CPIX    , DPIX     , DMPSX    , DTINSX   , EGX      , EHX      , EXRX
FSAVX   , GADJX    , GOVSHRX  , GSAVX    , IADJX    , INVSHRX  , MPSX
MPSADJX , PAX      , PDDX     , PDSX     , PEX      , PINTAX   , PMX
PQX     , PVAX     , PWEX     , PWMX     , PXX      , PXACX    , QAX
QDX     , QEX      , QFX      , QFSX     , QGX      , QHX      , QHAX
QINTX   , QINTAX   , QINVX    , QMX      , QQX      , QTX      , QVAX
QXX     , QXACX    , TABSX    , TINSX    , TINSADJX , TRIIX    , WALRASX
WFX     , WFDISTX  , YFX      , YGX      , YIFX     , YIX

*% change for all model variables
CPIXP   , DPIXP    , EGXP     , EHXP     , EXRXP    , FSAVXP   , GADJXP
GOVSHRXP, GSAVXP   , IADJXP   , INVSHRXP , MPSXP    , PAXP     , PDDXP
PDSXP   , PEXP     , PINTAXP  , PMXP     , PQXP     , PVAXP    , PWEXP
PWMXP   , PXXP     , PXACXP   , QAXP     , QDXP     , QEXP     , QFXP
QFSXP   , QGXP     , QHXP     , QHAXP    , QINTXP   , QINTAXP  , QINVXP
QMXP    , QQXP     , QTXP     , QVAXP    , QXXP     , QXACXP   , TABSXP
TINSXP  , TRIIXP   , WFAXP    , WFXP     , WFDISTXP , YFXP     , YGXP
YIFXP   , YIXP

*Other displays
SAMBUD  ,  SAMBUDP , GDPTAB1  , GDPTAB1P , GDPTAB2  , GDPTAB2P

"The parameters MACCLOS and FACCLOS, and the sets ACES and ALEO"
"indicate the values for model features with user choice."

 MACCLOS
 "For GOV"
 "  1 -> gov savings are flexible, dir tax rate is fixed"
 "  2 -> gov savings are fixed"
 "       uniform dir tax rate point chng for selected ins"
 "  3 -> gov savings are fixed"
 "       scaled dir tax rate for selected institutions"
 ""
 "For ROW"
 "  1 -> exch rate is flexible, for savings are fixed"
 "  2 -> exch rate is fixed   , for savings are flexible"
 ""
 "For SAVINV"
  "1 -> inv-driven sav -- uniform mps rate point chng for selected ins"
  "2 -> inv-driven sav -- scaled mps for selected ins"
  "3 -> inv is sav-driven"
  "4 -> inv is fixed abs share - uniform mps rate chng (cf. 1)"
  "5 -> inv is fixed abs share - scaled mps (cf. 2)"
 ""
 FACCLOS
 "FMOBFE = 1 -> mobile and fully employed"
 "FACTFE = 1 -> activity-specific and fully employed"
 "FMOBUE = 1 -> mobile and unemployed"

 ACES
 "Activities in ACES have a CES aggregation function at the top of"
 "the technology nest."

 ALEO
 "Activities in ALEO have a Leontief aggregation function at the top of"
 "the technology nest."

 SIMBASINIT
 "For simulations in SIMBASINIT, the variables are initialized at"
 "base levels."

SAMBUDGAP , GDPGAP  ,

SOLVEREP

"MODEL STATUS:"
" 1 OPTIMAL"
" 2 LOCALLY OPTIMAL"
" 3 UNBOUNDED"
" 4 INFEASIBLE"
" 5 LOCALLY INFEASIBLE"
" 6 INTERMEDIATE INFEASIBLE"
" 7 INTERMEDIATE NON-OPTIMAL"
" 8 INTEGER SOLUTION"
" 9 INTERMEDIATE NON-INTEGER"
"10 INTEGER INFEASIBLE"
"11 (UNUSED)"
"12 ERROR UNKNOWN"
"13 ERROR NO SOLUTION"
""
"SOLVER STATUS:"
" 1 NORMAL COMPLETION"
" 2 ITERATION INTERRUPT"
" 3 RESOURCE INTERRUPT"
" 4 TERMINATED BY SOLVER"
" 5 EVALUATION ERROR LIMIT"
" 6 UNKNOWN"
" 7 (UNUSED)"
" 8 ERROR PREPROCESSOR ERROR"
" 9 ERROR SETUP FAILURE"
"10 ERROR SOLVER FAILURE"
"11 ERROR INTERNAL SOLVER ERROR"
"12 ERROR POST-PROCESSOR ERROR"
"13 ERROR SYSTEM FAILURE"
""
"NUM-REDEFEQ shows the number of redefined equations (should be zero)"
""
SOLVEWARN
"If error(s) (UNDF), one or more SOLVEREP values are illegal."
""
NEGPWARN, NEGQWARN, NEGWFWARN, NEGQFWARN
"Negative prices and quantities are economically illegal"
""
GAPWARN, WALRASWARN,
""
ERRMPSEQ1
"See the explanation where ERRMPSEQ1 is declared."
;

$INCLUDE includes\2REPSUM.INC
$INCLUDE includes\2REPORT.INC

*execute_unload "0vars.gdx" CPI0 DPI0 DMPS0 DTINS0 EG0 EH0 EXR0 FSAV0 GADJ0 GOVSHR0 GSAV0 IADJ0 INVSHR0 MPS0 MPSADJ0 PA0 PDD0 PDS0 PE0 PINTA0 PM0 PQ0 PVA0 PWE0 PWM0 PX0 PXAC0 QA0 QD0 QE0 QF0 QFS0 QG0 QH0 QHA0 QINT0 QINTA0 QINV0 QM0 QQ0 QT0 QVA0 QX0 QXAC0 TABS0 TINS0 TINSADJ0 TRII0 WALRAS0 WF0 WFDIST0 YF0 YG0 YIF0 YI0 CPIX DPIX DMPSX DTINSX EGX EHX EXRX FSAVX GADJX GOVSHRX GSAVX IADJX INVSHRX MPSX MPSADJX PAX PDDX PDSX PEX PINTAX PMX PQX PVAX PWEX PWMX PXX PXACX QAX QDX QEX QFX QFSX QGX QHX QHAX QINTX QINTAX QINVX QMX QQX QTX QVAX QXX QXACX TABSX TINSX TINSADJX TRIIX WALRASX WFX WFDISTX YFX YGX YIFX YIX CPIXP DPIXP EGXP EHXP EXRXP FSAVXP GADJXP GOVSHRXP GSAVXP IADJXP INVSHRXP MPSXP PAXP PDDXP PDSXP PEXP PINTAXP PMXP PQXP PVAXP PWEXP PWMXP PXXP PXACXP QAXP QDXP QEXP QFXP QFSXP QGXP QHXP QHAXP QINTXP QINTAXP QINVXP QMXP QQXP QTXP QVAXP QXXP QXACXP TABSXP TINSXP TRIIXP WFAXP WFXP WFDISTXP YFXP YGXP YIFXP YIXP
*execute_unload "0tabs.gdx" STRUCBASE MACROTAB GDPTAB1 GDPTAB1P GDPTAB2 GDPTAB2P QHTAB EVTAB YFTAB QATAB PATAB SVALUE SGROWTH SSHARE DVALUE DGROWTH DSHARE QETAB QMTAB PXTAB PETAB PMTAB PQTAB PWETAB PWMTAB SAMBUD SAMBUDP GDPTAB1 GDPTAB1P GDPTAB2 GDPTAB2P NUMERAIRE SICLOS GOVCLOS ROWCLOS
