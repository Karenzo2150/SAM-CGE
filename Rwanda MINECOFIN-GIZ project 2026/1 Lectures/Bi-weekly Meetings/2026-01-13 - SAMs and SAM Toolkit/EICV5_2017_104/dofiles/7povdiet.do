/* 	Objective: Create output file with following sets of variables
	
	Household demographics: hid hhdclass hs ae sex age educ reg hwt  
	Household consumption (per SAM): hid sam (total consumption)
	Official welfare aggregates (from poverty analysis): daily food and nonfood expenditure per adult equivalent & poverty line(s)
	
	
	edited by BH 
	note: this is in a "RWA_104" directory, but none of the nexus groups present are not in n86 

*/	
gl nexus_path = "C:/Users/BHOLTEMEYER/Dropbox (IFPRI)/NEXUS (Internal)"
cd "$nexus_path/4 Country SAMs\RWA_X104\Surveys\EICV5_2017_104"
** cd "C:\Users\KPAUW\Dropbox (IFPRI)\NEXUS (Internal)\4 Country SAMs\RWA_X104\Surveys\EICV5_2017_104\dofiles"


*copy do-file standard formatting & checks 	
copy	"$nexus_path/4 Country SAMs/do/povdiet_format_0111.do" ///
		"dofiles/povdiet_format_0111.do", replace
do 		"dofiles/povdiet_format_0111.do"

* necessary to fill these locals:
loc nexus		=	86					/* there might be 104 nexus groups in the SAM, but none of the HH expenditures are outside of N86 */
loc svy_yr1 	= 	2016
loc svy_yr2 	= 	2017
loc svy_name 	= 	"EICV=Rwanda Integrated Living Conditions Survey, 5"
loc isocode 	= 	"RWA"


* show the WDI poverty headcount ratio: 
	import excel "$nexus_path/6 Poverty Diet Module/in/data/global/WDI poverty.xlsx", sheet("POV") firstrow clear
	keep if inlist(CountryCode,"`isocode'")
	unab years: y????
	qui foreach k in `years' { 
		destring `k', replace force
		su `k'
		if `r(N)'==0 drop `k'
	}
	noi list CountryCode SeriesName y????, abb(20)
	
/*   +---------------------------------------------------------------------------------------------------------------------------+
     | CountryCode                                                            SeriesName   y2000   y2005   y2010   y2013   y2016 |
     |---------------------------------------------------------------------------------------------------------------------------|
  1. |         RWA   Poverty headcount ratio at $2.15 a day (2017 PPP) (% of population)    75.2    66.1    59.2    53.7      52 |
  2. |         RWA   Poverty headcount ratio at $3.65 a day (2017 PPP) (% of population)    89.5    83.8    82.3    79.7      78 |
  3. |         RWA   Poverty headcount ratio at $6.85 a day (2017 PPP) (% of population)      96    93.9    93.4    92.9    92.2 |
  4. |         RWA   Poverty headcount ratio at national poverty lines (% of population)       .       .       .    39.1    38.2 |
     +---------------------------------------------------------------------------------------------------------------------------+

*/
	

loc PRT_nat_R  	= 43.1		//  
loc PRT_nat  	= 38.2		//  
loc PRT_usd_L 	= 52		//  PRT="poverty rate target"; WDI $2.15 (PPP 2017) 
loc PRT_usd_M 	= 78		//  PRT="poverty rate target"; WDI $3.65 (PPP 2017)
	
	
	
qui { /* vars for estimating latent budget shares */


/* HH demographics */
		***************** edit this part: start *********************
		use "data\cs_S1_S2_S3_S4_S6A_S6E_Person", clear 
		keep hhid	s1q1		s1q3y
		ren (hhid	s1q1		s1q3y) (hid sex age)
		g 		sex_str = "F" if sex==2
		replace sex_str = "M" if sex==1
		ta sex sex_str, m 
		***************** edit this part: end *********************


ta age sex_str, m 
assert age<. 
sort hid age 
loc cutoffs = "5 20 30 40 50 60 70 120 "
keep hid age sex_str 
loc l = 0 
foreach k in `cutoffs' { 
	loc u = `k'
	g   	dm_F =	(`l'<=age & age<`u' & sex_str=="F" ) 
	g   	dm_M =	(`l'<=age & age<`u' & sex_str=="M" ) 
	egen  	qty_`l'_`u'_F = sum(dm_F), by(hid )
	egen  	qty_`l'_`u'_M = sum(dm_M), by(hid )
	drop 	dm_F dm_M 
	lab var  	qty_`l'_`u'_F "# of women in HH:  `l'<=age<`u'"
	lab var  	qty_`l'_`u'_M "# of   men in HH:  `l'<=age<`u'"
	loc l = `k'
}
keep hid qty_* 
duplicates drop 
des 
su 
tempfile tf_HH_structure
sa 		`tf_HH_structure'





/* month of interview */

		***************** edit this part: start *********************
		use "data\cs_S1_S2_S3_S4_S6A_S6E_Person", clear 
		keep hhid	s0q18?
		ren (hhid	s0q18m ) (hid month )
		gen month_tm = mofd(dofy(s0q18y))+month -1 
		lab var month_tm 	"month & year of consumption" 
		lab var month 		"month of consumption" 
		format month_tm %tm 
		duplicates  drop 
		list if _n<10

		***************** edit this part: end *********************
keep hid month*
tempfile tf_month_dummies
sa 		`tf_month_dummies'



/* enumeration area */
		***************** edit this part: start *********************
		use "data\cs_S0_S5_Household", clear
		ren  (hhid  district clust) (hid geo1  geo2)
		qui foreach k in  geo1 geo2 {
			levelsof `k'
			noi di  "levels of `k': `r(r)'"	
			bys `k': gen N_`k'=_N
			bys `k': gen n_`k'=_n
			lab var N_`k' "HHs per group using `k'"
			noi ta N_`k' if n_`k'==1 , m 
		}
		lab var geo1 "geo var used for first stage of heckman"
		lab var geo2 "geo var used for 2nd stage of heckman or OLS"
		***************** edit this part: end *********************
keep  	hid 	geo?

mer 	1:1 hid using 		`tf_HH_structure'	, nogen 
mer 	1:1 hid using 		`tf_month_dummies'	, nogen 

replace hid = hid - 100000 // See 1weights.do 



tempfile tf_latent_vars
sa 		`tf_latent_vars'

}


   	
* get a list of the nexus categories that should exist in this file
u "$nexus_path/4 Country SAMs/do/nexus_concordance" , clear 
** keep if dm_in_HH_file=="YES"
keep if n`nexus'==1
assert inlist(type,"f","n")
levelsof nexus_cat , clean loc(goods)






	* Start with hid data
	use "work\1weights", clear
	recode urban (1 = 2 "2 = Urban") (2 = 1 "1 = Rural"), gen(rural)
	ta urban rural, m 
	
	
	
	* Merge in person-level demographic data
	mer 1:m hid using "work\4labclass", nogen keep(3)
	rename (s1q1 s1q3y province) (sex age reg)		// Regions are Kigali - Southern - Western - Northern - Eastern 
	rename (hw pw) (hwt pwt)
	* Recreate hs variable as hs is inconsistent with hw and pw (note - this still results in integer household size)
	replace hs = pwt/hwt
	* Calculate own ae measure: compare with official measure later
	gen aew = age
	recode aew (0/2 = 0.40) (3/4 = 0.48) (5/6 = 0.56) (7/8 = 0.64) (9/10 = 0.76) (13/14 = 1.00) // All
	recode aew (11/12 = 0.80) (15/18 = 1.20) (19/59 = 1.00) (60/110 = 0.88) if sex == 1			// Male
	recode aew (11/12 = 0.88) (15/18 = 1.00) (19/59 = 0.88) (60/110 = 0.72) if sex == 2			// Female
	egen aeown = sum(aew), by(hid)
	
	* First person (pid = 1) is always head of household (s1q2)
	keep if pid == 1 
	keep hid hwt pwt hs aeown rural reg sex age educ labclass
	tempfile temp
	save `temp'

	/* 	Note on hhdclass: Rwanda SAM distinguishes rural, urban and kigali households, 
		by quintile. No farm variable although this is created in 5hhdclass.do. Consistent 
		our definition farm households are rural only and report some farm income */ 
	use "work\5hhdclass", clear
	* Remove duplicate households
	sort hid valh	valt	valp
	isid hid valh	valt	valp /* this is an important line if we want to be able to replicate our work */
	by hid: keep if _n==1
	keep hid hhdclass0 farm
	mer 1:1 hid using `temp', nogen keep(3)
	tempfile temp
	save `temp'
	
	* Consumption data (in millions per annum per household - convert later)
	use "work\2consumption", clear
	collapse (sum) valt, by(hid samdesc)
	reshape wide valt, i(hid) j(samdesc) string 
	recode valt* (.=0)
	rename valt* *

   	* for the missing goods, give them a value of 0 
	qui foreach k in `goods'  { 
		cap order 	c`k'
		if _rc!=0 {
			noi di "c`k' not found, so set generate it and set it to 0" 
			g 			c`k' = 0 	
			lab var 	c`k'  "nexus `k' "
		}
	}
		





	mer 1:1 hid using `temp', nogen keep(3)
	tempfile temp
	save `temp'
	
	* Poverty data - note Rwanda converted expenditures to 2014 prices and used the 2014 poverty line
	use "data\EICV5_Poverty_file", clear
	sa "work\my_original_data", replace
	keep hhid ae sol_jan foodshare1 epov_jan pov_jan pop_wt ur
	rename (hhid sol_jan epov_jan pov_jan) (hid oexp_t xpoor poor)
	recast double oexp_t
	ren pop_wt pwt 
    replace hid = hid - 100000 // See 1weights.do 
	gen double oexp_f = foodshare1*oexp_t
	* Official poverty lines (per poverty report)
	** gen pl_nat = 159375 // Jan 2014 national poverty line
	** gen pl_ext = 105064 // Extreme poverty - cost of aquiring 2500kcal/ae

	* Now inflate poverty lines and expenditures to 2016/2017 prices
	* CPI 2010-2019 = 100 103 114 120 123 126 135 147 146 151
	* Take 2014 and inflate using average of 2016/17 (survey took place Oct 2016 to Sep 2017)
	* Also change to daily 
	loc CPI_15_16 = (135 + 147)/2
	loc CPI_factor = `CPI_15_16' / 123
	noi di "cpi factor is `CPI_factor' " 
	foreach v in  oexp_t  oexp_f {
		replace `v' = `v'*`CPI_factor'/365 
	}
	gen double oexp_n = oexp_t - oexp_f

	lab var 	oexp_t	"total expenditure per day per adult equivalent" 
	lab var 	oexp_f	"food expenditure per day per adult equivalent" 
	lab var 	oexp_n	"nonfood expenditure per day per adult equivalent" 


	
	* Drop variables and merge
	keep hid ae oexp* 
	mer 1:1 hid using `temp', nogen keep(3)


	
	/* 
	--------------------------------------------------------------------------------------------------------------------------------
	------------------------------------------------constructing poverty lines------------------------------------------------------
	--------------------------------------------------------------------------------------------------------------------------------
		the WDI 		poverty lines are simple to construct. 								(use "simple loop") 
		the national 	poverty lines are simple to construct if rural poverty is unknown 	(use nat_pov_lines program; target="nat")
		the national 	poverty lines are harder to construct if rural poverty is   known 	(use nat_pov_lines program; target="nat_and_rur")
	*/
	* this program constructs the national poverty line ("pl_nat") to hit 2 poverty targets (national & rural) 
	nat_pov_lines, target("nat_and_rur") mode("1line") nat(`PRT_nat') nat_R(`PRT_nat_R') /* mode should be '1line' or '2lines'; target should be 'nat' or 'nat_and_rur' */

	* "simple loop": constructs poverty lines that hit a 1 poverty target
	foreach k in 	 "usd_L" 		"usd_M"  { 
		noi di _newline(2) "pov target for `k' is `PRT_`k''"
		_pctile oexp_t [pw=pwt] , p(`PRT_`k'')						
		gen pl_`k' = `r(r1)' 	
		sepov 	oexp_t [pw=pwt], p(pl_`k')
		if "`k'"=="usd_L" lab var pl_usd_L	"daily per AE poverty line using $2.15 (2017PPP)" 
		if "`k'"=="usd_M" lab var pl_usd_M	"daily per AE poverty line using $3.65 (2017PPP)" 
	}

	/*------------------------------------------------------------------------------------------------------------------------------
	--------------------------------------------------------------------------------------------------------------------------------
	--------------------------------------------------------------------------------------------------------------------------------
	*/


su pl_*
 
/*  Variable |        Obs        Mean    Std. dev.       Min        Max
-------------+---------------------------------------------------------
    pl_usd_L |     14,579    617.9137           0   617.9137   617.9137
    pl_usd_M |     14,579    1039.987           0   1039.987   1039.987
      pl_nat |     14,579    499.6633    2.621448   493.9372   500.8633
*/



* Compare official ae estimate with own
	sum ae aeown, det
	sum pw hw hs ae


ta reg, m 
decode reg  , gen(reg_str_temp)
g 		reg_str= "RKG" if reg_str_temp=="Kigali City"
replace reg_str= "RSP" if reg_str_temp=="Southern Province"
replace reg_str= "RWP" if reg_str_temp=="Western Province"
replace reg_str= "RNP" if reg_str_temp=="Northern Province"
replace reg_str= "REP" if reg_str_temp=="Eastern Province"
lab var reg_str "3-letter region string" 
ta  	reg_str	reg_str_temp, m 


* merge on the vars for estimating latent budget shares 
	mer 1:1 hid using 	`tf_latent_vars', 	assert(2 3)
	drop if _mer==2 
	drop _mer 


* survey id info 
g 		svy_yr1 	= `svy_yr1'
g 		svy_yr2 	= `svy_yr2'
g 		nexus 		= `nexus'
g 		isocode 	= "`isocode'"
g 		svy_name 	= "`svy_name'"
lab var svy_yr1 	"year 1 of survey"
lab var svy_yr2 	"year 2 of survey"
lab var nexus 		"number of nexus accounts (eg 86, 90, etc)"
lab var isocode 	"country"
lab var svy_name 	"name of survey"

	
	
*standard formatting & checks 	(this will also save a copy of the final data set here:	"$nexus_path/6 Poverty Diet Module/in/data" )
consistency_and_checks
	



sa "output\5povdiet", replace

exit 
