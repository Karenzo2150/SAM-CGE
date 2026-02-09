$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2: Static simulation file
 This file (2simulation_static.gms) runs static model simulations and generates standard reporting results.
 
SECTIONS:
 2.1  Define simulations using standard data imported from Excel
 2.2  Optional: Define simulations using non-standard GAMS code 
 2.3  Declare reporting parameters
 2.4  Loop: Solve model for active simulations
 2.5  Generate standard reporting outputs 
$offtext


*------------------------------------------------------------------
*2.1 Define simulations using standard data imported from Excel
*------------------------------------------------------------------

*Load simulation names, shocks, and closures and calibrate simulation parameters
$include includes\static\stat_shocks.inc


*------------------------------------------------------------------
*2.2 Optional: Define simulations using non-standard GAMS code
*------------------------------------------------------------------





*------------------------------------------------------------------
*2.3 Declare reporting parameters
*------------------------------------------------------------------

*Setup reporting parameters 
$include includes\static\stat_repsetup.inc


*------------------------------------------------------------------
*2.4 Loop: Solve model for active simulations
*------------------------------------------------------------------

LOOP(SIMC,

*--- Initialize variables and parameters ---

$include includes\static\stat_varinit.inc

*--- Impose non-closure-related shocks to base model ---

*  World prices
 pwe(C) = PWESIM(C,SIMC);
 pwm(C) = PWMSIM(C,SIMC);

*  Total factor productivity (TFP)
 alphava(A) = ALPHAVASIM(A,SIMC);
 
*  Factor-specific productivity 
 alphaf(F,A) = ALPHAFSIM(F,A,SIMC);

*  Transaction cost margins
 icd(C,CP) = ICDSIM(C,CP,SIMC);
 ice(C,CP) = ICESIM(C,CP,SIMC);
 icm(C,CP) = ICMSIM(C,CP,SIMC);

*  Transfers from factors to institutions, including rest of world
 shif(INS,F) = SHIFSIM(INS,F,SIMC);

*  Transfers from domestic nongovernment institutions to government and rest of world
 shii(INS,INSDNG) = SHIISIM(INS,INSDNG,SIMC);

*  Transfers from government and rest of world 
 trnsf(F,INS)    = TRNSFSIM(F,INS,SIMC);
 trnsi(INS,INSP) = TRNSISIM(INS,INSP,SIMC);
 
*  Savings and tax rates (for institution, activity and commodity-specific shocks)
 mpsbar(H) = MPSSIM(H,SIMC);
 tabar(A)  = TASIM(A,SIMC);
 tebar(C)  = TESIM(C,SIMC);
 tfbar(F)  = TFSIM(F,SIMC);
 tibar(H)  = TISIM(H,SIMC);
 tmbar(C)  = TMSIM(C,SIMC);
 tqbar(C)  = TQSIM(C,SIMC);
 tvbar(A)  = TVSIM(A,SIMC);
 
*--- Apply closure rules, closure-related shocks, and fix unused variables ---

$include includes\static\stat_closures.inc

*--- Solve model ---

OPTIONS ITERLIM = 1000, LIMROW = 1000, LIMCOL = 0, SOLPRINT=ON, MCP=PATH, NLP=CONOPT CNS=CONOPT;

 STANDCGE.HOLDFIXED  = 1;
 STANDCGE.TOLINFREP  = 0.001;
 STANDCGE.MCPRHOLDFX = 1;
 STANDCGE.SCALEOPT   = 1;

 SOLVE STANDCGE USING MCP;

*--- Save results between solves ---

$batinclude includes\static\stat_reploop.inc SIMC

);


*------------------------------------------------------------------
*2.5 Generate standard reporting outputs 
*------------------------------------------------------------------

$include includes\static\stat_report.inc 
