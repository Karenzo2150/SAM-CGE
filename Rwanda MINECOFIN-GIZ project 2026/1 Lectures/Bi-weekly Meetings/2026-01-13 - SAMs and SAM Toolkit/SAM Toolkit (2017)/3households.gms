*NEXUS 58 sector SAM Building Toolkit
*Step 2: National SAM with disaggregated household and labor accounts

$setglobal input  "3HHD_X104_2017"
$setglobal output "0output"
$setglobal check "0households"

*$call "xlstalk -s %input%.xlsx"
$call "gdxxrw i=%input%.xlsx o=%input%.gdx index=index!a7"
$gdxin %input%.gdx
*$call "xlstalk -o %input%.xlsx"

SET
 X                income or expenditure /inc,exp/
*SAM sets
 AC               micro SAM accounts
 ACNT(AC)         micro SAM accounts without total
 A(AC)            activities - all
 ALIV(A)          activities - livestock
 AMIN(A)          activities - mining
 C(AC)            commodities
 F(AC)            factors - all
 FLAB(F)          factors - labor
 FLND(F)          factors - land
 FCAP(F)          factors - capital
 FREM(F)          factors - to be removed
 H(AC)            households
 T(AC)            taxes
 FOOD(AC)         food items (activities and commodities)
*Data sets
 MAC              macro SAM accounts
 MACNT(MAC)       macro SAM accounts without total
 AAC(AC)          national SAM accounts (same aggregation as Step 1)
 AACNT(AAC)       national SAM accounts without total
*Mappings
 MAPAC(A,C)       mapping macro-micro accounts
 MAPMAC(MAC,AC)   mapping activities-commodities
 MAPAACAC(AAC,AC) mapping national-all
;

$load    MAC AC
$loaddc  AAC A ALIV AMIN C F FLAB FLND FCAP H T FOOD MAPAC MAPMAC MAPAACAC

 ACNT(AC) = YES;
 ACNT('TOTAL') = NO;

 MACNT(MAC) = YES;
 MACNT('MTOT') = NO;

 AACNT(AAC) = YES;
 AACNT('TOTAL') = NO;

ALIAS
 (MAC,MACP), (MACNT,MACNTP), (AC,ACP), (ACNT,ACNTP), (AAC,AACP), (AACNT,AACNTP)
 (A,AP), (ALIV,ALIVP), (AMIN,AMINP), (C,CP)
 (F,FP), (FLAB,FLABP), (FLND,FLNDP), (FCAP,FCAPP)
 (H,HP,HPP), (T,TP)
;

PARAMETERS
 SCALE           scaling multiplier      / 1.000 /
*Data parameters
 SAM(AC,ACP)     micro SAM
 FACACT(A,F)     factor income generation
 MISCFAC(F,X,AC) miscellaneous factor accounts
 HHDFAC(H,F)     factor payments to households
 OWNSHR(A)       own consumption share of total household consumption
 ACTHHD(A,H)     household own consumption
 COMHHD(C,H)     household market consumption
 MISCHHD(H,X,AC) miscellaneous household accounts
 HHDDATA(H,*)    survey household consumption and population data
*Working parameters
 MSAM(MAC,MACP)  macro SAM
 ASAM(AAC,AACP)  aggregate national SAM
 FACSHR(A,F)     factor income shares
 ACTSHR(A,H)     own consumption shares
 COMSHR(C,H)     marketed consumption shares
;

$loaddc FACACT HHDFAC OWNSHR ACTHHD COMHHD
$load   MISCFAC MISCHHD HHDDATA

*$call "xlstalk -s %output%.xlsx"
$call "gdxxrw i=%output%.xlsx o=%output%.gdx index=index!a15"
$gdxin %output%.gdx

$load SAM

*Preparation work ------

*Check ranges in data tables
*  Note: Returns error on negative transfers and savings rates
 FACACT(A,F)$(FACACT(A,F) LT 0) = 1/0;
 MISCFAC(F,X,AC)$(MISCFAC(F,X,AC) LT 0) = 1/0;
 ACTHHD(A,H)$(ACTHHD(A,H) LT 0) = 1/0;
 COMHHD(C,H)$(COMHHD(C,H) LT 0) = 1/0;
 MISCHHD(H,X,AC)$(MISCHHD(H,X,AC) LT 0) = 1/0;
 OWNSHR(A)$(OWNSHR(A) LT 0) = 1/0;
 OWNSHR(A)$(OWNSHR(A) GT 1) = 1/0;

*Separate own and marketed consumption
 SAM(A,'HHD') = OWNSHR(A) * SUM(C$MAPAC(A,C), SAM(C,'HHD'));
 SAM(C,'HHD') = SAM(C,'HHD') - SUM(A$MAPAC(A,C), SAM(A,'HHD'));
 SAM(A,C)$MAPAC(A,C) = SAM(A,C) - SAM(A,'HHD');

*Separate own and marketed consumption
* SAM(A,'HHD') = OWNSHR(A) * SUM(C$MAPAC(A,C), SAM(C,'HHD'));
* SAM(C,'HHD') = SAM(C,'HHD') - SUM(A$MAPAC(A,C), SAM(A,'HHD'));
* SAM(A,C)$SAM(A,C) = SAM(A,C)/SUM(CP, SAM(A,CP)) * SUM(CP, SAM(A,CP)) - SAM(A,'HHD');

*Scale SAM
 SAM(AC,ACP) = SAM(AC,ACP) * SCALE;
*Calculate national and macro SAM control totals
 MSAM(MAC,MACP) = SUM((AC,ACP)$(MAPMAC(MAC,AC) AND MAPMAC(MACP,ACP)), SAM(AC,ACP));
 ASAM(AAC,AACP) = SUM((AC,ACP)$(MAPAACAC(AAC,AC) AND MAPAACAC(AACP,ACP)), SAM(AC,ACP));

*Factors -----------

SET
 FINCAC(AC)      misc factor income accounts      / GOV, ROW /
 FEXPAC(AC)      misc factor expenditure accounts / FTAX, GOV, ROW /
;

*Calculate factor shares (assign to aggregate if missing)
*  Labor
 FACSHR(A,FLAB)$SUM(FLABP, FACACT(A,FLABP)) = FACACT(A,FLAB) / SUM(FLABP, FACACT(A,FLABP));
 FACSHR(A,'FLAB')$(NOT SUM(FLABP, ABS(FACACT(A,FLABP)))) = 1.00;
*  Land
 FACSHR(A,FLND)$SUM(FLNDP, FACACT(A,FLNDP)) = FACACT(A,FLND) / SUM(FLNDP, FACACT(A,FLNDP));
 FACSHR(A,'FLND')$(NOT SUM(FLNDP, ABS(FACACT(A,FLNDP)))) = 1.00;
*  Capital
 FACSHR(A,FCAP)$SUM(FCAPP, FACACT(A,FCAPP)) = FACACT(A,FCAP) / SUM(FCAPP, FACACT(A,FCAPP));
 FACSHR(A,'FCAP')$(NOT SUM(FCAPP, ABS(FACACT(A,FCAPP)))) = 1.00;

*Apply factor income shares to SAM
 SAM(FLAB,A) = FACSHR(A,FLAB) * SAM('FLAB',A);
 SAM(FLND,A) = FACSHR(A,FLND) * SAM('FLND',A);
 SAM(FCAP,A) = FACSHR(A,FCAP) * SAM('FCAP',A);

*Assume aggregate factors without activity incomes are to be removed
 FREM('FLAB')$(NOT SUM(A, SAM('FLAB',A))) = YES;
 FREM('FLND')$(NOT SUM(A, SAM('FLND',A))) = YES;
 FREM('FCAP')$(NOT SUM(A, SAM('FCAP',A))) = YES;

*Miscellaneous factor incomes
*  If no information, then set default to macro SAM
 MISCFAC(FLAB,'INC',FINCAC)$(NOT SUM(FLABP, MISCFAC(FLABP,'INC',FINCAC))) = SUM(MAC$MAPMAC(MAC,FINCAC), MSAM('MLAB',MAC))/MSAM('MLAB','MACT');
 MISCFAC(FLND,'INC',FINCAC)$(NOT SUM(FLNDP, MISCFAC(FLNDP,'INC',FINCAC))) = SUM(MAC$MAPMAC(MAC,FINCAC), MSAM('MLND',MAC))/MSAM('MLND','MACT');
 MISCFAC(FCAP,'INC',FINCAC)$(NOT SUM(FCAPP, MISCFAC(FCAPP,'INC',FINCAC))) = SUM(MAC$MAPMAC(MAC,FINCAC), MSAM('MCAP',MAC))/MSAM('MCAP','MACT');
*  Rate-based using factor incomes from activities
 SAM(F,FINCAC) = MISCFAC(F,'INC',FINCAC) * SUM(A, SAM(F,A));
*  Remove aggregate factors and then scale to match macro SAM totals
 SAM(FREM,FINCAC) = 0;
 SAM(FLAB,FINCAC)$SUM(FLABP, SAM(FLABP,FINCAC)) = SAM(FLAB,FINCAC) * SUM(MAC$MAPMAC(MAC,FINCAC), MSAM('MLAB',MAC)) / SUM(FLABP, SAM(FLABP,FINCAC));
 SAM(FLND,FINCAC)$SUM(FLNDP, SAM(FLNDP,FINCAC)) = SAM(FLND,FINCAC) * SUM(MAC$MAPMAC(MAC,FINCAC), MSAM('MLND',MAC)) / SUM(FLNDP, SAM(FLNDP,FINCAC));
 SAM(FCAP,FINCAC)$SUM(FCAPP, SAM(FCAPP,FINCAC)) = SAM(FCAP,FINCAC) * SUM(MAC$MAPMAC(MAC,FINCAC), MSAM('MCAP',MAC)) / SUM(FCAPP, SAM(FCAPP,FINCAC));

*Miscellaneous factor payments
*  If no information, then set default to macro SAM
 MISCFAC(FLAB,'EXP',FEXPAC)$(NOT SUM(FLABP, MISCFAC(FLABP,'EXP',FEXPAC))) = SUM(MAC$MAPMAC(MAC,FEXPAC), MSAM(MAC,'MLAB'))/MSAM('MTOT','MLAB');
 MISCFAC(FLND,'EXP',FEXPAC)$(NOT SUM(FLNDP, MISCFAC(FLNDP,'EXP',FEXPAC))) = SUM(MAC$MAPMAC(MAC,FEXPAC), MSAM(MAC,'MLND'))/MSAM('MTOT','MLND');
 MISCFAC(FCAP,'EXP',FEXPAC)$(NOT SUM(FCAPP, MISCFAC(FCAPP,'EXP',FEXPAC))) = SUM(MAC$MAPMAC(MAC,FEXPAC), MSAM(MAC,'MCAP'))/MSAM('MTOT','MCAP');
*  Rate-based using total factor incomes
 SAM(FEXPAC,F) = MISCFAC(F,'EXP',FEXPAC) * SUM(ACNT, SAM(F,ACNT));
*  Remove aggregate factors and then scale to match macro SAM totals
 SAM(FEXPAC,FREM) = 0;
 SAM(FEXPAC,FLAB)$SUM(FLABP, SAM(FEXPAC,FLABP)) = SAM(FEXPAC,FLAB) * SUM(MAC$MAPMAC(MAC,FEXPAC), MSAM(MAC,'MLAB')) / SUM(FLABP, SAM(FEXPAC,FLABP));
 SAM(FEXPAC,FLND)$SUM(FLNDP, SAM(FEXPAC,FLNDP)) = SAM(FEXPAC,FLND) * SUM(MAC$MAPMAC(MAC,FEXPAC), MSAM(MAC,'MLND')) / SUM(FLNDP, SAM(FEXPAC,FLNDP));
 SAM(FEXPAC,FCAP)$SUM(FCAPP, SAM(FEXPAC,FCAPP)) = SAM(FEXPAC,FCAP) * SUM(MAC$MAPMAC(MAC,FEXPAC), MSAM(MAC,'MCAP')) / SUM(FCAPP, SAM(FEXPAC,FCAPP));

*Net factor payments to households and enterprises
 SAM('HHD',F) = 0;
 SAM('ENT',F) = 0;
 SAM('HHD',FLAB) = SUM(ACNT, SAM(FLAB,ACNT) - SAM(ACNT,FLAB));
 SAM('HHD',FLND) = SUM(ACNT, SAM(FLND,ACNT) - SAM(ACNT,FLND));
 SAM('ENT',FCAP) = SUM(ACNT, SAM(FCAP,ACNT) - SAM(ACNT,FCAP));
*  Make agricultural crop and livestock capital pay directly to households
 SAM('HHD','FCAP-C') = SAM('ENT','FCAP-C');
 SAM('HHD','FCAP-L') = SAM('ENT','FCAP-L');
 SAM('HHD','ENT') = SAM('HHD','ENT') - SAM('ENT','FCAP-C') - SAM('ENT','FCAP-L');
 SAM('ENT','FCAP-C') = 0;
 SAM('ENT','FCAP-L') = 0;

*Households -----------

SET
 HINCAC(AC)      misc household income accounts      / ENT, GOV, ROW /
 HEXPAC(AC)      misc household expenditure accounts / DTAX, GOV, S-I, ROW /
;

*Household consumption shares
*  Own consumption
 ACTSHR(A,H)$SUM(HP, ACTHHD(A,HP)) = ACTHHD(A,H)/SUM(HP, ACTHHD(A,HP));
 ACTSHR(A,'HHD')$(NOT SUM(HP, ACTSHR(A,HP)) AND SAM(A,'HHD')) = 1.00;
*  Marketed consumption
 COMSHR(C,H)$SUM(HP, COMHHD(C,HP)) = COMHHD(C,H)/SUM(HP, COMHHD(C,HP));
 COMSHR(C,'HHD')$(NOT SUM(HP, COMSHR(C,HP)) AND SAM(C,'HHD')) = 1.00;

*Apply consumption shares to SAM
 SAM(A,H) = ACTSHR(A,H) * SAM(A,'HHD');
 SAM(C,H) = COMSHR(C,H) * SAM(C,'HHD');

*Miscellaneous household expenditures
*  If no information, then set default to macro SAM
 MISCHHD(H,'EXP',HEXPAC)$(NOT SUM(HP, MISCHHD(HP,'EXP',HEXPAC))) = SUM(MAC$MAPMAC(MAC,HEXPAC), MSAM(MAC,'MHHD'))/MSAM('MCOM','MHHD');
*  Rate-based using total consumption spending
 SAM(HEXPAC,H) = MISCHHD(H,'EXP',HEXPAC) * (SUM(A, SAM(A,H)) + SUM(C, SAM(C,H)));
*  Scale to match macro SAM totals
 SAM(HEXPAC,H)$SUM(HP, SAM(HEXPAC,HP)) = SAM(HEXPAC,H) * SUM(MAC$MAPMAC(MAC,HEXPAC), MSAM(MAC,'MHHD')) / SUM(HP, SAM(HEXPAC,HP));

*Household incomes from factors (share-based)
*  If no information, then set default to macro SAM
 HHDFAC('HHD',F)$(NOT SUM(HP, HHDFAC(HP,F))) = 1.00;
*  Rate-based using total factor income payments to aggregate households
 SAM(H,F)$SUM(HP, HHDFAC(HP,F)) = HHDFAC(H,F)/SUM(HP, HHDFAC(HP,F)) * SAM('HHD',F);

*Miscellaneous household incomes
*  If no information, then set default to macro SAM
 MISCHHD(H,'INC',HINCAC)$(NOT SUM(HP, MISCHHD(HP,'INC',HINCAC))) = SUM(MAC$MAPMAC(MAC,HINCAC), MSAM('MHHD',MAC))/MSAM('MHHD','MTOT');
*  Rate-based using total household spending
 SAM(H,HINCAC) = MISCHHD(H,'INC',HINCAC) * SUM(ACNT, SAM(ACNT,H));
*  Scale to match macro SAM totals
 SAM(H,HINCAC)$SUM(HP, SAM(HP,HINCAC)) = SAM(H,HINCAC) * SUM(MAC$MAPMAC(MAC,HINCAC), MSAM('MHHD',MAC)) / SUM(HP, SAM(HP,HINCAC));

*Scale down household incomes from enterprises
 SAM(H,'ENT') = SAM(H,'ENT') * (MSAM('MHHD','MENT')-SUM((HP,FCAP), SAM(HP,FCAP)))/SUM(HP, SAM(HP,'ENT'));

*Optional RAS balancing -------
*   RAS household incomes to match expenditures (retain income source pattern)

SET  COUNT / 1*100 /;
PARAMETER
 RAS       / 0 /
 HHDINC(AC)
;
IF(RAS = 1,
 LOOP(COUNT,
  HHDINC(ACNT) = SUM(H, SAM(H,ACNT));
  SAM(H,ACNT)$SUM(ACNTP, SAM(H,ACNTP)) = SAM(H,ACNT) * SUM(ACNTP, SAM(ACNTP,H)) / SUM(ACNTP, SAM(H,ACNTP));
  SAM(H,ACNT)$SUM(HP, SAM(HP,ACNT)) = SAM(H,ACNT) * HHDINC(ACNT) / SUM(HP, SAM(HP,ACNT));
 );
);


*Check balances -------

PARAMETER
 DIFF(AC,*)
 MDIFF(MAC,MACP)
 ADIFF(AAC,AACP)
;

*Check totals for prior micro SAM
 SAM(ACNT,'TOTAL') = SUM(ACNTP, SAM(ACNT,ACNTP));
 SAM('TOTAL',ACNT) = SUM(ACNTP, SAM(ACNTP,ACNT));
 DIFF(ACNT,'DIFF') = SAM(ACNT,'TOTAL')-SAM('TOTAL',ACNT);
 DIFF(ACNT,'DIFF')$(ABS(DIFF(ACNT,'DIFF')) LT 1E-6) = 0;
 DIFF(ACNT,'PDIFF')$SAM('TOTAL',ACNT) = DIFF(ACNT,'DIFF') / SAM('TOTAL',ACNT) * 100;

*Differences between original and final macro SAM
 MDIFF(MACNT,MACNTP) = SUM((ACNT,ACNTP)$(MAPMAC(MACNT,ACNT) AND MAPMAC(MACNTP,ACNTP)), SAM(ACNT,ACNTP)) - MSAM(MACNT,MACNTP);
 MDIFF(MACNT,MACNTP)$(ABS(MDIFF(MACNT,MACNTP)) lt 1E-6) = 0;

*Differences between original and final micro SAM
 ADIFF(AACNT,AACNTP) = SUM((ACNT,ACNTP)$(MAPAACAC(AACNT,ACNT) AND MAPAACAC(AACNTP,ACNTP)), SAM(ACNT,ACNTP)) - ASAM(AACNT,AACNTP);
 ADIFF(AACNT,AACNTP)$(ABS(ADIFF(AACNT,AACNTP)) lt 1E-6) = 0;

OPTION ADIFF:2:1:1, MDIFF:2:1:1, DIFF:2:1:1;
DISPLAY
 ADIFF, MDIFF
 "Income - Expenditure"
 DIFF
;

SET
 INCAC(AC)       permissable household income accounts
 EXPAC(AC)       permissable household expenditure accounts
;

 INCAC(F) = YES;
 INCAC('ENT') = YES;
 INCAC('GOV') = YES;
 INCAC('ROW') = YES;
 INCAC('TOTAL') = YES;

 EXPAC('AMAIZ') = YES;
 EXPAC('CMAIZ') = YES;
 EXPAC('CFOOD') = YES;
 EXPAC('GOV') = YES;
 EXPAC('DTAX') = YES;
 EXPAC('S-I') = YES;
 EXPAC('ROW') = YES;
 EXPAC('TOTAL') = YES;

PARAMETER
 INCTAB(H,AC)    household income table
 EXPTAB(H,AC)    household expennditure table
 POPTAB(H,*)
;

*Household income data (for checking)
 INCTAB(H,INCAC) = SAM(H,INCAC);
 EXPTAB(H,EXPAC) = SAM(EXPAC,H);
 EXPTAB(H,'AMAIZ') = SUM(A, SAM(A,H));
 EXPTAB(H,'CMAIZ') = SUM(C, SAM(C,H));
 EXPTAB(H,'CFOOD') = SUM(FOOD, SAM(FOOD,H));

*$call "xlstalk -s %check%.xlsx"
*execute_unload "%check%.gdx" INCTAB EXPTAB HHDDATA
*execute 'gdxxrw.exe i=%check%.gdx o=%check%.xlsx index=index!a5'
*$call "xlstalk -o %check%.xlsx"



PARAMETER XLTEST;
execute_unload "%check%.gdx" INCTAB EXPTAB HHDDATA
execute 'xlstalk.exe -m %check%.xlsx';
 XLTEST = ERRORLEVEL;
IF(XLTEST = 1,
execute 'xlstalk.exe -c %check%.xlsx';
);
IF(XLTEST = 2,
execute 'xlstalk.exe -s %check%.xlsx';
);
execute 'gdxxrw.exe i=%check%.gdx o=%check%.xlsx index=index!a5' ;
execute 'xlstalk.exe -o %check%.xlsx';
DISPLAY XLTEST;


*Diagnostics ---

PARAMETER
 CHKNEG(AC,ACP)

;

 CHKNEG(A,C)$(SAM(A,C) LT 0) = 1/0;
 CHKNEG(C,A)$(SAM(C,A) LT 0) = 1/0;
 CHKNEG(F,A)$(SAM(F,A) LT 0) = 1/0;
 CHKNEG(A,H)$(SAM(A,H) LT 0) = 1/0;
* CHKNEG(C,H)$(SAM(C,H) LT 0) = 1/0;
 CHKNEG(C,'S-I')$(SAM(C,'S-I') LT 0) = 1/0;
 CHKNEG(C,'GOV')$(SAM(C,'GOV') LT 0) = 1/0;
 CHKNEG(C,'ROW')$(SAM(C,'ROW') LT 0) = 1/0;
* CHKNEG('ROW',C)$(SAM('ROW',C) LT 0) = 1/0;
 CHKNEG('TRC',C)$(SAM('TRC',C) LT 0) = 1/0;

DISPLAY CHKNEG;



