$TITLE IFPRI Standard CGE Model Version 2.0

$ontext
PART 2.4 (Sections 3-9): Apply closure rules, closure-related shocks, and fix unused variables
 This include file (includes\2static_closures.inc) sets the numeraire and macro and factor market
 closures for each simulation based on information from Excel (see includes\2static_shocks.inc)

SECTIONS:
 2.4.3  Numeraire
 2.4.4  Savings-investment closures
 2.4.5  Current account (rest of world) closures
 2.4.6  Government account closures
 2.4.7  Selecting closure commodities, activities and institutions
 2.4.8  Factor market closures
 2.4.9  Fixing variables not in the model to zero
$offtext


*------------------------------------------------------------------
*2.4.3  Numeraire
*------------------------------------------------------------------

*Numeraire closure 1: Fixed consumer price index
IF(NUMERAIRE(SIMC) EQ 1,
*   Fixed consumer price index
 CPI.FX = CPI0;
*   Flexible domestic price index
 DPI.LO = -INF;
 DPI.UP = +INF;
 DPI.L  = DPI0;
);

*Numeraire closure 2: Fixed domestic price index
IF(NUMERAIRE(SIMC) EQ 2,
*   Flexible consumer price index
 CPI.LO = -INF;
 CPI.UP = +INF;
 CPI.L  = CPI0;  
*   Fixed domestic price index
 DPI.FX = DPI0;
);


*------------------------------------------------------------------
*2.4.4  Savings-investment closures
*------------------------------------------------------------------

*Savings-investment closure 1: Investment-driven savings (uniform adjustments to savings rates)
IF(SICLOSE(SIMC) EQ 1,
*   Fixed scaled MPS for selected institutions
 MPSADJ.FX = MPSADJSIM(SIMC,TC);
*   Flexible uniform MPS rate point change for selected institutions 
 DMPS.LO   = -INF;
 DMPS.UP   = +INF;
 DMPS.L    = DMPSSIM(SIMC,TC);
*   Fixed investment demand quantity adjustment factors
 IADJ.FX   = IADJSIM(SIMC,TC);
*   Flexible absorption shares for investment demand
 INVSHR.LO = -INF;
 INVSHR.UP = +INF;
 INVSHR.L  = INVSHRSIM(SIMC,TC);
*   Fixed government demand quantity adjustment factors
 GADJ.FX   = GADJSIM(SIMC,TC);
*   Flexible absorption share for government demand
 GOVSHR.LO = -INF;
 GOVSHR.UP = +INF;
 GOVSHR.L  = GOVSHRSIM(SIMC,TC);
);

*Savings-investment closure 2: Investment-driven savings (scaled adjustments to savings rates)
IF(SICLOSE(SIMC) EQ 2,
*   Flexible scaled MPS for selected institutions
 MPSADJ.LO = -INF;
 MPSADJ.UP = +INF;
 MPSADJ.L  = MPSADJSIM(SIMC,TC);
*   Fixed uniform MPS rate point change for selected institutions 
 DMPS.FX   = DMPSSIM(SIMC,TC);
*   Fixed investment demand quantity adjustment factors
 IADJ.FX   = IADJSIM(SIMC,TC);
*   Flexible absorption shares for investment demand
 INVSHR.LO = -INF;
 INVSHR.UP = +INF;
 INVSHR.L  = INVSHRSIM(SIMC,TC);
*   Fixed government demand quantity adjustment factors
 GADJ.FX   = GADJSIM(SIMC,TC);
*   Flexible absorption share for government demand
 GOVSHR.LO = -INF;
 GOVSHR.UP = +INF;
 GOVSHR.L  = GOVSHRSIM(SIMC,TC);
);

*Savings-investment closure 3: Savings-driven investment
IF(SICLOSE(SIMC) EQ 3,
*   Fixed scaled MPS for selected institutions
 MPSADJ.FX = MPSADJSIM(SIMC,TC);
*   Fixed uniform MPS rate point change for selected institutions 
 DMPS.FX   = DMPSSIM(SIMC,TC);
*   Flexible investment demand quantity adjustment factors
 IADJ.LO   = -INF;
 IADJ.UP   = +INF;
 IADJ.L    = IADJSIM(SIMC,TC);
*   Flexible absorption shares for investment demand
 INVSHR.LO = -INF;
 INVSHR.UP = +INF;
 INVSHR.L  = INVSHRSIM(SIMC,TC);
*   Fixed government demand quantity adjustment factors
 GADJ.FX   = GADJSIM(SIMC,TC);
*   Flexible absorption share for government demand
 GOVSHR.LO = -INF;
 GOVSHR.UP = +INF;
 GOVSHR.L  = GOVSHRSIM(SIMC,TC);
);

*Savings-investment closure 4: Balanced closure (uniform adjustments to savings rates)
IF(SICLOSE(SIMC) EQ 4,
*   Fixed scaled MPS for selected institutions
 MPSADJ.FX = MPSADJSIM(SIMC,TC);
*   Flexible uniform MPS rate point change for selected institutions 
 DMPS.LO   = -INF;
 DMPS.UP   = +INF;
 DMPS.L    = DMPSSIM(SIMC,TC);
*   Flexible investment demand quantity adjustment factors
 IADJ.LO   = -INF;
 IADJ.UP   = +INF;
 IADJ.L    = IADJSIM(SIMC,TC);
*   Fixed absorption shares for investment demand
 INVSHR.FX = INVSHRSIM(SIMC,TC);
*   Flexible government demand quantity adjustment factors
 GADJ.LO   = -INF;
 GADJ.UP   = +INF;
 GADJ.L    = GADJSIM(SIMC,TC);
*   Fixed absorption share for government demand
 GOVSHR.FX = GOVSHRSIM(SIMC,TC);
);
 
*Savings-investment closure 5: Balanced closure (uniform adjustments to savings rates)
IF(SICLOSE(SIMC) EQ 5,
*Balanced closure (scaled adjustments to savings rates)
*   Flexible scaled MPS for selected institutions
 MPSADJ.LO = -INF;
 MPSADJ.UP = +INF;
 MPSADJ.L  = MPSADJSIM(SIMC,TC);
*   Fixed uniform MPS rate point change for selected institutions 
 DMPS.FX   = DMPSSIM(SIMC,TC);
*   Flexible investment demand quantity adjustment factors
 IADJ.LO   = -INF;
 IADJ.UP   = +INF;
 IADJ.L    = IADJSIM(SIMC,TC);
*   Fixed absorption shares for investment demand
 INVSHR.FX = INVSHRSIM(SIMC,TC);
*   Flexible government demand quantity adjustment factors
 GADJ.LO   = -INF;
 GADJ.UP   = +INF;
 GADJ.L    = GADJSIM(SIMC,TC);
*   Fixed absorption share for government demand
 GOVSHR.FX = GOVSHRSIM(SIMC,TC);
);


*------------------------------------------------------------------
*2.4.5  Current account (rest of world) closures
*------------------------------------------------------------------

*Current account closure 1: Fixed foreign savings
IF(ROWCLOSE(SIMC) EQ 1,
*   Flexible exchange rate
 EXR.LO   = -INF;
 EXR.UP   = +INF;
 EXR.L    = EXRSIM(SIMC,TC);
*   Fixed foreign savings
 FSAV.FX  = FSAVSIM(SIMC,TC);
);

*Current account closure 2: Fixed exchange rate
IF(ROWCLOSE(SIMC) EQ 2,
*   Fixed exchange rate
 EXR.FX   = EXRSIM(SIMC,TC);
*   Flexible foreign savings
 FSAV.LO  = -INF;
 FSAV.UP  = +INF;
 FSAV.L   = FSAVSIM(SIMC,TC);
);


*------------------------------------------------------------------
*2.4.6  Government account closures
*------------------------------------------------------------------

*Government closure 1: Government savings are flexible and all direct and indirect tax rates are fixed
IF(GOVCLOSE(SIMC) EQ 1,
*   Flexible government savings
 GSAV.LO     = -INF;
 GSAV.UP     = +INF;
 GSAV.L      = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 2: Government savings are fixed and direct tax rates adjust (uniform adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 2,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.LO      = -INF;
 DTI.UP      = +INF;
 DTI.L       = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 3: Government savings are fixed and direct tax rates adjust (scaled adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 3,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.LO    = -INF;
 TIADJ.UP    = +INF; 
 TIADJ.L     = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 4: Government savings are fixed and composite commodity tax rates adjust (uniform adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 4,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.LO      = -INF;
 DTQ.UP      = +INF; 
 DTQ.L       = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 5: Government savings are fixed and composite commodity tax rates adjust (scaled adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 5,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.LO    = -INF;
 TQADJ.UP    = +INF; 
 TQADJ.L     = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 6: Government savings are fixed and activity tax rates adjust (uniform adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 6,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.LO      = -INF;
 DTA.UP      = +INF; 
 DTA.L       = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 7: Government savings are fixed and activity tax rates adjust (scaled adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 7,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.LO    = -INF;
 TAADJ.UP    = +INF; 
 TAADJ.L     = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 8: Government savings are fixed and import tariff rates adjust (uniform adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 8,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.LO      = -INF;
 DTM.UP      = +INF; 
 DTM.L       = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 9: Government savings are fixed and import tariff rates adjust (scaled adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 9,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX   = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX     = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.LO    = -INF;
 TMADJ.UP    = +INF; 
 TMADJ.L     = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 10: Government savings are fixed and export tax rates adjust (uniform adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 10,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.LO      = -INF;
 DTE.UP      = +INF; 
 DTE.L       = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 11: Government savings are fixed and export tax rates adjust (scaled adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 11,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.LO    = -INF;
 TEADJ.UP    = +INF; 
 TEADJ.L     = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 12: Government savings are fixed and value-added tax rates adjust (uniform adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 12,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.LO      = -INF;
 DTV.UP      = +INF;
 DTV.L       = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 13: Government savings are fixed and value-added tax rates adjust (scaled adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 13,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.LO    = -INF;
 TVADJ.UP    = +INF;
 TVADJ.L     = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);

*Government closure 14: Government savings are fixed and factor tax rates adjust (uniform adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 14,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.FX    = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.LO      = -INF;
 DTF.UP      = +INF;
 DTF.L       = DTFSIM(SIMC,TC);
);

*Government closure 15: Government savings are fixed and factor tax rates adjust (scaled adjustments to tax rates)
IF(GOVCLOSE(SIMC) EQ 15,
*   Flexible government savings
 GSAV.FX     = GSAVSIM(SIMC,TC);
*   Fixed scaled direct taxes (TINS) for selected institutions
 TIADJ.FX    = TIADJSIM(SIMC,TC);
*   Fixed uniform direct taxes (TINS) for selected institutions
 DTI.FX      = DTISIM(SIMC,TC);
*   Fixed scaled composite commodity taxes (TQ) for selected commodities
 TQADJ.FX    = TQADJSIM(SIMC,TC);
*   Fixed uniform composite commodity taxes (TQ) for selected commodities
 DTQ.FX      = DTQSIM(SIMC,TC);
*   Fixed scaled activity taxes (TA) for selected activities
 TAADJ.FX    = TAADJSIM(SIMC,TC);
*   Fixed uniform activity taxes (TA) for selected activities
 DTA.FX      = DTASIM(SIMC,TC);
*   Fixed scaled import tariffs (TM) for selected commodities
 TMADJ.FX    = TMADJSIM(SIMC,TC);
*   Fixed uniform import tariffs (TM) for selected commodities
 DTM.FX      = DTMSIM(SIMC,TC);
*   Fixed scaled export taxes (TE) for selected commodities
 TEADJ.FX    = TEADJSIM(SIMC,TC);
*   Fixed uniform export taxes (TE) for selected commodities
 DTE.FX      = DTESIM(SIMC,TC);
*   Fixed scaled value-added taxes (TVA) for selected activities
 TVADJ.FX    = TVADJSIM(SIMC,TC);
*   Fixed uniform value-added taxes (TVA) for selected activities
 DTV.FX      = DTVSIM(SIMC,TC);
*   Fixed scaled factor taxes (TF) for selected factors
 TFADJ.LO    = -INF;
 TFADJ.UP    = +INF;
 TFADJ.L     = TFADJSIM(SIMC,TC);
*   Fixed uniform factor taxes (TF) for selected factors
 DTF.FX      = DTFSIM(SIMC,TC);
);


*------------------------------------------------------------------
*2.4.7  Selecting closure commodities, activities and institutions
*------------------------------------------------------------------

*  Institutions with potentially flexible savings and direct tax rates.
 mps01(INSDNG)  = MPS01SIM(INSDNG,SIMC);        
 ti01(INSDNG)   = TI01SIM(INSDNG,SIMC);       

*  Activities with potentially flexible tax rates.
 ta01(A)        = TA01SIM(A,SIMC);      
 tv01(A)        = TV01SIM(A,SIMC);

*  Commodities with potentially flexible tax rates.
 te01(C)        = TE01SIM(C,SIMC);      
 tm01(C)        = TM01SIM(C,SIMC);   
 tq01(C)        = TQ01SIM(C,SIMC);      

*  Factors with potentially flexible tax rates.
 tf01(F)        = TF01SIM(F,SIMC);
 

*------------------------------------------------------------------
*2.4.8  Factor market closures
*------------------------------------------------------------------

*Factor closure 1: Factors are fully employed and mobile between activities. WF is the market-clearing variable for each factor.
LOOP(F$(FACCLOSE(F,SIMC) EQ 1),
*   Fixed total factor supply 
 QFS.FX(F)           = QFSSIM(F,SIMC,TC);
*   Flexible economywide wage rate
 WF.LO(F)            = -INF;
 WF.UP(F)            = +INF;
 WF.L(F)             = WFSIM(F,SIMC,TC);
*   Fixed sector-specific wage distortion variable 
 WFDIST.FX(F,A)      = WFDIST0(F,A);
*   Flexible factor demand by activity 
 QF.LO(F,A)$QF0(F,A) = -INF;
 QF.UP(F,A)$QF0(F,A) = +INF;
 QF.L(F,A)$QF0(F,A)  = QFSIM(F,A,SIMC,TC);
);

*Factor closure 2: Factors are fully employed and activity-specific. WFDIST(F,A) is the clearing variable, one for each segment of the factor market.
LOOP(F$(FACCLOSE(F,SIMC) EQ 2),
*   Flexible total factor supply 
 QFS.LO(F)           = -INF;
 QFS.UP(F)           = +INF;
 QFS.L(F)            = QFSSIM(F,SIMC,TC);
*   Fixed economywide wage rate
 WF.FX(F)            = WFSIM(F,SIMC,TC);
*   Flexible sector-specific wage distortion variable 
 WFDIST.LO(F,A)$QF0(F,A) = -INF;
 WFDIST.UP(F,A)$QF0(F,A) = +INF;
 WFDIST.L(F,A)$QF0(F,A)  = WFDIST0(F,A);
*   Fixed factor demand by activity 
 QF.FX(F,A)          = QFSIM(F,A,SIMC,TC);
);

*Factor closure 3: Factors are unemployed and mobile. For each activity, the wage WFDIST*WF is fixed. QFS is the market-clearing variable for the unified labor market.
LOOP(F$(FACCLOSE(F,SIMC) EQ 3),
*   Flexible total factor supply 
 QFS.LO(F)           = -INF;
 QFS.UP(F)           = +INF;
 QFS.L(F)            = QFSSIM(F,SIMC,TC); 
*   Fixed economywide wage rate
 WF.FX(F)            = WFSIM(F,SIMC,TC);
*   Fixed sector-specific wage distortion variable 
 WFDIST.FX(F,A)      = WFDIST0(F,A);
*   Flexible factor demand by activity 
 QF.LO(F,A)$QF0(F,A) = -INF;
 QF.UP(F,A)$QF0(F,A) = +INF;
 QF.L(F,A)$QF0(F,A)  = QFSIM(F,A,SIMC,TC);
);

*Fixed capital by activity (even with general capital mobility)
LOOP(A$AFIXCAP(A,SIMC),
*   Fixed factor use in selected activity 
 QF.FX(FCAP,A)                 = QFSIM(FCAP,A,SIMC,TC);
*   Flexible sector-specific wage distortion variable 
 WFDIST.LO(FCAP,A)$QF0(FCAP,A) = -INF;
 WFDIST.UP(FCAP,A)$QF0(FCAP,A) = +INF;
 WFDIST.L(FCAP,A)$QF0(FCAP,A)  = WFDIST0(FCAP,A);
);

*Fixed land by activity (even with general land mobility)
LOOP(A$AFIXLND(A,SIMC),
*   Fixed factor use in selected activity 
 QF.FX(FLND,A)                 = QFSIM(FLND,A,SIMC,TC);
*   Flexible sector-specific wage distortion variable 
 WFDIST.LO(FLND,A)$QF0(FLND,A) = -INF;
 WFDIST.UP(FLND,A)$QF0(FLND,A) = +INF;
 WFDIST.L(FLND,A)$QF0(FLND,A)  = WFDIST0(FLND,A);
);


*------------------------------------------------------------------
*2.4.9  Fixing variables not in the model to zero
*------------------------------------------------------------------

 PA.FX(A)$(NOT AA(A))                    = 0;
 PDD.FX(C)$(NOT CD(C))                   = 0;
 PDS.FX(C)$(NOT CD(C))                   = 0;
 PE.FX(C)$(NOT CE(C))                    = 0;
 PM.FX(C)$(NOT CM(C))                    = 0;
 PVA.FX(A)$(NOT QVA0(A))                 = 0;
 PX.FX(C)$(NOT CX(C))                    = 0;
 PXAC.FX(A,C)$(NOT SAM(A,C))             = 0;
 QA.FX(A)$(NOT AA(A))                    = 0;
 QD.FX(C)$(NOT CD(C))                    = 0;
 QE.FX(C)$(NOT CE(C))                    = 0;
 QF.FX(F,A)$(NOT QF0(F,A))               = 0;
 QG.FX(C)$(NOT SAM(C,GV))                = 0;
 QH.FX(C,H)$(NOT SAM(C,H))               = 0;
 QHA.FX(A,H)$(NOT SAM(A,H))              = 0;
 QINT.FX(C,A)$(NOT SAM(C,A))             = 0;
 QINV.FX(C)$(NOT SAM(C,SI))              = 0;
 QM.FX(C)$(NOT CM(C))                    = 0;
 QQ.FX(C)$(NOT (CD(C) OR CM(C)))         = 0;
 QT.FX(C)$(NOT CT(C))                    = 0;
 QVA.FX(A)$(NOT QVA0(A))                 = 0;
 QX.FX(C)$(NOT CX(C))                    = 0;
 QXAC.FX(A,C)$(NOT SAM(A,C))             = 0;
 TRII.FX(INS,INSP)$(NOT TRII0(INS,INSP)) = 0;
 YI.FX(INS)$(NOT YI0(INS))               = 0;
 YIF.FX(INS,F)$(NOT YIF0(INS,F))         = 0;
 YF.FX(F)$(NOT YF0(F))                   = 0;