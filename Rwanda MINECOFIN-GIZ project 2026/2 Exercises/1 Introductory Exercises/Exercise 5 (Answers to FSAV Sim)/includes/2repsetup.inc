$STITLE Input file: REPSETUP.INC. Sets and parameters for reports. Standard CGE modeling system, Version 1.01

*SETS AND PARAMETERS FOR REPORTS++++++++


SET

 SAC  SAM account categories
 /
 ACT     actitivities
 COM     commodities
 FAC     factors
 INSDNG  domestic non-government institutions
 GOV     government
 SAVINV  savings-investments
 INSTAX  direct taxes on institutions
 FACTAX  direct taxes on factors
 VATAX   value added tax
 ACTTAX  tax on activity gross revenue
 COMTAX  tax on commodity sales in the domestic market
 IMPTAX  import tariff
 EXPTAX  export tax
 ROW     rest of world (FCU)
 /

 IND3  third index for SAM budgets
 /
 INC
 SPND
 GAP
 /

 KGDP  first index in GDP tables
 /
 NOMINAL, REAL, NOMSHARE, REALSHARE, DEFLATOR
 /

 IGDP  Items for GDP and national accounts
  /
  ABSORP   absorption
  PRVCON   private consumption
  FIXINV   fixed investment
  DSTOCK   stock change
  GOVCON   government consumption
  EXPORTS  exports
  IMPORTS  imports
  GDPMP    GDP at market prices (alt. 1: spending)
  GDPMP2   GDP at market prices (alt. 2: value-added)
  NETITAX  net indirect taxes
  GDPFC2   GDP at factor cost
  /

 IGDP2(IGDP)  Items for GDPMP summation
  /
  PRVCON   private consumption
  FIXINV   fixed investment
  DSTOCK   stock change
  GOVCON   government consumption
  EXPORTS  exports
  IMPORTS  imports
  /


*The sets MODTYPE and SOLVEIND are used in the parameters SOLVEMAX,
*SOLVEREP, and SOLVEWARN.

 MODTYPE  model types
  /
 MCP mixed-complementarity programming
 NLP non-linear programming
 /

 SOLVEIND  solve indicators
 /
 MODEL-STATUS    model status
 SOLVER-STATUS   solver status
 NUM-REDEFEQ     number of redefined equations
 /
 ;



*==========================================================
*Parameter defining legal values for SOLVEREP==============
*==========================================================


TABLE
 SOLVEMAX(SOLVEIND,MODTYPE) max permitted value for SOLVEREP indicators

                MCP   NLP
MODEL-STATUS     1     2
SOLVER-STATUS    1     1
NUM-REDEFEQ      0     0

$ontext
Note: See the end of SIM.GMS (or the GAMS Users' Guide) for explanation
of what different values for MODEL-STATUS or SOLVER-STATUS represent.
NUM-REDEFEQ shows the number of redefined equations.
$offtext



*==========================================================
*Report parameters in LOOP=================================
*==========================================================
PARAMETERS
*Values for all model variables============================
*Values for all model variables (variable name + X)========
 CPIX(SIM)        consumer price index (PQ-based)
 DPIX(SIM)        index for domestic producer prices (PDS-based)
 DMPSX(SIM)       change in marginal propensity to save for selected inst
 DTINSX(SIM)      change in domestic institution tax share
 EGX(SIM)         total current government expenditure
 EHX(H,SIM)       household consumption expenditure
 EXRX(SIM)        exchange rate
 FSAVX(SIM)       foreign savings
 GADJX(SIM)       government demand scaling factor
 GOVSHRX(SIM)     govt consumption share of absorption
 GSAVX(SIM)       government savings
 IADJX(SIM)       investment scaling factor (for fixed capital formation)
 INVSHRX(SIM)     investment share of absorption
 MPSX(INS,SIM)    marginal propensity to save for dom non-gov inst ins
 MPSADJX(SIM)     savings rate scaling factor
 PAX(A,SIM)       output price of activity a
 PDDX(C,SIM)      demand price for com'y c produced & sold domestically
 PDSX(C,SIM)      supply price for com'y c produced & sold domestically
 PEX(C,SIM)       price of exports
 PINTAX(A,SIM)    price of intermediate aggregate
 PMX(C,SIM)       price of imports
 PQX(C,SIM)       price of composite good c
 PVAX(A,SIM)      value added price
 PWEX(C,SIM)      world price of exports
 PWMX(C,SIM)      world price of imports
 PXX(C,SIM)       average output price
 PXACX(A,C,SIM)   price of commodity c from activity a
 QAX(A,SIM)       level of domestic activity
 QDX(C,SIM)       qnty of domestic sales
 QEX(C,SIM)       qnty of exports
 QFX(F,A,SIM)     qnty demanded of factor f from activity a
 QFSX(F,SIM)      qnty of factor supply
 QGX(C,SIM)       qnty of government consumption
 QHX(C,H,SIM)     qnty consumed of market commodity c by household h
 QHAX(A,C,H,SIM)  qnty consumed of home commodity c fr act a by hhd h
 QINTX(C,A,SIM)   qnty of intermediate demand for c from activity a
 QINTAX(A,SIM)    qnty of aggregate intermediate input
 QINVX(C,SIM)     qnty of fixed investment demand
 QMX(C,SIM)       qnty of imports
 QQX(C,SIM)       qnty of composite goods supply
 QTX(C,SIM)       qnty of trade and transport demand for commodity c
 QVAX(A,SIM)      qnty of aggregate value added
 QXX(C,SIM)       qnty of aggregate marketed commodity output
 QXACX(A,C,SIM)   qnty of ouput of commodity c from activity a
 TABSX(SIM)       total absorption
 TINSX(INS,SIM)   rate of direct tax on domestic institutions ins
 TINSADJX(SIM)    direct tax scaling factor
 TRIIX(INS,INSP,SIM) transfers to dom. inst. insdng from insdngp
 WALRASX(SIM)     savings-investment imbalance (should be zero)
 WFX(F,SIM)       economy-wide wage (rent) for factor f
 WFDISTX(F,A,SIM) factor wage distortion variable
 YFX(F,SIM)       factor income
 YGX(SIM)         total current government income
 YIFX(INS,F,SIM)  income of institution ins from factor f
 YIX(INS,SIM)     income of (domestic non-governmental) institution ins

 WFAX(F,A,SIM)  price of factor f for activity a

*Budgets for SAM accounts==================================
 SAMBUD(SAC,AC,IND3,AC,SIM)  budgets for SAM accounts
*Note: For RoW, for exch earnings of model country defined as income;
*for exch spending of model country defined as spending

*National accounts data=====================================
 GDPTAB1(KGDP,IGDP,SIM) GDP and national accounts
 GDPTAB2(KGDP,AC,SIM)   GDP at factor cost by activity

*Macro and factor closures=================================
 MACCLOS(*,SIM)      Macro closures actually used (by sim)
 FACCLOS(F,*,SIM)    Factor closures actually used (by sim and f)

*==========================================================
*Post-calculated report parameters=========================
*==========================================================
*% change in LOOP parameters: above parameter name + P
*For base, these parameters show the base value.(%ch)
 CPIXP(SIM)        consumer price index (PQ-based) (%ch)
 DPIXP(SIM)        index for dom producer prices (PDS-based) (%ch)
*DMPSXP(SIM)       zero for base
*DTINSXP(SIM)      zero for base
 EGXP(SIM)         total current gov expenditure (%ch)
 EHXP(H,SIM)       hhd consumption expenditure (%ch)
 EXRXP(SIM)        exchange rate (%ch)
 FSAVXP(SIM)       foreign savings (%ch)
 GADJXP(SIM)       gov demand scaling factor (%ch)
 GOVSHRXP(SIM)     govt consumption share of absorption (%ch)
 GSAVXP(SIM)       gov savings (%ch)
 IADJXP(SIM)       fixed investment scaling factor (%ch)
 INVSHRXP(SIM)     investment share of absorption (%ch)
 MPSXP(INS,SIM)    marg prop to save for dom non-gov inst ins (%ch)
*MPSADJXP(SIM)     zero for base
 PAXP(A,SIM)       output price of activity a (%ch)
 PDDXP(C,SIM)      demand price for com'y c produced & sold dom'ly (%ch)
 PDSXP(C,SIM)      supply price for com'y c produced & sold dom'ly (%ch)
 PEXP(C,SIM)       price of exports (%ch)
 PINTAXP(A,SIM)    price of intermediate aggregate (%ch)
 PMXP(C,SIM)       price of imports (%ch)
 PQXP(C,SIM)       price of composite good c (%ch)
 PVAXP(A,SIM)      value added price (%ch)
 PWEXP(C,SIM)      world price of exports (%ch)
 PWMXP(C,SIM)      world price of imports (%ch)
 PXXP(C,SIM)       average output price (%ch)
 PXACXP(A,C,SIM)   price of comm c from activity a (%ch)
 QAXP(A,SIM)       level of dom activity (%ch)
 QDXP(C,SIM)       qnty of dom sales (%ch)
 QEXP(C,SIM)       qnty of exports (%ch)
 QFXP(F,A,SIM)     qnty demanded of factor f from activity a (%ch)
 QFSXP(F,SIM)      qnty of factor supply (%ch)
 QGXP(C,SIM)       qnty of gov consumption (%ch)
 QHXP(C,H,SIM)     qnty consumed of market comm c by hhd h (%ch)
 QHAXP(A,C,H,SIM)  qnty consumed of home comm c fr act a by hhd h (%ch)
 QINTXP(C,A,SIM)   qnty of intermediate demand for c from act'y a (%ch)
 QINTAXP(A,SIM)    qnty of aggregate intermediate input (%ch)
 QINVXP(C,SIM)     qnty of fixed investment demand (%ch)
 QMXP(C,SIM)       qnty of imports (%ch)
 QQXP(C,SIM)       qnty of composite goods supply (%ch)
 QTXP(C,SIM)       qnty of trade and transport demand for comm c (%ch)
 QVAXP(A,SIM)      qnty of aggregate value added (%ch)
 QXXP(C,SIM)       qnty of aggregate marketed comm output (%ch)
 QXACXP(A,C,SIM)   qnty of ouput of comm c from activity a (%ch)
 TABSXP(SIM)       total absorption (%ch)
 TINSXP(INS,SIM)   rate of direct tax on dom institutions ins (%ch)
*TINSADJXP(SIM)    zero for base
 TRIIXP(INS,INSP,SIM) transfers to dom. inst. insdng from insdngp (%ch)
*WALRASXP(SIM)     zero for base
 WFXP(F,SIM)       economy-wide wage (rent) for factor f (%ch)
 WFDISTXP(F,A,SIM) factor wage distortion variable (%ch)
 YFXP(F,SIM)       factor income (%ch)
 YGXP(SIM)         total current gov income (%ch)
 YIFXP(INS,F,SIM)  income of institution ins from factor f (%ch)
 YIXP(INS,SIM)     income of (dom non-gov) institution ins (%ch)

 WFAXP(F,A,SIM)  price of factor f for activity a (%ch)

*Other %-age change reports
 SAMBUDP(SAC,AC,IND3,AC,SIM) budgets for SAM accounts (%ch for non-base)
 GDPTAB1P(KGDP,IGDP,SIM) GDP and national accounts (%ch for non-base)
 GDPTAB2P(KGDP,AC,SIM)   GDP at f.c. by activity (%ch for non-base)

*Consistency and solution checks========================================
 SAMBUDGAP(SAC,AC,SIM) abs value of inc-spnd gaps for SAM acc budgets
 GDPGAP(SIM)                    gaps in GDP reports
 SOLVEREP(SOLVEIND,MODTYPE,SIM) model+solver status & no of redef eq'ons by model type

 NEGPWARN(C,SIM)  comm c has one or more neg'e prices for sim'on sim
 NEGQWARN(C,SIM)  comm c has one or more neg'e qnties for sim'on sim
 NEGWFWARN(F,SIM) factor f has one or more neg'e wages for sim'on sim
 NEGQFWARN(F,SIM) factor f has one or more neg'e qnties for sim'on sim

 GAPWARN(SIM)     error if abs gap above cutoff
 WALRASWARN(SIM)  error if abs value of WALRAS above cutoff
 SOLVEWARN(SOLVEIND,MODTYPE,SIM)   error if values of SOLVEREP are illegal
 ;



*#*#*#*#*# THE END OF REPSETUP.INC #*#*#*#*