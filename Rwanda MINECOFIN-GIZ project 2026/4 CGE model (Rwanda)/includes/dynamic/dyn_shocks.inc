$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2.1: Define simulations using standard data imported from Excel
 This include file (includes\2dynamic_shocks.inc) imports country simulation data from the Excel selected by
 the user (dynsim%dataext%.xlsx) and calibrates the simulation shock parameters and closure rules.

SECTIONS:
 2.1.1  Import simulation data from Excel
 2.1.2  Define closure parameters
 2.1.3  Define shock parameters
 2.1.4  Capital accumulation parameters
$offtext


*------------------------------------------------------------------
*2.1.1  Import simulation data from Excel
*------------------------------------------------------------------

$ontext
 This section imports the simulation data from Excel, where each simulation's data is entered on separate worksheets. These are combined
 into aggregate parameters starting with "A". Shock values are stored in parameters starting with "ASIM". For many of the parameters,
 the user must decide if the shock is multiplicative or additive (e.g., should a tax rate increase by 10% or 10%-points?). This choice
 is stored in the parameters starting "ATYP".  
$offtext

SET
 SIM                    simulations 
 SIMC(SIM)              current simulations
 SIMNB(SIM)             all simulations except BASE
 SIMNUM                 simulation numbers (used for shock aggregation loop)    / 1*15 /
 T                      time periods (years)
 TC(T)                  current time periods (years)
 T1(T)                  first time period (year)
 TN(T)                  final active time period (year)
 MCLOSEAC               macro closure dimensions        / numeraire, savings-investment, current-account, government-account, factors /
 SIMAC                  simulation data dimesnions      / start, end, alphaf, alphava, drate, exr, fixcap, fixlnd, fsav, gadj, govshr, gsav, iadj, icd, ice, icm, invshr, mps, pop, pwe, pwm, qfs, save, shk, ta, tax, te, tf, ti, tm, tq, trfg, trfw, trtg, trtw, tv, type, wf /
 SIMAC2(SIMAC)          simulation data dimesnions      / alphava, drate, exr, fixcap, fixlnd, fsav, gadj, govshr, gsav, iadj, icd, ice, icm, invshr, mps, pop, pwe, pwm, qfs, shk, ta, te, tf, ti, tm, tq, trfg, trfw, trtg, trtw, tv, type, wf /
 SIMACC(SIMAC)          simulation data dimesnions      / pwe, pwm, te, tm, tq, ice, icm, icd /
 SIMACA(SIMAC)          simulation data dimesnions      / alphava, ta, tv /
 SIMACF(SIMAC)          simulation data dimesnions      / wf, qfs, alphaf, tf, trtg, trtw, trfg, trfw /
 SIMACH(SIMAC)          simulation data dimesnions      / pop, mps, ti, trtg, trtw, trfg, trfw /
 SIMACS(SIMAC)          simulation data dimesnions      / exr, fsav, iadj, invshr, mps, gsav, gadj, govshr, te, tm, tq, ta, tv, tf, ti, drate /
 SHKAREA                shock areas in model            / com, act, fac, hhd, sca /
*Time periods for shocks on commodities, activities, factors, households, and scalars
 TIM1C(SIMAC,*,*), TIM2C(SIMAC,*,*), TIM3C(SIMAC,*,*), TIM4C(SIMAC,*,*), TIM5C(SIMAC,*,*), TIM6C(SIMAC,*,*), TIM7C(SIMAC,*,*), TIM8C(SIMAC,*,*), TIM9C(SIMAC,*,*), TIM10C(SIMAC,*,*), TIM11C(SIMAC,*,*), TIM12C(SIMAC,*,*), TIM13C(SIMAC,*,*), TIM14C(SIMAC,*,*), TIM15C(SIMAC,*,*)
 TIM1A(SIMAC,*,*), TIM2A(SIMAC,*,*), TIM3A(SIMAC,*,*), TIM4A(SIMAC,*,*), TIM5A(SIMAC,*,*), TIM6A(SIMAC,*,*), TIM7A(SIMAC,*,*), TIM8A(SIMAC,*,*), TIM9A(SIMAC,*,*), TIM10A(SIMAC,*,*), TIM11A(SIMAC,*,*), TIM12A(SIMAC,*,*), TIM13A(SIMAC,*,*), TIM14A(SIMAC,*,*), TIM15A(SIMAC,*,*)
 TIM1F(SIMAC,*,*), TIM2F(SIMAC,*,*), TIM3F(SIMAC,*,*), TIM4F(SIMAC,*,*), TIM5F(SIMAC,*,*), TIM6F(SIMAC,*,*), TIM7F(SIMAC,*,*), TIM8F(SIMAC,*,*), TIM9F(SIMAC,*,*), TIM10F(SIMAC,*,*), TIM11F(SIMAC,*,*), TIM12F(SIMAC,*,*), TIM13F(SIMAC,*,*), TIM14F(SIMAC,*,*), TIM15F(SIMAC,*,*)
 TIM1H(SIMAC,*,*), TIM2H(SIMAC,*,*), TIM3H(SIMAC,*,*), TIM4H(SIMAC,*,*), TIM5H(SIMAC,*,*), TIM6H(SIMAC,*,*), TIM7H(SIMAC,*,*), TIM8H(SIMAC,*,*), TIM9H(SIMAC,*,*), TIM10H(SIMAC,*,*), TIM11H(SIMAC,*,*), TIM12H(SIMAC,*,*), TIM13H(SIMAC,*,*), TIM14H(SIMAC,*,*), TIM15H(SIMAC,*,*)
 TIM1S(SIMAC,*,*), TIM2S(SIMAC,*,*), TIM3S(SIMAC,*,*), TIM4S(SIMAC,*,*), TIM5S(SIMAC,*,*), TIM6S(SIMAC,*,*), TIM7S(SIMAC,*,*), TIM8S(SIMAC,*,*), TIM9S(SIMAC,*,*), TIM10S(SIMAC,*,*), TIM11S(SIMAC,*,*), TIM12S(SIMAC,*,*), TIM13S(SIMAC,*,*), TIM14S(SIMAC,*,*), TIM15S(SIMAC,*,*)
;

ALIAS (T,TP,TPP), (TC,TCP), (FCAP,FCAPP);

PARAMETER
 TNUM                  number of years in active time period set
*Imported simulation names and closures choices
 ACTIVE(SIM)            active simulations
 MCLOSE(MCLOSEAC,SIM)   chosen macro closures 
 FCLOSE(F,SIM)          chosen factor closures
*Shocks on commodities, activities, factors, and households, plus scalar shocks
 SIMBC(C,SIMAC),     SIM1C(C,SIMAC),     SIM2C(C,SIMAC),     SIM3C(C,SIMAC),     SIM4C(C,SIMAC),     SIM5C(C,SIMAC),     SIM6C(C,SIMAC),     SIM7C(C,SIMAC),     SIM8C(C,SIMAC),     SIM9C(C,SIMAC),     SIM10C(C,SIMAC),     SIM11C(C,SIMAC),     SIM12C(C,SIMAC),     SIM13C(C,SIMAC),     SIM14C(C,SIMAC),     SIM15C(C,SIMAC)
 SIMBA(A,SIMAC),     SIM1A(A,SIMAC),     SIM2A(A,SIMAC),     SIM3A(A,SIMAC),     SIM4A(A,SIMAC),     SIM5A(A,SIMAC),     SIM6A(A,SIMAC),     SIM7A(A,SIMAC),     SIM8A(A,SIMAC),     SIM9A(A,SIMAC),     SIM10A(A,SIMAC),     SIM11A(A,SIMAC),     SIM12A(A,SIMAC),     SIM13A(A,SIMAC),     SIM14A(A,SIMAC),     SIM15A(A,SIMAC)
 SIMBF(F,SIMAC),     SIM1F(F,SIMAC),     SIM2F(F,SIMAC),     SIM3F(F,SIMAC),     SIM4F(F,SIMAC),     SIM5F(F,SIMAC),     SIM6F(F,SIMAC),     SIM7F(F,SIMAC),     SIM8F(F,SIMAC),     SIM9F(F,SIMAC),     SIM10F(F,SIMAC),     SIM11F(F,SIMAC),     SIM12F(F,SIMAC),     SIM13F(F,SIMAC),     SIM14F(F,SIMAC),     SIM15F(F,SIMAC)
 SIMBH(INS,SIMAC),   SIM1H(INS,SIMAC),   SIM2H(INS,SIMAC),   SIM3H(INS,SIMAC),   SIM4H(INS,SIMAC),   SIM5H(INS,SIMAC),   SIM6H(INS,SIMAC),   SIM7H(INS,SIMAC),   SIM8H(INS,SIMAC),   SIM9H(INS,SIMAC),   SIM10H(INS,SIMAC),   SIM11H(INS,SIMAC),   SIM12H(INS,SIMAC),   SIM13H(INS,SIMAC),   SIM14H(INS,SIMAC),   SIM15H(INS,SIMAC)
 SIMBS(SIMAC,SIMAC), SIM1S(SIMAC,SIMAC), SIM2S(SIMAC,SIMAC), SIM3S(SIMAC,SIMAC), SIM4S(SIMAC,SIMAC), SIM5S(SIMAC,SIMAC), SIM6S(SIMAC,SIMAC), SIM7S(SIMAC,SIMAC), SIM8S(SIMAC,SIMAC), SIM9S(SIMAC,SIMAC), SIM10S(SIMAC,SIMAC), SIM11S(SIMAC,SIMAC), SIM12S(SIMAC,SIMAC), SIM13S(SIMAC,SIMAC), SIM14S(SIMAC,SIMAC), SIM15S(SIMAC,SIMAC)
 TYP1C(SIMAC),       TYP2C(SIMAC),       TYP3C(SIMAC),       TYP4C(SIMAC),       TYP5C(SIMAC),       TYP6C(SIMAC),       TYP7C(SIMAC),       TYP8C(SIMAC),       TYP9C(SIMAC),       TYP10C(SIMAC),       TYP11C(SIMAC),       TYP12C(SIMAC),       TYP13C(SIMAC),       TYP14C(SIMAC),       TYP15C(SIMAC)
 TYP1A(SIMAC),       TYP2A(SIMAC),       TYP3A(SIMAC),       TYP4A(SIMAC),       TYP5A(SIMAC),       TYP6A(SIMAC),       TYP7A(SIMAC),       TYP8A(SIMAC),       TYP9A(SIMAC),       TYP10A(SIMAC),       TYP11A(SIMAC),       TYP12A(SIMAC),       TYP13A(SIMAC),       TYP14A(SIMAC),       TYP15A(SIMAC)
 TYP1F(SIMAC),       TYP2F(SIMAC),       TYP3F(SIMAC),       TYP4F(SIMAC),       TYP5F(SIMAC),       TYP6F(SIMAC),       TYP7F(SIMAC),       TYP8F(SIMAC),       TYP9F(SIMAC),       TYP10F(SIMAC),       TYP11F(SIMAC),       TYP12F(SIMAC),       TYP13F(SIMAC),       TYP14F(SIMAC),       TYP15F(SIMAC)
 TYP1H(SIMAC),       TYP2H(SIMAC),       TYP3H(SIMAC),       TYP4H(SIMAC),       TYP5H(SIMAC),       TYP6H(SIMAC),       TYP7H(SIMAC),       TYP8H(SIMAC),       TYP9H(SIMAC),       TYP10H(SIMAC),       TYP11H(SIMAC),       TYP12H(SIMAC),       TYP13H(SIMAC),       TYP14H(SIMAC),       TYP15H(SIMAC)
*Aggregated shock parameters
 ASIMC(C,SIMAC,SIM,T)
 ASIMA(A,SIMAC,SIM,T)
 ASIMF(F,SIMAC,SIM,T)
 ASIMH(INS,SIMAC,SIM,T)
 ASIMS(SIMAC,SIM,T)
 ATYPC(SIMAC,SIM)
 ATYPA(SIMAC,SIM)
 ATYPF(SIMAC,SIM)
 ATYPH(SIMAC,SIM)
 ATYPS(SIMAC,SIM)
;

*Read input data from excel file (dynsim%dataext%.xlsx)
$call "gdxxrw i=data\\%folder%\dynsim%dataext%.xlsx o=sims.gdx index=index!a5"
$gdxin sims.gdx
*Read sets and data
$load SIM T
$loaddc ACTIVE MCLOSE FCLOSE TC
$loaddc SIMBC SIMBA SIMBF SIMBH SIMBS
$loaddc SIM1C SIM2C SIM3C SIM4C SIM5C SIM6C SIM7C SIM8C SIM9C SIM10C SIM11C SIM12C SIM13C SIM14C SIM15C
$loaddc SIM1A SIM2A SIM3A SIM4A SIM5A SIM6A SIM7A SIM8A SIM9A SIM10A SIM11A SIM12A SIM13A SIM14A SIM15A
$loaddc SIM1F SIM2F SIM3F SIM4F SIM5F SIM6F SIM7F SIM8F SIM9F SIM10F SIM11F SIM12F SIM13F SIM14F SIM15F
$loaddc SIM1H SIM2H SIM3H SIM4H SIM5H SIM6H SIM7H SIM8H SIM9H SIM10H SIM11H SIM12H SIM13H SIM14H SIM15H
$loaddc SIM1S SIM2S SIM3S SIM4S SIM5S SIM6S SIM7S SIM8S SIM9S SIM10S SIM11S SIM12S SIM13S SIM14S SIM15S
$loaddc TYP1C TYP2C TYP3C TYP4C TYP5C TYP6C TYP7C TYP8C TYP9C TYP10C TYP11C TYP12C TYP13C TYP14C TYP15C
$loaddc TYP1A TYP2A TYP3A TYP4A TYP5A TYP6A TYP7A TYP8A TYP9A TYP10A TYP11A TYP12A TYP13A TYP14A TYP15A
$loaddc TYP1F TYP2F TYP3F TYP4F TYP5F TYP6F TYP7F TYP8F TYP9F TYP10F TYP11F TYP12F TYP13F TYP14F TYP15F
$loaddc TYP1H TYP2H TYP3H TYP4H TYP5H TYP6H TYP7H TYP8H TYP9H TYP10H TYP11H TYP12H TYP13H TYP14H TYP15H
$loaddc TIM1C TIM2C TIM3C TIM4C TIM5C TIM6C TIM7C TIM8C TIM9C TIM10C TIM11C TIM12C TIM13C TIM14C TIM15C
$loaddc TIM1A TIM2A TIM3A TIM4A TIM5A TIM6A TIM7A TIM8A TIM9A TIM10A TIM11A TIM12A TIM13A TIM14A TIM15A
$loaddc TIM1F TIM2F TIM3F TIM4F TIM5F TIM6F TIM7F TIM8F TIM9F TIM10F TIM11F TIM12F TIM13F TIM14F TIM15F
$loaddc TIM1H TIM2H TIM3H TIM4H TIM5H TIM6H TIM7H TIM8H TIM9H TIM10H TIM11H TIM12H TIM13H TIM14H TIM15H
$loaddc TIM1S TIM2S TIM3S TIM4S TIM5S TIM6S TIM7S TIM8S TIM9S TIM10S TIM11S TIM12S TIM13S TIM14S TIM15S
$gdxin

*Set active simulations (with base sim always active)
 SIMC(SIM)$(ACTIVE(SIM) NE 0) = YES;
 SIMC('BASE') = YES;
 SIMC('INIT') = NO;
 
*Set first and final time periods
 T1(TC)$(ORD(TC) EQ 1) = YES;
 TN(TC)$(ORD(TC) EQ SMAX(TCP, ORD(TCP))) = YES;
 
*Number of years in active time period set
 TNUM = SUM(T$TN(T), ORD(T)) - SUM(T$T1(T), ORD(T));
 
*All simulations except BASE
 SIMNB(SIMC)   = YES;
 SIMNB('BASE') = NO;
 
*Aggregate multiple imported parameters from each SIM worksheet into single parameters subcripted on SIM
$include includes\dynamic\dyn_process.inc 


*------------------------------------------------------------------
*2.1.2  Define closure parameters
*------------------------------------------------------------------

$ontext
 This section first checks that the user-selected closure choices imported from Excel are valid - if not, they are set to
 default values. Valid choices are then assigned to different closure parameters containing the rules for each simulation. 
$offtext

PARAMETER
*Closure parameters 
 NUMERAIRE(SIM)         numeraire
 SICLOSE(SIM)           savings-investment closures
 ROWCLOSE(SIM)          current account (rest of world) closures
 GOVCLOSE(SIM)          government account closures 
 FACCLOSE(F,SIM)        factor market closures
*Selecting which commodities, activities and institutions adjust under closure rules
 MPS01SIM(INS,SIM)      0-1 parameter for potential flexing of savings rates
 TA01SIM(A,SIM)         0-1 parameter for potential flexing of activity tax rates
 TE01SIM(C,SIM)         0-1 parameter for potential flexing of export tax rates
 TF01SIM(F,SIM)         0-1 parameter for potential flexing of factor tax rates
 TI01SIM(INS,SIM)       0-1 parameter for potential flexing of direct tax rates
 TM01SIM(C,SIM)         0-1 parameter for potential flexing of import tariff rates
 TQ01SIM(C,SIM)         0-1 parameter for potential flexing of sales tax rates
 TV01SIM(A,SIM)         0-1 parameter for potential flexing of value-added tax rates
*Fixed factors by activity
 AFIXCAP(A,SIM)         activities with fixed capital (even with general capital mobility)
 AFIXLND(A,SIM)         activities with fixed land (even with general land mobility)
;

TABLE CLOSBOUNDS(MCLOSEAC,*)   Closure bounds and default values
                        MIN MAX DEF
 NUMERAIRE              1   2   2
 SAVINGS-INVESTMENT     1   5   3
 CURRENT-ACCOUNT        1   2   1
 GOVERNMENT-ACCOUNT     1   15  1
 FACTORS                1   3   1
;
 
*For user-selected macro and factor closures outside of permissable bounds, set to default values
 MCLOSE(MCLOSEAC,SIM)$(MCLOSE(MCLOSEAC,SIM) LT CLOSBOUNDS(MCLOSEAC,'MIN') OR MCLOSE(MCLOSEAC,SIM) GT CLOSBOUNDS(MCLOSEAC,'MAX')) = CLOSBOUNDS(MCLOSEAC,'DEF');
 FCLOSE(F,SIM)$(FCLOSE(F,SIM) LT CLOSBOUNDS('FACTORS','MIN') OR FCLOSE(F,SIM) GT CLOSBOUNDS('FACTORS','MAX')) = CLOSBOUNDS('FACTORS','DEF');

*Set macro-closures to default values 
 NUMERAIRE(SIM) = CLOSBOUNDS('NUMERAIRE','DEF');           
 SICLOSE(SIM)   = CLOSBOUNDS('SAVINGS-INVESTMENT','DEF');     
 ROWCLOSE(SIM)  = CLOSBOUNDS('CURRENT-ACCOUNT','DEF');  
 GOVCLOSE(SIM)  = CLOSBOUNDS('GOVERNMENT-ACCOUNT','DEF');

*For non-base simulations, macro-closures are replaced with imported simulation data (if within max-min bounds)
 NUMERAIRE(SIM) = MCLOSE('NUMERAIRE',SIM);
 SICLOSE(SIM)   = MCLOSE('SAVINGS-INVESTMENT',SIM); 
 ROWCLOSE(SIM)  = MCLOSE('CURRENT-ACCOUNT',SIM);
 GOVCLOSE(SIM)  = MCLOSE('GOVERNMENT-ACCOUNT',SIM);
 
*For closures with flexible savings or tax rates, the default is that the rates of all domestic non-government institutions adjust.
 MPS01SIM(INS,SIM) = 1; 
 TI01SIM(INS,SIM)  = 1;
 TA01SIM(A,SIM)    = 1;
 TV01SIM(A,SIM)    = 1;
 TE01SIM(C,SIM)    = 1;
 TM01SIM(C,SIM)    = 1;
 TQ01SIM(C,SIM)    = 1;
 TF01SIM(F,SIM)    = 1;

*For non-base simulations, replace with zero if imported Excel data has value of 2 (i.e., exclude from shock or closure).
 MPS01SIM(INSDNG,SIMNB)$(SUM(T1, ASIMH(INSDNG,'SAVE',SIMNB,T1)) EQ 2) = 0;
 TI01SIM(INSDNG,SIMNB)$(SUM(T1, ASIMH(INSDNG,'TAX',SIMNB,T1)) EQ 2)   = 0;
 TA01SIM(A,SIMNB)$(SUM(T1, ASIMA(A,'TAX',SIMNB,T1)) EQ 2)             = 0;      
 TV01SIM(A,SIMNB)$(SUM(T1, ASIMA(A,'TAX',SIMNB,T1)) EQ 2)             = 0;
 TE01SIM(C,SIMNB)$(SUM(T1, ASIMC(C,'TAX',SIMNB,T1)) EQ 2)             = 0;      
 TM01SIM(C,SIMNB)$(SUM(T1, ASIMC(C,'TAX',SIMNB,T1)) EQ 2)             = 0;      
 TQ01SIM(C,SIMNB)$(SUM(T1, ASIMC(C,'TAX',SIMNB,T1)) EQ 2)             = 0;      
 TF01SIM(F,SIMNB)$(SUM(T1, ASIMF(F,'TAX',SIMNB,T1)) EQ 2)             = 0;      

*If savings or tax rates are excluded (fixed) for all activities, factors or instiutions, then generate an error.
*  Note: should rather choose a SI or GOV closure rule that fixes all savings or tax rates - also any closure that
*        assumes at least rates are flexible will no longer work.
 MPS01SIM(INSDNG,SIM)$(SUM(INSDNGP, MPS01SIM(INSDNGP,SIM)) EQ 0) = 1/0;
 TI01SIM(INSDNG,SIM)$(SUM(INSDNGP, TI01SIM(INSDNGP,SIM)) EQ 0)   = 1/0;
 TA01SIM(A,SIM)$(SUM(AP, TA01SIM(AP,SIM)) EQ 0)                  = 1/0;
 TV01SIM(A,SIM)$(SUM(AP, TV01SIM(AP,SIM)) EQ 0)                  = 1/0;
 TE01SIM(C,SIM)$(SUM(CP, TE01SIM(CP,SIM)) EQ 0)                  = 1/0;
 TM01SIM(C,SIM)$(SUM(CP, TM01SIM(CP,SIM)) EQ 0)                  = 1/0;
 TQ01SIM(C,SIM)$(SUM(CP, TQ01SIM(CP,SIM)) EQ 0)                  = 1/0;
 TF01SIM(F,SIM)$(SUM(FP, TF01SIM(FP,SIM)) EQ 0)                  = 1/0;

*Sectors with fixed capital stocks (if fixed in baseline then fixed in all simulations) 
 AFIXCAP(A,SIM) = NO;
 AFIXCAP(A,SIMC)$(SUM(TC, ASIMA(A,'FIXCAP','BASE',TC)) NE 0 OR SUM(TC, ASIMA(A,'FIXCAP',SIMC,TC)) NE 0) = YES;

*Sectors with fixed land stocks (if fixed in baseline then fixed in all simulations) 
 AFIXLND(A,SIM) = NO;
 AFIXLND(A,SIMC)$(SUM(TC, ASIMA(A,'FIXLND','BASE',TC)) NE 0 OR SUM(TC, ASIMA(A,'FIXLND',SIMC,TC)) NE 0) = YES;

*Set factor closures to default value (1 = fully employed and mobile across activities)
 FACCLOSE(F,SIM) = 1;

*For non-base simulations, replace with imported simulation data (if withint max-min bounds)
 FACCLOSE(F,SIM) = FCLOSE(F,SIM); 
 

*------------------------------------------------------------------
*2.1.3  Define shock parameters
*------------------------------------------------------------------

$ontext
 This section declares and defines a number of shock parameters that are used within the simulation loop to adjust the values
of parameters and exogenous variables in the base model. Shock parameters start with the variable or parameter name, followed
by "SIM". Default values for all shock parameters are base year values.
$offtext

PARAMETERS
*Commodity shock parameters
 PWESIM(C,SIM,T)          world price for exports
 PWMSIM(C,SIM,T)          world price for imports
 TEADJSIM(SIM,T)          export tax (TE) scaling factor
 DTESIM(SIM,T)            additive export tax (TE) adjustment
 TESIM(C,SIM,T)           export tax rate (commodity-specific)
 TMADJSIM(SIM,T)          import tariff (TM) scaling factor
 DTMSIM(SIM,T)            additive import tariff (TM) adjustment
 TMSIM(C,SIM,T)           import tariff rate (commodity-specific)
 TQADJSIM(SIM,T)          composite commodity tax (TQ) scaling factor
 DTQSIM(SIM,T)            additive sales tax (TQ) adjustment
 TQSIM(C,SIM,T)           sales tax rate (commodity-specific)
 ICESIM(C,CP,SIM,T)       export transaction costs
 ICMSIM(C,CP,SIM,T)       import transaction costs
 ICDSIM(C,CP,SIM,T)       domestic transaction costs
*Activity shock parameters
 ALPHAVASIM(A,SIM,T)      total factor productivity (TFP)
 TAADJSIM(SIM,T)          activity tax (TA) scaling factor
 DTASIM(SIM,T)            additive activity tax (TA) adjustment
 TASIM(A,SIM,T)           activity tax rate (activity-specific)
 TVADJSIM(SIM,T)          value-added tax (TVA) scaling factor
 DTVSIM(SIM,T)            additive value-added tax (TVA) adjustment
 TVSIM(A,SIM,T)           value added tax rate (activity-specific)
*Factor shock parameters
 WFSIM(F,SIM,T)           economywide wage-rental rate
 QFSSIM(F,SIM,T)          factor supply
 QFSIM(F,A,SIM,T)         factor demand
 ALPHAFSIM(F,A,SIM,T)     factor-specific productivity
 TFADJSIM(SIM,T)          direct factor tax (TF) scaling factor
 DTFSIM(SIM,T)            additive direct factor tax (TF) adjustment
 TFSIM(F,SIM,T)           factor tax rate (factor-specific)
 TRNSFSIM(F,INS,SIM,T)    factor transfers from government and rest of world
 SHIFSIM(INS,F,SIM,T)     share of factor income transferred to government and rest of world 
*Institution shock parameters
 POPSIM(H,SIM,T)          household populations   
 MPSADJSIM(SIM,T)         institutional savings rate scaling factor
 DMPSSIM(SIM,T)           additive institutional savings rate adjustment
 MPSSIM(INS,SIM,T)        institutional savings rate (institution-specific)
 TIADJSIM(SIM,T)          direct tax (TINS) scaling factor
 DTISIM(SIM,T)            additive domestic institution tax (TINS) adjustment
 TISIM(INS,SIM,T)         direct tax rate (institution-specific)
 TRNSISIM(INS,INSP,SIM,T) domestic institution transfers from government and rest of world
 SHIISIM(INS,INS,SIM,T)   share of domestic non-government institution income transferred to government and rest of world
*Macro shock parameters
 EXRSIM(SIM,T)            exchange rate
 FSAVSIM(SIM,T)           foreign savings
 IADJSIM(SIM,T)           investment adjustment factor
 INVSHRSIM(SIM,T)         investment share of absorption
 GSAVSIM(SIM,T)           government savings
 GADJSIM(SIM,T)           government spending
 GOVSHRSIM(SIM,T)         government consumption share of absorption
;

*--- Initialize shock parameters to base year values ---

*Commodity shocks 
*  World prices (PWE, PWM)
 PWESIM(C,SIMC,TC) = pwe0(C);
 PWMSIM(C,SIMC,TC) = pwm0(C);
*  Export tax (TE) rate
 TEADJSIM(SIMC,TC) = TEADJ0;
 DTESIM(SIMC,TC)   = DTE0;
 TESIM(C,SIMC,TC)  = TE0(C);
*  Import tariff (TM) rate
 TMADJSIM(SIMC,TC) = TMADJ0;
 DTMSIM(SIMC,TC)   = DTM0;
 TMSIM(C,SIMC,TC)  = TM0(C);
*  Composite commodity tax (TQ) rate 
 TQADJSIM(SIMC,TC) = TQADJ0;
 DTQSIM(SIMC,TC)   = DTQ0;
 TQSIM(C,SIMC,TC)  = TQ0(C);
*  Transaction costs (ice, icm, icd)
 ICESIM(C,CP,SIMC,TC) = ice0(C,CP);
 ICMSIM(C,CP,SIMC,TC) = icm0(C,CP);
 ICDSIM(C,CP,SIMC,TC) = icd0(C,CP);

*Activities
*  Total factor productivity (TFP)
 ALPHAVASIM(A,SIMC,TC) = alphava0(A);   
*  Activity tax (TA) rate
 TAADJSIM(SIMC,TC) = TAADJ0;
 DTASIM(SIMC,TC)   = DTA0;
 TASIM(A,SIMC,TC)  = TA0(A);
*  Value-added tax (TVA) rate 
 TVADJSIM(SIMC,TC) = TVADJ0;
 DTVSIM(SIMC,TC)   = DTV0;         
 TVSIM(A,SIMC,TC)  = TV0(A);
 
*Factors
*  Economywide wage-rental rate (WF)
 WFSIM(F,SIMC,TC) = WF0(F);
*  Factor supply (QFS)
 QFSSIM(F,SIMC,TC)  = QFS0(F);
*  Factor demand (QF)
 QFSIM(F,A,SIMC,TC) = QF0(F,A);
*  Factor-specific productivity (alphaf)
 ALPHAFSIM(F,A,SIMC,TC) = alphaf0(F,A);
*  Direct factor tax (TF) rate  
 TFADJSIM(SIMC,TC) = TFADJ0;
 DTFSIM(SIMC,TC)   = DTF0;
 TFSIM(F,SIMC,TC)  = TF0(F);
*  Share of factor income transferred to government and rest of world (shif)
 SHIFSIM(INS,F,SIMC,TC) = shif0(INS,F);
*  Factor transfers from government and rest of world (trnsf)
 TRNSFSIM(F,INS,SIMC,TC)    = trnsf0(F,INS);
 
*Institutions
*  Household populations (POP)  
 POPSIM(H,SIMC,TC) = pop0(H);
*  Institutional savings (MPS) rate
 MPSADJSIM(SIMC,TC) = MPSADJ0;
 DMPSSIM(SIMC,TC)   = DMPS0;
 MPSSIM(H,SIMC,TC)  = MPS0(H);
*  Direct tax (TI) rate
 TIADJSIM(SIMC,TC) = TIADJ0;
 DTISIM(SIMC,TC)   = DTI0;
 TISIM(H,SIMC,TC)  = TI0(H);
*  Share of domestic non-government institution income transferred to government and rest of world (shii)
 SHIISIM(INS,INSDNG,SIMC,TC) = shii0(INS,INSDNG);
*  Domestic institution transfers from government and rest of world (trnsi)
 TRNSISIM(INS,INSP,SIMC,TC) = trnsi0(INS,INSP);
 
*Macro/scalar 
*  Exchange rate (EXR)
 EXRSIM(SIMC,TC) = EXR0;
*  Foreign savings (FSAV)
 FSAVSIM(SIMC,TC) = FSAV0;
*  Investment adjustment factor (IADJ)
 IADJSIM(SIMC,TC) = IADJ0;
*  Government savings (GSAV)
 GSAVSIM(SIMC,TC) = GSAV0;
*  Government spending (GADJ)
 GADJSIM(SIMC,TC) = GADJ0;
*  Investment share of absorption (INVSHR)
 INVSHRSIM(SIMC,TC) = INVSHR0;
*  Government share of absorption (GOVSHR)
 GOVSHRSIM(SIMC,TC) = GOVSHR0;


*--- Update shock parameters with imported baseline and shock simulation data ---


LOOP(TC$(NOT T1(TC)),

*Commodity shocks

*  World price for exports
 PWESIM(C,SIMC,TC)$(ATYPC('PWE',SIMC) EQ 1) = PWESIM(C,SIMC,TC-1) * (1+ASIMC(C,'PWE',SIMC,TC)/100);
 PWESIM(C,SIMC,TC)$(ATYPC('PWE',SIMC) EQ 2) = PWESIM(C,SIMC,TC-1) + ASIMC(C,'PWE',SIMC,TC);
 
*  World price for imports
 PWMSIM(C,SIMC,TC)$(ATYPC('PWM',SIMC) EQ 1) = PWMSIM(C,SIMC,TC-1) * (1+ASIMC(C,'PWM',SIMC,TC)/100);
 PWMSIM(C,SIMC,TC)$(ATYPC('PWM',SIMC) EQ 2) = PWMSIM(C,SIMC,TC-1) + ASIMC(C,'PWM',SIMC,TC);
 
*  Export tax (TE) rate
 TESIM(C,SIMC,TC)$(ATYPS('TE',SIMC) EQ 1)  = TESIM(C,SIMC,TC-1)  * (1+ASIMS('TE',SIMC,TC)/100); 
 TESIM(C,SIMC,TC)$(ATYPS('TE',SIMC) EQ 2)  = TESIM(C,SIMC,TC-1)  + ASIMS('TE',SIMC,TC)/100; 
 TESIM(C,SIMC,TC)$(ATYPC('TE',SIMC) EQ 1 AND TESIM(C,SIMC,TC) EQ TESIM(C,SIMC,TC-1)) = TESIM(C,SIMC,TC-1)  * (1+ASIMC(C,'TE',SIMC,TC)/100); 
 TESIM(C,SIMC,TC)$(ATYPC('TE',SIMC) EQ 2 AND TESIM(C,SIMC,TC) EQ TESIM(C,SIMC,TC-1)) = TESIM(C,SIMC,TC-1)  + ASIMC(C,'TE',SIMC,TC)/100; 

*  Import tariff (TM) rate
 TMSIM(C,SIMC,TC)$(ATYPS('TM',SIMC) EQ 1)  = TMSIM(C,SIMC,TC-1)  * (1+ASIMS('TM',SIMC,TC)/100); 
 TMSIM(C,SIMC,TC)$(ATYPS('TM',SIMC) EQ 2)  = TMSIM(C,SIMC,TC-1)  + ASIMS('TM',SIMC,TC)/100;
 TMSIM(C,SIMC,TC)$(ATYPC('TM',SIMC) EQ 1 AND TMSIM(C,SIMC,TC) EQ TMSIM(C,SIMC,TC-1))  = TMSIM(C,SIMC,TC-1)  * (1+ASIMC(C,'TM',SIMC,TC)/100); 
 TMSIM(C,SIMC,TC)$(ATYPC('TM',SIMC) EQ 2 AND TMSIM(C,SIMC,TC) EQ TMSIM(C,SIMC,TC-1))  = TMSIM(C,SIMC,TC-1)  + ASIMC(C,'TM',SIMC,TC)/100;
 
*  Composite commodity tax (TQ) rate
 TQSIM(C,SIMC,TC)$(ATYPS('TQ',SIMC) EQ 1)  = TQSIM(C,SIMC,TC-1) * (1+ASIMS('TQ',SIMC,TC)/100); 
 TQSIM(C,SIMC,TC)$(ATYPS('TQ',SIMC) EQ 2)  = TQSIM(C,SIMC,TC-1) + ASIMS('TQ',SIMC,TC)/100; 
 TQSIM(C,SIMC,TC)$(ATYPC('TQ',SIMC) EQ 1 AND TQSIM(C,SIMC,TC) EQ TQSIM(C,SIMC,TC-1))  = TQSIM(C,SIMC,TC-1) * (1+ASIMC(C,'TQ',SIMC,TC)/100); 
 TQSIM(C,SIMC,TC)$(ATYPC('TQ',SIMC) EQ 2 AND TQSIM(C,SIMC,TC) EQ TQSIM(C,SIMC,TC-1))  = TQSIM(C,SIMC,TC-1) + ASIMC(C,'TQ',SIMC,TC)/100; 

*  Export transaction costs (ice)
*    Only apply shock if commodity is a supplier of transaction cost demand (e.g., transport, trade services)
 ICESIM(C,CP,SIMC,TC)$(SUM(CPP, ice0(C,CPP)) AND ATYPC('ICE',SIMC) EQ 1) = ICESIM(C,CP,SIMC,TC-1) * (1+ASIMC(CP,'ICE',SIMC,TC)/100);
 ICESIM(C,CP,SIMC,TC)$(SUM(CPP, ice0(C,CPP)) AND ATYPC('ICE',SIMC) EQ 2) = ICESIM(C,CP,SIMC,TC-1) + ASIMC(CP,'ICE',SIMC,TC);
 
*  Import transaction costs (icm)
*    Only apply shock if commodity is a supplier of transaction cost demand (e.g., transport, trade services)
 ICMSIM(C,CP,SIMC,TC)$(SUM(CPP, icm0(C,CPP)) AND ATYPC('ICM',SIMC) EQ 1) = ICMSIM(C,CP,SIMC,TC-1) * (1+ASIMC(CP,'ICM',SIMC,TC)/100);
 ICMSIM(C,CP,SIMC,TC)$(SUM(CPP, icm0(C,CPP)) AND ATYPC('ICM',SIMC) EQ 2) = ICMSIM(C,CP,SIMC,TC-1) + ASIMC(CP,'ICM',SIMC,TC);
 
*  Domestic transaction costs (icd)
*    Only apply shock if commodity is a supplier of transaction cost demand (e.g., transport, trade services)
 ICDSIM(C,CP,SIMC,TC)$(SUM(CPP, icd0(C,CPP)) AND ATYPC('ICD',SIMC) EQ 1) = ICDSIM(C,CP,SIMC,TC-1) * (1+ASIMC(CP,'ICD',SIMC,TC)/100);
 ICDSIM(C,CP,SIMC,TC)$(SUM(CPP, icd0(C,CPP)) AND ATYPC('ICD',SIMC) EQ 2) = ICDSIM(C,CP,SIMC,TC-1) + ASIMC(CP,'ICD',SIMC,TC);


*Activity shocks

*  Total factor productivity (alphava)
 ALPHAVASIM(A,SIMC,TC)$(ATYPA('ALPHAVA',SIMC) EQ 1) = ALPHAVASIM(A,SIMC,TC-1) * (1+ASIMA(A,'ALPHAVA',SIMC,TC)/100);
 ALPHAVASIM(A,SIMC,TC)$(ATYPA('ALPHAVA',SIMC) EQ 2) = ALPHAVASIM(A,SIMC,TC-1) + ASIMA(A,'ALPHAVA',SIMC,TC); 
 
*  Activity tax (TA) rate
 TASIM(A,SIMC,TC)$(ATYPS('TA',SIMC) EQ 1)  = TASIM(A,SIMC,TC-1)  * (1+ASIMS('TA',SIMC,TC)/100); 
 TASIM(A,SIMC,TC)$(ATYPS('TA',SIMC) EQ 2)  = TASIM(A,SIMC,TC-1)  + ASIMS('TA',SIMC,TC)/100; 
 TASIM(A,SIMC,TC)$(ATYPA('TA',SIMC) EQ 1 AND TASIM(A,SIMC,TC) EQ TASIM(A,SIMC,TC-1))  = TASIM(A,SIMC,TC-1)  * (1+ASIMA(A,'TA',SIMC,TC)/100); 
 TASIM(A,SIMC,TC)$(ATYPA('TA',SIMC) EQ 2 AND TASIM(A,SIMC,TC) EQ TASIM(A,SIMC,TC-1))  = TASIM(A,SIMC,TC-1)  + ASIMA(A,'TA',SIMC,TC)/100; 
 
*  Value-added tax (TVA) rate
 TVSIM(A,SIMC,TC)$(ATYPS('TV',SIMC) EQ 1)  = TVSIM(A,SIMC,TC-1)  * (1+ASIMS('TV',SIMC,TC)/100); 
 TVSIM(A,SIMC,TC)$(ATYPS('TV',SIMC) EQ 2)  = TVSIM(A,SIMC,TC-1)  + ASIMS('TV',SIMC,TC)/100; 
 TVSIM(A,SIMC,TC)$(ATYPA('TV',SIMC) EQ 1 AND TVSIM(A,SIMC,TC) EQ TVSIM(A,SIMC,TC-1))  = TVSIM(A,SIMC,TC-1)  * (1+ASIMA(A,'TV',SIMC,TC)/100); 
 TVSIM(A,SIMC,TC)$(ATYPA('TV',SIMC) EQ 2 AND TVSIM(A,SIMC,TC) EQ TVSIM(A,SIMC,TC-1))  = TVSIM(A,SIMC,TC-1)  + ASIMA(A,'TV',SIMC,TC)/100;
 

*Factor shocks
 
*  Economywide wage-rental rate (WF)
*    Shock is ineffective when factor is fully employed and variable WF is flexible (FACCLOS = 1)
 WFSIM(F,SIMC,TC)$(ATYPF('WF',SIMC) EQ 1) = WFSIM(F,SIMC,TC-1) * (1+ASIMF(F,'WF',SIMC,TC)/100);
 WFSIM(F,SIMC,TC)$(ATYPF('WF',SIMC) EQ 2) = WFSIM(F,SIMC,TC-1) + ASIMF(F,'WF',SIMC,TC);
 
*  Factor supply (QFS)
*    Shock is ineffective when factor is unemployed or sector-specific and variable QFS is flexible (FACCLOS = 2,3)
 QFSSIM(F,SIMC,TC)$(ATYPF('QFS',SIMC) EQ 1) = QFSSIM(F,SIMC,TC-1) * (1+ASIMF(F,'QFS',SIMC,TC)/100);
 QFSSIM(F,SIMC,TC)$(ATYPF('QFS',SIMC) EQ 2) = QFSSIM(F,SIMC,TC-1) + ASIMF(F,'QFS',SIMC,TC);
 
*  Factor demand (QF)
*    Shock is ineffective when factor is unemployed or mobile across activities (FACCLOS = 1,3)
 QFSIM(FCAP,A,SIMC,TC)$(ASIMA(A,'FIXCAP',SIMC,TC) NE 0) = QFSIM(FCAP,A,SIMC,TC-1) * (1+ASIMA(A,'FIXCAP',SIMC,TC)/100);
 QFSIM(FLND,A,SIMC,TC)$(ASIMA(A,'FIXLND',SIMC,TC) NE 0) = QFSIM(FLND,A,SIMC,TC-1) * (1+ASIMA(A,'FIXLND',SIMC,TC)/100);
 
*  Factor-specific productivity (alphaf)
*    Shock is both factor- and sector-specific (activities excluded from shock are selected in the activity block on the simulation Excel worksheets).   
 ALPHAFSIM(F,A,SIMC,TC)$(ATYPF('QFS',SIMC) EQ 1 AND ASIMA(A,'ALPHAF',SIMC,TC) EQ 1) = ALPHAFSIM(F,A,SIMC,TC-1) * (1+ASIMF(F,'ALPHAF',SIMC,TC)/100);
 ALPHAFSIM(F,A,SIMC,TC)$(ATYPF('QFS',SIMC) EQ 2 AND ASIMA(A,'ALPHAF',SIMC,TC) EQ 1) = ALPHAFSIM(F,A,SIMC,TC-1) + ASIMF(F,'ALPHAF',SIMC,TC);
 
*  Direct factor tax (TF) rate
 TFSIM(F,SIMC,TC)$(ATYPS('TF',SIMC) EQ 1)  = TFSIM(F,SIMC,TC-1)  * (1+ASIMS('TF',SIMC,TC)/100); 
 TFSIM(F,SIMC,TC)$(ATYPS('TF',SIMC) EQ 2)  = TFSIM(F,SIMC,TC-1)  + ASIMS('TF',SIMC,TC)/100;
 TFSIM(F,SIMC,TC)$(ATYPF('TF',SIMC) EQ 1 AND TFSIM(F,SIMC,TC) EQ TFSIM(F,SIMC,TC-1))  = TFSIM(F,SIMC,TC-1)  * (1+ASIMF(F,'TF',SIMC,TC)/100); 
 TFSIM(F,SIMC,TC)$(ATYPF('TF',SIMC) EQ 2 AND TFSIM(F,SIMC,TC) EQ TFSIM(F,SIMC,TC-1))  = TFSIM(F,SIMC,TC-1)  + ASIMF(F,'TF',SIMC,TC)/100;
 
*  Share of factor income transferred to government and rest of world (shif)
*    Shock factor income transferred to government 
 SHIFSIM(GV,F,SIMC,TC)$(ATYPF('TRTG',SIMC) EQ 1) = SHIFSIM(GV,F,SIMC,TC-1) * (1+ASIMF(F,'TRTG',SIMC,TC)/100);
 SHIFSIM(GV,F,SIMC,TC)$(ATYPF('TRTG',SIMC) EQ 2) = SHIFSIM(GV,F,SIMC,TC-1) + ASIMF(F,'TRTG',SIMC,TC)/100; 
*    Shock factor income transferred to rest of world
 SHIFSIM(RW,F,SIMC,TC)$(ATYPF('TRTW',SIMC) EQ 1) = SHIFSIM(RW,F,SIMC,TC-1) * (1+ASIMF(F,'TRTW',SIMC,TC)/100);
 SHIFSIM(RW,F,SIMC,TC)$(ATYPF('TRTW',SIMC) EQ 2) = SHIFSIM(RW,F,SIMC,TC-1) + ASIMF(F,'TRTW',SIMC,TC)/100;
*    Recalculate non-government and non-ROW shares 
 SHIFSIM(INSDNG,F,SIMC,TC)$SUM(INSDNGP, shif0(INSDNGP,F))
    = SHIF0(INSDNG,F) / SUM(INSDNGP, shif0(INSDNGP,F)) * (1 - SHIFSIM(GV,F,SIMC,TC) - SHIFSIM(RW,F,SIMC,TC));
 
*  Factor transfers from government and rest of world (trnsf)
*    Shock government transfers to factors
 TRNSFSIM(F,GV,SIMC,TC)$(ATYPF('TRFG',SIMC) EQ 1) = TRNSFSIM(F,GV,SIMC,TC-1) * (1+ASIMF(F,'TRFG',SIMC,TC)/100);
 TRNSFSIM(F,GV,SIMC,TC)$(ATYPF('TRFG',SIMC) EQ 2) = TRNSFSIM(F,GV,SIMC,TC-1) + ASIMF(F,'TRFG',SIMC,TC);
*    Shock rest of world transfers to factors
 TRNSFSIM(F,RW,SIMC,TC)$(ATYPF('TRFW',SIMC) EQ 1) = TRNSFSIM(F,RW,SIMC,TC-1) * (1+ASIMF(F,'TRFW',SIMC,TC)/100);
 TRNSFSIM(F,RW,SIMC,TC)$(ATYPF('TRFW',SIMC) EQ 2) = TRNSFSIM(F,RW,SIMC,TC-1) + ASIMF(F,'TRFW',SIMC,TC);


*Institution shocks 

*  Household populations (POP)  
 POPSIM(H,SIMC,TC)$(ATYPH('POP',SIMC) EQ 1) = POPSIM(H,SIMC,TC-1) * (1+ASIMH(H,'POP',SIMC,TC)/100);
 POPSIM(H,SIMC,TC)$(ATYPH('POP',SIMC) EQ 2) = POPSIM(H,SIMC,TC-1) + ASIMH(H,'POP',SIMC,TC);

*  Institutional savings (MPS) rate
 MPSSIM(INSDNG,SIMC,TC)$(ATYPS('MPS',SIMC) EQ 1)  = MPSSIM(INSDNG,SIMC,TC-1)  * (1+ASIMS('MPS',SIMC,TC)/100); 
 MPSSIM(INSDNG,SIMC,TC)$(ATYPS('MPS',SIMC) EQ 2)  = MPSSIM(INSDNG,SIMC,TC-1)  + ASIMS('MPS',SIMC,TC)/100;  
 MPSSIM(INSDNG,SIMC,TC)$(ATYPH('MPS',SIMC) EQ 1 AND MPSSIM(INSDNG,SIMC,TC) EQ MPSSIM(INSDNG,SIMC,TC-1))  = MPSSIM(INSDNG,SIMC,TC-1)  * (1+ASIMH(INSDNG,'MPS',SIMC,TC)/100); 
 MPSSIM(INSDNG,SIMC,TC)$(ATYPH('MPS',SIMC) EQ 2 AND MPSSIM(INSDNG,SIMC,TC) EQ MPSSIM(INSDNG,SIMC,TC-1))  = MPSSIM(INSDNG,SIMC,TC-1)  + ASIMH(INSDNG,'MPS',SIMC,TC)/100;  
 
*  Direct tax (TI) rate
 TISIM(INSDNG,SIMC,TC)$(ATYPS('TI',SIMC) EQ 1)  = TISIM(INSDNG,SIMC,TC-1)  * (1+ASIMS('TI',SIMC,TC)/100); 
 TISIM(INSDNG,SIMC,TC)$(ATYPS('TI',SIMC) EQ 2)  = TISIM(INSDNG,SIMC,TC-1)  + ASIMS('TI',SIMC,TC)/100;
 TISIM(INSDNG,SIMC,TC)$(ATYPH('TI',SIMC) EQ 1 AND TISIM(INSDNG,SIMC,TC) EQ TISIM(INSDNG,SIMC,TC-1))  = TISIM(INSDNG,SIMC,TC-1)  * (1+ASIMH(INSDNG,'TI',SIMC,TC)/100); 
 TISIM(INSDNG,SIMC,TC)$(ATYPH('TI',SIMC) EQ 2 AND TISIM(INSDNG,SIMC,TC) EQ TISIM(INSDNG,SIMC,TC-1))  = TISIM(INSDNG,SIMC,TC-1)  + ASIMH(INSDNG,'TI',SIMC,TC)/100;

*  Share of domestic non-government institution income transferred to government and rest of world (shii)
*    Shock domestic non-government instituional income transferred to government 
 SHIISIM(GV,INSDNG,SIMC,TC)$(ATYPH('TRTG',SIMC) EQ 1) = SHIISIM(GV,INSDNG,SIMC,TC-1) * (1+ASIMH(INSDNG,'TRTG',SIMC,TC)/100);
 SHIISIM(GV,INSDNG,SIMC,TC)$(ATYPH('TRTG',SIMC) EQ 2) = SHIISIM(GV,INSDNG,SIMC,TC-1) + ASIMH(INSDNG,'TRTG',SIMC,TC)/100; 
*    Shock institution income transferred to rest of world       
 SHIISIM(RW,INSDNG,SIMC,TC)$(ATYPH('TRTW',SIMC) EQ 1) = SHIISIM(RW,INSDNG,SIMC,TC-1) * (1+ASIMH(INSDNG,'TRTW',SIMC,TC)/100);
 SHIISIM(RW,INSDNG,SIMC,TC)$(ATYPH('TRTW',SIMC) EQ 2) = SHIISIM(RW,INSDNG,SIMC,TC-1) + ASIMH(INSDNG,'TRTW',SIMC,TC)/100;
*    Recalculate non-government and non-ROW shares 
 SHIISIM(INSDNGP,INSDNG,SIMC,TC)$(1 - shii0(GV,INSDNG) - shii0(RW,INSDNG))
    = shii0(INSDNGP,INSDNG) / (1 - shii0(GV,INSDNG) - shii0(RW,INSDNG)) * (1 - SHIISIM(GV,INSDNG,SIMC,TC) - SHIISIM(RW,INSDNG,SIMC,TC));
 
*  Domestic non-government institution transfers from government and rest of world (trnsi)
*    Shock government transfers to domestic non-government institutions
 TRNSISIM(INSDNG,GV,SIMC,TC)$(ATYPH('TRFG',SIMC) EQ 1) = TRNSISIM(INSDNG,GV,SIMC,TC-1) * (1+ASIMH(INSDNG,'TRFG',SIMC,TC)/100);
 TRNSISIM(INSDNG,GV,SIMC,TC)$(ATYPH('TRFG',SIMC) EQ 2) = TRNSISIM(INSDNG,GV,SIMC,TC-1) + ASIMH(INSDNG,'TRFG',SIMC,TC);
*    Shock rest of world transfers to domestic non-government institutions
 TRNSISIM(INSDNG,RW,SIMC,TC)$(ATYPH('TRFW',SIMC) EQ 1) = TRNSISIM(INSDNG,RW,SIMC,TC-1) * (1+ASIMH(INSDNG,'TRFW',SIMC,TC)/100);
 TRNSISIM(INSDNG,RW,SIMC,TC)$(ATYPH('TRFW',SIMC) EQ 2) = TRNSISIM(INSDNG,RW,SIMC,TC-1) + ASIMH(INSDNG,'TRFW',SIMC,TC);

*Macro/scalar shocks

*  Exchange rate (EXR)
*    Shock is ineffective when variable EXR is flexible (ROWCLOS = 1)
 EXRSIM(SIMC,TC)$(ATYPS('EXR',SIMC) EQ 1) = EXRSIM(SIMC,TC-1) * (1+ASIMS('EXR',SIMC,TC)/100);
 EXRSIM(SIMC,TC)$(ATYPS('EXR',SIMC) EQ 2) = EXRSIM(SIMC,TC-1) + ASIMS('EXR',SIMC,TC);

*  Foreign savings (FSAV)
 FSAVSIM(SIMC,TC)$(ATYPS('FSAV',SIMC) EQ 1) = FSAVSIM(SIMC,TC-1) * (1+ASIMS('FSAV',SIMC,TC)/100);
 FSAVSIM(SIMC,TC)$(ATYPS('FSAV',SIMC) EQ 2) = FSAVSIM(SIMC,TC-1) + ASIMS('FSAV',SIMC,TC);
 
*  Investment adjustment factor (IADJ)
 IADJSIM(SIMC,TC)$(ATYPS('IADJ',SIMC) EQ 1) = IADJSIM(SIMC,TC-1) * (1+ASIMS('IADJ',SIMC,TC)/100);
 IADJSIM(SIMC,TC)$(ATYPS('IADJ',SIMC) EQ 2) = IADJSIM(SIMC,TC-1) + ASIMS('IADJ',SIMC,TC)/100;
 
*  Investment share of absorption (INVSHR)
 INVSHRSIM(SIMC,TC)$(ATYPS('INVSHR',SIMC) EQ 1) = INVSHRSIM(SIMC,TC-1) * (1+ASIMS('INVSHR',SIMC,TC)/100);
 INVSHRSIM(SIMC,TC)$(ATYPS('INVSHR',SIMC) EQ 2) = INVSHRSIM(SIMC,TC-1) + ASIMS('INVSHR',SIMC,TC)/100;
 
*  Government savings (GSAV)
 GSAVSIM(SIMC,TC)$(ATYPS('GSAV',SIMC) EQ 1) = GSAVSIM(SIMC,TC-1) * (1+ASIMS('GSAV',SIMC,TC)/100);
 GSAVSIM(SIMC,TC)$(ATYPS('GSAV',SIMC) EQ 2) = GSAVSIM(SIMC,TC-1) + ASIMS('GSAV',SIMC,TC);

*  Government spending (GADJ)
 GADJSIM(SIMC,TC)$(ATYPS('GADJ',SIMC) EQ 1) = GADJSIM(SIMC,TC-1) * (1+ASIMS('GADJ',SIMC,TC)/100);
 GADJSIM(SIMC,TC)$(ATYPS('GADJ',SIMC) EQ 2) = GADJSIM(SIMC,TC-1) + ASIMS('GADJ',SIMC,TC)/100;

*  Government share of absorption (GOVSHR)
 GOVSHRSIM(SIMC,TC)$(ATYPS('GOVSHR',SIMC) EQ 1) = GOVSHRSIM(SIMC,TC-1) * (1+ASIMS('GOVSHR',SIMC,TC)/100);
 GOVSHRSIM(SIMC,TC)$(ATYPS('GOVSHR',SIMC) EQ 2) = GOVSHRSIM(SIMC,TC-1) + ASIMS('GOVSHR',SIMC,TC)/100;
 
*  Government transfers to and from the rest of world (trnsi)
*    Shock government transfers to rest of world
 TRNSISIM(RW,GV,SIMC,TC)$(ATYPS('TRTW',SIMC) EQ 1) = TRNSISIM(RW,GV,SIMC,TC-1) * (1+ASIMS('TRTW',SIMC,TC)/100);
 TRNSISIM(RW,GV,SIMC,TC)$(ATYPS('TRTW',SIMC) EQ 2) = TRNSISIM(RW,GV,SIMC,TC-1) + ASIMS('TRTW',SIMC,TC);
*    Shock rest of world transfers to government
 TRNSISIM(GV,RW,SIMC,TC)$(ATYPS('TRFW',SIMC) EQ 1) = TRNSISIM(GV,RW,SIMC,TC-1) * (1+ASIMS('TRFW',SIMC,TC)/100);
 TRNSISIM(GV,RW,SIMC,TC)$(ATYPS('TRFW',SIMC) EQ 2) = TRNSISIM(GV,RW,SIMC,TC-1) + ASIMS('TRFW',SIMC,TC);

);


*------------------------------------------------------------------
*2.1.4  Capital accumulation parameters
*------------------------------------------------------------------

PARAMETER
*Investment-to-capital conversion
 DRATESIM(SIM,T)        capital depreciation rate in baseline and simulations
 arate                  capital accumulation rate in baseline
 iwts(C)                investment commodity demand weight
 alphai                 investment shift parameter (for converting investment quantities into capital quantities)
*Exogenous capital growth rates
 AFXGR(A,SIM,T)         exogenous activity capital growth rates
*Newly accumulated capital 
 QKAP(SIM,T)            total new capital stock
 QKAP_N(SIM,T)          new capital net of activities with exogenous capital growth 
*Current capital allocation shares  
 QKAP_S1(F)             shares of existing aggregate capital by type (sums to one)
 QKAP_S2(F,A)           sectoral shares of existing capital by type (rows sum to one)
*Relative profit rate diffdrentials 
 WF_ADJ(F)              WF adjusted to exclude activities with exogenous capital growth 
 WFDIST_ADJ(F,A)        WFDIST adjusted to exclude activties with exogenous capital growth 
 WF_K2(F)               average rental on capital by type (across all activities)
 WFDIST_K2(F,A)         ratio of sectoral to average rental by capital type
 WF_K1                  average rental on all capital (economywide)
*New capital allocation shares 
 QINV_1(F)              investment shares by type of capital
 QINV_2(F,A)            investment shares by sector for each capital type
*New capital quantities (QKD) and growth rates (QKR)
 QKAP_D(F,A)           change in sectoral real capital stock
 QKAP_DS(F)            change in aggregate real capital stock
 QKAP_R(F,A)           annual rate of growth of sectoral capital stock by type
 QKAP_RS(F)            annual rate of growth of aggregate capital stock by type
*Capital mobility 
 betai1                 capital mobility parameter by type                      / 2.00 /
 betai2                 capital mobility by sector                              / 2.00 /
;

*Capital depreciation rate in baseline and simulations
 DRATESIM(SIMC,TC) = ASIMS('DRATE','BASE',TC)/100;           
LOOP(TC$(NOT T1(TC)), 
 DRATESIM(SIMC,TC)$(ATYPS('DRATE',SIMC) EQ 1) = DRATESIM(SIMC,TC-1) * (1+ASIMS('DRATE',SIMC,TC)/100);
 DRATESIM(SIMC,TC)$(ATYPS('DRATE',SIMC) EQ 2) = DRATESIM(SIMC,TC-1) + ASIMS('DRATE',SIMC,TC)/100;
);

*Capital accumulation rate in baseline (weighted across all capital types)
 ARATE = SUM((FCAP,TC)$(ORD(TC) EQ 2), QFSSIM(FCAP,'BASE',TC)) / SUM((FCAP,TC)$(ORD(TC) EQ 1), QFSSIM(FCAP,'BASE',TC)) - 1;

*  Calculate investment units to achieve targeted initial year capital accumulation rate after depreciation
 iwts(C) = QINV0(C) / SUM(CP, QINV0(CP));
 alphai  = ((SUM(T1, DRATESIM('BASE',T1)) + arate) * SUM(FCAP, QFS0(FCAP))) / SUM(C, QINV0(C)*iwts(C));
 












