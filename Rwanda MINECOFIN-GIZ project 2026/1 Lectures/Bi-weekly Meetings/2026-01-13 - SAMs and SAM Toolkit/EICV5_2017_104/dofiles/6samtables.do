*	Table 1: For own consumption share of total consumption
	use ..\work\2consumption, clear
	merge m:m hid using ..\work\1weights, nogen
	merge m:m hid using ..\work\5hhdclass, nogen
	*Move own consumption of agricultural products to purchased products if nonfarm households
	replace valp = valp + valh if farm  == 2 & area == 1 & valh > 0 & sam <30
	replace valh = 0 if farm  == 2 & area == 1 & valh > 0 & sam <30
	collapse (sum) valt valh [iw=hw], by(sam)
	merge 1:m sam using 6order_act, nogen
	recode valt valh (.=0)
	format valt valh %12.0fc
	order sam samdes valt valh 
	sort sam
	save ..\output\1ownshr, replace
	
*	Table 2: Household own consumption values by HH class 
	use ..\work\2consumption, clear
	merge m:m hid using ..\work\1weights, nogen
	merge m:m hid using ..\work\5hhdclass, nogen
	*Move own consumption of agricultural products to purchased products if nonfarm households
	replace valp = valp + valh if farm  == 2 & area == 1 & valh > 0 & sam <30
	replace valh = 0 if farm  == 2 & area == 1 & valh > 0 & sam <30
	*replace hhdclass0  = 111 if hhdclass0  == 121  & valh > 0 & sam <30
	*replace hhdclass0  = 112 if hhdclass0  == 122  & valh > 0 & sam <30
	*replace hhdclass0  = 113 if hhdclass0  == 123  & valh > 0 & sam <30
	*replace hhdclass0  = 114 if hhdclass0  == 124  & valh > 0 & sam <30
	*replace hhdclass0  = 114 if hhdclass0  == 125  & valh > 0 & sam <30
	collapse (sum) valh [iw=hw], by(sam hhdclass0)
	replace valh = valh / 1000
	drop if hhdclass0==.
	reshape wide valh, i(sam) j(hhdclass0) 
	renpfix valh hhd
	merge 1:m sam using 6order_act, nogen
	order sam samdesc 
	sort sam
	drop sam
	save ..\output\2acthhd, replace

*	Table 3: Household marketed consumption values by HH class 
	use ..\work\2consumption, clear
	merge m:m hid using ..\work\1weights, nogen
	merge m:m hid using ..\work\5hhdclass, nogen
	*Move own consumption of agricultural products to purchased products if nonfarm households
	replace valp = valp + valh if farm  == 2 & area == 1 & valh > 0 & sam <30
	replace valh = 0 if farm  == 2 & area == 1 & valh > 0 & sam <30
	collapse (sum) valp [iw=hw], by(sam hhdclass0)
	replace valp = valp / 1000
	drop if hhdclass0==.
	reshape wide valp, i(sam) j(hhdclass0) 
	renpfix valp hhd
	merge 1:m sam using 6order_act, nogen
	order sam samdes
	sort sam
	drop sam
	save ..\output\3comhhd, replace
	
*	Table 4: Household total consumption values by HH class 
	use ..\work\2consumption, clear
	merge m:m hid using ..\work\1weights, nogen
	merge m:m hid using ..\work\5hhdclass, nogen
	*Move own consumption of agricultural products to purchased products if nonfarm households
	*replace valp = valp + valh if farm  == 2 & area == 1 & valh > 0 & sam <30
	*replace valh = 0 if farm  == 2 & area == 1 & valh > 0 & sam <30
	collapse (sum) valp valh [iw=hw], by(sam hhdclass0)
	gen valt = (valp+valh) / 1000
	drop valh valp
	drop if hhdclass0==.
	reshape wide valt, i(sam) j(hhdclass0) 
	renpfix valt hhd
	merge 1:m sam using 6order_act, nogen
	order sam samdes
	sort sam
	drop sam
	save ..\output\4comhhd_tot, replace

*	Table 4: Crop earnings by sector and labor type (household level)
	use ..\work\4labclass, clear
	bysort hid: keep if _n==1
	merge m:m hid using ..\work\3crop, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	collapse (sum) cropinc  [iw=hw], by(labclass sam)
	reshape wide cropinc , i(sam) j(labclass) 
	renpfix cropinc flab
	merge m:m sam using 6order_act, nogen
	order sam samdes
	sort sam
	drop sam
	save ..\output\4labcrop, replace
	
*	Table 5: Livestock earnings by sector and labor type (household level)
	use ..\work\4labclass, clear
	bysort hid: keep if _n==1
	merge m:m hid using ..\work\3lvstk, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	collapse (sum) lvstkinc  [iw=hw], by(labclass sam)
	reshape wide lvstkinc , i(sam) j(labclass) 
	renpfix lvstkinc flab
	merge m:m sam using 6order_act, nogen
	order sam samdes
	sort sam
	drop sam
	save ..\output\5lablvstk, replace
	
*	Table 6: Crop earnings by labor and household type 
	use ..\work\4labclass, clear
	bysort hid: keep if _n==1
	merge m:m hid using ..\work\3crop, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	merge m:m hid using "..\work\5hhdclass", keep(3) nogen
	collapse (sum) cropinc [iw=hw], by(labclass hhdclass0)
	reshape wide cropinc, i(hhdclass0) j(labclass) 
	renpfix cropinc flab
	rename hhdclass0 hhdclass
	merge m:m hhdclass using 6order_hhd, nogen
	order hhdclass hhddesc 
	sort hhdclass
	drop hhdclass
   	save ..\output\6hhdcrp, replace	
	
*	Table 7: Livestock earnings by labor and household type (household level)
	use ..\work\4labclass, clear
	bysort hid: keep if _n==1
	merge m:m hid using ..\work\3lvstk, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	merge m:m hid using ..\work\5hhdclass, keep(3) nogen
	collapse (sum) lvstkinc [iw=hw], by(labclass hhdclass0)
	reshape wide lvstkinc, i(hhdclass0) j(labclass) 
	renpfix lvstkinc flab
	rename hhdclass0 hhdclass
	merge m:m hhdclass using 6order_hhd, nogen
	order hhdclass hhddesc 
	sort hhdclass
	drop hhdclass
	save ..\output\7hhdliv, replace

*	Table 8: Wage earnings by sector and labor type (individual level)
	use ..\work\4labclass, clear
	merge m:m hid pid using ..\work\3wage, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	collapse (sum) wage  [iw=hw], by(labclass sam)
	reshape wide wage , i(sam) j(labclass) 
	renpfix wage flab
	merge m:m sam using 6order_act, nogen
	order sam samdes
	sort sam
	drop sam
	save ..\output\8labwage, replace
	
*	Table 9: Wage earnings by labor and household type (individual level)
	use ..\work\4labclass, clear	
	merge m:m hid pid using ..\work\3wage, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	merge m:m hid using ..\work\5hhdclass, keep(3) nogen
	collapse (sum) wage [iw=hw], by(labclass hhdclass0)
	reshape wide wage, i(hhdclass0) j(labclass) 
	renpfix wage flab
	rename hhdclass0 hhdclass
	merge m:m hhdclass using 6order_hhd, nogen
	order hhdclass hhddesc 
	sort hhdclass
	drop hhdclass
	save ..\output\9hhdwage, replace
	
*	Table 10: Wage employment by labor and household type (individual level)
	use ..\work\4labclass, clear	
	merge m:m hid pid using ..\work\3wage, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	merge m:m hid using ..\work\5hhdclass, keep(3) nogen
	collapse (sum) hw, by(labclass hhdclass0)
	reshape wide hw, i(hhdclass0) j(labclass) 
	renpfix hw flab
	rename hhdclass0 hhdclass
	merge m:m hhdclass using 6order_hhd, nogen
	order hhdclass hhddesc 
	sort hhdclass
	drop hhdclass
	save ..\output\10hhdemp, replace

*	Table 11: Non-farm enterprise earnings (SALES) by labor type and SAM (household level)
	use ..\work\4labclass, clear
	merge m:m hid using ..\work\3ent, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	collapse (sum) sales  [iw=hw], by(labclass sam)
	reshape wide sales , i(sam) j(labclass) 
	renpfix sales flab
	merge m:m sam using 6order_act, nogen
	order sam samdes
	sort sam
	drop sam
	save ..\output\11labent, replace

*	Table 12: Non-farm enterprise earnings (SALES) by labor and household type (household level)
	use ..\work\4labclass, clear
	merge m:m hid using ..\work\3ent, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	merge m:m hid using ..\work\5hhdclass, keep(3) nogen
	collapse (sum) sales [iw=hw], by(labclass hhdclass0)
	reshape wide sales, i(hhdclass0) j(labclass) 
	renpfix sales flab
	rename hhdclass0 hhdclass
	merge m:m hhdclass using 6order_hhd, nogen
	order hhdclass hhddesc 
	sort hhdclass
	drop hhdclass
	save ..\output\12hhdent, replace

*	Table 13: Misc earnings by household type
	use ..\work\5hhdclass, clear
	merge m:m hid using ..\work\3misc, keep(3) nogen
	merge m:m hid using ..\work\1weights, keep(3) nogen
	collapse (sum) misc1-misc25 [iw=hw], by(hhdclass0)
	lab var misc1 "The Rwanda Social Security Board"
    lab var misc2 "Payments for medical treatment"
    lab var misc3 "Old Age Grant"
    lab var misc4 "The Genocide Survivors Support and Assistance Fund (FARG)"
    lab var misc5 "Local government education  support"
    lab var misc6 "Educational scholarships (primary, secondary, university, TV"
    lab var misc7 "The Rwanda Demobilization and Reintegration Commission (RDRC"
    lab var misc8 "Food relief"
    lab var misc9 "Allowance for  dismissal or termination  of employment"
    lab var misc10 "Government donations of goods (Telephones, bicycles, mosquit"
    lab var misc11 "Other benefits to the household  - e.g. NGOs (Specify)"
    lab var misc12 "Pension from  the private sector"
    lab var misc13 "Private savings fund (private sector)"
    lab var misc14 "Insurance  dividends"
    lab var misc15 "Dowry, contribution to wedding or inheritance"
    lab var misc16 "Gambling â Lottery â Tombola"
    lab var misc17 "Sale of  fixed / non fixed assets"
    lab var misc18 "Property rent (Fixed or non-fixed assets)"
    lab var misc19 "NGO/ Charity contribution to education costs"
    lab var misc20 "Other benefits (specify..)"
	lab var misc21 "cash and food transfers received"                                                         
	lab var misc22 "amount received from land rental"                                           
	lab var misc23  "amount received from agr. equipment rental" 
	lab var misc24 "VUP, UBUDEHE direct suppport over the last 12 months"
	lab var misc25 "Payment to hh over the last 12 months"
	rename hhdclass0 hhdclass
	sort hhdclass
	merge m:m hhdclass using 6order_hhd, nogen
	order hhdclass hhddesc
	sort hhdclass
	drop hhdclass
	save ..\output\13misc_hhd, replace
	
*	Table 14: National populations by household type 
	use ..\work\5hhdclass, clear
	merge m:m hid using ..\work\1weights, keep(3) nogen		
	replace hw = hw / 1000
	replace pw = pw / 1000
	collapse (sum) pw hw, by(hhdclass0)
	rename hhdclass0 hhdclass
	sort hhdclass
	merge m:m hhdclass using 6order_hhd, nogen
	order hhdclass hhddesc
	sort hhdclass
	drop hhdclass
	save ..\output\14hhdpop_nat, replace

exit
	
*	Microsim
	use "..\data\EICV5_Poverty_file", clear
	rename weight hw
	rename pop_wt pw
	rename member hsisze
*EAA - Add Cons1 since 'cons1' is reported in EICV5_poverty_file and not in 5hhdclass as below.
    replace cons1 = cons1/1000000
	
	keep hhid hw pw hs ur
**	keep hhid hw pw hs ur cons1
	rename ur urban
	merge 1:1 hhid using "..\data\cs_s0_s5_household"
	rename hhid hid	
    replace hid = hid - 100000
	merge m:m hid using "..\work\5hhdclass", nogen keep(3)
*	replace Consumption = Consumption / 1000000
*	collapse (sum) Consumption [iw=hw], by(hhdclass0)

merge m:m hid using "$path0\work\cons1"

	collapse (sum) cons1 [iw=hw], by(hhdclass0)
	sort hhdclass0
	merge m:m hhdclass0 using "..\dofiles\3maphhd", nogen
	order order
	sort order
	save "..\work\xtotcons", replace
	
*---Detailed single consumption vector	
	
	use "..\work\2consumption", clear
	drop if valt == 0
	merge m:m hid using "..\work\1weights"
	drop _m
	collapse (sum) valt [iw=hw], by(sam samdesc item itemdesc)
	rename valt total
	order total sam samdesc total item itemdesc 
	sort item
	drop if item == .
	save "..\output\comvect", replace

