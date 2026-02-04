*s=national gdx=national
*NEXUS 58 sector SAM Building Toolkit
*Step 1: National SAM with aggregate household and labor account

$setglobal national "1RWA_X104_2017"
$setglobal output   "0output"

*$call "xlstalk -s %national%.xlsx"
$call "gdxxrw i=%national%.xlsx o=%national%.gdx index=index!a7"
$gdxin %national%.gdx

SET
*SAM sets
 AC              micro SAM accounts
 ACNT(AC)        micro SAM accounts without total
 A(AC)           activities
 C(AC)           commodities
 F(AC)           factors
 T(AC)           taxes
*Data sets
 MAC             macro SAM accounts
 MACNT(MAC)      macro SAM accounts without total
 SAC             supply use table accounts
*Mappings
 MAPAC(A,C)      activity to commodity
 MAPMAC(MAC,AC)  macro to micro
;

$load    MAC SAC AC
$loaddc  A C F T MAPAC MAPMAC

 ACNT(AC) = YES;
 ACNT('TOTAL') = NO;

 MACNT(MAC) = YES;
 MACNT('MTOT') = NO;

ALIAS (MAC,MACP), (MACNT,MACNTP), (AC,ACP), (ACNT,ACNTP), (A,AP), (C,CP), (F,FP), (T,TP);

PARAMETER
 SCALE           scaling multiplier      / 1.000 /
 SAM(AC,ACP)     micro SAM
*Data parameters
 MSAM(MAC,MACP)  macro SAM
 SUT(C,SAC)      supply-use table
 USE(AC,A)       use table
 SUPPLY(A,C)     supply table
*Checking balances
 MSAMX(MAC,MACP) reconstructed macro SAM
 DIFF(AC)        micro SAM row and column differences
 MDIFF(MAC,MACP) differences between original and reconstructed macro SAMs

;

$load MSAM SUT USE SUPPLY

*Activities -----------

*Production
 SAM(ACNT,A) = USE(ACNT,A);
*Activity taxes (producer taxes less subsidies)
 SAM('ATAX',A)$SUM(C, SUT(C,'TAX_PRD')) = SUM(C$MAPAC(A,C), SUT(C,'TAX_PRD')/SUM(CP, SUT(CP,'TAX_PRD'))) * MSAM('MATX','MACT');
*Marketed supply
 SAM(A,C) = SUPPLY(A,C);
 SAM(A,C)$MAPAC(A,C) = SAM(A,C) + SUM(ACNT, SAM(ACNT,A)-SAM(A,ACNT));


*Commodities ----------

*Final demand and imports
 SAM(C,'HHD')$SUM(CP, SUT(CP,'CON_PRV')) = SUT(C,'CON_PRV')/SUM(CP, SUT(CP,'CON_PRV')) * MSAM('MCOM','MHHD');
 SAM(C,'GOV')$SUM(CP, SUT(CP,'CON_PUB')) = SUT(C,'CON_PUB')/SUM(CP, SUT(CP,'CON_PUB')) * MSAM('MCOM','MGOV');
 SAM(C,'S-I')$SUM(CP, SUT(CP,'INV_DEM')) = SUT(C,'INV_DEM')/SUM(CP, SUT(CP,'INV_DEM')) * MSAM('MCOM','MS-I');
 SAM(C,'G-I')$SUM(CP, SUT(CP,'INV_GOV')) = SUT(C,'INV_GOV')/SUM(CP, SUT(CP,'INV_GOV')) * MSAM('MCOM','MG-I');
 SAM(C,'DSTK')$SUM(CP, SUT(CP,'INV_STK')) = SUT(C,'INV_STK')/SUM(CP, SUT(CP,'INV_STK')) * MSAM('MCOM','MSTK');
 SAM(C,'ROW')$SUM(CP, SUT(CP,'TRD_EXP')) = SUT(C,'TRD_EXP')/SUM(CP, SUT(CP,'TRD_EXP')) * MSAM('MCOM','MROW');
 SAM('ROW',C)$SUM(CP, SUT(CP,'TRD_IMP')) = SUT(C,'TRD_IMP')/SUM(CP, SUT(CP,'TRD_IMP')) * MSAM('MROW','MCOM');
*Transaction cost margins
 SAM('TRC',C) = SUT(C,'TRC_REC');
 SAM(C,'TRC') = SUT(C,'TRC_PAY');
*Commodity taxes (product taxes less subsidies)
 SAM('CTAX',C)$SUM(CP, SUT(CP,'TAX_IMP'))  = SUT(C,'TAX_IMP')/SUM(CP, SUT(CP,'TAX_IMP'))   * MSAM('MCTX','MCOM');
 SAM('ETAX',C)$SUM(CP, SUT(CP,'TAX_EXP'))  = SUT(C,'TAX_EXP')/SUM(CP, SUT(CP,'TAX_EXP'))   * MSAM('METX','MCOM');
 SAM('MTAX',C)$SUM(CP, SUT(CP,'TAX_EXM'))  = SUT(C,'TAX_EXM')/SUM(CP, SUT(CP,'TAX_EXM'))   * MSAM('MMTX','MCOM');
 SAM('STAX',C)$SUM(CP, SUT(CP,'TAX_SAL'))  = SUT(C,'TAX_SAL')/SUM(CP, SUT(CP,'TAX_SAL'))   * MSAM('MSTX','MCOM');
 SAM('VTAX',C)$SUM(CP, SUT(CP,'TAX_VAT'))  = SUT(C,'TAX_VAT')/SUM(CP, SUT(CP,'TAX_VAT'))   * MSAM('MVTX','MCOM');
 SAM('XTAX',C)$SUM(CP, SUT(CP,'TAX_EXD'))  = SUT(C,'TAX_EXD')/SUM(CP, SUT(CP,'TAX_EXD'))   * MSAM('MXTX','MCOM');

*Other accounts -------

 SAM(ACNT,ACNTP)$(NOT A(ACNT) AND NOT A(ACNTP) AND NOT C(ACNT) AND NOT C(ACNTP))
         = SUM((MACNT,MACNTP)$(MAPMAC(MACNT,ACNT) AND MAPMAC(MACNTP,ACNTP)), MSAM(MACNT,MACNTP));

*Check balances -------

 SAM('TOTAL',ACNT) = SUM(ACNTP, SAM(ACNTP,ACNT));
 SAM(ACNT,'TOTAL') = SUM(ACNTP, SAM(ACNT,ACNTP));
 DIFF(ACNT) = SAM('TOTAL',ACNT) - SAM(ACNT,'TOTAL');
 DIFF(ACNT)$(ABS(DIFF(ACNT)) LT 1E-6) = 0;

 MSAMX(MAC,MACP) = SUM((AC,ACP)$(MAPMAC(MAC,AC) AND MAPMAC(MACP,ACP)), SAM(AC,ACP));
 MDIFF(MAC,MACP) = MSAMX(MAC,MACP) - MSAM(MAC,MACP);
 MDIFF(MAC,MACP)$(ABS(MDIFF(MAC,MACP)) LT 1E-6) = 0;

 OPTION MDIFF:0, DIFF:0;
 DISPLAY MDIFF, DIFF;


PARAMETER
 CHKNEG(AC,ACP)
;

 CHKNEG(A,C)$(SAM(A,C) LT 0) = 1/0;
 CHKNEG(C,A)$(SAM(C,A) LT 0) = 1/0;
 CHKNEG(F,A)$(SAM(F,A) LT 0) = 1/0;
 CHKNEG(A,'HHD')$(SAM(A,'HHD') LT 0) = 1/0;
* CHKNEG(C,'HHD')$(SAM(C,'HHD') LT 0) = 1/0;
 CHKNEG(C,'S-I')$(SAM(C,'S-I') LT 0) = 1/0;
 CHKNEG(C,'GOV')$(SAM(C,'GOV') LT 0) = 1/0;
 CHKNEG(C,'ROW')$(SAM(C,'ROW') LT 0) = 1/0;
* CHKNEG('ROW',C)$(SAM('ROW',C) LT 0) = 1/0;
 CHKNEG('TRC',C)$(SAM('TRC',C) LT 0) = 1/0;
