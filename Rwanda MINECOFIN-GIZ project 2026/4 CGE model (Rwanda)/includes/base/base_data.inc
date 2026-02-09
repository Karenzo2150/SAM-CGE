$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 1.4: Import country data 
 This include file (includes\1base_data.inc) imports country data from the Excel selected
 by the user (base_%data%.xlsx) and makes any adjustments to the data prior to calibration.

SECTIONS:
 1.4.1  Data sets and parameters 
 1.4.2  SAM adjustments
 1.4.3  Factor quantities
 1.4.4  SAM dependent set definitions 
$offtext


*------------------------------------------------------------------
*1.4.1  Data sets and parameters 
*------------------------------------------------------------------

SET
*Subsets
 AAGR(A)            activities - agriculture
 ANAG(A)            activities - non-agruiculture
 AIND(A)            activities - industry
 ASRV(A)            activities - services
 CAGR(C)            commodities - agriculture
 CNAG(C)            commodities - non-agriculture
 CIND(C)            commodities - industry
 CSRV(C)            commodities - services
 FLAB(F)            factors - labor
 FLND(F)            factors - land
 FCAP(F)            factors - capital
 EN(INS)            enterprises
 TAXES(AC)          tax types in SAM
*Data sets
 EF                 headings for elasticity tables         / ACES, ACCES, ELASAC, ELASCA, ELASPRD, ELASPRD2, SIGMAQ, SIGMAT /
 TX                 tax types in model                     / ACTTAX, COMTAX, EXPTAX, FACTAX, IMPTAX, INSTAX, VATTAX /
*Data adjustments 
 CXREM(C)           remove small export flows (zero out and move to stocks)
 CMREM(C)           remove small import flows (zero out and move to stocks)
 CXREX(C)           net out re-export flows (reduce imports until all production is exported)
 CXNET(C)           net out exports (zero exports and move to imports)
 CMNET(C)           net out imports (zero imports and move to exports)
*Mappings           
 MAPAC(A,C)         mapping from activities to commodities
 MAPTX(TX,AC)       mapping from SAM tax accounts to tax accounts TX
;                   

SINGLETON SETS
 CTC(AC)            aggregate transactions cost
 CTD(AC)            domestic transactions cost account
 CTE(AC)            export transactions cost account
 CTM(AC)            import transactions cost account
 SI(AC)             savings-investment
 STK(AC)            inventory investment
;

SCALAR
*Control
 SAMSCALE           scaling factor for SAM values (muliplier)
 LABSCALE           scaling factor for labor factor quantity or wage data (muliplier)
 LNDSCALE           scaling factor for land factor quantity or rental rate data (muliplier)
 CAPSCALE           scaling factor for capital factor quantity or rental rate data (muliplier)
 POPSCALE           scaling factor for population (muliplier)
 QWBASE             country's factor data is either quantities (1) or wages (2)
 EXRBASE            base year exchange rate (LCUs per FCU)
;                   
                    
PARAMETER
*SAM
 SAM(AC,ACP)        standard social accounting matrix (SAM)
*Elasticities       
 AELAS(A,EF)        activity based elasticities data
 CELAS(C,EF)        commodity based elasticities data
 FFORM(A,EF)        choice of production funtional forms
*Demand             
 FRISCH(H)          Frisch parameter for LES demand system
 HELAS(AC,H)        household expenditure elasticities (activity and commodity)
*Factors            
 QFSBASE(F)         base year total supply quantity for factor F
 QFBASE(A,F)        base year factor employment for factor F in activity A
*Households             
 HPOP(H)             base year population numbers for household H
 QFSHBASE(H,F)      base year factor endowments for household H
*Calibration parameters 
 SAMBALCHK(AC)      column minus row total for SAM
 TAXPAR(TX,AC)      tax payments by type of tax TX
;

ALIAS
 (C,CPP), (ACNT,ACNTP), (EN,ENP), (INS,INSP), (INSD,INSDP), (INSDNG,INSDNGP,INSDNGPP)
;            

*Read input data from excel file
$call 'GDXXRW i=data\\%folder%\basemod%dataext%.xlsx o=data.gdx index=index!a5'
$gdxin data.gdx
*Read sets and data
$load AC 
$loaddc A C F INS 
$loaddc AAGR AIND ASRV CAGR CIND CSRV FLAB FLND FCAP INSD INSDNG EN H GV CTC CTD CTE CTM RW SI STK TAXES MAPTX MAPAC
$loaddc SAMSCALE LABSCALE LNDSCALE CAPSCALE POPSCALE CXREM CMREM CXREX CXNET CMNET QWBASE EXRBASE SAM AELAS CELAS FFORM FRISCH HELAS QFSBASE QFBASE HPOP QFSHBASE
$gdxin

*Further set definitions
*  Activities with data in the SAM 
 AA(A)$SAM('TOTAL',A)     = YES;
*  Activities with top-level CES aggregation (otherwise Leontief)
 ACES(A)                  = NO;
 ALEO(A)$(NOT ACES(A))    = YES;
*  Activities with CET output disaggregation (otherwise Leontief)
 ACCES(A)$AA(A)           = YES;
*  Factors with data in the SAM 
 FA(F)$SAM(F,'TOTAL')     = YES;
*  Household-commodity and household-activity consumption combinations in the SAM
 HA(A,H)$SAM(A,H)         = YES;
 HC(C,H)$SAM(C,H)         = YES;
*Nonagricultural activities and commodities
 ANAG(A)$(NOT AAGR(A))    = YES;
 CNAG(C)$(NOT CAGR(C))    = YES;
*All accounts, except for TOTAL
 ACNT(AC)                 = YES;
 ACNT('TOTAL')            = NO;

*Scaling SAM values and quantities data
 SAM(AC,ACP)      = SAM(AC,ACP)*SAMSCALE;
 QFBASE(A,FLAB)   = QFBASE(A,FLAB)*LABSCALE;
 QFBASE(A,FLND)   = QFBASE(A,FLND)*LNDSCALE;
 QFBASE(A,FCAP)   = QFBASE(A,FCAP)*CAPSCALE;
 HPOP(H)          = HPOP(H)*POPSCALE; 

*Check SAM balances before adjustments
 SAM('TOTAL',AC) = 0;
 SAM(AC,'TOTAL') = 0;
 SAM('TOTAL',AC) = SUM(ACNT, SAM(ACNT,AC));
 SAM(AC,'TOTAL') = SUM(ACNT, SAM(AC,ACNT));
 SAMBALCHK(AC)   = SAM('TOTAL',AC) - SAM(AC,'TOTAL');
 SAMBALCHK(AC)$(ABS(SAMBALCHK(AC)) LT 1E-6) = 0;

*If account balances exceed a critical maximum value, SAMBAL.INC will balance the SAM exactly.
*$INCLUDE includes\1sambal.inc


*------------------------------------------------------------------
*1.4.2  SAM adjustments
*------------------------------------------------------------------

*Minor adjustments are made in the SAM (when needed) to fit the model structure.

*--- Remove small domestic supply values
*    If there is a very small value for domestic sales, add the discrepancy to exports to ensure all domestic production is exported.

PARAMETER
 CHKEXP(C)           activity with all exports to commodity
 EXPSHR(C)           share of domestic production that is exported
;                    

 EXPSHR(C)$SUM(A, SAM(A,C)) = (SAM(C,RW) - SUM(ACNT$MAPTX('EXPTAX',ACNT), SAM(ACNT,C)) - SUM(CTE, SAM(CTE,C))) / SUM(A, SAM(A,C));
 
LOOP(C$(ABS(EXPSHR(C) - 1) LT 1E-4),
 CHKEXP(C) = EXPSHR(C);
 SAM(C,RW) = (SUM(A, SAM(A,C)) + SUM(ACNT$MAPTX('EXPTAX',ACNT), SAM(ACNT,C)) + SUM(CTE, SAM(CTE,C))); 
);

*--- Eliminate payments of any account to itself

 SAM(ACNT,ACNT) = 0;
 
*--- Remove or net out small trade flows (see Adjust sheet)

*Remove small export flows (CXREM)
*   Move export flows and taxes to change in stocks 
 SAM(CXREM,STK) = SAM(CXREM,STK) + SAM(CXREM,RW) - SUM(ACNT$MAPTX('EXPTAX',ACNT), SAM(ACNT,CXREM));
*   Eliminate export flows and taxes from SAM
 SAM(CXREM,RW)  = 0;
 SAM(ACNT,CXREM)$MAPTX('EXPTAX',ACNT) = 0;

*Remove small import flows (CMREM)
*   Move import flows and taxes to change in stocks 
 SAM(CMREM,STK) = SAM(CMREM,STK) - SAM(RW,CMREM) - SUM(ACNT$MAPTX('IMPTAX',ACNT), SAM(ACNT,CMREM));
*   Eliminate import flows and taxes from SAM
 SAM(RW,CMREM)  = 0;
 SAM(ACNT,CMREM)$MAPTX('IMPTAX',ACNT) = 0;
 
*Net out exports (CXNET)      
*   Remove export flows and taxes from import flows
 SAM(RW,CXNET) = SAM(RW,CXNET) - SAM(CXNET,RW) - SUM(ACNT$MAPTX('EXPTAX',ACNT), SAM(ACNT,CXNET)); 
*   Eliminate export flows and taxes from SAM
 SAM(CXNET,RW)  = 0;
 SAM(ACNT,CXNET)$MAPTX('EXPTAX',ACNT) = 0;  

*Net out imports (CMNET)
*   Remove import flows and taxes from export flows
 SAM(CMNET,RW) = SAM(CMNET,RW) - SAM(RW,CMNET) - SUM(ACNT$MAPTX('IMPTAX',ACNT), SAM(ACNT,CMNET)); 
*   Eliminate import flows and taxes from SAM
 SAM(RW,CMNET)  = 0;
 SAM(ACNT,CMNET)$MAPTX('IMPTAX',ACNT) = 0;
 
*Manually re-balance SAM (move imbalances to rest of world)
*   Update total value of stocks (since stocks now include the values of removed exports and imports)
 SAM(STK,SI)  = SUM(C, SAM(C,STK));
*   Update government tax revenues (since import and export taxes may have been removed)
 SAM(GV,TAXES) = 0;
 SAM(GV,TAXES) = SUM(ACNT, SAM(TAXES,ACNT));
*   Update government receipts from rest of world (since total import and export tax revenues may have changed)
 SAM(GV,RW) = 0;
 SAM(GV,RW) = SUM(ACNT, SAM(ACNT,GV) - SAM(GV,ACNT));
*   Update current account balance (since trade flows and government foreign inflows may have changed)
 SAM(SI,RW)  = 0;
 SAM(SI,RW) = SUM(ACNT, SAM(RW,ACNT) - SAM(ACNT,RW));
 
*--- Initialize tax accounts after adjustments

 TAXPAR('ACTTAX',A)    = SUM(ACP$MAPTX('ACTTAX',ACP), SAM(ACP,A));
 TAXPAR('COMTAX',C)    = SUM(ACP$MAPTX('COMTAX',ACP), SAM(ACP,C));
 TAXPAR('EXPTAX',C)    = SUM(ACP$MAPTX('EXPTAX',ACP), SAM(ACP,C));
 TAXPAR('FACTAX',F)    = SUM(ACP$MAPTX('FACTAX',ACP), SAM(ACP,F));
 TAXPAR('IMPTAX',C)    = SUM(ACP$MAPTX('IMPTAX',ACP), SAM(ACP,C));
 TAXPAR('INSTAX',INSD) = SUM(ACP$MAPTX('INSTAX',ACP), SAM(ACP,INSD));
 TAXPAR('VATTAX',A)    = SUM(ACP$MAPTX('VATTAX',ACP), SAM(ACP,A));

*--- Compute transaction cost margins

PARAMETER
 mDOMPRD(C)          domestic production (net of TRC)
 mDOMSAL(C)          domestic sales of domestically produced commodities (net of TRC)
 mEXPORT(C)          exports (net of TRC)
 mIMPORT(C)          imports (net of TRC)
 mMARGIN(C)          transaction cost margin (same for domestic imports and exports)
;                    

*Domestic production (total net of TRC)
 mDOMPRD(C)$SUM(A, SAM(A,C)) = SUM(A, SAM(A,C));

*Imports (net of TRC)
 mIMPORT(C)$SAM(RW,C) = SAM(RW,C) + TAXPAR('IMPTAX',C);

*Transaction margin (implied to be the same for domestic imports and export)
 mMARGIN(C)$(mIMPORT(C) + mDOMPRD(C)) = SAM(CTC,C)/ (mIMPORT(C) + mDOMPRD(C));

*Exports (net of TRC)
 mEXPORT(C)$(1 + mMARGIN(C)) = (SAM(C,RW) - TAXPAR('EXPTAX',C)) / (1 + mMARGIN(C));

*Domestic sales of domestically produced commodities (net of TRC)
 mDOMSAL(C)$SUM(A, SAM(A,C)) = mDOMPRD(C) - mEXPORT(C);

*Update SAM values with disaggregated commodity margin payment values
 SAM(CTE,C)$mEXPORT(C) = mEXPORT(C) * mMARGIN(C);
 SAM(CTM,C)$mIMPORT(C) = mIMPORT(C) * mMARGIN(C);
 SAM(CTD,C)$mDOMSAL(C) = mDOMSAL(C) * mMARGIN(C);

*Update SAM values with disaggregated commodity margin receipts values
 SAM(C,CTE)$SUM(CP, SAM(CP,CTC)) = SAM(C,CTC)/SUM(CP, SAM(CP,CTC)) * SUM(CP, SAM(CTE,CP));
 SAM(C,CTM)$SUM(CP, SAM(CP,CTC)) = SAM(C,CTC)/SUM(CP, SAM(CP,CTC)) * SUM(CP, SAM(CTM,CP));
 SAM(C,CTD)$SUM(CP, SAM(CP,CTC)) = SAM(C,CTC)/SUM(CP, SAM(CP,CTC)) * SUM(CP, SAM(CTD,CP));

*Remove aggregate transaction cost margin account
 SAM(CTC,AC) = 0;
 SAM(AC,CTC) = 0;
 
*--- Check SAM balances after adjustments
 SAM('TOTAL',AC) = 0;
 SAM(AC,'TOTAL') = 0;
 SAM('TOTAL',AC) = SUM(ACNT, SAM(ACNT,AC));
 SAM(AC,'TOTAL') = SUM(ACNT, SAM(AC,ACNT));
 SAMBALCHK(AC)   = SAM('TOTAL',AC) - SAM(AC,'TOTAL');
 SAMBALCHK(AC)$(ABS(SAMBALCHK(AC)) LT 1E-6) = 0;
 

*------------------------------------------------------------------
*1.4.3  Factor quantities
*------------------------------------------------------------------

PARAMETER
 QF2BASE(F,A)        quantity of factor F employed by activity A (extracted data)
 QFSH2BASE(H,F)      household H endowmemt quantity of factor F (extracted data)
 WFH2BASE(H,F)       household H average earnings per unit of factor F (extracted data)
;

*--- Factor employment by sector

*If there is a SAM payment from A to F and neither supply nor demand quantities have been defined in
*   the country data file, then SAM values are used as quantities and wages will equal 1.
 QF2BASE(F,A)$(SAM(F,A) AND (QFBASE(A,F) EQ 0 AND QFSBASE(F) EQ 0)) = SAM(F,A);

*If country's factor employment data is quantities
IF(QWBASE EQ 1, 
*If there are aggregate supplies of QFSBASE(F), then the supply is allocated across sectors according
*   to factor payment shares. In this case, factor wages will be the same across sectors.
 QF2BASE(F,A)$(SAM(F,A) AND QFSBASE(F)) = QFSBASE(F)*SAM(F,A) / SUM(AP, SAM(F,AP));

*If SAM(F,A) exists and sectoral factor quantities QFBASE(F,A) have been specified in the country data
*   file, then they are used. The QF(F,A) values are used even if QFSBASE(F) data have also been provided.
 QF2BASE(F,A)$(QFBASE(A,F) AND SAM(F,A)) = QFBASE(A,F);
); 

*If country's factor employment data is average wages or rental rates
IF(QWBASE EQ 2, 
*If there are aggregate wages in QFSBASE(F), then SAM values are divided by the economywide wage to derive 
*   sector employment quantities. In this case, employment across sectors is proportional to SAM values.
 QF2BASE(F,A)$(SAM(F,A) AND QFSBASE(F)) = SUM(AP, SAM(F,AP)) / QFSBASE(F);

*If SAM(F,A) exists and sectoral factor wages QFBASE(F,A) have been specified in the country data
*   file, then the SAM value is divided by the sector-specific wage to derive employment quantities.  
 QF2BASE(F,A)$(QFBASE(A,F) AND SAM(F,A)) = SAM(F,A) / QFBASE(A,F);
);

*--- Household factor endowment (used to calibrate SHIF)

*If country's household factor endowment data is quantities
IF(QWBASE EQ 1, 
*If there is a factor-to-household payment in the SAM, then use the supplied factor endowment data (even if zero).
 QFSH2BASE(H,F)$SAM(H,F) = QFSHBASE(H,F);
);

*If country's factor endowment data is average wages or rental rates
IF(QWBASE EQ 2,
*If there is a factor-to-household payment in the SAM, then divide this by the supplied factor earnings rate data (if available).
 QFSH2BASE(H,F)$(SAM(H,F) AND QFSHBASE(H,F)) = SAM(H,F)/ QFSHBASE(H,F);
);

*If there is a factor-to-household payment in SAM, but there is no reported household ownership of OR EARNINGS FROM that
*   factor, then treat the factor-to-household payment in the SAM as the household's endowment.
 QFSH2BASE(H,F)$(SAM(H,F) AND QFSHBASE(H,F) EQ 0) = SAM(H,F);

*Scale factor endownments across households to match the total factor supply quantity estimated above. 
 QFSH2BASE(H,F)$SUM(HP, QFSH2BASE(HP,F)) = QFSH2BASE(H,F)/SUM(HP, QFSH2BASE(HP,F)) * SUM(A, QF2BASE(F,A));
 

*------------------------------------------------------------------
*1.4.4. SAM dependent set definitions
*------------------------------------------------------------------

*CD is the set for commodities with domestic sales of domestic output
*   i.e., for which (value of sales at producer prices) > (value of exports at producer prices)
 CD(C)$(SUM(A, SAM(A,C)) GT (SAM(C,RW) - TAXPAR('EXPTAX',C) - SUM(CTE, SAM(CTE,C)))) = YES;
 CDN(C) = NOT CD(C);

*CE is the set for commodities with exports
 CE(C)$SAM(C,RW) = YES;
 CEN(C) = NOT CE(C);

*CE is the set for commodities with imports
 CM(C)$SAM(RW,C) = YES;
 CMN(C) = NOT CM(C);

*CX is the set for commodities with domestic sales
 CX(C)$SUM(A, SAM(A,C)) = YES;

*CT is the set for commodities with demand from transaction cost margins
 CT(C)$(SUM(CTD, SAM(C,CTD)) + SUM(CTE, SAM(C,CTE)) + SUM(CTM, SAM(C,CTM))) = YES;
 
*Mapping between activities and commodities in the supply matrix
* MAPAC(A,C)$SAM(A,C) = YES;

*If activity has no intermediate inputs, then Leontief function must be used at the top of the technology nest
 ACES(A)$(NOT ALEO(A)) = YES;