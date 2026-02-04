/*
Author: Brian Holtemeyer 
Pupose: This do-file standardizes the povdiet data by
			- constructing variables 
			- forcing the exact number of variables and their order 
			- does various checks


	Variable table

						NEW_VARIABLE?	STRING?
		--------------------------------------------------------------------------------------------	
			isocode 		YES			YES				set these values in the locals at the top of the povdiet do-file; 3 letters
			nexus 			YES							set these values in the locals at the top of the povdiet do-file; 
			svy_yr1 		YES							set these values in the locals at the top of the povdiet do-file; first year
			svy_yr2 		YES							set these values in the locals at the top of the povdiet do-file; second year
			svy_name 		YES			YES				name of survey (eg HBS=Household Budget Survey)
			reg_str			YES			YES				should start with "R" & be 3 characters. Use regions used in $regname found in "NEXUS (Internal)\6 Poverty Diet Module\in\do\COUNTRY_in_YEAR.do"
			month			YES							month of survey 
			month_tm		YES							month & year of survey 
			geo1			YES 						geo var for stage 1 of heckman
			geo2			YES 						geo var for stage 2 of heckman
			qty_*_M 		YES							# of men 	in HH of some age range
			qty_*_F			YES 						# of women 	in HH of some age range
			hid  						YES
			reg  
			rural 
			hwt 
			pwt 
			hs 
			ae 
			farm 
			sex 
			age 
			educ 
			pl_nat 
			pl_usd_L 
			pl_usd_M 
			expend_deflator YES
			oexp_f  
			oexp_n 										This variable *might* need to be constructed (oexp_n = oexp_t - oexp_f) 
			oexp_t 	
		--------------------------------------------------------------------------------------------	

	change log: 
	2022-09-22	added vars ea, month, and qty_*_?
	2023-01-11	added program to construct national poverty rates that hit both national and rural poverty targets 
	
*/

cap program drop 	consistency_and_checks
program 			consistency_and_checks
qui { 



noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= begin: stanardized formatting & checks  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "



loc nexus 	= nexus[1]
loc yr1 	= svy_yr1[1]					/* these 2 locals are used to name the file that gets saved */
loc iso 	= isocode[1]				/* these 2 locals are used to name the file that gets saved */

* get a list of the nexus categories that should exist in this file, and save them to local `expend_vars' 
preserve 
	u "$nexus_path/4 Country SAMs/do/nexus_concordance" , clear 
	keep if n`nexus'==1
	replace nexus_cat="c"+nexus_cat
	levelsof nexus_cat, clean 
	loc expend_vars = "`r(levels)'"
restore 

unab HH_demographic_vars: qty_*_M qty_*_F

#delimit;
loc all_vars_in_order =  "
isocode 
nexus 
svy_yr1 
svy_yr2 
svy_name
hid 
hid_orig
HH_class 
HH_class_new 
reg 
reg_str 
rural 
hwt 
pwt 
hs 
ae 
farm 
sex 
age 
educ 
quint 
decil	
month 
month_tm 	
geo1 
geo2	
`HH_demographic_vars'	 
expend_deflator
pl_nat 
pl_usd_L 
pl_usd_M 
oexp_f  
oexp_n 	
oexp_t		" ; 
#delimit cr 

noi di _newline(2) 	"note 1: 'checks' have not been passed until there is no messages in red" 
noi di				"note 2: these are the variables that should exist in this data set: " _newline(1) 	" `all_vars_in_order' 	" _newline(2) 




tempfile tf_my_temp_12345
sa 		`tf_my_temp_12345'


noi di "* * * check the nexus vars ... "
preserve
	*identify the c???? vars in the data: 
	keep  `expend_vars'	
	des 	, clear replace 
	gen 	nexus_cat =	name
	replace nexus_cat = substr(name,2,4) if substr(name,1,1)=="c" & length(name)==5 
	lab var nexus_cat "nexus activity"
	mer m:1 nexus_cat using "$nexus_path\4 Country SAMs\do\nexus_concordance"
	
	noi di "      *nexus check 1) check for items that are not in the nexus concordance *at all*"
	cap assert _mer>1
	if _rc!=0 {
		noi di in red "there are nexus commodities that are not in the nexus concordance "
		noi ta nexus_cat _mer if _mer==1 , m 
		error_here
	}

	noi di "      *nexus check 2) check that there are not any items that should not exist in N`nexus' "
	cap assert n`nexus'==1 if _mer==3 
	if _rc!=0 {
		noi di in red "there are nexus commodities that should not be in N`nexus' concordance "
		noi list nexus_cat _mer n`nexus' if _mer==3 & n`nexus'!=1 
		error_here
	}

	noi di "      *nexus check 3) check that the # of c???? vars matches the specific nexus system"
	keep if _mer==3 
	levelsof nexus_cat 
	assert `r(r)'==`nexus'
	if _rc!=0 {
		noi di in red "the # of nexus groups is not `nexus' as expected: "
		noi levelsof nexus_cat
		noi return list 
		error_here
	}
restore 



di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= begin: new var construction =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "

foreach k in quint decil HH_class HH_class_new hid_orig 	n12_afat n12_dair n12_disc n12_frui n12_good n12_hous n12_legu n12_prot n12_root n12_serv n12_stap n12_vege    { 
	cap drop `k'
}

noi di "* * * construct decile and quintile variables"
xtile quint 	= oexp_t [w=pw], n(5)
xtile decil 	= oexp_t [w=pw], n(10)
lab var quint 	"quintiles of total expenditure per adult equivalent"
lab var decil 	"deciles of total expenditure per adult equivalent"


noi di "* * * construct 2 HH-class variables"
* 		1) new: 		hhd_TQ where T=type={r,u} 		& D=decile	= {1-10}
* 		2) original: 	hhd_TQ where T=type={f,n,u} 	& Q=quintile= {1-5}
tostring quint	, gen(quint_str) 
tostring decil	, gen(decil_str) 
g 		HH_class	 = "hhd_n"+quint_str 	if rural==1 & farm==2
replace	HH_class	 = "hhd_f"+quint_str 	if rural==1 & farm==1
replace	HH_class	 = "hhd_u"+quint_str 	if rural==2
lab var HH_class "class of HH; format: hhd_TQ where T=type={f,n,u} 	& Q=quintile= {1-5}"
g 		HH_class_new = "hhd_r"+decil_str 	if rural==1
replace	HH_class_new = "hhd_u"+decil_str 	if rural==2
lab var HH_class_new "class of HH; format: hhd_TD where T=type={r,u} & D=decile = {1-10}"
drop decil_str quint_str


noi di "* * * construct aggregated consumption groups N12_* (this makes our lives easier later)"
preserve 
	keep  			c????		hid
	reshape long 	c@, 	i(	hid) j(nexus_cat) str 
	mer m:1 nexus_cat using "$nexus_path\4 Country SAMs\do\nexus_concordance", //assert( 2 3 ) 
	ta nexus_cat _mer , m 
	keep if _mer==3 
	collapse (sum) 	c, by(hid 	nexus12)
	reshape wide 	c, i(hid) j(nexus12) str
	ren cg???? n12_????	
	unab N12_expend_vars: n12_????	
	loc all_vars_in_order="`all_vars_in_order' `N12_expend_vars' " 	/* add to the list */	
	foreach k in `N12_expend_vars' { 	
		lab var 	`k'	"daily expend per AE, aggregated to N12: `k'" 
	}
	tempfile tf_nexus12
	sa 		`tf_nexus12'
restore 
mer 1:1 hid using `tf_nexus12', assert(3) nogen 


noi di "* * * construct integer 'hid' variable from 1 to _N "
ren 	hid hid_orig
sort 		hid_orig
isid 		hid_orig
gen 	hid = _n 
lab var hid "hid variable constructed in 'povdiet_format' do-file" 

di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= end: new var construction =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "


noi di "* * * check the right variables EXIST"
set varabbrev off	
				foreach k in `all_vars_in_order' `expend_vars' { 
					capture confirm variable `k'
					if _rc!=0 {
						noi di in red "   variable |`k'| does not exist, and it should. please fix"
						
					}
				}
set varabbrev on 




noi di "* * * check variable types (these should be the only string variables: isocode,	hid,	HH_class,	reg_str" 
foreach k in `all_vars_in_order' { 
	loc vartype: type `k'
	if inlist("`k'", "hid_orig") {
		* we don't know what type of variable 'hid_orig' is because some surveys use strings while others use integers (which is fine)
		if substr("`vartype'",1,3)=="str" format hid_orig %15s
	}
	else { 
		if inlist("`k'","isocode",	"HH_class",	"HH_class_new", "reg_str", "svy_name") {
			cap assert substr("`vartype'",1,3)=="str"
			if _rc!=0 {
				noi di in red "   variable |`k'| has type `vartype' , but it should be a string "
				error_here
			}
		}
		else 	{
			cap assert substr("`vartype'",1,3)!="str"
			if _rc!=0 {
				noi di in red "   variable |`k'| has type `vartype' , but it should NOT be a string "
				error_here
			}
		}
	}
}

/* this isn't a very helpful check: */
** noi di "* * * check variables have a label (there's no way to check whether it's a good label!) "
** foreach k in `all_vars_in_order' { 
	** loc lab: var lab `k' 
	** if length("`lab'")<=3 {
		** noi di in red "   should be labelled better: `k'"
	** }
** }



noi di "* * * check values for all non-string vars are not missing"
foreach k in `all_vars_in_order' { 
	loc vartype: type `k'
	if substr("`vartype'",1,3)!="str" { 
		capture assert `k'<.
		if _rc!=0 {
			noi di in red "   variable |`k'| has some missing values and it should not. please fix"
			error_here
		}
	}
}


noi di "* * * check values are >0"
foreach k in 	 	 	 hwt pwt hs ae 	 sex 	 educ svy_yr1 svy_yr2 quint { 
	capture assert `k'>0
	if _rc!=0 {
		noi di in red "   variable |`k'| has some 0 values and it should not. please fix"
		error_here
	}
}

di "* * * misc checks on numeric vars"
tempvar mean_hwt
egen `mean_hwt' = mean(hwt)
loc num_check1 = "inlist(sex,1,2)							"
loc num_check2 = "inlist(sex,1,2) 							"		
loc num_check3 = "inlist(farm,1,2) 							"	
loc num_check4 = "inlist(rural,1,2) 						"	
loc num_check5 = "inrange(age,0,130)						"	
loc num_check6 = "inlist(educ,1,2,3,4)						"		
loc num_check7 = "inlist(quint,1,2,3,4,5)					"	
loc num_check8 = "inrange(decil,1,10)						"	
loc num_check9 = "inrange(hs,1,55)							"	
loc num_check10= "inrange(month,1,12)		| month== 	99	"	
loc num_check11= "inrange(month_tm,600,800)	| month_tm==99	"	
loc num_check12= "inrange(`mean_hwt',100,10000)				"
loc num_check13= "inrange(expend_deflator,0.6,1.3)			"
loc num_check14= "oexp_f> 0									"
loc num_check15= "oexp_n>=0									"
loc num_check16= "abs(oexp_t -(oexp_f+oexp_n))<0.0000000001	"
loc num_check17= "quint==1 if inlist(decil,1,2)				"
loc num_check18= "quint==2 if inlist(decil,3,4)				"
loc num_check19= "quint==3 if inlist(decil,5,6)				"
loc num_check20= "quint==4 if inlist(decil,7,8)				"
loc num_check21= "quint==5 if inlist(decil,9,10)			"
loc num_check22= "abs(hs - round(hs,1))<0.0001				"
loc num_check23= "abs(pwt/hwt - hs)    <0.0001				"
forv k= 1/23 { 
	cap assert `num_check`k''
	if _rc!=0 noi di in red "   failed this check: `num_check`k''"
}
foreach k in `HH_demographic_vars' {
	cap assert inrange(`k',0,30) | `k'==99
	if _rc!=0 {
		noi di in red "   failed this check: assert inrange(`k',0,30) | `k'==99 "
		noi ta `k' , m 
	}
	
	egen 				avg_qty = mean(`k') 
	cap assert inrange(	avg_qty,0,3) | `k'==99
	if _rc!=0 {
		noi di in red "   failed this check: assert inrange(avg_qty,0.0001,3) | `k'==99 "
		noi su `k' , m 
	}
	drop avg_qty
}







levelsof quint , clean
cap assert `r(r)'==5						
if _rc!=0 {
	noi di in red "   variable |quint| does not have 5 unique values"
	error_here
}
levelsof decil, clean
cap assert `r(r)'==10
if _rc!=0 {
	noi di in red "   variable |decil| does not have 10 unique values"
	error_here
}

noi di "* * * There should not be few HHs with a given poverty line "
if "`iso'"!="IND" { 
	preserve 
		collapse (count) N = hwt , by(pl_nat rural quint) 
		cap assert N>=30				/* arbitrary */
		if _rc!=0 {
			noi list * 
			noi di in red "   fewer than 30 HHs with a given poverty line"
		}
	restore 
}

noi di "* * * misc checks on string vars"
noi { 
	assert length(reg_str)==3
	assert length(HH_class)==6
	assert substr(reg_str,1,1)=="R"
	assert substr(HH_class,1,4)=="hhd_"
	assert inlist(substr(HH_class,-1,1),"1","2","3","4","5")
	assert inlist(substr(HH_class,-2,1),"n","f","u")
	assert substr(HH_class,-2,1)=="f" if rural==1 & farm==1
	assert substr(HH_class,-2,1)=="n" if rural==1 & farm==2
	assert substr(HH_class,-2,1)=="u" if rural==2
}

noi di "* * * potential 'red flags' (It *might* be fine, but we should confirm)"
preserve /* check geo1 */ 
	g HHs_per_geo=1
	collapse (sum) HHs_per_geo, by(geo1) 
	su HHs_per_geo
	lab var HHs_per_geo "HHs per geo" 
	cap assert inrange(HHs_per_geo,10,1000) 
	if _rc!=0 { 
		noi di in red "   **potential** 'red flag': I expect the # of HHs per geo1 area to be roughly in this inteval: 100 - 1000"
		noi ta HHs_per_geo, m 
	}
restore 


preserve /* check geo2 */
	g HHs_per_geo=1
	collapse (sum) HHs_per_geo, by(geo2) 
	su HHs_per_geo
	lab var HHs_per_geo "HHs per geo" 
	cap assert inrange(HHs_per_geo,10,100) 
	if _rc!=0 { 
		noi di in red "   **potential** 'red flag': I expect the # of HHs per geo2 area to be roughly in this inteval: 10 - 100"
		noi ta HHs_per_geo, m 
	}
restore 




levelsof HH_class , clean
cap assert `r(r)'==15					
if _rc!=0 {
	noi ta HH_class quint, m 
	noi di in red "   **potential** 'red flag': I expect |HH_class| has 15 unique values, but it's possible to have fewer, in theory"
	
}

levelsof pl_nat , clean
cap assert `r(r)'<=5			/* arbitrary */	
if _rc!=0 {
	noi di in red "   **potential** 'red flag': ariable |pl_nat| has over 5 unique values, which seems high. Confirm that this is right"
	
}
preserve 
	collapse (sum) pwt, by(quint)
	su pwt 
	*cap 	assert `r(max)'/`r(min)' < 1.25		/* if each quintile has about 20% of the population, then the max/min should not be far from 1 */			
	cap 	assert `r(max)'/`r(min)' < 3		/* if each quintile has about 20% of the population, then the max/min should not be far from 1 */			
	
	/* result for NGA wave 4 surprised me, so I changed from 1.25 to 3. 
					 +---------------------+
					 | quinti~s        pwt |
					 |---------------------|
				  1. |        1   5.76e+07 |
				  2. |        2   4.65e+07 |
				  3. |        3   3.84e+07 |
				  4. |        4   3.09e+07 |
				  5. |        5   2.01e+07 |
					 +---------------------+
	*/
	if _rc!=0 {
		noi list * 
		noi di in red  "   **potential** 'red flag': There is higher-than-expected variation in the # of people per quintile"
		
	}
restore 
preserve 
	ta rural, gen(rural_) 
	ta rural_1 rural, m 			/* rural_1 should be "rural"; rural_2 should be "urban" */
	su rural_1 [aw=hwt]
	cap assert `r(mean)'<0.9 
	cap assert `r(mean)'>0.3 
	if _rc!=0 {
		noi 	su rural_1 [aw=hwt]
		noi di in red "   **potential** 'red flag': The share of HHs that are rural is outside the interval [30% - 90%] "
		
	}
restore 





noi di "* * * formatting "
format `expend_vars'	hwt	pwt	ae 		hs	farm	age	educ	quint decil oexp_?	pl_* 	%11.0fc 
format 	hid 		svy_yr1	svy_yr2	nexus													%9.0f
format 	svy_name																			%15s

isid 	hid 
sort 	hid 
order 	`all_vars_in_order'
keep 	`all_vars_in_order'

lab data " `iso' 'povdiet' data; constructed in '4 Country SAMs' or '4 Nexus 90' "

*note: "add notes here"


noi di _newline(2) "saving a copy here: "   
noi sa 		"$nexus_path\6 Poverty Diet Module\in\data\survey_`iso'_`yr1'" 	,	replace 

noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= end: stanardized formatting & checks  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "

}
end 


cap program drop 	nat_pov_lines
program 			nat_pov_lines
qui { 
	
	/* use this code to construct a national poverty rate */
	
	syntax , mode(str) target(str)  nat(real) [nat_R(numlist) ]

	noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
	noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= begin: constructing national poverty line =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
	noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
	noi di _newline(2) "----------------------------------------------------------------------------------------------------------------------|"
	noi di "target='nat'         ==> target only national poverty rates      (if 'nat' selected, then choice of mode has no effect)"
	noi di "target='nat_and_rur' ==> target national & rural poverty rates"
	noi di "		if 'nat_and_rur' selected, then mode choice has effect: "
	noi di "			mode='1line'  ==> single national poverty line by rescaling expenditures"
	noi di "			mode='2lines' ==> have separate poverty line for urban & rural areas, no expenditure rescaling"
	noi di "----------------------------------------------------------------------------------------------------------------------|"

	noi di 	in red  _newline(2) 	"selected target: `target'"  _newline(1)		"selected mode: `mode'"
	noi di in text "" 
	
	if 1<2 { /* checks */
		*pl_nat should not *already* exist 
		cap order pl_nat 
		if _rc==0 { 
			noi di "pl_nat should not exist"
			error_here
		}
			
		cap assert inlist("`mode'","1line","2lines")
		if _rc!=0 { 
			noi di "mode should be '1line' or '2lines'"
			error_here
		}
		cap assert inlist("`target'","nat","nat_and_rur")
		if _rc!=0 { 
			noi di "target should be 'nat' or 'nat_and_rur'"
			error_here
		}
		
		foreach k in nat_R 		nat { 
			cap assert "`k'"!=""
			if _rc!=0 { 
				noi di "`k' must be set"
				error_here
			}
		}
		foreach k in rural pwt oexp_t {
			cap order `k' 
			if _rc!=0 { 
				noi di "`k' variable does not exist"
				error_here
			}
		}
		cap assert inlist(rural,1,2)
		if _rc!=0 { 
			noi di "rural outside of 1-2"
			error_here
		}
	}
	
	
	g double expend_deflator=1  /* ie no adjustment to expenditures in order to hit regional poverty rate */
	format expend_deflator %9.4fc
	lab var expend_deflator "expenditure deflator so that a single poverty line can hit multiple targets"

	if "`target'"=="nat" {				/* if there is NO rural poverty rate target */
		noi di _newline(2) "pov target for `k' is `PRT_nat'"
		_pctile oexp_t [pw=pwt] , p(`nat')						
		gen pl_nat = `r(r1)' 			
		lab var pl_nat 		"daily per national poverty line" 	

		* show info about deflator and poverty lines
		noi ta 	expend_deflator 	rural, m 
		noi ta 	pl_nat			 	rural, m 
		
		*checks 
		noi di _newline(2) "targets: 'national' =`nat'" 
		noi sepov 	oexp_t 	[pw=pwt], p(pl_nat) 	alfa(0)
	}
	if "`target'"=="nat_and_rur" {		/* if there IS a  rural poverty rate target */
	
		* determine the urban poverty rate (nat_U) needed to hit the national number (nat; function of urban/rural populations and gap between national and rural poverty rates) 
		foreach k in 1 2 { 
			su 	pwt 		if rural==`k' 
			loc pwt`k' = `r(mean)'*`r(N)'
		}
		loc nat_U= `nat' - (`nat_R'-`nat') * (`pwt1'/`pwt2')
		noi di "in order to hit the national target of `nat'%, as an intermediate step, the urban rate must be `nat_U'%" 
		cap assert inrange(`nat_U',0,100)
		if _rc!=0 { 
			noi di "nat_U outside of 0-100"
			error_here
		}
		

		if "`mode'"=="1line" {  
			_pctile oexp_t [pw=pwt] if rural==1 , p(`nat_R'	)						
			loc pl_R 	= `r(r1)' 		
			_pctile oexp_t [pw=pwt] if rural==2 , p(`nat_U'	)						
			loc pl_U 	= `r(r1)' 			 
			_pctile oexp_t [pw=pwt] 			, p(`nat'	)						
			loc pl_nat 	= `r(r1)' 			 
			g  	pl_nat  = `r(r1)' 			/* notice that this is a single number across urban and rural areas */
			replace expend_deflator =  	`pl_nat'/`pl_R'  	if rural==1
			replace expend_deflator = 	`pl_nat'/`pl_U' 	if rural==2 
			replace oexp_t = oexp_t*expend_deflator 	 
			replace oexp_f = oexp_f*expend_deflator 	 
			replace oexp_n = oexp_n*expend_deflator 	 
		}
		if "`mode'"=="2lines" {  
			_pctile oexp_t [pw=pwt] if rural==1 , p(`nat_R')						
			gen 	double pl_nat = `r(r1)' 		if rural==1
			_pctile oexp_t [pw=pwt] if rural==2 , p(`nat_U')						
			replace 		pl_nat = `r(r1)' 		if rural==2 
		}
		
		lab var pl_nat 		"daily per national poverty line" 	

		* show info about deflator and poverty lines
		noi ta 	expend_deflator 	rural, m 
		noi ta 	pl_nat			 	rural, m 
		
		*checks 
		noi di _newline(2) "targets: 'rural'  =`nat_R'" 
		noi sepov 	oexp_t 	[pw=pwt], p(pl_nat) 	alfa(0)	by(rural)

		noi di _newline(2) "targets: 'national'=`nat'" 
		noi sepov 	oexp_t 	[pw=pwt], p(pl_nat) 	alfa(0)
	}
	
	noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
	noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- done: constructing national poverty line =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
	noi di " =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- "
	
}
end 




exit 




