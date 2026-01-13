$TITLE Example on using GDX to import data from Excel and export to Excel

SET
 S1              set 1 from Excel
 S2              set 2 from Excel
;

PARAMETER
 P1(S1,S2)       imported parameter
 P2(S2,S1)       exported parameter
;


*Step 1: Import from Excel
execute 'xlstalk.exe -s example2.xlsx';
$call "gdxxrw i=example1.xlsx o=import.gdx index=index!a5"
$gdxin import.gdx
$load S1 S2
$loaddc P1
$gdxin

*Step 2: Transpose imported parameter
 P2(S2,S1) = P1(S1,S2);

*Step 3: Calculate totals
 P2('total',S1) = SUM(S2, P2(S2,S1));
 P2(S2,'total') = SUM(S1, P2(S2,S1));

*Step 4: Export new parameter back to Excel
execute_unload "export.gdx" P2
execute 'gdxxrw.exe i=export.gdx o=example1.xlsx index=index!a15';
execute 'xlstalk.exe -o example2.xlsx';