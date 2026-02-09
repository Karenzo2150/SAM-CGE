$TITLE IFPRI Standard CGE Model Version 2.1

$ontext
PART 1: Base model
 This file (1model_base.gms) generates the base model. It first declares the standard model (i.e., variables
 and equations) and then calibrates the model using country data imported from Excel. The base model is then
 solved and standard reporting parameters are generated. 
 
SECTIONS:
 1.1  Model sets, parameters and variables
 1.2  Model equations
 1.3  Model declaration
 1.4  Import country data       (includes\1base_data.inc)
 1.5  Calibrate the base model  (includes\1base_calibrate.inc)
 1.6  Solve the base model       
 1.7  Base model reporting      (includes\1base_report.inc)
$offtext


*------------------------------------------------------------------
*1.1 Model sets, parameters and variables
*------------------------------------------------------------------

*Only the sets, parameters and variables that appear in the model's equations are declared here. All
*other parameters used to calibrate the model and report results are declared in the 1calibration.inc and 1data.inc files. 

SETS
 AC                global set for model accounts - aggregated microsam accounts
 ACNT(AC)          all elements in AC except TOTAL
*Model sets        
 A(AC)             activities
 C(AC)             commodities
 F(AC)             all factors 
 INS(AC)           institutions
 INSD(INS)         domestic institutions
 INSDNG(INSD)      domestic non-government institutions
 H(INSDNG)         households
*Conditional sets  
 ACES(A)           activities with CES function at top of technology nest
 ALEO(A)           activities with Leontief function at top of technology nest
 ACCES(A)          activities with CES domestic activity aggregation function
 CD(C)             commodities with domestic sales of output
 CDN(C)            commodities without domestic sales of output
 CE(C)             exported commodities
 CEN(C)            non-export commodities
 CM(C)             imported commodities
 CMN(C)            non-imported commodities
 CT(C)             transaction service commodities
 CX(C)             commodities with output
 AA(A)             activities with positive domestic production
 FA(F)             factors with positive employment and incomes
 HA(A,H)           households with base year own consumption of output from activity A
 HC(C,H)           households with base year marketed consumption of commodity C
;

SINGLETON SETS
 GV(INS)           government
 RW(INS)           rest of the world
;

ALIAS
 (AC,ACP), (A,AP), (C,CP), (F,FP), (INSDNG,INSDNGP), (H,HP)
;

PARAMETERS
 alphaa(A)          shift parameter for top level CES function
 alphaac(C)         shift parameter for domestic commodity aggregation function
 alphaca(A)         shift parameter for domestic activity aggregation function
 alphaf(F,A)        productivity shift for factor F in activity A
 alphaq(C)          shift parameter for QQ Armington function
 alphat(C)          shift parameter for CET QX aggregation function
 alphava(A)         shift parameter for CES activity production function
 betah(A,H)         marginal share of household consumption on home commodity C from activity A
 betam(C,H)         marginal share of household consumption on marketed commodity C
 cwts(C)            consumer price index weights
 deltaa(A)          share parameter for top level CES function
 deltaac(A,C)       share parameter for domestic commodity aggregation function
 deltaca(A,C)       share parameter for domestic activity aggregation function
 deltaq(C)          share parameter for Armington function
 deltat(C)          share parameter for CET QX function
 deltava(F,A)       share parameter for CES activity production function
 dwts(C)            domestic sales price weights
 gammah(A,H)        per-capita subsistence consumption for household H on home commodity C for activity A
 gammam(C,H)        per-capita subsistence consumption of marketed commodity C for household H
 ica(C,A)           intermediate input c per unit of aggregate intermediate
 icd(C,CP)          trade input of C per unit of commodity CP produced & sold domestically
 ice(C,CP)          trade input of C per unit of commodity CP exported
 icm(C,CP)          trade input of C per unit of commodity CP imported
 inta(A)            aggregate intermediate input coefficient
 iva(A)             aggregate value added coefficient
 mps01(AC)          0-1 parameter for potential flexing of savings rates
 mpsbar(AC)         marginal propensity to save for domestic non-government institution INS (exogenous part)
 pop(H)             total population of workers and non-workers in household H
 pwe(C)             world price of exports
 pwm(C)             world price of imports
 qbarg(C)           exogenous (unscaled) government demand
 qbarinv(C)         exogenous (unscaled) investment demand
 qdst(C)            inventory investment by sector of origin
 rhoa(A)            CES top level function exponent
 rhoac(C)           domestic commodity aggregation function exponent
 rhoca(A)           domestic activity aggregation function exponent
 rhoq(C)            Armington function exponent
 rhot(C)            CET function exponent
 rhova(A)           CES activity production function exponent
 shif(AC,AC)        share of institution INS (incl. rest of world) in post-tax income of factor F
 shii(AC,AC)        share of institution INS in post-tax post-savings income of institution INSP
 ta01(A)            0-1 parameter for potential flexing of activity tax rates
 tabar(A)           activity tax rate on activity A (exogenous part)
 te01(C)            0-1 parameter for potential flexing of export tax rates
 tebar(C)           export tax rate on commodity C (exogenous part)
 tf01(F)            0-1 parameter for potention flexing of factor taxes
 tfbar(F)           factor tax rate on factor F (exogenous part)
 theta(A,C)         yield of commodity C per unit of activity A
 ti01(AC)           0-1 parameter for potential flexing of direct tax rates
 tibar(INS)         direct tax rate on domestic institution INS (exogenous part)
 tm01(C)            0-1 parameter for potential flexing of import tax rates
 tmbar(C)           import tax rate on commodity C (exogenous part)
 trnsf(F,INS)       transfers from factor F to institution INS (including rest of world)
 trnsi(INS,INS)     transfers from institution INS) to institution INSP (including rest of world)
 tq01(C)            0-1 parameter for potential flexing of sales tax rates
 tqbar(C)           sales tax rate on commodity C (exogenous part)
 tv01(A)            0-1 parameter for potential flexing of value added tax rates
 tvbar(A)           value-added tax rate on activity A (exogenous part)
;                  
                   
VARIABLES
 CPI                consumer price index (PQ-based)
 DMPS               change in marginal propensity to save for selected institution
 DPI                index for domestic producer prices (PDS-based)
 DTA                additive activity tax (TA) adjustment
 DTE                additive export tax (TE) adjustment
 DTF                additive direct factor tax (TF) adjustment
 DTI                additive domestic institution tax (TI) adjustment
 DTM                additive import tariff (TM) adjustment
 DTQ                additive sales tax (TQ) adjustment
 DTV                additive value-added tax (TV) adjustment
 EG                 total current government expenditure
 EH(H)              household consumption expenditure
 EXR                exchange rate
 FSAV               foreign savings
 GADJ               government demand scaling factor
 GOVSHR             government consumption share of absorption
 GSAV               government savings
 IADJ               investment scaling factor (for fixed capital formation)
 INVSHR             investment share of absorption
 MPS(INS)           marginal propensity to save for domestic non-government institution INS
 MPSADJ             savings rate (MPS) scaling factor
 PA(A)              output price of activity A
 PDD(C)             demand price for commodity C produced and sold domestically
 PDS(C)             supply price for commodity C produced and sold domestically
 PE(C)              price of export aggregate to producer excluding transport costs
 PINTA(A)           price of intermediate aggregate
 PM(C)              price of import aggregate to demander including transport costs
 PQ(C)              price of composite commodity C
 PSAV               total private savings
 PVA(A)             value added price
 PX(C)              average output price
 PXAC(A,C)          price of commodity C from activity A
 QA(A)              level of domestic activity
 QD(C)              quantity of domestic sales
 QE(C)              quantity of exports
 QF(F,A)            quantity demanded of factor F from activity A
 QFS(F)             quantity of factor supply
 QG(C)              quantity of government consumption
 QH(C,H)            quantity consumed of marketed commodity C by household H
 QHA(A,H)           quantity consumed of home activity A by household H
 QINT(C,A)          quantity of intermediate demand for commodity C from activity A
 QINTA(A)           quantity of aggregate intermediate input
 QINV(C)            quantity of fixed investment demand
 QM(C)              quantity of imports
 QQ(C)              quantity of composite goods supply
 QT(C)              quantity of trade and transport demand for commodity C
 QVA(A)             quantity of aggregate value added
 QX(C)              quantity of aggregate marketed commodity output
 QXAC(A,C)          quantity of ouput of commodity C from activity A
 TA(A)              activity tax rates
 TAADJ              activity tax (TA) scaling factor
 TABS               total absorption
 TE(C)              export tax rates
 TEADJ              export tax (TE) scaling factor
 TF(F)              direct factor tax rates
 TFADJ              direct factor tax (TF) scaling factor
 TI(INS)            direct tax rates on domestic institutions INSD
 TIADJ              direct tax (TI) scaling factor
 TM(C)              import tariff rates
 TMADJ              import tariff (TM) scaling factor
 TRII(INS,INS)      transfers from column institutions INSF to row institutions INS
 TQ(C)              composite commodity taxes
 TQADJ              composite commodity tax (TQ) scaling factor
 TV(A)              value-added tax rate
 TVADJ              value-added tax (TV) scaling factor
 WALRAS             savings-investment imbalance (should be zero)
 WF(F)              economywide wage (rent) for factor F
 WFDIST(F,A)        wage distortion variable for factor F in activity A
 YF(F)              factor income from activities
 YG                 total government income
 YI(INS)            income of domestic non-government institution INS
 YIF(INS,F)         income of institution INS from factor F
;


*------------------------------------------------------------------
*1.2 Model equations
*------------------------------------------------------------------

EQUATIONS
*--- Prices ---
 PMDEF(C)           domestic import price 
 PEDEF(C)           domestic export price 
 PDDDEF(C)          demand price for commodities produced and sold domestically
 PQDEF(C)           value of sales in domestic market 
 PXDEF(C)           value of marketed domestic output 
 PADEF(A)           activity output price 
 PINTADEF(A)        price of aggregate intermediate input for activity A
 PVADEF(A)          value-added price and adding up condition for top nest for activity A
 CPIDEF             consumer price index
 DPIDEF             domestic producer price index
*--- Production and trade ---
 CESAGGPRD(A)       CES aggregate production function for activity A (if CES top nest)
 CESAGGFOC(A)       CES aggregate first-order condition for activity A (if CES top nest)
 LEOAGGINT(A)       Leontief aggregate intermediate demand for activity A (if Leontief top nest)
 LEOAGGVA(A)        Leontief aggregate value-added demand for activity A (if Leontief top nest)
 CESVAPRD(A)        CES value-added production function for activity A
 FACDEM(F,A)        CES value-added first-order condition for factor F used in activity A
 INTDEM(C,A)        intermediate demand for commodity C from activity A
 COMPRDFN(A,C)      production function for commodity C and activity A
 COMPRDFN2(A,C)     CET first order conditions for commodity C to activity A aggregation
 OUTAGGFN(C)        output aggregation function for commodity C
 OUTAGGFOC(A,C)     first-order condition for output aggregation function for commodity C produced by activity A
 CET(C)             CET export supply function for commodity C
 ESUPPLY(C)         first-order condition for export supply for commodity C
 CET2(C)            domestic sales and exports for commodity C (for commodities without both domestic sales and exports)
 ARMINGTON(C)       composite commodity aggregation function for commodity C
 COSTMIN(C)         first-order condition for composite commodity cost minimization for commodity C
 ARMINGTON2(C)      composite supply for commoidity C (for commodities without both domestic sales and imports)
 QTDEM(C)           demand for transactions (trade and transport) services
*--- Institution    income and expenditure ---
 YFDEF(F)           total incomes including transfers for factor F
 YIFDEF(INS,F)      factor incomes to domestic institutions and rest of world
 YIDEF(INS)         total incomes of domest nongovernment institutions
 TRIIDEF(INS,INS)   transfers from institution INSP to institution INS
 EHDEF(H)           household consumption expenditures
 HMDEM(C,H)         LES consumption demand by household H for marketed commodity C
 HADEM(A,H)         LES consumption demand by household H for home for activity A
 INVDEM(C)          fixed investment demand
 GOVDEM(C)          government consumption demand
 YGDEF              total government income
 EGDEF              total government expenditures
*--- System constraints ---
 FACEQUIL(F)        factor market equilibrium
 COMEQUIL(C)        composite commodity market equilibrium
 CURACCBAL          current account balance
 GOVBAL             government balance
 PRVSAV             total private savings
 SAVINVBAL          savings-investment balance
 TABSEQ             total absorption
 INVABEQ            investment share in absorption
 GOVABEQ            government consumption share in absorption
*--- Savings and tax rates ---
 MPSDEF(INS)        marginal propensity to save for institution INS
 TADEF(A)           activity taxes
 TEDEF(C)           export tax rates
 TFDEF(F)           factor tax rate
 TIDEF(INS)         direct tax rate for institution INS
 TMDEF(C)           tariff rates
 TQDEF(C)           commodity taxes
 TVDEF(A)           value-added taxes
;

*--- Price equations ----

 PMDEF(C)$CM(C)..
         PM(C) =E= pwm(C)*(1 + TM(C))*EXR + SUM(CT, PQ(CT)*icm(CT,C));

 PEDEF(C)$CE(C)..
         PE(C) =E= pwe(C)*(1 - TE(C))*EXR - SUM(CT, PQ(CT)*ice(CT,C));

 PDDDEF(C)$CD(C)..
         PDD(C) =E= PDS(C) + SUM(CT, PQ(CT)*icd(CT,C));

 PQDEF(C)$(CD(C) OR CM(C))..
         PQ(C)*(1 - TQ(C))*QQ(C) =E= PDD(C)*QD(C) + PM(C)*QM(C);

 PXDEF(C)$CX(C)..
         PX(C)*QX(C) =E= PDS(C)*QD(C) + PE(C)*QE(C);

 PADEF(A)$AA(A)..
         PA(A) =E= SUM(C, PXAC(A,C)*theta(A,C));

 PINTADEF(A)$AA(A)..
         PINTA(A) =E= SUM(C, PQ(C)*ica(C,A));

 PVADEF(A)$AA(A)..
         PVA(A)*QVA(A) =E= PA(A)*(1-TA(A))*QA(A) - PINTA(A)*QINTA(A);

 CPIDEF..
         CPI =E= SUM(C, cwts(C)*PQ(C));

 DPIDEF..
         DPI =E= SUM(CD, dwts(CD)*PDS(CD));

*--- Production and trade equations ---

 CESAGGPRD(A)$ACES(A)..
         QA(A) =E= alphaa(A)*(deltaa(A)*QVA(A)**(-rhoa(A)) + (1-deltaa(A))*QINTA(A)**(-rhoa(A)))**(-1/rhoa(A));

 CESAGGFOC(A)$ACES(A)..
         QVA(A) =E= QINTA(A)*((PINTA(A)/PVA(A))*(deltaa(A)/(1 - deltaa(A))))**(1/(1+rhoa(A)));

 LEOAGGVA(A)$ALEO(A)..
         QVA(A) =E= iva(A)*QA(A);

 LEOAGGINT(A)$ALEO(A)..
         QINTA(A) =E= inta(A)*QA(A);

 CESVAPRD(A)$AA(A)..
         QVA(A) =E= alphava(A)*(SUM(F, deltava(F,A)*(alphaf(F,A)*QF(F,A))**(-rhova(A))) )**(-1/rhova(A)) ;

 FACDEM(F,A)$deltava(F,A)..
         WF(F)*WFDIST(F,A) =E= PVA(A)*(1-TV(A))*QVA(A) * SUM(FP, deltava(FP,A)*(alphaf(FP,A)*QF(FP,A))**(-rhova(A)))**(-1) * deltava(F,A) * (alphaf(F,A)*QF(F,A))**(-rhova(A)-1);

 INTDEM(C,A)$ica(C,A)..
         QINT(C,A) =E= ica(C,A)*QINTA(A);

 COMPRDFN(A,C)$(theta(A,C) AND NOT ACCES(A))..
         QXAC(A,C) =E= theta(A,C)*(QA(A) - SUM(H, QHA(A,H)));

 COMPRDFN2(A,C)$(theta(A,C) AND ACCES(A))..
         QXAC(A,C) =E= (QA(A) - SUM(H, QHA(A,H)))*(PXAC(A,C)/(PA(A)*deltaca(A,C)*alphaca(A)**rhoca(A)))**(1/(rhoca(A)-1));

 OUTAGGFN(C)$CX(C)..
         QX(C) =E= alphaac(C)*SUM(A, deltaac(A,C)*QXAC(A,C)**(-rhoac(C)))**(-1/rhoac(C));

 OUTAGGFOC(A,C)$deltaac(A,C)..
         PXAC(A,C) =E= PX(C)*QX(C) * SUM(AP, deltaac(AP,C)*QXAC(AP,C)**(-rhoac(C)))**(-1)*deltaac(A,C)*QXAC(A,C)**(-rhoac(C)-1);

 CET(C)$(CE(C) AND CD(C))..
         QX(C) =E= alphat(C)*(deltat(C)*QE(C)**rhot(C) + (1 - deltat(C))*QD(C)**rhot(C))**(1/rhot(C));

 ESUPPLY(C)$(CE(C) AND CD(C))..
         QE(C) =E=  QD(C)*((PE(C)/PDS(C))*((1 - deltat(C))/deltat(C)))**(1/(rhot(C)-1));

 CET2(C)$((CD(C) AND CEN(C)) OR (CE(C) AND CDN(C)))..
         QX(C) =E= QD(C) + QE(C);

 ARMINGTON(C)$(CM(C) AND CD(C))..
         QQ(C) =E= alphaq(C)*(deltaq(C)*QM(C)**(-rhoq(C)) + (1 - deltaq(C))*QD(C)**(-rhoq(C)))**(-1/rhoq(C));

 COSTMIN(C)$(CM(C) AND CD(C))..
         QM(C) =E= QD(C)*((PDD(C)/PM(C))*(deltaq(C)/(1 - deltaq(C))))**(1/(1 + rhoq(C)));

 ARMINGTON2(C)$((CD(C) AND CMN(C)) OR (CM(C) AND CDN(C)))..
         QQ(C) =E= QD(C) + QM(C);

 QTDEM(C)$CT(C)..
         QT(C) =E= SUM(CP, icm(C,CP)*QM(CP)+ ice(C,CP)*QE(CP)+ icd(C,CP)*QD(CP));

*--- Institution income and expenditure equations ---

 YFDEF(F)$FA(F)..
         YF(F) =E= SUM(A, WF(F)*WFDIST(F,A)*QF(F,A)) + trnsf(F,GV)*CPI + trnsf(F,RW)*EXR;

 YIFDEF(INS,F)$FA(F)..
         YIF(INS,F) =E= shif(INS,F) * YF(F)*(1-TF(F));
         
 YIDEF(INSDNG)..
         YI(INSDNG) =E= SUM(F, YIF(INSDNG,F)) + SUM(INSDNGP, TRII(INSDNG,INSDNGP)) + trnsi(INSDNG,GV)*CPI + trnsi(INSDNG,RW)*EXR;

 TRIIDEF(INS,INSDNG)$shii(INS,INSDNG)..
         TRII(INS,INSDNG) =E= shii(INS,INSDNG) * YI(INSDNG)*(1-TI(INSDNG))*(1-MPS(INSDNG));

 EHDEF(H)$(SUM(C, HC(C,H)) OR SUM(A, HA(A,H)))..
         EH(H) =E= (1 - SUM(INS, shii(INS,H))) * YI(H)*(1-TI(H))*(1-MPS(H));

 HMDEM(C,H)$HC(C,H)..
         PQ(C)*QH(C,H)  =E= pop(H)*(PQ(C)*gammam(C,H) + betam(C,H)*(EH(H)/pop(H) - SUM(CP, PQ(CP)*gammam(CP,H)) - SUM(A,  PA(A)*gammah(A,H))));

 HADEM(A,H)$HA(A,H)..
         PA(A)*QHA(A,H) =E= pop(H)*(PA(A)*gammah(A,H) + betah(A,H)*(EH(H)/pop(H) - SUM(C, PQ(C)*gammam(C,H)) - SUM(AP, PA(AP)*gammah(AP,H))));

 INVDEM(C)..
         QINV(C) =E= IADJ*qbarinv(C);

 GOVDEM(C)..
         QG(C) =E= GADJ*qbarg(C);

 YGDEF..
         YG =E=    SUM(A, TA(A)*PA(A)*QA(A))
                 + SUM(CM, TM(CM)*pwm(CM)*QM(CM)*EXR)
                 + SUM(CE, TE(CE)*pwe(CE)*QE(CE)*EXR)
                 + SUM(C, TQ(C)*PQ(C)*QQ(C))
                 + SUM(A, TV(A)*PVA(A)*QVA(A))
                 + SUM(F, TF(F)*YF(F))
                 + SUM(INSDNG, TI(INSDNG)*YI(INSDNG))
                 + SUM(F, YIF(GV,F))
                 + SUM(INSDNG, TRII(GV,INSDNG))
                 + trnsi(GV,RW)*EXR;

 EGDEF..
         EG =E=   SUM(C, PQ(C)*QG(C))
                + SUM(INSDNG, trnsi(INSDNG,GV))*CPI
                + trnsi(RW,GV)*EXR;

*--- System constraints ---

 FACEQUIL(F)..
         QFS(F) =E= SUM(A, QF(F,A));
         
 COMEQUIL(C)$(CD(C) OR CM(C))..
         QQ(C) =E= SUM(A, QINT(C,A)) + SUM(H, QH(C,H)) + QG(C) + QINV(C) + qdst(C) + QT(C);

 CURACCBAL..
         SUM(CM, pwm(CM)*QM(CM)) + SUM(F, YIF(RW,F))/EXR + SUM(INSDNG, TRII(RW,INSDNG))/EXR + trnsi(RW,GV) =E= SUM(CE, pwe(CE)*QE(CE)) + SUM(F, trnsf(F,RW)) + SUM(INSD, trnsi(INSD,RW)) + FSAV;

 GOVBAL..
         YG =E= EG + GSAV;

 PRVSAV..
         PSAV =E= SUM(INSDNG, MPS(INSDNG)*(1-TI(INSDNG))*YI(INSDNG));

 SAVINVBAL..
          PSAV + GSAV + FSAV*EXR =E= SUM(C, PQ(C)*QINV(C)) + SUM(C, PQ(C)*qdst(C)) + WALRAS;

 TABSEQ..
         TABS =E= SUM((C,H)$HC(C,H), PQ(C)*QH(C,H)) + SUM((A,H)$HA(A,H), PA(A)*QHA(A,H)) + SUM(C, PQ(C)*QG(C)) + SUM(C, PQ(C)*QINV(C)) + SUM(C, PQ(C)*qdst(C));

 INVABEQ..
         INVSHR*TABS =E= SUM(C, PQ(C)*QINV(C)) + SUM(C, PQ(C)*qdst(C));

 GOVABEQ..
         GOVSHR*TABS =E= SUM(C, PQ(C)*QG(C));

*--- Savings and tax rates ---

 MPSDEF(INSDNG)..
         MPS(INSDNG)  =E= mpsbar(INSDNG)*(1 + MPSADJ*mps01(INSDNG)) + DMPS*mps01(INSDNG);

 TADEF(A)..
         TA(A) =E= tabar(A)*(1 + TAADJ*ta01(A)) + DTA*ta01(A);

 TEDEF(C)$CE(C)..
         TE(C) =E= tebar(C)*(1 + TEADJ*te01(C)) + DTE*te01(C);

 TFDEF(F)..
         TF(F) =E= tfbar(F)*(1 + TFADJ*tf01(F)) + DTF*tf01(F);

 TIDEF(INSDNG)..
         TI(INSDNG) =E= tibar(INSDNG)*(1 + TIADJ*ti01(INSDNG)) + DTI*ti01(INSDNG);

 TMDEF(C)$CM(C)..
         TM(C)  =E= tmbar(C)*(1 + TMADJ*tm01(C)) + DTM*tm01(C);

 TQDEF(C)..
         TQ(C) =E= tqbar(C)*(1 + TQADJ*tq01(C)) + DTQ*tq01(C);

 TVDEF(A)..
         TV(A) =E= tvbar(A)*(1 + TVADJ*tv01(A)) + DTV*tv01(A);



*------------------------------------------------------------------
*1.3 Model declaration
*------------------------------------------------------------------

MODEL STANDCGE  standard IFPRI CGE model /
*--- Prices ---
 PMDEF.PM
 PEDEF.PE
 PDDDEF.PDD
 PQDEF.PQ
 PXDEF.PX
 PADEF.PA
 PINTADEF.PINTA
 PVADEF.PVA
 CPIDEF
 DPIDEF
*--- Production and trade ---
 CESAGGPRD
 CESAGGFOC
 LEOAGGINT
 LEOAGGVA
 CESVAPRD.QVA
 FACDEM
 INTDEM.QINT
 COMPRDFN
 COMPRDFN2
 OUTAGGFN.QX
 OUTAGGFOC.QXAC
 CET
 ESUPPLY
 CET2
 ARMINGTON
 COSTMIN
 ARMINGTON2
 QTDEM.QT
*--- Institution income and expenditure equations ---
 YFDEF.YF
 YIFDEF.YIF
 YIDEF.YI
 TRIIDEF.TRII
 EHDEF.EH
 HMDEM.QH
 HADEM.QHA
 INVDEM
 GOVDEM.QG
 YGDEF.YG
 EGDEF.EG
*--- System constraints ---
 FACEQUIL
 COMEQUIL
 CURACCBAL
 GOVBAL
 PRVSAV.PSAV
 SAVINVBAL.WALRAS
 TABSEQ.TABS
 INVABEQ
 GOVABEQ
*--- Savings and tax rates ---
 MPSDEF.MPS
 TADEF.TA
 TEDEF.TE
 TFDEF.TF
 TIDEF.TI
 TMDEF.TM
 TQDEF.TQ
 TVDEF.TV
/;


*------------------------------------------------------------------
*1.4 Import country data
*------------------------------------------------------------------

*Load country data from excel file and make any data adjustments 
$include includes\base\base_data.inc

*Run diagnostic checks on country data 
$include includes\base\base_diagnostic.inc

display ERREXPOUT, ERRSAMBAL;
*------------------------------------------------------------------
*1.5 Calibrate the base model
*------------------------------------------------------------------

*Calibrate model parameters and variables using country data
$include includes\base\base_calibration.inc

display ERREXPOUT, ERRSAMBAL, rhoq;
*------------------------------------------------------------------
*1.6 Solve the base model
*------------------------------------------------------------------

$ontext
 These options are useful for debugging. When checking whether the initial data represent a solution, set LIMROW to a
 value greater than the number of equations and search for three asterisks in the listing file. SOLPRINT=ON provides
 a complete listing file. 
$offtext

OPTIONS ITERLIM = 1000, LIMROW = 1000, LIMCOL = 0, SOLPRINT=ON, MCP=PATH, NLP=CONOPT CNS=CONOPT;

$ontext
 The HOLDFIXED option converts all variables which are fixed (.FX) into parameters. They are then not solved as part
 of the model. The TOLINFREP parameter sets the tolerance for determinining whether initial values of variables
 represent a solution of the model equations. Whether these initial equation values are printed is determimed by the
 LIMROW option. Equations which are not satsfied to the degree TOLINFREP are printed with three asterisks next to
 their listing.
$offtext

 STANDCGE.HOLDFIXED  = 1;
 STANDCGE.TOLINFREP  = 0.001;
 STANDCGE.MCPRHOLDFX = 1;
 STANDCGE.SCALEOPT   = 1;

 SOLVE STANDCGE USING MCP;
 

*------------------------------------------------------------------
*1.7 Base model reporting
*------------------------------------------------------------------

*Base solution reports
$include includes\base\base_report.inc