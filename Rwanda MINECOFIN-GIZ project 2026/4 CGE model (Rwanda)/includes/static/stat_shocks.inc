$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2.1: Define simulations using standard data imported from Excel
 This include file (includes\2static_shocks.inc) imports country simulation data from the Excel selected by
 the user (statsim%dataext%.xlsx) and calibrates the simulation shock parameters and closure rules.

SECTIONS:
 2.1.1  Import simulation data from Excel
 2.1.2  Define closure parameters
 2.1.3  Define shock parameters
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
 MCLOSEAC               macro closure dimensions        / numeraire, savings-investment, current-account, government-account, factors /
 SIMAC                  simulation data dimesnions      / alphaf, alphava, exr, fixcap, fixlnd, fsav, gadj, govshr, gsav, iadj, icd, ice, icm, invshr, mps, pop, pwe, pwm, qfs, save, shk, ta, tax, te, tf, ti, tm, tq, trfg, trfw, trtg, trtw, tv, type, wf /
;

PARAMETER
*Imported simulation names and closures choices
 ACTIVE(SIM)            active simulations
 MCLOSE(MCLOSEAC,SIM)   chosen macro closures 
 FCLOSE(F,SIM)          chosen factor closures
*Shocks on commodities, activities, factors, and households, plus scalar shocks
 SIM1C(C,SIMAC),     SIM2C(C,SIMAC),     SIM3C(C,SIMAC),     SIM4C(C,SIMAC),     SIM5C(C,SIMAC),     SIM6C(C,SIMAC),     SIM7C(C,SIMAC),     SIM8C(C,SIMAC),     SIM9C(C,SIMAC),     SIM10C(C,SIMAC),     SIM11C(C,SIMAC),     SIM12C(C,SIMAC),     SIM13C(C,SIMAC),     SIM14C(C,SIMAC),     SIM15C(C,SIMAC)
 SIM1A(A,SIMAC),     SIM2A(A,SIMAC),     SIM3A(A,SIMAC),     SIM4A(A,SIMAC),     SIM5A(A,SIMAC),     SIM6A(A,SIMAC),     SIM7A(A,SIMAC),     SIM8A(A,SIMAC),     SIM9A(A,SIMAC),     SIM10A(A,SIMAC),     SIM11A(A,SIMAC),     SIM12A(A,SIMAC),     SIM13A(A,SIMAC),     SIM14A(A,SIMAC),     SIM15A(A,SIMAC)
 SIM1F(F,SIMAC),     SIM2F(F,SIMAC),     SIM3F(F,SIMAC),     SIM4F(F,SIMAC),     SIM5F(F,SIMAC),     SIM6F(F,SIMAC),     SIM7F(F,SIMAC),     SIM8F(F,SIMAC),     SIM9F(F,SIMAC),     SIM10F(F,SIMAC),     SIM11F(F,SIMAC),     SIM12F(F,SIMAC),     SIM13F(F,SIMAC),     SIM14F(F,SIMAC),     SIM15F(F,SIMAC)
 SIM1H(INS,SIMAC),   SIM2H(INS,SIMAC),   SIM3H(INS,SIMAC),   SIM4H(INS,SIMAC),   SIM5H(INS,SIMAC),   SIM6H(INS,SIMAC),   SIM7H(INS,SIMAC),   SIM8H(INS,SIMAC),   SIM9H(INS,SIMAC),   SIM10H(INS,SIMAC),   SIM11H(INS,SIMAC),   SIM12H(INS,SIMAC),   SIM13H(INS,SIMAC),   SIM14H(INS,SIMAC),   SIM15H(INS,SIMAC)
 SIM1S(SIMAC,SIMAC), SIM2S(SIMAC,SIMAC), SIM3S(SIMAC,SIMAC), SIM4S(SIMAC,SIMAC), SIM5S(SIMAC,SIMAC), SIM6S(SIMAC,SIMAC), SIM7S(SIMAC,SIMAC), SIM8S(SIMAC,SIMAC), SIM9S(SIMAC,SIMAC), SIM10S(SIMAC,SIMAC), SIM11S(SIMAC,SIMAC), SIM12S(SIMAC,SIMAC), SIM13S(SIMAC,SIMAC), SIM14S(SIMAC,SIMAC), SIM15S(SIMAC,SIMAC)
 TYP1C(SIMAC),       TYP2C(SIMAC),       TYP3C(SIMAC),       TYP4C(SIMAC),       TYP5C(SIMAC),       TYP6C(SIMAC),       TYP7C(SIMAC),       TYP8C(SIMAC),       TYP9C(SIMAC),       TYP10C(SIMAC),       TYP11C(SIMAC),       TYP12C(SIMAC),       TYP13C(SIMAC),       TYP14C(SIMAC),       TYP15C(SIMAC)
 TYP1A(SIMAC),       TYP2A(SIMAC),       TYP3A(SIMAC),       TYP4A(SIMAC),       TYP5A(SIMAC),       TYP6A(SIMAC),       TYP7A(SIMAC),       TYP8A(SIMAC),       TYP9A(SIMAC),       TYP10A(SIMAC),       TYP11A(SIMAC),       TYP12A(SIMAC),       TYP13A(SIMAC),       TYP14A(SIMAC),       TYP15A(SIMAC)
 TYP1F(SIMAC),       TYP2F(SIMAC),       TYP3F(SIMAC),       TYP4F(SIMAC),       TYP5F(SIMAC),       TYP6F(SIMAC),       TYP7F(SIMAC),       TYP8F(SIMAC),       TYP9F(SIMAC),       TYP10F(SIMAC),       TYP11F(SIMAC),       TYP12F(SIMAC),       TYP13F(SIMAC),       TYP14F(SIMAC),       TYP15F(SIMAC)
 TYP1H(SIMAC),       TYP2H(SIMAC),       TYP3H(SIMAC),       TYP4H(SIMAC),       TYP5H(SIMAC),       TYP6H(SIMAC),       TYP7H(SIMAC),       TYP8H(SIMAC),       TYP9H(SIMAC),       TYP10H(SIMAC),       TYP11H(SIMAC),       TYP12H(SIMAC),       TYP13H(SIMAC),       TYP14H(SIMAC),       TYP15H(SIMAC)
*Aggregated shock and shock type parameters
 ASIMC(C,SIMAC,SIM)
 ASIMA(A,SIMAC,SIM)
 ASIMF(F,SIMAC,SIM)
 ASIMH(INS,SIMAC,SIM)
 ASIMS(SIMAC,SIM)
 ATYPC(SIMAC,SIM)
 ATYPA(SIMAC,SIM)
 ATYPF(SIMAC,SIM)
 ATYPH(SIMAC,SIM)
 ATYPS(SIMAC,SIM)
;

*Read input data from excel file (statsim%dataext%.xlsx)
$call "gdxxrw i=data\\%folder%\statsim%dataext%.xlsx o=sims.gdx index=index!a5"
$gdxin sims.gdx
*Read sets and data
$load SIM 
$loaddc ACTIVE MCLOSE FCLOSE
$loaddc SIM1C SIM2C SIM3C SIM4C SIM5C SIM6C SIM7C SIM8C SIM9C SIM10C SIM11C SIM12C SIM13C SIM14C SIM15C
$loaddc SIM1A SIM2A SIM3A SIM4A SIM5A SIM6A SIM7A SIM8A SIM9A SIM10A SIM11A SIM12A SIM13A SIM14A SIM15A
$loaddc SIM1F SIM2F SIM3F SIM4F SIM5F SIM6F SIM7F SIM8F SIM9F SIM10F SIM11F SIM12F SIM13F SIM14F SIM15F
$loaddc SIM1H SIM2H SIM3H SIM4H SIM5H SIM6H SIM7H SIM8H SIM9H SIM10H SIM11H SIM12H SIM13H SIM14H SIM15H
$loaddc SIM1S SIM2S SIM3S SIM4S SIM5S SIM6S SIM7S SIM8S SIM9S SIM10S SIM11S SIM12S SIM13S SIM14S SIM15S
$loaddc TYP1C TYP2C TYP3C TYP4C TYP5C TYP6C TYP7C TYP8C TYP9C TYP10C TYP11C TYP12C TYP13C TYP14C TYP15C
$loaddc TYP1A TYP2A TYP3A TYP4A TYP5A TYP6A TYP7A TYP8A TYP9A TYP10A TYP11A TYP12A TYP13A TYP14A TYP15A
$loaddc TYP1F TYP2F TYP3F TYP4F TYP5F TYP6F TYP7F TYP8F TYP9F TYP10F TYP11F TYP12F TYP13F TYP14F TYP15F
$loaddc TYP1H TYP2H TYP3H TYP4H TYP5H TYP6H TYP7H TYP8H TYP9H TYP10H TYP11H TYP12H TYP13H TYP14H TYP15H
$gdxin

*Set active simulations (with base sim always active)
 SIMC(SIM)$(ACTIVE(SIM) NE 0) = YES;
 SIMC('BASE') = YES;
 
*All simulations except BASE
 SIMNB(SIMC)   = YES;
 SIMNB('BASE') = NO;

*Aggregate multiple imported parameters from each SIM worksheet into single parameters subcripted on SIM
$include includes\static\stat_process.inc


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
 NUMERAIRE              1   2   1
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
 NUMERAIRE(SIMNB) = MCLOSE('NUMERAIRE',SIMNB);
 SICLOSE(SIMNB)   = MCLOSE('SAVINGS-INVESTMENT',SIMNB); 
 ROWCLOSE(SIMNB)  = MCLOSE('CURRENT-ACCOUNT',SIMNB);
 GOVCLOSE(SIMNB)  = MCLOSE('GOVERNMENT-ACCOUNT',SIMNB);
 
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
 MPS01SIM(INSDNG,SIMNB)$(ASIMH(INSDNG,'SAVE',SIMNB) EQ 2) = 0;
 TI01SIM(INSDNG,SIMNB)$(ASIMH(INSDNG,'TAX',SIMNB) EQ 2)   = 0;
 TA01SIM(A,SIMNB)$(ASIMA(A,'TAX',SIMNB) EQ 2)             = 0;      
 TV01SIM(A,SIMNB)$(ASIMA(A,'TAX',SIMNB) EQ 2)             = 0;
 TE01SIM(C,SIMNB)$(ASIMC(C,'TAX',SIMNB) EQ 2)             = 0;      
 TM01SIM(C,SIMNB)$(ASIMC(C,'TAX',SIMNB) EQ 2)             = 0;      
 TQ01SIM(C,SIMNB)$(ASIMC(C,'TAX',SIMNB) EQ 2)             = 0;      
 TF01SIM(F,SIMNB)$(ASIMF(F,'TAX',SIMNB) EQ 2)             = 0;
 
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

*Sectors with fixed capital stocks 
 AFIXCAP(A,SIM) = NO;
 AFIXCAP(A,SIM)$(ASIMA(A,'FIXCAP',SIM) NE 0) = YES;

*Sectors with fixed land stocks 
 AFIXLND(A,SIM) = NO;
 AFIXLND(A,SIM)$(ASIMA(A,'FIXLND',SIM) NE 0) = YES;
 
*Set factor closures to default value (1 = fully employed and mobile across activities)
 FACCLOSE(F,SIM) = 1;

*For non-base simulations, replace with imported simulation data (if withint max-min bounds)
 FACCLOSE(F,SIMNB) = FCLOSE(F,SIMNB); 
 

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
 PWESIM(C,SIM)          world price for exports
 PWMSIM(C,SIM)          world price for imports
 TEADJSIM(SIM)          export tax (TE) scaling factor
 DTESIM(SIM)            additive export tax (TE) adjustment
 TESIM(C,SIM)           export tax rate (commodity-specific)
 TMADJSIM(SIM)          import tariff (TM) scaling factor
 DTMSIM(SIM)            additive import tariff (TM) adjustment
 TMSIM(C,SIM)           import tariff rate (commodity-specific)
 TQADJSIM(SIM)          composite commodity tax (TQ) scaling factor
 DTQSIM(SIM)            additive sales tax (TQ) adjustment
 TQSIM(C,SIM)           sales tax rate (commodity-specific)
 ICESIM(C,CP,SIM)       export transaction costs
 ICMSIM(C,CP,SIM)       import transaction costs
 ICDSIM(C,CP,SIM)       domestic transaction costs
*Activity shock parameters
 ALPHAVASIM(A,SIM)      total factor productivity (TFP)
 TAADJSIM(SIM)          activity tax (TA) scaling factor
 DTASIM(SIM)            additive activity tax (TA) adjustment
 TASIM(A,SIM)           activity tax rate (activity-specific)
 TVADJSIM(SIM)          value-added tax (TVA) scaling factor
 DTVSIM(SIM)            additive value-added tax (TVA) adjustment
 TVSIM(A,SIM)           value added tax rate (activity-specific)
*Factor shock parameters
 WFSIM(F,SIM)           economywide wage-rental rate
 QFSSIM(F,SIM)          factor supply
 QFSIM(F,A,SIM)         factor demand
 ALPHAFSIM(F,A,SIM)     factor-specific productivity
 TFADJSIM(SIM)          direct factor tax (TF) scaling factor
 DTFSIM(SIM)            additive direct factor tax (TF) adjustment
 TFSIM(F,SIM)           factor tax rate (factor-specific)
 TRNSFSIM(F,INS,SIM)    factor transfers from government and rest of world
 SHIFSIM(INS,F,SIM)     share of factor income transferred to government and rest of world 
*Institution shock parameters
 POPSIM(H,SIM)          household populations   
 MPSADJSIM(SIM)         institutional savings rate scaling factor
 DMPSSIM(SIM)           additive institutional savings rate adjustment
 MPSSIM(INS,SIM)        institutional savings rate (institution-specific)
 TIADJSIM(SIM)          direct tax (TINS) scaling factor
 DTISIM(SIM)            additive domestic institution tax (TINS) adjustment
 TISIM(INS,SIM)         direct tax rate (institution-specific)
 TRNSISIM(INS,INSP,SIM) domestic institution transfers from government and rest of world
 SHIISIM(INS,INS,SIM)   share of domestic non-government institution income transferred to government and rest of world
*Macro shock parameters
 EXRSIM(SIM)            exchange rate
 FSAVSIM(SIM)           foreign savings
 IADJSIM(SIM)           investment adjustment factor
 INVSHRSIM(SIM)         investment share of absorption
 GSAVSIM(SIM)           government savings
 GADJSIM(SIM)           government spending
 GOVSHRSIM(SIM)         government consumption share of absorption
;


*--- Initialize shock parameters to base year values ---

*Commodity shocks 
*  World prices (PWE, PWM)
 PWESIM(C,SIMC) = pwe0(C);
 PWMSIM(C,SIMC) = pwm0(C);
*  Export tax (TE) rate
 TEADJSIM(SIMC) = TEADJ0;
 DTESIM(SIMC)   = DTE0;
 TESIM(C,SIMC)  = TE0(C);
*  Import tariff (TM) rate
 TMADJSIM(SIMC) = TMADJ0;
 DTMSIM(SIMC)   = DTM0;
 TMSIM(C,SIMC)  = TM0(C);
*  Composite commodity tax (TQ) rate 
 TQADJSIM(SIMC) = TQADJ0;
 DTQSIM(SIMC)   = DTQ0;
 TQSIM(C,SIMC)  = TQ0(C);
*  Transaction costs (ice, icm, icd)
 ICESIM(C,CP,SIMC) = ice0(C,CP);
 ICMSIM(C,CP,SIMC) = icm0(C,CP);
 ICDSIM(C,CP,SIMC) = icd0(C,CP);

*Activities
*  Total factor productivity (TFP)
 ALPHAVASIM(A,SIMC) = alphava0(A);   
*  Activity tax (TA) rate
 TAADJSIM(SIMC) = TAADJ0;
 DTASIM(SIMC)   = DTA0;
 TASIM(A,SIMC)  = TA0(A);
*  Value-added tax (TVA) rate 
 TVADJSIM(SIMC) = TVADJ0;
 DTVSIM(SIMC)   = DTV0;         
 TVSIM(A,SIMC)  = TV0(A);
 
*Factors
*  Economywide wage-rental rate (WF)
 WFSIM(F,SIMC) = WF0(F);
*  Factor supply (QFS)
 QFSSIM(F,SIMC)  = QFS0(F);
*  Factor demand (QF)
 QFSIM(F,A,SIMC) = QF0(F,A);
*  Factor-specific productivity (alphaf)
 ALPHAFSIM(F,A,SIMC) = alphaf0(F,A);
*  Direct factor tax (TF) rate  
 TFADJSIM(SIMC) = TFADJ0;
 DTFSIM(SIMC)   = DTF0;
 TFSIM(F,SIMC)  = TF0(F);
*  Share of factor income transferred to government and rest of world (shif)
 SHIFSIM(INS,F,SIMC) = shif0(INS,F);
*  Factor transfers from government and rest of world (trnsf)
 TRNSFSIM(F,INS,SIMC)    = trnsf0(F,INS);
 
*Institutions
*  Household populations (POP)  
 POPSIM(H,SIMC) = pop0(H);
*  Institutional savings (MPS) rate
 MPSADJSIM(SIMC) = MPSADJ0;
 DMPSSIM(SIMC)   = DMPS0;
 MPSSIM(H,SIMC)  = MPS0(H);
*  Direct tax (TI) rate
 TIADJSIM(SIMC) = TIADJ0;
 DTISIM(SIMC)   = DTI0;
 TISIM(H,SIMC)  = TI0(H);
*  Share of domestic non-government institution income transferred to government and rest of world (shii)
 SHIISIM(INS,INSDNG,SIMC) = shii0(INS,INSDNG);
*  Domestic non-government institution transfers from government and rest of world (trnsi)
 TRNSISIM(INS,INSP,SIMC) = trnsi0(INS,INSP);
 
*Macro/scalar 
*  Exchange rate (EXR)
 EXRSIM(SIMC) = EXR0;
*  Foreign savings (FSAV)
 FSAVSIM(SIMC) = FSAV0;
*  Investment adjustment factor (IADJ)
 IADJSIM(SIMC) = IADJ0;
*  Government savings (GSAV)
 GSAVSIM(SIMC) = GSAV0;
*  Government spending (GADJ)
 GADJSIM(SIMC) = GADJ0;
*  Investment share of absorption (INVSHR)
 INVSHRSIM(SIMC) = INVSHR0;
*  Government share of absorption (GOVSHR)
 GOVSHRSIM(SIMC) = GOVSHR0;
 

*--- Update shock parameters with imported baseline and shock simulation data ---

*Commodity shocks

*  World price for exports
 PWESIM(C,SIM)$(ATYPC('PWE',SIM) EQ 1) = pwe0(C) * (1+ASIMC(C,'PWE',SIM)/100);
 PWESIM(C,SIM)$(ATYPC('PWE',SIM) EQ 2) = pwe0(C) + ASIMC(C,'PWE',SIM);

*  World price for imports
 PWMSIM(C,SIM)$(ATYPC('PWM',SIM) EQ 1) = pwm0(C) * (1+ASIMC(C,'PWM',SIM)/100);
 PWMSIM(C,SIM)$(ATYPC('PWM',SIM) EQ 2) = pwm0(C) + ASIMC(C,'PWM',SIM);
 
*  Export tax (TE) rate
 TESIM(C,SIM)$(ATYPS('TE',SIM) EQ 1)  = TE0(C) * (1+ASIMS('TE',SIM)/100); 
 TESIM(C,SIM)$(ATYPS('TE',SIM) EQ 2)  = TE0(C) + ASIMS('TE',SIM)/100; 
 TESIM(C,SIM)$(ATYPC('TE',SIM) EQ 1 AND TESIM(C,SIM) EQ TE0(C))  = TE0(C) * (1+ASIMC(C,'TE',SIM)/100); 
 TESIM(C,SIM)$(ATYPC('TE',SIM) EQ 2 AND TESIM(C,SIM) EQ TE0(C))  = TE0(C) + ASIMC(C,'TE',SIM)/100; 

*  Import tariff (TM) rate
 TMSIM(C,SIM)$(ATYPS('TM',SIM) EQ 1)  = TM0(C) * (1+ASIMS('TM',SIM)/100); 
 TMSIM(C,SIM)$(ATYPS('TM',SIM) EQ 2)  = TM0(C) + ASIMS('TM',SIM)/100;
 TMSIM(C,SIM)$(ATYPC('TM',SIM) EQ 1 AND TMSIM(C,SIM) EQ TM0(C))  = TM0(C) * (1+ASIMC(C,'TM',SIM)/100); 
 TMSIM(C,SIM)$(ATYPC('TM',SIM) EQ 2 AND TMSIM(C,SIM) EQ TM0(C))  = TM0(C) + ASIMC(C,'TM',SIM)/100;
 
*  Composite commodity tax (TQ) rate
 TQSIM(C,SIM)$(ATYPS('TQ',SIM) EQ 1)  = TQ0(C) * (1+ASIMS('TQ',SIM)/100); 
 TQSIM(C,SIM)$(ATYPS('TQ',SIM) EQ 2)  = TQ0(C) + ASIMS('TQ',SIM)/100; 
 TQSIM(C,SIM)$(ATYPC('TQ',SIM) EQ 1 AND TQSIM(C,SIM) EQ TQ0(C))  = TQ0(C) * (1+ASIMC(C,'TQ',SIM)/100); 
 TQSIM(C,SIM)$(ATYPC('TQ',SIM) EQ 2 AND TQSIM(C,SIM) EQ TQ0(C))  = TQ0(C) + ASIMC(C,'TQ',SIM)/100; 

*  Export transaction costs
*    Only apply shock if commodity is a supplier of transaction cost demand (e.g., transport, trade services)
 ICESIM(C,CP,SIM)$(SUM(CPP, ice0(C,CPP)) AND ATYPC('ICE',SIM) EQ 1) = ice0(C,CP) * (1+ASIMC(CP,'ICE',SIM)/100);
 ICESIM(C,CP,SIM)$(SUM(CPP, ice0(C,CPP)) AND ATYPC('ICE',SIM) EQ 2) = ice0(C,CP) + ASIMC(CP,'ICE',SIM);
 
*  Import transaction costs
*    Only apply shock if commodity is a supplier of transaction cost demand (e.g., transport, trade services)
 ICMSIM(C,CP,SIM)$(SUM(CPP, icm0(C,CPP)) AND ATYPC('ICM',SIM) EQ 1) = icm0(C,CP) * (1+ASIMC(CP,'ICM',SIM)/100);
 ICMSIM(C,CP,SIM)$(SUM(CPP, icm0(C,CPP)) AND ATYPC('ICM',SIM) EQ 2) = icm0(C,CP) + ASIMC(CP,'ICM',SIM);
 
*  Domestic transaction costs
*    Only apply shock if commodity is a supplier of transaction cost demand (e.g., transport, trade services)
 ICDSIM(C,CP,SIM)$(SUM(CPP, icd0(C,CPP)) AND ATYPC('ICD',SIM) EQ 1) = icd0(C,CP) * (1+ASIMC(CP,'ICD',SIM)/100);
 ICDSIM(C,CP,SIM)$(SUM(CPP, icd0(C,CPP)) AND ATYPC('ICD',SIM) EQ 2) = icd0(C,CP) + ASIMC(CP,'ICD',SIM);

*Activity shocks

*  Total factor productivity (TFP)
 ALPHAVASIM(A,SIM)$(ATYPA('ALPHAVA',SIM) EQ 1) = alphava0(A) * (1+ASIMA(A,'ALPHAVA',SIM)/100);
 ALPHAVASIM(A,SIM)$(ATYPA('ALPHAVA',SIM) EQ 2) = alphava0(A) + ASIMA(A,'ALPHAVA',SIM);
 
*  Activity tax (TA) rate
 TASIM(A,SIM)$(ATYPS('TA',SIM) EQ 1)  = TA0(A) * (1+ASIMS('TA',SIM)/100); 
 TASIM(A,SIM)$(ATYPS('TA',SIM) EQ 2)  = TA0(A) + ASIMS('TA',SIM)/100; 
 TASIM(A,SIM)$(ATYPA('TA',SIM) EQ 1 AND TASIM(A,SIM) EQ TA0(A))  = TA0(A) * (1+ASIMA(A,'TA',SIM)/100); 
 TASIM(A,SIM)$(ATYPA('TA',SIM) EQ 2 AND TASIM(A,SIM) EQ TA0(A))  = TA0(A) + ASIMA(A,'TA',SIM)/100; 
 
*  Value-added tax (TVA) rate
 TVSIM(A,SIM)$(ATYPS('TV',SIM) EQ 1)  = TV0(A) * (1+ASIMS('TV',SIM)/100); 
 TVSIM(A,SIM)$(ATYPS('TV',SIM) EQ 2)  = TV0(A) + ASIMS('TV',SIM)/100; 
 TVSIM(A,SIM)$(ATYPA('TV',SIM) EQ 1 AND TVSIM(A,SIM) EQ TV0(A))  = TV0(A) * (1+ASIMA(A,'TV',SIM)/100); 
 TVSIM(A,SIM)$(ATYPA('TV',SIM) EQ 2 AND TVSIM(A,SIM) EQ TV0(A))  = TV0(A) + ASIMA(A,'TV',SIM)/100; 

*Factor shocks
 
*  Economywide wage-rental rate
*    Shock is ineffective when factor is fully employed and variable WF is flexible (FACCLOS = 1)
 WFSIM(F,SIM)$(ATYPF('WF',SIM) EQ 1) = WF0(F) * (1+ASIMF(F,'WF',SIM)/100);
 WFSIM(F,SIM)$(ATYPF('WF',SIM) EQ 2) = WF0(F) + ASIMF(F,'WF',SIM);
 
*  Factor supply
*    Shock is ineffective when factor is unemployed or sector-specific and variable QFS is flexible (FACCLOS = 2,3)
 QFSSIM(F,SIM)$(ATYPF('QFS',SIM) EQ 1) = QFS0(F) * (1+ASIMF(F,'QFS',SIM)/100);
 QFSSIM(F,SIM)$(ATYPF('QFS',SIM) EQ 2) = QFS0(F) + ASIMF(F,'QFS',SIM);
 
*  Factor demand (QF)
*    Shock is ineffective when factor is unemployed or mobile across activities (FACCLOS = 1,3)
 QFSIM(FCAP,A,SIM)$(ASIMA(A,'FIXCAP',SIM) NE 0) = QFS0(FCAP) * (1+ASIMA(A,'FIXCAP',SIM)/100);
 QFSIM(FLND,A,SIM)$(ASIMA(A,'FIXLND',SIM) NE 0) = QFS0(FLND) + (1+ASIMA(A,'FIXLND',SIM)/100);
 
*  Factor-specific productivity
*    Shock is both factor- and sector-specific (activities excluded from shock are selected in the activity block on the simulation Excel worksheets).   
 ALPHAFSIM(F,A,SIM)$(ATYPF('QFS',SIM) EQ 1 AND ASIMA(A,'ALPHAF',SIM) EQ 1) = alphaf0(F,A) * (1+ASIMF(F,'ALPHAF',SIM)/100);
 ALPHAFSIM(F,A,SIM)$(ATYPF('QFS',SIM) EQ 2 AND ASIMA(A,'ALPHAF',SIM) EQ 1) = alphaf0(F,A) + ASIMF(F,'ALPHAF',SIM);
 
*  Direct factor tax (TF) rate
 TFSIM(F,SIM)$(ATYPS('TF',SIM) EQ 1)  = TF0(F) * (1+ASIMS('TF',SIM)/100); 
 TFSIM(F,SIM)$(ATYPS('TF',SIM) EQ 2)  = TF0(F) + ASIMS('TF',SIM)/100;
 TFSIM(F,SIM)$(ATYPF('TF',SIM) EQ 1 AND TFSIM(F,SIM) EQ TF0(F))  = TF0(F) * (1+ASIMF(F,'TF',SIM)/100); 
 TFSIM(F,SIM)$(ATYPF('TF',SIM) EQ 2 AND TFSIM(F,SIM) EQ TF0(F))  = TF0(F) + ASIMF(F,'TF',SIM)/100;
 
*  Share of factor income transferred to government and rest of world (shif)
*    Shock factor income transferred to government 
 SHIFSIM(GV,F,SIMC)$(ATYPF('TRTG',SIMC) EQ 1) = shif0(GV,F) * (1+ASIMF(F,'TRTG',SIMC)/100);
 SHIFSIM(GV,F,SIMC)$(ATYPF('TRTG',SIMC) EQ 2) = shif0(GV,F) + ASIMF(F,'TRTG',SIMC)/100; 
*    Shock factor income transferred to rest of world
 SHIFSIM(RW,F,SIMC)$(ATYPF('TRTW',SIMC) EQ 1) = shif0(RW,F) * (1+ASIMF(F,'TRTW',SIMC)/100);
 SHIFSIM(RW,F,SIMC)$(ATYPF('TRTW',SIMC) EQ 2) = shif0(RW,F) + ASIMF(F,'TRTW',SIMC)/100;
*    Recalculate non-government and non-ROW shares 
 SHIFSIM(INSDNG,F,SIMC)$SUM(INSDNGP, shif0(INSDNGP,F))
    = SHIF0(INSDNG,F) / SUM(INSDNGP, shif0(INSDNGP,F)) * (1 - SHIFSIM(GV,F,SIMC) - SHIFSIM(RW,F,SIMC));
 
*  Factor transfers from government and rest of world (trnsf)
*    Shock government transfers to factors
 TRNSFSIM(F,GV,SIMC)$(ATYPF('TRFG',SIMC) EQ 1) = trnsf0(F,GV) * (1+ASIMF(F,'TRFG',SIMC)/100);
 TRNSFSIM(F,GV,SIMC)$(ATYPF('TRFG',SIMC) EQ 2) = trnsf0(F,GV) + ASIMF(F,'TRFG',SIMC);
*    Shock rest of world transfers to factors
 TRNSFSIM(F,RW,SIMC)$(ATYPF('TRFW',SIMC) EQ 1) = trnsf0(F,RW) * (1+ASIMF(F,'TRFW',SIMC)/100);
 TRNSFSIM(F,RW,SIMC)$(ATYPF('TRFW',SIMC) EQ 2) = trnsf0(F,RW) + ASIMF(F,'TRFW',SIMC);

*Institution shocks 

*  Household populations (POP)  
 POPSIM(H,SIM)$(ATYPH('POP',SIM) EQ 1) = pop0(H) * (1+ASIMH(H,'POP',SIM)/100);
 POPSIM(H,SIM)$(ATYPH('POP',SIM) EQ 2) = pop0(H) * ASIMH(H,'POP',SIM);

*  Institutional savings (MPS) rate
 MPSSIM(INSDNG,SIM)$(ATYPS('MPS',SIM) EQ 1)  = MPS0(INSDNG) * (1+ASIMS('MPS',SIM)/100); 
 MPSSIM(INSDNG,SIM)$(ATYPS('MPS',SIM) EQ 2)  = MPS0(INSDNG) + ASIMS('MPS',SIM)/100;  
 MPSSIM(INSDNG,SIM)$(ATYPH('MPS',SIM) EQ 1 AND MPSSIM(INSDNG,SIM) EQ MPS0(INSDNG))  = MPS0(INSDNG) * (1+ASIMH(INSDNG,'MPS',SIM)/100); 
 MPSSIM(INSDNG,SIM)$(ATYPH('MPS',SIM) EQ 2 AND MPSSIM(INSDNG,SIM) EQ MPS0(INSDNG))  = MPS0(INSDNG) + ASIMH(INSDNG,'MPS',SIM)/100;  
 
*  Direct tax (TINS) rate
 TISIM(INSDNG,SIM)$(ATYPS('TI',SIM) EQ 1)  = TI0(INSDNG) * (1+ASIMS('TI',SIM)/100); 
 TISIM(INSDNG,SIM)$(ATYPS('TI',SIM) EQ 2)  = TI0(INSDNG) + ASIMS('TI',SIM)/100;
 TISIM(INSDNG,SIM)$(ATYPH('TI',SIM) EQ 1 AND TISIM(INSDNG,SIM) EQ TI0(INSDNG))  = TI0(INSDNG) * (1+ASIMH(INSDNG,'TI',SIM)/100); 
 TISIM(INSDNG,SIM)$(ATYPH('TI',SIM) EQ 2 AND TISIM(INSDNG,SIM) EQ TI0(INSDNG))  = TI0(INSDNG) + ASIMH(INSDNG,'TI',SIM)/100;
 

*  Share of domestic non-government institution income transferred to government and rest of world (shii)
*    Shock domestic non-government instituional income transferred to government 
 SHIISIM(GV,INSDNG,SIMC)$(ATYPH('TRTG',SIMC) EQ 1) = shii0(GV,INSDNG) * (1+ASIMH(INSDNG,'TRTG',SIMC)/100);
 SHIISIM(GV,INSDNG,SIMC)$(ATYPH('TRTG',SIMC) EQ 2) = shii0(GV,INSDNG) + ASIMH(INSDNG,'TRTG',SIMC)/100; 
*    Shock institution income transferred to rest of world       
 SHIISIM(RW,INSDNG,SIMC)$(ATYPH('TRTW',SIMC) EQ 1) = shii0(RW,INSDNG) * (1+ASIMH(INSDNG,'TRTW',SIMC)/100);
 SHIISIM(RW,INSDNG,SIMC)$(ATYPH('TRTW',SIMC) EQ 2) = shii0(RW,INSDNG) + ASIMH(INSDNG,'TRTW',SIMC)/100;
*    Recalculate non-government and non-ROW shares 
 SHIISIM(INSDNGP,INSDNG,SIMC)$(1 - shii0(GV,INSDNG) - shii0(RW,INSDNG))
    = shii0(INSDNGP,INSDNG) / (1 - shii0(GV,INSDNG) - shii0(RW,INSDNG)) * (1 - SHIISIM(GV,INSDNG,SIMC) - SHIISIM(RW,INSDNG,SIMC));
 
*  Domestic non-government institution transfers from government and rest of world (trnsi)
*    Shock government transfers to domestic non-government institutions
 TRNSISIM(INSDNG,GV,SIMC)$(ATYPH('TRFG',SIMC) EQ 1) = trnsi0(INSDNG,GV) * (1+ASIMH(INSDNG,'TRFG',SIMC)/100);
 TRNSISIM(INSDNG,GV,SIMC)$(ATYPH('TRFG',SIMC) EQ 2) = trnsi0(INSDNG,GV) + ASIMH(INSDNG,'TRFG',SIMC);
*    Shock rest of world transfers to domestic non-government institutions
 TRNSISIM(INSDNG,RW,SIMC)$(ATYPH('TRFW',SIMC) EQ 1) = trnsi0(INSDNG,RW) * (1+ASIMH(INSDNG,'TRFW',SIMC)/100);
 TRNSISIM(INSDNG,RW,SIMC)$(ATYPH('TRFW',SIMC) EQ 2) = trnsi0(INSDNG,RW) + ASIMH(INSDNG,'TRFW',SIMC);

*Macro/scalar shocks

*  Exchange rate
*    Shock is ineffective when variable EXR is flexible (ROWCLOS = 1)
 EXRSIM(SIM)$(ATYPS('EXR',SIM) EQ 1) = EXR0 * (1+ASIMS('EXR',SIM)/100);
 EXRSIM(SIM)$(ATYPS('EXR',SIM) EQ 2) = EXR0 * ASIMS('EXR',SIM);

*  Foreign savings
*    Shock is ineffective when variable FSAV is flexible (ROWCLOS = 2)
 FSAVSIM(SIM)$(ATYPS('FSAV',SIM) EQ 1) = FSAV0 * (1+ASIMS('FSAV',SIM)/100);
 FSAVSIM(SIM)$(ATYPS('FSAV',SIM) EQ 2) = FSAV0 + ASIMS('FSAV',SIM);
 
*  Investment adjustment factor
*    Shock is ineffective when variable IADJ is flexible (SICLOS = 3,4,5)
 IADJSIM(SIM)$(ATYPS('IADJ',SIM) EQ 1) = IADJ0 * (1+ASIMS('IADJ',SIM)/100);
 IADJSIM(SIM)$(ATYPS('IADJ',SIM) EQ 2) = IADJ0 + ASIMS('IADJ',SIM)/100;
 
*  Investment share of absorption 
*    Shock is ineffective when variable INVSHR is flexible (SICLOS = 1,2,3)
 INVSHRSIM(SIM)$(ATYPS('INVSHR',SIM) EQ 1) = INVSHR0 * (1+ASIMS('INVSHR',SIM)/100);
 INVSHRSIM(SIM)$(ATYPS('INVSHR',SIM) EQ 2) = INVSHR0 + ASIMS('INVSHR',SIM)/100;
 
*  Government savings
*    Shock is ineffective when variable GSAV is flexible (GOVCLOS = 1)
 GSAVSIM(SIM)$(ATYPS('GSAV',SIM) EQ 1) = GSAV0 * (1+ASIMS('GSAV',SIM)/100);
 GSAVSIM(SIM)$(ATYPS('GSAV',SIM) EQ 2) = GSAV0 + ASIMS('GSAV',SIM);

*  Government spending
*    Shock is ineffective when variable GADJ is flexible (SICLOS = 4,5)
 GADJSIM(SIM)$(ATYPS('GADJ',SIM) EQ 1) = GADJ0 * (1+ASIMS('GADJ',SIM)/100);
 GADJSIM(SIM)$(ATYPS('GADJ',SIM) EQ 2) = GADJ0 + ASIMS('GADJ',SIM)/100;

*  Government share of absorption 
*    Shock is ineffective when variable GOVSHR is flexible (SICLOS = 1,2,3)
 GOVSHRSIM(SIM)$(ATYPS('GOVSHR',SIM) EQ 1) = GOVSHR0 * (1+ASIMS('GOVSHR',SIM)/100);
 GOVSHRSIM(SIM)$(ATYPS('GOVSHR',SIM) EQ 2) = GOVSHR0 + ASIMS('GOVSHR',SIM)/100;
 
*  Government transfers to and from rest of world (trnsi)
*    Shock government transfers to rest of world
 TRNSISIM(RW,GV,SIMC)$(ATYPS('TRTW',SIMC) EQ 1) = trnsi0(RW,GV) * (1+ASIMS('TRTW',SIMC)/100);
 TRNSISIM(RW,GV,SIMC)$(ATYPS('TRTW',SIMC) EQ 2) = trnsi0(RW,GV) + ASIMS('TRTW',SIMC);
*    Shock rest of world transfers to government 
 TRNSISIM(GV,RW,SIMC)$(ATYPS('TRFW',SIMC) EQ 1) = trnsi0(GV,RW) * (1+ASIMS('TRFW',SIMC)/100);
 TRNSISIM(GV,RW,SIMC)$(ATYPS('TRFW',SIMC) EQ 2) = trnsi0(GV,RW) + ASIMS('TRFW',SIMC);


