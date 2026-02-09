$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2.3: Declare reporting parameters
 This include file (includes\2static_repsetup.inc) creates parameters used to store results within
 the simulation loop after each solve (see includes\2static_reploop.inc). Note: All other results 
 parameters are declared and defined in the standard reporting file (includes\2static_report.inc).

SECTIONS:
 2.3.1  Sets for internal reporting parameters
 2.3.2  Parameters for storing post-solution variable values
$offtext


*------------------------------------------------------------------
*2.3.1  Sets for internal reporting parameters
*------------------------------------------------------------------

SETS
 SAC            SAM account categories /
  ACT           actitivities
  COM           commodities
  FAC           factors
  INSDNG        domestic nongovernment institutions
  GOV           government
  SAVINV        savings-investments
  INSTAX        direct taxes on institutions
  FACTAX        direct taxes on factors
  VATTAX        value added tax
  ACTTAX        tax on activity gross revenue
  COMTAX        tax on commodity sales in the domestic market
  IMPTAX        import tariff
  EXPTAX        export tax
  ROW           rest of world (FCU)
 /
 IND3           third index for SAM budgets     / INC, SPND, GAP /
 KGDP           first index in GDP tables       / NOMINAL, REAL, NOMSHARE, REALSHARE, DEFLATOR /
 IGDP           items for GDP and national accounts  /
  ABSORP        absorption
  PRVCON        private consumption
  FIXINV        fixed investment
  DSTOCK        stock change
  GOVCON        government consumption
  EXPORTS       exports
  IMPORTS       imports
  GDPMP         GDP at market prices (alt. 1: spending)
  GDPMP2        GDP at market prices (alt. 2: value-added)
  NETITAX       net indirect taxes
  GDPFC2        GDP at factor cost
 /
 IGDP2(IGDP)    items for GDPMP summation /
  PRVCON        private consumption
  FIXINV        fixed investment
  DSTOCK        stock change
  GOVCON        government consumption
  EXPORTS       exports
  IMPORTS       imports
 /

*The sets MODTYPE and SOLVEIND are used in the parameters SOLVEMAX, SOLVEREP, and SOLVEWARN.
 MODTYPE        model types /
  MCP           mixed-complementarity programming
  NLP           non-linear programming
 /
 SOLVEIND  solve indicators /
 MODEL-STATUS   model status
 SOLVER-STATUS  solver status
 NUM-REDEFEQ    number of redefined equations
 /
;

TABLE SOLVEMAX(SOLVEIND,MODTYPE)    max permitted value for SOLVEREP indicators
                 MCP   NLP
 MODEL-STATUS     1     2
 SOLVER-STATUS    1     1
 NUM-REDEFEQ      0     0
;


*------------------------------------------------------------------
*2.3.2  Parameters for storing post-solution variable values
*------------------------------------------------------------------

PARAMETERS
*Model parameters (parameters ending with X contain post-solution values)
 x_alphaf(F,A,SIM)                  productivity shift for factor F in activity A
 x_alphava(A,SIM)                   shift parameter for CES activity production function
 x_betah(A,H,SIM)                   marginal share of household consumption on home commodity C from activity A
 x_betam(C,H,SIM)                   marginal share of household consumption on marketed commodity C
 x_gammah(A,H,SIM)                  per-capita subsistence consumption for household H on home commodity C for activity A
 x_gammam(C,H,SIM)                  per-capita subsistence consumption of marketed commodity C for household H
 x_icd(C,CP,SIM)                    trade input of C per unit of commodity CP produced & sold domestically
 x_ice(C,CP,SIM)                    trade input of C per unit of commodity CP exported
 x_icm(C,CP,SIM)                    trade input of C per unit of commodity CP imported
 x_pop(H,SIM)                       total population of workers and non-workers in household H
 x_pwe(C,SIM)                       world price of exports
 x_pwm(C,SIM)                       world price of imports
 x_qbarinv(C,SIM)                   exogenous (unscaled) investment demand
 x_qbarg(C,SIM)                     exogenous (unscaled) government demand
 x_qdst(C,SIM)                      inventory investment by sector of origin
 x_shif(AC,ACP,SIM)                 share of institution INS (incl. rest of world) in post-tax income of factor F
 x_shii(AC,ACP,SIM)                 share of institution INS in post-tax post-savings income of institution INSP
 x_trnsf(F,INS,SIM)                 transfers from factor F to institution INS (including rest of world)
 x_trnsi(INS,INS,SIM)               transfers from institution INS) to institution INSP (including rest of world)

*Model variables (parameters ending with X contain post-solution values)
 x_CPI(SIM)                         consumer price index (PQ-based)
 x_DMPS(SIM)                        change in marginal propensity to save for selected institution
 x_DPI(SIM)                         index for domestic producer prices (PDS-based)
 x_DTA(SIM)                         additive activity tax (TA) adjustment
 x_DTE(SIM)                         additive export tax (TE) adjustment
 x_DTF(SIM)                         additive direct factor tax (TF) adjustment
 x_DTI(SIM)                         additive domestic institution tax (TI) adjustment
 x_DTM(SIM)                         additive import tariff (TM) adjustment
 x_DTQ(SIM)                         additive sales tax (TQ) adjustment
 x_DTV(SIM)                         additive value-added tax (TV) adjustment
 x_EG(SIM)                          total current government expenditure
 x_EH(H,SIM)                        household consumption expenditure
 x_EXR(SIM)                         exchange rate
 x_FSAV(SIM)                        foreign savings
 x_GADJ(SIM)                        government demand scaling factor
 x_GOVSHR(SIM)                      government consumption share of absorption
 x_GSAV(SIM)                        government savings
 x_IADJ(SIM)                        investment scaling factor (for fixed capital formation)
 x_INVSHR(SIM)                      investment share of absorption
 x_MPS(AC,SIM)                      marginal propensity to save for domestic non-government institution INS
 x_MPSADJ(SIM)                      savings rate (MPS) scaling factor
 x_PA(A,SIM)                        output price of activity A
 x_PDD(C,SIM)                       demand price for commodity C produced and sold domestically
 x_PDS(C,SIM)                       supply price for commodity C produced and sold domestically
 x_PE(C,SIM)                        price of export aggregate to producer excluding transport costs
 x_PM(C,SIM)                        price of import aggregate to demander including transport costs
 x_PINTA(A,SIM)                     price of intermediate aggregate
 x_PQ(C,SIM)                        price of composite commodity C
 x_PSAV(SIM)                        total private savings
 x_PVA(A,SIM)                       value added price
 x_PX(C,SIM)                        average output price
 x_PXAC(A,C,SIM)                    price of commodity C from activity A
 x_QA(A,SIM)                        level of domestic activity
 x_QD(C,SIM)                        quantity of domestic sales
 x_QE(C,SIM)                        quantity of exports
 x_QF(F,A,SIM)                      quantity demanded of factor F from activity A
 x_QFS(F,SIM)                       quantity of factor supply
 x_QG(C,SIM)                        quantity of government consumption
 x_QH(C,H,SIM)                      quantity consumed of marketed commodity C by household H
 x_QHA(A,H,SIM)                     quantity consumed of home activity A by household H
 x_QINT(C,A,SIM)                    quantity of intermediate demand for commodity C from activity A
 x_QINTA(A,SIM)                     quantity of aggregate intermediate input
 x_QINV(C,SIM)                      quantity of fixed investment demand
 x_QM(C,SIM)                        quantity of imports
 x_QQ(C,SIM)                        quantity of composite goods supply
 x_QT(C,SIM)                        quantity of trade and transport demand for commodity C
 x_QVA(A,SIM)                       quantity of aggregate value added
 x_QX(C,SIM)                        quantity of aggregate marketed commodity output
 x_QXAC(A,C,SIM)                    quantity of ouput of commodity C from activity A
 x_TA(A,SIM)                        activity tax rates
 x_TAADJ(SIM)                       activity tax (TA) scaling factor
 x_TABS(SIM)                        total absorption
 x_TE(C,SIM)                        export tax rates
 x_TEADJ(SIM)                       export tax (TE) scaling factor
 x_TF(F,SIM)                        direct factor tax rates
 x_TFADJ(SIM)                       direct factor tax (TF) scaling factor
 x_TI(AC,SIM)                       direct tax rates on domestic institutions INSD
 x_TIADJ(SIM)                       direct tax (TI) scaling factor
 x_TM(C,SIM)                        import tariff rates
 x_TMADJ(SIM)                       import tariff (TM) scaling factor
 x_TRII(AC,ACP,SIM)                 transfers from column institutions INSF to row institutions INS
 x_TQ(C,SIM)                        composite commodity taxes
 x_TQADJ(SIM)                       composite commodity tax (TQ) scaling factor
 x_TV(A,SIM)                        value-added tax rate
 x_TVADJ(SIM)                       value-added tax (TV) scaling factor
 x_WALRAS(SIM)                      savings-investment imbalance (should be zero)
 x_WF(F,SIM)                        economywide wage (rent) for factor F
 x_WFDIST(F,A,SIM)                  wage distortion variable for factor F in activity A
 x_YF(F,SIM)                        factor income from activities
 x_YG(SIM)                          total government income
 x_YI(INS,SIM)                      income of domestic non-government institution INS
 x_YIF(INS,F,SIM)                   income of institution INS from factor F

*Closures
 x_MACCLOSURES(*,SIM)               macro closures actually used (by sim)
 x_FACCLOSURES(F,SIM)               factor closures actually used (by sim and f)

*Calculated reporting parameters    
 x_SAMBUD(SAC,AC,IND3,AC,SIM)       budgets for SAM accounts
 x_GDPTAB1(KGDP,IGDP,SIM)           GDP and national accounts
 x_GDPTAB2(KGDP,AC,SIM)             GDP at factor cost by activity
 
*Solution reporting and error-checking parameters
 x_SAMBUDGAP(SAC,AC,SIM)            absolute value of income minus spending gaps for SAM account budgets
 x_GDPGAP(SIM)                      gaps in GDP reports
 x_SOLVEREP(SOLVEIND,MODTYPE,SIM)   model and solver status & number of redefined equations by model type
 x_GAPWARN(SIM)                     error if absolute SAMBUDGAP is above cutoff
 x_WALRASWARN(SIM)                  error if absolute value of WALRAS is above cutoff
 x_SOLVEWARN(SOLVEIND,MODTYPE,SIM)   error if values of SOLVEREP are illegal 
 x_NEGPWARN(C,SIM)                  commodity C has one or more negative prices for simulation SIM
 x_NEGQWARN(C,SIM)                  commodity C has one or more negative quantities for simulation SIM
 x_NEGWFWARN(F,SIM)                 factor F has one or more negative wages for simulation SIM 
 x_NEGQFWARN(F,SIM)                 factor F has one or more negative quantities for simulation SIM
;