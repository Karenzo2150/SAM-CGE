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
 x_alphaf(F,A,%1,%2)      = alphaf(F,A);
 x_alphava(A,%1,%2)       = alphava(A);      
 x_betah(A,H,%1,%2)       = betah(A,H);      
 x_betam(C,H,%1,%2)       = betam(C,H);      
 x_gammah(A,H,%1,%2)      = gammah(A,H);     
 x_gammam(C,H,%1,%2)      = gammam(C,H);     
 x_icd(C,CP,%1,%2)        = icd(C,CP);       
 x_ice(C,CP,%1,%2)        = ice(C,CP);       
 x_icm(C,CP,%1,%2)        = icm(C,CP);       
 x_pop(H,%1,%2)           = pop(H);         
 x_pwe(C,%1,%2)           = pwe(C);          
 x_pwm(C,%1,%2)           = pwm(C);          
 x_qbarg(C,%1,%2)         = qbarg(C);        
 x_qbarinv(C,%1,%2)       = qbarinv(C);      
 x_qdst(C,%1,%2)          = qdst(C);         
 x_shif(AC,ACP,%1,%2)     = shif(AC,ACP);    
 x_shii(AC,ACP,%1,%2)     = shii(AC,ACP);    
 x_trnsf(F,INS,%1,%2)     = trnsf(F,INS);
 x_trnsi(INS,INSP,%1,%2)  = trnsi(INS,INSP);  

*Variable values 
 x_CPI(%1,%2)             = CPI.L;
 x_DMPS(%1,%2)            = DMPS.L;
 x_DPI(%1,%2)             = DPI.L;
 x_DTA(%1,%2)             = DTA.L;
 x_DTE(%1,%2)             = DTE.L;
 x_DTF(%1,%2)             = DTF.L;
 x_DTI(%1,%2)             = DTI.L;       
 x_DTM(%1,%2)             = DTM.L;         
 x_DTQ(%1,%2)             = DTQ.L;         
 x_DTV(%1,%2)             = DTV.L;        
 x_EG(%1,%2)              = EG.L;
 x_EH(H,%1,%2)            = EH.L(H);
 x_EXR(%1,%2)             = EXR.L;
 x_FSAV(%1,%2)            = FSAV.L;
 x_GADJ(%1,%2)            = GADJ.L;
 x_GOVSHR(%1,%2)          = GOVSHR.L;
 x_GSAV(%1,%2)            = GSAV.L;
 x_IADJ(%1,%2)            = IADJ.L;
 x_INVSHR(%1,%2)          = INVSHR.L;
 x_MPS(INS,%1,%2)         = MPS.L(INS);
 x_MPSADJ(%1,%2)          = MPSADJ.L;      
 x_PA(A,%1,%2)            = PA.L(A);
 x_PDD(C,%1,%2)           = PDD.L(C);
 x_PDS(C,%1,%2)           = PDS.L(C);
 x_PE(C,%1,%2)            = PE.L(C);
 x_PM(C,%1,%2)            = PM.L(C);
 x_PINTA(A,%1,%2)         = PINTA.L(A);
 x_PQ(C,%1,%2)            = PQ.L(C);
 x_PSAV(%1,%2)            = PSAV.L;
 x_PVA(A,%1,%2)           = PVA.L(A);
 x_PX(C,%1,%2)            = PX.L(C);
 x_PXAC(A,C,%1,%2)        = PXAC.L(A,C);
 x_QA(A,%1,%2)            = QA.L(A);
 x_QD(C,%1,%2)            = QD.L(C);
 x_QE(C,%1,%2)            = QE.L(C);
 x_QF(F,A,%1,%2)          = QF.L(F,A);
 x_QFS(F,%1,%2)           = QFS.L(F);
 x_QG(C,%1,%2)            = QG.L(C);
 x_QH(C,H,%1,%2)          = QH.L(C,H);
 x_QHA(A,H,%1,%2)         = QHA.L(A,H);
 x_QINT(C,A,%1,%2)        = QINT.L(C,A);
 x_QINTA(A,%1,%2)         = QINTA.L(A);
 x_QINV(C,%1,%2)          = QINV.L(C);
 x_QM(C,%1,%2)            = QM.L(C);
 x_QQ(C,%1,%2)            = QQ.L(C);
 x_QT(C,%1,%2)            = QT.L(C);
 x_QVA(A,%1,%2)           = QVA.L(A);
 x_QX(C,%1,%2)            = QX.L(C);
 x_QXAC(A,C,%1,%2)        = QXAC.L(A,C);
 x_TA(A,%1,%2)            = TA.L(A);        
 x_TAADJ(%1,%2)           = TAADJ.L;
 x_TABS(%1,%2)            = TABS.L;
 x_TE(C,%1,%2)            = TE.L(C);
 x_TEADJ(%1,%2)           = TEADJ.L;
 x_TF(F,%1,%2)            = TF.L(F);
 x_TFADJ(%1,%2)           = TFADJ.L;
 x_TI(INS,%1,%2)          = TI.L(INS);
 x_TIADJ(%1,%2)           = TIADJ.L;
 x_TM(C,%1,%2)            = TM.L(C);
 x_TMADJ(%1,%2)           = TMADJ.L;
 x_TRII(INS,INSP,%1,%2)   = TRII.L(INS,INSP);
 x_TQ(C,%1,%2)            = TQ.L(C);
 x_TQADJ(%1,%2)           = TQADJ.L;
 x_TV(A,%1,%2)            = TV.L(A);
 x_TVADJ(%1,%2)           = TVADJ.L;
 x_WALRAS(%1,%2)          = WALRAS.L;
 x_WF(F,%1,%2)            = WF.L(F);
 x_WFDIST(F,A,%1,%2)      = WFDIST.L(F,A);
 x_YF(F,%1,%2)            = YF.L(F);
 x_YG(%1,%2)              = YG.L;
 x_YI(INS,%1,%2)          = YI.L(INS);
 x_YIF(INS,F,%1,%2)       = YIF.L(INS,F);
 
 
*------------------------------------------------------------------
*2.4.11  Budgets for SAM accounts
*------------------------------------------------------------------

*Activity accounts.
 x_SAMBUD('ACT',A,'INC',C,%1,%2)                 = PXAC.L(A,C)*theta(A,C)*(QA.L(A)-SUM(H, QHA.L(A,H)));
 x_SAMBUD('ACT',A,'INC',H,%1,%2)                 = PA.L(A)*QHA.L(A,H);
 x_SAMBUD('ACT',A,'SPND',F,%1,%2)                = WF.L(F)*WFDIST.L(F,A)*QF.L(F,A);
 x_SAMBUD('ACT',A,'SPND',C,%1,%2)                = PQ.L(C)*QINT.L(C,A);
 x_SAMBUD('ACT',A,'SPND','VATTAX',%1,%2)         = TV.L(A)*PVA.L(A)*QVA.L(A);
 x_SAMBUD('ACT',A,'SPND','ACTTAX',%1,%2)         = TA.L(A)*PA.L(A)*QA.L(A);

*Commodity accounts.
 x_SAMBUD('COM',C,'INC',H,%1,%2)                 = PQ.L(C)*QH.L(C,H);
 x_SAMBUD('COM',C,'INC',GV,%1,%2)                = PQ.L(C)*QG.L(C);
 x_SAMBUD('COM',C,'INC',SI,%1,%2)                = PQ.L(C)*QINV.L(C);
 x_SAMBUD('COM',C,'INC',STK,%1,%2)               = PQ.L(C)*qdst(C);
 x_SAMBUD('COM',C,'INC',RW,%1,%2)                = EXR.L*pwe(C) * QE.L(C);
 x_SAMBUD('COM',C,'INC',A,%1,%2)                 = PQ.L(C)*QINT.L(C,A);
 x_SAMBUD('COM',C,'INC','DUM',%1,%2)             = PQ.L(C)*QT.L(C);
 x_SAMBUD('COM',C,'SPND',A,%1,%2)                = PXAC.L(A,C)*theta(A,C)*(QA.L(A)-SUM(H, QHA.L(A,H)));
 x_SAMBUD('COM',C,'SPND','COMTAX',%1,%2)         = TQ.L(C)*PQ.L(C)*QQ.L(C);
 x_SAMBUD('COM',C,'SPND','IMPTAX',%1,%2)         = TM.L(C)*EXR.L*pwm(C)*QM.L(C);
 x_SAMBUD('COM',C,'SPND',RW,%1,%2)               = EXR.L*pwm(C)*QM.L(C);
 x_SAMBUD('COM',C,'SPND','EXPTAX',%1,%2)         = TE.L(C)*EXR.L*pwe(C)*QE.L(C);
 x_SAMBUD('COM',C,'SPND',CTD,%1,%2)              = SUM(CT, PQ.L(CT)*icd(CT,C)*QD.L(C));
 x_SAMBUD('COM',C,'SPND',CTM,%1,%2)              = SUM(CT, PQ.L(CT)*icm(CT,C)*QM.L(C));
 x_SAMBUD('COM',C,'SPND',CTE,%1,%2)              = SUM(CT, PQ.L(CT)*ice(CT,C)*QE.L(C));
 
*Factor accounts.
 x_SAMBUD('FAC',F,'INC',A,%1,%2)                 = WF.L(F) * WFDIST.L(F,A) * QF.L(F,A);
 x_SAMBUD('FAC',F,'INC',GV,%1,%2)                = trnsf(F,GV)*CPI.L; 
 x_SAMBUD('FAC',F,'INC',RW,%1,%2)                = trnsf(F,RW)*EXR.L;
 x_SAMBUD('FAC',F,'SPND',INS,%1,%2)              = shif(INS,F)*YF.L(F)*(1-TF.L(F));
 x_SAMBUD('FAC',F,'SPND','FACTAX',%1,%2)         = TF.L(F)*YF.L(F);
 
*Domestic nongovernment institution accounts.
 x_SAMBUD('INSDNG',INSDNG,'INC',F,%1,%2)         = YIF.L(INSDNG,F);
 x_SAMBUD('INSDNG',INSDNG,'INC',INSDNGP,%1,%2)   = TRII.L(INSDNG,INSDNGP);
 x_SAMBUD('INSDNG',INSDNG,'INC',GV,%1,%2)        = trnsi(INSDNG,GV)*CPI.L;
 x_SAMBUD('INSDNG',INSDNG,'INC',RW,%1,%2)        = trnsi(INSDNG,RW)*EXR.L;
 x_SAMBUD('INSDNG',H,'SPND',A,%1,%2)             = PA.L(A)*QHA.L(A,H);
 x_SAMBUD('INSDNG',H,'SPND',C,%1,%2)             = PQ.L(C)*QH.L(C,H);
 x_SAMBUD('INSDNG',INSDNG,'SPND',INS,%1,%2)      = TRII.L(INS,INSDNG);
 x_SAMBUD('INSDNG',INSDNG,'SPND',SI,%1,%2)       = MPS.L(INSDNG)*(1-TI.L(INSDNG))*YI.L(INSDNG);
 x_SAMBUD('INSDNG',INSDNG,'SPND','INSTAX',%1,%2) = TI.L(INSDNG) * YI.L(INSDNG);

*Government account.
 x_SAMBUD('GOV','DUM','INC','INSTAX',%1,%2)      = SUM(INSDNG, TI.L(INSDNG)*YI.L(INSDNG));
 x_SAMBUD('GOV','DUM','INC','FACTAX',%1,%2)      = SUM(F, TF.L(F)*YF.L(F));
 x_SAMBUD('GOV','DUM','INC','VATTAX',%1,%2)      = SUM(A, TV.L(A)*PVA.L(A)*QVA.L(A));
 x_SAMBUD('GOV','DUM','INC','ACTTAX',%1,%2)      = SUM(A, TA.L(A)*PA.L(A)*QA.L(A));
 x_SAMBUD('GOV','DUM','INC','IMPTAX',%1,%2)      = SUM(C, TM.L(C)*pwm(C)*QM.L(C))*EXR.L;
 x_SAMBUD('GOV','DUM','INC','EXPTAX',%1,%2)      = SUM(C, TE.L(C)*pwe(C)*QE.L(C))*EXR.L;
 x_SAMBUD('GOV','DUM','INC','COMTAX',%1,%2)      = SUM(C, TQ.L(C)*PQ.L(C)*QQ.L(C));
 x_SAMBUD('GOV','DUM','INC',INS,%1,%2)           = TRII.L(GV,INS);
 x_SAMBUD('GOV','DUM','INC',F,%1,%2)             = YIF.L(GV,F);
 x_SAMBUD('GOV','DUM','INC',RW,%1,%2)            = trnsi(GV,RW) * EXR.L;
 x_SAMBUD('GOV','DUM','SPND',C,%1,%2)            = PQ.L(C)*QG.L(C);
 x_SAMBUD('GOV','DUM','SPND',INSD,%1,%2)         = trnsi(INSD,GV)*CPI.L;
 x_SAMBUD('GOV','DUM','SPND',SI,%1,%2)           = GSAV.L;
 x_SAMBUD('GOV','DUM','SPND',RW,%1,%2)           = trnsi(RW,GV)*EXR.L;

*Savings-investment account.
 x_SAMBUD('SAVINV','DUM','INC',INSDNG,%1,%2)     = MPS.L(INSDNG)*(1-TI.L(INSDNG))*YI.L(INSDNG);
 x_SAMBUD('SAVINV','DUM','INC',GV,%1,%2)         = GSAV.L;
 x_SAMBUD('SAVINV','DUM','INC',RW,%1,%2)         = EXR.L*FSAV.L;
 x_SAMBUD('SAVINV','DUM','SPND',C,%1,%2)         = PQ.L(C)*QINV.L(C);
 x_SAMBUD('SAVINV','DUM','SPND',STK,%1,%2)       = SUM(C, PQ.L(C)*qdst(C));    

*Tax accounts.
*  Incomes
 x_SAMBUD('INSTAX','DUM','INC',INSDNG,%1,%2)     = TI.L(INSDNG) * YI.L(INSDNG);
 x_SAMBUD('FACTAX','DUM','INC',F,%1,%2)          = TF.L(F) * YF.L(F);
 x_SAMBUD('VATTAX','DUM','INC',A,%1,%2)          = TV.L(A) * PVA.L(A) * QVA.L(A);
 x_SAMBUD('ACTTAX','DUM','INC',A,%1,%2)          = TA.L(A) * PA.L(A) * QA.L(A);
 x_SAMBUD('COMTAX','DUM','INC',C,%1,%2)          = TQ.L(C) * QQ.L(C);
 x_SAMBUD('IMPTAX','DUM','INC',C,%1,%2)          = TM.L(C) * pwm(C) * QM.L(C) * EXR.L;
 x_SAMBUD('EXPTAX','DUM','INC',C,%1,%2)          = TE.L(C) * pwe(C) * QE.L(C) * EXR.L;
 x_SAMBUD('INSTAX','DUM','SPND',GV,%1,%2)        = SUM(INSDNG, TI.L(INSDNG) * YI.L(INSDNG));
 x_SAMBUD('FACTAX','DUM','SPND',GV,%1,%2)        = SUM(F, TF.L(F) * YF.L(F));
 x_SAMBUD('VATTAX','DUM','SPND',GV,%1,%2)        = SUM(A, TV.L(A) * PVA.L(A) * QVA.L(A));
 x_SAMBUD('ACTTAX','DUM','SPND',GV,%1,%2)        = SUM(A, TA.L(A) * PA.L(A) * QA.L(A));
 x_SAMBUD('COMTAX','DUM','SPND',GV,%1,%2)        = SUM(C, TQ.L(C) * QQ.L(C));
 x_SAMBUD('IMPTAX','DUM','SPND',GV,%1,%2)        = SUM(C, TM.L(C) * pwm(C) * QM.L(C)) * EXR.L;
 x_SAMBUD('EXPTAX','DUM','SPND',GV,%1,%2)        = SUM(C, TE.L(C) * pwe(C) * QE.L(C)) * EXR.L;

*Rest of world account.
 x_SAMBUD('ROW','DUM','INC',C,%1,%2)             = pwm(C)*QM.L(C)*EXR.L;
 x_SAMBUD('ROW','DUM','INC',F,%1,%2)             = YIF.L(RW,F)*EXR.L;
 x_SAMBUD('ROW','DUM','INC',INS,%1,%2)           = TRII.L(RW,INS)*EXR.L;
 x_SAMBUD('ROW','DUM','INC',GV,%1,%2)            = trnsi(RW,GV)*EXR.L;
 
 x_SAMBUD('ROW','DUM','SPND',C,%1,%2)            = pwe(C)*QE.L(C)*EXR.L;
 x_SAMBUD('ROW','DUM','SPND',F,%1,%2)            = trnsf(F,RW)*EXR.L;
 x_SAMBUD('ROW','DUM','SPND',INS,%1,%2)          = trnsi(INS,RW)*EXR.L;
 x_SAMBUD('ROW','DUM','SPND','S-I',%1,%2)        = FSAV.L*EXR.L;

*Totals
 x_SAMBUD(SAC,AC,'INC','TOTAL',%1,%2)            = SUM(ACNT, x_SAMBUD(SAC,AC,'INC',ACNT,%1,%2));
 x_SAMBUD(SAC,AC,'SPND','TOTAL',%1,%2)           = SUM(ACNT, x_SAMBUD(SAC,AC,'SPND',ACNT,%1,%2));
 
*Gap in totals
 x_SAMBUDGAP(SAC,ACNT,%1,%2)                     = ABS(x_SAMBUD(SAC,ACNT,'INC','TOTAL',%1,%2) - x_SAMBUD(SAC,ACNT,'SPND','TOTAL',%1,%2));
 x_SAMBUDGAP(SAC,'TOTAL',%1,%2)                  = SUM(ACNT, x_SAMBUDGAP(SAC,ACNT,%1,%2));

*------------------------------------------------------------------
*2.4.12  National accounts data
*------------------------------------------------------------------
 
*--- GDP by expenditure ---

*Private consumption.
 x_GDPTAB1('NOMINAL','PRVCON',%1,%2)   =  SUM((C,H), PQ.L(C)*QH.L(C,H)) + SUM((A,H), PA.L(A)*QHA.L(A,H));
 x_GDPTAB1('REAL','PRVCON',%1,%2)      =  SUM((C,H), PQ0(C)*QH.L(C,H))  + SUM((A,H), PA0(A)*QHA.L(A,H));
 
*Fixed capital formation. 
 x_GDPTAB1('NOMINAL','FIXINV',%1,%2)   = SUM(C, PQ.L(C)*QINV.L(C));
 x_GDPTAB1('REAL','FIXINV',%1,%2)      = SUM(C, PQ0(C)*QINV.L(C));
 
*Change in stocks. 
 x_GDPTAB1('NOMINAL','DSTOCK',%1,%2)   = SUM(C, PQ.L(C)*qdst(C));
 x_GDPTAB1('REAL','DSTOCK',%1,%2)      = SUM(C, PQ0(C)*qdst(C));
 
*Government consumption. 
 x_GDPTAB1('NOMINAL','GOVCON',%1,%2)   = SUM(C, PQ.L(C)*QG.L(C));
 x_GDPTAB1('REAL','GOVCON',%1,%2)      = SUM(C, PQ0(C)*QG.L(C));
 
*Exports. 
 x_GDPTAB1('NOMINAL','EXPORTS',%1,%2)  = SUM(CE, pwe(CE)*QE.L(CE)*EXR.L);
 x_GDPTAB1('REAL','EXPORTS',%1,%2)     = SUM(CE, pwe0(CE)*QE.L(CE)*EXR0);
 
*Imports. 
 x_GDPTAB1('NOMINAL','IMPORTS',%1,%2)  = -SUM(CM, pwm(CM)*QM.L(CM)*EXR.L);
 x_GDPTAB1('REAL','IMPORTS',%1,%2)     = -SUM(CM, pwm0(CM)*QM.L(CM)*EXR0);
 
*Gross domestic product at market prices. 
 x_GDPTAB1('NOMINAL','GDPMP',%1,%2)    = SUM(IGDP2, x_GDPTAB1('NOMINAL',IGDP2,%1,%2));
 x_GDPTAB1('REAL','GDPMP',%1,%2)       = SUM(IGDP2, x_GDPTAB1('REAL',IGDP2,%1,%2));
 
*Total absorption. 
 x_GDPTAB1('NOMINAL','ABSORP',%1,%2)   = x_GDPTAB1('NOMINAL','GDPMP',%1,%2) - x_GDPTAB1('NOMINAL','IMPORTS',%1,%2) - x_GDPTAB1('NOMINAL','EXPORTS',%1,%2);
 x_GDPTAB1('REAL','ABSORP',%1,%2)      = x_GDPTAB1('REAL','GDPMP',%1,%2) - x_GDPTAB1('REAL','IMPORTS',%1,%2) - x_GDPTAB1('REAL','EXPORTS',%1,%2);
 
*Gross domestic product at factor cost. 
 x_GDPTAB1('NOMINAL','GDPFC2',%1,%2)   = SUM(A, PVA.L(A)*(1-TV.L(A))*QVA.L(A));
 x_GDPTAB1('REAL','GDPFC2',%1,%2)      = SUM(A, PVA0(A)*(1-TV0(A))*QVA.L(A));
 
*Net indirect taxes.
 x_GDPTAB1('NOMINAL','NETITAX',%1,%2) =
            SUM(A, TA.L(A)*PA.L(A)*QA.L(A))
          + SUM(A, TV.L(A)*PVA.L(A)*QVA.L(A))
          + SUM(C, TM.L(C)*pwm(C)*QM.L(C)*EXR.L)
          + SUM(C, TE.L(C)*pwe(C)*QE.L(C)*EXR.L)
          + SUM(C, TQ.L(C)*PQ.L(C)*QQ.L(C));
 x_GDPTAB1('REAL','NETITAX',%1,%2) =
            SUM(A, TA0(A)*PA0(A)*QA.L(A))
          + SUM(A, TV0(A)*PVA0(A)*QVA.L(A))
          + SUM(C, TM0(C)*PWM0(C)*QM.L(C)*EXR0)
          + SUM(C, TE0(C)*PWE0(C)*QE.L(C)*EXR0)
          + SUM(C, TQ0(C)*PQ0(C)*QQ.L(C));

*Alternative measure of gross domestic product at market prices. 
 x_GDPTAB1('NOMINAL','GDPMP2',%1,%2) = x_GDPTAB1('NOMINAL','GDPFC2',%1,%2) + x_GDPTAB1('NOMINAL','NETITAX',%1,%2);
 
*Shares of total GDP at market prices.
 x_GDPTAB1('NOMSHARE',IGDP,%1,%2)$x_GDPTAB1('NOMINAL','GDPMP',%1,%2) = x_GDPTAB1('NOMINAL',IGDP,%1,%2)/x_GDPTAB1('NOMINAL','GDPMP',%1,%2)*100;
 x_GDPTAB1('REALSHARE',IGDP,%1,%2)$x_GDPTAB1('REAL','GDPMP',%1,%2)   = x_GDPTAB1('REAL',IGDP,%1,%2)/x_GDPTAB1('REAL','GDPMP',%1,%2)*100;

*GDP deflator.
 x_GDPTAB1('DEFLATOR',IGDP,%1,%2)$x_GDPTAB1('REAL',IGDP,%1,%2) = x_GDPTAB1('NOMINAL',IGDP,%1,%2)/x_GDPTAB1('REAL',IGDP,%1,%2)*100;

*Gap in GDP at market prices measured two ways
 x_GDPGAP(%1,%2) = ABS(x_GDPTAB1('NOMINAL','GDPMP',%1,%2) - x_GDPTAB1('NOMINAL','GDPMP2',%1,%2));

*--- GDP by sector ---

*Activity GDP at factor cost. 
 x_GDPTAB2('NOMINAL',A,%1,%2)         = PVA.L(A)*(1-TV.L(A))*QVA.L(A);
 x_GDPTAB2('REAL',A,%1,%2)            = PVA0(A)*(1-TV0(A))*QVA.L(A);

*Total GDP at factor cost. 
 x_GDPTAB2('NOMINAL','TOTAL',%1,%2)   = SUM(A, x_GDPTAB2('NOMINAL',A,%1,%2));
 x_GDPTAB2('REAL','TOTAL',%1,%2)      = SUM(A, x_GDPTAB2('REAL',A,%1,%2));

*Shares of total GDP at factor cost.
 x_GDPTAB2('NOMSHARE',A,%1,%2)        = x_GDPTAB2('NOMINAL',A,%1,%2)/x_GDPTAB2('NOMINAL','TOTAL',%1,%2)*100;
 x_GDPTAB2('REALSHARE',A,%1,%2)       = x_GDPTAB2('REAL',A,%1,%2)/x_GDPTAB2('REAL','TOTAL',%1,%2)*100;

*Total shares.
 x_GDPTAB2('NOMSHARE','TOTAL',%1,%2)  = SUM(A, x_GDPTAB2('NOMSHARE',A,%1,%2));
 x_GDPTAB2('REALSHARE','TOTAL',%1,%2) = SUM(A, x_GDPTAB2('REALSHARE',A,%1,%2));

*Activity GDP deflator.
 x_GDPTAB2('DEFLATOR',A,%1,%2)$x_GDPTAB2('REAL',A,%1,%2)              = x_GDPTAB2('NOMINAL',A,%1,%2)/x_GDPTAB2('REAL',A,%1,%2)*100;
 x_GDPTAB2('DEFLATOR','TOTAL',%1,%2)$x_GDPTAB2('REAL','TOTAL',%1,%2)  = x_GDPTAB2('NOMINAL','TOTAL',%1,%2)/x_GDPTAB2('REAL','TOTAL',%1,%2)*100;


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

 x_SOLVEREP('MODEL-STATUS','MCP',%1,%2)  = STANDCGE.MODELSTAT;
 x_SOLVEREP('SOLVER-STATUS','MCP',%1,%2) = STANDCGE.SOLVESTAT;
 x_SOLVEREP('NUM-REDEFEQ','MCP',%1,%2)   = STANDCGE.NUMREDEF;

*Values are reset to zero to avoid using results from earlier solve in the definition of SOLVEREP FOR later solves.
 STANDCGE.MODELSTAT = 0;
 STANDCGE.SOLVESTAT = 0;
 STANDCGE.NUMREDEF  = 0;