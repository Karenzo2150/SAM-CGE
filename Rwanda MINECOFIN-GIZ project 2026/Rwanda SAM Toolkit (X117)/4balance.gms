*r=households s=final
$TITLE Cross Entropy SAM Estimation August 2003
$OFFSYMLIST OFFSYMXREF OFFUPPER
$ONEMPTY

SETS
 ACBAL(AC)        accounts with row-column balance
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
 MACRO            potential macro control totals /
         OWN,    MKT,    LAB,    CAP,    LND,    ENT,    GOV,    SAV,    ROW,    DTAX,   S-I
 /
 MACRO2(MACRO)    macro constraints actually imposed  /
         OWN,    MKT,    LAB,    CAP,    LND,    ENT,    GOV,    SAV,    ROW,    DTAX,   S-I
 /
 MACAGG(AC,ACP,MACRO)    macro aggregator matrix
 AMAC(MACRO)             additive error for macro constraints
 LMAC(MACRO)             multiplicative error for macro constraints
 JWT                     weights for error support set  /1*3 /
*Cells falling into the household income from factors block
 FACtorSHR(H,AC)
;

SCALAR
 cutoff            lower bound on absolute cell values          /0.0000 /
 epsilon           epsilon value for cross-entropy minimand     /.00001 /
;

*-----------------------------------------------------------------------
*Parameters and variables ----------------------------------------------
*-----------------------------------------------------------------------

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
 vbar4(h,AC,jwt)   Error support set 4 for household factor income shares
 wbar1(ac,jwt)     Weights on error support set 1
 wbar2(macro,jwt)  Weights on error support set 2
 wbar3(ac,acp,jwt) Weights on error support set 3
 wbar4(h,AC,jwt)   Weights on error support set 4
 sigmay1(ac)       Prior standard error of column sums
 sigmay2(macro)    Prior standard error of macro aggregates
 sigmay3(ac,acp)   Prior standard error for cell constraints
 sigmay4(h,AC)     Prior standard error for factor income constraints
 fachhdtarg(h,AC)  Target factor income shares
 ;

VARIABLES
 TSAM(AC,ACP)      SAM values
 COEFF(AC,ACP)     SAM coefficients
 COLSUM(AC)        column sums
 ERR1(AC)          Error value on column sums
 ERR2(MACRO)       Error value for macro aggregates
 ERR3(AC,ACP)      Error value for cell constraint
 ERR4(h,AC)        Error value for factor income distribution
 W1(AC,jwt)        Error weights
 W2(macro,jwt)     Error weights
 W3(AC,ACP,jwt)    Error weights
 W4(H,AC,jwt)      Error weights
 DENTROPY          Entropy difference (objective)
;

*-----------------------------------------------------------------------
*Equations -------------------------------------------------------------
*-----------------------------------------------------------------------

EQUATIONS
 SAMFLOW1(ac,acp)  SAM flows with additive errors
 SAMFLOW2(ac,acp)  SAM flows with logarithmic errors
 SAMCOEFF1(ac,acp) SAM coefficients with additive errors
 SAMCOEFF2(ac,acp) SAM coefficients with logarithmic errors
 COLSUMEQ1(ac)     column sums with additive errors
 COLSUMDEF(ac)     define column sums
 COEFFDEF(ac,acp)  define coefficients
 SAMEQ(ac)         Row and column sum constraint
*macro constraints
 MACROEQ(macro)    macro aggregation constraints
 ERROR1EQ(ac)      definition of error term 1
 ERROR2EQ(macro)   definition of error term 2
 ERROR3EQ(ac,acp)  definition of error term 3
 ERROR4EQ(h,AC)    definition of error term 4
 SUMW1(ac)         sum of weights 1
 SUMW2(macro)      sm of weights 2
 SUMW3(ac,acp)     sum of weights 3
 SUMW4(h,AC)       sum of weights 4
 FACHHDEQ(H,AC)    factor incomes to households
 ENTROPY           entropy difference definition
;

*Equations  ############

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
  COEFF(acnt,acntp) =E= TSAM(acnt,acntp)/COLSUM(acntp);

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
                            +
               SUM((H,ACNT,jwt)$FACtorSHR(H,ACNT),
                    W4(H,ACNT,jwt)
                  * (LOG(W4(H,ACNT,jwt) + epsilon)
                  - LOG(wbar4(H,ACNT,jwt) + epsilon)))
;

 FACHHDEQ(H,ACNT)$FACtorSHR(H,ACNT)..
  TSAM(H,ACNT)/SUM(ACNTP$FACtorSHR(H,ACNTP), TSAM(H,ACNTP)) =E= fachhdtarg(h,ACNT) + ERR4(H,ACNT);

 ERROR4EQ(H,ACNT)$FACtorSHR(H,ACNT)..
  ERR4(H,ACNT) =E= SUM(jwt, W4(H,ACNT,jwt)*vbar4(H,ACNT,jwt)) ;

 SUMW4(H,ACNT)$FACtorSHR(H,ACNT)..
  SUM(jwt, W4(H,ACNT,jwt)) =E= 1 ;


*-----------------------------------------------------------------------
*SAM calibration -------------------------------------------------------
*-----------------------------------------------------------------------

 TSAM0(acnt,acntp) = SAM(acnt,acntp);

*DIAGNOSTICS
*$include diagnostic.inc

*Define various sets based on initial SAM, tsam0

*For a SAM, which is square, ACBAL is the entire set.
 ACBAL(ACNT) = YES;
*Make only household accounts active
 ACBAL(H) = YES;

 TSAM0('TOTAL',ACNTP)  = SUM(ACNT,  TSAM0(ACNT,ACNTP));
 TSAM0(ACNT,"TOTAL")   = SUM(ACNTP, TSAM0(ACNT,ACNTP));
 SAMBALCHK(ACNT)$ACBAL(ACNT) = TSAM0('TOTAL',ACNT) - TSAM0(ACNT,'TOTAL');

DISPLAY "TSAM0 before balancing", TSAM0, SAMBALCHK;

*Define column sums that can be constrained.
*Might want to exclude columns with only one entry. Or, alternatively,
*leave them in and define entry constraint in terms of coefficients.
*Can exclude any other columns for which column constraints do not
*make a lot of sense.
*Balance accounts which sum to zero by definition should probably be
*constrained exactly, with no error. Can be done by simply setting their
*prior standard error, sigmay1, to zero, which will happen automatically if
*the target column sum is zero. See section on defining sigmay1.

PARAMETER
 COUNTCOL(AC)  number of nonzero cells in columns
 COUNTROW(AC)  number of nonzero cells in rows
;

LOOP (ACNTP,
 COUNTCOL(ACNTP) = 0 ;
 COUNTROW(ACNTP) = 0 ;
 LOOP (ACNT,
   COUNTCOL(ACNTP)$TSAM0(ACNT,ACNTP) = COUNTCOL(ACNTP) + 1 ;
   COUNTROW(ACNTP)$TSAM0(ACNTP,ACNT) = COUNTROW(ACNTP) + 1 ;
 );
);

*Define column and row sets for all accounts with any nonzero elements in the
*corresponding row and column. A pure balancing SAM account might have a row or
*column with all zeros. It is harmless to exclude such accounts from the
*balancing procedure, but they must be part of ACBAL.
 ICOL(ACNT)$(COUNTCOL(ACNT) OR ACBAL(ACNT)) = YES;
 IROW(ACNT)$(COUNTROW(ACNT) OR ACBAL(ACNT)) = YES;

*Define columns and rows with nonzero sums and compute column coefficients.
*Nonzero here is defined as significant absolute value so that column
*coefficients can be computed safely.
 ICOLNZ(ACNT)$(ABS(TSAM0('TOTAL',ACNT) GT 0.00)) = YES;
 COEFF0(ACNT,ICOLNZ)      = TSAM0(ACNT,ICOLNZ)/TSAM0('TOTAL',ICOLNZ);
 COLSUM0(ACNT)$ICOL(ACNT) = TSAM0('TOTAL',ACNT);

*Define column accounts that will have constraints. Start by assuming all
*column accounts will be constrained. Those with zero or negative sums cannot
*have column coefficients that are constrained.
 ICOL2(ACNT) = ICOL(ACNT);

*Constrain column sums where there will be lots of coefficients. Otherwise, we
*will only be constraining relative cell values, not values.
 ICOL2(A) = NO;
 ICOL2(C) = NO;

*Assume all col sum errors are additive. Multiplicative column sum errors
*are not yet programmed.
 LCOL(ICOL2) = NO;
 ACOL(ICOL2) = YES;

*Find negative cell entries
 IZERO(ACNT,ACNTP)$(TSAM0(ACNT,ACNTP) EQ 0)   = YES;
 NONZERO(ACNT,ACNTP)$(NOT IZERO(ACNT,ACNTP))  = YES;
 INEG(ACNT,ACNTP)$((TSAM0(ACNT,ACNTP) LT 0) AND NONZERO(ACNT,ACNTP)) = YES;

*Specify nature of cell error, whether on coefficients or on values,
*and whether additive or multiplicative.
*Negative cells are specified as values with additive errors.
*All positive cells are initially specified with multiplicative errors
*on values. This ensures that positive cells will not change sign.
*Then various cells are chosen to be specified as coefficients.
*All coefficient cells are specified with multiplicative errors.

 IVALUE(ACNT,ACNTP)$(NONZERO(ACNT,ACNTP)) = YES;

*Now set cells which are naturally seen as coefficients. Do not specify as
*coefficient if cell does not have a positive coefficient value, coeff0.

*Set any negative cells to values
 IVALUE(ACNT,ACNTP)$INEG(ACNT,ACNTP) = YES;

*Set cells in columns with only one cell to value
 IVALUE(IROW,ICOL)$((COUNTCOL(ICOL) EQ 1) AND NONZERO(IROW,ICOL)) = YES;

*Set any cells in columns with negative or zero sum to values. Such cells
*should not have a positive coeff0, but this is an extra check.
 IVALUE(ACNT,ACNTP)$(ICOL(ACNTP) AND (COLSUM0(ACNTP) LT 0)
                 AND ICOLNZ(ACNTP)) = YES;

*Set all non-household cells to fixed
 IVALUE(ACNT,ACNTP)$((NOT H(ACNT)) AND (NOT H(ACNTP))) = NO;
*Set household expenditures to coefficients
 IVALUE(ACNT,H)$(COEFF0(ACNT,H) GT 0) = NO ;

*If cell error is not on values, then it will be on coefficients.
 ICOEFF(ACNT,ACNTP)$((NOT IZERO(ACNT,ACNTP))
                 AND (NOT IVALUE(ACNT,ACNTP))) = YES;

 ICOEFF(ACNT,ACNTP)$((NOT H(ACNT)) AND (NOT H(ACNTP))) = NO;

 ESTIMATE(ACNT,ACNTP)$(IVALUE(ACNT,ACNTP) or ICOEFF(ACNT,ACNTP)) = YES;

*Start by assuming that all cells have additive errors.
 ACELL(ACNT,ACNTP)$ESTIMATE(ACNT,ACNTP) = YES;

*Turn off ACELL for cells that have multiplicative errors
 ACELL(ACNT,ACNTP)$ICOEFF(ACNT,ACNTP) = NO;
*Make sure that ACELL is on for negative cells
 ACELL(ACNT,ACNTP)$INEG(ACNT,ACNTP) = YES;

 LCELL(ACNT,ACNTP)$(NOT ACELL(ACNT,ACNTP)) = YES;

 IFIXV(ACNT,ACNTP)$((not IVALUE(ACNT,ACNTP)) and
                    (not ICOEFF(ACNT,ACNTP))) = YES;

*Check for errors. Cells cannot be constrained in both values and coefficients.
*All cells to be estimated must have lcell or acell.
SET
 ICHECK(ac,acp)  Error check for cell constraints
;

 ICHECK(ACNT,ACNTP)$(IVALUE(ACNT,ACNTP) AND ICOEFF(ACNT,ACNTP)) = YES;
DISPLAY 'Error check. Cells with both ivalue and icoeff', ICHECK ;

 ICHECK(ACNT,ACNTP)$(ESTIMATE(ACNT,ACNTP) AND ((NOT ACELL(ACNT,ACNTP)) AND
                                                NOT LCELL(ACNT,ACNTP))) = YES;
DISPLAY 'Error check. Cells to be estimated but neither acell nor lcell', ICHECK ;

 ICHECK(IROW,ICOL)$(ESTIMATE(IROW,ICOL) and IZERO(IROW,ICOL)) = YES;
DISPLAY 'Error check. Cells to be estimated but initially zero', ICHECK ;

DISPLAY
 COUNTROW, IROW, COUNTCOL, ICOL, ICOL2, LCOL, IZERO, NONZERO, INEG
 IVALUE, ICOEFF, ACELL, LCELL
;

*-----------------------------------------------------------------------
*Macro aggregates and other country-specific constraints ---------------
*-----------------------------------------------------------------------

*Define macro aggregates for household control totals
 MACAGG(A,H,'OWN')       = YES;
 MACAGG(C,H,'MKT')       = YES;
 MACAGG(H,FLAB,'LAB')    = YES;
 MACAGG(H,FCAP,'CAP')    = YES;
 MACAGG(H,FLND,'LND')    = YES;
 MACAGG(H,'ENT','ENT')   = YES;
 MACAGG(H,'GOV','GOV')   = YES;
 MACAGG(H,'ROW','ROW')   = YES;
 MACAGG('S-I',H,'GOV')   = YES;
 MACAGG('DTAX',H,'DTAX') = YES;

*The included constraints ensure that column totals for the household
*entries are fixed so that the balanced household block will fit cleanly
*into the pre-balanced aggregate household SAM from 2balance.gms
*$include 4macrocontrols.inc

*Initialize values from TSAM0
 MACTOTAL0(MACRO) = SUM((IROW,ICOL)$MACAGG(IROW,ICOL,MACRO), TSAM0(IROW,ICOL));

DISPLAY MACTOTAL0;

PARAMETER
 TOTINC(H)       total household income
;

 TOTINC(H) = SUM(FP, TSAM0(H,FP)) + TSAM0(H,'ENT') + SUM(HPP, TSAM0(H,HPP)) + TSAM0(H,'ROW');

 FACHHDTARG(H,F)$TOTINC(H)     = TSAM0(H,F)/TOTINC(H);
 FACHHDTARG(H,'ENT')$TOTINC(H) = TSAM0(H,'ENT')/TOTINC(H);
 FACHHDTARG(H,HP)$TOTINC(H)    = TSAM0(H,HP)/TOTINC(H);
 FACHHDTARG(H,'ROW')$TOTINC(H) = TSAM0(H,'ROW')/TOTINC(H);

 FACtorSHR(H,ACNT)$FACHHDTARG(H,ACNT) = YES;

DISPLAY FACtorSHR, FACHHDTARG;

*-----------------------------------------------------------------------
*Error bounds and support sets -----------------------------------------
*-----------------------------------------------------------------------

*Set sigmay1 and target column sums

* JT: target consumption spending since measured more accurately in most cases
  COLTARGET(ACBAL) = 1.0*COLSUM0(ACBAL) + 0.0*SUM(ICOL, TSAM0(ACBAL,ICOL));
  COLTARGET(ACNT)$(ICOL(ACNT) AND (NOT ACBAL(ACNT))) = COLSUM0(ACNT);

*Set sigmay1, standard errors for errors on column totals
  sigmay1(acnt)$(ICOL2(ACNT) AND ACOL(ACNT)) = 0.00001 * ABS(coltarget(ACNT));
  sigmay1(H)$(ICOL2(H) AND ACOL(H))          = 0.1 * ABS(coltarget(H));

*Set sigmay2, standard errors for errors on macro aggregates
  sigmay2(macro2) = 0.01*ABS(mactotal0(macro2));

*Set sigmay3, standard errors for errors on cell values
  sigmay3(ACNT,ACNTP)$(IVALUE(ACNT,ACNTP) AND ACELL(ACNT,ACNTP)) = 0.33 * ABS(tsam0(ACNT, ACNTP));
  sigmay3(ACNT,ACNTP)$(IVALUE(ACNT,ACNTP) AND LCELL(ACNT,ACNTP)) = 0.33;

  sigmay3(ACNT,ACNTP)$(ICOEFF(ACNT,ACNTP) AND ACELL(ACNT,ACNTP)) = 0.33 * ABS(coeff0(ACNT, ACNTP));
  sigmay3(ACNT,ACNTP)$(ICOEFF(ACNT,ACNTP) AND LCELL(ACNT,ACNTP)) = 0.33;

  sigmay3(ACNT,H)$(ICOEFF(ACNT,H) AND LCELL(ACNT,H)) = 0.5;
  sigmay3(H,ACNT)$(ICOEFF(H,ACNT) AND LCELL(H,ACNT)) = 0.5;

  sigmay4(H,ACNT)$FACtorSHR(H,ACNT)
    = 0.10 * ABS(TSAM0(H,ACNT)/SUM(ACNTP$FACtorSHR(H,ACNTP), TSAM0(H,ACNTP)));

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
  vbar1(ACNT,'1') = -3 * sigmay1(ACNT);
  vbar1(ACNT,'2') =  0;
  vbar1(ACNT,'3') = +3 * sigmay1(ACNT);

  wbar1(ACNT,'1') =  1/18;
  wbar1(ACNT,'2') = 16/18;
  wbar1(ACNT,'3') =  1/18;

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
  vbar1(ACNT,'1')  = -3 * sigmay1(ACNT);
  vbar1(ACNT,'2')  = -1 * sigmay1(ACNT);
  vbar1(ACNT,'3')  =  0;
  vbar1(ACNT,'4')  = +1 * sigmay1(ACNT);
  vbar1(ACNT,'5')  = +3 * sigmay1(ACNT);

  wbar1(ACNT,'1')  =   1/72;
  wbar1(ACNT,'2')  =  27/72;
  wbar1(ACNT,'3')  =  16/72;
  wbar1(ACNT,'4')  =  27/72;
  wbar1(ACNT,'5')  =   1/72;
$offtext

*$ontext
* Set constants for 3-weight error distribution
  vbar2(MACRO,'1')  = -3 * sigmay2(MACRO);
  vbar2(MACRO,'2')  =  0;
  vbar2(MACRO,'3')  = +3 * sigmay2(MACRO);

  wbar2(MACRO,'1')  =  1/18;
  wbar2(MACRO,'2')  = 16/18;
  wbar2(MACRO,'3')  =  1/18;
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
  vbar3(ACNT,ACNTP,'1')  = -3 * sigmay3(ACNT,ACNTP);
  vbar3(ACNT,ACNTP,'2')  =  0;
  vbar3(ACNT,ACNTP,'3')  = +3 * sigmay3(ACNT,ACNTP);

  wbar3(ACNT,ACNTP,'1')  =  1/18;
  wbar3(ACNT,ACNTP,'2')  = 16/18;
  wbar3(ACNT,ACNTP,'3')  =  1/18;
*$offtext

$ontext
* Set constants for 5-weight error distribution
  vbar3(ACNT,ACNTP,'1')  = -3 * sigmay3(ACNT,ACNTP);
  vbar3(ACNT,ACNTP,'2')  = -1 * sigmay3(ACNT,ACNTP);
  vbar3(ACNT,ACNTP,'3')  =  0;
  vbar3(ACNT,ACNTP,'4')  = +1 * sigmay3(ACNT,ACNTP);
  vbar3(ACNT,ACNTP,'5')  = +3 * sigmay3(ACNT,ACNTP);

  wbar3(ACNT,ACNTP,'1')  =   1/72;
  wbar3(ACNT,ACNTP,'2')  =  27/72;
  wbar3(ACNT,ACNTP,'3')  =  16/72;
  wbar3(ACNT,ACNTP,'4')  =  27/72;
  wbar3(ACNT,ACNTP,'5')  =   1/72;
$offtext

*$ontext
  vbar4(H,ACNT,'1') = -3 * sigmay4(H,ACNT);
  vbar4(H,ACNT,'2') =  0;
  vbar4(H,ACNT,'3') = +3 * sigmay4(H,ACNT);

  wbar4(H,ACNT,'1') =  1/18;
  wbar4(H,ACNT,'2') = 16/18;
  wbar4(H,ACNT,'3') =  1/18;
*$offtext

$ontext
*Error distribution set for factor income shares
* Set constants for 5-weight error distribution
  vbar4(H,ACNT,'1')  = -3 * sigmay4(H,ACNT) ;
  vbar4(H,ACNT,'2')  = -1 * sigmay4(H,ACNT) ;
  vbar4(H,ACNT,'3')  =  0              ;
  vbar4(H,ACNT,'4')  = +1 * sigmay4(H,ACNT) ;
  vbar4(H,ACNT,'5')  = +3 * sigmay4(H,ACNT) ;

  wbar4(H,ACNT,'1')  =   1/72;
  wbar4(H,ACNT,'2')  =  27/72;
  wbar4(H,ACNT,'3')  =  16/72;
  wbar4(H,ACNT,'4')  =  27/72;
  wbar4(H,ACNT,'5')  =   1/72;
$offtext

DISPLAY
 sigmay1, sigmay2, sigmay3, sigmay4
 vbar1, vbar2, vbar3, vbar4
;

*-----------------------------------------------------------------------
*Define model ----------------------------------------------------------
*-----------------------------------------------------------------------

MODEL SAMENTROP  /
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
 ERROR4EQ
 SUMW1
 SUMW2
 SUMW3
 SUMW4
 FACHHDEQ
 ENTROPY
/;

*-----------------------------------------------------------------------
*Intialize variables ---------------------------------------------------
*-----------------------------------------------------------------------

 TSAM.L(ACNT,ACNTP)       = tsam0(ACNT,ACNTP);
 COEFF.L(ACNT,ACNTP)      = coeff0(ACNT,ACNTP);
 COLSUM.L(ICOL)           = colsum0(ICOL);
 ERR1.L(AC)               = 0;
 ERR2.L(MACRO)            = 0;
 ERR3.L(AC,ACP)           = 0;
 ERR4.L(H,ACNT)           = 0;
 W1.L(ACNT,JWT)           = wbar1(ACNT,JWT);
 W2.L(MACRO,JWT)          = wbar2(MACRO,JWT);
 W3.L(ACNT,ACNTP,jwt)     = wbar3(ACNT,ACNTP,JWT);
 W4.L(H,ACNT,JWT)         = wbar4(H,ACNT,JWT);
 DENTROPY.L               = 0;

*-----------------------------------------------------------------------
*Define bounds for cell values -----------------------------------------
*-----------------------------------------------------------------------

* Defining equation SAMMAKE over non-zero elements of A ($Abar1(acnt,acntp))
* guarantees that the zero structure of the original SAM is maintained
* in the estimated SAM. Fixing all the zero entries to zero greatly
* reduces the size of the estimation problem. If it is desired to
* allow a zero entry to become nonzero in the estimated SAM, then
* the condition $ABAR1(acnt,acntp) must be replaced with a new set that
* does not include cells which are currently zero but may be nonzero.

* COEFF.LO(ACNT,ACNTP)$ICOEFF(ACNT,ACNTP)        = 0 ;
* COEFF.UP(ACNT,ACNTP)$ICOEFF(ACNT,ACNTP)        = 1 ;
* COEFF.FX(ACNT,ACNTP)$(NOT NONZERO(ACNT,ACNTP)) = 0;

*Fix coeff to zero if it is not a ivalue
 COEFF.FX(ACNT,ACNTP)$IFIXV(ACNT,ACNTP) = COEFF0(ACNT,ACNTP) ;

* TSAM.LO(ACNT,ACNTP)                    = 0.0 ;
* TSAM.UP(ACNT,ACNTP)                    = +inf ;
 TSAM.FX(ACNT,ACNTP)$IFIXV(ACNT,ACNTP)  = TSAM0(ACNT,ACNTP) ;

* Upper and lower bounds on the error weights
 W1.LO(ACNT,JWT)       = 0;
 W1.UP(ACNT,JWT)       = 1;
 W2.LO(MACRO2,JWT)     = 0;
 W2.UP(MACRO2,JWT)     = 1;
 W3.LO(ACNT,ACNTP,JWT) = 0;
 W3.UP(ACNT,ACNTP,JWT) = 1;
 W4.LO(H,ACNT,JWT)     = 0;
 W4.UP(H,ACNT,JWT)     = 1;

*If standard deviation of errors is set to zero, fix the weights to the prior
*so that the error will always be zero.
 W1.FX(ACNT,JWT)$(sigmay1(ACNT) EQ 0)             = wbar1(ACNT,JWT) ;
 W2.FX(MACRO2,JWT)$(sigmay2(MACRO2) EQ 0)         = wbar2(MACRO2,JWT) ;
 W3.FX(ACNT,ACNTP,JWT)$(sigmay3(ACNT,ACNTP) EQ 0) = wbar3(ACNT,ACNTP,JWT) ;
 W4.FX(H,ACNT,JWT)$(NOT FACtorSHR(H,ACNT))           = wbar4(H,ACNT,JWT) ;
 ERR1.FX(acnt)$(sigmay1(ACNT) EQ 0)               = 0 ;
 ERR2.FX(MACRO2)$(sigmay2(MACRO2) EQ 0)           = 0 ;
 ERR3.FX(ACNT,ACNTP)$(sigmay3(ACNT,ACNTP) EQ 0)   = 0 ;
 ERR4.FX(H,ACNT)$(NOT FACtorSHR(H,ACNT))             = 0 ;


*-----------------------------------------------------------------------
*Solve model -----------------------------------------------------------
*-----------------------------------------------------------------------

OPTION ITERLIM  = 100000;
OPTION LIMROW   = 0, LIMCOL       = 0;
OPTION SOLPRINT = OFF;
OPTION RESLIM   = 100000;

*OPTION NLP = PATHNLP ;
OPTION NLP = CONOPT3;

 SAMENTROP.HOLDFIXED = 1 ;

SOLVE SAMENTROP USING NLP MINIMIZING DENTROPY;

*-----------------------------------------------------------------------
*Reporting -------------------------------------------------------------
*-----------------------------------------------------------------------

PARAMETERS
 SAMCE(AC,ACP)      new balanced SAM flows from CE
 SEM                squared Error Measure
 VALDIFF(AC,ACP)    differnce btw original SAM and Final SAM in values
 PERDIFF(AC,ACP)    differnce btw original SAM and Final SAM in Percent
 BIGDIFFP(AC,ACP)   cells with large percent change
;

 SAMCE(ACNT,ACNTP)        = TSAM.L(ACNT,ACNTP);
 SAMCE('TOTAL',acntp)     = SUM(acnt, SAMCE(ACNT,ACNTP));
 SAMCE(acnt,'TOTAL')      = SUM(acntp, SAMCE(ACNT,ACNTP));

 SAMBALCHK(ACNT)$ACBAL(ACNT) = SAMCE('TOTAL',ACNT) - SAMCE(ACNT,'TOTAL');

 SEM = SUM((ACNT,ACNTP), SQR(COEFF.L(ACNT,ACNTP) - COEFF0(ACNT,ACNTP)))/SQR(9);

 VALDIFF(AC,ACP) = SAMCE(AC,ACP) - TSAM0(AC,ACP);
 PERDIFF(AC,ACP)$TSAM0(AC,ACP) = 100*(SAMCE(AC,ACP)/TSAM0(AC,ACP) - 1 );
 BIGDIFFP(AC,ACP)$(ABS(PERDIFF(AC,ACP)) GT 25) = perdiff(AC,ACP);

DISPLAY
 'SAMCE after balancing', SAMCE
 'SAMBALCHK after balancing', SAMBALCHK
 SEM, SAMCE, VALDIFF, PERDIFF, bigdiffp, DENTROPY.L
;

*Household income data (for checking)
 INCTAB(H,INCAC) = SAMCE(H,INCAC);
 EXPTAB(H,EXPAC) = SAMCE(EXPAC,H);
 EXPTAB(H,'AMAIZ') = SUM(A, SAMCE(A,H));
 EXPTAB(H,'CMAIZ') = SUM(C, SAMCE(C,H));
 EXPTAB(H,'CFOOD') = SUM(FOOD, SAMCE(FOOD,H));

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

 SAM(AC,ACP) = SAMCE(AC,ACP)/SCALE;


execute_unload "%output%.gdx" SAM
execute 'xlstalk.exe -m %output%.xlsx';
 XLTEST = ERRORLEVEL;
IF(XLTEST = 1,
execute 'xlstalk.exe -c %output%.xlsx';
);
IF(XLTEST = 2,
execute 'xlstalk.exe -s %output%.xlsx';
);
execute 'gdxxrw.exe i=%output%.gdx o=%output%.xlsx index=index!a25' ;
*execute 'xlstalk.exe -o %output%.xlsx';
DISPLAY XLTEST;



