$TITLE Input file: 3report.gms. IFPRI Extended standard recursive dynamic CGE modeling system, Version 2.00

*Load reporting sets and mappings
$call "gdxxrw i=2simulation.xlsx o=2simulation.gdx index=repindex!a6"
$gdxin 2simulation.gdx

SET
 RA      supply-side accounts
 RAG(RA) aggregate supply-side accounts
 HA      household accounts
 HAG(HA) aggregate household accounts
 LA      factor accounts
 LAG(LA) aggregate factor accounts
 DA      reporting demand accounts /
  dGDP, dPRVCON, dINVEST, dGOVCON, dEXPORT, dIMPORT
 /
 TAXAC /
  tIMPshr, tIMPtar, tIMPrev, tEXPshr, tEXPtax, tEXPrev, tACTshr, tACTtax, tACTrev
 /
 MCA(C,A)
 MCRA(C,RA)
;

ALIAS (RA,RAP), (DA,DAP), (HA,HAP), (FA,FAP);

PARAMETER
*Mappings
 MARA(A,RA)                      mapping between activities and aggregates
 MHHA(H,HA)                      mapping between households and aggregates
 MFLA(F,LA)                      mapping between factors and aggregates
*Supply-side reporting parameters
 sVALUE(RA,SIM)                  GDP at factor cost
 sSHARE(RA,SIM)                  share of GDP at factor cost
 sGROWTH(RA,SIM)                 change in GDP at factor cost
 sCONTR(RA,SIM)                  contribution to change in GDP
*Demand-side reporting parameters
 dVALUE(DA,SIM)                  GDP at market prices
 dSHARE(DA,SIM)                  share of GDP at market prices
 dGROWTH(DA,SIM)                 change in GDP at market prices
 dCONTR(DA,SIM)                  contribution to change in GDP
*Import and export growth rates by aggregate commodity
 QETAB(RA,SIM)                   real export value
 QMTAB(RA,SIM)                   real import value
*Income and expenditure table
 YITAB(HA,SIM)                   household incomes
 QHTAB2(RA,SIM)                  real household spending
 QCTAB(HA,SIM)                   real household consumption
*Prices
 PXTAB(RA,SIM)                   output supply prices
 PQTAB(RA,SIM)                   final composite demand prices
 PETAB(RA,SIM)                   export prices
 PMTAB(RA,SIM)                   import prices
 PWETAB(RA,SIM)                  world export prices
 PWMTAB(RA,SIM)                  world import prices
*Factor employment and wages tables
 QFTAB(F,RA,SIM)
 QFSTAB(LA,SIM)
 WFTAB(LA,SIM)
 YFTAB2(LA,SIM)
*Structural base table
 STRUCBASE2(RA,STRCOL)           economic structure in the base
*Tax tables
 TAXTOT(*,INSDNG,SIM)
 TAXTAB(RA,TAXAC)
;

*Load sets and mappings from excel file 3report.xls
$load RA HA LA
$loaddc RAG HAG LAG MARA MHHA MFLA MCA
*Ensure that there are no mapping entries for total GDP at factor cost
 MARA(A,'sGDP') = 1;
*Mapping between reporting activities and commodities
 MCRA(C,RA) = SUM(A$MCA(C,A), MARA(A,RA));

*Growth decompositions (Supply-side and demand-side) --------------------------
*------------------------------------------------------------------------------

*Calculate supply-side decomposition (GDP at factor cost) ------------
*Values and shares
 sVALUE(RA,SIMCUR)     = SUM(A$MARA(A,RA), PVA0(A)*(1-tva0(A))*QVAX(A,SIMCUR));
 sSHARE(RA,SIMCUR)$SUM(RAP$(NOT RAG(RAP)), sVALUE(RAP,SIMCUR))     = sVALUE(RA,SIMCUR) / SUM(RAP$(NOT RAG(RAP)), sVALUE(RAP,SIMCUR))*100;
*Growth rates
 sGROWTH(RA,SIMCUR)$sVALUE(RA,'BASE') = (sVALUE(RA,SIMCUR)/sVALUE(RA,'BASE')-1)*100;
 SGROWTH(RA,'BASE') = sSHARE(RA,'BASE');
*Contribution to growth
 sCONTR(RA,SIMCUR) = sSHARE(RA,'BASE')/100*sGROWTH(RA,SIMCUR);

*Calculate supply-side decomposition of growth (GDP at factor cost) ------------
*Values and shares
 dVALUE('dPRVCON',SIMCUR) = GDPTAB1('REAL','PRVCON' ,SIMCUR);
 dVALUE('dINVEST',SIMCUR) = GDPTAB1('REAL','FIXINV' ,SIMCUR) + GDPTAB1('REAL','DSTOCK',SIMCUR);
 dVALUE('dGOVCON',SIMCUR) = GDPTAB1('REAL','GOVCON' ,SIMCUR);
 dVALUE('dEXPORT',SIMCUR) = GDPTAB1('REAL','EXPORTS',SIMCUR);
 dVALUE('dIMPORT',SIMCUR) = GDPTAB1('REAL','IMPORTS',SIMCUR);
 dSHARE(DA,SIMCUR)        = dVALUE(DA,SIMCUR) / SUM(DAP, dVALUE(DAP,SIMCUR))*100;
 dVALUE('dGDP',SIMCUR)    = SUM(DA, dVALUE(DA,SIMCUR));
 dSHARE('dGDP',SIMCUR)    = SUM(DA, dSHARE(DA,SIMCUR));
*Annual growth rates
 dGROWTH(DA,SIMCUR)$dVALUE(DA,'BASE') = (dVALUE(DA,SIMCUR)/dVALUE(DA,'BASE')-1)*100;
 dGROWTH(DA,SIMCUR) = dSHARE(DA,SIMCUR);
*Annual contribution to growth
 dCONTR(DA,SIMCUR) = dSHARE(DA,'BASE')/100*dGROWTH(DA,SIMCUR);

*Export and import tables -----------------------------------------------------
*------------------------------------------------------------------------------

*Changes
 QETAB(RA,SIMCUR)$SUM(C$MCRA(C,RA), QE0(C)) = (SUM(C$MCRA(C,RA), PWE0(C)*EXR0*QEX(C,SIMCUR))/SUM(C$MCRA(C,RA), PWE0(C)*EXR0*QE0(C))-1)*100;
 QMTAB(RA,SIMCUR)$SUM(C$MCRA(C,RA), QM0(C)) = (SUM(C$MCRA(C,RA), PWM0(C)*EXR0*QMX(C,SIMCUR))/SUM(C$MCRA(C,RA), PWM0(C)*EXR0*QM0(C))-1)*100;
*Initial shares
 QETAB(RA,'BASE')$SUM(C, PE0(C)*QE0(C)) = SUM(C$MCRA(C,RA), PE0(C)*QE0(C))/SUM(C, PE0(C)*QE0(C))*100;
 QMTAB(RA,'BASE')$SUM(C, PM0(C)*QM0(C)) = SUM(C$MCRA(C,RA), PM0(C)*QM0(C))/SUM(C, PM0(C)*QM0(C))*100;

*Prices tables ----------------------------------------------------------------
*------------------------------------------------------------------------------

 PXTAB(RA,SIMCUR)$SUM(C$MCRA(C,RA), QX0(C))  = SUM(C$MCRA(C,RA), PXX(C,SIMCUR)  * PX0(C)*QX0(C)  / SUM(CP$(MCRA(C,RA) AND MCRA(CP,RA)), PX0(CP)*QX0(CP)));
 PQTAB(RA,SIMCUR)$SUM(C$MCRA(C,RA), QQ0(C))  = SUM(C$MCRA(C,RA), PQX(C,SIMCUR)  * PQ0(C)*QQ0(C)  / SUM(CP$(MCRA(C,RA) AND MCRA(CP,RA)), PQ0(CP)*QQ0(CP)));
 PETAB(RA,SIMCUR)$SUM(C$MCRA(C,RA), QE0(C))  = SUM(C$MCRA(C,RA), PEX(C,SIMCUR)  * PE0(C)*QE0(C)  / SUM(CP$(MCRA(C,RA) AND MCRA(CP,RA)), PE0(CP)*QE0(CP)));
 PMTAB(RA,SIMCUR)$SUM(C$MCRA(C,RA), QM0(C))  = SUM(C$MCRA(C,RA), PMX(C,SIMCUR)  * PM0(C)*QM0(C)  / SUM(CP$(MCRA(C,RA) AND MCRA(CP,RA)), PM0(CP)*QM0(CP)));
 PWETAB(RA,SIMCUR)$SUM(C$MCRA(C,RA), QE0(C)) = SUM(C$MCRA(C,RA), PWEX(C,SIMCUR) * PWE0(C)*QE0(C) / SUM(CP$(MCRA(C,RA) AND MCRA(CP,RA)), PWE0(CP)*QE0(CP)));
 PWMTAB(RA,SIMCUR)$SUM(C$MCRA(C,RA), QM0(C)) = SUM(C$MCRA(C,RA), PWMX(C,SIMCUR) * PWM0(C)*QM0(C) / SUM(CP$(MCRA(C,RA) AND MCRA(CP,RA)), PWM0(CP)*QM0(CP)));

 PXTAB(RA,SIMCUR)$PXTAB(RA,'BASE') = (PXTAB(RA,SIMCUR)/PXTAB(RA,'BASE')-1)*100;
 PQTAB(RA,SIMCUR)$PQTAB(RA,'BASE') = (PQTAB(RA,SIMCUR)/PQTAB(RA,'BASE')-1)*100;
 PETAB(RA,SIMCUR)$PETAB(RA,'BASE') = (PETAB(RA,SIMCUR)/PETAB(RA,'BASE')-1)*100;
 PMTAB(RA,SIMCUR)$PMTAB(RA,'BASE') = (PMTAB(RA,SIMCUR)/PMTAB(RA,'BASE')-1)*100;
 PWETAB(RA,SIMCUR)$PWETAB(RA,'BASE') = (PWETAB(RA,SIMCUR)/PWETAB(RA,'BASE')-1)*100;
 PWMTAB(RA,SIMCUR)$PWMTAB(RA,'BASE') = (PWMTAB(RA,SIMCUR)/PWMTAB(RA,'BASE')-1)*100;

 PXTAB(RA,'BASE')$SUM(C, QX0(C))  = SUM(C$MCRA(C,RA), PX0(C)*QX0(C))  / SUM(CP, PX0(CP)*QX0(CP))*100;
 PQTAB(RA,'BASE')$SUM(C, QQ0(C))  = SUM(C$MCRA(C,RA), PQ0(C)*QQ0(C))  / SUM(CP, PQ0(CP)*QQ0(CP))*100;
 PETAB(RA,'BASE')$SUM(C, QE0(C))  = SUM(C$MCRA(C,RA), PE0(C)*QE0(C))  / SUM(CP, PE0(CP)*QE0(CP))*100;
 PMTAB(RA,'BASE')$SUM(C, QM0(C))  = SUM(C$MCRA(C,RA), PM0(C)*QM0(C))  / SUM(CP, PM0(CP)*QM0(CP))*100;
 PWETAB(RA,'BASE')$SUM(C, QE0(C)) = SUM(C$MCRA(C,RA), PWE0(C)*QE0(C)) / SUM(CP, PWE0(CP)*QE0(CP))*100;
 PWMTAB(RA,'BASE')$SUM(C, QM0(C)) = SUM(C$MCRA(C,RA), PWM0(C)*QM0(C)) / SUM(CP, PWM0(CP)*QM0(CP))*100;

*Factor employment and wages --------------------------------------------------
*------------------------------------------------------------------------------

 QFTAB(F,RA,SIMCUR)$SUM(A$MARA(A,RA), QFX(F,A,'BASE')) = (SUM(A$MARA(A,RA), QFX(F,A,SIMCUR))/SUM(A$MARA(A,RA), QFX(F,A,'BASE'))-1)*100;
 QFTAB(F,RA,'BASE')$SUM(A, QF0(F,A)) = SUM(A$MARA(A,RA), QF0(F,A)) / SUM(A, QF0(F,A))*100;

* WFX2(F,SIMCUR)$SUM(A, QFX(F,A,SIMCUR)) = SUM(A, WFX(F,SIMCUR)*WFDISTX(F,A,SIMCUR)*QFX(F,A,SIMCUR))/SUM(A, QFX(F,A,SIMCUR));
* WFXP2(F,SIMCUR)$WFX2(F,'BASE') = (WFX2(F,SIMCUR) /  WFX2(F,'BASE') -1 )*100;
* WFXP2(F,'BASE') =  WFX2(F,'BASE');

 QFSTAB(LA,SIMCUR)$SUM(F$MFLA(F,LA), QFSX(F,'BASE')) = (SUM(F$MFLA(F,LA), QFSX(F,SIMCUR))/SUM(F$MFLA(F,LA), QFSX(F,'BASE'))-1)*100;
 QFSTAB(LA,'BASE') = SUM(F$MFLA(F,LA), QFSX(F,'BASE'));

 WFTAB(LA,SIMCUR)$SUM((F,A)$MFLA(F,LA), QFX(F,A,SIMCUR))
         = SUM((F,A)$MFLA(F,LA), QFX(F,A,SIMCUR)*WFX(F,SIMCUR)*WFDISTX(F,A,SIMCUR)/CPIX(SIMCUR)) / SUM((F,A)$MFLA(F,LA), QFX(F,A,SIMCUR));
 WFTAB(LA,SIMCUR)$WFTAB(LA,'BASE') = (WFTAB(LA,SIMCUR)/WFTAB(LA,'BASE')-1)*100;
 WFTAB(LA,'BASE')$SUM((F,A)$MFLA(F,LA), QF0(F,A))
         = SUM((F,A)$MFLA(F,LA), QF0(F,A)*WF0(F)*WFDIST0(F,A)) / SUM((F,A)$MFLA(F,LA), QF0(F,A));

 YFTAB2(LA,SIMCUR)$SUM(F$MFLA(F,LA), QFSX(F,SIMCUR)) = SUM(F$MFLA(F,LA), YFX(F,SIMCUR)/CPIX(SIMCUR)) / SUM(F$MFLA(F,LA), QFSX(F,SIMCUR));
 YFTAB2(LA,SIMCUR)$YFTAB2(LA,'BASE') = (YFTAB2(LA,SIMCUR) / YFTAB2(LA,'BASE')-1)*100;
 YFTAB2(LA,'BASE')$SUM(F$MFLA(F,LA), QFS0(F)) = SUM(F$MFLA(F,LA), YF0(F)) / SUM(F$MFLA(F,LA), QFS0(F));

*New structural base table ----------------------------------------------------
*------------------------------------------------------------------------------

 STRUCBASE2(RA,'VAshr')  = sSHARE(RA,'BASE');
 STRUCBASE2(RA,'PRDshr') = SUM(A$MARA(A,RA), PA0(A)*(1-tva0(A))*QA0(A)) / SUM(A, PA0(A)*(1-tva0(A))*QA0(A)) * 100;
 STRUCBASE2(RA,'EMPshr') = SUM((FLAB,A)$MARA(A,RA), QF0(FLAB,A)) / SUM((FLAB,A), QF0(FLAB,A)) * 100;
 STRUCBASE2(RA,'EXPshr') = SUM(C$MCRA(C,RA), pwe0(C)*EXR0*QE0(C)) / SUM(C, pwe0(C)*EXR0*QE0(C)) * 100;
 STRUCBASE2(RA,'IMPshr') = SUM(C$MCRA(C,RA), pwm0(C)*EXR0*QM0(C)) / SUM(C, pwm0(C)*EXR0*QM0(C)) * 100;
 STRUCBASE2(RA,'EXP-OUTshr')$SUM(C$MCRA(C,RA), PX0(C)*QX0(C)) = SUM(C$MCRA(C,RA), PE0(C)*EXR0*QE0(C)) / SUM(C$MCRA(C,RA), PX0(C)*QX0(C)) * 100;
 STRUCBASE2(RA,'IMP-DEMshr')$SUM(C$MCRA(C,RA), PQ0(C)*(1-tq0(C))*QQ0(C)) = SUM(C$MCRA(C,RA), PM0(C)*EXR0*QM0(C)) / SUM(C$MCRA(C,RA), PQ0(C)*(1-tq0(C))*QQ0(C)) * 100;
 STRUCBASE2('sGDP','VAshr')  = SUM(RA$(NOT RAG(RA)), STRUCBASE2(RA,'VAshr') );
 STRUCBASE2('sGDP','PRDshr') = SUM(RA$(NOT RAG(RA)), STRUCBASE2(RA,'PRDshr'));
 STRUCBASE2('sGDP','EMPshr') = SUM(RA$(NOT RAG(RA)), STRUCBASE2(RA,'EMPshr'));
 STRUCBASE2('sGDP','EXPshr') = SUM(RA$(NOT RAG(RA)), STRUCBASE2(RA,'EXPshr'));
 STRUCBASE2('sGDP','IMPshr') = SUM(RA$(NOT RAG(RA)), STRUCBASE2(RA,'IMPshr'));
 STRUCBASE2('sGDP','EXP-OUTshr')$SUM(C, PX0(C)*QX0(C)) = SUM(C, PE0(C)*EXR0*QE0(C)) / SUM(C, PX0(C)*QX0(C)) * 100;
 STRUCBASE2('sGDP','IMP-DEMshr')$SUM(C, PQ0(C)*(1-tq0(C))*QQ0(C)) = SUM(C, PM0(C)*EXR0*QM0(C)) / SUM(C, PQ0(C)*(1-tq0(C))*QQ0(C)) * 100;

*Household income and expenditure tables --------------------------------------
*------------------------------------------------------------------------------

 QHTAB2(RA,SIMCUR) = SUM((H,C)$MCRA(C,RA), PQ0(C)*QHX(C,H,SIMCUR)) + SUM((H,A,C)$MARA(A,RA), PXAC0(A,C)*QHAX(A,C,H,SIMCUR));
 QHTAB2(RA,SIMCUR)$QHTAB2(RA,'BASE') = (QHTAB2(RA,SIMCUR) / QHTAB2(RA,'BASE')-1) * 100;
 QHTAB2(RA,'BASE') = SUM((H,C)$MCRA(C,RA), PQ0(C)*QH0(C,H)) + SUM((H,A,C)$MARA(A,RA), PXAC0(A,C)*QHA0(A,C,H));
* QHTAB2(RA,SIMCUR)$SUM((H,C)$MCRA(C,RA), PQ0(C)*QH0(C,H)) = (SUM((H,C)$MCRA(C,RA), PQ0(C)*QHX(C,H,SIMCUR))/SUM((H,C)$MCRA(C,RA), PQ0(C)*QH0(C,H))-1)*100;
* QHTAB2(RA,'BASE')$SUM((H,C), PQ0(C)*QH0(C,H)) = SUM((H,C)$MCRA(C,RA), PQ0(C)*QH0(C,H))/SUM((H,C), PQ0(C)*QH0(C,H))*100;

* YITAB(INSDNG,SIMCUR)$YIX(INSDNG,'BASE') = ((YIX(INSDNG,SIMCUR)/CPIX(SIMCUR))/(YIX(INSDNG,'BASE')/CPIX('BASE'))-1)*100;
* YITAB(INSDNG,'BASE') = YI0(INSDNG)/CPIX('BASE');

 YITAB(HA,SIMCUR)$SUM(H$MHHA(H,HA), YIX(H,'BASE')/CPIX('BASE')) = (SUM(H$MHHA(H,HA), YIX(H,SIMCUR)/CPIX(SIMCUR)) / SUM(H$MHHA(H,HA), YIX(H,'BASE')/CPIX('BASE'))-1)*100;
 YITAB(HA,'BASE')$SUM(H$MHHA(H,HA), YI0(H)/CPI0) = SUM(H$MHHA(H,HA), YI0(H)/CPI0);

* QHTAB(H,SIMCUR) = SUM(C, PQX(C,'BASE')*QHX(C,H,SIMCUR)) + SUM((A,C), PXACX(A,C,'BASE')*QHAX(A,C,H,SIMCUR));

 QCTAB(HA,SIMCUR) = SUM((H,C)$MHHA(H,HA), PQ0(C)*QHX(C,H,SIMCUR)) + SUM((H,A,C)$MHHA(H,HA), PXAC0(A,C)*QHAX(A,C,H,SIMCUR));
 QCTAB(HA,SIMCUR)$QCTAB(HA,'BASE') = (QCTAB(HA,SIMCUR)/QCTAB(HA,'BASE')-1)*100;
 QCTAB(HA,'BASE') = SUM((H,C)$MHHA(H,HA), PQ0(C)*QH0(C,H)) + SUM((H,A,C)$MHHA(H,HA), PXAC0(A,C)*QHA0(A,C,H));
* QCTAB(HA,SIMCUR)$SUM((H,C)$MHHA(H,HA), PQ0(C)*QHX(C,H,'BASE')) = (SUM((H,C)$MHHA(H,HA), PQ0(C)*QHX(C,H,SIMCUR)) / SUM((H,C)$MHHA(H,HA), PQ0(C)*QHX(C,H,'BASE')) -1)*100;
* QCTAB(HA,'BASE') = SUM((H,C)$MHHA(H,HA), PQ0(C)*QH0(C,H));


*Tax tables -------------------------------------------------------------------
*------------------------------------------------------------------------------

 TAXTAB(RA,'tIMPshr') = QMTAB(RA,'BASE');
 TAXTAB(RA,'tIMPtar')$SUM(C$MCRA(C,RA), QM0(C)) = SUM(C$MCRA(C,RA), tm0(C) * PWM0(C)*EXR0*QM0(C)  / SUM(CP$(MCRA(C,RA) AND MCRA(CP,RA)), PWM0(CP)*EXR0*QM0(CP)))*100;
 TAXTAB(RA,'tIMPrev') = TAXTAB(RA,'tIMPtar')/100 * SUM(C$MCRA(C,RA), PWM0(C)*EXR0*QM0(C));
 TAXTAB(RA,'tIMPrev')$TAXTAB('sGDP','tIMPrev') = TAXTAB(RA,'tIMPrev') / TAXTAB('sGDP','tIMPrev') *100;
 TAXTAB(RA,'tEXPshr') = QETAB(RA,'BASE');
 TAXTAB(RA,'tEXPtax')$SUM(C$MCRA(C,RA), QE0(C)) = SUM(C$MCRA(C,RA), te0(C) * PWE0(C)*EXR0*QE0(C)  / SUM(CP$(MCRA(C,RA) AND MCRA(CP,RA)), PWE0(CP)*EXR0*QE0(CP)))*100;
 TAXTAB(RA,'tEXPrev') = TAXTAB(RA,'tEXPtax')/100 * SUM(C$MCRA(C,RA), PWE0(C)*EXR0*QE0(C));
 TAXTAB(RA,'tEXPrev')$TAXTAB('sGDP','tEXPrev') = TAXTAB(RA,'tEXPrev') / TAXTAB('sGDP','tEXPrev') *100;
 TAXTAB(RA,'tACTshr') = SUM(A$MARA(A,RA), PA0(A)*QA0(A)) / SUM(AP, PA0(AP)*QA0(AP))*100;
 TAXTAB(RA,'tACTtax')$SUM(A$MARA(A,RA), QA0(A)) = SUM(A$MARA(A,RA), ta0(A) * PA0(A)*QA0(A)  / SUM(AP$(MARA(A,RA) AND MARA(AP,RA)), PA0(AP)*QA0(AP)))*100;
 TAXTAB(RA,'tACTrev') = TAXTAB(RA,'tACTtax')/100 * SUM(A$MARA(A,RA), PA0(A)*QA0(A));
 TAXTAB(RA,'tACTrev')$TAXTAB('sGDP','tACTrev') = TAXTAB(RA,'tACTrev') / TAXTAB('sGDP','tACTrev') *100;

 TAXTOT('DTAX-HHD-RATE',INSDNG,SIMCUR) = TINSX(INSDNG,SIMCUR)*100;
 TAXTOT('DTAX-HHD-VALUE',INSDNG,SIMCUR) = TINSX(INSDNG,SIMCUR)*YIX(INSDNG,SIMCUR);


*Ensure small shares for nontraded commodities (reporting only)
 QFTAB(F,RA,SIM)$(ABS(QFTAB(F,RA,SIM)) LT 1E-6)          = 0.00000001;
 QETAB(RA,SIM)$(ABS(QETAB(RA,SIM)) LT 1E-6)              = 0.00000001;
 QMTAB(RA,SIM)$(ABS(QMTAB(RA,SIM)) LT 1E-6)              = 0.00000001;
 PXTAB(RA,SIM)$(ABS(PXTAB(RA,SIM)) LT 1E-6)              = 0.00000001;
 PQTAB(RA,SIM)$(ABS(PQTAB(RA,SIM)) LT 1E-6)              = 0.00000001;
 PETAB(RA,SIM)$(ABS(PETAB(RA,SIM)) LT 1E-6)              = 0.00000001;
 PMTAB(RA,SIM)$(ABS(PMTAB(RA,SIM)) LT 1E-6)              = 0.00000001;
 PWETAB(RA,SIM)$(ABS(PWETAB(RA,SIM)) LT 1E-6)            = 0.00000001;
 PWMTAB(RA,SIM)$(ABS(PWMTAB(RA,SIM)) LT 1E-6)            = 0.00000001;
 SGROWTH(RA,SIM)$(ABS(SGROWTH(RA,SIM)) LT 1E-6)          = 0.00000001;
 SCONTR(RA,SIM)$(ABS(SCONTR(RA,SIM)) LT 1E-6)            = 0.00000001;
 EVTAB(H,SIM)$(ABS(EVTAB(H,SIM)) LT 1E-6)                = 0.00000001;
 EVTAB('TOTAL',SIM)$(ABS(EVTAB('TOTAL',SIM)) LT 1E-6)    = 0.00000001;
 QHTAB2(RA,SIM)$(ABS(QHTAB2(RA,SIM)) LT 1E-6)            = 0.00000001;
 YITAB(HA,SIM)$(ABS(YITAB(HA,SIM)) LT 1E-6)              = 0.00000001;
 WFTAB(LA,SIM)$(ABS(WFTAB(LA,SIM)) LT 1E-6)              = 0.00000001;
 QFSTAB(LA,SIM)$(ABS(QFSTAB(LA,SIM)) LT 1E-6)            = 0.00000001;
 QFXP(F,A,SIM)$(ABS(QFXP(F,A,SIM)) LT 1E-6)              = 0.00000001;
 WFDISTXP(F,A,SIM)$(ABS(WFDISTXP(F,A,SIM)) LT 1E-6)      = 0.00000001;
 YFTAB2(LA,SIM)$(ABS(YFTAB2(LA,SIM) ) LT 1E-6)           = 0.00000001;
 MACROTAB(SIND,SIM)$(ABS(MACROTAB(SIND,SIM)) LT 1E-6)    = 0.00000001;
 GDPTAB1P(KGDP,IGDP,SIM)$(ABS(GDPTAB1P(KGDP,IGDP,SIM)) LT 1E-6) = 0.00000001;
 STRUCBASE2(RA,STRCOL)$(ABS(STRUCBASE2(RA,STRCOL)) LT 1E-6) = 0.00000001;
 TAXTAB(RA,TAXAC)$(ABS(TAXTAB(RA,TAXAC)) LT 1E-6)        = 0.00000001;
* WFXP2(F,SIM)$(ABS(WFXP2(F,SIM)) LT 1E-6)                = 0.00000001;
 TAXTOT('DTAX-HHD-RATE',INSDNG,SIM)$(ABS(TAXTOT('DTAX-HHD-RATE',INSDNG,SIM)) LT 1E-6)   = 0.00000001;
 TAXTOT('DTAX-HHD-VALUE',INSDNG,SIM)$(ABS(TAXTOT('DTAX-HHD-VALUE',INSDNG,SIM)) LT 1E-6) = 0.00000001;


*Prepare and display reporting tables -----------------------------------------
*------------------------------------------------------------------------------

OPTION
 QETAB:2:1:1,   QMTAB:2:1:1
 sVALUE:1:1:1,  sSHARE:3:1:1,  sGROWTH:2:1:1,  sCONTR:3:1:1
 dVALUE:3:1:1,  dSHARE:2:1:1,  dGROWTH:2:1:1,  dCONTR:2:1:1
 PXTAB:3:1:1,   PETAB:3:1:1,   PMTAB:3:1:1,    PQTAB:3:1:1
;

PARAMETER XLTEST;
execute_unload "0output.gdx" TAXTAB STRUCBASE2 MACROTAB GDPTAB1P SGROWTH SCONTR QETAB QMTAB PXTAB PQTAB PETAB PMTAB PWETAB PWMTAB YFTAB2 WFTAB QFSTAB QFTAB QCTAB QHTAB2 YITAB WFDISTXP  TAXTOT
execute 'xlstalk.exe -m 0output.xlsx';
 XLTEST = ERRORLEVEL;
IF(XLTEST = 1,
execute 'xlstalk.exe -c 0output.xlsx';
);
IF(XLTEST = 2,
execute 'xlstalk.exe -s 0output.xlsx';
);
execute 'gdxxrw.exe i=0output.gdx o=0output.xlsx index=index!g6' ;
execute 'xlstalk.exe -o 0output.xlsx';
DISPLAY XLTEST;

$exit

execute_unload "0output.gdx" GDPTAB1P SGROWTH QETAB QMTAB EVTAB QHTAB2 SCONTR PXTAB PQTAB PETAB PMTAB PWETAB PWMTAB YITAB YFXP WFXP2 QFSXP QFTAB WFDISTXP MACROTAB TAXTOT TAXTAB STRUCBASE2
execute 'gdxxrw.exe i=0output.gdx o=0output.xlsx index=index!g6'


