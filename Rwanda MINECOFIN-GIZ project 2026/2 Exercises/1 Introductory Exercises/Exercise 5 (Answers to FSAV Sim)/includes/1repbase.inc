$STITLE Input file: REPBASE.INC. Report on base solution. Standard CGE modeling system, Version 1.01

$ontext

This is an include file to MOD101.GMS that produces the following reports
on the economy based on data for the base solution (with the name of the
relevant parameter in parentheses):
1. Economic structure table (STRUCBASE)
2. GDP table (GDPBASE)
3. Macro SAM (MACROSAM)
4. Input shares, factor wages, and elasticities (FACTAB1 - 4)
5. Household incomes (HHDTAB1 - 2)

For STRUCBASE, note that both activity and commodity data is presented
under commodity headings.

$offtext


*1. Economic structure table (STRUCBASE)=============================

SETS

 STRROW  Rows (only used to control order in display)
 /
 TOTAL-1
 TAGR
 TNAGR
 TOTAL-2
 /

 STRCOL  Columns
 /
 VAshr       value-added share (%)
 PRDshr      production share (%)
 EMPshr      share in total employment (%)
 EXPshr      sector share in total exports (%)
 EXP-OUTshr  exports as share in sector output (%)
 IMPshr   sector share in total imports (%)
 IMP-DEMshr  imports as share of domestic demand (%)
 /

 STRCOL2(STRCOL)  Columns for summation operation
/
 VAshr    value-added share (%)
 PRDshr   production share (%)
 EMPshr   share in total employment (%)
 EXPshr   sector share in total exports (%)
 IMPshr   sector share in total imports (%)
/
;

SET
 MAPAC(A,C) mapping from activities to commodities
 ;

MAPAC(A,C)$SAM(A,C) = YES;

DISPLAY MAPAC;

PARAMETER
 STRUCBASE(*,STRCOL)  Economic structure in the base
 ;

*Note: For VAshr, PRDshr, and EMPshr, data scaled by share of activity
*in output of commodity to avoid double-counting when there is not a
*one-to-one mapping between activities and commodities.

 STRUCBASE(C,'VAshr')
   = 100*SUM(A$MAPAC(A,C),
     (PXAC.L(A,C)*QXAC.L(A,C)/SUM(CP, PXAC.L(A,CP)*QXAC.L(A,CP)))*
     PVA.L(A)*(1-tva(A))*QVA.L(A)
                          /SUM(AP, PVA.L(AP)*(1-tva(AP))*QVA.L(AP)) );

 STRUCBASE(C,'PRDshr')
   = 100*SUM(A$MAPAC(A,C),
        (PXAC.L(A,C)*QXAC.L(A,C)/SUM(CP, PXAC.L(A,CP)*QXAC.L(A,CP)))
                       *PA.L(A)*QA.L(A)/SUM(AP, PA.L(AP)*QA.L(AP)) );

 STRUCBASE(C,'EMPshr')$SUM(F, FLAB(F))
   = 100*SUM(A$MAPAC(A,C),
        (PXAC.L(A,C)*QXAC.L(A,C)/SUM(CP, PXAC.L(A,CP)*QXAC.L(A,CP)))
       *SUM(F$FLAB(F), QF.L(F,A))/
                                  SUM((F,AP)$FLAB(F), QF.L(F,AP)) );

 STRUCBASE(C,'EXPshr')
  = 100*pwe.l(C)*QE.L(C)/SUM(CP, pwe.l(CP)*QE.L(CP));

 STRUCBASE(C,'IMPshr')
   = 100*pwm.l(C)*QM.L(C)/SUM(CP, pwm.l(CP)*QM.L(CP));

 STRUCBASE(C,'EXP-OUTshr')$(PX.L(C)*QX.L(C))
  = 100*PE.L(C)*QE.L(C)/(PX.L(C)*QX.L(C));

 STRUCBASE('TOTAL-1','EXP-OUTshr')
 = 100*SUM(C, PE.L(C)*QE.L(C))/SUM(CP, PX.L(CP)*QX.L(CP)) ;

 STRUCBASE('TAGR','EXP-OUTshr')$SUM(C, CAGR(C))
   = 100*SUM(C$CAGR(C), PE.L(C)*QE.L(C))/SUM(C$CAGR(C), PX.L(C)*QX.L(C)) ;

 STRUCBASE('TNAGR','EXP-OUTshr')$SUM(C, CAGR(C))
   = 100*SUM(C$CNAGR(C), PE.L(C)*QE.L(C))
                                   /SUM(C$CNAGR(C), PX.L(C)*QX.L(C));

 STRUCBASE(C,'IMP-DEMshr')$(PQ.L(C)*(1 - tq(C))*QQ.L(C))
   = 100*PM.L(C)*QM.L(C)/(PQ.L(C)*(1 - tq(C))*QQ.L(C));

 STRUCBASE('TOTAL-1','IMP-DEMshr')
   = 100*SUM(C, PM.L(C)*QM.L(C))
                            /SUM(CP, PQ.L(CP)*(1 - tq(CP))*QQ.L(CP));

 STRUCBASE('TAGR','IMP-DEMshr')$SUM(C, CAGR(C))
   = 100*SUM(C$CAGR(C), PM.L(C)*QM.L(C))
                        /SUM(C$CAGR(C), PQ.L(C)*(1 - tq(C))*QQ.L(C));

 STRUCBASE('TNAGR','IMP-DEMshr')$SUM(C, CAGR(C))
   = 100*SUM(C$CNAGR(C), PM.L(C)*QM.L(C))
                       /SUM(C$CNAGR(C), PQ.L(C)*(1 - tq(C))*QQ.L(C));


*Summation=======================

 STRUCBASE('TOTAL-1',STRCOL2)  = SUM(C, STRUCBASE(C,STRCOL2)) ;

 STRUCBASE('TAGR',STRCOL2) = SUM(C$CAGR(C), STRUCBASE(C,STRCOL2));
 STRUCBASE('TNAGR',STRCOL2) = SUM(C$CNAGR(C), STRUCBASE(C,STRCOL2));

 STRUCBASE('TOTAL-2',STRCOL2)
   = STRUCBASE('TAGR',STRCOL2) + STRUCBASE('TNAGR',STRCOL2) ;

 STRUCBASE('TOTAL-2','IMP-DEMshr') = STRUCBASE('TOTAL-1','IMP-DEMshr') ;
 STRUCBASE('TOTAL-2','EXP-OUTshr') = STRUCBASE('TOTAL-1','EXP-OUTshr') ;

*=======

OPTION STRUCBASE:1;
DISPLAY STRUCBASE ;


*2. GDP table (GDPBASE===============================================

SETS

 IGDPX  Items for GDP and national accounts
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

 IGDPXX(IGDPX)  Items for GDPMP summation
  /
  PRVCON   private consumption
  FIXINV   fixed investment
  DSTOCK   stock change
  GOVCON   government consumption
  EXPORTS  exports
  IMPORTS  imports
  /

 KGDPX  second index in GDP tables
 /
 VALUE, PERC-GDP, PERC-TOT
 /

*================================

PARAMETERS
 GDPBASE(IGDPX,KGDPX) Aggregate national accounts summary
 GDPERR                error if alt GDP definitions are not identical
 ;
*================================

 GDPBASE('PRVCON','VALUE')
   =  SUM((C,H), PQ.L(C)*QH.L(C,H))
      + SUM((A,C,H), PXAC.L(A,C)*QHA.L(A,C,H));

 GDPBASE('FIXINV','VALUE')  = SUM(C, PQ.L(C)*QINV.L(C));
 GDPBASE('DSTOCK','VALUE')   = SUM(C, PQ.L(C)*QDST(C));
 GDPBASE('GOVCON','VALUE')  = SUM(C, PQ.L(C)*QG.L(C));
 GDPBASE('EXPORTS','VALUE') = SUM(CE, PWE.L(CE)*EXR.L*QE.L(CE));
 GDPBASE('IMPORTS','VALUE') = -SUM(CM, PWM.L(CM)*EXR.L*QM.L(CM));
 GDPBASE('GDPMP','VALUE') = SUM(IGDPXX, GDPBASE(IGDPXX,'VALUE'));

 GDPBASE('ABSORP','VALUE')
  = GDPBASE('GDPMP','VALUE') - GDPBASE('IMPORTS','VALUE')
    - GDPBASE('EXPORTS','VALUE');

 GDPBASE('GDPFC2','VALUE') = SUM(A, PVA.L(A)*(1-tva(A))*QVA.L(A));

 GDPBASE('NETITAX','VALUE') =
            SUM(A, ta(A)*PA.L(A)*QA.L(A))
          + SUM(A, tva(A)*PVA.L(A)*QVA.L(A))
          + SUM(CM, tm(CM)*QM.L(CM)*PWM.L(CM))*EXR.L
          + SUM(CE, te(CE)*QE.L(CE)*PWE.L(CE))*EXR.L
          + SUM(C, tq(C)*PQ.L(C)*QQ.L(C));

 GDPBASE('GDPMP2','VALUE')
  = GDPBASE('GDPFC2','VALUE') + GDPBASE('NETITAX','VALUE');

 GDPERR$(ABS(GDPBASE('GDPMP2','VALUE') - GDPBASE('GDPMP','VALUE')) GT 0.00001)
  = 1/0;

* GDPBASE('GDPMP2','VALUE') = 0;


 GDPBASE(IGDPX,'PERC-GDP')$GDPBASE('GDPMP','VALUE')
  = 100*GDPBASE(IGDPX,'VALUE')/GDPBASE('GDPMP','VALUE');

*==================

OPTION GDPBASE:6;
DISPLAY GDPERR, GDPBASE;


*3. Macro SAM (MACSAM)===============================================


SET
 ACMAC     macrosam accounts

 /
 ACT2        Activities
 COM2        Commodities
 FAC2        Factors
 HOU2        Domestic non-gov institution (households + enterprises)
 GOV2        Current government
 ROW2        Rest of World
 S-I2        Savings investment account
 INSTAX2     direct taxes on domestic institutions
 FACTAX2     direct factor taxes
 IMPTAX2     import taxes
 EXPTAX2     export taxes
 VATAX2      value-added taxes
 ACTTAX2     indirect taxes on activity revenue
 COMTAX2     indirect taxes on commodity sales in domestic market
 TOTAL2      totals
 /

 ACMACNT(ACMAC)  all macrosam accounts except TOTAL2


ACMACTAX(ACMAC) tax accounts
 /
 INSTAX2     direct taxes on domestic institutions
 FACTAX2     direct factor taxes
 IMPTAX2     import taxes
 EXPTAX2     export taxes
 VATAX2      value-added taxes
 ACTTAX2     indirect taxes on activity revenue
 COMTAX2     indirect taxes on commodity sales in domestic market
 /

 ;

ACMACNT(ACMAC)    = YES;
ACMACNT('TOTAL2') = NO;

ALIAS(ACMAC,ACMACP),(ACMACNT,ACMACNTP);

PARAMETER
   MACROSAM(ACMAC,ACMACP)   Macro SAM
   BALCHK2(ACMAC)         total balance check
   ;

*Defining SAM cells==============

 MACROSAM('COM2','ACT2')    = SUM((C,A), PQ.L(C)*QINT.L(C,A));
 MACROSAM('FAC2','ACT2')    = SUM(A, PVA.L(A)*(1-tva(a))*QVA.L(A));
 MACROSAM('VATAX2','ACT2')  = SUM(A, tva(A)*PVA.L(A)*QVA.L(A));
 MACROSAM('ACTTAX2','ACT2') = SUM(A, ta(A)*PA.L(A)*QA.L(A));

 MACROSAM('COM2','COM2')    = SUM(C, PQ.L(C)*QT.L(C));
 MACROSAM('ACT2','COM2')    = SUM((C,A), QXAC.L(A,C)*PXAC.L(A,C));
 MACROSAM('ROW2','COM2')    = SUM(C, pwm.L(C)*QM.L(C))*EXR.L;
 MACROSAM('COMTAX2','COM2') = SUM(C, tq(C)*PQ.L(C)*QQ.L(C));
 MACROSAM('IMPTAX2','COM2') = SUM(C, tm(C)*pwm.L(C)*QM.L(C))*EXR.L;
 MACROSAM('EXPTAX2','COM2') = SUM(C, te(C)*pwe.L(C)*QE.L(C))*EXR.L;

 MACROSAM('HOU2','FAC2')    = SUM((INSDNG,F), YIF.L(INSDNG,F));
 MACROSAM('GOV2','FAC2')    = SUM(F, YIF.L('GOV',F));
 MACROSAM('ROW2','FAC2')    = SUM(F, trnsfr('ROW',F))*EXR.L;
 MACROSAM('FACTAX2','FAC2') = SUM(f, tf(f)*YF.L(F));

 MACROSAM('COM2','HOU2')    = SUM((C,H), PQ.L(C)*QH.L(C,H));
 MACROSAM('ACT2','HOU2')    = SUM((A,C,H), PXAC.L(A,C)*QHA.L(A,C,H));
 MACROSAM('INSTAX2','HOU2') = SUM(INSDNG, TINS.L(INSDNG)*YI.L(INSDNG));
 MACROSAM('HOU2','HOU2')    = SUM((INSDNG,INSDNGP), TRII.L(INSDNG,INSDNGP));
 MACROSAM('S-I2','HOU2')
  =  SUM(INSDNG, MPS.L(INSDNG) * (1 - TINS.L(INSDNG)) * YI.L(INSDNG));

 MACROSAM('COM2','GOV2')    = SUM(C, PQ.L(C)*QG.L(C));
 MACROSAM('HOU2','GOV2')    = SUM(INSD, trnsfr(INSD,'GOV'))*CPI.L;
 MACROSAM('S-I2','GOV2')    = GSAV.L ;

 MACROSAM('COM2','ROW2')    = SUM(C, pwe.L(C)*QE.L(C))*EXR.L;
 MACROSAM('HOU2','ROW2')    = SUM(INSDNG, trnsfr(INSDNG,'ROW'))*EXR.L;
 MACROSAM('GOV2','ROW2')    = trnsfr('GOV','ROW')*EXR.L;
 MACROSAM('S-I2','ROW2')    = FSAV.L*EXR.L ;

 MACROSAM('COM2','S-I2')
  = SUM(C, PQ.L(C)*QINV.L(C)) + SUM(C, PQ.L(C)*qdst(C));

 MACROSAM('GOV2',ACMACTAX)  = SUM(ACMAC, MACROSAM(ACMACTAX,ACMAC));


*Computing account totals========

 MACROSAM('TOTAL2', ACMAC) = 0;
 MACROSAM(ACMAC,'TOTAL2')   = 0;

 MACROSAM('TOTAL2', ACMACNTP) = SUM(ACMACNT,  MACROSAM(ACMACNT,ACMACNTP));
 MACROSAM(ACMACNT,'TOTAL2')   = SUM(ACMACNTP, MACROSAM(ACMACNT,ACMACNTP));


*Checking account balances=======

 BALCHK2(ACMACNT) = MACROSAM('TOTAL2',ACMACNT) - MACROSAM(ACMACNT,'TOTAL2');

PARAMETER
 MACCHK  error message if Macro SAM does not balance
 ;

 MACCHK(ACMACNT)$(ABS(BALCHK2(ACMACNT)) GT 0.00001) = 1/0;
*If error, either correct the SAM or exclude the include file.

*==========

OPTION MACROSAM:2;
DISPLAY BALCHK2, MACCHK, MACROSAM;


*4. Input shares, factor wages, and elasticities (FACTAB1 - 4)=======

*The parameters FACTAB1, FACTAB2, FACTAB3, FACTAB4 are covered in this
*section.


SETS
 FF(AC) all factor accounts and total
 AA(AC) all activity accounts and total
 ;

 FF(F)       = YES;
 FF('TOTAL') = YES;
 AA(A)       = YES;
 AA('TOTAL') = YES;


PARAMETERS
 FACTAB1(AC,ACP) Factor shares within sector
 FACTAB2(AC,ACP) Factor shares across sectors
 FACTAB3(AC,*)   Agg factor & intd. input shares & their sub. elasticity
 FACTAB4(AC,ACP) Factor wages by sector
 ;

 FACTAB1(A,F)       = WF.L(F)*wfdist.L(F,A)*QF.L(F,A) ;
 FACTAB1('TOTAL',F) = SUM(A, FACTAB1(A,F)) ;
 FACTAB1(A,'TOTAL') = SUM(F, FACTAB1(A,F)) ;
 FACTAB1('TOTAL','TOTAL') = SUM(F, FACTAB1('TOTAL',F)) ;
 FACTAB2(AA,FF)     = FACTAB1(AA,FF) ;
 FACTAB4(AA,FF)     = FACTAB1(AA,FF) ;

 FACTAB2(AA,FF)$FACTAB2('TOTAL',FF) = 100*FACTAB2(AA,FF)/FACTAB2('TOTAL',FF) ;
 FACTAB1(AA,FF)$FACTAB1(AA,'TOTAL') = 100*FACTAB1(AA,FF)/FACTAB1(AA,'TOTAL') ;

 FACTAB3(A,'QVASHR')$QA0(A)   = 100*PVA.L(A)*QVA.L(A)/(PA.L(A)*(1-ta(A))*QA.L(A)) ;
 FACTAB3(A,'QINTSHR')$QA0(A)  = 100*PINTA.L(A)*QINTA.L(A)/(PA.L(A)*(1-ta(A))*QA.L(A)) ;
 FACTAB3('TOTAL','QVASHR')  = 100*SUM(A, PVA.L(A)*QVA.L(A)) /
                              SUM(A, PA.L(A)*(1-ta(A))*QA.L(A)) ;
 FACTAB3('TOTAL','QINTSHR') = 100*SUM(A, PINTA.L(A)*QINTA.L(A)) /
                              SUM(A, PA.L(A)*(1-ta(A))*QA.L(A)) ;
 FACTAB3(A,'ACES')     = ACES(A) ;
 FACTAB3(A,'SIGMAQA')$ACES(A) = PRODELAS2(A) ;
 FACTAB3(A,'SIGMAVA')  = PRODELAS(A) ;

 FACTAB4(AA,'TOTAL')    = 0 ;
 FACTAB4(A,F)$QF.L(F,A) = FACTAB4(A,F)/QF.L(F,A) ;
 FACTAB4('TOTAL',F)$SUM(A, QF.L(F,A)) = FACTAB4('TOTAL',F)/SUM(A, QF.L(F,A)) ;

 OPTION FACTAB1:1, FACTAB2:1, FACTAB3:1, FACTAB4:3 ;
 Display FACTAB1, FACTAB2, FACTAB3, FACTAB4 ;


*5. Household incomes (HHDTAB1 - 2)==================================

PARAMETERS
 HHDTAB1(AC,ACP) Share of item ACP in the total income of hhd H (%)
 HHDTAB2(AC,ACP) Share of hhd AC in total hhd income from item ACP (%)
 ;

 HHDTAB1(H,ACNT)       = 100*SAM(H,ACNT)/SUM(ACNTP, SAM(H,ACNTP));
 HHDTAB1('TOTAL',ACNT) = 100*SUM(H, SAM(H,ACNT))/SUM((H,ACNTP), SAM(H,ACNTP));
 HHDTAB1(AC,'TOTAL')    = SUM(ACNT, HHDTAB1(AC,ACNT));

 HHDTAB2(H,ACNT)$SUM(HP, SAM(HP,ACNT)) = 100*SAM(H,ACNT)/SUM(HP, SAM(HP,ACNT));
 HHDTAB2(H,'TOTAL')                    = 100*SUM(ACNT, SAM(H,ACNT))/SUM((HP,ACNT), SAM(HP,ACNT));

 HHDTAB2('TOTAL',AC)                   = SUM(H, HHDTAB2(H,AC));

 OPTION  HHDTAB1:1, HHDTAB2:1;
 DISPLAY HHDTAB1, HHDTAB2;


*#*#*#*#*# THE END OF REPBASE.INC #*#*#*#*