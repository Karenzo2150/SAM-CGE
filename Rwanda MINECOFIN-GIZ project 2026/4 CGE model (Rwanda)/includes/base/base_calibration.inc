$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 1.5: Calibrate base model   
 This include file (includes\1base_calibrate.inc) uses the imported country data to calibrate
 the base model's sets, parameters, and variables.

SECTIONS:
 1.5.1  Declare calibration parameters, including base year values
 1.5.2  Prices and quantities  
 1.5.3  Production and trade
 1.5.4  Institutions
 1.5.5  LES calibration
 1.5.6  System constraints
 1.5.7  Initialize variables 
 1.5.8  Fixing variables not in the model to zero
 1.5.9  Base model closures
$offtext


*------------------------------------------------------------------
* 1.5.1  Declare calibration parameters, including base year values
*------------------------------------------------------------------

*For model calibration, one parameter is created for each model variable with the suffix "0" added to the variable name.
*  0 is also added to the names of parameters whose values are changed in experiments.

PARAMETERS
*Model parameters base year values
 alphaf0(F,A)       productivity shift for factor F in activity A
 alphava0(A)        shift parameter for CES activity production function
 betah0(A,H)        marginal share of household consumption on home commodity C from activity A
 betam0(C,H)        marginal share of household consumption on marketed commodity C
 gammah0(A,H)       per-capita subsistence consumption for household H on home commodity C for activity A
 gammam0(C,H)       per-capita subsistence consumption of marketed commodity C for household H
 icd0(C,CP)         trade input of C per unit of commodity CP produced & sold domestically
 ice0(C,CP)         trade input of C per unit of commodity CP exported
 icm0(C,CP)         trade input of C per unit of commodity CP imported
 pop0(H)            total population of workers and non-workers in household H
 pwe0(C)            world price of exports
 pwm0(C)            world price of imports
 qbarg0(C)          exogenous (unscaled) government demand
 qbarinv0(C)        exogenous (unscaled) investment demand
 qdst0(C)           inventory investment by sector of origin
 shif0(AC,ACP)      share of institution INS (incl. rest of world) in post-tax income of factor F
 shii0(AC,ACP)      share of institution INS in post-tax post-savings income of institution INSP
 trnsf0(F,INS)      transfers from factor F to institution INS (including rest of world)
 trnsi0(INS,INSP)   transfers from institution INS) to institution INSP (including rest of world)
*Model variables    base year values
 CPI0               consumer price index (PQ-based)
 DMPS0              change in marginal propensity to save for selected institution
 DPI0               index for domestic producer prices (PDS-based)
 DTA0               additive activity tax (TA) adjustment
 DTE0               additive export tax (TE) adjustment
 DTF0               additive direct factor tax (TF) adjustment
 DTI0               additive domestic institution tax (TI) adjustment
 DTM0               additive import tariff (TM) adjustment
 DTQ0               additive sales tax (TQ) adjustment
 DTV0               additive value-added tax (TV) adjustment
 EG0                total current government expenditure
 EH0(H)             household consumption expenditure
 EXR0               exchange rate
 FSAV0              foreign savings
 GADJ0              government demand scaling factor
 GOVSHR0            government consumption share of absorption
 GSAV0              government savings
 IADJ0              investment scaling factor (for fixed capital formation)
 INVSHR0            investment share of absorption
 MPS0(AC)           marginal propensity to save for domestic non-government institution INS
 MPSADJ0            savings rate (MPS) scaling factor
 PA0(A)             output price of activity A
 PDD0(C)            demand price for commodity C produced and sold domestically
 PDS0(C)            supply price for commodity C produced and sold domestically
 PE0(C)             price of export aggregate to producer excluding transport costs
 PINTA0(A)          price of intermediate aggregate
 PM0(C)             price of import aggregate to demander including transport costs
 PQ0(C)             price of composite commodity C
 PSAV0              total private savings
 PVA0(A)            value added price
 PX0(C)             average output price
 PXAC0(A,C)         price of commodity C from activity A
 QA0(A)             level of domestic activity
 QD0(C)             quantity of domestic sales
 QE0(C)             quantity of exports
 QF0(F,A)           quantity demanded of factor F from activity A
 QFS0(F)            quantity of factor supply
 QG0(C)             quantity of government consumption
 QH0(C,H)           quantity consumed of marketed commodity C by household H
 QHA0(A,H)          quantity consumed of home activity A by household H
 QINT0(C,A)         quantity of intermediate demand for commodity C from activity A
 QINTA0(A)          quantity of aggregate intermediate input
 QINV0(C)           quantity of fixed investment demand
 QM0(C)             quantity of imports
 QQ0(C)             quantity of composite goods supply
 QT0(C)             quantity of trade and transport demand for commodity C
 QVA0(A)            quantity of aggregate value added
 QX0(C)             quantity of aggregate marketed commodity output
 QXAC0(A,C)         quantity of ouput of commodity C from activity A 
 TA0(A)             activity tax rates
 TAADJ0             activity tax (TA) scaling factor
 TABS0              total absorption
 TE0(C)             export tax rates
 TEADJ0             export tax (TE) scaling factor
 TF0(F)             direct factor tax rates
 TFADJ0             factor tax (TF) scaling factor
 TI0(AC)            direct tax rates on domestic institutions INSD
 TIADJ0             direct tax (TI) scaling factor
 TM0(C)             import tariff rates
 TMADJ0             import tariff (TM) scaling factor
 TRII0(AC,ACP)      transfers from column institutions INSF to row institutions INS
 TQ0(C)             composite commodity taxes
 TQADJ0             composite commodity tax (TQ) scaling factor
 TV0(A)             value-added tax rates
 TVADJ0             value-added tax (TV) scaling factor
 WALRAS0            savings-investment imbalance (should be zero)
 WF0(F)             economy-wide wage (rent) for factor F
 WFDIST0(F,A)       wage distortion variable for factor F in activity A
 YF0(F)             factor income from activities
 YG0                total government income
 YIF0(INS,F)        income of institution INS from factor F
 YI0(INS)           income of domestic non-government institution INS
;                   
                    
                    
*------------------ ------------------------------------------------
* 1.5.2  Prices and quantities
*------------------------------------------------------------------

$ontext
 The prices PDS, PX, and PE  may be initialized at any desired price. The user may prefer to initialize these prices at
 unity or, if he/she is interested in tracking commodity flows in physical units, at commodity-specific, observed prices
 (per physical unit). For any given commodity, these three prices should be identical. Initialization at observed prices
 may be attractive for disaggregated agricultural commodities. If so, the corresponding quantity values reflect physical
 units (given the initial price).

 The remaining supply-side price, PXAC, and the non-commodity prices, EXR and PA may be initizalized at any desired
 level. In practice, it may be preferable to initialize PXAC at the relevant supply-side price and EXR and PA at unity.

 If physical units are used, the user should select the unit (tons vs. '000 tons) so that initial price and quantity
 variables are reasonably scaled (for example between 1.0E-2 and 1.0E+3) -- bad scaling may cause solver problems.
 Initialization at unity should cause no problem as long as the initial SAM is reasonably scaled.
$offtext

PARAMETER
 PSUP(C)            initial supply-side market price for commodity C
 SHCTD(C)           share of commodity CT in transaction services for domestic sales
 SHCTE(C)           share of commodity CT in transaction services for exports
 SHCTM(C)           share of commodity CT in transaction services for imports
;

 PSUP(C)               = 1;
 PE0(C)$CE(C)          = PSUP(C);
 PX0(C)$CX(C)          = PSUP(C);
 PDS0(C)$CD(C)         = PSUP(C);
 PXAC0(A,C)$SAM(A,C)   = PSUP(C);
 PA0(A)$SAM('TOTAL',A) = 1;

$ontext
 The exchange rate may be initialized at unity, in which case all data are in foreign currency units (FCU; e.g.,
 dollars). Set the exchange rate at another value to differentiate foreign exchange transactions, which will be valued
 in FCU, and domestic transactions valued in local currency units (LCU). The SAM is assumed to be valued in LCU, and
 the exchange rate is then used to calculate FCU values for transactions with the rest of the world.
$offtext

 EXR0 = EXRBASE;

*Activity quantity = payment to activity divided by activity price.
*  QA covers both on-farm consumption and marketed output output GROSS of tax.
 QA0(A)$PA0(A) = SAM('TOTAL',A)/PA0(A);

*Unit value-added price = total value-added / activity quantity define QVA0 and PVA0 gross of factor taxes.
 QVA0(A)               = SUM(F, SAM(F,A)) + TAXPAR('VATTAX',A);
 PVA0(A)$QVA0(A)       = (SUM(F, SAM(F,A)) + TAXPAR('VATTAX',A))/QVA0(A);
 iva(A)$QA0(A)         = QVA0(A)/QA0(A);
 QXAC0(A,C)$PXAC0(A,C) = SAM(A,C)/PXAC0(A,C);

*Home consumption of activity output
 QHA0(A,H)$PA0(A) = SAM(A,H)/PA0(A);

*Output quantity = value received by producers divided by producer price.
*  QX covers only marketed output.
 QX0(C)$SUM(A, SAM(A,C)) = SUM(A, SAM(A,C)) / PX0(C);

*Export quantity = export revenue received by producers (ie. minus tax and transactions cost) divided by export price.
 QE0(C)$CE(C) = (SAM(C,RW) - TAXPAR('EXPTAX',C) - SAM(CTE,C))/PE0(C);

*World export price = rest of world export payment (in foreign currency) / export quantity.
 pwe0(C)$CE(C) = (SAM(C,RW)/EXR0) / QE0(C);
 pwe(C)        = pwe0(C);

*Export taxes and adjustment factors
 TE0(C)$CE(C)  = TAXPAR('EXPTAX',C)/SAM(C,RW);
 TEADJ0        = 0;
 DTE0          = 0;
 te01(C)$CE(C) = 1;
 tebar(C)      = TE0(C);

*Quantity of output sold domestically = output quantity less quantity exported = value of domestic sales divided by
*  domestic supply price. QD0 covers only marketed output.
 QD0(C)$CD(C) = QX0(C) - QE0(C);

*Domestic demander price = demander payment divided by quantity bought.
 PDD0(C)$QD0(C) = (PDS0(C)*QD0(C) + SAM(CTD,C))/QD0(C);

*Define import price to equal domestic price so that import and domestic units are the same to the purchaser.
*  If no domestic good, set PM to 1.
 PM0(CM) = PDD0(CM);
 PM0(CM)$(QD0(CM) EQ 0) = 1;

*Import quantity = demander payment for imports (including tariffs and marketing cost) divided by demander price.
 QM0(C)$CM(C) = (SAM(RW,C) + TAXPAR('IMPTAX',C) + SAM(CTM,C))/PM0(C);

*World import price = import value (in foreign currency) / import quantity.
 pwm0(C)$CM(C) = (SAM(RW,C)/EXR0) / QM0(C);
 pwm(C) = pwm0(C);

*Import taxes and adjustment factors.
 TM0(C)$CM(C) = TAXPAR('IMPTAX',C)/ SAM(RW,C);
 TMADJ0 = 0;
 DTM0 = 0;
 tm01(C) = 1;
 tmbar(C) = TM0(C);

*Composite supply is the sum of domestic market sales and imports (since they are initialized at the same price).
 QQ0(C)$(CD(C) OR CM(C)) = QD0(C) + QM0(C) ;
 PQ0(C)$QQ0(C) = (SAM(C,'TOTAL') - SAM(C,RW))/QQ0(C);

*Sales taxes and adjustment factors.
 TQ0(C)$QQ0(C) = TAXPAR('COMTAX',C)/(PQ0(C)*QQ0(C));
 TQADJ0 = 0;
 DTQ0 = 0;
 tq01(C) = 1;
 tqbar(C) = TQ0(C);

*The following code works when for any number of sectors providing transactions services, as well as for the case when
*  they are not in the SAM.
 SHCTD(CT) = SAM(CT,CTD)/SAM('TOTAL',CTD);
 SHCTM(CT) = SAM(CT,CTM)/SAM('TOTAL',CTM);
 SHCTE(CT) = SAM(CT,CTE)/SAM('TOTAL',CTE);

*Transactions input coefficients
 icd0(CT,C)$QD0(C) = (SHCTD(CT)*SAM(CTD,C)/PQ0(CT)) / QD0(C);
 ice0(CT,C)$QE0(C) = (SHCTM(CT)*SAM(CTE,C)/PQ0(CT)) / QE0(C);
 icm0(CT,C)$QM0(C) = (SHCTE(CT)*SAM(CTM,C)/PQ0(CT)) / QM0(C);

 icd(CT,C) = icd0(CT,C);
 ice(CT,C) = ice0(CT,C);
 icm(CT,C) = icm0(CT,C);

*Value added taxes. Indirect activity tax rate = tax payment / output value. Tax is here applied to total output value
*  (including own consumption).
 TV0(A)$(PVA0(A)*QVA0(A)) = TAXPAR('VATTAX',A) / (PVA0(A)*QVA0(A));
 TVADJ0 = 0;
 DTV0 = 0;
 tv01(A) = 1;
 tvbar(A) = tv0(A);

*Activity taxes and adjustment factors. QA is GROSS of tax, so base for TA is as well.
 TA0(A)$SAM(A,'TOTAL') = TAXPAR('ACTTAX',A) / SAM(A,'TOTAL');
 DTA0 = 0;
 TAADJ0 = 0;
 ta01(A) = 1;
 tabar(A) = ta0(A);

*Yield coefficient for C-to-A linear aggregation (ACCES(A) = NO). Net out home consumption of activity A before aggregating.
*   Yield coefficient = quantity produced less home-consumed output / activity quantity less home-consumed output.
 theta(A,C)$(PXAC0(A,C) AND (QA0(A) - SUM(H, SAM(A,H)))) = (SAM(A,C)/PXAC0(A,C)) / (QA0(A) - SUM(H, SAM(A,H)));

*Intermediate input coefficient = input use / output quantity.
 QINTA0(A) = SUM(C$PQ0(C), SAM(C,A)/PQ0(C));

 ica(C,A)$(PQ0(C) AND QINTA0(A)) = (SAM(C,A)/PQ0(C)) / QINTA0(A);

 inta(A)$QA0(A) = QINTA0(A) / QA0(A);
 pinta0(A)      = SUM(C, ica(C,A)*PQ0(C));

*CPI weight by commodity = household consumption value for commodity / total household consumption value.
*  CPI does not consider on-farm consumption.
 cwts(C)$SUM((CP,H), SAM(CP,H)) = SUM(H, SAM(C,H)) / SUM((CP,H), SAM(CP,H));

*Domestic sales price index weight = domestic sales value for commodity / total domestic salues value.
*  Domestic sales price index does not consider on-farm consumption.
 dwts(C) = (SUM(A, SAM(A,C)) - (SAM(C,RW) - SUM(cte, SAM(cte,C))))/
            SUM(CP, SUM(A, SAM(A,CP)) - (SAM(CP,RW) - SUM(cte, SAM(cte,CP))));

 CPI0    = SUM(C, cwts(C)*PQ0(C));
 DPI0    = SUM(CD, dwts(CD)*PDS0(CD)) ;


*------------------------------------------------------------------
* 1.5.3  Production and trade
*------------------------------------------------------------------

PARAMETER
 WFA(F,A)           wage for factor f in activity a (used for calibration)
 predeltaa(A)       dummy used to define deltaa
 predelta(C)        dummy used to define deltaq
;

*Compute exponents from elasticites
 rhoa(A)$(AA(A) AND ACES(A))   = (1/AELAS(A,'ELASPRD2')) - 1;
 rhoac(C)$CELAS(C,'ELASAC')    =  1/CELAS(C,'ELASAC')    - 1;
 rhoca(A)$(AA(A) AND ACCES(A)) = (1/AELAS(A,'ELASCA'))   + 1;
 rhoq(C)$(CM(C) AND CD(C))     = (1/CELAS(C,'SIGMAQ'))   - 1;
 rhot(C)$(CE(C) AND CD(C))     = (1/CELAS(C,'SIGMAT'))   + 1;
 rhova(A)$AA(A)                = (1/AELAS(A,'ELASPRD'))  - 1;

*CES aggregation of domestic output from different activities.
 deltaac(A,C)$(SAM(A,C) AND CELAS(C,'ELASAC')) = (PXAC0(A,C)*QXAC0(A,C)**(1/CELAS(C,'ELASAC')))/SUM(AP, PXAC0(AP,C)*QXAC0(AP,C)**(1/CELAS(C,'ELASAC')));
 alphaac(C)$SUM(A,deltaac(A,C)) = QX0(C)/(SUM(A$deltaac(A,C), deltaac(A,C) * QXAC0(A,C)**(-rhoac(C))) )**(-1/rhoac(C));

*CET disaggregation of domestic output to different commodities.
 deltaca(A,C)$QXAC0(A,C) = (PXAC0(A,C)*(QXAC0(A,C))**(1-rhoca(A))) / SUM(CP$QXAC0(A,CP), PXAC0(A,CP)*(QXAC0(A,CP))**(1-rhoca(A)));
 alphaca(A)$ACCES(A)     = (QA0(A) - SUM(H, QHA0(A,H))) / (SUM(C$deltaca(A,C), deltaca(A,C)*QXAC0(A,C)**rhoca(A)))**(1/rhoca(A));

*Defining factor employment and supply.
 QF0(F,A) = QF2BASE(F,A);
 QFS0(F)  = SUM(A, QF0(F,A));

*Economy-wide wage average is total factor income over employment.
 WF0(F)$SUM(A, QF0(F,A)) = SUM(A, SAM(F,A))/SUM(A, QF0(F,A));

*Wage distortion factor.
 WFA(F,A)$SAM(F,A)     = SAM(F,A)/QF0(F,A);
 WFDIST0(F,A)$SAM(F,A) = WFA(F,A)/WF0(F);

*CES activity production function.
 deltava(F,A)$QF0(F,A) = (WFDIST0(F,A)*WF0(F)*(QF0(F,A))**(1+rhova(A))) / SUM(FP, WFDIST0(FP,A)*WF0(FP)*(QF0(FP,A))**(1+rhova(A)));
 alphava0(A)$QVA0(A) = QVA0(A)/(SUM(F$(QF0(F,A)), deltava(F,A)*QF0(F,A)**(-rhova(A))))**(-1/rhova(A));
 alphava(A)   = alphava0(A);
 alphaf0(F,A) = 1;
 alphaf(F,A)  = alphaf0(F,A); 

*CES top level production function.
 predeltaa(A) = 0 ;
 predeltaa(A)$(ACES(A) AND QINTA0(A)) = (PVA0(A)/PINTA0(A))*(QVA0(A)/QINTA0(A))**(1+rhoa(A));
 deltaa(A)$ACES(A) = predeltaa(A)/(1 + predeltaa(A)) ;
 alphaa(A)$deltaa(A) = QA0(A)/((deltaa(A)*QVA0(A)**(-rhoa(A)) + (1-deltaa(A))*QINTA0(A)**(-rhoa(A)))**(-1/rhoa(A)));

*Intermediate demand.
 QINT0(C,A)$PQ0(C) = SAM(C,A) / PQ0(C);

*Transactions demand.
 QT0(CT)$PQ0(CT) = (SUM(CTD, SAM(CT,CTD)) + SUM(CTE, SAM(CT,CTE)) + SUM(CTM, SAM(CT,CTM))) / PQ0(CT);

*CET transformation.
 deltat(C)$(CE(C) AND CD(C)) = 1 / (1 + PDS0(C)/PE0(C)*(QE0(C)/QD0(C))**(rhot(C)-1));

 alphat(C)$(CE(C) AND CD(C)) = QX0(C) / (deltat(C)*QE0(C)**rhot(C) + (1-deltat(C))*QD0(C)**rhot(C))**(1/rhot(C));

*Armington aggregation.
 predelta(C)$(CM(C) AND CD(C)) = (PM0(C)/(PDD0(C)))*(QM0(C)/QD0(C))**(1+rhoq(C));
 deltaq(C)$(CM(C) AND CD(C)) = predelta(C)/(1 + predelta(C));
 alphaq(C)$(CM(C) AND CD(C)) = QQ0(C)/(deltaq(C)*QM0(C)**(-rhoq(C)) + (1-deltaq(C))*QD0(C)**(-rhoq(C)))**(-1/rhoq(C));


*------------------------------------------------------------------
* 1.5.4  Institutions
*------------------------------------------------------------------

*Factor income by factor category from activities (value added).
 YF0(F) = SUM(A, SAM(F,A)) + SAM(F,GV) + SAM(F,RW);

*Exogenous transfers (in local currency) from factors F to government.
 trnsf0(F,GV) = SAM(F,GV)/CPI0;

*Exogenous transfers (in foreign currency) from factors F to rest of world.
 trnsf0(F,RW) = SAM(F,RW)/EXR0;

*Factor payments to institutions (including rest of world).
 YIF0(INS,F) = SAM(INS,F);

*Shares of institutions in factor income (net of factor taxes).
 shif0(INS,F)$(SAM(F,'TOTAL') - TAXPAR('FACTAX',F)) = SAM(INS,F)/(SAM(F,'TOTAL') - TAXPAR('FACTAX',F));
 shif(INS,F) = shif0(INS,F);

*Factor taxes
 TF0(F)$YF0(F) = TAXPAR('FACTAX',F)/YF0(F);
 DTF0     = 0;
 TFADJ0   = 0;
 tf01(F)  = 1;
 tfbar(F) = tf0(F);

*Total income for domestic non-government institutions (includes transfers from government and rest of world).
 YI0(INSDNG) = SAM('TOTAL',INSDNG);

*Exogenous transfers (in foreign currency) from rest of world to domestic institutions INSD.
 trnsi0(INSD,RW) = SAM(INSD,RW)/EXR0;

*Exogenous transfers (in local currency) from government to domestic institutions INSD.
 trnsi0(INSD,GV) = SAM(INSD,GV)/CPI0;

*Exogenous transfers (in foreign currency) from government to rest of world.
 trnsi0(RW,GV) = SAM(RW,GV)/EXR0;

 trnsf(F,INS)    = trnsf0(F,INS);
 trnsi(INS,INSP) = trnsi0(INS,INSP);

*Endogenous transfers from domestic non-government institutions to institutions INS (including rest of world).
 TRII0(INS,INSDNG) = SAM(INS,INSDNG);

*Share of institution INS in income of domestic non-government institutions (net of direct taxes and savings).
 shii0(INS,INSDNG)$(SAM('TOTAL',INSDNG) - TAXPAR('INSTAX',INSDNG) - SAM(SI,INSDNG))
         = SAM(INS,INSDNG) / (SAM('TOTAL',INSDNG) - TAXPAR('INSTAX',INSDNG) - SAM(SI,INSDNG));
 shii(AC,ACP) = shii0(AC,ACP); 

*Direct tax rates.
 TI0(INSDNG)$SAM('TOTAL',INSDNG) = TAXPAR('INSTAX',INSDNG)/SAM('TOTAL',INSDNG);
 DTI0          = 0;
 TIADJ0        = 0;
 ti01(INSDNG)  = 1;
 tibar(INSDNG) = TI0(INSDNG);

*Savings rates (share of disposable post-tax income).
 MPS0(INSDNG)$SAM('TOTAL',INSDNG) = SAM(SI,INSDNG)/(SAM('TOTAL',INSDNG) - TAXPAR('INSTAX',INSDNG));
 DMPS0          = 0;
 MPSADJ0        = 0;
 mps01(INSDNG)  = 1;
 mpsbar(INSDNG) = MPS0(INSDNG);

*Household consumption spending and consumption quantities.
*  QH is total, not per capita.
 EH0(H)          = SUM(C, SAM(C,H)) + SUM(A, SAM(A,H));
 QH0(C,H)$PQ0(C) = SAM(C,H) / PQ0(C);

*Government indicators.
 YG0           = SAM('TOTAL',GV);
 EG0           = SAM('TOTAL',GV) - SAM(SI,GV);
 QG0(C)$PQ0(C) = SAM(C,GV)/PQ0(C);
 qbarg0(C)     = QG0(C);
 qbarg(C)      = qbarg0(C);
 GADJ0         = 1;
 GSAV0         = SAM(SI,GV);


*------------------------------------------------------------------
* 1.5.5  LES calibration
*------------------------------------------------------------------

PARAMETERS
*Calibration
 BUDSHR(C,H)        budget share for marketed commodity C and household H
 BUDSHR2(A,H)       budget share for home consumption of activity A and household H
 BUDSHRCHK(H)       check that budget shares some to unity
 ELASCHK(*,H)       check that expenditure elasticities satisfy Engel aggregation
*Checking
 SUPERNUM(H)        LES supernumerary income
 FRISCH2(H)         alternative definition of Frisch (ratio of consumption to supernumerary consumption)
 LESCHK(H)          check on LES parameter definitions (error message)
 SUPERNUMR(H)       ratio of supernumerary income to total household consumption expenditure EH
 PELAS(AC,H)        own price elasticity for home consumed activities A and marketed commodities C
;

 BUDSHR(C,H)$EH0(H)  = SAM(C,H)/EH0(H);
 BUDSHR2(A,H)$EH0(H) = SAM(A,H)/EH0(H);

 BUDSHRCHK(H) = SUM(C, BUDSHR(C,H)) + SUM(A, BUDSHR2(A,H)) - 1;
 BUDSHRCHK(H)$(ABS(BUDSHRCHK(H)) LT 1E-6) = 0;

 ELASCHK('1',H) = (SUM(C, BUDSHR(C,H)*HELAS(C,H)) + SUM(A, BUDSHR2(A,H)*HELAS(A,H))) - 1;
 ELASCHK('1',H)$(ABS(ELASCHK('1',H)) LT 1E-6) = 0;

*Correct elasticities to make them satisfy Engle aggregation exactly.
 HELAS(AC,H)$(ELASCHK('1',H) + 1) = HELAS(AC,H)/(ELASCHK('1',H) + 1);

*Check Engel aggregation again after possible corrections.
 ELASCHK('2',H) = (SUM(C, BUDSHR(C,H)*HELAS(C,H)) + SUM(A, BUDSHR2(A,H)*HELAS(A,H))) - 1;
 ELASCHK('2',H)$(ABS(ELASCHK('2',H)) LT 1E-6) = 0;

*Marginal share of household consumption on marketed commodities and home activities.
 betam0(C,H) = BUDSHR(C,H)*HELAS(C,H);
 betah0(A,H) = BUDSHR2(A,H)*HELAS(A,H);
 betam(C,H)  = betam0(C,H);
 betah(A,H)  = betah0(A,H);

*Household populations.
 pop0(H) = HPOP(H)*POPSCALE;
 pop(H)  = pop0(H);

*Per-capita subsistence consumption for household H on home activities and marketed commodities.
 gammam0(C,H)$BUDSHR(C,H)
         = ((SUM(CP, SAM(CP,H))/pop(H) + [SUM(AP, QHA0(AP,H)*PA0(AP))/hpop(H)]) / PQ0(C))
         * (BUDSHR(C,H) + betam(C,H)/FRISCH(H));
 gammah0(A,H)$BUDSHR2(A,H)
         = ((SUM(CP, SAM(CP,H))/pop(H) + [SUM(AP, QHA0(AP,H)*PA0(AP))/hpop(H)]) / PA0(A))
         * (BUDSHR2(A,H) + betah(A,H)/FRISCH(H));
 gammam(C,H) = gammam0(C,H);
 gammah(A,H) = gammah0(A,H);

*Checking LES parameters.
*   LES supernumerary income.
 SUPERNUM(H) = EH0(H) - pop(H) * (SUM(A, gammah(A,H)*PA0(A)) + SUM(C, gammam(C,H)*PQ0(C)));
*   Ratio of supernumerary income to total household consumption expenditure EH.
 SUPERNUMR(H)$EH0(H) = SUPERNUM(H)/EH0(H);
*   Alternative definition of Frisch (ratio of consumption to supernumerary consumption).
 FRISCH2(H)$SUPERNUM(H) = -EH0(H)/SUPERNUM(H);
*   Check on LES parameter definitions (error message).
 LESCHK(H) = FRISCH(H) - FRISCH2(H);
*   Own price elasticity for home consumed activities A and marketed commodities C.
 PELAS(C,H)$QH0(C,H)  = -HELAS(C,H)*( PQ0(C)*gammam(C,H) / (SUM(CP, SAM(CP,H)) + SUM(AP, SAM(AP,H))) - 1/FRISCH(H));
 PELAS(A,H)$QHA0(A,H) = -HELAS(A,H)*( PA0(A)*gammah(A,H) / (SUM(CP, SAM(CP,H)) + SUM(AP, SAM(AP,H))) - 1/FRISCH(H));

*------------------------------------------------------------------
* 1.5.6  System constraints
*------------------------------------------------------------------

*Fixed capital formation indicators.
 QINV0(C)$PQ0(C) = SAM(C,SI)/PQ0(C);
 qbarinv0(C)     = QINV0(C);
 qbarinv(C)      = qbarinv0(C);
 IADJ0           = 1 ;

*Stock changes.
 qdst0(C)$PQ0(C) = SAM(C,STK)/PQ0(C);
 qdst(C)         = qdst0(C);

*Foreign savings or capital inflows (in foreign currency).
 FSAV0 = SAM(SI,RW)/EXR0;

*Total private savings.
 PSAV0 = SUM(EN, SAM(SI,EN)) + SUM(H, SAM(SI,H));

*Total absorption.
 TABS0 = SUM((C,H), SAM(C,H)) + SUM((A,H), SAM(A,H)) + SUM(C, SAM(C,GV)) + SUM(C, SAM(C,SI)) + SUM(C, SAM(C,STK));

*Government and investment shares of total absorption.
 GOVSHR0 = SUM(C, SAM(C,GV))/TABS0;
 INVSHR0 = SAM('TOTAL',SI)/TABS0;

 WALRAS0 = 0;


*------------------------------------------------------------------
* 1.5.7  Initialize variables
*------------------------------------------------------------------

 CPI.L          = CPI0;         
 DMPS.L         = DMPS0;        
 DPI.L          = DPI0;
 DTA.L          = DTA0;
 DTE.L          = DTE0;
 DTF.L          = DTF0;
 DTI.L          = DTI0;
 DTM.L          = DTM0;
 DTQ.L          = DTQ0;
 DTV.L          = DTV0;
 EG.L           = EG0;
 EH.L(H)        = EH0(H);
 EXR.L          = EXR0;
 FSAV.L         = FSAV0;
 GADJ.L         = GADJ0;
 GOVSHR.L       = GOVSHR0;
 GSAV.L         = GSAV0;
 IADJ.L         = IADJ0;
 INVSHR.L       = INVSHR0;
 MPS.L(INS)     = MPS0(INS);
 MPSADJ.L       = MPSADJ0;
 PA.L(A)        = PA0(A);
 PDD.L(C)       = PDD0(C);
 PDS.L(C)       = PDS0(C);
 PE.L(C)        = PE0(C);
 PINTA.L(A)     = PINTA0(A);
 PM.L(C)        = PM0(C);
 PQ.L(C)        = PQ0(C);
 PSAV.L         = PSAV0;
 PVA.L(A)       = PVA0(A);
 PX.L(C)        = PX0(C);
 PXAC.L(A,C)    = PXAC0(A,C);
 TA.L(A)        = TA0(A);
 TAADJ.L        = TAADJ0;
 TABS.L         = TABS0;
 TE.L(C)        = TE0(C);
 TEADJ.L        = TEADJ0;
 TF.L(F)        = TF0(F);
 TFADJ.L        = TFADJ0;
 TI.L(INS)      = TI0(INS);
 TIADJ.L        = TIADJ0;
 TM.L(C)        = TM0(C);
 TMADJ.L        = TMADJ0;
 TRII.L(INS,INSP) = TRII0(INS,INSP);
 TQ.L(C)        = TQ0(C);
 TQADJ.L        = TQADJ0;
 TV.L(A)        = TV0(A);
 TVADJ.L        = TVADJ0;
 QA.L(A)        = QA0(A);
 QD.L(C)        = QD0(C);
 QE.L(C)        = QE0(C);
 QF.L(F,A)      = QF0(F,A);
 QFS.L(F)       = QFS0(F);
 QG.L(C)        = QG0(C);
 QH.L(C,H)      = QH0(C,H);
 QHA.L(A,H)     = QHA0(A,H);
 QINT.L(C,A)    = QINT0(C,A);
 QINTA.L(A)     = QINTA0(A);
 QINV.L(C)      = QINV0(C);
 QM.L(C)        = QM0(C);
 QQ.L(C)        = QQ0(C);
 QT.L(C)        = QT0(C);
 QVA.L(A)       = QVA0(A);
 QX.L(C)        = QX0(C);
 QXAC.L(A,C)    = QXAC0(A,C);
 WALRAS.L       = WALRAS0;
 WF.L(F)        = WF0(F);
 WFDIST.L(F,A)  = WFDIST0(F,A);
 YF.L(F)        = YF0(F);
 YG.L           = YG0;
 YI.L(INS)      = YI0(INS);
 YIF.L(INS,F)   = YIF0(INS,F);


*------------------------------------------------------------------
* 1.5.8  Fixing variables not in the model to zero
*------------------------------------------------------------------

 PA.FX(A)$(NOT AA(A))                    = 0;
 PDD.FX(C)$(NOT CD(C))                   = 0;
 PDS.FX(C)$(NOT CD(C))                   = 0;
 PE.FX(C)$(NOT CE(C))                    = 0;
 PM.FX(C)$(NOT CM(C))                    = 0;
 PVA.FX(A)$(NOT QVA0(A))                 = 0;
 PX.FX(C)$(NOT CX(C))                    = 0;
 PXAC.FX(A,C)$(NOT SAM(A,C))             = 0;
 QA.FX(A)$(NOT AA(A))                    = 0;
 QD.FX(C)$(NOT CD(C))                    = 0;
 QE.FX(C)$(NOT CE(C))                    = 0;
 QF.FX(F,A)$(NOT QF0(F,A))               = 0;
 QG.FX(C)$(NOT SAM(C,GV))                = 0;
 QH.FX(C,H)$(NOT SAM(C,H))               = 0;
 QHA.FX(A,H)$(NOT SAM(A,H))              = 0;
 QINT.FX(C,A)$(NOT SAM(C,A))             = 0;
 QINV.FX(C)$(NOT SAM(C,SI))              = 0;
 QM.FX(C)$(NOT CM(C))                    = 0;
 QQ.FX(C)$(NOT (CD(C) OR CM(C)))         = 0;
 QT.FX(C)$(NOT CT(C))                    = 0;
 QVA.FX(A)$(NOT QVA0(A))                 = 0;
 QX.FX(C)$(NOT CX(C))                    = 0;
 QXAC.FX(A,C)$(NOT SAM(A,C))             = 0;
 TRII.FX(INS,INSP)$(NOT TRII0(INS,INSP)) = 0;
 YI.FX(INS)$(NOT YI0(INS))               = 0;
 YF.FX(F)$(NOT YF0(F))                   = 0;
 YIF.FX(INS,F)$(NOT YIF0(INS,F))         = 0;
 

*------------------------------------------------------------------
* 1.5.9  Base model closures
*------------------------------------------------------------------

$ontext
 In the static and dynamic simulation files, the user chooses between alternative closures. These choices take
 precedence over the choices for the base model made in this file. The clearing variables for factor market and macro
 constraint equations are as follows:

 FACEQUIL - WF: for each factor, the economywide wage is the market-clearing variable in a setting with perfect factor
 mobility across activities, given fixed factor supplies QFS. Alternative: Various choices depending on FCLOSURE(F).

 CURACCBAL - EXR: a flexible exchange rate clears the current account of the RoW given FSAV. Alternative: Fix EXR
 and flex FSAV OR fix both EXR and FSAV and flex PR 

 GOVBAL - GSAV: flexible government savings clears the government account, with fixed government demand for
 commodities. All tax rates are fixed.

 SAVINVBAL - IADJ: Aggregate real investment adjusts to match aggregate savings (savings drives investment).

 CPI is specified as the model numeraire.

 Factor market closure assumes full employment with wages endogenous.
$offtext

*Factor markets (full employment, wage endogenous).
 QFS.FX(F)   = QFS0(F);
 WFDIST.FX(F,A) = WFDIST0(F,A);

*Current account (flexible exchange rate, fixed foreign savings, no premium on parallel market).
 FSAV.FX     = FSAV0;

*Current government balance (fixed consumption demand, fixed tax rates, flexible government savings).
 GADJ.FX     = GADJ0;
 TAADJ.FX    = TAADJ0;
 DTA.FX      = DTA0;
 TEADJ.FX    = TEADJ0;
 DTE.FX      = DTE0;
 TFADJ.FX    = TFADJ0;
 DTF.FX      = DTF0;
 TIADJ.FX    = TIADJ0;
 DTI.FX      = DTI0;
 TMADJ.FX    = TMADJ0;
 DTM.FX      = DTM0;
 TQADJ.FX    = TQADJ0;
 DTQ.FX      = DTQ0;
 TVADJ.FX    = TVADJ0;
 DTV.FX      = DTV0;

*Savings-investment balance (fixed savings rates, flexible investment demand)
 MPSADJ.FX   = MPSADJ0;
 DMPS.FX     = DMPS0;

*Numeraire price
 CPI.FX      = CPI0;
