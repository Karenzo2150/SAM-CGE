clear
set more off

*cd "A:\Dropbox (IFPRI)\NEXUS\Nexus Project\7 AgGDP+\SAMs\RWA_X104\Surveys\EICV5_2017_104\dofiles"

cd "C:/Users/`c(username)'/Dropbox (IFPRI)/NEXUS 3.0/4 Country SAMs/RWA/Surveys/EICV5_2017_104/dofiles"

*---Step 1: Weight file ---
*	Create weight file [1weights.dta] with variables [hid hw pw hs]
	do 1weights.do
	
*---Step 2: Household consumption file ---
*	Generate consumption file [2consumption.dta] 
*   with variables [hid item itemdesc valp valh valk valt sam samdesc]
	do 2consumption.do
	
*---Step 3: Household income file ---
*	Generate income file [3incomes.dta] 
*	with variables [hid sales frminc wage misc1 misc2 misc3 misc income] 
	do 3incomes.do
	
*---Step 4: Labor classifications ---
*	Generate labor classification file
*   hid educ labclass
	do 4labclass.do
	

*---Step 5: Household classifications ---
*	National SAM split (used for documentation)
*   hid educ hhclass0	
	do 5hhdclass.do

*---Step 6: SAM tables ---
*	Produce SAM tables in the "output" folder 
	do 6samtables.do
