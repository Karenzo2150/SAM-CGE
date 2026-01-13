$STITLE Input file: REPLOOP.INC. Definitions of report parameters. Standard CGE modeling system, Version 1.01

*==========================================================
*Variable values===========================================
*==========================================================

CPIX(%1)        = CPI.L;
DPIX(%1)        = DPI.L;
DMPSX(%1)       = DMPS.L;
DTINSX(%1)      = DTINS.L;
EGX(%1)         = EG.L;
EHX(H,%1)       = EH.L(H);
EXRX(%1)        = EXR.L;
FSAVX(%1)       = FSAV.L;
GADJX(%1)       = GADJ.L;
GOVSHRX(%1)     = GOVSHR.L;
GSAVX(%1)       = GSAV.L;
IADJX(%1)       = IADJ.L;
INVSHRX(%1)     = INVSHR.L;
MPSX(INS,%1)    = MPS.L(INS);
MPSADJX(%1)     = MPSADJ.L;
PAX(A,%1)       = PA.L(A);
PDDX(C,%1)      = PDD.L(C);
PDSX(C,%1)      = PDS.L(C);
PEX(C,%1)       = PE.L(C);
PINTAX(A,%1)    = PINTA.L(A);
PMX(C,%1)       = PM.L(C);
PQX(C,%1)       = PQ.L(C);
PVAX(A,%1)      = PVA.L(A);
PWEX(C,%1)      = PWE.L(C);
PWMX(C,%1)      = PWM.L(C);
PXX(C,%1)       = PX.L(C);
PXACX(A,C,%1)   = PXAC.L(A,C);
QAX(A,%1)       = QA.L(A);
QDX(C,%1)       = QD.L(C);
QEX(C,%1)       = QE.L(C);
QFX(F,A,%1)     = QF.L(F,A);
QFSX(F,%1)      = QFS.L(F);
QGX(C,%1)       = QG.L(C);
QHX(C,H,%1)     = QH.L(C,H);
QHAX(A,C,H,%1)  = QHA.L(A,C,H);
QINTX(C,A,%1)   = QINT.L(C,A);
QINTAX(A,%1)    = QINTA.L(A);
QINVX(C,%1)     = QINV.L(C);
QMX(C,%1)       = QM.L(C);
QQX(C,%1)       = QQ.L(C);
QTX(C,%1)       = QT.L(C);
QVAX(A,%1)      = QVA.L(A);
QXX(C,%1)       = QX.L(C);
QXACX(A,C,%1)   = QXAC.L(A,C);
TABSX(%1)       = TABS.L;
TINSX(INS,%1)   = TINS.L(INS);
TINSADJX(%1)    = TINSADJ.L;
TRIIX(INS,INSP,%1) = TRII.L(INS,INSP);
WALRASX(%1)     = WALRAS.L;
WFX(F,%1)       = WF.L(F);
WFDISTX(F,A,%1) = WFDIST.L(F,A);
YFX(F,%1)       = YF.L(F);
YGX(%1)         = YG.L;
YIFX(INSD,F,%1) = YIF.L(INSD,F);
YIX(INSDNG,%1)  = YI.L(INSDNG);

*Computed activity-specific wage
WFAX(F,A,%1)    = WF.L(F)*WFDIST.L(F,A);


*==========================================================
*Budgets for SAM accounts==================================
*==========================================================

 SAMBUD('ACT',A,'INC',C,%1)        = PXAC.L(A,C)*theta(A,C)*QA.L(A);

 SAMBUD('ACT',A,'SPND',F,%1)       = WF.L(F)*WFDIST.L(F,A)*QF.L(F,A);
 SAMBUD('ACT',A,'SPND',C,%1)       = PQ.L(C)*QINT.L(C,A);
 SAMBUD('ACT',A,'SPND','VATAX',%1) = tva(A)*PVA.L(A)*QVA.L(A);
 SAMBUD('ACT',A,'SPND','ACTTAX',%1) = ta(A)*PA.L(A)*QA.L(A);

*========================

 SAMBUD('COM',C,'INC',H,%1)      = PQ.L(C)*QH.L(C,H)
                                   + SUM(A, PXAC.L(A,C)*QHA.L(A,C,H));
 SAMBUD('COM',C,'INC','GOV',%1)  = PQ.L(C)*QG.L(C);
 SAMBUD('COM',C,'INC','S-I',%1)  = PQ.L(C)*QINV.L(C);
 SAMBUD('COM',C,'INC','DSTK',%1) = PQ.L(C)*qdst(C);
 SAMBUD('COM',C,'INC','ROW',%1)  = EXR.L*pwe.L(C)*QE.L(C);
 SAMBUD('COM',C,'INC',A,%1)      = PQ.L(C)*QINT.L(C,A);
 SAMBUD('COM',CT,'INC','DUM',%1) = PQ.L(CT)*QT.L(CT);

 SAMBUD('COM',C,'SPND',A,%1)           = PXAC.L(A,C)*theta(A,C)*QA.L(A);
 SAMBUD('COM',C,'SPND','COMTAX',%1)    = tq(C)*PQ.L(C)*QQ.L(C);
 SAMBUD('COM',C,'SPND','IMPTAX',%1)    = tm(C)*EXR.L*pwm.L(C)*QM.L(C);
 SAMBUD('COM',C,'SPND','ROW',%1)       = EXR.L*pwm.L(C)*QM.L(C);
 SAMBUD('COM',C,'SPND','EXPTAX',%1)    = te(C)*EXR.L*pwe.L(C)*QE.L(C);
 SAMBUD('COM',C,'SPND','TRNCSTDOM',%1) = SUM(CT, PQ.L(CT)*icd(CT,C)*QD.L(C));
 SAMBUD('COM',C,'SPND','TRNCSTIMP',%1) = SUM(CT, PQ.L(CT)*icm(CT,C)*QM.L(C));
 SAMBUD('COM',C,'SPND','TRNCSTEXP',%1) = SUM(CT, PQ.L(CT)*ice(CT,C)*QE.L(C));

*========================

 SAMBUD('FAC',F,'INC',A,%1)              = WF.L(F)*WFDIST.L(F,A)*QF.L(F,A);
 SAMBUD('FAC',F,'SPND',INSD,%1)          = YIF.L(INSD,F);
 SAMBUD('FAC',F,'SPND','ROW',%1)         = EXR.L*trnsfr('ROW',F);
 SAMBUD('FAC',F,'SPND','FACTAX',%1)
*   = tf(F)*(SUM(A, WF.L(F)*WFDIST.L(F,A)*QF.L(F,A)) - EXR.L*trnsfr('ROW',F));
   = tf(F)*YF.L(F);

*SUM(FD, tf(FD)*YF(FD))

*========================

 SAMBUD('INSDNG',INSDNG,'INC',F,%1)            = YIF.L(INSDNG,F);
 SAMBUD('INSDNG',INSDNG,'INC',INSDNGP,%1)      = TRII.L(INSDNG,INSDNGP);
 SAMBUD('INSDNG',INSDNG,'INC','GOV',%1)        = trnsfr(INSDNG,'GOV')*CPI.L;
 SAMBUD('INSDNG',INSDNG,'INC','ROW',%1)        = trnsfr(INSDNG,'ROW')*EXR.L;

 SAMBUD('INSDNG',H,'SPND',C,%1)
   = PQ.L(C)*QH.L(C,H) + SUM(A, PXAC.L(A,C)*QHA.L(A,C,H));
 SAMBUD('INSDNG',INSDNGP,'SPND',INSDNG,%1)   = TRII.L(INSDNG,INSDNGP);
 SAMBUD('INSDNG',INSDNG,'SPND','ROW',%1)     = EXR.L*trnsfr('ROW',INSDNG);

* SAMBUD('INSDNG',INSDNG,'SPND','S-I',%1)
*    = MPS.L(INSDNG)*((1 - TINS.L(INSDNG))*YI.L(INSDNG) - EXR.L*trnsfr('ROW',INSDNG));

*ME 10/10/02
 SAMBUD('INSDNG',INSDNG,'SPND','S-I',%1)
    = MPS.L(INSDNG)*(1 - TINS.L(INSDNG))*YI.L(INSDNG);

 SAMBUD('INSDNG',INSDNG,'SPND','INSTAX',%1)    = TINS.L(INSDNG)*YI.L(INSDNG);

*========================

 SAMBUD('GOV','DUM','INC','INSTAX',%1)
  = SUM(INSDNG, TINS.L(INSDNG)*YI.L(INSDNG));

 SAMBUD('GOV','DUM','INC','FACTAX',%1)
  = SUM(F, tf(F)*YF.L(F));

 SAMBUD('GOV','DUM','INC','VATAX',%1)
  = SUM(A, tva(A)*PVA.L(A)*QVA.L(A));

 SAMBUD('GOV','DUM','INC','ACTTAX',%1)
  = SUM(A, ta(A)*PA.L(A)*QA.L(A));

 SAMBUD('GOV','DUM','INC','IMPTAX',%1)
  = SUM(C, tm(C)*pwm.L(C)*QM.L(C))*EXR.L;

 SAMBUD('GOV','DUM','INC','EXPTAX',%1)
  = SUM(C, te(C)*pwe.L(C)*QE.L(C))*EXR.L;

 SAMBUD('GOV','DUM','INC','COMTAX',%1) = SUM(C, tq(C)*PQ.L(C)*QQ.L(C));

 SAMBUD('GOV','DUM','INC',F,%1) = YIF.L('GOV',F);

 SAMBUD('GOV','DUM','INC','ROW',%1)  = trnsfr('GOV','ROW')*EXR.L;


 SAMBUD('GOV','DUM','SPND',C,%1)     = PQ.L(C)*QG.L(C);
 SAMBUD('GOV','DUM','SPND',INSD,%1)  = trnsfr(INSD,'GOV')*CPI.L;
 SAMBUD('GOV','DUM','SPND','S-I',%1) = GSAV.L;

*========================
*ME 10/10/02
* SAMBUD('SAVINV','DUM','INC',INSDNG,%1)
*  = MPS.L(INSDNG)*((1 - TINS.L(INSDNG))*YI.L(INSDNG) - EXR.L*trnsfr('ROW',INSDNG));

 SAMBUD('SAVINV','DUM','INC',INSDNG,%1)
  = MPS.L(INSDNG)*(1 - TINS.L(INSDNG))*YI.L(INSDNG);

 SAMBUD('SAVINV','DUM','INC','GOV',%1)     = GSAV.L;
 SAMBUD('SAVINV','DUM','INC','ROW',%1)     = EXR.L*FSAV.L;

 SAMBUD('SAVINV','DUM','SPND',C,%1)      = PQ.L(C)*QINV.L(C);
 SAMBUD('SAVINV','DUM','SPND','DSTK',%1) = SUM(C, PQ.L(C)*qdst(C));

*========================

 SAMBUD('INSTAX','DUM','INC',INSDNG,%1)   = TINS.L(INSDNG)*YI.L(INSDNG);
 SAMBUD('INSTAX','DUM','SPND','GOV',%1)   = SUM(INSDNG, TINS.L(INSDNG)*YI.L(INSDNG));

 SAMBUD('FACTAX','DUM','INC',F,%1)        = tf(F)*YF.L(F);
 SAMBUD('FACTAX','DUM','SPND','GOV',%1)   = SUM(F, tf(F)*YF.L(F));

 SAMBUD('VATAX','DUM','INC',A,%1)         = tva(A)*PVA.L(A)*QVA.L(A);
 SAMBUD('VATAX','DUM','SPND','GOV',%1)    = SUM(A, tva(A)*PVA.L(A)*QVA.L(A));

 SAMBUD('ACTTAX','DUM','INC',A,%1)        = ta(A)*PA.L(A)*QA.L(A);
 SAMBUD('ACTTAX','DUM','SPND','GOV',%1)   = SUM(A, ta(A)*PA.L(A)*QA.L(A));

 SAMBUD('COMTAX','DUM','INC',C,%1)        = tq(C)*QQ.L(C);
 SAMBUD('COMTAX','DUM','SPND','GOV',%1)   = SUM(C, tq(C)*QQ.L(C));

 SAMBUD('IMPTAX','DUM','INC',C,%1)        = tm(C)*pwm.L(C)*QM.L(C)*EXR.L;
 SAMBUD('IMPTAX','DUM','SPND','GOV',%1)   = SUM(C, tm(C)*pwm.L(C)*QM.L(C))*EXR.L;

 SAMBUD('EXPTAX','DUM','INC',C,%1)        = te(C)*pwe.L(C)*QE.L(C)*EXR.L;
 SAMBUD('EXPTAX','DUM','SPND','GOV',%1)   = SUM(C, te(C)*pwe.L(C)*QE.L(C))*EXR.L;

*========================

 SAMBUD('ROW','DUM','INC',C,%1)      = EXR.L*pwm.L(C)*QM.L(C);
 SAMBUD('ROW','DUM','INC',F,%1)      = EXR.L*trnsfr('ROW',F);
 SAMBUD('ROW','DUM','INC',INS,%1)    = EXR.L*trnsfr('ROW',INS);

 SAMBUD('ROW','DUM','SPND',C,%1)     = EXR.L*pwe.L(C)*QE.L(C);
 SAMBUD('ROW','DUM','SPND',INS,%1)   = EXR.L*trnsfr(INS,'ROW');
 SAMBUD('ROW','DUM','SPND','S-I',%1) = EXR.L*FSAV.L;

*========================

 SAMBUD(SAC,AC,'INC','TOTAL',%1)  = SUM(ACNT, SAMBUD(SAC,AC,'INC',ACNT,%1));
 SAMBUD(SAC,AC,'SPND','TOTAL',%1) = SUM(ACNT, SAMBUD(SAC,AC,'SPND',ACNT,%1));


*==========================================================
*National accounts data====================================
*==========================================================

 GDPTAB1('NOMINAL','PRVCON',%1)
   =  SUM((C,H), PQ.L(C)*QH.L(C,H))
      + SUM((A,C,H), PXAC.L(A,C)*QHA.L(A,C,H));

 GDPTAB1('REAL','PRVCON',%1)
   =  SUM((C,H), PQX(C,'BASE')*QH.L(C,H))
      + SUM((A,C,H), PXACX(A,C,'BASE')*QHA.L(A,C,H));

 GDPTAB1('NOMINAL','FIXINV',%1)  = SUM(C, PQ.L(C)*QINV.L(C));
 GDPTAB1('REAL','FIXINV',%1)     = SUM(C, PQX(C,'BASE')*QINV.L(C));

 GDPTAB1('NOMINAL','DSTOCK',%1)   = SUM(C, PQ.L(C)*QDST(C));
 GDPTAB1('REAL','DSTOCK',%1)      = SUM(C, PQX(C,'BASE')*QDST(C));

 GDPTAB1('NOMINAL','GOVCON',%1)  = SUM(C, PQ.L(C)*QG.L(C));
 GDPTAB1('REAL','GOVCON',%1)     = SUM(C, PQX(C,'BASE')*QG.L(C));

 GDPTAB1('NOMINAL','EXPORTS',%1) = SUM(CE, PWE.L(CE)*EXR.L*QE.L(CE));
 GDPTAB1('REAL','EXPORTS',%1)    = SUM(CE, PWEX(CE,'BASE')*EXR0*QE.L(CE));

 GDPTAB1('NOMINAL','IMPORTS',%1) = -SUM(CM, PWM.L(CM)*EXR.L*QM.L(CM));
 GDPTAB1('REAL','IMPORTS',%1)    = -SUM(CM, PWMX(CM,'BASE')*EXR0*QM.L(CM));

 GDPTAB1('NOMINAL','GDPMP',%1) = SUM(IGDP2, GDPTAB1('NOMINAL',IGDP2,%1));
 GDPTAB1('REAL','GDPMP',%1)    = SUM(IGDP2, GDPTAB1('REAL',IGDP2,%1));

 GDPTAB1('NOMINAL','ABSORP',%1)
  = GDPTAB1('NOMINAL','GDPMP',%1) - GDPTAB1('NOMINAL','IMPORTS',%1)
    - GDPTAB1('NOMINAL','EXPORTS',%1);

 GDPTAB1('REAL','ABSORP',%1)
  = GDPTAB1('REAL','GDPMP',%1) - GDPTAB1('REAL','IMPORTS',%1)
    - GDPTAB1('REAL','EXPORTS',%1);

 GDPTAB1('NOMINAL','GDPFC2',%1) = SUM(A, PVA.L(A)*(1-tva(A))*QVA.L(A));
 GDPTAB1('REAL','GDPFC2',%1)    = SUM(A, PVAX(A,'BASE')*(1-tva0(A))*QVA.L(A));

 GDPTAB1('NOMINAL','NETITAX',%1) =
            SUM(A, ta(A)*PA.L(A)*QA.L(A))
          + SUM(A, tva(A)*PVA.L(A)*QVA.L(A))
          + SUM(CM, tm(CM)*PWM.L(CM)*EXR.L*QM.L(CM))
          + SUM(CE, te(CE)*PWE.L(CE)*EXR.L*QE.L(CE))
          + SUM(C, tq(C)*PQ.L(C)*QQ.L(C));

 GDPTAB1('REAL','NETITAX',%1) =
            SUM(A, ta0(A)*PA0(A)*QA.L(A))
          + SUM(A, tva0(A)*PVA0(A)*QVA.L(A))
          + SUM(CM, tm0(CM)*PWM0(CM)*EXR0*QM.L(CM))
          + SUM(CE, te0(CE)*PWE0(CE)*EXR0*QE.L(CE))
          + SUM(C, tq0(C)*PQ0(C)*QQ.L(C));


 GDPTAB1('NOMINAL','GDPMP2',%1)
  = GDPTAB1('NOMINAL','GDPFC2',%1) + GDPTAB1('NOMINAL','NETITAX',%1);

 GDPTAB1('NOMSHARE',IGDP,%1)$GDPTAB1('NOMINAL','GDPMP',%1)
  = 100*GDPTAB1('NOMINAL',IGDP,%1)/GDPTAB1('NOMINAL','GDPMP',%1);

 GDPTAB1('REALSHARE',IGDP,%1)$GDPTAB1('REAL','GDPMP',%1)
  = 100*GDPTAB1('REAL',IGDP,%1)/GDPTAB1('REAL','GDPMP',%1);

 GDPTAB1('DEFLATOR',IGDP,%1)$GDPTAB1('REAL',IGDP,%1)
  = 100*GDPTAB1('NOMINAL',IGDP,%1)/GDPTAB1('REAL',IGDP,%1);

*==================

 GDPTAB2('NOMINAL',A,%1)       = PVA.L(A)*(1-tva(A))*QVA.L(A);
 GDPTAB2('REAL',A,%1)          = PVAX(A,'BASE')*(1-tva0(A))*QVA.L(A);

 GDPTAB2('NOMINAL','TOTAL',%1) = SUM(A, GDPTAB2('NOMINAL',A,%1));
 GDPTAB2('REAL','TOTAL',%1)    = SUM(A, GDPTAB2('REAL',A,%1));

 GDPTAB2('NOMSHARE',A,%1)
  = 100*GDPTAB2('NOMINAL',A,%1)/GDPTAB2('NOMINAL','TOTAL',%1);

 GDPTAB2('REALSHARE',A,%1)
  = 100*GDPTAB2('REAL',A,%1)/GDPTAB2('REAL','TOTAL',%1);

 GDPTAB2('NOMSHARE','TOTAL',%1)  = SUM(A, GDPTAB2('NOMSHARE',A,%1));
 GDPTAB2('REALSHARE','TOTAL',%1) = SUM(A, GDPTAB2('REALSHARE',A,%1));

 GDPTAB2('DEFLATOR',A,%1)$GDPTAB2('REAL',A,%1)
  = 100*GDPTAB2('NOMINAL',A,%1)/GDPTAB2('REAL',A,%1);

 GDPTAB2('DEFLATOR','TOTAL',%1)$GDPTAB2('REAL','TOTAL',%1)
  = 100*GDPTAB2('NOMINAL','TOTAL',%1)/GDPTAB2('REAL','TOTAL',%1);


*==========================================================
*Closure information=======================================
*==========================================================

*Macro closures
 MACCLOS('S-I',%1) = SICLOS(%1);
 MACCLOS('GOV',%1) = GOVCLOS(%1);
 MACCLOS('ROW',%1) = ROWCLOS(%1);

*Factor closures
 FACCLOS(F,'FMOBFE',%1) = FMOBFE(F,%1);
 FACCLOS(F,'FACTFE',%1) = FACTFE(F,%1);
 FACCLOS(F,'FMOBUE',%1) = FMOBUE(F,%1);



*Gaps and solver reports=========================

 SAMBUDGAP(SAC,ACNT,%1)
  = ABS(SAMBUD(SAC,ACNT,'INC','TOTAL',%1) - SAMBUD(SAC,ACNT,'SPND','TOTAL',%1));

 SAMBUDGAP(SAC,'TOTAL',%1) = SUM(ACNT, SAMBUDGAP(SAC,ACNT,%1));

 GDPGAP(%1)
  =  ABS(GDPTAB1('NOMINAL','GDPMP',%1) - GDPTAB1('NOMINAL','GDPMP2',%1));


 SOLVEREP('MODEL-STATUS','MCP',%1)  = STANDCGE.MODELSTAT;
 SOLVEREP('SOLVER-STATUS','MCP',%1) = STANDCGE.SOLVESTAT;
 SOLVEREP('NUM-REDEFEQ','MCP',%1)   = STANDCGE.NUMREDEF;

 SOLVEREP('MODEL-STATUS','NLP',%1)  = NLPCGE.MODELSTAT;
 SOLVEREP('SOLVER-STATUS','NLP',%1) = NLPCGE.SOLVESTAT;


*Values are reset to zero to avoid using results from earlier solve in
*the definition of SOLVEREP FOR later solves.

 STANDCGE.MODELSTAT = 0;
 STANDCGE.SOLVESTAT = 0;
 STANDCGE.NUMREDEF  = 0;

 NLPCGE.MODELSTAT   = 0;
 NLPCGE.SOLVESTAT   = 0;
 NLPCGE.NUMREDEF    = 0;


ERRMPSEQ1(INSDNG,%1)
 $(
  ( (DMPS.UP - DMPS.LO GT 1.0E-6) OR (MPSADJ.UP - MPSADJ.LO GT 1.0E-6) )
 AND
  (ABS(mpsbar(INSDNG) - 1) LT 1.0E-6)
 AND
  (MPS01(INSDNG) EQ 1)
                                                               ) = 1;

*#*#*#*#*# THE END OF REPLOOP.INC #*#*#*#*
