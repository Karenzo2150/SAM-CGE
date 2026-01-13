$TITLE Demand-supply multi-market training model (Exercise 1)


*1. Sets ----------------------------------------------------------------

SETS
 C       commodities     / agr, ind /
;


*2. Parameters ----------------------------------------------------------

PARAMETERS
*initialization parameters (read in original data)
 QD0(C)          demand quantity /
         agr     200
         ind     100
 /
 QS0(C)          supply quantity /
         agr     200
         ind     100
 /
 P0(C)           market price /
         agr     1
         ind     1
 /
*elasticities and intercepts
 s0(C)           supply curve intercept
 s1(C)           price elasticity of supply
 d0(C)           demand curve intercept
 d1(C)           price elasticity of demand
;

*gives values to the various elasticity parameters
*i.e., slope of curve multiplied by initial price/quantity ratio
 s1(C) = 0.50 * (QS0(C)/P0(C));
 d1(C) = 2.00 * (QD0(C)/P0(C));

*calculate intercept parameters for demand and supply curves
 s0(C) = QS0(C) - s1(C)*P0(C);
 d0(C) = QD0(C) + d1(C)*P0(C);


*3. Variables -----------------------------------------------------------

VARIABLES
 QD(C)           demand quantity
 QS(C)           supply quantity
 P(C)            market price
;

*Set the value (level) of variables to initial values
 QD.L(C) = QD0(C);
 QS.L(C) = QS0(C);
 P.L(C)  = P0(C);


*4. Equations -----------------------------------------------------------

EQUATIONS
 DEMAND(C)       demand curve
 SUPPLY(C)       supply curve
 MKTEQU(C)       market equilibrium
;

 DEMAND(C)..     QD(C)   =E= d0(C) - d1(C)*P(C);
 SUPPLY(C)..     QS(C)   =E= s0(C) + s1(C)*P(C);
 MKTEQU(C)..     QD(C)   =E= QS(C);

*5. Model ---------------------------------------------------------------

MODEL MMMOD      demand-supply model /
 DEMAND
 SUPPLY
 MKTEQU
/;

SOLVE MMMOD USING MCP;

*Display initial and final values
DISPLAY d0, d1, s0, s1, QD0, QD.L, QS0, QS.L, P0, P.L;