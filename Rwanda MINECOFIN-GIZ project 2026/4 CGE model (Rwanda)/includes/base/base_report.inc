$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 1.7: Base model reporting 
 This include file (includes\1base_report.inc) produces the following reports based on data from
 the base model solution (with the name of the relevant parameter in parentheses):

SECTIONS:
 1.7.1  Economic structure table by activity            (STRUCBASEA)
 1.7.2  Economic structure table by commoidity          (STRUCBASEC)
 1.7.3  GDP table                                       (GDPBASE)
 1.7.4  Macro SAM                                       (MACROSAM)
 1.7.5  Input shares, factor wages, and elasticities    (FACTAB1-4)
 1.7.6  Household incomes                               (HHDTAB1-2)
$offtext


*------------------------------------------------------------------
* 1.7.1. Economic structure table by activity (STRUCBASEA)
* 1.7.2. Economic structure table by commodity (STRUCBASEC)
*------------------------------------------------------------------

SETS
 STRROW             rows (controls order in display) /
  TOTAL-1           total
  TAGR              agriculture
  TNAG              non-agriculture
  TIND              industry
  TSRV              services
  TOTAL-2           total
 /                  
 STRCOL             columns /
  VAshr             value-added shares (%)
  PRDshr            production shares (%)
  EMPshr            employment shares (%)
  QQshr             total commodity supply shares (%)
  HHDshr            private marketed consumption shares (%)
  OWNshr            private own consumption shares (%)
  MKTshr            private marketed consumption shares (%)
  GOVshr            public consumption shares (%)
  INVshr            gross capital formation shares (%)
  EXPshr            sector share in total exports (%)
  IMPshr            sector share in total imports (%)
  OWN-OUTshr        private own consumption as share of production (%)
  EXP-OUTshr        exports as share in sector output (%)
  IMP-DEMshr        imports as share of domestic demand (%)
  TRErate           transaction cost rate - exports (%)
  TRMrate           transaction cost rate - imports (%)
  TRDrate           transaction cost rate - domestic (%)
 /                  
 STRCOL2(STRCOL)    columns for summation operation /
  QQshr             sector share in total commodity supply (%)
  HHDshr            sector share in total private marketed consumption (%)
  GOVshr            sector share in total public consumption (%)
  INVshr            sector share in total gross capital formation (%)
  EXPshr            sector share in total exports (%)
  IMPshr            sector share in total imports (%)
 /                  
 STRCOL3(STRCOL)    columns for activities /
  VAshr             value-added shares (%)
  PRDshr            production shares (%)
  EMPshr            employment shares (%)
  OWNshr            private own consumption shares (%)
 /                  
;

PARAMETER
 b_STRUCTABC(*,STRCOL)      economic structure by commodity in the base
 b_STRUCTABA(*,STRCOL)      economic structure by activity in the base
;

*Note: For VAshr, PRDshr, and EMPshr, data scaled by share of activity in output of commodity to avoid double-counting
*when there is not a one-to-one mapping between activities and commodities.

*Structural data by activities
 b_STRUCTABA(A,'VAshr')                           = PVA.L(A)*(1-TV.L(A))*QVA.L(A) / SUM(AP, PVA.L(AP)*(1-TV.L(AP))*QVA.L(AP)) * 100;
 b_STRUCTABA(A,'PRDshr')                          = PA.L(A)*QA.L(A) / SUM(AP, PA.L(AP)*QA.L(AP)) * 100;
 b_STRUCTABA(A,'EMPshr')                          = SUM(F$FLAB(F), QF.L(F,A)) / SUM((F,AP)$FLAB(F), QF.L(F,AP)) * 100;
 b_STRUCTABA(A,'OWNshr')$SUM(H, QHA0(A,H))        = SUM(H, PA.L(A)*QHA.L(A,H)) / SUM((AP,H), PA.L(AP)*QHA.L(AP,H)) * 100;
 b_STRUCTABA(A,'OWN-OUTshr')$(PA.L(A) * QA.L(A))  = SUM(H, PA.L(A)*QHA.L(A,H)) / (PA.L(A)*QA.L(A)) * 100;

*Structural data by commodity
 b_STRUCTABC(C,'QQshr')                           = PQ.L(C)*QQ.L(C) / SUM(CP, PQ.L(CP)*QQ.L(CP)) * 100;
 b_STRUCTABC(C,'HHDshr')                          = SUM(H, PQ.L(C)*QH.L(C,H)) / SUM((CP,H), PQ.L(CP)*QH.L(CP,H)) * 100;
 b_STRUCTABC(C,'MKTshr')                          = SUM(H, PQ.L(C)*QH.L(C,H)) / SUM((CP,H), PQ.L(CP)*QH.L(CP,H)) * 100;
 b_STRUCTABC(C,'GOVshr')                          = PQ.L(C)*QG.L(C) / SUM(CP, PQ.L(CP)*QG.L(CP)) * 100;
 b_STRUCTABC(C,'INVshr')                          = PQ.L(C)*(QINV.L(C)+qdst(C)) / SUM(CP, PQ.L(CP)*(QINV.L(CP)+qdst(CP))) * 100;
 b_STRUCTABC(C,'EXPshr')                          = pwe(C)*QE.L(C) / SUM(CP, pwe(CP)*QE.L(CP)) * 100;
 b_STRUCTABC(C,'IMPshr')                          = pwm(C)*QM.L(C) / SUM(CP, pwm(CP)*QM.L(CP)) * 100;
 b_STRUCTABC(C,'EXP-OUTshr')$(PX.L(C)*QX.L(C))    = PE.L(C)*QE.L(C) / (PX.L(C)*QX.L(C)) * 100;
 b_STRUCTABC(C,'IMP-DEMshr')$(PQ.L(C)*QQ.L(C))    = PM.L(C)*QM.L(C) / (PQ.L(C)*(1 - TQ.L(C))*QQ.L(C)) * 100;
 
*Aggregates: Own consumption-output shares
 b_STRUCTABA('TOTAL-1','OWN-OUTshr')              = SUM((A,H),         PA.L(A)*QHA.L(A,H)) / SUM(A,         PA.L(A)*QA.L(A)) * 100;
 b_STRUCTABA('TAGR','OWN-OUTshr')$SUM(A, AAGR(A)) = SUM((A,H)$AAGR(A), PA.L(A)*QHA.L(A,H)) / SUM(A$AAGR(A), PA.L(A)*QA.L(A)) * 100;
 b_STRUCTABA('TNAG','OWN-OUTshr')$SUM(A, AAGR(A)) = SUM((A,H)$AAGR(A), PA.L(A)*QHA.L(A,H)) / SUM(A$AAGR(A), PA.L(A)*QA.L(A)) * 100;
 b_STRUCTABA('TIND','OWN-OUTshr')$SUM(A, AIND(A)) = SUM((A,H)$AIND(A), PA.L(A)*QHA.L(A,H)) / SUM(A$AIND(A), PA.L(A)*QA.L(A)) * 100;
 b_STRUCTABA('TSRV','OWN-OUTshr')$SUM(A, ASRV(A)) = SUM((A,H)$ASRV(A), PA.L(A)*QHA.L(A,H)) / SUM(A$ASRV(A), PA.L(A)*QA.L(A)) * 100;

*Aggregates: Export-output shares
 b_STRUCTABC('TOTAL-1','EXP-OUTshr')              = SUM(C,         PE.L(C)*QE.L(C)) / SUM(C,         PX.L(C)*QX.L(C)) * 100;
 b_STRUCTABC('TAGR','EXP-OUTshr')$SUM(C, CAGR(C)) = SUM(C$CAGR(C), PE.L(C)*QE.L(C)) / SUM(C$CAGR(C), PX.L(C)*QX.L(C)) * 100;
 b_STRUCTABC('TNAG','EXP-OUTshr')$SUM(C, CAGR(C)) = SUM(C$CAGR(C), PE.L(C)*QE.L(C)) / SUM(C$CAGR(C), PX.L(C)*QX.L(C)) * 100;
 b_STRUCTABC('TIND','EXP-OUTshr')$SUM(C, CIND(C)) = SUM(C$CIND(C), PE.L(C)*QE.L(C)) / SUM(C$CIND(C), PX.L(C)*QX.L(C)) * 100;
 b_STRUCTABC('TSRV','EXP-OUTshr')$SUM(C, CSRV(C)) = SUM(C$CSRV(C), PE.L(C)*QE.L(C)) / SUM(C$CSRV(C), PX.L(C)*QX.L(C)) * 100;

*Aggregates: Import-demand shares
 b_STRUCTABC('TOTAL-1','IMP-DEMshr')              = SUM(C,         PM.L(C)*QM.L(C)) / SUM(C,         PQ.L(C)*(1 - TQ.L(C))*QQ.L(C)) * 100;
 b_STRUCTABC('TAGR','IMP-DEMshr')$SUM(C, CAGR(C)) = SUM(C$CAGR(C), PM.L(C)*QM.L(C)) / SUM(C$CAGR(C), PQ.L(C)*(1 - TQ.L(C))*QQ.L(C)) * 100;
 b_STRUCTABC('TNAG','IMP-DEMshr')$SUM(C, CAGR(C)) = SUM(C$CAGR(C), PM.L(C)*QM.L(C)) / SUM(C$CAGR(C), PQ.L(C)*(1 - TQ.L(C))*QQ.L(C)) * 100;
 b_STRUCTABC('TIND','IMP-DEMshr')$SUM(C, CAGR(C)) = SUM(C$CIND(C), PM.L(C)*QM.L(C)) / SUM(C$CIND(C), PQ.L(C)*(1 - TQ.L(C))*QQ.L(C)) * 100;
 b_STRUCTABC('TSRV','IMP-DEMshr')$SUM(C, CAGR(C)) = SUM(C$CSRV(C), PM.L(C)*QM.L(C)) / SUM(C$CSRV(C), PQ.L(C)*(1 - TQ.L(C))*QQ.L(C)) * 100;

*Summation: Activities.
 b_STRUCTABA('TOTAL-1',STRCOL3)                   = SUM(A,         b_STRUCTABA(A,STRCOL3));
 b_STRUCTABA('TAGR',STRCOL3)                      = SUM(A$AAGR(A), b_STRUCTABA(A,STRCOL3));
 b_STRUCTABA('TNAG',STRCOL3)                      = SUM(A$ANAG(A), b_STRUCTABA(A,STRCOL3));
 b_STRUCTABA('TIND',STRCOL3)                      = SUM(A$AIND(A), b_STRUCTABA(A,STRCOL3));
 b_STRUCTABA('TSRV',STRCOL3)                      = SUM(A$ASRV(A), b_STRUCTABA(A,STRCOL3));
 b_STRUCTABA('TOTAL-2',STRCOL3)                   = b_STRUCTABA('TAGR',STRCOL3) + b_STRUCTABA('TNAG',STRCOL3);

*Summation: Commodities.
 b_STRUCTABC('TOTAL-1',STRCOL2)                   = SUM(C,         b_STRUCTABC(C,STRCOL2)) ;
 b_STRUCTABC('TAGR',STRCOL2)                      = SUM(C$CAGR(C), b_STRUCTABC(C,STRCOL2));
 b_STRUCTABC('TNAG',STRCOL2)                      = SUM(C$CNAG(C), b_STRUCTABC(C,STRCOL2));
 b_STRUCTABC('TIND',STRCOL2)                      = SUM(C$CIND(C), b_STRUCTABC(C,STRCOL2));
 b_STRUCTABC('TSRV',STRCOL2)                      = SUM(C$CSRV(C), b_STRUCTABC(C,STRCOL2));
 b_STRUCTABC('TOTAL-2',STRCOL2)                   = b_STRUCTABC('TAGR',STRCOL2) + b_STRUCTABC('TNAG',STRCOL2);
 
 b_STRUCTABA('TOTAL-2','OWN-OUTshr')              = b_STRUCTABA('TOTAL-1','OWN-OUTshr') ;
 b_STRUCTABC('TOTAL-2','IMP-DEMshr')              = b_STRUCTABC('TOTAL-1','IMP-DEMshr') ;
 b_STRUCTABC('TOTAL-2','EXP-OUTshr')              = b_STRUCTABC('TOTAL-1','EXP-OUTshr') ;

*------------------------------------------------------------------
* 1.7.3  GDP table (GDPBASE)
*------------------------------------------------------------------

SETS
 IGDPX              items for GDP and national accounts /
  ABSORP            absorption
  PRVCON            private consumption
  FIXINV            fixed investment
  DSTOCK            stock change
  GOVCON            government consumption
  EXPORTS           exports
  IMPORTS           imports
  GDPMP             GDP at market prices (alt. 1: spending)
  GDPMP2            GDP at market prices (alt. 2: value-added)
  NETITAX           net indirect taxes
  GDPFC2            GDP at factor cost
 /
 IGDPXX(IGDPX)      items for GDPMP summation /
  PRVCON            private consumption
  FIXINV            fixed investment
  DSTOCK            stock change
  GOVCON            government consumption
  EXPORTS           exports
  IMPORTS           imports
 /
 KGDPX              second index in GDP tables /
  VALUE, PERC-GDP, PERC-TOT
 /
;

PARAMETERS
 b_GDPTAB(IGDPX,KGDPX)    aggregate national accounts summary
 b_GDPERR                 error if alt GDP definitions are not identical
;

 b_GDPTAB('PRVCON','VALUE')  =  SUM((C,H), PQ.L(C)*QH.L(C,H)) + SUM((A,H), PA.L(A)*QHA.L(A,H));
 b_GDPTAB('FIXINV','VALUE')  =  SUM(C, PQ.L(C)*QINV.L(C));
 b_GDPTAB('DSTOCK','VALUE')  =  SUM(C, PQ.L(C)*QDST(C));
 b_GDPTAB('GOVCON','VALUE')  =  SUM(C, PQ.L(C)*QG.L(C));
 b_GDPTAB('EXPORTS','VALUE') =  SUM((CE), pwe(CE)*EXR.L*QE.L(CE));
 b_GDPTAB('IMPORTS','VALUE') = -SUM((CM), pwm(CM)*EXR.L*QM.L(CM));
 b_GDPTAB('GDPMP','VALUE')   =  SUM(IGDPXX, b_GDPTAB(IGDPXX,'VALUE'));
 b_GDPTAB('ABSORP','VALUE')  =  b_GDPTAB('GDPMP','VALUE') + b_GDPTAB('IMPORTS','VALUE') - b_GDPTAB('EXPORTS','VALUE');

 b_GDPTAB('GDPFC2','VALUE')  = SUM((F,A), WF.L(F)*WFDIST.L(F,A)*QF.L(F,A));

 b_GDPTAB('NETITAX','VALUE') =
           SUM(A,    TA.L(A)*PA.L(A)*QA.L(A))
         + SUM(A,    TV.L(A)*PVA.L(A)*QVA.L(A))
         + SUM((CM), TM.L(CM)*QM.L(CM)*pwm(CM))*EXR.L
         + SUM((CE), TE.L(CE)*QE.L(CE)*pwe(CE))*EXR.L
         + SUM(C,    TQ.L(C)*PQ.L(C)*QQ.L(C));

 b_GDPTAB('GDPMP2','VALUE')
         = b_GDPTAB('GDPFC2','VALUE') + b_GDPTAB('NETITAX','VALUE');

 b_GDPERR$(ABS(b_GDPTAB('GDPMP2','VALUE') - b_GDPTAB('GDPMP','VALUE')) GT 0.00001)
         = b_GDPTAB('GDPMP2','VALUE') - b_GDPTAB('GDPMP','VALUE');

 b_GDPTAB(IGDPX,'PERC-GDP')$b_GDPTAB('GDPMP','VALUE')
         = 100 * b_GDPTAB(IGDPX,'VALUE')/b_GDPTAB('GDPMP','VALUE');


*------------------------------------------------------------------
* 1.7.4  Macro SAM (MACROSAM)
*------------------------------------------------------------------

SET
 ACMAC              macrosam accounts /
  ACT2              activities
  COM2              commodities
  FAC2              factors
  ENT2              enterprises
  HOU2              households
  GOV2              current government
  ACTTAX2           indirect taxes on activity revenue
  COMTAX2           indirect taxes on commodity sales in domestic market
  EXPTAX2           export taxes
  FACTAX2           direct factor taxes
  IMPTAX2           import taxes
  INSTAX2           direct taxes on domestic institutions
  VATAX2            value-added taxes
  S-I2              savings investment account
  ROW2              rest of World
  TOTAL2            totals
 /                  
 ACMACNT(ACMAC)     all macrosam accounts except TOTAL2
 ACMACTAX(ACMAC)    tax accounts /
  ACTTAX2           indirect taxes on activity revenue
  COMTAX2           indirect taxes on commodity sales in domestic market
  EXPTAX2           export taxes
  FACTAX2           direct factor taxes
  IMPTAX2           import taxes
  INSTAX2           direct taxes on domestic institutions
  VATAX2            value-added taxes
 /
;

 ACMACNT(ACMAC)    = YES;
 ACMACNT('TOTAL2') = NO;

ALIAS(ACMAC,ACMACP),(ACMACNT,ACMACNTP);

PARAMETER
 b_MACROSAM(ACMAC,ACMACP)   macro SAM
 b_BALCHK2(ACMAC)           total balance check
;

*Activities.
 b_MACROSAM('COM2','ACT2')    = SUM((C,A),  PQ.L(C)*QINT.L(C,A));
 b_MACROSAM('FAC2','ACT2')    = SUM((F,A),  WF.L(F)*WFDIST.L(F,A)*QF.L(F,A));
 b_MACROSAM('ACTTAX2','ACT2') = SUM(A,      TA.L(A)*PA.L(A)*QA.L(A));
 b_MACROSAM('VATAX2','ACT2')  = SUM(A,      TV.L(A)*PVA.L(A)*QVA.L(A));

*Commodities.
 b_MACROSAM('ACT2','COM2')    = SUM((C,A),  QXAC.L(A,C) * PXAC.L(A,C));
 b_MACROSAM('COM2','COM2')    = SUM(C,      PQ.L(C)*QT.L(C));
 b_MACROSAM('ROW2','COM2')    = SUM(CM,     pwm(CM)*QM.L(CM))*EXR.L;
 b_MACROSAM('COMTAX2','COM2') = SUM(C,      TQ.L(C)*PQ.L(C)*QQ.L(C));
 b_MACROSAM('IMPTAX2','COM2') = SUM(CM,     TM.L(CM)*pwm(CM)*QM.L(CM))*EXR.L;
 b_MACROSAM('EXPTAX2','COM2') = SUM(CE,     TE.L(CE)*pwe(CE)*QE.L(CE))*EXR.L;

*Factors.
 b_MACROSAM('ENT2','FAC2')    = SUM((F,EN), YIF.L(EN,F));
 b_MACROSAM('HOU2','FAC2')    = SUM((H,F),  YIF.L(H,F));
 b_MACROSAM('GOV2','FAC2')    = SUM(F,      YIF.L(GV,F));
 b_MACROSAM('FACTAX2','FAC2') = SUM(F,      TF.L(F)*YF.L(F));
 b_MACROSAM('ROW2','FAC2')    = SUM(F,      YIF.L(RW,F));

*Enterprises.
 b_MACROSAM('ENT2','ENT2')    = SUM((EN,ENP), TRII.L(EN,ENP));
 b_MACROSAM('HOU2','ENT2')    = SUM((H,EN), TRII.L(H,EN));
 b_MACROSAM('GOV2','ENT2')    = SUM(EN,     TRII.L(GV,EN));
 b_MACROSAM('INSTAX2','ENT2') = SUM(EN,     TI.L(EN)*YI.L(EN));
 b_MACROSAM('S-I2','ENT2')    = SUM(EN,     MPS.L(EN)*YI.L(EN)*(1-TI.L(EN)));
 b_MACROSAM('ROW2','ENT2')    = SUM(EN,     TRII.L(RW,EN));

*Households.
 b_MACROSAM('ACT2','HOU2')    = SUM((A,H),  PA.L(A)*QHA.L(A,H));
 b_MACROSAM('COM2','HOU2')    = SUM((C,H),  PQ.L(C)*QH.L(C,H));
 b_MACROSAM('ENT2','HOU2')    = SUM((EN,H), TRII.L(EN,H));
 b_MACROSAM('HOU2','HOU2')    = SUM((H,HP), TRII.L(H,HP));
 b_MACROSAM('GOV2','HOU2')    = SUM(H,      TRII.L(GV,H));
 b_MACROSAM('INSTAX2','HOU2') = SUM(H,      TI.L(H)*YI.L(H));
 b_MACROSAM('S-I2','HOU2')    = SUM(H,      MPS.L(H)*YI.L(H)*(1-TI.L(H)));
 b_MACROSAM('ROW2','HOU2')    = SUM(H,      TRII.L(RW,H));

*Government.
 b_MACROSAM('COM2','GOV2')    = SUM(C,      PQ.L(C)*QG.L(C));
 b_MACROSAM('ENT2','GOV2')    = SUM(EN,     trnsi(EN,GV))*CPI.L;
 b_MACROSAM('HOU2','GOV2')    = SUM(H,      trnsi(H,GV))*CPI.L;
 b_MACROSAM('S-I2','GOV2')    =             GSAV.L;
 b_MACROSAM('ROW2','GOV2')    =             trnsi(RW,GV)*EXR.L;
 b_MACROSAM('GOV2',ACMACTAX)  = SUM(ACMAC,  b_MACROSAM(ACMACTAX,ACMAC));

*Savings-investment.
 b_MACROSAM('COM2','S-I2')    = SUM(C,      PQ.L(C)*QINV.L(C)) + SUM(C, PQ.L(C)*qdst(C));

*Rest of world.
 b_MACROSAM('COM2','ROW2')    = SUM(CE,     pwe(CE)*QE.L(CE))*EXR.L;
 b_MACROSAM('FAC2','ROW2')    = SUM(F,      trnsf(F,RW))*EXR.L;
 b_MACROSAM('ENT2','ROW2')    = SUM(EN,     trnsi(EN,RW))*EXR.L;
 b_MACROSAM('HOU2','ROW2')    = SUM(H,      trnsi(H,RW))*EXR.L;
 b_MACROSAM('GOV2','ROW2')    =             trnsi(GV,RW)*EXR.L;
 b_MACROSAM('S-I2','ROW2')    =             FSAV.L*EXR.L;

*Account totals.
 b_MACROSAM('TOTAL2',ACMAC)   = 0;
 b_MACROSAM(ACMAC,'TOTAL2')   = 0;

 b_MACROSAM('TOTAL2', ACMACNTP) = SUM(ACMACNT,  b_MACROSAM(ACMACNT,ACMACNTP));
 b_MACROSAM(ACMACNT,'TOTAL2')   = SUM(ACMACNTP, b_MACROSAM(ACMACNT,ACMACNTP));

*Checking account balances.
 b_BALCHK2(ACMACNT) = b_MACROSAM('TOTAL2',ACMACNT) - b_MACROSAM(ACMACNT,'TOTAL2');
 b_BALCHK2(ACMACNT)$(ABS(b_BALCHK2(ACMACNT)) LT 1E-6) = 0;


*------------------------------------------------------------------
* 1.7.5  Input shares, factor wages, and elasticities (FACTAB1-4)
*------------------------------------------------------------------

SETS
 FFAC(AC)           all factor accounts and total
 AACT(AC)           all activity accounts and total
;

 FFAC(F)       = YES;
 FFAC('TOTAL') = YES;
 AACT(A)       = YES;
 AACT('TOTAL') = YES;

PARAMETERS
 b_FACTAB1(AC,ACP)    factor shares within sector
 b_FACTAB2(AC,ACP)    factor shares across sectors
 b_FACTAB3(AC,*)      aggregate factor and intermediate input shares and their substitution elasticity
 b_FACTAB4(AC,ACP)    factor wages by sector
;

 b_FACTAB1(A,F)                 = WF.L(F)*WFDIST.L(F,A)*QF.L(F,A);
 b_FACTAB1('TOTAL',F)           = SUM(A, b_FACTAB1(A,F));
 b_FACTAB1(A,'TOTAL')           = SUM(F, b_FACTAB1(A,F));
 b_FACTAB1('TOTAL','TOTAL')     = SUM(F, b_FACTAB1('TOTAL',F));
 b_FACTAB2(AACT,FFAC)           = b_FACTAB1(AACT,FFAC);
 b_FACTAB1(AACT,FFAC)$b_FACTAB1(AACT,'TOTAL') = b_FACTAB1(AACT,FFAC)/b_FACTAB1(AACT,'TOTAL')*100;
 b_FACTAB2(AACT,FFAC)$b_FACTAB2('TOTAL',FFAC) = b_FACTAB2(AACT,FFAC)/b_FACTAB2('TOTAL',FFAC)*100;

 b_FACTAB3(A,'QVASHR')$QA.L(A)  = PVA.L(A)*QVA.L(A)/(PA.L(A)*(1-TA.L(A))*QA.L(A))*100;
 b_FACTAB3(A,'QINTSHR')$QA.L(A) = PINTA.L(A)*QINTA.L(A)/(PA.L(A)*(1-TA.L(A))*QA.L(A))*100;
 b_FACTAB3('TOTAL','QVASHR')    = SUM(A, PVA.L(A)*QVA.L(A))/SUM(A, PA.L(A)*(1-TA.L(A))*QA.L(A))*100;
 b_FACTAB3('TOTAL','QINTSHR')   = SUM(A, PINTA.L(A)*QINTA.L(A))/SUM(A, PA.L(A)*(1-TA.L(A))*QA.L(A))*100;
 b_FACTAB3(A,'ACES')$QA.L(A)    = ACES(A);
 b_FACTAB3(A,'SIGMAQA')$QA.L(A) = AELAS(A,'ELASPRD2');
 b_FACTAB3(A,'SIGMAVA')$QA.L(A) = AELAS(A,'ELASPRD');

 b_FACTAB4(AACT,FFAC)           = b_FACTAB1(AACT,FFAC);
 b_FACTAB4(AACT,'TOTAL')        = 0;
 b_FACTAB4(A,F)$QF.L(F,A)       = b_FACTAB4(A,F)/QF.L(F,A);
 b_FACTAB4('TOTAL',F)$SUM(A, QF.L(F,A)) = b_FACTAB4('TOTAL',F)/SUM(A, QF.L(F,A));


*------------------------------------------------------------------
* 1.7.6  Household incomes (HHDTAB1-2)
*------------------------------------------------------------------

PARAMETERS
 b_HHDTAB1(AC,ACP)    share of item ACP in the total income of household H (%)
 b_HHDTAB2(AC,ACP)    share of household AC in total household income from item ACP (%)
;

 b_HHDTAB1(H,ACNT)$SUM(ACNTP, SAM(H,ACNTP))           = SAM(H,ACNT)/SUM(ACNTP, SAM(H,ACNTP))*100;
 b_HHDTAB1('TOTAL',ACNT)$SUM((H,ACNTP), SAM(H,ACNTP)) = SUM(H, SAM(H,ACNT))/SUM((H,ACNTP), SAM(H,ACNTP))*100;
 b_HHDTAB1(AC,'TOTAL')                                = SUM(ACNT, b_HHDTAB1(AC,ACNT));

 b_HHDTAB2(H,ACNT)$SUM(HP, SAM(HP,ACNT))              = SAM(H,ACNT)/SUM(HP, SAM(HP,ACNT))*100;
 b_HHDTAB2(H,'TOTAL')$SUM((HP,ACNT), SAM(HP,ACNT))    = SUM(ACNT, SAM(H,ACNT))/SUM((HP,ACNT), SAM(HP,ACNT))*100;
 b_HHDTAB2('TOTAL',AC)                                = SUM(H, b_HHDTAB2(H,AC));
 
DISPLAY b_STRUCTABA b_STRUCTABC 