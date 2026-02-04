*---Farm incomes

*   Crop	

	*Crop harvests on a large scale
   	use "..\data\cs_S7D_large_crop", clear
	rename hhid	hid
    replace hid = hid - 100000
	rename s7dq7 harvst
	keep hid crop harvst 
	tempfile large
	save `large'

	*Crop harvests on a small scale
	use "..\data\cs_s7e_small_crop", clear
	rename hhid	hid
    replace hid = hid - 100000
	rename s7eq2 crop 
	drop if crop == 99
	duplicates tag hid crop s7eq8, gen(dupli)
	*Cleaning: drop one of the 100 duplicates
	bysort hid crop s7eq8: drop if dupli>0 & _n==1
	rename s7eq8 harvst
	keep hid crop harvst 
	tempfile small
	save `small'
	
	*Other income from agriculture, exclude forestry
	use "..\data\cs_S7F_income_agriculture", clear
	rename hhid	hid
    replace hid = hid - 100000
	rename s7fqcode crop 
*	lab drop s7fqcode
	replace crop = 100 + crop
	keep if (crop == 101 | crop == 102 | crop == 103 | crop == 104 | crop == 110 | crop == 111 | crop == 112 ) & (s7fq2!=. | s7fq3 !=.) 
	gen harvst = s7fq3 
	replace harvst = s7fq2 * 12 if s7fq1==1 & s7fq3==0
	keep hid crop harvst 
	tempfile other
	save `other'
	
	*Merge crop all harvest
	append using `large'
	append using `small'
	append using `other'
	
	*Map crops onto SAM accounts 
	merge m:1 crop using "..\dofiles\3mapcrop_x104", keep(3) nogen
	
*	Create temporary working file
	keep hid crop sam samdesc harvst
	rename harvst cropinc
	recode cropinc (.= 0)
	*Sum up at household and crop level 
	duplicates tag hid crop, gen(multi)
	tab multi
	collapse (sum)cropinc, by(hid crop sam samdesc)
	*	Scale values to millions
	replace cropinc = cropinc / 1000000
	sort hid crop
	save  "..\work\3crop", replace

*	Livestock
	use "..\data\cs_s7a1_livestock", clear
	rename hhid hid
    replace hid = hid - 100000
	
	rename s7aq5 own
	rename s7aq6  p_u 
	rename s7aq3 lvstk
	gen lvstk_val = own * p_u 
	rename lvstk_val lvstkinc 
	keep if lvstkinc>0 & lvstkinc!=.
	keep hid lvstk lvstkinc 
	tempfile lvstk1
	save `lvstk1'

*	Livestock Products
	use "..\data\cs_s7a3_livestock", clear
	rename hhid hid
    replace hid = hid - 100000
	rename s7a3q1 lvstk
	rename s7a3q3 month
	gen lvstkinc = s7a3q7 * month  
	*Shift item codes to address conflicting codes between livestock and livestock products
	replace lvstk = lvstk + 70
	lab val lvstk lvstk
	keep if lvstkinc>0 & lvstkinc!=.
	keep hid lvstk lvstkinc

*	Merge livestock value with income from livestock products 
	append using  `lvstk1'

*	Map livestock onto SAM accounts 
	merge m:m lvstk using  "..\dofiles\3maplvstk_x104"
	drop _m

*	Create temporary working file
	keep hid lvstk sam samdesc lvstkinc	
	recode lvstkinc	 (.=0)
	*	Scale values to millions
	replace lvstkinc = lvstkinc / 1000000
	sort hid lvstk
	save  "..\work\3lvstk", replace

*---Master farm income file

	use  "..\work\3crop", clear
    rename cropinc frminc
	tempfile crop
	save `crop'
  
	use  "..\work\3lvstk", clear
	rename lvstkinc frminc
	append using  `crop'
  
	order hid sam samdesc crop lvstk frminc
    sort hid sam
	drop crop lvstk
	save  "..\work\3farm", replace
	
*---Wage
	*Net salary in cash
	use "..\data\cs_s6b_employement_6c_salaried_s6d_business", clear
	rename hhid hid
    replace hid = hid - 100000
	
	rename s6bq4b sector
	gen     wage1 = s6cq17a  if s6cq17b==4 
	replace wage1 = s6cq17a * 10 if s6cq17b==3       
	replace wage1 = s6cq17a * 50 if s6cq17b==2   
	replace wage1 = s6cq17a * 200 if s6cq17b==1  
	
	*In-kind payments
	gen     wage2 = s6cq19a  if s6cq19b==4 
	replace wage2 = s6cq19a * 10 if s6cq19b==3       
	replace wage2 = s6cq19a * 50 if s6cq19b==2   
	replace wage2 = s6cq19a * 200 if s6cq19b==1  
	
	*Housing subsidy
	gen     wage3 = s6cq21a  if s6cq21b==4 
	replace wage3 = s6cq21a * 10 if s6cq21b==3       
	replace wage3 = s6cq21a * 50 if s6cq21b==2   
	replace wage3 = s6cq21a * 200 if s6cq21b==1  
	
	*Other allowances
	gen     wage4 = s6cq23a  if s6cq23b==4 
	replace wage4 = s6cq23a * 10 if s6cq23b==3       
	replace wage4 = s6cq23a * 50 if s6cq23b==2   
	replace wage4 = s6cq23a * 200 if s6cq23b==1 
	
	egen wage = rsum(wage1 wage2 wage3 wage4)
	keep hid pid sector wage

*	Merge with sam sector mapping
	sort sector
	*ISIC4 var is by name (not coded), see manual coding by sectordesc
	*bysort s6bq4b: tab s6bq4a
*	merge m:m sector using  "$path0\dofiles\3mapsector"
	merge m:m sector using  ..\dofiles\3mapsector_x104, nogen
	keep if pid != .
	keep if wage > 0 

	*so many mixed farming", replace with maize
	*rename sector sectordesc
	replace sam = 1 if  samdesc == "unmapped"
	order hid pid sam samdesc sectordesc wage
	sort hid pid
	*	Scale values to millions
	replace wage = wage / 1000000
    save  "..\work\3wage", replace

*---Nonfarm enterprise incomes
	use "..\data\cs_s6b_employement_6c_salaried_s6d_business", clear
	rename hhid hid
    replace hid = hid - 100000
	rename s6bq4b sector
	
	gen sales=s6dq34a if s6dq34b==4
    replace sales=s6dq34a * 200 if s6dq34b==1
	replace sales=s6dq34a * 50 if s6dq34b==2
	replace sales=s6dq34a * 10 if s6dq34b==3

	*Merge with sam sector mapping
	sort sector
	merge m:m sector using  ..\dofiles\3mapsector_x104, nogen
	keep if pid != .
	keep  if sales > 0 & sales != .
	
	* Drop one obs. with high sales (cap at top 1% of sales earnings)
	sum sales, detail
	drop if sales>10^9
	keep hid pid sam samdesc sectordesc sales 
	
	*replace mixed farming with maize
	replace sam = 1 if  samdesc == "unmapped"
	order hid pid sam samdesc sectordesc sales 
	sort hid 
	*	Scale values to millions
	replace sales = sales / 1000000
	save ..\work\3ent, replace	

*---Other incomes 
	*Income support programmes
	use "..\data\cs_s9d_other_income", clear
	rename hhid hid
    replace hid = hid - 100000
	
	rename s9dq3 misc
	drop if s9dq0 >= .
	collapse (sum) misc, by(hid s9dq0)
	reshape wide misc, i(hid)j(s9dq0)
	tempfile 3temp_misc1_20
	save `3temp_misc1_20'
*/
		
	use "..\data\cs_s9b_transfers_in", clear
	rename hhid hid
    replace hid = hid - 100000
	egen misc21=rsum(s9bq7 s9bq10 s9bq12) 
	collapse (sum) misc21, by(hid)
	lab var misc21  "Annual cash and food transfers received from other households"  
	keep hid misc21
	tempfile 3temp_misc21
	save `3temp_misc21'

	*
	use "..\data\cs_s7b1_land_agriculture", clear
	rename hhid hid
    replace hid = hid - 100000
	
	rename s7b1q8 misc22
	lab var misc22 "amount received from land rental in the last 12 months"
	keep hid misc22
	tempfile 3temp_misc22
	save `3temp_misc22'

	*
	use "..\data\cs_s7b2_land_agriculture", clear
	rename hhid hid
    replace hid = hid - 100000
	rename s7b2q9  misc23
	collapse (sum) misc23, by(hid)
	lab var misc23 "amount received from agr. equipment rental in the last 12 months"
	keep hid misc23
	tempfile 3temp_misc23
	save `3temp_misc23'

	*
*	use "$path0\data\cs_s9c_vup", clear
	use "..\data\cs_s9c_vup_ubudehe_and_Rssp_schemes", clear
	rename hhid hid
    replace hid = hid - 100000
	
	gen annualVUP = s9cq10*s9cq11
	rename annualVUP  misc24 
    lab var misc24 "VUP, UBUDEHE direct suppport over the last 12 months"
    keep hid misc24
	tempfile 3temp_misc24
	save `3temp_misc24'
	
	use "..\data\cs_s9c3_vup_ubudehe_and_Rssp_schemes", clear
	rename hhid hid
    replace hid = hid - 100000	
	rename s9cq27  misc25
	lab var misc25 "Payment to hh over the last 12 months"
	keep hid misc25
	tempfile 3temp_misc25
	save `3temp_misc25'

*---Master misc income file
	use `3temp_misc1_20'
	merge 1:1 hid using  `3temp_misc21'
	drop _m
	merge 1:1 hid using `3temp_misc22'
    drop _m
	merge 1:1 hid using  `3temp_misc23'
    drop _m
	merge 1:1 hid using  `3temp_misc24'
    drop _m
	merge 1:m hid using  `3temp_misc25'
	drop _m
	
	*Scale values to millions
	for var misc21-misc25: recode X .=0
	for var misc1-misc25: replace X = X / 1000000
	save  "..\work\3misc", replace 

