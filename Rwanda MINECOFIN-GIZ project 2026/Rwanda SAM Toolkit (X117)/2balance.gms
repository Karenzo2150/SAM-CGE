*r=national
$TITLE Cross Entropy SAM Estimation August 2003
$OFFSYMLIST OFFSYMXREF OFFUPPER
$ONEMPTY

SETS
 ACBAL(AC)        accounts with row-column balance
;

ALIAS (AC,ACP,ACPP,ACPPP), (ACNT,ACNTP,ACNTPP,ACNTPPP), (ACBAL,ACBALP);

SETS
 SMLCELL(AC,ACP)  SAM cells with abs value < cutoff are removed
 INEG(AC,ACP)     cells with negative values in data
 IZERO(AC,ACP)    cells with zero entry
 NONZERO(AC,ACP)  cells with nonzero entry
 ICOEFF(AC,ACP)   cell coefficients to be estimated
 IVALUE(AC,ACP)   cell values to be estimated
 ESTIMATE(AC,ACP) cells to be estimated and not fixed
 IFIXC(AC,ACP)    cell coefficient fixed with no error
 IFIXV(AC,ACP)    cell value fixed with no error
 ACELL(AC,ACP)    additive error for cells
 LCELL(AC,ACP)    logarithmic error for cells
 ICOL(AC)         columns with non zero elements
 ICOL2(AC)        column sums to be constrained with or without error
 ICOLNZ(AC)       columns with nonzero sum
 IROW(AC)         rows with non zero elements
 ACOL(AC)         additive errors for column sum constraints
 LCOL(AC)         multiplicative errors for column sum constraints
 MACRO            potential macro control totals
    /
    LABACT, LNDACT, KAPACT
    ATXACT, ETXCOM, MTXCOM, STXCOM, DTXLAB, DTXLND, DTXCAP, DTXHHD, DTXENT
    COMHHD, COMGOV, COMINV, COMROW, ROWCOM
    GOVLAB, GOVLND, GOVCAP
    ROWLAB, ROWLND, ROWCAP
    HHDENT, GOVENT, SAVENT, ROWENT
    ENTHHD, GOVHHD, SAVHHD, ROWHHD
    SAVROW
    AGR, MIN, MAN, UTL, CON, TRD, TRN, HOT, COM, FBS, GOV, OSV
    /
 MACRO2(MACRO)    macro constraints actually imposed
    /
    LABACT, LNDACT, KAPACT
    ATXACT, ETXCOM, MTXCOM, STXCOM, DTXLAB, DTXLND, DTXCAP, DTXHHD, DTXENT
    COMHHD, COMGOV, COMINV, COMROW, ROWCOM
    GOVLAB, GOVLND, GOVCAP
    ROWLAB, ROWLND, ROWCAP
    HHDENT, GOVENT, SAVENT, ROWENT
    ENTHHD, GOVHHD, SAVHHD, ROWHHD
    SAVROW
    AGR, MIN, MAN, UTL, CON, TRD, TRN, HOT, COM, FBS, GOV, OSV
    /
 AGR(A) / asorg,amaiz,awhea,arice,aocer,aipot,aspot,acass,aroot,abean,apeas,avege,abanb,abanc,abans,afrui,agnut,asoya,aoils,acoff,ateal,atoba,asugr,apyre,aocrp,acatt,asmlr,apoul,aoliv,amilk,aeggs,ahony,ahunt,afuel,achar,afore,afish /
 MIN(A) / angas,amore,aomin,ameat /
 MAN(A) / afsea,afveg,afoil,adair,agmll,abake,afeed,afood,aalco,abeve,aptob,atext,awood,aprnt,apetr,achem,aphar,aprub,anmet,aceme,aclay,ametl,amach,avehi,afurn,aoman,arepr /
 UTL(A) / aelec,awatr,awast /
 CON(A) / acons,acont /
 TRD(A) / avehr,aveht,atrdw,atrdr /
 TRN(A) / atrnl,atrna,atrns,apost /
 HOT(A) / ahotl /
 COM(A) / apubl,acomm,ainfo /
 FBS(A) / abank,ainsu,aofsv,arent,areal,alegl,aenga,aprod,atrvl,aobsv /
 GOV(A) / apadm,aeduc,aheal,asocw /
 OSV(A) / acult,aarts,aosrv,adsrv,atrdc /
 MACAGG(ac,acp,macro) Macro aggregator matrix
 AMAC(MACRO)      additive error for macro constraints
 LMAC(MACRO)      multiplicative error for macro constraints
 JWT              Weights for error support set  /1*3/
;

SCALAR
 cutoff            lower bound on absolute cell values
 epsilon           epsilon value for cross-entropy minimand     /.000001 /
 ;
 cutoff = 0 ;

PARAMETER
 tsam0(AC,ACP)     initial SAM
 sambalchk(ac)     col sums minus row sums
 coeff0(AC,ACP)    column coefficients
 colsum0(AC)       initial column sum
 coltarget(AC)     target column sum
 mactotal0(MACRO)  initial macro totals
 vbar1(ac,jwt)     Error support set 1 for column constraints
 vbar2(macro,jwt)  Error support set 2 for macro constraints
 vbar3(ac,acp,jwt) Error support set 3 for cell constraints
 wbar1(ac,jwt)     Weights on error support set 1
 wbar2(macro,jwt)  Weights on error support set 2
 wbar3(ac,acp,jwt) Weights on error support set 3
 sigmay1(ac)       Prior standard error of column sums
 sigmay2(macro)    Prior standard error of macro aggregates
 sigmay3(ac,acp)   Prior standard error for cell constraints
 ;

VARIABLES
 TSAM(AC,ACP)      SAM values
 COEFF(AC,ACP)     SAM coefficients
 COLSUM(AC)        column sums
 ERR1(AC)          Error value on column sums
 ERR2(MACRO)       Error value for macro aggregates
 ERR3(AC,ACP)      Error value for cell constraint
 W1(AC,jwt)        Error weights
 W2(macro,jwt)     Error weights
 W3(AC,ACP,jwt)    Error weights
 DENTROPY          Entropy difference (objective)
 ;

EQUATIONS
 SAMFLOW1(ac,acp)  SAM flows with additive errors
 SAMFLOW2(ac,acp)  SAM flows with logarithmic errors
 SAMCOEFF1(ac,acp) SAM coefficients with additive errors
 SAMCOEFF2(ac,acp) SAM coefficients with logarithmic errors
 COLSUMEQ1(ac)     column sums with additive errors

 COLSUMDEF(ac)     define column sums
 COEFFDEF(ac,acp)  define coefficients

 SAMEQ(ac)          row and column sum constraint

*macro constraints
 MACROEQ(macro)    macro aggregation constraints

 ERROR1EQ(ac)      definition of error term 1
 ERROR2EQ(macro)   definition of error term 2
 ERROR3EQ(ac,acp)  definition of error term 3
 SUMW1(ac)         Sum of weights 1
 SUMW2(macro)      Sum of weights 2
 SUMW3(ac,acp)     Sum of weights 3
 ENTROPY           Entropy difference definition
 ;

*SAM value and coefficient constraints
 SAMFLOW1(acnt,acntp)$(IVALUE(acnt,acntp) and ACELL(acnt,acntp))..
  TSAM(acnt,acntp)  =E= tsam0(acnt,acntp) + ERR3(acnt,acntp) ;

 SAMFLOW2(acnt,acntp)$(IVALUE(acnt,acntp) and LCELL(acnt,acntp))..
  TSAM(acnt,acntp)  =E= tsam0(acnt,acntp)*EXP(ERR3(acnt,acntp)) ;

 SAMCOEFF1(acnt,acntp)$(ICOEFF(acnt,acntp) and ACELL(acnt,acntp))..
  COEFF(acnt,acntp) =E= coeff0(acnt,acntp) + ERR3(acnt,acntp) ;

 SAMCOEFF2(acnt,acntp)$(ICOEFF(acnt,acntp) and LCELL(acnt,acntp))..
  COEFF(acnt,acntp) =E= coeff0(acnt,acntp)*EXP(ERR3(acnt,acntp)) ;

*Column sum constraints
 COLSUMEQ1(acnt)$(ICOL2(acnt) and ACOL(acnt))..
  COLSUM(acnt)      =E= coltarget(acnt) + ERR1(acnt) ;

*Define column sums and coefficients
 COLSUMDEF(acnt)$ICOL(acnt)..
  COLSUM(acnt)      =E= SUM(acntp$IROW(acntp), TSAM(acntp,acnt)) ;

*Only compute coefficients for nonzero cells
 COEFFDEF(acnt,acntp)$((NOT IFIXV(acnt,acntp)) and ICOL(acntp) and IROW(acnt) and ICOLNZ(acntp))..
  COEFF(acnt,acntp)*COLSUM(acntp) =E= TSAM(acnt,acntp);

*Row and column sum equality constraint
 SAMEQ(acnt)$ACBAL(acnt)..
  COLSUM(acnt)      =E= SUM(acntp$ICOL(acntp), TSAM(acnt,acntp)) ;

*Macro constrints
 MACROEQ(MACRO2)..
  SUM((irow,icol)$MACAGG(irow,icol,macro2),
  TSAM(irow,icol)) =E= MACTOTAL0(macro2) + ERR2(macro2) ;

*Definition of error terms

 ERROR1EQ(acnt)$(ICOL2(acnt) and ACOL(acnt) and sigmay1(acnt))..
  ERR1(acnt)   =E= SUM(jwt, W1(acnt,jwt)*vbar1(acnt,jwt)) ;

 SUMW1(acnt)$(ICOL2(acnt) and ACOL(acnt) and sigmay1(acnt))..
  SUM(jwt, W1(acnt,jwt)) =E= 1 ;

 ERROR2EQ(macro2)$sigmay2(macro2)..
  ERR2(macro2) =E= SUM(jwt, W2(macro2,jwt)*vbar2(macro2,jwt)) ;

 SUMW2(macro2)$sigmay2(macro2)..
  SUM(jwt, W2(macro2,jwt)) =E= 1 ;

 ERROR3EQ(acnt,acntp)$((IVALUE(acnt,acntp) or ICOEFF(acnt,acntp))
                      and sigmay3(acnt,acntp))..
  ERR3(acnt, acntp)  =E= SUM(jwt, W3(acnt,acntp,jwt)*vbar3(acnt,acntp,jwt)) ;

 SUMW3(acnt,acntp)$((IVALUE(acnt,acntp) or ICOEFF(acnt,acntp))
                      and sigmay3(acnt,acntp))..
  SUM(jwt, W3(acnt,acntp,jwt)) =E= 1 ;

*Objective function
 ENTROPY..
  DENTROPY =E= SUM((acnt,jwt)$(ICOL2(acnt) and ACOL(acnt) and sigmay1(acnt)),
                    W1(acnt,jwt)
                  * (LOG(W1(acnt,jwt) + epsilon)
                  - LOG(wbar1(acnt,jwt) + epsilon)))
                            +
               SUM((macro2,jwt)$sigmay2(macro2),
                    W2(macro2,jwt)
                  * (LOG(W2(macro2,jwt) + epsilon)
                  - LOG(wbar2(macro2,jwt) + epsilon)))
                            +
               SUM((acnt,acntp,jwt)$((IVALUE(acnt,acntp) or ICOEFF(acnt,acntp))
                                 and sigmay3(acnt,acntp)),
                    W3(acnt,acntp,jwt)
                  * (LOG(W3(acnt,acntp,jwt) + epsilon)
                  - LOG(wbar3(acnt,acntp,jwt) + epsilon)))
;


*Country-specific data and set definitions
*SETS and DATA======================

 TSAM0(acnt,acntp) = SAM(acnt,acntp)*SCALE;

*DIAGNOSTICS
*$include diagnostic.inc

*Define various sets based on initial SAM, tsam0

*For a SAM, which is square, ACBAL is the entire set.
 ACBAL(acnt) = YES ;

 TSAM0("TOTAL",acntp)  = sum(acnt,  TSAM0(acnt,acntp));
 TSAM0(acnt,"TOTAL")   = sum(acntp, TSAM0(acnt,acntp));
 SAMBALCHK(ACNT)$ACBAL(ACNT) = TSAM0('TOTAL',ACNT) - TSAM0(ACNT,'TOTAL');

 display " tsam0 before balancing", tsam0, sambalchk ;

*Define column sums that can be constrained.
*Might want to exclude columns with only one entry. Or, alternatively,
*leave them in and define entry constraint in terms of coefficients.
*Can exclude any other columns for which column constraints do not
*make a lot of sense.
*Balance accounts which sum to zero by definition should probably be
*constrained exactly, with no error. Can be done by simply setting their
*prior standard error, sigmay1, to zero, which will happen automatically if
*the target column sum is zero. See section on defining sigmay1.

 Parameter countcol(ac)  number of nonzero cells in columns
           countrow(ac)  number of nonzero cells in rows ;
 loop(acntp,
 countcol(acntp) = 0 ;
 countrow(acntp) = 0 ;
   loop(acnt,
   countcol(acntp)$TSAM0(acnt,acntp) = countcol(acntp) + 1 ;
   countrow(acntp)$TSAM0(acntp,acnt) = countrow(acntp) + 1 ;
   );
 );

*Define column and row sets for all accounts with any nonzero elements in the
*corresponding row and column. A pure balancing SAM account might have a row or
*column with all zeros. It is harmless to exclude such accounts from the
*balancing procedure, but they must be part of ACBAL.
 ICOL(acnt)$(countcol(acnt) or ACBAL(acnt))   = yes ;
 IROW(acnt)$(countrow(acnt) or ACBAL(acnt))   = yes ;

 display icol, countcol, irow, countrow ;

*Define columns and rows with nonzero sums and compute column coefficients.
*Nonzero here is defined as significant absolute value so that column
*coefficients can be computed safely.
 ICOLNZ(acnt)$(ABS(TSAM0("TOTAL",acnt) gt 0.00)) = yes ;
 coeff0(acnt,icolnz)      = TSAM0(acnt,icolnz)/TSAM0("TOTAL",icolnz) ;
 colsum0(acnt)$icol(acnt) = TSAM0("TOTAL",acnt) ;

*Define column accounts that will have constraints. Start by assuming all
*column accounts will be constrained. Those with zero or negative sums cannot
*have column coefficients that are constrained.
 ICOL2(acnt)    = ICOL(acnt) ;

*Constrain column sums where there will be lots of coefficients. Otherwise, we
*will only be constraining relative cell values, not values.
 ICOL2(A)       = NO ;
 ICOL2(C)       = NO ;

*Assume all col sum errors are additive. Multiplicative column sum errors
*are not yet programmed.
 LCOL(ICOL2)    = no ;
 ACOL(ICOL2)    = yes ;

 display countrow, irow, countcol, icol, icol2, lcol ;

*Find negative cell entries
 IZERO(acnt,acntp)$(TSAM0(acnt,acntp) eq 0)   = yes ;
 NONZERO(acnt,acntp)$(not IZERO(acnt,acntp))  = yes ;
 INEG(acnt,acntp)$((TSAM0(acnt,acntp) lt 0) and nonzero(acnt,acntp)) = yes ;

 display izero, nonzero ;
 display ineg ;

*Specify nature of cell error, whether on coefficients or on values,
*and whether additive or multiplicative.
*Negative cells are specified as values with additive errors.
*All positive cells are initially specified with multiplicative errors
*on values. This ensures that positive cells will not change sign.
*Then various cells are chosen to be specified as coefficients.
*All coefficient cells are specified with multiplicative errors.

 IVALUE(acnt,acntp)$(nonzero(acnt,acntp))          = yes ;

*Now set cells which are naturally seen as coefficients. Do not specify as
*coefficient if cell does not have a positive coefficient value, coeff0.
*JT: Set all household cells to coefficients
 IVALUE(acnt,'HHD')$(coeff0(acnt,'HHD') gt 0)              = yes ;

*Set any negative cells to values
 IVALUE(acnt,acntp)$ineg(acnt,acntp)               = yes ;

*Set cells in columns with only one cell to value
 IVALUE(irow,icol)$((countcol(icol) eq 1) and nonzero(irow,icol)) = yes ;

*Set any cells in columns with negative or zero sum to values. Such cells
*should not have a positive coeff0, but this is an extra check.
 IVALUE(acnt,acntp)$(icol(acntp) and (colsum0(acntp) lt 0)
                 and ICOLNZ(acntp))                = yes ;

*If cell error is not on values, then it will be on coefficients.

 ICOEFF(acnt,acntp)$((not izero(acnt,acntp)) and
                     (not ivalue(acnt,acntp)))    = yes ;

 ESTIMATE(acnt,acntp)$(ivalue(acnt,acntp) or icoeff(acnt,acntp)) = yes ;

*Start by assuming that all cells have additive errors.
 ACELL(acnt,acntp)$ESTIMATE(acnt,acntp)    = yes ;

*Turn off ACELL for cells that have multiplicative errors
 ACELL(acnt,acntp)$ICOEFF(acnt,acntp)      = no ;
*Make sure that ACELL is on for negative cells
 ACELL(acnt,acntp)$ineg(acnt,acntp)         = yes ;

 LCELL(acnt,acntp)$(NOT ACELL(acnt,acntp)) = yes ;

 IFIXV(acnt,acntp)$((not ivalue(acnt,acntp)) and
                    (not icoeff(acnt,acntp))) = yes ;

*Check for errors. Cells cannot be constrained in both values and coefficients.
*All cells to be estimated must have lcell or acell.
 SET ICHECK(ac,acp)  Error check for cell constraints;
 ICHECK(acnt,acntp)$(ivalue(acnt,acntp) and icoeff(acnt,acntp)) = yes ;
 display "Error check. Cells with both ivalue and icoeff", ICHECK ;
 ICHECK(acnt,acntp)$(estimate(acnt,acntp) and ((not acell(acnt,acntp)) and
                                                not lcell(acnt,acntp))) = yes ;
 display "Error check. Cells to be estimated but neither acell nor lcell",
      ICHECK ;
 ICHECK(irow,icol)$(estimate(irow,icol) and izero(irow,icol)) = yes ;
 display "Error check. Cells to be estimated but initially zero", ICHECK ;

 display ivalue, icoeff, acell, lcell ;

*Define macro aggregates for household control totals
    MACAGG('FLAB',A,'LABACT')       = YES;
    MACAGG('FLND',A,'LNDACT')       = YES;
    MACAGG('FCAP',A,'KAPACT')       = YES;
    MACAGG('ATAX',A,'ATXACT')     = YES;
    MACAGG('ETAX',C,'ETXCOM')     = YES;
    MACAGG('MTAX',C,'MTXCOM')     = YES;
    MACAGG('STAX',C,'STXCOM')     = YES;
    MACAGG('DTAX','FLAB','DTXLAB')  = YES;
    MACAGG('DTAX','FLND','DTXLND')  = YES;
    MACAGG('DTAX','FCAP','DTXCAP')  = YES;
    MACAGG('DTAX','HHD','DTXHHD') = YES;
    MACAGG('DTAX','ENT','DTXENT') = YES;
    MACAGG(C,'HHD','COMHHD')      = YES;
    MACAGG(C,'GOV','COMGOV')      = YES;
    MACAGG(C,'S-I','COMINV')      = YES;
    MACAGG(C,'ROW','COMROW')      = YES;
    MACAGG('ROW',C,'ROWCOM')      = YES;
    MACAGG('GOV','FLAB','GOVLAB')   = YES;
    MACAGG('GOV','FLND','GOVLND')   = YES;
    MACAGG('GOV','FCAP','GOVCAP')   = YES;
    MACAGG('ROW','FLAB','ROWLAB')   = YES;
    MACAGG('ROW','FLND','ROWLND')   = YES;
    MACAGG('ROW','FCAP','ROWCAP')   = YES;
    MACAGG('HHD','ENT','HHDENT')  = YES;
    MACAGG('GOV','ENT','GOVENT')  = YES;
    MACAGG('S-I','ENT','SAVENT')  = YES;
    MACAGG('ROW','ENT','ROWENT')  = YES;
    MACAGG('ENT','HHD','ENTHHD')  = YES;
    MACAGG('GOV','HHD','GOVHHD')  = YES;
    MACAGG('S-I','HHD','SAVHHD')  = YES;
    MACAGG('ROW','HHD','ROWHHD')  = YES;
    MACAGG('S-I','ROW','SAVROW')  = YES;

    MACAGG(F,AGR,'AGR') = YES;
    MACAGG(F,MIN,'MIN') = YES;
    MACAGG(F,MAN,'MAN') = YES;
    MACAGG(F,UTL,'UTL') = YES;
    MACAGG(F,CON,'CON') = YES;
    MACAGG(F,TRD,'TRD') = YES;
    MACAGG(F,TRN,'TRN') = YES;
    MACAGG(F,HOT,'HOT') = YES;
    MACAGG(F,COM,'COM') = YES;
    MACAGG(F,FBS,'FBS') = YES;
    MACAGG(F,GOV,'GOV') = YES;
    MACAGG(F,OSV,'OSV') = YES;

*Initialize values from TSAM0
 MACTOTAL0(macro)           = SUM((irow,icol)$MACAGG(irow,icol,macro),
                              TSAM0(irow,icol)) ;
 Display  mactotal0 ;

*Set error  bounds and support sets. Assume a prior on standard deviation
*of the errors, sigma.

*############### Define variable bounds on errors #####################
* Start from assumed prior knowledge of the standard error (perhaps due
* to measurement error) of the column sums. Below, we assume that all
* column sums have a standard error of 5%. This is a Bayesian prior,
* not a maintaned hypothesis.
* The estimated error is weighted sum of elements in an error support
* set:
*   ERR(acnt) = SUM(jwt, W(acnt,jwt)*VBAR(acnt,jwt))
* where the W's are estimated in the CE procedure.
* The prior variance of these errors is given by:
*   (sigmay(acnt))**2 = SUM(jwt, WBAR(acnt,jwt)*(VBAR(acnt,jwt))**2 )
* where the WBAR's are the prior on the weights.
* The VBARs are chosen to define a domain for the support set of +/- 3
* standard errors. The prior on the weights, WBAR, are then calculated
* to yield the specified prior on the standard error, sigmay.
* In Robinson, Cattaneo, and El-Said (2001), we specify prior weights
* (WBAR) that are uniform and set the prior standard error by the
* choice of support set, VBAR. In that paper, we use a three-weight
* specification (jwt /1*3/);
*
* We define three sets of errors with separate weights, W1, W2, and W3. The
* first is for specifying errors on column sums, the second for errors
* on macro aggregates (defined in the set macro), and the third for errors
* in cell values.

* If sigmay is set to zero, the corresponding constraint is assumed to be
* exact, with no error.

* Define standard errors for errors on column sums, sigmay1. Also set coltarget
* to average of initial column and row sums. Column sum can be zero or
* negative. Using an average of protosam column and row sums is arbitrary. If
* better prior information about column sums is known, use it. In this version,
* if the initial column sum is zero, then sigmay2 will also be zero and the
* account will be constrained to sum to zero. This is appropriate for a
* "balancing" account. However, a nonzero sum with or without error can also
* be specified.

*Set sigmay1 and target column sums

  coltarget(acbal) = 0.5*(colsum0(acbal) + SUM(icol, TSAM0(acbal,icol))) ;
*  coltarget(acbal) = colsum0(acbal);

*Set sigmay1, standard errors for errors on column totals

  sigmay1(acnt)$(ICOL2(acnt) and ACOL(acnt)) = 0.05*ABS(coltarget(acnt)) ;

*Set sigmay2, standard errors for errors on macro aggregates
  sigmay2(macro2)      = 0.1*ABS(mactotal0(macro2)) ;
SET
 MACRO3(MACRO2) / AGR, MIN, MAN, UTL, CON, TRD, TRN, HOT, COM, FBS, GOV, OSV /
;
  sigmay2(macro3)       = 0.005*ABS(mactotal0(macro3)) ;

* Set errors on cell elements, sigmay3. They can be on values or coefficients,
* and can be specified as additive or multiplicative. If multiplicative, the
* prior is implicitly specified as lognormal. That is, log(error) is
* distributed as a normal with mean zero and standard deviation sigmay3.
* Then EXP(error), which is the multiplicative error, has mean one.

*Set sigmay3, standard errors for errors on cell values

  sigmay3(acnt,acntp)$(IVALUE(acnt,acntp) and ACELL(acnt,acntp)) = 0.2*ABS(tsam0(acnt, acntp))   ;
  sigmay3(acnt,acntp)$(IVALUE(acnt,acntp) and LCELL(acnt,acntp)) = 0.2   ;

  sigmay3(acnt,acntp)$(ICOEFF(acnt,acntp) and ACELL(acnt,acntp)) = 0.2*ABS(coeff0(acnt, acntp))   ;
  sigmay3(acnt,acntp)$(ICOEFF(acnt,acntp) and LCELL(acnt,acntp)) = 0.2   ;

  sigmay3(ACNT,ACNTP)$((NOT ACBAL(ACNT)) AND (NOT ACBAL(ACNTP))) = 0;

  sigmay3(C,A)$(ICOEFF(C,A) and ACELL(C,A)) = 0.2*ABS(coeff0(C,A))   ;



$ontext
*Set sigmay3 to a large number if there are very few cells in a column and
*you do not have a strong prior on the column total.
*In this case, we assume that the row element constraints will be binding
  sigmay3(acnt,acntp)$(ICOEFF(acnt,acntp) and ACELL(acnt,acntp)
                                          and (count(acntp) eq 1))
    = 0.75*coeff0(acnt, acntp)   ;
  sigmay3(acnt,acntp)$(ICOEFF(acnt,acntp) and LCELL(acnt,acntp)
                                          and (count(acntp) eq 1))
    = 0.75   ;
*SR ### This can also be handled by specifying such cells as coeff and
* do not constrain the column sum.

$offtext

* This code assumes a prior mean of zero and a two-parameter
* distribution with specified prior standard error. There are three
* weights, W(acnt,jwt), to be estimated. The actual moments are estimated
* as part of the estimation procedure.
*$ontext
* Set constants for 3-weight error distribution
  vbar1(acnt,"1")  = -3 * sigmay1(acnt);
  vbar1(acnt,"2")  =  0             ;
  vbar1(acnt,"3")  = +3 * sigmay1(acnt);

  wbar1(acnt,"1")  =  1/18  ;
  wbar1(acnt,"2")  = 16/18  ;
  wbar1(acnt,"3")  =  1/18  ;

*$offtext

* This code assumes a prior mean of zero and a prior value of kurtosis
* consistent with a prior normal distribution with mean zero, variance
* sigmay**2, and kurtosis equal to 3*sigmay**4. The addition of a prior
* on kurtosis requires estimation of 5 weights (jwt = 5);
* The prior weights wbar are specified so that:
* SUM(jwt, wbar(acnt,jwt)*vbar(acnt,jwt)**4) = 3*sigmay(acnt,jwt)**4
* as well as defining the variance as above.
* The prior weights and support set are also symmetric, so the prior
* on all odd moments is zero. The choice of +/- 1 standard error
* for vbar(acnt,"2") and vbar(acnt,"4") is arbitrary.
* The actual moments are estimated as part of the estimation procedure.

$ontext
* Set constants for 5-weight error distribution
  vbar1(acnt,"1")  = -3 * sigmay1(acnt) ;
  vbar1(acnt,"2")  = -1 * sigmay1(acnt) ;
  vbar1(acnt,"3")  =  0              ;
  vbar1(acnt,"4")  = +1 * sigmay1(acnt) ;
  vbar1(acnt,"5")  = +3 * sigmay1(acnt) ;

  wbar1(acnt,"1")  =   1/72;
  wbar1(acnt,"2")  =  27/72;
  wbar1(acnt,"3")  =  16/72;
  wbar1(acnt,"4")  =  27/72;
  wbar1(acnt,"5")  =   1/72;
$offtext

*$ontext
* Set constants for 3-weight error distribution
  vbar2(macro,"1")  = -3 * sigmay2(macro);
  vbar2(macro,"2")  =  0             ;
  vbar2(macro,"3")  = +3 * sigmay2(macro);

  wbar2(macro,"1")  =  1/18  ;
  wbar2(macro,"2")  = 16/18  ;
  wbar2(macro,"3")  =  1/18  ;
*$offtext

$ontext
* Set constants for 5-weight error distribution
  vbar2(macro,"1")  = -3 * sigmay2(macro) ;
  vbar2(macro,"2")  = -1 * sigmay2(macro) ;
  vbar2(macro,"3")  =  0                  ;
  vbar2(macro,"4")  = +1 * sigmay2(macro) ;
  vbar2(macro,"5")  = +3 * sigmay2(macro) ;

  wbar2(macro,"1")  =   1/72;
  wbar2(macro,"2")  =  27/72;
  wbar2(macro,"3")  =  16/72;
  wbar2(macro,"4")  =  27/72;
  wbar2(macro,"5")  =   1/72;
$offtext

*$ontext
* Set constants for 3-weight error distribution
  vbar3(acnt,acntp,"1")  = -3 * sigmay3(acnt,acntp);
  vbar3(acnt,acntp,"2")  =  0             ;
  vbar3(acnt,acntp,"3")  = +3 * sigmay3(acnt,acntp);

  wbar3(acnt,acntp,"1")  =  1/18  ;
  wbar3(acnt,acntp,"2")  = 16/18  ;
  wbar3(acnt,acntp,"3")  =  1/18  ;
*$offtext

$ontext
* Set constants for 5-weight error distribution
  vbar3(acnt,acntp,"1")  = -3 * sigmay3(acnt,acntp);
  vbar3(acnt,acntp,"2")  = -1 * sigmay3(acnt,acntp);
  vbar3(acnt,acntp,"3")  =  0                  ;
  vbar3(acnt,acntp,"4")  = +1 * sigmay3(acnt,acntp);
  vbar3(acnt,acntp,"5")  = +3 * sigmay3(acnt,acntp);

  wbar3(acnt,acntp,"1")  =   1/72;
  wbar3(acnt,acntp,"2")  =  27/72;
  wbar3(acnt,acntp,"3")  =  16/72;
  wbar3(acnt,acntp,"4")  =  27/72;
  wbar3(acnt,acntp,"5")  =   1/72;
$offtext

 Display sigmay1, sigmay2, sigmay3;
 Display vbar1, vbar2, vbar3;

*######################## DEFINE MODEL ############################

 MODEL SAMENTROP
 /
 SAMFLOW1
 SAMFLOW2
 SAMCOEFF1
 SAMCOEFF2
 COLSUMEQ1
 COLSUMDEF
 COEFFDEF
 SAMEQ
 MACROEQ
 ERROR1EQ
 ERROR2EQ
 ERROR3EQ
 SUMW1
 SUMW2
 SUMW3
 ENTROPY
 / ;

DISPLAY "141",COLSUM0;


*Initialize variables
 TSAM.L(acnt,acntp)       = tsam0(acnt,acntp) ;
 COEFF.L(acnt,acntp)      = coeff0(acnt,acntp) ;
 COLSUM.L(icol)           = colsum0(icol) ;
 ERR1.L(AC)               = 0 ;
 ERR2.L(MACRO)            = 0 ;
 ERR3.L(AC,ACP)           = 0 ;
 W1.L(acnt,jwt)           = wbar1(acnt,jwt) ;
 W2.L(macro,jwt)          = wbar2(macro,jwt) ;
 W3.L(acnt,acntp,jwt)     = wbar3(acnt,acntp,jwt) ;
 DENTROPY.L               = 0 ;

*Set bounds and fix variables that need to be fixed
*###############  Define bounds for cell values  ####################

* Defining equation SAMMAKE over non-zero elements of A ($Abar1(acnt,acntp))
* guarantees that the zero structure of the original SAM is maintained
* in the estimated SAM. Fixing all the zero entries to zero greatly
* reduces the size of the estimation problem. If it is desired to
* allow a zero entry to become nonzero in the estimated SAM, then
* the condition $ABAR1(acnt,acntp) must be replaced with a new set that
* does not include cells which are currently zero but may be nonzero.

* COEFF.LO(acnt,acntp)$icoeff(acnt,acntp)      = 0 ;
* COEFF.UP(acnt,acntp)$icoeff(acnt,acntp)      = 1 ;
*COEFF.FX(acnt,acntp)$(NOT nonzero(acnt,acntp))= 0;

*Fix coeff to zero if it is not a ivalue
  COEFF.FX(acnt,acntp)$IFIXV(acnt,acntp)       = coeff0(acnt,acntp) ;

*TSAM.LO(acnt,acntp)                           = 0.0 ;
*TSAM.UP(acnt,acntp)                           = +inf ;

 TSAM.FX(acnt,acntp)$IFIXV(acnt,acntp)         = tsam0(acnt,acntp) ;

* Upper and lower bounds on the error weights
 W1.LO(acnt,jwt)                            = 0   ;
 W1.UP(acnt,jwt)                            = 1   ;
 W2.LO(macro2,jwt)                          = 0   ;
 W2.UP(macro2,jwt)                          = 1   ;
 W3.LO(acnt,acntp,jwt)                      = 0   ;
 W3.UP(acnt,acntp,jwt)                      = 1   ;

*If standard deviation of errors is set to zero, fix the weights to the prior
*so that the error will always be zero.
*   Note that it should not be necessary to fix W if ERR is fixed. I now
*   exclude equations for errors and error weights when sigmay is zero.
 W1.FX(acnt, jwt)$(sigmay1(acnt) eq 0)            = wbar1(acnt,jwt) ;
 W2.FX(macro2,jwt)$(sigmay2(macro2) eq 0)         = wbar2(macro2,jwt) ;
 W3.FX(acnt,acntp,jwt)$(sigmay3(acnt,acntp) eq 0) = wbar3(acnt,acntp,jwt) ;

 ERR1.FX(acnt)$(sigmay1(acnt) eq 0)               = 0 ;
 ERR2.FX(macro2)$(sigmay2(macro2) eq 0)           = 0 ;
 ERR3.FX(acnt,acntp)$(sigmay3(acnt,acntp) eq 0)   = 0 ;

*######################## SOLVE MODEL #############################

 OPTION ITERLIM       = 100000;
 OPTION LIMROW        = 150 ,    LIMCOL       = 150;
 OPTION SOLPRINT      = OFF ;
 OPTION RESLIM        = 100000;

  SAMENTROP.HOLDFIXED = 1 ;
* OPTION NLP          = PATHNLP ;
  OPTION NLP          = CONOPT3;


*########################### Solve statenment ######################

  SOLVE SAMENTROP using nlp minimizing dentropy ;

*###################################################################

*---------------- Parameters for reporting results
Parameters
 SAMCE(ac,acp)      New balanced SAM flows from CE
 SEM                Squared Error Measure
 VALDIFF(ac,acp)    Differnce btw original SAM and Final SAM in values
 PERDIFF(ac,acp)    Differnce btw original SAM and Final SAM in Percent
 bigdiffp(ac,acp)   Cells with large percent change
 NormEntrop         Normalized Entropy a measure of total uncertainty
 ;

 valdiff(acnt,acntp)               = TSAM.l(acnt,acntp) - tsam0(acnt,acntp) ;
 perdiff(acnt,acntp)$tsam0(acnt,acntp) = 100*(TSAM.l(acnt,acntp)/tsam0(acnt,acntp) - 1 ) ;
 bigdiffp(ac,acp)$(abs(perdiff(ac,acp)) gt 25) = perdiff(ac,acp) ;

 SAMCE(acnt,acntp)        = TSAM.l(acnt,acntp);
 SAMCE("total",acntp)     = SUM(acnt, SAMCE(acnt,acntp)) ;
 SAMCE(acnt,"total")      = SUM(acntp, SAMCE(acnt,acntp)) ;
 SAMBALCHK(ACNT)          = SAMCE('TOTAL',ACNT) - SAMCE(ACNT,'TOTAL');
 SAMBALCHK(ACNT)$(ABS(SAMBALCHK(ACNT)) LT 1E-6) = 0;

 display " SAMCE after balancing", samce ;
 display " SAMBALCHK after balancing", sambalchk ;

 SEM = Sum((acnt,acntp), SQR(COEFF.L(acnt,acntp) - coeff0(acnt,acntp)))/SQR(9);

$ontext
 NormEntrop             = SUM((acnt,acntp)$((coeff0(acnt,acntp) gt 0)
                                   and (ACOEF.L(acnt,acntp) gt 0)),
                          ACOEF.L(acnt,acntp)* LOG(ACOEF.L(acnt,acntp))) /
                          SUM((acnt,acntp)$(Abar1(acnt,acntp)),
                                   Abar1(acnt,acntp)* LOG (Abar1(acnt,acntp)))
 ;
$offtext



 display SEM, SAMCE, VALDIFF, PERDIFF, bigdiffp, DENTROPY.L, SAMBALCHK;


 SAM(AC,ACP) = SAMCE(AC,ACP)/SCALE;

PARAMETER XLTEST;
execute_unload "%output%.gdx" SAM
execute 'xlstalk.exe -m %output%.xlsx';
 XLTEST = ERRORLEVEL;
IF(XLTEST = 1,
execute 'xlstalk.exe -c %output%.xlsx';
);
IF(XLTEST = 2,
execute 'xlstalk.exe -s %output%.xlsx';
);
execute 'gdxxrw.exe i=%output%.gdx o=%output%.xlsx index=index!a5' ;
execute 'xlstalk.exe -o %output%.xlsx';
DISPLAY XLTEST;
