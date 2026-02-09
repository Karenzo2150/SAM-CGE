$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2.4 (Sections 10-14): Save results between solves
 Store model parameter and variable values after each solution loop. Generate standard
 results paramerters typically used for model debugging. 

SECTIONS:
 2.4.10  Storing post-solution variable and parameter values
 2.4.11  Budgets for SAM accounts                               (SAMBUD)
 2.4.12  National accounts data                                 (GDPTAB1 | GDPTAB2)
 2.4.13  Closure information                                    (MACCLOSURES | FACCLOSURES)
 2.4.14  Solver reports                                         (SOLVEREP)
$offtext


*------------------------------------------------------------------
*2.4.10  Storing post-solution variable and parameter values
*------------------------------------------------------------------

*Parameter values
 x_alphaf(F,A,%1)      = alphaf(F,A);
 x_alphava(A,%1)       = alphava(A);      
 x_betah(A,H,%1)       = betah(A,H);      
 x_betam(C,H,%1)       = betam(C,H);      
 x_gammah(A,H,%1)      = gammah(A,H);     
 x_gammam(C,H,%1)      = gammam(C,H);     
 x_pop(H,%1)           = hpop(H);         
 x_icd(C,CP,%1)        = icd(C,CP);       
 x_ice(C,CP,%1)        = ice(C,CP);       
 x_icm(C,CP,%1)        = icm(C,CP);       
 x_pwe(C,%1)           = pwe(C);          
 x_pwm(C,%1)           = pwm(C);          
 x_qbarg(C,%1)         = qbarg(C);        
 x_qbarinv(C,%1)       = qbarinv(C);      
 x_qdst(C,%1)          = qdst(C);         
 x_shif(AC,ACP,%1)     = shif(AC,ACP);    
 x_shii(AC,ACP,%1)     = shii(AC,ACP);    
 x_trnsf(F,INS,%1)     = trnsf(F,INS);
 x_trnsi(INS,INSP,%1)  = trnsi(INS,INSP);  

*Variable values 
 x_CPI(%1)             = CPI.L;
 x_DMPS(%1)            = DMPS.L;
 x_DPI(%1)             = DPI.L;
 x_DTA(%1)             = DTA.L;
 x_DTE(%1)             = DTE.L;
 x_DTF(%1)             = DTF.L;
 x_DTI(%1)             = DTI.L;       
 x_DTM(%1)             = DTM.L;         
 x_DTQ(%1)             = DTQ.L;         
 x_DTV(%1)             = DTV.L;        
 x_EG(%1)              = EG.L;
 x_EH(H,%1)            = EH.L(H);
 x_EXR(%1)             = EXR.L;
 x_FSAV(%1)            = FSAV.L;
 x_GADJ(%1)            = GADJ.L;
 x_GOVSHR(%1)          = GOVSHR.L;
 x_GSAV(%1)            = GSAV.L;
 x_IADJ(%1)            = IADJ.L;
 x_INVSHR(%1)          = INVSHR.L;
 x_MPS(INS,%1)         = MPS.L(INS);
 x_MPSADJ(%1)          = MPSADJ.L;      
 x_PA(A,%1)            = PA.L(A);
 x_PDD(C,%1)           = PDD.L(C);
 x_PDS(C,%1)           = PDS.L(C);
 x_PE(C,%1)            = PE.L(C);
 x_PM(C,%1)            = PM.L(C);
 x_PINTA(A,%1)         = PINTA.L(A);
 x_PQ(C,%1)            = PQ.L(C);
 x_PSAV(%1)            = PSAV.L;
 x_PVA(A,%1)           = PVA.L(A);
 x_PX(C,%1)            = PX.L(C);
 x_PXAC(A,C,%1)        = PXAC.L(A,C);
 x_QA(A,%1)            = QA.L(A);
 x_QD(C,%1)            = QD.L(C);
 x_QE(C,%1)            = QE.L(C);
 x_QF(F,A,%1)          = QF.L(F,A);
 x_QFS(F,%1)           = QFS.L(F);
 x_QG(C,%1)            = QG.L(C);
 x_QH(C,H,%1)          = QH.L(C,H);
 x_QHA(A,H,%1)         = QHA.L(A,H);
 x_QINT(C,A,%1)        = QINT.L(C,A);
 x_QINTA(A,%1)         = QINTA.L(A);
 x_QINV(C,%1)          = QINV.L(C);
 x_QM(C,%1)            = QM.L(C);
 x_QQ(C,%1)            = QQ.L(C);
 x_QT(C,%1)            = QT.L(C);
 x_QVA(A,%1)           = QVA.L(A);
 x_QX(C,%1)            = QX.L(C);
 x_QXAC(A,C,%1)        = QXAC.L(A,C);
 x_TA(A,%1)            = TA.L(A);        
 x_TAADJ(%1)           = TAADJ.L;
 x_TABS(%1)            = TABS.L;
 x_TE(C,%1)            = TE.L(C);
 x_TEADJ(%1)           = TEADJ.L;
 x_TF(F,%1)            = TF.L(F);
 x_TFADJ(%1)           = TFADJ.L;
 x_TI(INS,%1)          = TI.L(INS);
 x_TIADJ(%1)           = TIADJ.L;
 x_TM(C,%1)            = TM.L(C);
 x_TMADJ(%1)           = TMADJ.L;
 x_TRII(INS,INSP,%1)   = TRII.L(INS,INSP);
 x_TQ(C,%1)            = TQ.L(C);
 x_TQADJ(%1)           = TQADJ.L;
 x_TV(A,%1)            = TV.L(A);
 x_TVADJ(%1)           = TVADJ.L;
 x_WALRAS(%1)          = WALRAS.L;
 x_WF(F,%1)            = WF.L(F);
 x_WFDIST(F,A,%1)      = WFDIST.L(F,A);
 x_YF(F,%1)            = YF.L(F);
 x_YG(%1)              = YG.L;
 x_YI(INS,%1)          = YI.L(INS);
 x_YIF(INS,F,%1)       = YIF.L(INS,F);
 
 
*------------------------------------------------------------------
*2.4.11  Budgets for SAM accounts
*------------------------------------------------------------------

*Activity accounts.
 x_SAMBUD('ACT',A,'INC',C,%1)                 = PXAC.L(A,C)*theta(A,C)*(QA.L(A)-SUM(H, QHA.L(A,H)));
 x_SAMBUD('ACT',A,'INC',H,%1)                 = PA.L(A)*QHA.L(A,H);
 x_SAMBUD('ACT',A,'SPND',F,%1)                = WF.L(F)*WFDIST.L(F,A)*QF.L(F,A);
 x_SAMBUD('ACT',A,'SPND',C,%1)                = PQ.L(C)*QINT.L(C,A);
 x_SAMBUD('ACT',A,'SPND','VATTAX',%1)         = TV.L(A)*PVA.L(A)*QVA.L(A);
 x_SAMBUD('ACT',A,'SPND','ACTTAX',%1)         = TA.L(A)*PA.L(A)*QA.L(A);

*Commodity accounts.
 x_SAMBUD('COM',C,'INC',H,%1)                 = PQ.L(C)*QH.L(C,H);
 x_SAMBUD('COM',C,'INC',GV,%1)                = PQ.L(C)*QG.L(C);
 x_SAMBUD('COM',C,'INC',SI,%1)                = PQ.L(C)*QINV.L(C);
 x_SAMBUD('COM',C,'INC',STK,%1)               = PQ.L(C)*qdst(C);
 x_SAMBUD('COM',C,'INC',RW,%1)                = EXR.L*pwe(C) * QE.L(C);
 x_SAMBUD('COM',C,'INC',A,%1)                 = PQ.L(C)*QINT.L(C,A);
 x_SAMBUD('COM',C,'INC','DUM',%1)             = PQ.L(C)*QT.L(C);
 x_SAMBUD('COM',C,'SPND',A,%1)                = PXAC.L(A,C)*theta(A,C)*(QA.L(A)-SUM(H, QHA.L(A,H)));
 x_SAMBUD('COM',C,'SPND','COMTAX',%1)         = TQ.L(C)*PQ.L(C)*QQ.L(C);
 x_SAMBUD('COM',C,'SPND','IMPTAX',%1)         = TM.L(C)*EXR.L*pwm(C)*QM.L(C);
 x_SAMBUD('COM',C,'SPND',RW,%1)               = EXR.L*pwm(C)*QM.L(C);
 x_SAMBUD('COM',C,'SPND','EXPTAX',%1)         = TE.L(C)*EXR.L*pwe(C)*QE.L(C);
 x_SAMBUD('COM',C,'SPND',CTD,%1)              = SUM(CT, PQ.L(CT)*icd(CT,C)*QD.L(C));
 x_SAMBUD('COM',C,'SPND',CTM,%1)              = SUM(CT, PQ.L(CT)*icm(CT,C)*QM.L(C));
 x_SAMBUD('COM',C,'SPND',CTE,%1)              = SUM(CT, PQ.L(CT)*ice(CT,C)*QE.L(C));
 
*Factor accounts.
 x_SAMBUD('FAC',F,'INC',A,%1)                 = WF.L(F) * WFDIST.L(F,A) * QF.L(F,A);
 x_SAMBUD('FAC',F,'INC',GV,%1)                = trnsf(F,GV)*CPI.L; 
 x_SAMBUD('FAC',F,'INC',RW,%1)                = trnsf(F,RW)*EXR.L;
 x_SAMBUD('FAC',F,'SPND',INS,%1)              = shif(INS,F)*YF.L(F)*(1-TF.L(F));
 x_SAMBUD('FAC',F,'SPND','FACTAX',%1)         = TF.L(F)*YF.L(F);
 
*Domestic nongovernment institution accounts.
 x_SAMBUD('INSDNG',INSDNG,'INC',F,%1)         = YIF.L(INSDNG,F);
 x_SAMBUD('INSDNG',INSDNG,'INC',INSDNGP,%1)   = TRII.L(INSDNG,INSDNGP);
 x_SAMBUD('INSDNG',INSDNG,'INC',GV,%1)        = trnsi(INSDNG,GV)*CPI.L;
 x_SAMBUD('INSDNG',INSDNG,'INC',RW,%1)        = trnsi(INSDNG,RW)*EXR.L;
 x_SAMBUD('INSDNG',H,'SPND',A,%1)             = PA.L(A)*QHA.L(A,H);
 x_SAMBUD('INSDNG',H,'SPND',C,%1)             = PQ.L(C)*QH.L(C,H);
 x_SAMBUD('INSDNG',INSDNG,'SPND',INS,%1)      = TRII.L(INS,INSDNG);
 x_SAMBUD('INSDNG',INSDNG,'SPND',SI,%1)       = MPS.L(INSDNG)*(1-TI.L(INSDNG))*YI.L(INSDNG);
 x_SAMBUD('INSDNG',INSDNG,'SPND','INSTAX',%1) = TI.L(INSDNG) * YI.L(INSDNG);

*Government account.
 x_SAMBUD('GOV','DUM','INC','INSTAX',%1)      = SUM(INSDNG, TI.L(INSDNG)*YI.L(INSDNG));
 x_SAMBUD('GOV','DUM','INC','FACTAX',%1)      = SUM(F, TF.L(F)*YF.L(F));
 x_SAMBUD('GOV','DUM','INC','VATTAX',%1)      = SUM(A, TV.L(A)*PVA.L(A)*QVA.L(A));
 x_SAMBUD('GOV','DUM','INC','ACTTAX',%1)      = SUM(A, TA.L(A)*PA.L(A)*QA.L(A));
 x_SAMBUD('GOV','DUM','INC','IMPTAX',%1)      = SUM(C, TM.L(C)*pwm(C)*QM.L(C))*EXR.L;
 x_SAMBUD('GOV','DUM','INC','EXPTAX',%1)      = SUM(C, TE.L(C)*pwe(C)*QE.L(C))*EXR.L;
 x_SAMBUD('GOV','DUM','INC','COMTAX',%1)      = SUM(C, TQ.L(C)*PQ.L(C)*QQ.L(C));
 x_SAMBUD('GOV','DUM','INC',INS,%1)           = TRII.L(GV,INS);
 x_SAMBUD('GOV','DUM','INC',F,%1)             = YIF.L(GV,F);
 x_SAMBUD('GOV','DUM','INC',RW,%1)            = trnsi(GV,RW) * EXR.L;
 x_SAMBUD('GOV','DUM','SPND',C,%1)            = PQ.L(C)*QG.L(C);
 x_SAMBUD('GOV','DUM','SPND',INSD,%1)         = trnsi(INSD,GV)*CPI.L;
 x_SAMBUD('GOV','DUM','SPND',SI,%1)           = GSAV.L;
 x_SAMBUD('GOV','DUM','SPND',RW,%1)           = trnsi(RW,GV)*EXR.L;

*Savings-investment account.
 x_SAMBUD('SAVINV','DUM','INC',INSDNG,%1)     = MPS.L(INSDNG)*(1-TI.L(INSDNG))*YI.L(INSDNG);
 x_SAMBUD('SAVINV','DUM','INC',GV,%1)         = GSAV.L;
 x_SAMBUD('SAVINV','DUM','INC',RW,%1)         = EXR.L*FSAV.L;
 x_SAMBUD('SAVINV','DUM','SPND',C,%1)         = PQ.L(C)*QINV.L(C);
 x_SAMBUD('SAVINV','DUM','SPND',STK,%1)       = SUM(C, PQ.L(C)*qdst(C));    

*Tax accounts.
*  Incomes
 x_SAMBUD('INSTAX','DUM','INC',INSDNG,%1)     = TI.L(INSDNG) * YI.L(INSDNG);
 x_SAMBUD('FACTAX','DUM','INC',F,%1)          = TF.L(F) * YF.L(F);
 x_SAMBUD('VATTAX','DUM','INC',A,%1)          = TV.L(A) * PVA.L(A) * QVA.L(A);
 x_SAMBUD('ACTTAX','DUM','INC',A,%1)          = TA.L(A) * PA.L(A) * QA.L(A);
 x_SAMBUD('COMTAX','DUM','INC',C,%1)          = TQ.L(C) * QQ.L(C);
 x_SAMBUD('IMPTAX','DUM','INC',C,%1)          = TM.L(C) * pwm(C) * QM.L(C) * EXR.L;
 x_SAMBUD('EXPTAX','DUM','INC',C,%1)          = TE.L(C) * pwe(C) * QE.L(C) * EXR.L;
 x_SAMBUD('INSTAX','DUM','SPND',GV,%1)        = SUM(INSDNG, TI.L(INSDNG) * YI.L(INSDNG));
 x_SAMBUD('FACTAX','DUM','SPND',GV,%1)        = SUM(F, TF.L(F) * YF.L(F));
 x_SAMBUD('VATTAX','DUM','SPND',GV,%1)        = SUM(A, TV.L(A) * PVA.L(A) * QVA.L(A));
 x_SAMBUD('ACTTAX','DUM','SPND',GV,%1)        = SUM(A, TA.L(A) * PA.L(A) * QA.L(A));
 x_SAMBUD('COMTAX','DUM','SPND',GV,%1)        = SUM(C, TQ.L(C) * QQ.L(C));
 x_SAMBUD('IMPTAX','DUM','SPND',GV,%1)        = SUM(C, TM.L(C) * pwm(C) * QM.L(C)) * EXR.L;
 x_SAMBUD('EXPTAX','DUM','SPND',GV,%1)        = SUM(C, TE.L(C) * pwe(C) * QE.L(C)) * EXR.L;

*Rest of world account.
 x_SAMBUD('ROW','DUM','INC',C,%1)             = pwm(C)*QM.L(C)*EXR.L;
 x_SAMBUD('ROW','DUM','INC',F,%1)             = YIF.L(RW,F)*EXR.L;
 x_SAMBUD('ROW','DUM','INC',INS,%1)           = TRII.L(RW,INS)*EXR.L;
 x_SAMBUD('ROW','DUM','INC',GV,%1)            = trnsi(RW,GV)*EXR.L;
 
 x_SAMBUD('ROW','DUM','SPND',C,%1)            = pwe(C)*QE.L(C)*EXR.L;
 x_SAMBUD('ROW','DUM','SPND',F,%1)            = trnsf(F,RW)*EXR.L;
 x_SAMBUD('ROW','DUM','SPND',INS,%1)          = trnsi(INS,RW)*EXR.L;
 x_SAMBUD('ROW','DUM','SPND','S-I',%1)        = FSAV.L*EXR.L;

*Totals
 x_SAMBUD(SAC,AC,'INC','TOTAL',%1)            = SUM(ACNT, x_SAMBUD(SAC,AC,'INC',ACNT,%1));
 x_SAMBUD(SAC,AC,'SPND','TOTAL',%1)           = SUM(ACNT, x_SAMBUD(SAC,AC,'SPND',ACNT,%1));
 
*Gap in totals
 x_SAMBUDGAP(SAC,ACNT,%1)                     = ABS(x_SAMBUD(SAC,ACNT,'INC','TOTAL',%1) - x_SAMBUD(SAC,ACNT,'SPND','TOTAL',%1));
 x_SAMBUDGAP(SAC,'TOTAL',%1)                  = SUM(ACNT, x_SAMBUDGAP(SAC,ACNT,%1));

*------------------------------------------------------------------
*2.4.12  National accounts data
*------------------------------------------------------------------
 
*--- GDP by expenditure ---

*Private consumption.
 x_GDPTAB1('NOMINAL','PRVCON',%1)   =  SUM((C,H), PQ.L(C)*QH.L(C,H)) + SUM((A,H), PA.L(A)*QHA.L(A,H));
 x_GDPTAB1('REAL','PRVCON',%1)      =  SUM((C,H), PQ0(C)*QH.L(C,H))  + SUM((A,H), PA0(A)*QHA.L(A,H));
 
*Fixed capital formation. 
 x_GDPTAB1('NOMINAL','FIXINV',%1)   = SUM(C, PQ.L(C)*QINV.L(C));
 x_GDPTAB1('REAL','FIXINV',%1)      = SUM(C, PQ0(C)*QINV.L(C));
 
*Change in stocks. 
 x_GDPTAB1('NOMINAL','DSTOCK',%1)   = SUM(C, PQ.L(C)*qdst(C));
 x_GDPTAB1('REAL','DSTOCK',%1)      = SUM(C, PQ0(C)*qdst(C));
 
*Government consumption. 
 x_GDPTAB1('NOMINAL','GOVCON',%1)   = SUM(C, PQ.L(C)*QG.L(C));
 x_GDPTAB1('REAL','GOVCON',%1)      = SUM(C, PQ0(C)*QG.L(C));
 
*Exports. 
 x_GDPTAB1('NOMINAL','EXPORTS',%1)  = SUM(CE, pwe(CE)*QE.L(CE)*EXR.L);
 x_GDPTAB1('REAL','EXPORTS',%1)     = SUM(CE, pwe0(CE)*QE.L(CE)*EXR0);
 
*Imports. 
 x_GDPTAB1('NOMINAL','IMPORTS',%1)  = -SUM(CM, pwm(CM)*QM.L(CM)*EXR.L);
 x_GDPTAB1('REAL','IMPORTS',%1)     = -SUM(CM, pwm0(CM)*QM.L(CM)*EXR0);
 
*Gross domestic product at market prices. 
 x_GDPTAB1('NOMINAL','GDPMP',%1)    = SUM(IGDP2, x_GDPTAB1('NOMINAL',IGDP2,%1));
 x_GDPTAB1('REAL','GDPMP',%1)       = SUM(IGDP2, x_GDPTAB1('REAL',IGDP2,%1));
 
*Total absorption. 
 x_GDPTAB1('NOMINAL','ABSORP',%1)   = x_GDPTAB1('NOMINAL','GDPMP',%1) - x_GDPTAB1('NOMINAL','IMPORTS',%1) - x_GDPTAB1('NOMINAL','EXPORTS',%1);
 x_GDPTAB1('REAL','ABSORP',%1)      = x_GDPTAB1('REAL','GDPMP',%1) - x_GDPTAB1('REAL','IMPORTS',%1) - x_GDPTAB1('REAL','EXPORTS',%1);
 
*Gross domestic product at factor cost. 
 x_GDPTAB1('NOMINAL','GDPFC2',%1)   = SUM(A, PVA.L(A)*(1-TV.L(A))*QVA.L(A));
 x_GDPTAB1('REAL','GDPFC2',%1)      = SUM(A, PVA0(A)*(1-TV0(A))*QVA.L(A));
 
*Net indirect taxes.
 x_GDPTAB1('NOMINAL','NETITAX',%1) =
            SUM(A, TA.L(A)*PA.L(A)*QA.L(A))
          + SUM(A, TV.L(A)*PVA.L(A)*QVA.L(A))
          + SUM(C, TM.L(C)*pwm(C)*QM.L(C)*EXR.L)
          + SUM(C, TE.L(C)*pwe(C)*QE.L(C)*EXR.L)
          + SUM(C, TQ.L(C)*PQ.L(C)*QQ.L(C));
 x_GDPTAB1('REAL','NETITAX',%1) =
            SUM(A, TA0(A)*PA0(A)*QA.L(A))
          + SUM(A, TV0(A)*PVA0(A)*QVA.L(A))
          + SUM(C, TM0(C)*PWM0(C)*QM.L(C)*EXR0)
          + SUM(C, TE0(C)*PWE0(C)*QE.L(C)*EXR0)
          + SUM(C, TQ0(C)*PQ0(C)*QQ.L(C));

*Alternative measure of gross domestic product at market prices. 
 x_GDPTAB1('NOMINAL','GDPMP2',%1) = x_GDPTAB1('NOMINAL','GDPFC2',%1) + x_GDPTAB1('NOMINAL','NETITAX',%1);
 
*Shares of total GDP at market prices.
 x_GDPTAB1('NOMSHARE',IGDP,%1)$x_GDPTAB1('NOMINAL','GDPMP',%1) = x_GDPTAB1('NOMINAL',IGDP,%1)/x_GDPTAB1('NOMINAL','GDPMP',%1)*100;
 x_GDPTAB1('REALSHARE',IGDP,%1)$x_GDPTAB1('REAL','GDPMP',%1)   = x_GDPTAB1('REAL',IGDP,%1)/x_GDPTAB1('REAL','GDPMP',%1)*100;

*GDP deflator.
 x_GDPTAB1('DEFLATOR',IGDP,%1)$x_GDPTAB1('REAL',IGDP,%1) = x_GDPTAB1('NOMINAL',IGDP,%1)/x_GDPTAB1('REAL',IGDP,%1)*100;

*Gap in GDP at market prices measured two ways
 x_GDPGAP(%1) = ABS(x_GDPTAB1('NOMINAL','GDPMP',%1) - x_GDPTAB1('NOMINAL','GDPMP2',%1));

*--- GDP by sector ---

*Activity GDP at factor cost. 
 x_GDPTAB2('NOMINAL',A,%1)         = PVA.L(A)*(1-TV.L(A))*QVA.L(A);
 x_GDPTAB2('REAL',A,%1)            = PVA0(A)*(1-TV0(A))*QVA.L(A);

*Total GDP at factor cost. 
 x_GDPTAB2('NOMINAL','TOTAL',%1)   = SUM(A, x_GDPTAB2('NOMINAL',A,%1));
 x_GDPTAB2('REAL','TOTAL',%1)      = SUM(A, x_GDPTAB2('REAL',A,%1));

*Shares of total GDP at factor cost.
 x_GDPTAB2('NOMSHARE',A,%1)        = x_GDPTAB2('NOMINAL',A,%1)/x_GDPTAB2('NOMINAL','TOTAL',%1)*100;
 x_GDPTAB2('REALSHARE',A,%1)       = x_GDPTAB2('REAL',A,%1)/x_GDPTAB2('REAL','TOTAL',%1)*100;

*Total shares.
 x_GDPTAB2('NOMSHARE','TOTAL',%1)  = SUM(A, x_GDPTAB2('NOMSHARE',A,%1));
 x_GDPTAB2('REALSHARE','TOTAL',%1) = SUM(A, x_GDPTAB2('REALSHARE',A,%1));

*Activity GDP deflator.
 x_GDPTAB2('DEFLATOR',A,%1)$x_GDPTAB2('REAL',A,%1)              = x_GDPTAB2('NOMINAL',A,%1)/x_GDPTAB2('REAL',A,%1)*100;
 x_GDPTAB2('DEFLATOR','TOTAL',%1)$x_GDPTAB2('REAL','TOTAL',%1)  = x_GDPTAB2('NOMINAL','TOTAL',%1)/x_GDPTAB2('REAL','TOTAL',%1)*100;


*------------------------------------------------------------------
*2.4.13  Closure information
*------------------------------------------------------------------

*Macro closures
 x_MACCLOSURES('S-I',%1) = SICLOSE(%1);
 x_MACCLOSURES('GOV',%1) = GOVCLOSE(%1);
 x_MACCLOSURES('ROW',%1) = ROWCLOSE(%1);

*Factor closures
 x_FACCLOSURES(F,%1)     = FACCLOSE(F,%1);


*------------------------------------------------------------------
*2.4.14  Solver reports
*------------------------------------------------------------------

 x_SOLVEREP('MODEL-STATUS','MCP',%1)  = STANDCGE.MODELSTAT;
 x_SOLVEREP('SOLVER-STATUS','MCP',%1) = STANDCGE.SOLVESTAT;
 x_SOLVEREP('NUM-REDEFEQ','MCP',%1)   = STANDCGE.NUMREDEF;

*Values are reset to zero to avoid using results from earlier solve in the definition of SOLVEREP FOR later solves.
 STANDCGE.MODELSTAT = 0;
 STANDCGE.SOLVESTAT = 0;
 STANDCGE.NUMREDEF  = 0;