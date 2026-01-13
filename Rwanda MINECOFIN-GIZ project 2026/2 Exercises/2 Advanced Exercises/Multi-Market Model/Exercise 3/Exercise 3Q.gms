$TITLE Demand-supply multi-market training model (Exercise 2)


*1. Sets ----------------------------------------------------------------

SETS
 C       commodities     / agr, ind /
;

ALIAS (C,CP);

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
 Y0              income          / 300 /
 W               wage rate       / 1 /
*elasticities and intercepts
 s0(C)           supply curve intercept
 s1(C)           price elasticity of supply
 d0(C)           demand curve intercept
 d1(C)           price elasticity of demand
 d2(C)           income elasticity of demand
 d3(C,CP)        cross-price elasticity of demand
;

TABLE MAP(C,CP)
         agr   ind
 agr      0     1
 ind      1     0  
;

*gives values to the various elasticity parameters
*i.e., slope of curve multiplied by initial price/quantity ratio
 s1(C) = 0.50 * (QS0(C)/P0(C));
 d1(C) = 2.00 * (QD0(C)/P0(C));
 d2(C) = 0.75 * (QD0(C)/Y0);
 d3(C,CP)$MAP(C,CP) = 0.50 * (QD0(C)/P0(CP));

*calculate intercept parameters for demand and supply curves
 s0(C) = QS0(C) - s1(C)*P0(C);
*** New ***
 d0(C) = QD0(C) + d1(C)*P0(C) - d2(C)*Y0 - SUM(CP$MAP(C,CP), d3(C,CP)*P0(CP));


*3. Variables -----------------------------------------------------------

VARIABLES
 QD(C)           demand quantity
 QS(C)           supply quantity
 P(C)            market price
*** New ***
 Y               income
;

*Set the value (level) of variables to initial values
 QD.L(C) = QD0(C);
 QS.L(C) = QS0(C);
 P.L(C)  = P0(C);
*** New ***
 Y.L     = Y0;


*4. Equations -----------------------------------------------------------

EQUATIONS
 DEMAND(C)       demand curve
 SUPPLY(C)       supply curve
*** New ***
 INCOME          income
 MKTEQU(C)       market equilibrium
;

 DEMAND(C)..     QD(C)   =E= d0(C) - d1(C)*P(C) + d2(C)*Y + SUM(CP$MAP(C,CP), d3(C,CP)*P(CP));
 SUPPLY(C)..     QS(C)   =E= s0(C) + s1(C)*P(C);
 INCOME..        Y       =E= SUM(C, w*QS(C));
 MKTEQU(C)..     QD(C)   =E= QS(C);

*5. Model ---------------------------------------------------------------

MODEL MMMOD      demand-supply model /
 DEMAND
 SUPPLY
*** New ***
 INCOME
 MKTEQU
/;

SOLVE MMMOD USING MCP;

 S0('AGR') = S0('AGR') * 0.8;
 SOLVE MMMOD USING MCP;

*Display initial and final values
*** New ***
DISPLAY d0, d1, d2, s0, s1, QD0, QD.L, QS0, QS.L, P0, P.L, Y0, Y.L;
