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
 MAPRA(RA,A)                model activities to reporting activities
 MAPRC(RA,C)                model commodities to reporting activities
 MAPRF(RF,F)                model factors to reporting factors
 MAPRH(RH,H)                model households to reporting households
*Price index weights        
 pdwt(C)                    weight of commodity C in PD index
 pwewt(C)                   weight of commodity C in pwe index
 pwmwt(C)                   weight of commodity C in pwm index
 pwwt(*)                    weight of aggregate exports-imports in pw (tradables) index
*Reporting parameters (exported to Excel)     
 r_STRUCBASE(RA,STRCOL)     base year economic structure
 r_TAXBASE(RA,TAXAC)        base year activity and commodity taxes
 r_MACROTAB(SIND,SIM)       macroeconomic results (average annual percentage changes or point deviations in shares)
 r_GDPFCp(RA,SIM)           GDP at factor cost (average annual percentage changes)
 r_GDPFCs(RA,SIM)           GDP at factor cost (average annual point deviations in shares of total)
 r_GDPMPs(NRAC,RD,SIM)      GDP at market prices (point deviation in share of total)
 r_GDPMPp(NRAC,RD,SIM)      GDP at market prices (average annual point deviations in shares of total)
 r_QETAB(RA,SIM)            exports (average annual percentage changes)
 r_QMTAB(RA,SIM)            imports (average annual percentage changes)
 r_PXTAB(RA,SIM)            output supply prices (average annual percentage changes) 
 r_PQTAB(RA,SIM)            final composite demand prices (average annual percentage changes) 
 r_PETAB(RA,SIM)            export prices (average annual percentage changes) 
 r_PMTAB(RA,SIM)            import prices (average annual percentage changes) 
 r_PWETAB(RA,SIM)           world export prices (average annual percentage changes) 
 r_PWMTAB(RA,SIM)           world import prices (average annual percentage changes)  
 r_QFSTAB(RF,SIM)           total factor supply (average annual percentage changes)       
 r_WFTAB(RF,SIM)            economywide factor wage or rent (average annual percentage changes)    
 r_YFTAB(RF,SIM)            total factor income (average annual percentage changes)   
 r_YITAB(RH,SIM)            total household income (average annual percentage changes)
 r_QHHTAB(RH,SIM)           total consumption by household (average annual percentage changes)
 r_QHCTAB(RA,SIM)           total consumption by commodity (average annual percentage changes)
 r_TITAB(RH,SIM)            household direct tax rates (average annual point deviation in tax rate)
 r_MPSTAB(RH,SIM)           household savings rates (average annual point deviation in savings rate)
*Annual values (used to generate reporting parameters)
 x_MACROTAB(SIND,SIM,T)     macroeconomic results
 x_GDPFC(RA,SIM,T)          GDP at factor cost (value)
 x_GDPMP(NRAC,RD,SIM,T)     GDP at market prices (value) 
 x_QETAB(RA,SIM,T)          exports (value)
 x_QMTAB(RA,SIM,T)          imports (value)
 x_PXTAB(RA,SIM,T)          output supply prices (value) 
 x_PQTAB(RA,SIM,T)          final composite demand prices (value) 
 x_PETAB(RA,SIM,T)          export prices (value) 
 x_PMTAB(RA,SIM,T)          import prices (value) 
 x_PWETAB(RA,SIM,T)         world export prices (value) 
 x_PWMTAB(RA,SIM,T)         world import prices (value)
 x_QFSTAB(RF,SIM,T)         total factor supply (value)       
 x_WFTAB(RF,SIM,T)          economywide factor wage or rent (value)    
 x_YFTAB(RF,SIM,T)          total factor income (value)   
 x_YITAB(RH,SIM,T)          total household income (value)
 x_QHHTAB(RH,SIM,T)         total consumption by household (value)
 x_QHCTAB(RA,SIM,T)         total consumption by commodity (value)
 x_TITAB(RH,SIM,T)          household direct tax rates (value)
 x_MPSTAB(RH,SIM,T)         household savings rates (value) 
*Average annual growth rates (used to generate reporting parameters)
 p_GDPFC(RA,SIM)            GDP at factor cost (average annual percentage changes)
 p_GDPMP(NRAC,RD,SIM)       GDP at market prices (average annual percentage changes)
 p_QETAB(RA,SIM)            exports (average annual percentage changes)
 p_QMTAB(RA,SIM)            imports (average annual percentage changes)
 p_PXTAB(RA,SIM)            output supply prices (average annual percentage changes) 
 p_PQTAB(RA,SIM)            final composite demand prices (average annual percentage changes) 
 p_PETAB(RA,SIM)            export prices (average annual percentage changes) 
 p_PMTAB(RA,SIM)            import prices (average annual percentage changes) 
 p_PWETAB(RA,SIM)           world export prices (average annual percentage changes) 
 p_PWMTAB(RA,SIM)           world import prices (average annual percentage changes) 
 p_QFSTAB(RF,SIM)           total factor supply (average annual percentage changes)       
 p_WFTAB(RF,SIM)            economywide factor wage or rent (average annual percentage changes)    
 p_YFTAB(RF,SIM)            total factor income (average annual percentage changes)   
 p_YITAB(RH,SIM)            total household income (average annual percentage changes)
 p_QHHTAB(RH,SIM)           total consumption by household (average annual percentage changes)
 p_QHCTAB(RA,SIM)           total consumption by commodity (average annual percentage changes)
 p_TITAB(RH,SIM)            household direct tax rates (average annual point deviation in tax rate)
 p_MPSTAB(RH,SIM)           household savings rates (average annual point deviation in savings rate)
;

*Read input data from excel file
$call 'GDXXRW i=data\\%folder%\dynrep%dataext%.xlsx o=reps.gdx index=index!a5'
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
 x_MACROTAB('QINVTOT',SIMC,TC) = SUM(C, PQ0(C)*x_QINV(C,SIMC,TC) + PQ0(C)*x_qdst(C,SIMC,TC));
 x_MACROTAB('QGTOT',SIMC,TC)   = SUM(C, PQ0(C)*x_QG(C,SIMC,TC));
 x_MACROTAB('QHTOT',SIMC,TC)   = SUM((C,H), PQ0(C)*x_QH(C,H,SIMC,TC)) + SUM((A,H), PA0(A)*x_QHA(A,H,SIMC,TC)) ;
 x_MACROTAB('QETOT',SIMC,TC)   = SUM(C, pwe0(C)*x_QE(C,SIMC,TC)*EXR0);  
 x_MACROTAB('QMTOT',SIMC,TC)   = SUM(C, pwm0(C)*x_QM(C,SIMC,TC)*EXR0);  
 x_MACROTAB('QABSTOT',SIMC,TC) = x_MACROTAB('QINVTOT',SIMC,TC) + x_MACROTAB('QGTOT',SIMC,TC) + x_MACROTAB('QHTOT',SIMC,TC);

*Exchange rates and price indices
 x_MACROTAB('CPI',SIMC,TC)     = x_CPI(SIMC,TC)/CPI0 * 100;
 x_MACROTAB('NEXR',SIMC,TC)    = x_EXR(SIMC,TC) * 100;
 x_MACROTAB('PDIND',SIMC,TC)   = SUM(C, pdwt(C)*x_PDS(C,SIMC,TC)) * 100;
 x_MACROTAB('PWEIND',SIMC,TC)  = SUM(C, x_pwe(C,SIMC,TC)*pwewt(C)) / SUM(C, pwe0(C)*pwewt(C)) * 100;
 x_MACROTAB('PWMIND',SIMC,TC)  = SUM(C, x_pwm(C,SIMC,TC)*pwmwt(C)) / SUM(C, pwm0(C)*pwmwt(C)) * 100;
 x_MACROTAB('TOFT',SIMC,TC)    = x_MACROTAB('PWEIND',SIMC,TC) / x_MACROTAB('PWMIND',SIMC,TC) * 100;
 x_MACROTAB('PWIND',SIMC,TC)   = pwwt('EXP')*x_MACROTAB('PWEIND',SIMC,TC) + pwwt('IMP')*x_MACROTAB('PWMIND',SIMC,TC);
 x_MACROTAB('REXR',SIMC,TC)    = x_MACROTAB('NEXR',SIMC,TC)*x_MACROTAB('PWIND',SIMC,TC) / x_MACROTAB('PDIND',SIMC,TC);
 
*Nominal GDP shares
 x_MACROTAB('INVGDP',SIMC,TC)    = (SUM(C, x_PQ(C,SIMC,TC)*x_QINV(C,SIMC,TC)) + SUM(C, x_PQ(C,SIMC,TC)*x_qdst(C,SIMC,TC))) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100; 
 x_MACROTAB('PRVSAVGDP',SIMC,TC) = SUM(INSDNG, x_SAMBUD('INSDNG',INSDNG,'SPND','S-I',SIMC,TC)) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('FORSAVGDP',SIMC,TC) = x_EXR(SIMC,TC)*x_FSAV(SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('TRDDEFGDP',SIMC,TC) = (SUM(C, x_PM(C,SIMC,TC)*x_QM(C,SIMC,TC)) - SUM(C, x_PE(C,SIMC,TC)*x_QE(C,SIMC,TC))) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('GOVSAVGDP',SIMC,TC) = x_SAMBUD('GOV','DUM','SPND','S-I',SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('TSAVGDP',SIMC,TC)   = x_MACROTAB('PRVSAVGDP',SIMC,TC) + x_MACROTAB('FORSAVGDP',SIMC,TC) + x_MACROTAB('GOVSAVGDP',SIMC,TC);
 x_MACROTAB('ACTTXGDP',SIMC,TC)  = x_SAMBUD('GOV','DUM','INC','ACTTAX',SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('VADTXGDP',SIMC,TC)  = x_SAMBUD('GOV','DUM','INC','VATTAX',SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('COMTXGDP',SIMC,TC)  = x_SAMBUD('GOV','DUM','INC','COMTAX',SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('EXPTXGDP',SIMC,TC)  = x_SAMBUD('GOV','DUM','INC','EXPTAX',SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('IMPTXGDP',SIMC,TC)  = x_SAMBUD('GOV','DUM','INC','IMPTAX',SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('FACTXGDP',SIMC,TC)  = x_SAMBUD('GOV','DUM','INC','FACTAX',SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('INSTXGDP',SIMC,TC)  = x_SAMBUD('GOV','DUM','INC','INSTAX',SIMC,TC) / x_GDPTAB1('NOMINAL','GDPMP',SIMC,TC) * 100;
 x_MACROTAB('INDTXGDP',SIMC,TC)  = x_MACROTAB('ACTTXGDP',SIMC,TC) + x_MACROTAB('VADTXGDP',SIMC,TC) + x_MACROTAB('COMTXGDP',SIMC,TC) + x_MACROTAB('EXPTXGDP',SIMC,TC) + x_MACROTAB('IMPTXGDP',SIMC,TC);
 x_MACROTAB('DIRTXGDP',SIMC,TC)  = x_MACROTAB('FACTXGDP',SIMC,TC) + x_MACROTAB('INSTXGDP',SIMC,TC);
 x_MACROTAB('TOTTXGDP',SIMC,TC)  = x_MACROTAB('INDTXGDP',SIMC,TC) + x_MACROTAB('DIRTXGDP',SIMC,TC);

*Excel export: Average annual percentage change
 r_MACROTAB(SINDP,SIMC)$SUM(T1, x_MACROTAB(SINDP,SIMC,T1)) = ((SUM(TN, x_MACROTAB(SINDP,SIMC,TN))/SUM(T1, x_MACROTAB(SINDP,SIMC,T1)))**(1/TNUM)-1)*100;
 r_MACROTAB(SINDP,'INIT') = SUM(T1, x_MACROTAB(SINDP,'BASE',T1));

*Excel export: Percentage-point deviation  
 r_MACROTAB(SINDDEV,SIMC)   = SUM(TN, x_MACROTAB(SINDDEV,SIMC,TN)) - SUM(T1, x_MACROTAB(SINDDEV,SIMC,T1));
 r_MACROTAB(SINDDEV,'INIT') = SUM(T1, x_MACROTAB(SINDDEV,'BASE',T1));

*Simulations report deviations from base
 r_MACROTAB(SIND,SIMNB) = r_MACROTAB(SIND,SIMNB) - r_MACROTAB(SIND,'BASE');

*------------------------------------------------------------------
*2.5.4  Gross domestic product
*------------------------------------------------------------------

*--- GDP at factor cost ---

*Real values
 x_GDPFC(RA,SIMC,TC) = SUM(A$MAPRA(RA,A), PVA0(A)*(1-TV0(A))*x_QVA(A,SIMC,TC));

*Average annual real growth rates
 p_GDPFC(RA,SIMC)$SUM(T1, x_GDPFC(RA,SIMC,T1)) = ((SUM(TN, x_GDPFC(RA,SIMC,TN))/SUM(T1, x_GDPFC(RA,SIMC,T1)))**(1/TNUM)-1)*100;
 
*Excel export: Average annual percentage change
 r_GDPFCp(RA,SIMC)   = p_GDPFC(RA,SIMC);
 r_GDPFCp(RA,'INIT') = SUM(T1, x_GDPFC(RA,'BASE',T1)) / SUM(A, PVA0(A)*(1-TV0(A))*QVA0(A)) * 100;
 r_GDPFCp(RA,SIMNB) = r_GDPFCp(RA,SIMNB) - r_GDPFCp(RA,'BASE');

*Excel export: Average annual percentage point deviation in shares from base year
 r_GDPFCs(RA,SIMC)   = (SUM(TN, x_GDPFC(RA,SIMC,TN) / SUM(A, PVA0(A)*(1-TV0(A))*x_QVA(A,SIMC,TN))) - SUM(T1, x_GDPFC(RA,SIMC,T1) / SUM(A, PVA0(A)*(1-TV0(A))*x_QVA(A,SIMC,T1)))) * 100; 
 r_GDPFCs(RA,'INIT') = SUM(T1, x_GDPFC(RA,'BASE',T1)) / SUM(A, PVA0(A)*(1-TV0(A))*QVA0(A)) * 100;
 r_GDPFCs(RA,SIMNB) = r_GDPFCs(RA,SIMNB) - r_GDPFCs(RA,'BASE');

*--- GDP at market prices ---

*Nominal values
 x_GDPMP('NOMINAL','r_PRVCON',SIMC,TC)  = SUM((C,H), x_PQ(C,SIMC,TC)*x_QH(C,H,SIMC,TC)) + SUM((A,H), x_PA(A,SIMC,TC)*x_QHA(A,H,SIMC,TC));
 x_GDPMP('NOMINAL','r_GOVCON',SIMC,TC)  = SUM(C, x_PQ(C,SIMC,TC)*x_QG(C,SIMC,TC)); 
 x_GDPMP('NOMINAL','r_GFCF',SIMC,TC)    = SUM(C, x_PQ(C,SIMC,TC)*x_QINV(C,SIMC,TC)); 
 x_GDPMP('NOMINAL','r_STK',SIMC,TC)     = SUM(C, x_PQ(C,SIMC,TC)*x_qdst(C,SIMC,TC)); 
 x_GDPMP('NOMINAL','r_GCF',SIMC,TC)     = x_GDPMP('NOMINAL','r_GFCF',SIMC,TC) + x_GDPMP('NOMINAL','r_STK',SIMC,TC); 
 x_GDPMP('NOMINAL','r_EXP',SIMC,TC)     = SUM(C, x_pwe(C,SIMC,TC)*x_QE(C,SIMC,TC)*x_EXR(SIMC,TC));
 x_GDPMP('NOMINAL','r_IMP',SIMC,TC)     = SUM(C, x_pwm(C,SIMC,TC)*x_QM(C,SIMC,TC)*x_EXR(SIMC,TC)); 
 x_GDPMP('NOMINAL','r_TRDBAL',SIMC,TC)  = x_GDPMP('NOMINAL','r_EXP',SIMC,TC) - x_GDPMP('NOMINAL','r_IMP',SIMC,TC);
 x_GDPMP('NOMINAL','r_ABSORP',SIMC,TC)  = x_GDPMP('NOMINAL','r_PRVCON',SIMC,TC) + x_GDPMP('NOMINAL','r_GOVCON',SIMC,TC) + x_GDPMP('NOMINAL','r_GCF',SIMC,TC);
 x_GDPMP('NOMINAL','r_GDPMP',SIMC,TC)   = x_GDPMP('NOMINAL','r_ABSORP',SIMC,TC) + x_GDPMP('NOMINAL','r_TRDBAL',SIMC,TC);
 x_GDPMP('NOMINAL','r_GDPFC',SIMC,TC)   = SUM(A, x_PVA(A,SIMC,TC)*(1-x_TV(A,SIMC,TC))*x_QVA(A,SIMC,TC)); 
 x_GDPMP('NOMINAL','r_NETITAX',SIMC,TC) = x_GDPMP('NOMINAL','r_GDPMP',SIMC,TC) - x_GDPMP('NOMINAL','r_GDPFC',SIMC,TC);
*Real values
 x_GDPMP('REAL','r_PRVCON',SIMC,TC)     = SUM((C,H), PQ0(C)*x_QH(C,H,SIMC,TC)) + SUM((A,H), PA0(A)*x_QHA(A,H,SIMC,TC));
 x_GDPMP('REAL','r_GOVCON',SIMC,TC)     = SUM(C, PQ0(C)*x_QG(C,SIMC,TC)); 
 x_GDPMP('REAL','r_GFCF',SIMC,TC)       = SUM(C, PQ0(C)*x_QINV(C,SIMC,TC)); 
 x_GDPMP('REAL','r_STK',SIMC,TC)        = SUM(C, PQ0(C)*x_qdst(C,SIMC,TC)); 
 x_GDPMP('REAL','r_GCF',SIMC,TC)        = x_GDPMP('REAL','r_GFCF',SIMC,TC) + x_GDPMP('REAL','r_STK',SIMC,TC); 
 x_GDPMP('REAL','r_EXP',SIMC,TC)        = SUM(C, pwe0(C)*x_QE(C,SIMC,TC)*EXR0);
 x_GDPMP('REAL','r_IMP',SIMC,TC)        = SUM(C, pwm0(C)*x_QM(C,SIMC,TC)*EXR0); 
 x_GDPMP('REAL','r_TRDBAL',SIMC,TC)     = x_GDPMP('REAL','r_EXP',SIMC,TC) - x_GDPMP('REAL','r_IMP',SIMC,TC);
 x_GDPMP('REAL','r_ABSORP',SIMC,TC)     = x_GDPMP('REAL','r_PRVCON',SIMC,TC) + x_GDPMP('REAL','r_GOVCON',SIMC,TC) + x_GDPMP('REAL','r_GCF',SIMC,TC);
 x_GDPMP('REAL','r_GDPMP',SIMC,TC)      = x_GDPMP('REAL','r_ABSORP',SIMC,TC) + x_GDPMP('REAL','r_TRDBAL',SIMC,TC);
 x_GDPMP('REAL','r_GDPFC',SIMC,TC)      = SUM(A, PVA0(A)*(1-TV0(A))*x_QVA(A,SIMC,TC)); 
 x_GDPMP('REAL','r_NETITAX',SIMC,TC)    = x_GDPMP('REAL','r_GDPMP',SIMC,TC) - x_GDPMP('REAL','r_GDPFC',SIMC,TC);
       
*Average annual real growth rates
 p_GDPMP(NRAC,RD,SIMC)$SUM(T1, x_GDPMP(NRAC,RD,SIMC,T1)) = ((SUM(TN, x_GDPMP(NRAC,RD,SIMC,TN))/SUM(T1, x_GDPMP(NRAC,RD,SIMC,T1)))**(1/TNUM)-1)*100;

*Excel export: Average annual real growth rates
 r_GDPMPp(NRAC,RD,SIMC)   = p_GDPMP(NRAC,RD,SIMC);
 r_GDPMPp(NRAC,RD,'INIT') = SUM(T1, x_GDPMP(NRAC,RD,'BASE',T1) / x_GDPMP(NRAC,'r_GDPMP','BASE',T1)) * 100;
 r_GDPMPp(NRAC,RD,SIMNB) = r_GDPMPp(NRAC,RD,SIMNB) - r_GDPMPp(NRAC,RD,'BASE');
 
*Excel export: Average annual percentage point deviation in shares from base year
 r_GDPMPs(NRAC,RD,SIMC)   = (SUM(TN, x_GDPMP(NRAC,RD,SIMC,TN) / x_GDPMP(NRAC,'r_GDPMP',SIMC,TN)) - SUM(T1, x_GDPMP(NRAC,RD,SIMC,T1) / x_GDPMP(NRAC,'r_GDPMP',SIMC,T1)))*100;
 r_GDPMPs(NRAC,RD,'INIT') = SUM(T1, x_GDPMP(NRAC,RD,'BASE',T1) / x_GDPMP(NRAC,'r_GDPMP','BASE',T1)) * 100;
 r_GDPMPs(NRAC,RD,SIMNB) = r_GDPMPs(NRAC,RD,SIMNB) - r_GDPMPs(NRAC,RD,'BASE');
 

*------------------------------------------------------------------
*2.5.5  International trade
*------------------------------------------------------------------

*Real values 
 x_QETAB(RA,SIMC,TC) = SUM(C$MAPRC(RA,C), pwe0(C)*x_QE(C,SIMC,TC)*EXR0);
 x_QMTAB(RA,SIMC,TC) = SUM(C$MAPRC(RA,C), pwm0(C)*x_QM(C,SIMC,TC)*EXR0);
 
*Average annual real growth rates
 p_QETAB(RA,SIMC)$SUM(T1, x_QETAB(RA,SIMC,T1)) = ((SUM(TN, x_QETAB(RA,SIMC,TN))/SUM(T1, x_QETAB(RA,SIMC,T1)))**(1/TNUM)-1)*100;
 p_QMTAB(RA,SIMC)$SUM(T1, x_QMTAB(RA,SIMC,T1)) = ((SUM(TN, x_QMTAB(RA,SIMC,TN))/SUM(T1, x_QMTAB(RA,SIMC,T1)))**(1/TNUM)-1)*100;

*Excel export: Average annual real growth rates
 r_QETAB(RA,SIMC) = p_QETAB(RA,SIMC);
 r_QMTAB(RA,SIMC) = p_QMTAB(RA,SIMC);
 r_QETAB(RA,'INIT')$SUM(C, pwe0(C)*QE0(C)*EXR0) = SUM(T1, x_QETAB(RA,'BASE',T1)) / SUM(C, pwe0(C)*QE0(C)*EXR0) * 100;
 r_QMTAB(RA,'INIT')$SUM(C, pwm0(C)*QM0(C)*EXR0) = SUM(T1, x_QMTAB(RA,'BASE',T1)) / SUM(C, pwm0(C)*QM0(C)*EXR0) * 100;
 r_QETAB(RA,SIMNB) = r_QETAB(RA,SIMNB) - r_QETAB(RA,'BASE');
 r_QMTAB(RA,SIMNB) = r_QMTAB(RA,SIMNB) - r_QMTAB(RA,'BASE');


*------------------------------------------------------------------
*2.5.6  Prices
*------------------------------------------------------------------

*Weighted values
 x_PXTAB(RA,SIMC,TC)$SUM(C$MAPRC(RA,C), QX0(C))  = SUM(C$MAPRC(RA,C), x_PX(C,SIMC,TC)  * PX0(C)*QX0(C)  / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PX0(CP)*QX0(CP)));          
 x_PQTAB(RA,SIMC,TC)$SUM(C$MAPRC(RA,C), QQ0(C))  = SUM(C$MAPRC(RA,C), x_PQ(C,SIMC,TC)  * PQ0(C)*QQ0(C)  / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PQ0(CP)*QQ0(CP))); 
 x_PETAB(RA,SIMC,TC)$SUM(C$MAPRC(RA,C), QE0(C))  = SUM(C$MAPRC(RA,C), x_PE(C,SIMC,TC)  * PE0(C)*QE0(C)  / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PE0(CP)*QE0(CP))); 
 x_PMTAB(RA,SIMC,TC)$SUM(C$MAPRC(RA,C), QM0(C))  = SUM(C$MAPRC(RA,C), x_PM(C,SIMC,TC)  * PM0(C)*QM0(C)  / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), PM0(CP)*QM0(CP))); 
 x_PWETAB(RA,SIMC,TC)$SUM(C$MAPRC(RA,C), QE0(C)) = SUM(C$MAPRC(RA,C), x_pwe(C,SIMC,TC) * pwe0(C)*QE0(C) / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), pwe0(CP)*QE0(CP)));
 x_PWMTAB(RA,SIMC,TC)$SUM(C$MAPRC(RA,C), QM0(C)) = SUM(C$MAPRC(RA,C), x_pwm(C,SIMC,TC) * pwm0(C)*QM0(C) / SUM(CP$(MAPRC(RA,C) AND MAPRC(RA,CP)), pwm0(CP)*QM0(CP)));

*Average annual real growth rates
 p_PXTAB(RA,SIMC)$SUM(T1, x_PXTAB(RA,SIMC,T1))   = ((SUM(TN, x_PXTAB(RA,SIMC,TN)) /SUM(T1, x_PXTAB(RA,SIMC,T1)) )**(1/TNUM)-1)*100;
 p_PQTAB(RA,SIMC)$SUM(T1, x_PQTAB(RA,SIMC,T1))   = ((SUM(TN, x_PQTAB(RA,SIMC,TN)) /SUM(T1, x_PQTAB(RA,SIMC,T1)) )**(1/TNUM)-1)*100; 
 p_PETAB(RA,SIMC)$SUM(T1, x_PETAB(RA,SIMC,T1))   = ((SUM(TN, x_PETAB(RA,SIMC,TN)) /SUM(T1, x_PETAB(RA,SIMC,T1)) )**(1/TNUM)-1)*100;
 p_PMTAB(RA,SIMC)$SUM(T1, x_PMTAB(RA,SIMC,T1))   = ((SUM(TN, x_PMTAB(RA,SIMC,TN)) /SUM(T1, x_PMTAB(RA,SIMC,T1)) )**(1/TNUM)-1)*100;
 p_PWETAB(RA,SIMC)$SUM(T1, x_PWETAB(RA,SIMC,T1)) = ((SUM(TN, x_PWETAB(RA,SIMC,TN))/SUM(T1, x_PWETAB(RA,SIMC,T1)))**(1/TNUM)-1)*100;
 p_PWMTAB(RA,SIMC)$SUM(T1, x_PWMTAB(RA,SIMC,T1)) = ((SUM(TN, x_PWMTAB(RA,SIMC,TN))/SUM(T1, x_PWMTAB(RA,SIMC,T1)))**(1/TNUM)-1)*100;
  
*Excel export: Average annual real growth rates
 r_PXTAB(RA,SIMC)  = p_PXTAB(RA,SIMC);
 r_PQTAB(RA,SIMC)  = p_PQTAB(RA,SIMC);
 r_PETAB(RA,SIMC)  = p_PETAB(RA,SIMC);
 r_PMTAB(RA,SIMC)  = p_PMTAB(RA,SIMC);
 r_PWETAB(RA,SIMC) = p_PWETAB(RA,SIMC);
 r_PWMTAB(RA,SIMC) = p_PWMTAB(RA,SIMC);
 r_PXTAB(RA,'INIT')$SUM(C, PX0(C)*QX0(C))   = SUM(T1, x_PXTAB(RA,'BASE',T1));      
 r_PQTAB(RA,'INIT')$SUM(C, PQ0(C)*QQ0(C))   = SUM(T1, x_PQTAB(RA,'BASE',T1));      
 r_PETAB(RA,'INIT')$SUM(C, PE0(C)*QE0(C))   = SUM(T1, x_PETAB(RA,'BASE',T1));      
 r_PMTAB(RA,'INIT')$SUM(C, PM0(C)*QM0(C))   = SUM(T1, x_PMTAB(RA,'BASE',T1));       
 r_PWETAB(RA,'INIT')$SUM(C, pwe0(C)*QE0(C)) = SUM(T1, x_PWETAB(RA,'BASE',T1));     
 r_PWMTAB(RA,'INIT')$SUM(C, pwm0(C)*QM0(C)) = SUM(T1, x_PWMTAB(RA,'BASE',T1));     
 r_PXTAB(RA,SIMNB)  = r_PXTAB(RA,SIMNB)  - r_PXTAB(RA,'BASE');
 r_PQTAB(RA,SIMNB)  = r_PQTAB(RA,SIMNB)  - r_PQTAB(RA,'BASE');
 r_PETAB(RA,SIMNB)  = r_PETAB(RA,SIMNB)  - r_PETAB(RA,'BASE');
 r_PMTAB(RA,SIMNB)  = r_PMTAB(RA,SIMNB)  - r_PMTAB(RA,'BASE');
 r_PWETAB(RA,SIMNB) = r_PWETAB(RA,SIMNB) - r_PWETAB(RA,'BASE');
 r_PWMTAB(RA,SIMNB) = r_PWMTAB(RA,SIMNB) - r_PWMTAB(RA,'BASE');
 

*------------------------------------------------------------------
*2.5.7  Factors 
*------------------------------------------------------------------ 

*Total factor supply
*  Values       
 x_QFSTAB(RF,SIMC,TC) = SUM(F$MAPRF(RF,F), x_QFS(F,SIMC,TC));
*  Average annual real growth rates
 p_QFSTAB(RF,SIMC)$SUM(T1, x_QFSTAB(RF,SIMC,T1)) = ((SUM(TN, x_QFSTAB(RF,SIMC,TN))/SUM(T1, x_QFSTAB(RF,SIMC,T1)))**(1/TNUM)-1)*100;
*Excel export: Average annual real growth rates
 r_QFSTAB(RF,SIMC)   = p_QFSTAB(RF,SIMC);
 r_QFSTAB(RF,'INIT') = SUM(T1, x_QFSTAB(RF,'BASE',T1));
 r_QFSTAB(RF,SIMNB) = r_QFSTAB(RF,SIMNB) - r_QFSTAB(RF,'BASE'); 
 
*Economywide factor wage or rent
*  Values       
 x_WFTAB(RF,SIMC,TC)$SUM((F,A)$MAPRF(RF,F), x_QF(F,A,SIMC,TC)) = SUM((F,A)$MAPRF(RF,F), x_WF(F,SIMC,TC)*x_WFDIST(F,A,SIMC,TC)*x_QF(F,A,SIMC,TC)) / SUM((F,A)$MAPRF(RF,F), x_QF(F,A,SIMC,TC));
*  Average annual real growth rates
 p_WFTAB(RF,SIMC)$SUM(T1, x_WFTAB(RF,SIMC,T1)) = ((SUM(TN, x_WFTAB(RF,SIMC,TN))/SUM(T1, x_WFTAB(RF,SIMC,T1)))**(1/TNUM)-1)*100;
*Excel export: Average annual real growth rates
 r_WFTAB(RF,SIMC)   = p_WFTAB(RF,SIMC);
 r_WFTAB(RF,'INIT') = SUM(T1, x_WFTAB(RF,'BASE',T1));
 r_WFTAB(RF,SIMNB) = r_WFTAB(RF,SIMNB) - r_WFTAB(RF,'BASE');

*Total factor income
*  Values       
 x_YFTAB(RF,SIMC,TC) = SUM(F$MAPRF(RF,F), x_YF(F,SIMC,TC));
*  Average annual real growth rates
 p_YFTAB(RF,SIMC)$SUM(T1, x_YFTAB(RF,SIMC,T1)) = ((SUM(TN, x_YFTAB(RF,SIMC,TN))/SUM(T1, x_YFTAB(RF,SIMC,T1)))**(1/TNUM)-1)*100;
*Excel export: Average annual real growth rates
 r_YFTAB(RF,SIMC)   = p_YFTAB(RF,SIMC);
 r_YFTAB(RF,'INIT') = SUM(T1, x_YFTAB(RF,'BASE',T1));
 r_YFTAB(RF,SIMNB) = r_YFTAB(RF,SIMNB) - r_YFTAB(RF,'BASE');
 

*------------------------------------------------------------------
*2.5.8  Households
*------------------------------------------------------------------

*Total household income (percentage deviation)
*  Values    
 x_YITAB(RH,SIMC,TC) = SUM(H$MAPRH(RH,H), x_YI(H,SIMC,TC));
*  Average annual real growth rates
 p_YITAB(RH,SIMC)$SUM(T1, x_YITAB(RH,SIMC,T1)) = ((SUM(TN, x_YITAB(RH,SIMC,TN))/SUM(T1, x_YITAB(RH,SIMC,T1)))**(1/TNUM)-1) * 100; 
*Excel export: Average annual real growth rates
 r_YITAB(RH,SIMC)   = p_YITAB(RH,SIMC); 
 r_YITAB(RH,'INIT')$SUM(H, YI0(H)) = SUM(H$MAPRH(RH,H), YI0(H)) / SUM(H, YI0(H)) * 100;
 r_YITAB(RH,SIMNB) = r_YITAB(RH,SIMNB) - r_YITAB(RH,'BASE'); 

*Total consumption by household
*  Values    
 x_QHHTAB(RH,SIMC,TC) = SUM((C,H)$MAPRH(RH,H), PQ0(C)*x_QH(C,H,SIMC,TC)) + SUM((A,H)$MAPRH(RH,H), PA0(A)*x_QHA(A,H,SIMC,TC));
*  Average annual real growth rates
 p_QHHTAB(RH,SIMC)$SUM(T1, x_QHHTAB(RH,SIMC,T1)) = ((SUM(TN, x_QHHTAB(RH,SIMC,TN))/SUM(T1, x_QHHTAB(RH,SIMC,T1)))**(1/TNUM)-1) * 100; 
*Excel export: Average annual real growth rates
 r_QHHTAB(RH,SIMC)   = p_QHHTAB(RH,SIMC); 
 r_QHHTAB(RH,'INIT')$(SUM((C,H), PQ0(C)*QH0(C,H)) + SUM((A,H), PA0(A)*QHA0(A,H)))
    = (SUM((C,H)$MAPRH(RH,H), PQ0(C)*QH0(C,H)) + SUM((A,H)$MAPRH(RH,H), PA0(A)*QHA0(A,H))) / (SUM((C,H), PQ0(C)*QH0(C,H)) + SUM((A,H), PA0(A)*QHA0(A,H))) * 100; 
 r_QHHTAB(RH,SIMNB) = r_QHHTAB(RH,SIMNB) - r_QHHTAB(RH,'BASE');

*Total consumption by commodity
*  Values    
 x_QHCTAB(RA,SIMC,TC) = SUM((C,H)$MAPRC(RA,C), PQ0(C)*x_QH(C,H,SIMC,TC)) + SUM((A,H)$MAPRA(RA,A), PA0(A)*x_QHA(A,H,SIMC,TC));
*  Average annual real growth rates
 p_QHCTAB(RA,SIMC)$SUM(T1, x_QHCTAB(RA,SIMC,T1)) = ((SUM(TN, x_QHCTAB(RA,SIMC,TN))/SUM(T1, x_QHCTAB(RA,SIMC,T1)))**(1/TNUM)-1)*100; 
*Excel export: Average annual real growth rates
 r_QHCTAB(RA,SIMC)   = p_QHCTAB(RA,SIMC); 
 r_QHCTAB(RA,'INIT')$(SUM((C,H), PQ0(C)*QH0(C,H)) + SUM((A,H), PA0(A)*QHA0(A,H)))
    = (SUM((C,H)$MAPRC(RA,C), PQ0(C)*QH0(C,H)) + SUM((A,H)$MAPRA(RA,A), PA0(A)*QHA0(A,H))) / (SUM((C,H), PQ0(C)*QH0(C,H)) + SUM((A,H), PA0(A)*QHA0(A,H))) * 100; 
 r_QHCTAB(RA,SIMNB) = r_QHCTAB(RA,SIMNB) - r_QHCTAB(RA,'BASE');

*Household direct tax rates
*  Values    
 x_TITAB(RH,SIMC,TC)$SUM(H$MAPRH(RH,H), YI0(H)) = SUM(H$MAPRH(RH,H), x_TI(H,SIMC,TC)*YI0(H)) / SUM(H$MAPRH(RH,H), YI0(H)) * 100;
*  Average annual real growth rates
 p_TITAB(RH,SIMC)    = (SUM(TN, x_TITAB(RH,SIMC,TN)) - SUM(T1, x_TITAB(RH,SIMC,T1)))/TNUM;
*Excel export: Average annual real growth rates
 r_TITAB(RH,SIMC)   = p_TITAB(RH,SIMC); 
 r_TITAB(RH,'INIT') = SUM(T1, x_TITAB(RH,'BASE',T1)); 
 r_TITAB(RH,SIMNB) = r_TITAB(RH,SIMNB) - r_TITAB(RH,'BASE');

*Household savings rates
*  Values    
 x_MPSTAB(RH,SIMC,TC)$SUM(H$MAPRH(RH,H), YI0(H)) = SUM(H$MAPRH(RH,H), x_MPS(H,SIMC,TC)*YI0(H)) / SUM(H$MAPRH(RH,H), YI0(H)) * 100;
*  Average annual real growth rates
 p_MPSTAB(RH,SIMC)    = (SUM(TN, x_MPSTAB(RH,SIMC,TN)) - SUM(T1, x_MPSTAB(RH,SIMC,T1)))/TNUM;
*Excel export: Average annual real growth rates
 r_MPSTAB(RH,SIMC)   = p_MPSTAB(RH,SIMC); 
 r_MPSTAB(RH,'INIT') = SUM(T1, x_MPSTAB(RH,'BASE',T1)); 
 r_MPSTAB(RH,SIMNB) = r_MPSTAB(RH,SIMNB) - r_MPSTAB(RH,'BASE');
 
 
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
 r_QETAB(RA,SIM)        $(NOT r_QETAB(RA,SIM)       ) = eps;
 r_QMTAB(RA,SIM)        $(NOT r_QMTAB(RA,SIM)       ) = eps;
 r_PXTAB(RA,SIM)        $(NOT r_PXTAB(RA,SIM)       ) = eps;
 r_PQTAB(RA,SIM)        $(NOT r_PQTAB(RA,SIM)       ) = eps;
 r_PETAB(RA,SIM)        $(NOT r_PETAB(RA,SIM)       ) = eps;
 r_PMTAB(RA,SIM)        $(NOT r_PMTAB(RA,SIM)       ) = eps;
 r_PWETAB(RA,SIM)       $(NOT r_PWETAB(RA,SIM)      ) = eps;
 r_PWMTAB(RA,SIM)       $(NOT r_PWMTAB(RA,SIM)      ) = eps;
 r_QFSTAB(RF,SIM)       $(NOT r_QFSTAB(RF,SIM)      ) = eps;
 r_WFTAB(RF,SIM)        $(NOT r_WFTAB(RF,SIM)       ) = eps;  
 r_YFTAB(RF,SIM)        $(NOT r_YFTAB(RF,SIM)       ) = eps;
 r_YITAB(RH,SIM)        $(NOT r_YITAB(RH,SIM)       ) = eps;
 r_QHHTAB(RH,SIM)       $(NOT r_QHHTAB(RH,SIM)      ) = eps;
 r_QHCTAB(RA,SIM)       $(NOT r_QHCTAB(RA,SIM)      ) = eps;
 r_TITAB(RH,SIM)        $(NOT r_TITAB(RH,SIM)       ) = eps;
 r_MPSTAB(RH,SIM)       $(NOT r_MPSTAB(RH,SIM)      ) = eps;


*Export to Excel
PARAMETER XLTEST;
*execute_unload "report.gdx"  
execute_unload "report.gdx" r_YITAB r_QHHTAB r_QHCTAB r_TITAB r_MPSTAB r_PXTAB r_PQTAB r_PETAB r_PMTAB r_PWETAB r_PWMTAB r_QETAB r_QMTAB r_YFTAB r_WFTAB r_QFSTAB r_GDPFCp r_GDPFCs r_GDPMPp r_GDPMPs r_MACROTAB r_STRUCBASE r_TAXBASE 
execute 'xlstalk.exe -m data\\%folder%\dynrep%dataext%.xlsx'; 
 XLTEST = ERRORLEVEL;
IF(XLTEST = 1,
execute 'xlstalk.exe -c data\\%folder%\dynrep%dataext%.xlsx';
);
IF(XLTEST = 2,
execute 'xlstalk.exe -s data\\%folder%\dynrep%dataext%.xlsx';
);
execute 'gdxxrw.exe i=report.gdx o=data\\%folder%\dynrep%dataext%.xlsx index=index!a20' ;
execute 'xlstalk.exe -o data\\%folder%\dynrep%dataext%.xlsx';
DISPLAY XLTEST;


*------------------------------------------------------------------
*2.5.10  EV and CV welfare measures
*------------------------------------------------------------------

PARAMETER
 IC(H,SIM,TC)               indirect compensation function by household H and simulation SIM
 EV(AC,SIM,TC)              equivalent variation by household AC and simulation SIM
 BETAAUX(H)                 auxiliary term based on marginal spending shares
 PRICEIND(H,SIM,TC)         price index
 EXPSUB(H,SIM,TC)           subsistence spending for household H under simulation SIM
 INDUTIL(H,SIM,TC)          indirect utility for household H under simulation SIM
 EXPV0(H,SIM,TC)            base-utility expenditure function for household H under simulation SIM
 CV(AC,SIM,TC)              compensating variation for household H under simulation SIM
 CV2(AC,SIM,TC)             concise formula for CV
 EVX(AC,SIM,TC)             disaggregated EV results
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
 IC(H,SIMC,TC)
    = ((x_EH(H,SIMC,TC) - SUM(C, x_PQ(C,SIMC,TC)*gammam(C,H)) - SUM(A, x_PA(A,SIMC,TC)*gammah(A,H)))  / (PROD(C, x_PQ(C,SIMC,TC)**betam(C,H)) * PROD(A, x_PA(A,SIMC,TC)**betah(A,H))))
    * (PROD(C, PQ0(C)**betam(C,H)) * PROD(A, PA0(A)**betah(A,H))) +  SUM(C, PQ0(C)*gammam(C,H)) + SUM(A, PA0(A)*gammah(A,H));

*Equivalent variation
*  EV measures the income change that, at base prices, would be equivalent to the change simulated for SIM 
 EV(H,SIMC,TC)       = IC(H,SIMC,TC) - EH0(H);
 EV('TOTAL',SIMC,TC) = SUM(H, EV(H,SIMC,TC));
*  Disaggregated EV results
 EVX(H,'BASE',TC)       = EH0(H);
 EVX('TOTAL','BASE',TC) = SUM(H, EH0(H));
 EVX(H,SIMNB,TC)$EH0(H) = EV(H,SIMNB,TC) / EH0(H) * 100;
 EVX('TOTAL',SIMNB,TC)$SUM(H, EH0(H)) = SUM(H, EV(H,SIMNB,TC)) / SUM(H, EH0(H)) * 100;

*Compensating variation 
*   "ALPHA"
 BETAAUX(H)           = PROD(C, betam(C,H)**betam(C,H))  * PROD(A, betah(A,H)**betah(A,H));
 PRICEIND(H,SIMC,TC)  = PROD(C, x_PQ(C,SIMC,TC)**betam(C,H)) * PROD(A, x_PA(A,SIMC,TC)**betah(A,H));
 EXPSUB(H,SIMC,TC)    = SUM(C, x_PQ(C,SIMC,TC)*gammam(C,H))  + SUM(A, x_PA(A,SIMC,TC)*gammah(A,H));
*   "V"
 INDUTIL(H,SIMC,TC)   = BETAAUX(H) *(x_EH(H,SIMC,TC) - EXPSUB(H,SIMC,TC)) / PRICEIND(H,SIMC,TC);
*   "e(p1,u0)"
 EXPV0(H,SIMC,TC)     = (INDUTIL(H,'BASE',TC)/BETAAUX(H)) * PRICEIND(H,SIMC,TC) + EXPSUB(H,SIMC,TC);
 CV(H,SIMC,TC)        = x_EH(H,SIMC,TC) - EXPV0(H,SIMC,TC);
 CV('TOTAL',SIMC,TC)  = SUM(H, CV(H,SIMC,TC));
*   Alternative definition of CV requiring less precalculations.
 CV2(H,SIMC,TC)       = (x_EH(H,SIMC,TC) - EXPSUB(H,SIMC,TC)) - (EH0(H) - EXPSUB(H,'BASE',TC)) * PRICEIND(H,SIMC,TC) / PRICEIND(H,'BASE',TC);
 CV2('TOTAL',SIMC,TC) = SUM(H, CV2(H,SIMC,TC));

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

*Calculate percentage deviations
*  Parameters
 p_alphavf(F,A,SIMC)   $SUM(T1, x_alphaf(F,A,SIMC,T1)   ) = ((SUM(TN, x_alphaf(F,A,SIMC,TN)   )/SUM(T1, x_alphaf(F,A,SIMC,T1)   ))**(1/TNUM)-1)*100; 
 p_alphava(A,SIMC)     $SUM(T1, x_alphava(A,SIMC,T1)    ) = ((SUM(TN, x_alphava(A,SIMC,TN)    )/SUM(T1, x_alphava(A,SIMC,T1)    ))**(1/TNUM)-1)*100; 
 p_betah(A,H,SIMC)     $SUM(T1, x_betah(A,H,SIMC,T1)    ) = ((SUM(TN, x_betah(A,H,SIMC,TN)    )/SUM(T1, x_betah(A,H,SIMC,T1)    ))**(1/TNUM)-1)*100; 
 p_betam(C,H,SIMC)     $SUM(T1, x_betam(C,H,SIMC,T1)    ) = ((SUM(TN, x_betam(C,H,SIMC,TN)    )/SUM(T1, x_betam(C,H,SIMC,T1)    ))**(1/TNUM)-1)*100; 
 p_gammah(A,H,SIMC)    $SUM(T1, x_gammah(A,H,SIMC,T1)   ) = ((SUM(TN, x_gammah(A,H,SIMC,TN)   )/SUM(T1, x_gammah(A,H,SIMC,T1)   ))**(1/TNUM)-1)*100; 
 p_gammam(C,H,SIMC)    $SUM(T1, x_gammam(C,H,SIMC,T1)   ) = ((SUM(TN, x_gammam(C,H,SIMC,TN)   )/SUM(T1, x_gammam(C,H,SIMC,T1)   ))**(1/TNUM)-1)*100; 
 p_icd(C,CP,SIMC)      $SUM(T1, x_icd(C,CP,SIMC,T1)     ) = ((SUM(TN, x_icd(C,CP,SIMC,TN)     )/SUM(T1, x_icd(C,CP,SIMC,T1)     ))**(1/TNUM)-1)*100; 
 p_ice(C,CP,SIMC)      $SUM(T1, x_ice(C,CP,SIMC,T1)     ) = ((SUM(TN, x_ice(C,CP,SIMC,TN)     )/SUM(T1, x_ice(C,CP,SIMC,T1)     ))**(1/TNUM)-1)*100; 
 p_icm(C,CP,SIMC)      $SUM(T1, x_icm(C,CP,SIMC,T1)     ) = ((SUM(TN, x_icm(C,CP,SIMC,TN)     )/SUM(T1, x_icm(C,CP,SIMC,T1)     ))**(1/TNUM)-1)*100; 
 p_pop(H,SIMC)         $SUM(T1, x_pop(H,SIMC,T1)        ) = ((SUM(TN, x_pop(H,SIMC,TN)        )/SUM(T1, x_pop(H,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_pwe(C,SIMC)         $SUM(T1, x_pwe(C,SIMC,T1)        ) = ((SUM(TN, x_pwe(C,SIMC,TN)        )/SUM(T1, x_pwe(C,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_pwm(C,SIMC)         $SUM(T1, x_pwm(C,SIMC,T1)        ) = ((SUM(TN, x_pwm(C,SIMC,TN)        )/SUM(T1, x_pwm(C,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_qbarg(C,SIMC)       $SUM(T1, x_qbarg(C,SIMC,T1)      ) = ((SUM(TN, x_qbarg(C,SIMC,TN)      )/SUM(T1, x_qbarg(C,SIMC,T1)      ))**(1/TNUM)-1)*100; 
 p_qbarinv(C,SIMC)     $SUM(T1, x_qbarinv(C,SIMC,T1)    ) = ((SUM(TN, x_qbarinv(C,SIMC,TN)    )/SUM(T1, x_qbarinv(C,SIMC,T1)    ))**(1/TNUM)-1)*100; 
 p_qdst(C,SIMC)        $SUM(T1, x_qdst(C,SIMC,T1)       ) = ((SUM(TN, x_qdst(C,SIMC,TN)       )/SUM(T1, x_qdst(C,SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_shif(AC,ACP,SIMC)   $SUM(T1, x_shif(AC,ACP,SIMC,T1)  ) = ((SUM(TN, x_shif(AC,ACP,SIMC,TN)  )/SUM(T1, x_shif(AC,ACP,SIMC,T1)  ))**(1/TNUM)-1)*100; 
 p_shii(AC,ACP,SIMC)   $SUM(T1, x_shii(AC,ACP,SIMC,T1)  ) = ((SUM(TN, x_shii(AC,ACP,SIMC,TN)  )/SUM(T1, x_shii(AC,ACP,SIMC,T1)  ))**(1/TNUM)-1)*100; 
 p_trnsf(F,INS,SIMC)   $SUM(T1, x_trnsf(F,INS,SIMC,T1)  ) = ((SUM(TN, x_trnsf(F,INS,SIMC,TN)  )/SUM(T1, x_trnsf(F,INS,SIMC,T1)  ))**(1/TNUM)-1)*100; 
 p_trnsi(INS,INS,SIMC) $SUM(T1, x_trnsi(INS,INS,SIMC,T1)) = ((SUM(TN, x_trnsi(INS,INS,SIMC,TN))/SUM(T1, x_trnsi(INS,INS,SIMC,T1)))**(1/TNUM)-1)*100;            
 p_CPI(SIMC)           $SUM(T1, x_CPI(SIMC,T1)          ) = ((SUM(TN, x_CPI(SIMC,TN)          )/SUM(T1, x_CPI(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_DMPS(SIMC)          $SUM(T1, x_DMPS(SIMC,T1)         ) = ((SUM(TN, x_DMPS(SIMC,TN)         )/SUM(T1, x_DMPS(SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_DPI(SIMC)           $SUM(T1, x_DPI(SIMC,T1)          ) = ((SUM(TN, x_DPI(SIMC,TN)          )/SUM(T1, x_DPI(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_DTA(SIMC)           $SUM(T1, x_DTA(SIMC,T1)          ) = ((SUM(TN, x_DTA(SIMC,TN)          )/SUM(T1, x_DTA(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_DTE(SIMC)           $SUM(T1, x_DTE(SIMC,T1)          ) = ((SUM(TN, x_DTE(SIMC,TN)          )/SUM(T1, x_DTE(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_DTF(SIMC)           $SUM(T1, x_DTF(SIMC,T1)          ) = ((SUM(TN, x_DTF(SIMC,TN)          )/SUM(T1, x_DTF(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_DTI(SIMC)           $SUM(T1, x_DTI(SIMC,T1)          ) = ((SUM(TN, x_DTI(SIMC,TN)          )/SUM(T1, x_DTI(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_DTM(SIMC)           $SUM(T1, x_DTM(SIMC,T1)          ) = ((SUM(TN, x_DTM(SIMC,TN)          )/SUM(T1, x_DTM(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_DTQ(SIMC)           $SUM(T1, x_DTQ(SIMC,T1)          ) = ((SUM(TN, x_DTQ(SIMC,TN)          )/SUM(T1, x_DTQ(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_DTV(SIMC)           $SUM(T1, x_DTV(SIMC,T1)          ) = ((SUM(TN, x_DTV(SIMC,TN)          )/SUM(T1, x_DTV(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_EG(SIMC)            $SUM(T1, x_EG(SIMC,T1)           ) = ((SUM(TN, x_EG(SIMC,TN)           )/SUM(T1, x_EG(SIMC,T1)           ))**(1/TNUM)-1)*100; 
 p_EH(H,SIMC)          $SUM(T1, x_EH(H,SIMC,T1)         ) = ((SUM(TN, x_EH(H,SIMC,TN)         )/SUM(T1, x_EH(H,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_EXR(SIMC)           $SUM(T1, x_EXR(SIMC,T1)          ) = ((SUM(TN, x_EXR(SIMC,TN)          )/SUM(T1, x_EXR(SIMC,T1)          ))**(1/TNUM)-1)*100; 
 p_FSAV(SIMC)          $SUM(T1, x_FSAV(SIMC,T1)         ) = ((SUM(TN, x_FSAV(SIMC,TN)         )/SUM(T1, x_FSAV(SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_GADJ(SIMC)          $SUM(T1, x_GADJ(SIMC,T1)         ) = ((SUM(TN, x_GADJ(SIMC,TN)         )/SUM(T1, x_GADJ(SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_GOVSHR(SIMC)        $SUM(T1, x_GOVSHR(SIMC,T1)       ) = ((SUM(TN, x_GOVSHR(SIMC,TN)       )/SUM(T1, x_GOVSHR(SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_GSAV(SIMC)          $SUM(T1, x_GSAV(SIMC,T1)         ) = ((SUM(TN, x_GSAV(SIMC,TN)         )/SUM(T1, x_GSAV(SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_IADJ(SIMC)          $SUM(T1, x_IADJ(SIMC,T1)         ) = ((SUM(TN, x_IADJ(SIMC,TN)         )/SUM(T1, x_IADJ(SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_INVSHR(SIMC)        $SUM(T1, x_INVSHR(SIMC,T1)       ) = ((SUM(TN, x_INVSHR(SIMC,TN)       )/SUM(T1, x_INVSHR(SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_MPS(AC,SIMC)        $SUM(T1, x_MPS(AC,SIMC,T1)       ) = ((SUM(TN, x_MPS(AC,SIMC,TN)       )/SUM(T1, x_MPS(AC,SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_MPSADJ(SIMC)        $SUM(T1, x_MPSADJ(SIMC,T1)       ) = ((SUM(TN, x_MPSADJ(SIMC,TN)       )/SUM(T1, x_MPSADJ(SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_PA(A,SIMC)          $SUM(T1, x_PA(A,SIMC,T1)         ) = ((SUM(TN, x_PA(A,SIMC,TN)         )/SUM(T1, x_PA(A,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_PDD(C,SIMC)         $SUM(T1, x_PDD(C,SIMC,T1)        ) = ((SUM(TN, x_PDD(C,SIMC,TN)        )/SUM(T1, x_PDD(C,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_PDS(C,SIMC)         $SUM(T1, x_PDS(C,SIMC,T1)        ) = ((SUM(TN, x_PDS(C,SIMC,TN)        )/SUM(T1, x_PDS(C,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_PE(C,SIMC)          $SUM(T1, x_PE(C,SIMC,T1)         ) = ((SUM(TN, x_PE(C,SIMC,TN)         )/SUM(T1, x_PE(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_PM(C,SIMC)          $SUM(T1, x_PM(C,SIMC,T1)         ) = ((SUM(TN, x_PM(C,SIMC,TN)         )/SUM(T1, x_PM(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_PINTA(A,SIMC)       $SUM(T1, x_PINTA(A,SIMC,T1)      ) = ((SUM(TN, x_PINTA(A,SIMC,TN)      )/SUM(T1, x_PINTA(A,SIMC,T1)      ))**(1/TNUM)-1)*100; 
 p_PQ(C,SIMC)          $SUM(T1, x_PQ(C,SIMC,T1)         ) = ((SUM(TN, x_PQ(C,SIMC,TN)         )/SUM(T1, x_PQ(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_PSAV(SIMC)          $SUM(T1, x_PSAV(SIMC,T1)         ) = ((SUM(TN, x_PSAV(SIMC,TN)         )/SUM(T1, x_PSAV(SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_PVA(A,SIMC)         $SUM(T1, x_PVA(A,SIMC,T1)        ) = ((SUM(TN, x_PVA(A,SIMC,TN)        )/SUM(T1, x_PVA(A,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_PX(C,SIMC)          $SUM(T1, x_PX(C,SIMC,T1)         ) = ((SUM(TN, x_PX(C,SIMC,TN)         )/SUM(T1, x_PX(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_PXAC(A,C,SIMC)      $SUM(T1, x_PXAC(A,C,SIMC,T1)     ) = ((SUM(TN, x_PXAC(A,C,SIMC,TN)     )/SUM(T1, x_PXAC(A,C,SIMC,T1)     ))**(1/TNUM)-1)*100; 
 p_QA(A,SIMC)          $SUM(T1, x_QA(A,SIMC,T1)         ) = ((SUM(TN, x_QA(A,SIMC,TN)         )/SUM(T1, x_QA(A,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_QD(C,SIMC)          $SUM(T1, x_QD(C,SIMC,T1)         ) = ((SUM(TN, x_QD(C,SIMC,TN)         )/SUM(T1, x_QD(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_QE(C,SIMC)          $SUM(T1, x_QE(C,SIMC,T1)         ) = ((SUM(TN, x_QE(C,SIMC,TN)         )/SUM(T1, x_QE(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_QF(F,A,SIMC)        $SUM(T1, x_QF(F,A,SIMC,T1)       ) = ((SUM(TN, x_QF(F,A,SIMC,TN)       )/SUM(T1, x_QF(F,A,SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_QFS(F,SIMC)         $SUM(T1, x_QFS(F,SIMC,T1)        ) = ((SUM(TN, x_QFS(F,SIMC,TN)        )/SUM(T1, x_QFS(F,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_QG(C,SIMC)          $SUM(T1, x_QG(C,SIMC,T1)         ) = ((SUM(TN, x_QG(C,SIMC,TN)         )/SUM(T1, x_QG(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_QH(C,H,SIMC)        $SUM(T1, x_QH(C,H,SIMC,T1)       ) = ((SUM(TN, x_QH(C,H,SIMC,TN)       )/SUM(T1, x_QH(C,H,SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_QHA(A,H,SIMC)       $SUM(T1, x_QHA(A,H,SIMC,T1)      ) = ((SUM(TN, x_QHA(A,H,SIMC,TN)      )/SUM(T1, x_QHA(A,H,SIMC,T1)      ))**(1/TNUM)-1)*100; 
 p_QINT(C,A,SIMC)      $SUM(T1, x_QINT(C,A,SIMC,T1)     ) = ((SUM(TN, x_QINT(C,A,SIMC,TN)     )/SUM(T1, x_QINT(C,A,SIMC,T1)     ))**(1/TNUM)-1)*100; 
 p_QINTA(A,SIMC)       $SUM(T1, x_QINTA(A,SIMC,T1)      ) = ((SUM(TN, x_QINTA(A,SIMC,TN)      )/SUM(T1, x_QINTA(A,SIMC,T1)      ))**(1/TNUM)-1)*100; 
 p_QINV(C,SIMC)        $SUM(T1, x_QINV(C,SIMC,T1)       ) = ((SUM(TN, x_QINV(C,SIMC,TN)       )/SUM(T1, x_QINV(C,SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_QM(C,SIMC)          $SUM(T1, x_QM(C,SIMC,T1)         ) = ((SUM(TN, x_QM(C,SIMC,TN)         )/SUM(T1, x_QM(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_QQ(C,SIMC)          $SUM(T1, x_QQ(C,SIMC,T1)         ) = ((SUM(TN, x_QQ(C,SIMC,TN)         )/SUM(T1, x_QQ(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_QT(C,SIMC)          $SUM(T1, x_QT(C,SIMC,T1)         ) = ((SUM(TN, x_QT(C,SIMC,TN)         )/SUM(T1, x_QT(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_QVA(A,SIMC)         $SUM(T1, x_QVA(A,SIMC,T1)        ) = ((SUM(TN, x_QVA(A,SIMC,TN)        )/SUM(T1, x_QVA(A,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_QX(C,SIMC)          $SUM(T1, x_QX(C,SIMC,T1)         ) = ((SUM(TN, x_QX(C,SIMC,TN)         )/SUM(T1, x_QX(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_QXAC(A,C,SIMC)      $SUM(T1, x_QXAC(A,C,SIMC,T1)     ) = ((SUM(TN, x_QXAC(A,C,SIMC,TN)     )/SUM(T1, x_QXAC(A,C,SIMC,T1)     ))**(1/TNUM)-1)*100; 
 p_TA(A,SIMC)          $SUM(T1, x_TA(A,SIMC,T1)         ) = ((SUM(TN, x_TA(A,SIMC,TN)         )/SUM(T1, x_TA(A,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_TAADJ(SIMC)         $SUM(T1, x_TAADJ(SIMC,T1)        ) = ((SUM(TN, x_TAADJ(SIMC,TN)        )/SUM(T1, x_TAADJ(SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_TABS(SIMC)          $SUM(T1, x_TABS(SIMC,T1)         ) = ((SUM(TN, x_TABS(SIMC,TN)         )/SUM(T1, x_TABS(SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_TE(C,SIMC)          $SUM(T1, x_TE(C,SIMC,T1)         ) = ((SUM(TN, x_TE(C,SIMC,TN)         )/SUM(T1, x_TE(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_TEADJ(SIMC)         $SUM(T1, x_TEADJ(SIMC,T1)        ) = ((SUM(TN, x_TEADJ(SIMC,TN)        )/SUM(T1, x_TEADJ(SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_TF(F,SIMC)          $SUM(T1, x_TF(F,SIMC,T1)         ) = ((SUM(TN, x_TF(F,SIMC,TN)         )/SUM(T1, x_TF(F,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_TFADJ(SIMC)         $SUM(T1, x_TFADJ(SIMC,T1)        ) = ((SUM(TN, x_TFADJ(SIMC,TN)        )/SUM(T1, x_TFADJ(SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_TI(AC,SIMC)         $SUM(T1, x_TI(AC,SIMC,T1)        ) = ((SUM(TN, x_TI(AC,SIMC,TN)        )/SUM(T1, x_TI(AC,SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_TIADJ(SIMC)         $SUM(T1, x_TIADJ(SIMC,T1)        ) = ((SUM(TN, x_TIADJ(SIMC,TN)        )/SUM(T1, x_TIADJ(SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_TM(C,SIMC)          $SUM(T1, x_TM(C,SIMC,T1)         ) = ((SUM(TN, x_TM(C,SIMC,TN)         )/SUM(T1, x_TM(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_TMADJ(SIMC)         $SUM(T1, x_TMADJ(SIMC,T1)        ) = ((SUM(TN, x_TMADJ(SIMC,TN)        )/SUM(T1, x_TMADJ(SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_TRII(AC,ACP,SIMC)   $SUM(T1, x_TRII(AC,ACP,SIMC,T1)  ) = ((SUM(TN, x_TRII(AC,ACP,SIMC,TN)  )/SUM(T1, x_TRII(AC,ACP,SIMC,T1)  ))**(1/TNUM)-1)*100; 
 p_TQ(C,SIMC)          $SUM(T1, x_TQ(C,SIMC,T1)         ) = ((SUM(TN, x_TQ(C,SIMC,TN)         )/SUM(T1, x_TQ(C,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_TQADJ(SIMC)         $SUM(T1, x_TQADJ(SIMC,T1)        ) = ((SUM(TN, x_TQADJ(SIMC,TN)        )/SUM(T1, x_TQADJ(SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_TV(A,SIMC)          $SUM(T1, x_TV(A,SIMC,T1)         ) = ((SUM(TN, x_TV(A,SIMC,TN)         )/SUM(T1, x_TV(A,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_TVADJ(SIMC)         $SUM(T1, x_TVADJ(SIMC,T1)        ) = ((SUM(TN, x_TVADJ(SIMC,TN)        )/SUM(T1, x_TVADJ(SIMC,T1)        ))**(1/TNUM)-1)*100; 
 p_WF(F,SIMC)          $SUM(T1, x_WF(F,SIMC,T1)         ) = ((SUM(TN, x_WF(F,SIMC,TN)         )/SUM(T1, x_WF(F,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_WFDIST(F,A,SIMC)    $SUM(T1, x_WFDIST(F,A,SIMC,T1)   ) = ((SUM(TN, x_WFDIST(F,A,SIMC,TN)   )/SUM(T1, x_WFDIST(F,A,SIMC,T1)   ))**(1/TNUM)-1)*100; 
 p_YF(F,SIMC)          $SUM(T1, x_YF(F,SIMC,T1)         ) = ((SUM(TN, x_YF(F,SIMC,TN)         )/SUM(T1, x_YF(F,SIMC,T1)         ))**(1/TNUM)-1)*100; 
 p_YG(SIMC)            $SUM(T1, x_YG(SIMC,T1)           ) = ((SUM(TN, x_YG(SIMC,TN)           )/SUM(T1, x_YG(SIMC,T1)           ))**(1/TNUM)-1)*100; 
 p_YI(INS,SIMC)        $SUM(T1, x_YI(INS,SIMC,T1)       ) = ((SUM(TN, x_YI(INS,SIMC,TN)       )/SUM(T1, x_YI(INS,SIMC,T1)       ))**(1/TNUM)-1)*100; 
 p_YIF(INS,F,SIMC)     $SUM(T1, x_YIF(INS,F,SIMC,T1)    ) = ((SUM(TN, x_YIF(INS,F,SIMC,TN)    )/SUM(T1, x_YIF(INS,F,SIMC,T1)    ))**(1/TNUM)-1)*100; 

*Store base year values

 p_alphavf(F,A,'INIT')    = alphaf0(F,A);
 p_alphava(A,'INIT')      = alphava0(A);
 p_betah(A,H,'INIT')      = betah0(A,H);
 p_betam(C,H,'INIT')      = betam0(C,H);
 p_gammah(A,H,'INIT')     = gammah0(A,H);
 p_gammam(C,H,'INIT')     = gammam0(C,H);
 p_icd(C,CP,'INIT')       = icd0(C,CP);
 p_ice(C,CP,'INIT')       = ice0(C,CP);
 p_icm(C,CP,'INIT')       = icm0(C,CP);
 p_pop(H,'INIT')          = pop0(H);
 p_pwe(C,'INIT')          = pwe0(C);
 p_pwm(C,'INIT')          = pwm0(C);
 p_qbarg(C,'INIT')        = qbarg0(C);
 p_qbarinv(C,'INIT')      = qbarinv0(C);
 p_qdst(C,'INIT')         = qdst0(C);
 p_shif(AC,ACP,'INIT')    = shif0(AC,ACP);
 p_shii(AC,ACP,'INIT')    = shii0(AC,ACP);
 p_trnsf(F,INS,'INIT')    = trnsf0(F,INS);
 p_trnsi(INS,INSP,'INIT') = trnsi0(INS,INSP);
 p_CPI('INIT')            = CPI0;
 p_DMPS('INIT')           = DMPS0;
 p_DPI('INIT')            = DPI0;
 p_DTA('INIT')            = DTA0;
 p_DTE('INIT')            = DTE0;
 p_DTF('INIT')            = DTF0;
 p_DTI('INIT')            = DTI0;
 p_DTM('INIT')            = DTM0;
 p_DTQ('INIT')            = DTQ0;
 p_DTV('INIT')            = DTV0;
 p_EG('INIT')             = EG0;
 p_EH(H,'INIT')           = EH0(H);
 p_EXR('INIT')            = EXR0;
 p_FSAV('INIT')           = FSAV0;
 p_GADJ('INIT')           = GADJ0;
 p_GOVSHR('INIT')         = GOVSHR0;
 p_GSAV('INIT')           = GSAV0;
 p_IADJ('INIT')           = IADJ0;
 p_INVSHR('INIT')         = INVSHR0;
 p_MPS(AC,'INIT')         = MPS0(AC);
 p_MPSADJ('INIT')         = MPSADJ0;
 p_PA(A,'INIT')           = PA0(A);
 p_PDD(C,'INIT')          = PDD0(C);
 p_PDS(C,'INIT')          = PDS0(C);
 p_PE(C,'INIT')           = PE0(C);
 p_PM(C,'INIT')           = PM0(C);
 p_PINTA(A,'INIT')        = PINTA0(A);
 p_PQ(C,'INIT')           = PQ0(C);
 p_PSAV('INIT')           = PSAV0;
 p_PVA(A,'INIT')          = PVA0(A);
 p_PX(C,'INIT')           = PX0(C);
 p_PXAC(A,C,'INIT')       = PXAC0(A,C);
 p_QA(A,'INIT')           = QA0(A);
 p_QD(C,'INIT')           = QD0(C);
 p_QE(C,'INIT')           = QE0(C);
 p_QF(F,A,'INIT')         = QF0(F,A);
 p_QFS(F,'INIT')          = QFS0(F);
 p_QG(C,'INIT')           = QG0(C);
 p_QH(C,H,'INIT')         = QH0(C,H);
 p_QHA(A,H,'INIT')        = QHA0(A,H);
 p_QINT(C,A,'INIT')       = QINT0(C,A);
 p_QINTA(A,'INIT')        = QINTA0(A);
 p_QINV(C,'INIT')         = QINV0(C);
 p_QM(C,'INIT')           = QM0(C);
 p_QQ(C,'INIT')           = QQ0(C);
 p_QT(C,'INIT')           = QT0(C);
 p_QVA(A,'INIT')          = QVA0(A);
 p_QX(C,'INIT')           = QX0(C);
 p_QXAC(A,C,'INIT')       = QXAC0(A,C);
 p_TA(A,'INIT')           = TA0(A);
 p_TAADJ('INIT')          = TAADJ0;
 p_TABS('INIT')           = TABS0;
 p_TE(C,'INIT')           = TE0(C);
 p_TEADJ('INIT')          = TEADJ0;
 p_TF(F,'INIT')           = TF0(F);
 p_TFADJ('INIT')          = TFADJ0;
 p_TI(AC,'INIT')          = TI0(AC);
 p_TIADJ('INIT')          = TIADJ0;
 p_TM(C,'INIT')           = TM0(C);
 p_TMADJ('INIT')          = TMADJ0;
 p_TRII(AC,ACP,'INIT')    = TRII0(AC,ACP);
 p_TQ(C,'INIT')           = TQ0(C);
 p_TQADJ('INIT')          = TQADJ0;
 p_TV(A,'INIT')           = TV0(A);
 p_TVADJ('INIT')          = TVADJ0;
 p_WF(F,'INIT')           = WF0(F);
 p_WFDIST(F,A,'INIT')     = WFDIST0(F,A);
 p_YF(F,'INIT')           = YF0(F);
 p_YG('INIT')             = YG0;
 p_YI(INS,'INIT')         = YI0(INS);
 p_YIF(INS,F,'INIT')      = YIF0(INS,F);
 







