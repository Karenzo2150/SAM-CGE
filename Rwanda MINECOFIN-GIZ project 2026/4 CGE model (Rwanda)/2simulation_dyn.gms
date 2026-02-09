$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2: Recursive dynamic simulation file
 This file (2simulation_dyn.gms) runs dynamic model simulations and generates standard reporting results.
 
SECTIONS:
 2.1  Define simulations using standard data imported from Excel
 2.2  Optional: Define own simulations without using standard Excel 
 2.3  Declare reporting parameters
 2.4  Loop: Solve model for active simulations
 2.5  Generate standard reporting outputs 
$offtext


*------------------------------------------------------------------
*2.1 Define simulations using standard data imported from Excel
*------------------------------------------------------------------

*Load simulation names, shocks, and closures and calibrate simulation parameters
$include includes\dynamic\dyn_shocks.inc


*------------------------------------------------------------------
*2.2 Optional: Define own simulations without using standard Excel 
*------------------------------------------------------------------



*------------------------------------------------------------------
*2.3 Declare reporting parameters
*------------------------------------------------------------------

*Setup reporting parameters 
$include includes\dynamic\dyn_repsetup.inc


*------------------------------------------------------------------
*2.4 Loop: Solve model for active simulations
*------------------------------------------------------------------

LOOP((SIMC,TC),

*Base year: Initialize variables and parameters
IF(T1(TC),
$include includes\dynamic\dyn_varinit.inc
);

*Non-base year: Impose shocks on the model
IF(NOT T1(TC),

*--- Exogenous non-closure-related shocks ---

*  World prices
 pwe(C) = PWESIM(C,SIMC,TC);
 pwm(C) = PWMSIM(C,SIMC,TC);

*  Total factor productivity (TFP)
 alphava(A) = ALPHAVASIM(A,SIMC,TC);

*  Factor-specific productivity 
 alphaf(F,A) = ALPHAFSIM(F,A,SIMC,TC);

*  Transaction cost margins
 icd(C,CP) = ICDSIM(C,CP,SIMC,TC);
 ice(C,CP) = ICESIM(C,CP,SIMC,TC);
 icm(C,CP) = ICMSIM(C,CP,SIMC,TC);

*  Transfers from factors to institutions, including rest of world
 shif(INS,F) = SHIFSIM(INS,F,SIMC,TC);

*  Transfers from domestic nongovernment institutions to government and rest of world
 shii(INS,INSDNG) = SHIISIM(INS,INSDNG,SIMC,TC);

*  Transfers from government and rest of world 
 trnsf(F,INS)    = TRNSFSIM(F,INS,SIMC,TC);
 trnsi(INS,INSP) = TRNSISIM(INS,INSP,SIMC,TC);

*  Savings and tax rates (for institution, activity and commodity-specific shocks)
 mpsbar(H) = MPSSIM(H,SIMC,TC);
 tabar(A)  = TASIM(A,SIMC,TC);
 tebar(C)  = TESIM(C,SIMC,TC);
 tfbar(F)  = TFSIM(F,SIMC,TC);
 tibar(H)  = TISIM(H,SIMC,TC);
 tmbar(C)  = TMSIM(C,SIMC,TC);
 tqbar(C)  = TQSIM(C,SIMC,TC);
 tvbar(A)  = TVSIM(A,SIMC,TC);

*--- Endogenous capital accumulation and allocation ---

*Total new capital stock avaiable for allocation, and new capital net of activities with exogenous capital growth 
 QKAP(SIMC,TC) = alphai * SUM(CP, QINV.L(CP)*iwts(CP));
 QKAP_N(SIMC,TC) = QKAP(SIMC,TC) - SUM((FCAP,A)$AFIXCAP(A,SIMC), QFSIM(FCAP,A,SIMC,TC) - QF.L(FCAP,A));

*Current capital allocation shares 
 QKAP_S1(FCAP) = SUM(A$(NOT AFIXCAP(A,SIMC)), QF.L(FCAP,A)) / SUM((FCAPP,A)$(NOT AFIXCAP(A,SIMC)), QF.L(FCAPP,A));
 QKAP_S2(FCAP,A)$(NOT AFIXCAP(A,SIMC) AND QKAP_S1(FCAP)) = QF.L(FCAP,A) / SUM(AP$(NOT AFIXCAP(AP,SIMC)), QF.L(FCAP,AP));

*Relative profit rate diffdrentials
*  WF and WFDIST adjusted to exclude activities with exogenous capital growth 
 WF_ADJ(FCAP)$QKAP_S1(FCAP) = SUM(A$(NOT AFIXCAP(A,SIMC)), WF.L(FCAP) * WFDIST.L(FCAP,A) * QF.L(FCAP,A)) / SUM(A$(NOT AFIXCAP(A,SIMC)), QF.L(FCAP,A));
 WFDIST_ADJ(FCAP,A)$(NOT AFIXCAP(A,SIMC) AND WF_ADJ(FCAP)) = WF.L(FCAP)*WFDIST.L(FCAP,A) / WF_ADJ(FCAP);
*  Average rental on capital by type (across all activities) and on all capital 
 WF_K2(FCAP) = SUM(A$(NOT AFIXCAP(A,SIMC)), WF_ADJ(FCAP) * WFDIST_ADJ(FCAP,A) * QKAP_S2(FCAP,A));
 WF_K1 = SUM(FCAP, WF_K2(FCAP) * QKAP_S1(FCAP));
*  Ratio of sectoral to average rental by capital type
 WFDIST_K2(FCAP,A)$(NOT AFIXCAP(A,SIMC) AND WF_K2(FCAP)) = WF_ADJ(FCAP) * WFDIST_ADJ(FCAP,A) / WF_K2(FCAP);

*New capital allocation shares 
 QINV_1(FCAP) = QKAP_S1(FCAP) * (1 + betai1 * ((WF_K2(FCAP) - WF_K1) / WF_K1));
 QINV_2(FCAP,A)$(NOT AFIXCAP(A,SIMC)) = QKAP_S2(FCAP,A) * (1 + betai2 * (WFDIST_K2(FCAP,A) - 1));
 
*Final capital stock growth rates
*  Newly allocated capital quantities 
 QKAP_DS(FCAP) = QINV_1(FCAP) * QKAP_N(SIMC,TC);
 QKAP_D(FCAP,A)$(NOT AFIXCAP(A,SIMC)) = QINV_2(FCAP,A) * QKAP_DS(FCAP);
*  Growth rates for endogenous capital growth activities
 QKAP_RS(FCAP)$QFS0(FCAP)  = QKAP_DS(FCAP) / QFS.L(FCAP) - SUM(A, DRATESIM(SIMC,TC) * QF.L(FCAP,A) / SUM(AP, QF.L(FCAP,AP)));
 QKAP_R(FCAP,A)$(NOT AFIXCAP(A,SIMC) AND QF0(FCAP,A)) = QKAP_D(FCAP,A) / QF.L(FCAP,A) - DRATESIM(SIMC,TC);
*  Growth rates for exogenous capital growth activities
 QKAP_R(FCAP,A)$(AFIXCAP(A,SIMC) AND QF0(FCAP,A)) = ASIMA(A,'FIXCAP',SIMC,TC)/100;

*Update factor supply and demand simulation parameters (used in closure file)
 QFSIM(FCAP,A,SIMC,TC) = QFSIM(FCAP,A,SIMC,TC-1) * (1 + QKAP_R(FCAP,A));
 QFSSIM(FCAP,SIMC,TC)  = SUM(A, QFSIM(FCAP,A,SIMC,TC));
 
*--- Apply closure rules, closure-related shocks, and fix unused variables ---

);

$include includes\dynamic\dyn_closures.inc

*--- Solve model ---

OPTIONS ITERLIM = 1000, LIMROW = 1000, LIMCOL = 0, SOLPRINT=ON, MCP=PATH, NLP=CONOPT CNS=CONOPT;

 STANDCGE.HOLDFIXED  = 1;
 STANDCGE.TOLINFREP  = 0.001;
 STANDCGE.MCPRHOLDFX = 1;
 STANDCGE.SCALEOPT   = 1;

 SOLVE STANDCGE USING MCP;


*--- Save results between solves ---

$batinclude includes\dynamic\dyn_reploop.inc SIMC TC

);


*------------------------------------------------------------------
*2.5 Generate standard reporting outputs 
*------------------------------------------------------------------

$include includes\dynamic\dyn_report.inc 