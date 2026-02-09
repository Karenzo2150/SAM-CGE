$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2.4 (Sections 1-2): Initialize variables and parameters
 This include file (includes\2static_varinit.inc) initializes model parameters and variables
 to base year values between solves.

SECTIONS:
 2.4.1  Initialize model parameter values
 2.4.2  Initialize model variable values
$offtext

*------------------------------------------------------------------
*2.4.1  Initialize model parameter values
*------------------------------------------------------------------

 alphaf(F,A)     = alphaf0(F,A);  
 alphava(A)      = alphava0(A);
 betah(A,H)      = betah0(A,H);
 betam(C,H)      = betam0(C,H);
 gammah(A,H)     = gammah0(A,H);   
 gammam(C,H)     = gammam0(C,H);   
 icd(C,CP)       = icd0(C,CP);     
 ice(C,CP)       = ice0(C,CP);     
 icm(C,CP)       = icm0(C,CP);     
 mpsbar(H)       = MPS0(H); 
 pop(H)          = pop0(H);       
 pwe(C)          = pwe0(C);        
 pwm(C)          = pwm0(C);        
 qbarg(C)        = qbarg0(C);      
 qbarinv(C)      = qbarinv0(C);    
 qdst(C)         = qdst0(C);       
 shif(AC,ACP)    = shif0(AC,ACP);  
 shii(AC,ACP)    = shii0(AC,ACP);  
 tabar(A)        = TA0(A);  
 tebar(C)        = TE0(C);  
 tfbar(F)        = TF0(F);  
 tibar(H)        = TI0(H);
 tmbar(C)        = TM0(C);  
 tqbar(C)        = TQ0(C);  
 trnsf(F,INS)    = trnsf0(F,INS);
 trnsi(INS,INSP) = trnsi0(INS,INSP);
 tvbar(A)        = TV0(A);  


*------------------------------------------------------------------
*2.4.2  Initialize model variable values
*------------------------------------------------------------------

 CPI.L            = CPI0;
 DMPS.L           = DMPS0;
 DPI.L            = DPI0;
 DTA.L            = DTA0;
 DTE.L            = DTE0;
 DTF.L            = DTF0;
 DTI.L            = DTI0;
 DTM.L            = DTM0;
 DTQ.L            = DTQ0;
 DTV.L            = DTV0;
 EG.L             = EG0;
 EH.L(H)          = EH0(H);
 EXR.L            = EXR0;
 FSAV.L           = FSAV0;
 GADJ.L           = GADJ0;
 GOVSHR.L         = GOVSHR0;
 GSAV.L           = GSAV0;
 IADJ.L           = IADJ0;
 INVSHR.L         = INVSHR0;
 MPS.L(INS)       = MPS0(INS);
 MPSADJ.L         = MPSADJ0;
 PA.L(A)          = PA0(A);
 PDD.L(C)         = PDD0(C);
 PDS.L(C)         = PDS0(C);
 PE.L(C)          = PE0(C);
 PM.L(C)          = PM0(C);
 PINTA.L(A)       = PINTA0(A);
 PQ.L(C)          = PQ0(C);
 PSAV.L           = PSAV0;
 PVA.L(A)         = PVA0(A);
 PX.L(C)          = PX0(C);
 PXAC.L(A,C)      = PXAC0(A,C);
 QA.L(A)          = QA0(A);
 QD.L(C)          = QD0(C);
 QE.L(C)          = QE0(C);
 QF.L(F,A)        = QF0(F,A);
 QFS.L(F)         = QFS0(F);
 QG.L(C)          = QG0(C);
 QH.L(C,H)        = QH0(C,H);
 QHA.L(A,H)       = QHA0(A,H);
 QINT.L(C,A)      = QINT0(C,A);
 QINTA.L(A)       = QINTA0(A);
 QINV.L(C)        = QINV0(C);
 QM.L(C)          = QM0(C);
 QQ.L(C)          = QQ0(C);
 QT.L(C)          = QT0(C);
 QVA.L(A)         = QVA0(A);
 QX.L(C)          = QX0(C);
 QXAC.L(A,C)      = QXAC0(A,C);
 TA.L(A)          = TA0(A);
 TAADJ.L          = TAADJ0;
 TABS.L           = TABS0;
 TE.L(C)          = TE0(C);
 TEADJ.L          = TEADJ0;
 TF.L(F)          = TF0(F);
 TFADJ.L          = TFADJ0;
 TI.L(INS)        = TI0(INS);
 TIADJ.L          = TIADJ0;
 TM.L(C)          = TM0(C);
 TMADJ.L          = TMADJ0;
 TRII.L(INS,INSP) = TRII0(INS,INSP);
 TQ.L(C)          = TQ0(C);
 TQADJ.L          = TQADJ0;
 TV.L(A)          = TV0(A);
 TVADJ.L          = TVADJ0;
 WALRAS.L         = WALRAS0;
 WF.L(F)          = WF0(F);
 WFDIST.L(F,A)    = WFDIST0(F,A);
 YF.L(F)          = YF0(F);
 YG.L             = YG0;
 YI.L(INS)        = YI0(INS);
 YIF.L(INS,F)     = YIF0(INS,F);