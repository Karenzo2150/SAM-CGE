$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2.5: Generate standard reporting outputs
 This include file (includes\2static_report.inc) generates standard reporting parameters that
 are exported to the user-named Excel (reps_%data%.inc). Note: All parameters exported to
 the standard Excel file start with "r_". 

SECTIONS:
 2.5.1   Sets and parameters for standard reporting 
 2.5.2   Base year information                      (r_STRUCBASE | r_TAXBASE)                                              
 2.5.3   Macroeconomic results                      (r_MACROTAB)                                                           
 2.5.4   Gross domestic product                     (r_GDPX | r_GDPXS | r_GDPXP | r_GDPMPX | r_GDPMPXS | r_GDPMPXP)        
 2.5.5   International trade                        (r_QEXP | r_QMXP)                                                      
 2.5.6   Prices                                     (r_PXXP | r_PQXP | r_PEXP | r_PMXP | r_PWEXP | r_PWMXP)                
 2.5.7   Factors                                    (r_QFSXP | r_WFXP | r_YFXP)                                            
 2.5.8   Households                                 (r_YIXP | r_QHHXP | r_QHCXP | r_TINSXP | r_MPSXP)                      
 2.5.9   Export results to Excel                                                                               
 2.5.10  EV and CV welfare measures                 (EV | CV) 
 2.5.11  Other reporting: Percentage deviations from base year
$offtext


*------------------------------------------------------------------
*2.5.1  Sets and parameters for standard reporting 
*------------------------------------------------------------------

SET
 RA                     all activity reporting accounts
 RAA(RA)                aggregate activity reporting accounts
 RF                     all factor reporting accounts
 RFA(RF)                aggregate factor reporting accounts
 RH                     all household reporting accounts
 RHA(RH)                aggregate household reporting accounts
 RD                     GDP demand-side accounts   / r_GDPFC, r_NETITAX, r_GDPMP, r_ABSORP, r_PRVCON, r_GOVCON, r_GCF, r_GFCF, r_STK, r_TRDBAL, r_EXP, r_IMP /
 NRAC                   nomrinal or real values    / NOMINAL, REAL /
 TAXAC                  tax table accounts         / tIMPshr, tIMPtax, tIMPrev, tEXPshr, tEXPtax, tEXPrev, tSALshr, tSALtax, tSALrev, tACTshr, tACTtax, tACTrev, tVADshr, tVADtax, tVADrev /
 SIND                   macro summary indicators   /
  QABSTOT                   real absorption (LCU at base prices)
  QHTOT                     real household consumption (LCU at base prices)
  QGTOT                     real government consumption (LCU at base prices)
  QINVTOT                   real investment (LCU at base prices)
  QETOT                     total real exports (LCU at base prices)
  QMTOT                     total real imports (LCU at base prices)
  REXR                      PPP real exchange rate (LCUs per FCU)
  NEXR                      nominal exchange rate (LCUs per FCU)
  PWEIND                    exports price index (FCU - 100 for base)
  PWMIND                    imports price index (FCU - 100 for base)
  PWIND                     world (tradables) price index (FCU - 100 for base)
  PDIND                     domestic (non-tradables) price index (100 for base)
  CPI                       consumer price index (100 for base)
  TOFT                      terms of trade (ratio pwe index and pwm index) (100 for base)
  INVGDP                    investment (share of nominal GDP)
  TSAVGDP                   total savings (share of nominal GDP)
  PRVSAVGDP                 private (household + enterprise) savings (share of nominal GDP)
  GOVSAVGDP                 government savings (share of nominal GDP)
  FORSAVGDP                 foreign savings (share of nominal GDP)
  TRDDEFGDP                 trade deficit (share of nominal GDP)
  TOTTXGDP                  total tax revenue (share of nominal GDP) 
  INDTXGDP                  indirect tax revenue (share of nominal GDP)
  ACTTXGDP                  activity tax revenue (share of nominal GDP)
  VADTXGDP                  value-added tax revenue (share of nominal GDP)
  COMTXGDP                  sales tax revenue (share of nominal GDP)
  EXPTXGDP                  export tax revenue (share of nominal GDP)
  IMPTXGDP                  import tariff revenue (share of nominal GDP)
  DIRTXGDP                  direct tax revenue (share of nominal GDP)
  FACTXGDP                  factor tax revenue (share of nominal GDP)
  INSTXGDP                  institution tax revenue (share of nominal GDP)
 /
 SINDDEV(SIND)          summary indicators showing deviation from BASE / INVGDP, TSAVGDP, PRVSAVGDP, FORSAVGDP, TRDDEFGDP, GOVSAVGDP, TOTTXGDP, INDTXGDP, ACTTXGDP, VADTXGDP, COMTXGDP, EXPTXGDP, IMPTXGDP, DIRTXGDP, FACTXGDP, INSTXGDP /
 SINDP(SIND)            summary indicators showing percent change
;

ALIAS (RA,RAP), (RF,RFP), (RH,RHP);

PARAMETERS
*Mappings activities, factors, and households to reporting accounts
 MAPRA(RA,A)            model activities to reporting activities
 MAPRC(RA,C)            model commodities to reporting activities
 MAPRF(RF,F)            model factors to reporting factors
 MAPRH(RH,H)            model households to reporting households
*Price index weights 
 pdwt(C)                weight of commodity C in PD index
 pwewt(C)               weight of commodity C in pwe index
 pwmwt(C)               weight of commodity C in pwm index
 pwwt(*)                weight of aggregate exports-imports in pw (tradables) index
*Reporting parameters (exported to Excel)
 r_STRUCBASE(RA,STRCOL) base year economic structure
 r_TAXBASE(RA,TAXAC)    base year activity and commodity taxes
 r_MACROTAB(SIND,SIM)   macroeconomic results
 r_GDPFCs(RA,SIM)       GDP at factor cost (share of total)
 r_GDPFCp(RA,SIM)       GDP at factor cost (percentage deviation)
 r_GDPMPs(NRAC,RD,SIM)  GDP at market prices (share of total)
 r_GDPMPp(NRAC,RD,SIM)  GDP at market prices (percentage deviation)
 r_QE(RA,SIM)           exports (percentage deviation)
 r_QM(RA,SIM)           imports (percentage deviation)
 r_PX(RA,SIM)           output supply prices (percentage deviation) 
 r_PQ(RA,SIM)           final composite demand prices (percentage deviation) 
 r_PE(RA,SIM)           export prices (percentage deviation) 
 r_PM(RA,SIM)           import prices (percentage deviation) 
 r_PWE(RA,SIM)          world export prices (percentage deviation) 
 r_PWM(RA,SIM)          world import prices (percentage deviation)
 r_QFS(RF,SIM)          total factor supply (percentage deviation)       
 r_WF(RF,SIM)           economywide factor wage or rent (percentage deviation)    
 r_YF(RF,SIM)           total factor income (percentage deviation)   
 r_YI(RH,SIM)           total household income (percentage deviation)
 r_QHH(RH,SIM)          total consumption by household (percentage deviation)
 r_QHC(RA,SIM)          total consumption by commodity (percentage deviation)
 r_TI(RH,SIM)           household direct tax rates
 r_MPS(RH,SIM)          household savings rates
*Processed values (used to generate reporting parameters)
 x_GDPFC(RA,SIM)        GDP at factor cost (value)
 x_GDPMP(NRAC,RD,SIM)   GDP at market prices (value)
;

*Read input data from excel file
$call 'GDXXRW i=data\\%folder%\statrep%dataext%.xlsx o=reps.gdx index=index!a5'
$gdxin reps.gdx
*Read sets and data
$load RA RF RH 
$loaddc RAA RFA RHA 
$loaddc MAPRA MAPRF MAPRH
$gdxin

 MAPRC(RA,C)$SUM(A, MAPAC(A,C) AND MAPRA(RA,A)) = YES;
 SINDP(SIND)$(NOT SINDDEV(SIND)) = YES; 


*------------------------------------------------------------------
*2.5.2  Base year information
*------------------------------------------------------------------

*Economic structure
 r_STRUCBASE(RA,'VAshr')  = SUM(A$MAPRA(RA,A), PVA0(A)*(1-TV0(A))*QVA0(A)) / SUM(A, PVA0(A)*(1-TV0(A))*QVA0(A)) * 100;
 r_STRUCBASE(RA,'PRDshr') = SUM(A$MAPRA(RA,A), PA0(A)*QA0(A)) / SUM(A, PA0(A)*QA0(A)) * 100;
 r_STRUCBASE(RA,'EMPshr') = SUM((FLAB,A)$MAPRA(RA,A), QF0(FLAB,A)) / SUM((FLAB,A), QF0(FLAB,A)) * 100;
 r_STRUCBASE(RA,'QQshr')  = SUM(C$MAPRC(RA,C), PQ0(C)*QQ0(C)) / SUM(C, PQ0(C)*QQ0(C)) * 100; 
 r_STRUCBASE(RA,'HHDshr') = (SUM((C,H)$MAPRC(RA,C), PQ0(C)*QH0(C,H)) + SUM((A,H)$MAPRA(RA,A), PA0(A)*QHA0(A,H))) / (SUM((C,H), PQ0(C)*QH0(C,H)) + SUM((A,H), PA0(A)*QHA0(A,H))) * 100;
 r_STRUCBASE(RA,'OWNshr')$SUM((A,H), PA0(A)*QHA0(A,H)) = SUM((A,H)$MAPRA(RA,A), PA0(A)*QHA0(A,H)) / SUM((A,H), PA0(A)*QHA0(A,H)) * 100;
 r_STRUCBASE(RA,'MKTshr') = SUM((C,H)$MAPRC(RA,C), PQ0(C)*QH0(C,H)) / SUM((C,H), PQ0(C)*QH0(C,H)) * 100;
 r_STRUCBASE(RA,'GOVshr') = SUM(C$MAPRC(RA,C), PQ0(C)*QG0(C)) / SUM(C, PQ0(C)*QG0(C)) * 100;
 r_STRUCBASE(RA,'INVshr') = SUM(C$MAPRC(RA,C), PQ0(C)*QINV0(C)) / SUM(C, PQ0(C)*QINV0(C)) * 100;
 r_STRUCBASE(RA,'EXPshr') = SUM(C$MAPRC(RA,C), pwe0(C)*EXR0*QE0(C)) / SUM(C, pwe0(C)*EXR0*QE0(C)) * 100;
 r_STRUCBASE(RA,'IMPshr') = SUM(C$MAPRC(RA,C), pwm0(C)*EXR0*QM0(C)) / SUM(C, pwm0(C)*EXR0*QM0(C)) * 100; 
 r_STRUCBASE(RA,'EXP-OUTshr')$SUM(C$MAPRC(RA,C), PX0(C)*QX0(C)) = SUM(C$MAPRC(RA,C), PE0(C)*EXR0*QE0(C)) / SUM(C$MAPRC(RA,C), PX0(C)*QX0(C)) * 100;
 r_STRUCBASE(RA,'IMP-DEMshr')$SUM(C$MAPRC(RA,C), PQ0(C)*(1-TQ0(C))*QQ0(C)) = SUM(C$MAPRC(RA,C), PM0(C)*EXR0*QM0(C)) / SUM(C$MAPRC(RA,C), PQ0(C)*(1-TQ0(C))*QQ0(C)) * 100;
 r_STRUCBASE(RA,'OWN-OUTshr')$SUM(A$MAPRA(RA,A), PA0(A)*QA0(A)) = SUM((A,H)$MAPRA(RA,A), PA0(A)*QHA0(A,H)) / SUM(A$MAPRA(RA,A), PA0(A)*QA0(A)) * 100; 
 r_STRUCBASE(RA,'TRMrate')$SUM(C$MAPRC(RA,C), QM0(C)) = SUM((C,CT)$MAPRC(RA,C), PQ0(CT)*icm0(CT,C)*QM0(C)) / SUM(C$MAPRC(RA,C), PM0(C)*QM0(C)) * 100;
 r_STRUCBASE(RA,'TRErate')$SUM(C$MAPRC(RA,C), QE0(C)) = SUM((C,CT)$MAPRC(RA,C), PQ0(CT)*ice0(CT,C)*QE0(C)) / SUM(C$MAPRC(RA,C), PE0(C)*QE0(C) + SUM(CT, PQ0(CT)*ice0(CT,C)*QE0(C))) * 100;
 r_STRUCBASE(RA,'TRDrate')$SUM(C$MAPRC(RA,C), QD0(C)) = SUM((C,CT)$MAPRC(RA,C), PQ0(CT)*icd0(CT,C)*QD0(C)) / SUM(C$MAPRC(RA,C), PDD0(C)*QD0(C)) * 100;

*Activity and commodity taxes
*  Tax base shares
 r_TAXBASE(RA,'tIMPshr')$SUM(C, pwm0(C)*QM0(C))  = SUM(C$MAPRC(RA,C), pwm0(C)*QM0(C)) / SUM(C, pwm0(C)*QM0(C)) * 100;
 r_TAXBASE(RA,'tEXPshr')$SUM(C, pwe0(C)*QE0(C))  = SUM(C$MAPRC(RA,C), pwe0(C)*QE0(C)) / SUM(C, pwe0(C)*QE0(C)) * 100;
 r_TAXBASE(RA,'tSALshr')$SUM(C, PQ0(C)*QQ0(C))   = SUM(C$MAPRC(RA,C), PQ0(C)*QQ0(C)) / SUM(C, PQ0(C)*QQ0(C)) * 100;
 r_TAXBASE(RA,'tACTshr')$SUM(A, PA0(A)*QA0(A))   = SUM(A$MAPRA(RA,A), PA0(A)*QA0(A)) / SUM(A, PA0(A)*QA0(A)) * 100;
 r_TAXBASE(RA,'tVADshr')$SUM(A, PVA0(A)*QVA0(A)) = SUM(A$MAPRA(RA,A), PVA0(A)*QVA0(A)) / SUM(A, PVA0(A)*QVA0(A)) * 100;
*  Tax rates 
 r_TAXBASE(RA,'tIMPtax')$SUM(C$MAPRC(RA,C), QM0(C))  = SUM(C$MAPRC(RA,C), TM0(C)*pwm0(C)*QM0(C)*EXR0 / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), pwm0(CP)*QM0(CP)*EXR0)) * 100;
 r_TAXBASE(RA,'tEXPtax')$SUM(C$MAPRC(RA,C), QE0(C))  = SUM(C$MAPRC(RA,C), TE0(C)*pwe0(C)*QE0(C)*EXR0 / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), pwe0(CP)*QE0(CP)*EXR0)) * 100;
 r_TAXBASE(RA,'tSALtax')$SUM(C$MAPRC(RA,C), QQ0(C))  = SUM(C$MAPRC(RA,C), TQ0(C)*PQ0(C)*QQ0(C) / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PQ0(CP)*QQ0(CP))) * 100;
 r_TAXBASE(RA,'tACTtax')$SUM(A$MAPRA(RA,A), QA0(A))  = SUM(A$MAPRA(RA,A), TA0(A)*PA0(A)*QA0(A) / SUM(AP$(MAPRA(RA,A) AND MAPRA(RA,AP)), PA0(AP)*QA0(AP))) * 100;
 r_TAXBASE(RA,'tVADtax')$SUM(A$MAPRA(RA,A), QVA0(A)) = SUM(A$MAPRA(RA,A), TV0(A)*PVA0(A)*QVA0(A) / SUM(AP$(MAPRA(RA,A) AND MAPRA(RA,AP)), PVA0(AP)*QVA0(AP))) * 100;
*  Tax revenues
 r_TAXBASE(RA,'tIMPrev')$SUM(C, TM0(C)*pwm0(C)*QM0(C)*EXR0) = SUM(C$MAPRC(RA,C), TM0(C)*pwm0(C)*QM0(C)*EXR0) / SUM(C, TM0(C)*pwm0(C)*QM0(C)*EXR0) * 100;
 r_TAXBASE(RA,'tEXPrev')$SUM(C, TE0(C)*pwe0(C)*QE0(C)*EXR0) = SUM(C$MAPRC(RA,C), TE0(C)*pwe0(C)*QE0(C)*EXR0) / SUM(C, TE0(C)*pwe0(C)*QE0(C)*EXR0) * 100;
 r_TAXBASE(RA,'tSALrev')$SUM(C, TQ0(C)*PQ0(C)*QQ0(C))       = SUM(C$MAPRC(RA,C), TQ0(C)*PQ0(C)*QQ0(C)) / SUM(C, TQ0(C)*PQ0(C)*QQ0(C)) * 100;      
 r_TAXBASE(RA,'tACTrev')$SUM(A, TA0(A)*PA0(A)*QA0(A))       = SUM(A$MAPRA(RA,A), TA0(A)*PA0(A)*QA0(A)) / SUM(A, TA0(A)*PA0(A)*QA0(A)) * 100;      
 r_TAXBASE(RA,'tVADrev')$SUM(A, TV0(A)*PVA0(A)*QVA0(A))     = SUM(A$MAPRA(RA,A), TV0(A)*PVA0(A)*QVA0(A)) / SUM(A, TV0(A)*PVA0(A)*QVA0(A)) * 100;   


*------------------------------------------------------------------
*2.5.3  Macroeconomic results
*------------------------------------------------------------------

*Price index weights
 pdwt(C)     = PDS0(C)*QD0(C) / SUM(CP, PDS0(CP)*QD0(CP));
 pwewt(C)    = pwe0(C)*QE0(C) / SUM(CP, pwe0(CP)*QE0(CP));
 pwmwt(C)    = pwm0(C)*QM0(C) / SUM(CP, pwm0(CP)*QM0(CP));
 pwwt('EXP') = SUM(CP, pwe0(CP)*QE0(CP)) / (SUM(CP, pwe0(CP)*QE0(CP)) + SUM(CP, pwm0(CP)*QM0(CP)));
 pwwt('IMP') = SUM(CP, pwm0(CP)*QM0(CP)) / (SUM(CP, pwe0(CP)*QE0(CP)) + SUM(CP, pwm0(CP)*QM0(CP)));
 
*Real quantities
 r_MACROTAB('QINVTOT',SIMC) = SUM(C, PQ0(C)*x_QINV(C,SIMC) + PQ0(C)*x_qdst(C,SIMC));
 r_MACROTAB('QGTOT',SIMC)   = SUM(C, PQ0(C)*x_QG(C,SIMC));
 r_MACROTAB('QHTOT',SIMC)   = SUM((C,H), PQ0(C)*x_QH(C,H,SIMC)) + SUM((A,H), PA0(A)*x_QHA(A,H,SIMC)) ;
 r_MACROTAB('QETOT',SIMC)   = SUM(C, pwe0(C)*x_QE(C,SIMC)*EXR0);  
 r_MACROTAB('QMTOT',SIMC)   = SUM(C, pwm0(C)*x_QM(C,SIMC)*EXR0);  
 r_MACROTAB('QABSTOT',SIMC) = r_MACROTAB('QINVTOT',SIMC) + r_MACROTAB('QGTOT',SIMC)  + r_MACROTAB('QHTOT',SIMC);

*Exchange rates and price indices
 r_MACROTAB('CPI',SIMC)     = x_CPI(SIMC)/CPI0 * 100;
 r_MACROTAB('NEXR',SIMC)    = x_EXR(SIMC) * 100;
 r_MACROTAB('PDIND',SIMC)   = SUM(C, pdwt(C)*x_PDS(C,SIMC)) * 100;
 r_MACROTAB('PWEIND',SIMC)  = SUM(C, x_pwe(C,SIMC)*pwewt(C)) / SUM(C, pwe0(C)*pwewt(C)) * 100;
 r_MACROTAB('PWMIND',SIMC)  = SUM(C, x_pwm(C,SIMC)*pwmwt(C)) / SUM(C, pwm0(C)*pwmwt(C)) * 100;
 r_MACROTAB('TOFT',SIMC)    = r_MACROTAB('PWEIND',SIMC) / r_MACROTAB('PWMIND',SIMC) * 100;
 r_MACROTAB('PWIND',SIMC)   = pwwt('EXP')*r_MACROTAB('PWEIND',SIMC) + pwwt('IMP')*r_MACROTAB('PWMIND',SIMC);
 r_MACROTAB('REXR',SIMC)    = r_MACROTAB('NEXR',SIMC)*r_MACROTAB('PWIND',SIMC)/r_MACROTAB('PDIND',SIMC);

*Nominal GDP shares
 r_MACROTAB('INVGDP',SIMC)    = (SUM(C, x_PQ(C,SIMC)*x_QINV(C,SIMC)) + SUM(C, x_PQ(C,SIMC)*x_qdst(C,SIMC))) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100; 
 r_MACROTAB('PRVSAVGDP',SIMC) = SUM(INSDNG, x_SAMBUD('INSDNG',INSDNG,'SPND','S-I',SIMC)) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('FORSAVGDP',SIMC) = x_EXR(SIMC)*x_FSAV(SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('TRDDEFGDP',SIMC) = (SUM(C, x_PM(C,SIMC)*x_QM(C,SIMC)) - SUM(C, x_PE(C,SIMC)*x_QE(C,SIMC))) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('GOVSAVGDP',SIMC) = x_SAMBUD('GOV','DUM','SPND','S-I',SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('TSAVGDP',SIMC)   = r_MACROTAB('PRVSAVGDP',SIMC) + r_MACROTAB('FORSAVGDP',SIMC) + r_MACROTAB('GOVSAVGDP',SIMC);
 r_MACROTAB('ACTTXGDP',SIMC)  = x_SAMBUD('GOV','DUM','INC','ACTTAX',SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('VADTXGDP',SIMC)  = x_SAMBUD('GOV','DUM','INC','VATTAX',SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('COMTXGDP',SIMC)  = x_SAMBUD('GOV','DUM','INC','COMTAX',SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('EXPTXGDP',SIMC)  = x_SAMBUD('GOV','DUM','INC','EXPTAX',SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('IMPTXGDP',SIMC)  = x_SAMBUD('GOV','DUM','INC','IMPTAX',SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('FACTXGDP',SIMC)  = x_SAMBUD('GOV','DUM','INC','FACTAX',SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('INSTXGDP',SIMC)  = x_SAMBUD('GOV','DUM','INC','INSTAX',SIMC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC) * 100;
 r_MACROTAB('INDTXGDP',SIMC)  = r_MACROTAB('ACTTXGDP',SIMC) + r_MACROTAB('VADTXGDP',SIMC) + r_MACROTAB('COMTXGDP',SIMC) + r_MACROTAB('EXPTXGDP',SIMC) + r_MACROTAB('IMPTXGDP',SIMC);
 r_MACROTAB('DIRTXGDP',SIMC)  = r_MACROTAB('FACTXGDP',SIMC) + r_MACROTAB('INSTXGDP',SIMC);
 r_MACROTAB('TOTTXGDP',SIMC)  = r_MACROTAB('INDTXGDP',SIMC) + r_MACROTAB('DIRTXGDP',SIMC);

*Percentage deviation
 r_MACROTAB(SINDP,SIMNB)$SIMC(SIMNB) = (r_MACROTAB(SINDP,SIMNB)/r_MACROTAB(SINDP,'BASE') - 1) * 100;

*Percentage-point deviation  
 r_MACROTAB(SINDDEV,SIMNB)$SIMC(SIMNB) = r_MACROTAB(SINDDEV,SIMNB) - r_MACROTAB(SINDDEV,'BASE');
 

*------------------------------------------------------------------
*2.5.4  Gross domestic product
*------------------------------------------------------------------

*--- GDP at factor cost ---

*Real values
 x_GDPFC(RA,SIMC)  = SUM(A$MAPRA(RA,A), PVA0(A)*(1-TV0(A))*x_QVA(A,SIMC));

*Real shares
 r_GDPFCs(RA,SIMC)  = x_GDPFC(RA,SIMC) / SUM(A, PVA0(A)*(1-TV0(A))*x_QVA(A,SIMC)) * 100;
 r_GDPFCs(RA,SIMNB) = r_GDPFCs(RA,SIMNB) - r_GDPFCs(RA,'BASE'); 

*Percentage deviation
 r_GDPFCp(RA,SIMC)$x_GDPFC(RA,'BASE') = (X_GDPFC(RA,SIMC)/X_GDPFC(RA,'BASE')-1) * 100;
 r_GDPFCp(RA,'BASE') = r_GDPFCs(RA,'BASE');
 
*--- GDP at market prices ---

*Nominal values
 x_GDPMP('NOMINAL','r_PRVCON',SIMC)  = SUM((C,H), x_PQ(C,SIMC)*x_QH(C,H,SIMC)) + SUM((A,H), x_PA(A,SIMC)*x_QHA(A,H,SIMC));
 x_GDPMP('NOMINAL','r_GOVCON',SIMC)  = SUM(C, x_PQ(C,SIMC)*x_QG(C,SIMC)); 
 x_GDPMP('NOMINAL','r_GFCF',SIMC)    = SUM(C, x_PQ(C,SIMC)*x_QINV(C,SIMC)); 
 x_GDPMP('NOMINAL','r_STK',SIMC)     = SUM(C, x_PQ(C,SIMC)*x_qdst(C,SIMC)); 
 x_GDPMP('NOMINAL','r_GCF',SIMC)     = x_GDPMP('NOMINAL','r_GFCF',SIMC) + x_GDPMP('NOMINAL','r_STK',SIMC); 
 x_GDPMP('NOMINAL','r_EXP',SIMC)     = SUM(C, x_pwe(C,SIMC)*x_QE(C,SIMC)*x_EXR(SIMC));
 x_GDPMP('NOMINAL','r_IMP',SIMC)     = SUM(C, x_pwm(C,SIMC)*x_QM(C,SIMC)*x_EXR(SIMC)); 
 x_GDPMP('NOMINAL','r_TRDBAL',SIMC)  = x_GDPMP('NOMINAL','r_EXP',SIMC) - x_GDPMP('NOMINAL','r_IMP',SIMC);
 x_GDPMP('NOMINAL','r_ABSORP',SIMC)  = x_GDPMP('NOMINAL','r_PRVCON',SIMC) + x_GDPMP('NOMINAL','r_GOVCON',SIMC) + x_GDPMP('NOMINAL','r_GCF',SIMC);
 x_GDPMP('NOMINAL','r_GDPMP',SIMC)   = x_GDPMP('NOMINAL','r_ABSORP',SIMC) + x_GDPMP('NOMINAL','r_TRDBAL',SIMC);
 x_GDPMP('NOMINAL','r_GDPFC',SIMC)   = SUM(A, x_PVA(A,SIMC)*(1-x_TV(A,SIMC))*x_QVA(A,SIMC)); 
 x_GDPMP('NOMINAL','r_NETITAX',SIMC) = x_GDPMP('NOMINAL','r_GDPMP',SIMC) - x_GDPMP('NOMINAL','r_GDPFC',SIMC);

*Real values
 x_GDPMP('REAL','r_PRVCON',SIMC)     = SUM((C,H), PQ0(C)*x_QH(C,H,SIMC)) + SUM((A,H), PA0(A)*x_QHA(A,H,SIMC));
 x_GDPMP('REAL','r_GOVCON',SIMC)     = SUM(C, PQ0(C)*x_QG(C,SIMC)); 
 x_GDPMP('REAL','r_GFCF',SIMC)       = SUM(C, PQ0(C)*x_QINV(C,SIMC)); 
 x_GDPMP('REAL','r_STK',SIMC)        = SUM(C, PQ0(C)*x_qdst(C,SIMC)); 
 x_GDPMP('REAL','r_GCF',SIMC)        = x_GDPMP('REAL','r_GFCF',SIMC) + x_GDPMP('REAL','r_STK',SIMC); 
 x_GDPMP('REAL','r_EXP',SIMC)        = SUM(C, pwe0(C)*x_QE(C,SIMC)*EXR0);
 x_GDPMP('REAL','r_IMP',SIMC)        = SUM(C, pwm0(C)*x_QM(C,SIMC)*EXR0); 
 x_GDPMP('REAL','r_TRDBAL',SIMC)     = x_GDPMP('REAL','r_EXP',SIMC) - x_GDPMP('REAL','r_IMP',SIMC);
 x_GDPMP('REAL','r_ABSORP',SIMC)     = x_GDPMP('REAL','r_PRVCON',SIMC) + x_GDPMP('REAL','r_GOVCON',SIMC) + x_GDPMP('REAL','r_GCF',SIMC);
 x_GDPMP('REAL','r_GDPMP',SIMC)      = x_GDPMP('REAL','r_ABSORP',SIMC) + x_GDPMP('REAL','r_TRDBAL',SIMC);
 x_GDPMP('REAL','r_GDPFC',SIMC)      = SUM(A, PVA0(A)*(1-TV0(A))*x_QVA(A,SIMC)); 
 x_GDPMP('REAL','r_NETITAX',SIMC)    = x_GDPMP('REAL','r_GDPMP',SIMC) - x_GDPMP('REAL','r_GDPFC',SIMC);
       
*Shares
 r_GDPMPs(NRAC,RD,SIMC)$x_GDPMP(NRAC,'r_GDPMP',SIMC) = x_GDPMP(NRAC,RD,SIMC)/x_GDPMP(NRAC,'r_GDPMP',SIMC) * 100;
 r_GDPMPs(NRAC,RD,SIMC)$SIMNB(SIMC)                  = r_GDPMPs(NRAC,RD,SIMC) - r_GDPMPs(NRAC,RD,'BASE');

*Percentage deviation
 r_GDPMPp(NRAC,RD,SIMC)$x_GDPMP(NRAC,RD,'BASE') = (x_GDPMP(NRAC,RD,SIMC)/x_GDPMP(NRAC,RD,'BASE')-1) * 100;
 r_GDPMPp(NRAC,RD,'BASE')                       = r_GDPMPs(NRAC,RD,'BASE');
 

*------------------------------------------------------------------
*2.5.5  International trade
*------------------------------------------------------------------

*Exports (percentage deviation)
 r_QE(RA,SIMC)$SUM(C$MAPRC(RA,C), QE0(C)) = (SUM(C$MAPRC(RA,C), pwe0(C)*x_QE(C,SIMC)*EXR0)/SUM(C$MAPRC(RA,C), pwe0(C)*QE0(C)*EXR0)-1) * 100;
 r_QE(RA,'BASE')$SUM(C, QE0(C))           =  SUM(C$MAPRC(RA,C), pwe0(C)*QE0(C)*EXR0)/SUM(C, pwe0(C)*QE0(C)*EXR0) * 100;

*Imports (percentage deviation)
 r_QM(RA,SIMC)$SUM(C$MAPRC(RA,C), QM0(C)) = (SUM(C$MAPRC(RA,C), pwm0(C)*x_QM(C,SIMC)*EXR0)/SUM(C$MAPRC(RA,C), pwm0(C)*QM0(C)*EXR0)-1) * 100;
 r_QM(RA,'BASE')$SUM(C, QM0(C))           =  SUM(C$MAPRC(RA,C), pwm0(C)*QM0(C)*EXR0)/SUM(C, pwm0(C)*QM0(C)*EXR0) * 100;
 

*------------------------------------------------------------------
*2.5.6  Prices
*------------------------------------------------------------------

*Weighted values
 r_PX(RA,SIMC)$SUM(C$MAPRC(RA,C), QX0(C))  = SUM(C$MAPRC(RA,C), x_PX(C,SIMC)  * PX0(C)*QX0(C)  / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PX0(CP)*QX0(CP)));          
 r_PQ(RA,SIMC)$SUM(C$MAPRC(RA,C), QQ0(C))  = SUM(C$MAPRC(RA,C), x_PQ(C,SIMC)  * PQ0(C)*QQ0(C)  / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PQ0(CP)*QQ0(CP))); 
 r_PE(RA,SIMC)$SUM(C$MAPRC(RA,C), QE0(C))  = SUM(C$MAPRC(RA,C), x_PE(C,SIMC)  * PE0(C)*QE0(C)  / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PE0(CP)*QE0(CP))); 
 r_PM(RA,SIMC)$SUM(C$MAPRC(RA,C), QM0(C))  = SUM(C$MAPRC(RA,C), x_PM(C,SIMC)  * PM0(C)*QM0(C)  / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PM0(CP)*QM0(CP))); 
 r_PWE(RA,SIMC)$SUM(C$MAPRC(RA,C), QE0(C)) = SUM(C$MAPRC(RA,C), x_pwe(C,SIMC) * pwe0(C)*QE0(C) / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), pwe0(CP)*QE0(CP)));
 r_PWM(RA,SIMC)$SUM(C$MAPRC(RA,C), QM0(C)) = SUM(C$MAPRC(RA,C), x_pwm(C,SIMC) * pwm0(C)*QM0(C) / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), pwm0(CP)*QM0(CP)));

*Percentage deviation
 r_PX(RA,SIMC)$(SIMNB(SIMC) AND r_PX(RA,'BASE'))   = (r_PX(RA,SIMC)/r_PX(RA,'BASE')-1) * 100;
 r_PQ(RA,SIMC)$(SIMNB(SIMC) AND r_PQ(RA,'BASE'))   = (r_PQ(RA,SIMC)/r_PQ(RA,'BASE')-1) * 100;
 r_PE(RA,SIMC)$(SIMNB(SIMC) AND r_PE(RA,'BASE'))   = (r_PE(RA,SIMC)/r_PE(RA,'BASE')-1) * 100;
 r_PM(RA,SIMC)$(SIMNB(SIMC) AND r_PM(RA,'BASE'))   = (r_PM(RA,SIMC)/r_PM(RA,'BASE')-1) * 100;
 r_PWE(RA,SIMC)$(SIMNB(SIMC) AND r_PWE(RA,'BASE')) = (r_PWE(RA,SIMC)/r_PWE(RA,'BASE')-1) * 100;
 r_PWM(RA,SIMC)$(SIMNB(SIMC) AND r_PWM(RA,'BASE')) = (r_PWM(RA,SIMC)/r_PWM(RA,'BASE')-1) * 100;
  
*Weights
 r_PX(RA,'BASE')$SUM(CP, PX0(CP)*QX0(CP))   = SUM(C$MAPRC(RA,C), PX0(C)*QX0(C) / SUM(CP, PX0(CP)*QX0(CP))) * 100; 
 r_PQ(RA,'BASE')$SUM(CP, PQ0(CP)*QQ0(CP))   = SUM(C$MAPRC(RA,C), PQ0(C)*QQ0(C) / SUM(CP, PQ0(CP)*QQ0(CP))) * 100; 
 r_PE(RA,'BASE')$SUM(CP, PE0(CP)*QE0(CP))   = SUM(C$MAPRC(RA,C), PE0(C)*QE0(C) / SUM(CP, PE0(CP)*QE0(CP))) * 100; 
 r_PM(RA,'BASE')$SUM(CP, PM0(CP)*QM0(CP))   = SUM(C$MAPRC(RA,C), PM0(C)*QM0(C) / SUM(CP, PM0(CP)*QM0(CP))) * 100; 
 r_PWE(RA,'BASE')$SUM(CP, pwe0(CP)*QE0(CP)) = SUM(C$MAPRC(RA,C), pwe0(C)*QE0(C) / SUM(CP, pwe0(CP)*QE0(CP))) * 100;
 r_PWM(RA,'BASE')$SUM(CP, pwm0(CP)*QM0(CP)) = SUM(C$MAPRC(RA,C), pwm0(C)*QM0(C) / SUM(CP, pwm0(CP)*QM0(CP))) * 100;

  
*------------------------------------------------------------------
*2.5.7  Factors 
*------------------------------------------------------------------ 

*Total factor supply (percentage deviation)       
 r_QFS(RF,SIMC)$SUM(F$MAPRF(RF,F), x_QFS(F,SIMC)) = (SUM(F$MAPRF(RF,F), x_QFS(F,SIMC))/SUM(F$MAPRF(RF,F), x_QFS(F,'BASE'))-1) * 100;
 r_QFS(RF,'BASE')                                 = SUM(F$MAPRF(RF,F), QFS0(F));

*Economywide factor wage or rent (percentage deviation)    
 r_WF(RF,SIMC)$SUM((F,A)$MAPRF(RF,F), x_QF(F,A,SIMC)) = SUM((F,A)$MAPRF(RF,F), x_WF(F,SIMC)*x_WFDIST(F,A,SIMC)*x_QF(F,A,SIMC)) / SUM((F,A)$MAPRF(RF,F), x_QF(F,A,SIMC));
 r_WF(RF,SIMC)$r_WF(RF,'BASE')                        = (r_WF(RF,SIMC)/r_WF(RF,'BASE')-1) * 100;
 r_WF(RF,'BASE')$SUM((F,A)$MAPRF(RF,F), QF0(F,A))     = SUM((F,A)$MAPRF(RF,F), WF0(F)*WFDIST0(F,A)*QF0(F,A)) / SUM((F,A)$MAPRF(RF,F), QF0(F,A));

*Total factor income (percentage deviation)   
 r_YF(RF,SIMC)$SUM(F$MAPRF(RF,F), x_QFS(F,SIMC)) = SUM(F$MAPRF(RF,F), x_YF(F,SIMC)) / SUM(F$MAPRF(RF,F), x_QFS(F,SIMC));
 r_YF(RF,SIMC)$r_YF(RF,'BASE')                   = (r_YF(RF,SIMC)/r_YF(RF,'BASE')-1) * 100;
 r_YF(RF,'BASE')$SUM(F$MAPRF(RF,F), QFS0(F))     = SUM(F$MAPRF(RF,F), YF0(F));


*------------------------------------------------------------------
*2.5.8  Households
*------------------------------------------------------------------

*Total household income (percentage deviation)
 r_YI(RH,SIMC)$SUM(H$MAPRH(RH,H), x_YI(H,'BASE')) = (SUM(H$MAPRH(RH,H), x_YI(H,SIMC)) / SUM(H$MAPRH(RH,H), YI0(H))-1) * 100;
 r_YI(RH,'BASE')$SUM(H, YI0(H))                   =  SUM(H$MAPRH(RH,H), YI0(H)) / SUM(H, YI0(H)) * 100;
    
*Total consumption by household (percentage deviation)
 r_QHH(RH,SIMC)$SUM((C,H)$MAPRH(RH,H), PQ0(C)*QH0(C,H)) = (SUM((C,H)$MAPRH(RH,H), PQ0(C)*x_QH(C,H,SIMC)) / SUM((C,H)$MAPRH(RH,H), PQ0(C)*QH0(C,H))-1) * 100;
 r_QHH(RH,'BASE')$SUM((C,H), PQ0(C)*QH0(C,H))           =  SUM((C,H)$MAPRH(RH,H), PQ0(C)*QH0(C,H)) / SUM((C,H), PQ0(C)*QH0(C,H)) * 100;
 
*Total consumption by commodity (percentage deviation)
 r_QHC(RA,SIMC)$SUM((C,H)$MAPRC(RA,C), PQ0(C)*QH0(C,H)) = (SUM((C,H)$MAPRC(RA,C), PQ0(C)*x_QH(C,H,SIMC)) / SUM((C,H)$MAPRC(RA,C), PQ0(C)*QH0(C,H))-1) * 100;        
 r_QHC(RA,'BASE')$SUM((C,H), PQ0(C)*QH0(C,H))           =  SUM((C,H)$MAPRC(RA,C), PQ0(C)*QH0(C,H)) / SUM((C,H), PQ0(C)*QH0(C,H)) * 100;

*Household direct tax rates
 r_TI(RH,SIMC)$SUM(H$MAPRH(RH,H), YI0(H)) = SUM(H$MAPRH(RH,H), x_TI(H,SIMC)*YI0(H)) / SUM(H$MAPRH(RH,H), YI0(H)) * 100;
 r_TI(RH,SIMC)                            = r_TI(RH,SIMC) - r_TI(RH,'BASE'); 
 r_TI(RH,'BASE')$SUM(H, YI0(H))           = SUM(H$MAPRH(RH,H), TI0(H)*YI0(H)) / SUM(H, YI0(H)) * 100;
 
*Household savings rates
 r_MPS(RH,SIMC)$SUM(H$MAPRH(RH,H), YI0(H))  = SUM(H$MAPRH(RH,H), x_MPS(H,SIMC)*YI0(H)) / SUM(H$MAPRH(RH,H), YI0(H)) * 100;
 r_MPS(RH,SIMC)                             = r_MPS(RH,SIMC) - r_MPS(RH,'BASE');
 r_MPS(RH,'BASE')$SUM(H, YI0(H))            = SUM(H$MAPRH(RH,H), MPS0(H)*YI0(H)) / SUM(H, YI0(H)) * 100;


*------------------------------------------------------------------
*2.5.9  Export results to Excel
*------------------------------------------------------------------

*Missing values replaced with epsilon
 r_STRUCBASE(RA,STRCOL) $(NOT r_STRUCBASE(RA,STRCOL)) = eps;
 r_TAXBASE(RA,TAXAC)    $(NOT r_TAXBASE(RA,TAXAC)   ) = eps;
 r_MACROTAB(SIND,SIM)   $(NOT r_MACROTAB(SIND,SIM)  ) = eps; 
 r_GDPFCs(RA,SIM)       $(NOT r_GDPFCs(RA,SIM)      ) = eps;
 r_GDPFCp(RA,SIM)       $(NOT r_GDPFCp(RA,SIM)      ) = eps;
 r_GDPMPs(NRAC,RD,SIM)  $(NOT r_GDPMPs(NRAC,RD,SIM) ) = eps;
 r_GDPMPp(NRAC,RD,SIM)  $(NOT r_GDPMPp(NRAC,RD,SIM) ) = eps;
 r_QE(RA,SIM)           $(NOT r_QE(RA,SIM)          ) = eps;
 r_QM(RA,SIM)           $(NOT r_QM(RA,SIM)          ) = eps;
 r_PX(RA,SIM)           $(NOT r_PX(RA,SIM)          ) = eps;
 r_PQ(RA,SIM)           $(NOT r_PQ(RA,SIM)          ) = eps;
 r_PE(RA,SIM)           $(NOT r_PE(RA,SIM)          ) = eps;
 r_PM(RA,SIM)           $(NOT r_PM(RA,SIM)          ) = eps;
 r_PWE(RA,SIM)          $(NOT r_PWE(RA,SIM)         ) = eps;
 r_PWM(RA,SIM)          $(NOT r_PWM(RA,SIM)         ) = eps;
 r_QFS(RF,SIM)          $(NOT r_QFS(RF,SIM)         ) = eps;
 r_WF(RF,SIM)           $(NOT r_WF(RF,SIM)          ) = eps;  
 r_YF(RF,SIM)           $(NOT r_YF(RF,SIM)          ) = eps;
 r_YI(RH,SIM)           $(NOT r_YI(RH,SIM)          ) = eps;
 r_QHH(RH,SIM)          $(NOT r_QHH(RH,SIM)         ) = eps;
 r_QHC(RA,SIM)          $(NOT r_QHC(RA,SIM)         ) = eps;
 r_TI(RH,SIM)           $(NOT r_TI(RH,SIM)          ) = eps;
 r_MPS(RH,SIM)          $(NOT r_MPS(RH,SIM)         ) = eps;
 
*Export to Excel
PARAMETER XLTEST;
execute_unload "report.gdx" r_YI r_QHH r_QHC r_TI r_MPS r_YF r_WF r_QFS r_PX r_PQ r_PE r_PM r_PWE r_PWM r_QE r_QM r_GDPFCs r_GDPFCp r_GDPMPs r_GDPMPp r_MACROTAB r_STRUCBASE r_TAXBASE
execute 'xlstalk.exe -m data\\%folder%\statrep%dataext%.xlsx'; 
 XLTEST = ERRORLEVEL;
IF(XLTEST = 1,
execute 'xlstalk.exe -c data\\%folder%\statrep%dataext%.xlsx';
);
IF(XLTEST = 2,
execute 'xlstalk.exe -s data\\%folder%\statrep%dataext%.xlsx';
);
execute 'gdxxrw.exe i=report.gdx o=data\\%folder%\statrep%dataext%.xlsx index=index!a20' ;
execute 'xlstalk.exe -o data\\%folder%\statrep%dataext%.xlsx';
DISPLAY XLTEST;


*------------------------------------------------------------------
*2.5.10  EV and CV welfare measures
*------------------------------------------------------------------

PARAMETER
 IC(H,SIM)              indirect compensation function by household H and simulation SIM
 EV(AC,SIM)             equivalent variation by household AC and simulation SIM
 BETAAUX(H)             auxiliary term based on marginal spending shares
 PRICEIND(H,SIM)        price index
 EXPSUB(H,SIM)          subsistence spending for household H under simulation SIM
 INDUTIL(H,SIM)         indirect utility for household H under simulation SIM
 EXPV0(H,SIM)           base-utility expenditure function for household H under simulation SIM
 CV(AC,SIM)             compensating variation for household H under simulation SIM
 CV2(AC,SIM)            concise formula for CV
 EVX(AC,SIM)            disaggregated EV results
;

$ontext
 Source for IC and EV formulas (here adapted to fit demand system with home and market consumption):
 Blonigen, Bruce A., Joseph E. Flynn, and Kenneth A. Reinert (1997) Sector-Focused General Equilibrium
 Modeling, pp. 189-230 in eds. Joseph F. Francois and Kenneth A. Reinert, Applied Methods for Trade
 Policy Analysis. Cambridge, MA: Cambridge University Press. Formulas are on pp. 224-225.
 
 Sadoulet, E., and A. de Janvry (1995). Quantitative Development Policy Analysis. The Johns Hopkins
 University Press: Baltimore and London. Section 1.5.1.3, pp. 13-14.
 
 Note: CV is measured at simulated prices and incomes. It shows: the maximum payment the consumer
 would be willing to make to avoid having the simulated change undone (i.e. the payment after which
 the consumer would have been just as well off as without the change).For positive (negative) welfare
 change, CV > 0 (< 0).

 Note: EV is measured at base prices and incomes. It shows: the minimum payment that the consumer
 would require for foregoing a change (i.e., if the consumer receives this payment, then he/she is as
 well off under base prices and income as he/she would have been if the change had taken place.) For
 positive (negative) welfare change, CV > 0 (< 0).

$offtext

*Indirect compensation
*   IC measure the consumption value needed at base prices to generate same welfare as under prices and income under SIM
 IC(H,SIMC)
    = ((x_EH(H,SIMC) - SUM(C, x_PQ(C,SIMC)*gammam(C,H)) - SUM(A, x_PA(A,SIMC)*gammah(A,H)))  / (PROD(C, x_PQ(C,SIMC)**betam(C,H)) * PROD(A, x_PA(A,SIMC)**betah(A,H))))
    * (PROD(C, PQ0(C)**betam(C,H)) * PROD(A, PA0(A)**betah(A,H))) +  SUM(C, PQ0(C)*gammam(C,H)) + SUM(A, PA0(A)*gammah(A,H));

*Equivalent variation
*  EV measures the income change that, at base prices, would be equivalent to the change simulated for SIM 
 EV(H,SIMC) = IC(H,SIMC) - EH0(H);
 EV('TOTAL',SIMC) = SUM(H, EV(H,SIMC));
*  Disaggregated EV results
 EVX(H,'BASE')       = EH0(H);
 EVX('TOTAL','BASE') = SUM(H, EH0(H));
 EVX(H,SIMNB)$EH0(H) = EV(H,SIMNB) / EH0(H) * 100;
 EVX('TOTAL',SIMNB)$SUM(H, EH0(H)) = SUM(H, EV(H,SIMNB)) / SUM(H, EH0(H)) * 100;

*Compensating variation 
*   "ALPHA"
 BETAAUX(H)       = PROD(C, betam(C,H)**betam(C,H))   * PROD(A, betah(A,H)**betah(A,H));
 PRICEIND(H,SIMC)  = PROD(C, x_PQ(C,SIMC)**betam(C,H)) * PROD(A, x_PA(A,SIMC)**betah(A,H));
 EXPSUB(H,SIMC)    = SUM(C, x_PQ(C,SIMC)*gammam(C,H))  + SUM(A, x_PA(A,SIMC)*gammah(A,H));
*   "V"
 INDUTIL(H,SIMC)   = BETAAUX(H) *(x_EH(H,SIMC) - EXPSUB(H,SIMC)) / PRICEIND(H,SIMC);
*   "e(p1,u0)"
 EXPV0(H,SIMC)     = (INDUTIL(H,'BASE')/BETAAUX(H)) * PRICEIND(H,SIMC) + EXPSUB(H,SIMC);
 CV(H,SIMC)        = x_EH(H,SIMC) - EXPV0(H,SIMC);
 CV('TOTAL',SIMC)  = SUM(H, CV(H,SIMC));
*   Alternative definition of CV requiring less precalculations.
 CV2(H,SIMC)       = (x_EH(H,SIMC) - EXPSUB(H,SIMC)) - (EH0(H) - EXPSUB(H,'BASE')) * PRICEIND(H,SIMC) / PRICEIND(H,'BASE');
 CV2('TOTAL',SIMC) = SUM(H, CV2(H,SIMC));

$ONTEXT
 Deriving CV2:
 CV2 =  EH - EXPV0
     =  EH - ((V0/BETA) * PIND + EXPSUB);
     =  EH - EXPSUB - (V0/BETA) * PIND ;
     =  EH - EXPSUB - (1/BETA)*PIND*V0 ;
     = (EH - EXPSUB) - (1/BETA)*PIND *BETA*( EH0 - EXPSUB0 ) / PIND0;
     = (EH - EXPSUB) - PIND *( EH0 - EXPSUB0 ) / PIND0;
     = (EH - EXPSUB) - (EH0 - EXPSUB0) * PIND/PIND0;
 In words: CV = [current supernumerary spending] MINUS [base supernumerary spending adjusted for changes in price index].
$OFFTEXT

display BETAAUX, betam, betah ;
*------------------------------------------------------------------
*2.5.11  Other reporting: Percentage deviations from base year
*------------------------------------------------------------------

PARAMETER
*Model parameters (parameters ending with X contain post-solution values)
 p_alphavf(F,A,SIM)             productivity shift for factor F in activity A
 p_alphava(A,SIM)               shift parameter for CES activity production function
 p_betah(A,H,SIM)               marginal share of household consumption on home commodity C from activity A
 p_betam(C,H,SIM)               marginal share of household consumption on marketed commodity C
 p_gammah(A,H,SIM)              per-capita subsistence consumption for household H on home commodity C for activity A
 p_gammam(C,H,SIM)              per-capita subsistence consumption of marketed commodity C for household H
 p_icd(C,CP,SIM)                trade input of C per unit of commodity CP produced & sold domestically
 p_ice(C,CP,SIM)                trade input of C per unit of commodity CP exported
 p_icm(C,CP,SIM)                trade input of C per unit of commodity CP imported
 p_pop(H,SIM)                   total population of workers and non-workers in household H
 p_pwe(C,SIM)                   world price of exports
 p_pwm(C,SIM)                   world price of imports
 p_qbarg(C,SIM)                 exogenous (unscaled) government demand
 p_qbarinv(C,SIM)               exogenous (unscaled) investment demand
 p_qdst(C,SIM)                  inventory investment by sector of origin
 p_shif(AC,ACP,SIM)             share of institution INS (incl. rest of world) in post-tax income of factor F
 p_shii(AC,ACP,SIM)             share of institution INS in post-tax post-savings income of institution INSP
 p_trnsf(F,INS,SIM)             transfers from factor F to institution INS (including rest of world)
 p_trnsi(INS,INS,SIM)           transfers from institution INS) to institution INSP (including rest of world)
*Model variables (parameters ending with XP contain percentage deviations from base year values)
 p_CPI(SIM)                     consumer price index (PQ-based)
 p_DMPS(SIM)                    change in marginal propensity to save for selected institution
 p_DPI(SIM)                     index for domestic producer prices (PDS-based)
 p_DTA(SIM)                     additive activity tax (TA) adjustment
 p_DTE(SIM)                     additive export tax (TE) adjustment
 p_DTF(SIM)                     additive direct factor tax (TF) adjustment
 p_DTI(SIM)                     additive domestic institution tax (TINS) adjustment
 p_DTM(SIM)                     additive import tariff (TM) adjustment
 p_DTQ(SIM)                     additive sales tax (TQ) adjustment
 p_DTV(SIM)                     additive value-added tax (TVA) adjustment
 p_EG(SIM)                      total current government expenditure
 p_EH(H,SIM)                    household consumption expenditure
 p_EXR(SIM)                     exchange rate
 p_FSAV(SIM)                    foreign savings
 p_GADJ(SIM)                    government demand scaling factor
 p_GOVSHR(SIM)                  government consumption share of absorption
 p_GSAV(SIM)                    government savings
 p_IADJ(SIM)                    investment scaling factor (for fixed capital formation)
 p_INVSHR(SIM)                  investment share of absorption
 p_MPS(AC,SIM)                  marginal propensity to save for domestic non-government institution INS
 p_MPSADJ(SIM)                  savings rate (MPS) scaling factor
 p_PA(A,SIM)                    output price of activity A
 p_PDD(C,SIM)                   demand price for commodity C produced and sold domestically
 p_PDS(C,SIM)                   supply price for commodity C produced and sold domestically
 p_PE(C,SIM)                    price of export aggregate to producer excluding transport costs
 p_PM(C,SIM)                    price of import aggregate to demander including transport costs
 p_PINTA(A,SIM)                 price of intermediate aggregate
 p_PQ(C,SIM)                    price of composite commodity C
 p_PSAV(SIM)                    total private savings
 p_PVA(A,SIM)                   value added price
 p_PX(C,SIM)                    average output price
 p_PXAC(A,C,SIM)                price of commodity C from activity A
 p_QA(A,SIM)                    level of domestic activity
 p_QD(C,SIM)                    quantity of domestic sales
 p_QE(C,SIM)                    quantity of exports
 p_QF(F,A,SIM)                  quantity demanded of factor F from activity A
 p_QFS(F,SIM)                   quantity of factor supply
 p_QG(C,SIM)                    quantity of government consumption
 p_QH(C,H,SIM)                  quantity consumed of marketed commodity C by household H
 p_QHA(A,H,SIM)                 quantity consumed of home activity A by household H
 p_QINT(C,A,SIM)                quantity of intermediate demand for commodity C from activity A
 p_QINTA(A,SIM)                 quantity of aggregate intermediate input
 p_QINV(C,SIM)                  quantity of fixed investment demand
 p_QM(C,SIM)                    quantity of imports
 p_QQ(C,SIM)                    quantity of composite goods supply
 p_QT(C,SIM)                    quantity of trade and transport demand for commodity C
 p_QVA(A,SIM)                   quantity of aggregate value added
 p_QX(C,SIM)                    quantity of aggregate marketed commodity output
 p_QXAC(A,C,SIM)                quantity of ouput of commodity C from activity A
 p_TA(A,SIM)                    activity tax rates
 p_TAADJ(SIM)                   activity tax (TA) scaling factor
 p_TABS(SIM)                    total absorption
 p_TE(C,SIM)                    export tax rates
 p_TEADJ(SIM)                   export tax (TE) scaling factor
 p_TF(F,SIM)                    direct factor tax rates
 p_TFADJ(SIM)                   direct factor tax (TF) scaling factor
 p_TI(AC,SIM)                   direct tax rates on domestic institutions INSD
 p_TIADJ(SIM)                   direct tax (TINS) scaling factor
 p_TM(C,SIM)                    import tariff rates
 p_TMADJ(SIM)                   import tariff (TM) scaling factor
 p_TRII(AC,ACP,SIM)             transfers from column institutions INSF to row institutions INS
 p_TQ(C,SIM)                    composite commodity taxes
 p_TQADJ(SIM)                   composite commodity tax (TQ) scaling factor
 p_TV(A,SIM)                    value-added tax rate
 p_TVADJ(SIM)                   value-added tax (TVA) scaling factor
 p_WF(F,SIM)                    economywide wage (rent) for factor F
 p_WFDIST(F,A,SIM)              wage distortion variable for factor F in activity A
 p_YF(F,SIM)                    factor income from activities
 p_YG(SIM)                      total government income
 p_YI(INS,SIM)                  income of domestic non-government institution INS
 p_YIF(INS,F,SIM)               income of institution INS from factor F
;

*Percentage deviations
*  Parameters
 p_alphavf(F,A,SIMC)$x_alphaf(F,A,'BASE')       = (x_alphaf(F,A,SIMC) / x_alphaf(F,A,'BASE') - 1) * 100;          
 p_alphava(A,SIMC)$x_alphava(A,'BASE')          = (x_alphava(A,SIMC) / x_alphava(A,'BASE') - 1) * 100;      
 p_betah(A,H,SIMC)$x_betah(A,H,'BASE')          = (x_betah(A,H,SIMC) / x_betah(A,H,'BASE') - 1) * 100;      
 p_betam(C,H,SIMC)$x_betam(C,H,'BASE')          = (x_betam(C,H,SIMC) / x_betam(C,H,'BASE') - 1) * 100;      
 p_gammah(A,H,SIMC)$x_gammah(A,H,'BASE')        = (x_gammah(A,H,SIMC)/ x_gammah(A,H,'BASE') - 1) * 100;      
 p_gammam(C,H,SIMC)$x_gammam(C,H,'BASE')        = (x_gammam(C,H,SIMC)/ x_gammam(C,H,'BASE') - 1) * 100;      
 p_icd(C,CP,SIMC)$x_icd(C,CP,'BASE')            = (x_icd(C,CP,SIMC) / x_icd(C,CP,'BASE') - 1) * 100;      
 p_ice(C,CP,SIMC)$x_ice(C,CP,'BASE')            = (x_ice(C,CP,SIMC) / x_ice(C,CP,'BASE') - 1) * 100;      
 p_icm(C,CP,SIMC)$x_icm(C,CP,'BASE')            = (x_icm(C,CP,SIMC) / x_icm(C,CP,'BASE') - 1) * 100;      
 p_pop(H,SIMC)$x_pop(H,'BASE')                  = (x_pop(H,SIMC) / x_pop(H,'BASE') - 1) * 100;      
 p_pwe(C,SIMC)$x_pwe(C,'BASE')                  = (x_pwe(C,SIMC) / x_pwe(C,'BASE') - 1) * 100;      
 p_pwm(C,SIMC)$x_pwm(C,'BASE')                  = (x_pwm(C,SIMC) / x_pwm(C,'BASE') - 1) * 100;      
 p_qbarg(C,SIMC)$x_qbarg(C,'BASE')              = (x_qbarg(C,SIMC) / x_qbarg(C,'BASE') - 1) * 100;      
 p_qbarinv(C,SIMC)$x_qbarinv(C,'BASE')          = (x_qbarinv(C,SIMC) / x_qbarinv(C,'BASE') - 1) * 100;      
 p_qdst(C,SIMC)$x_qdst(C,'BASE')                = (x_qdst(C,SIMC) / x_qdst(C,'BASE') - 1) * 100;      
 p_shif(AC,ACP,SIMC)$x_shif(AC,ACP,'BASE')      = (x_shif(AC,ACP,SIMC) / x_shif(AC,ACP,'BASE') - 1) * 100;      
 p_shii(AC,ACP,SIMC)$x_shii(AC,ACP,'BASE')      = (x_shii(AC,ACP,SIMC) / x_shii(AC,ACP,'BASE') - 1) * 100;      
 p_trnsf(F,INS,SIMC)$x_trnsf(F,INS,'BASE')      = (x_trnsf(F,INS,SIMC) / x_trnsf(F,INS,'BASE') - 1) * 100;      
 p_trnsi(INS,INS,SIMC)$x_trnsi(INS,INS,'BASE')  = (x_trnsi(INS,INS,SIMC) / x_trnsi(INS,INS,'BASE') - 1) * 100;
*  Variables
 p_CPI(SIMC)$x_CPI('BASE')                      = (x_CPI(SIMC) / x_CPI('BASE') - 1) * 100;     
 p_DMPS(SIMC)$x_DMPS('BASE')                    = (x_DMPS(SIMC) / x_DMPS('BASE') - 1) * 100;     
 p_DPI(SIMC)$x_DPI('BASE')                      = (x_DPI(SIMC) / x_DPI('BASE') - 1) * 100;     
 p_DTA(SIMC)$x_DTA('BASE')                      = (x_DTA(SIMC) / x_DTA('BASE') - 1) * 100;     
 p_DTE(SIMC)$x_DTE('BASE')                      = (x_DTE(SIMC) / x_DTE('BASE') - 1) * 100;     
 p_DTF(SIMC)$x_DTF('BASE')                      = (x_DTF(SIMC) / x_DTF('BASE') - 1) * 100;     
 p_DTI(SIMC)$x_DTI('BASE')                      = (x_DTI(SIMC) / x_DTI('BASE') - 1) * 100;     
 p_DTM(SIMC)$x_DTM('BASE')                      = (x_DTM(SIMC) / x_DTM('BASE') - 1) * 100;     
 p_DTQ(SIMC)$x_DTQ('BASE')                      = (x_DTQ(SIMC) / x_DTQ('BASE') - 1) * 100;     
 p_DTV(SIMC)$x_DTV('BASE')                      = (x_DTV(SIMC) / x_DTV('BASE') - 1) * 100;     
 p_EG(SIMC)$x_EG('BASE')                        = (x_EG(SIMC) / x_EG('BASE') - 1) * 100;     
 p_EH(H,SIMC)$x_EH(H,'BASE')                    = (x_EH(H,SIMC) / x_EH(H,'BASE') - 1) * 100;     
 p_EXR(SIMC)$x_EXR('BASE')                      = (x_EXR(SIMC) / x_EXR('BASE') - 1) * 100;     
 p_FSAV(SIMC)$x_FSAV('BASE')                    = (x_FSAV(SIMC) / x_FSAV('BASE') - 1) * 100;     
 p_GADJ(SIMC)$x_GADJ('BASE')                    = (x_GADJ(SIMC) / x_GADJ('BASE') - 1) * 100;     
 p_GOVSHR(SIMC)$x_GOVSHR('BASE')                = (x_GOVSHR(SIMC) / x_GOVSHR('BASE') - 1) * 100;     
 p_GSAV(SIMC)$x_GSAV('BASE')                    = (x_GSAV(SIMC) / x_GSAV('BASE') - 1) * 100;     
 p_IADJ(SIMC)$x_IADJ('BASE')                    = (x_IADJ(SIMC) / x_IADJ('BASE') - 1) * 100;     
 p_INVSHR(SIMC)$x_INVSHR('BASE')                = (x_INVSHR(SIMC) / x_INVSHR('BASE') - 1) * 100;     
 p_MPS(AC,SIMC)$x_MPS(AC,'BASE')                = (x_MPS(AC,SIMC) / x_MPS(AC,'BASE') - 1) * 100;     
 p_MPSADJ(SIMC)$x_MPSADJ('BASE')                = (x_MPSADJ(SIMC) / x_MPSADJ('BASE') - 1) * 100;     
 p_PA(A,SIMC)$x_PA(A,'BASE')                    = (x_PA(A,SIMC) / x_PA(A,'BASE') - 1) * 100;     
 p_PDD(C,SIMC)$x_PDD(C,'BASE')                  = (x_PDD(C,SIMC) / x_PDD(C,'BASE') - 1) * 100;     
 p_PDS(C,SIMC)$x_PDS(C,'BASE')                  = (x_PDS(C,SIMC) / x_PDS(C,'BASE') - 1) * 100;     
 p_PE(C,SIMC)$x_PE(C,'BASE')                    = (x_PE(C,SIMC) / x_PE(C,'BASE') - 1) * 100;     
 p_PM(C,SIMC)$x_PM(C,'BASE')                    = (x_PM(C,SIMC) / x_PM(C,'BASE') - 1) * 100;     
 p_PINTA(A,SIMC)$x_PINTA(A,'BASE')              = (x_PINTA(A,SIMC) / x_PINTA(A,'BASE') - 1) * 100;     
 p_PQ(C,SIMC)$x_PQ(C,'BASE')                    = (x_PQ(C,SIMC) / x_PQ(C,'BASE') - 1) * 100;     
 p_PSAV(SIMC)$x_PSAV('BASE')                    = (x_PSAV(SIMC) / x_PSAV('BASE') - 1) * 100;     
 p_PVA(A,SIMC)$x_PVA(A,'BASE')                  = (x_PVA(A,SIMC) / x_PVA(A,'BASE') - 1) * 100;     
 p_PX(C,SIMC)$x_PX(C,'BASE')                    = (x_PX(C,SIMC) / x_PX(C,'BASE') - 1) * 100;     
 p_PXAC(A,C,SIMC)$x_PXAC(A,C,'BASE')            = (x_PXAC(A,C,SIMC) / x_PXAC(A,C,'BASE') - 1) * 100;     
 p_QA(A,SIMC)$x_QA(A,'BASE')                    = (x_QA(A,SIMC) / x_QA(A,'BASE') - 1) * 100;     
 p_QD(C,SIMC)$x_QD(C,'BASE')                    = (x_QD(C,SIMC) / x_QD(C,'BASE') - 1) * 100;     
 p_QE(C,SIMC)$x_QE(C,'BASE')                    = (x_QE(C,SIMC) / x_QE(C,'BASE') - 1) * 100;     
 p_QF(F,A,SIMC)$x_QF(F,A,'BASE')                = (x_QF(F,A,SIMC) / x_QF(F,A,'BASE') - 1) * 100;     
 p_QFS(F,SIMC)$x_QFS(F,'BASE')                  = (x_QFS(F,SIMC) / x_QFS(F,'BASE') - 1) * 100;     
 p_QG(C,SIMC)$x_QG(C,'BASE')                    = (x_QG(C,SIMC) / x_QG(C,'BASE') - 1) * 100;     
 p_QH(C,H,SIMC)$x_QH(C,H,'BASE')                = (x_QH(C,H,SIMC) / x_QH(C,H,'BASE') - 1) * 100;     
 p_QHA(A,H,SIMC)$x_QHA(A,H,'BASE')              = (x_QHA(A,H,SIMC) / x_QHA(A,H,'BASE') - 1) * 100;     
 p_QINT(C,A,SIMC)$x_QINT(C,A,'BASE')            = (x_QINT(C,A,SIMC) / x_QINT(C,A,'BASE') - 1) * 100;     
 p_QINTA(A,SIMC)$x_QINTA(A,'BASE')              = (x_QINTA(A,SIMC) / x_QINTA(A,'BASE') - 1) * 100;     
 p_QINV(C,SIMC)$x_QINV(C,'BASE')                = (x_QINV(C,SIMC) / x_QINV(C,'BASE') - 1) * 100;     
 p_QM(C,SIMC)$x_QM(C,'BASE')                    = (x_QM(C,SIMC) / x_QM(C,'BASE') - 1) * 100;     
 p_QQ(C,SIMC)$x_QQ(C,'BASE')                    = (x_QQ(C,SIMC) / x_QQ(C,'BASE') - 1) * 100;     
 p_QT(C,SIMC)$x_QT(C,'BASE')                    = (x_QT(C,SIMC) / x_QT(C,'BASE') - 1) * 100;     
 p_QVA(A,SIMC)$x_QVA(A,'BASE')                  = (x_QVA(A,SIMC) / x_QVA(A,'BASE') - 1) * 100;     
 p_QX(C,SIMC)$x_QX(C,'BASE')                    = (x_QX(C,SIMC) / x_QX(C,'BASE') - 1) * 100;     
 p_QXAC(A,C,SIMC)$x_QXAC(A,C,'BASE')            = (x_QXAC(A,C,SIMC) / x_QXAC(A,C,'BASE') - 1) * 100;     
 p_TA(A,SIMC)$x_TA(A,'BASE')                    = (x_TA(A,SIMC) / x_TA(A,'BASE') - 1) * 100;     
 p_TAADJ(SIMC)$x_TAADJ('BASE')                  = (x_TAADJ(SIMC) / x_TAADJ('BASE') - 1) * 100;     
 p_TABS(SIMC)$x_TABS('BASE')                    = (x_TABS(SIMC) / x_TABS('BASE') - 1) * 100;     
 p_TE(C,SIMC)$x_TE(C,'BASE')                    = (x_TE(C,SIMC) / x_TE(C,'BASE') - 1) * 100;     
 p_TEADJ(SIMC)$x_TEADJ('BASE')                  = (x_TEADJ(SIMC) / x_TEADJ('BASE') - 1) * 100;     
 p_TF(F,SIMC)$x_TF(F,'BASE')                    = (x_TF(F,SIMC) / x_TF(F,'BASE') - 1) * 100;     
 p_TFADJ(SIMC)$x_TFADJ('BASE')                  = (x_TFADJ(SIMC) / x_TFADJ('BASE') - 1) * 100;     
 p_TI(AC,SIMC)$x_TI(AC,'BASE')                  = (x_TI(AC,SIMC) / x_TI(AC,'BASE') - 1) * 100;     
 p_TIADJ(SIMC)$x_TIADJ('BASE')                  = (x_TIADJ(SIMC) / x_TIADJ('BASE') - 1) * 100;     
 p_TM(C,SIMC)$x_TM(C,'BASE')                    = (x_TM(C,SIMC) / x_TM(C,'BASE') - 1) * 100;     
 p_TMADJ(SIMC)$x_TMADJ('BASE')                  = (x_TMADJ(SIMC) / x_TMADJ('BASE') - 1) * 100;     
 p_TRII(AC,ACP,SIMC)$x_TRII(AC,ACP,'BASE')      = (x_TRII(AC,ACP,SIMC) / x_TRII(AC,ACP,'BASE') - 1) * 100;     
 p_TQ(C,SIMC)$x_TQ(C,'BASE')                    = (x_TQ(C,SIMC) / x_TQ(C,'BASE') - 1) * 100;     
 p_TQADJ(SIMC)$x_TQADJ('BASE')                  = (x_TQADJ(SIMC) / x_TQADJ('BASE') - 1) * 100;     
 p_TV(A,SIMC)$x_TV(A,'BASE')                    = (x_TV(A,SIMC) / x_TV(A,'BASE') - 1) * 100;     
 p_TVADJ(SIMC)$x_TVADJ('BASE')                  = (x_TVADJ(SIMC) / x_TVADJ('BASE') - 1) * 100;     
 p_WF(F,SIMC)$x_WF(F,'BASE')                    = (x_WF(F,SIMC) / x_WF(F,'BASE') - 1) * 100;     
 p_WFDIST(F,A,SIMC)$x_WFDIST(F,A,'BASE')        = (x_WFDIST(F,A,SIMC) / x_WFDIST(F,A,'BASE') - 1) * 100;     
 p_YF(F,SIMC)$x_YF(F,'BASE')                    = (x_YF(F,SIMC) / x_YF(F,'BASE') - 1) * 100;     
 p_YG(SIMC)$x_YG('BASE')                        = (x_YG(SIMC) / x_YG('BASE') - 1) * 100;     
 p_YI(INS,SIMC)$x_YI(INS,'BASE')                = (x_YI(INS,SIMC) / x_YI(INS,'BASE') - 1) * 100;     
 p_YIF(INS,F,SIMC)$x_YIF(INS,F,'BASE')          = (x_YIF(INS,F,SIMC) / x_YIF(INS,F,'BASE') - 1) * 100;     

*Store base year values
*  Parameters
 p_alphavf(F,A,'BASE')    = alphaf0(F,A);     
 p_alphava(A,'BASE')      = alphava0(A);               
 p_betah(A,H,'BASE')      = betah0(A,H);               
 p_betam(C,H,'BASE')      = betam0(C,H);               
 p_gammah(A,H,'BASE')     = gammah0(A,H);              
 p_gammam(C,H,'BASE')     = gammam0(C,H);              
 p_icd(C,CP,'BASE')       = icd0(C,CP);                
 p_ice(C,CP,'BASE')       = ice0(C,CP);                
 p_icm(C,CP,'BASE')       = icm0(C,CP);                
 p_pop(H,'BASE')          = pop0(H);                   
 p_pwe(C,'BASE')          = pwe0(C);                   
 p_pwm(C,'BASE')          = pwm0(C);                   
 p_qbarg(C,'BASE')        = qbarg0(C);                 
 p_qbarinv(C,'BASE')      = qbarinv0(C);               
 p_qdst(C,'BASE')         = qdst0(C);                  
 p_shif(AC,ACP,'BASE')    = shif0(AC,ACP);             
 p_shii(AC,ACP,'BASE')    = shii0(AC,ACP);             
 p_trnsf(F,INS,'BASE')    = trnsf0(F,INS);    
 p_trnsi(INS,INSP,'BASE') = trnsi0(INS,INSP);
*  Variables
 p_CPI('BASE')            = CPI0;
 p_DMPS('BASE')           = DMPS0;
 p_DPI('BASE')            = DPI0;
 p_DTA('BASE')            = DTA0;
 p_DTE('BASE')            = DTE0;
 p_DTF('BASE')            = DTF0;
 p_DTI('BASE')            = DTI0;
 p_DTM('BASE')            = DTM0;
 p_DTQ('BASE')            = DTQ0;
 p_DTV('BASE')            = DTV0;
 p_EG('BASE')             = EG0;
 p_EH(H,'BASE')           = EH0(H);
 p_EXR('BASE')            = EXR0;
 p_FSAV('BASE')           = FSAV0;
 p_GADJ('BASE')           = GADJ0;
 p_GOVSHR('BASE')         = GOVSHR0;
 p_GSAV('BASE')           = GSAV0;
 p_IADJ('BASE')           = IADJ0;
 p_INVSHR('BASE')         = INVSHR0;
 p_MPS(AC,'BASE')         = MPS0(AC);
 p_MPSADJ('BASE')         = MPSADJ0;
 p_PA(A,'BASE')           = PA0(A);
 p_PDD(C,'BASE')          = PDD0(C);
 p_PDS(C,'BASE')          = PDS0(C);
 p_PE(C,'BASE')           = PE0(C);
 p_PM(C,'BASE')           = PM0(C);
 p_PINTA(A,'BASE')        = PINTA0(A);
 p_PQ(C,'BASE')           = PQ0(C);
 p_PSAV('BASE')           = PSAV0;
 p_PVA(A,'BASE')          = PVA0(A);
 p_PX(C,'BASE')           = PX0(C);
 p_PXAC(A,C,'BASE')       = PXAC0(A,C);
 p_QA(A,'BASE')           = QA0(A);
 p_QD(C,'BASE')           = QD0(C);
 p_QE(C,'BASE')           = QE0(C);
 p_QF(F,A,'BASE')         = QF0(F,A);
 p_QFS(F,'BASE')          = QFS0(F);
 p_QG(C,'BASE')           = QG0(C);
 p_QH(C,H,'BASE')         = QH0(C,H);
 p_QHA(A,H,'BASE')        = QHA0(A,H);
 p_QINT(C,A,'BASE')       = QINT0(C,A);
 p_QINTA(A,'BASE')        = QINTA0(A);
 p_QINV(C,'BASE')         = QINV0(C);
 p_QM(C,'BASE')           = QM0(C);
 p_QQ(C,'BASE')           = QQ0(C);
 p_QT(C,'BASE')           = QT0(C);
 p_QVA(A,'BASE')          = QVA0(A);
 p_QX(C,'BASE')           = QX0(C);
 p_QXAC(A,C,'BASE')       = QXAC0(A,C);
 p_TA(A,'BASE')           = TA0(A);
 p_TAADJ('BASE')          = TAADJ0;
 p_TABS('BASE')           = TABS0;
 p_TE(C,'BASE')           = TE0(C);
 p_TEADJ('BASE')          = TEADJ0;
 p_TF(F,'BASE')           = TF0(F);
 p_TFADJ('BASE')          = TFADJ0;
 p_TI(AC,'BASE')          = TI0(AC);
 p_TIADJ('BASE')          = TIADJ0;
 p_TM(C,'BASE')           = TM0(C);
 p_TMADJ('BASE')          = TMADJ0;
 p_TRII(AC,ACP,'BASE')    = TRII0(AC,ACP);
 p_TQ(C,'BASE')           = TQ0(C);
 p_TQADJ('BASE')          = TQADJ0;
 p_TV(A,'BASE')           = TV0(A);
 p_TVADJ('BASE')          = TVADJ0;
 p_WF(F,'BASE')           = WF0(F);
 p_WFDIST(F,A,'BASE')     = WFDIST0(F,A);
 p_YF(F,'BASE')           = YF0(F);
 p_YG('BASE')             = YG0;
 p_YI(INS,'BASE')         = YI0(INS);
 p_YIF(INS,F,'BASE')      = YIF0(INS,F);