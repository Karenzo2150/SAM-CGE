*   See Contents of household consumption aggregates used for poverty analysis  (poverty report p.31)

*---Annual food expenditure ("$path0\data were collected during 10 visits that happen every two days in the areas outside Kigali City,
	
*	Purchased consumption
	use "..\data\cs_S8B_expenditure", clear
	rename hhid hid
    replace hid = hid - 100000
	rename s8bq0 item_p
	rename s8bq14 place
	egen valp = rowtotal(s8bq3 s8bq4 s8bq5 s8bq6 s8bq7 s8bq8 s8bq9 s8bq10 s8bq11 s8bq12)
	order valp,after(s8bq2)
	*fix missing months*
	egen avg_month=median(s8bq2) if s8bq2!=0,by(item_p)
	order avg_month,after (s8bq2)
	egen avg_month2=mean(avg_month),by(item_p)
	order avg_month2,after (avg_month)
	replace s8bq2=avg_month2 if valp>0 & s8bq2==0
	*replace valp = valp * s8bq2 if province==1
	replace valp = valp * 12 if province==1    /*Kigali's recall period is 30 days during the 11 visits*/
    *replace valp = valp/20 * (365*s8bq2/12) if province!=1 
    replace valp=valp/14*30*12 if province!=1 /*Outside Kigali's recall period is 14 days during the 8 visits*/
	/*use 12 months instead of the number of months from questionnaire to match the numbers in the poverty report*/
	keep hid item_p valp place
	*Give the same codes to purchased and home produced items (and consecutive to non-food codes)
    merge m:m item_p using  "..\dofiles\2map_purch_own", keep(3) nogen
	*Recode bar/restaurant purchases
	replace item = 309 if place == 8 	
	keep hid item item_p valp 
	tempfile purchase
	save `purchase'

*	Home produced consumption
	use  "..\data\cs_S8C_farming", clear
	rename hhid hid
    replace hid = hid - 100000
	rename s8cq0 item_h
	*egen qtyh = rowtotal(s8cq3 s8cq4 s8cq5 s8cq6 s8cq7 s8cq8 s8cq9 s8cq10 s8cq11 s8cq12)
	egen qtyh = rowtotal(s8cq4 s8cq4 s8cq5 s8cq6 s8cq7 s8cq8 s8cq9 s8cq10 s8cq11 s8cq12 s8cq13)
	order qtyh,after(s8cq2)
	*fix the missing months *
	egen avg_month=median(s8cq2) if s8cq2!=0,by(item_h)
	order avg_month,after (s8cq2)
	egen avg_month2=mean(avg_month),by(item_h)
	order avg_month2,after (avg_month)
	replace s8cq2=avg_month2 if qtyh>0 & s8cq2==0
	replace qtyh=qtyh*12 if province==1 /*Kigali's recall period is 30 days during the 11 visits*/
	*replace qtyh = qtyh/20*(365*s8cq2/12) if province!=1 
	replace qtyh=qtyh/14*30*12 if province!=1 /*Outside Kigali's recall period is 14 days during the 8 visits*/
	/*use 12 months instead of the number of months from questionnaire to match the numbers in the poverty report*/
	*the problem of missing unit price*
	*EAA    *what about the problem of 'Not applicable'*
	*egen med_price=median(s8cq14) if s8cq14>0 & s8cq14<9999 ,by(item_h)
    egen med_price=median(s8cq15) if s8cq15>0 & s8cq15<9999 ,by(item_h)
	*order med_price,after(s8cq14)
	order med_price,after(s8cq15)
	replace s8cq15=med_price if s8cq15==9999 & qtyh>0
	gen valh=qtyh*s8cq15
	replace valh=0 if valh==.	
	*drop if item>=99 & item<=101 /*construction wood, charcoal(wood)*/
	keep hid item_h valh
	*Give the same codes to purchased and home produced items (and consecutive to non-food codes)
    merge m:m item_h using  ..\dofiles\2map_purch_own, keep(3) nogen 
	keep hid item item_h valh 
	tempfile homeprod
	save `homeprod'
	
*Determining current main activity by household
. use "..\data\cs_S6B_Employement_6C_Salaried_S6D_Business.dta" 

. keep hhid clust province district ur region weight poverty quintile s6bq3b s6bq4b 
. rename hhid  hid 
. replace hid = hid - 100000
. numlabel, add
. gen ag=( s6bq4b==1)
. gen nonag=( s6bq4b >1)
. recode ag nonag (.=0)
. collapse (max)ag nonag ur, by(hid)
. gen agonly=(ag==1 & nonag==0) 
. gen nonagonly=(ag==0 & nonag==1)
. gen mixed=(ag==1 & nonag==1)
. gen nojob=(ag==0 & nonag==0)
*. drop if nonagonly == 1
	
merge 1:m hid using `homeprod' 
	
 
 replace nonagonly = 0 if nonagonly == 1 & ur == 2  & valh > 0 & item_h<85   
 
	keep hid item item_h valh nonagonly
	tempfile homeprod
	save `homeprod'	
	
	
	
*	In-kind consumption
	use  "..\data\cs_S9B_transfers_in", clear
    rename hhid hid
    replace hid = hid - 100000
	egen valk1 = rsum(s9bq10 s9bq12)
	collapse(sum) valk1, by(hid)  
	tempfile valk1
	save `valk1'

	* 	Employer provided benefits in kind (create item code=400, a corresponding sam code=300 was also created)
	use  "..\data\cs_S6B_Employement_6C_Salaried_S6D_Business", clear
	rename hhid hid
    replace hid = hid - 100000	
	gen valk2 = s6cq19a * 20 * 12 if s6cq19b == 1
	replace valk2 = s6cq19a * 52 if s6cq19b == 2
	replace valk2 = s6cq19a * 12 if s6cq19b == 3
	replace valk2 = s6cq19a if s6cq19b == 4
	collapse(sum) valk2, by(hid)  
	merge 1:1 hid using `valk1', nogen
	egen valk = rsum (valk1 valk2)
	gen item=400
	keep hid item valk
	tempfile valk
	save `valk'

	* Merge valp valh valk
	use  `purchase'
	merge m:m hid item using `homeprod'
	append using `valk'		
	*Total consumption (purchased + home + in-kind)
	*egen valt = rsum(valp valh valk)
	egen valt = rsum(valp valh)
*	Create temporary "$path0\working file
	*keep hid item valp valh valk valt	
	keep hid item valp valh valt	
	recode val* (.=0)
	save  "..\work\2temp_foods", replace	
	
*---Annual expenditures on semi-durable and durable goods (12 months recall period)
	use  "..\data\cs_S8A1_expenditure", clear
	rename hhid hid
    replace hid = hid - 100000
	rename s8a1q0 item
	rename s8a1q4 place
	*Consumption values 
	*Purchased consumption
	gen valp = s8a1q3
	*Exclude extension, construction already reported in section 5
	*drop if item==29 | item==30 
	*Total consumption 
	gen valt = valp
	*Recode bar/restaurant purchases
	replace item = 309 if place == 8 	
	*Create temporary "$path0\working file
	keep hid item valp valt		
	recode val* (.=0  )
	save  "..\work\2temp_durables", replace

*---Annual non-durables (30 day recall period)
	use  "..\data\cs_S8A2_expenditure", clear
	rename hhid hid
    replace hid = hid - 100000	
	rename s8a2q0 item
	replace item = 69 + item 
	rename s8a2q4 place
	*Consumption values 
	*Purchased consumption
	gen valp = s8a2q3*12
	*Total consumption 
	gen valt = valp
	*Recode bar/restaurant purchases
	replace item = 309 if place == 8 	
	*Create temporary "$path0\working file
	keep hid item valp valt	
	recode val* (.=0)
	save  "..\work\2temp_nondurables", replace
	
*---Other frequently made expenditure and frequently purchased services (since last enumerator's visit)
	use  "..\data\cs_S8A3_expenditure", clear
	rename hhid hid
    replace hid = hid - 100000	
	rename s8a3q0 item
	replace item = 124 + item 
	rename s8a3q14 place
	egen valp=rowtotal (s8a3q4 - s8a3q13)
	replace valp = valp * s8a3q2 if province==1
	replace valp = valp/20 * (365*s8a3q2/12) if province!=1 
	*Total consumption 
	gen valt = valp	
	*Recode bar/restaurant purchases
	replace item = 309 if place == 8 	
	*Create temporary "$path0\working file
	keep hid item valp valt	
	save  "..\work\2temp_other1", replace

*---Annual Expenditures on education, section 2
	use  "..\data\cs_S1_S2_S3_S4_S6A_S6E_Person", clear
	rename hhid hid 
    replace hid = hid - 100000
	egen valp = rowtotal(s4aq11a s4aq11b s4aq11c s4aq11d s4aq11e s4aq11f s4aq11g s4aq11h s4bq2)
    drop if  valp==0
	gen item = 500
	*Total consumption 
	gen valt = valp	
	*Create temporary "$path0\working file
	keep hid item valp valt
	save  "..\work\2temp_educ", replace
	
*---Annual expenditures on rent, section 5
	use  "..\data\cs_S0_S5_Household", clear
	rename hhid hid
    replace hid = hid - 100000
	gen valp = s5bq4a if s5bq4b == 3
	replace valp = s5bq4a*4 if s5bq4b == 2
	replace valp = s5bq4a*12 if s5bq4b == 1
	gen item =600
	*Total consumption 
	gen valt = valp	
	*Create temporary "$path0\working file
	keep hid item valp valt
	recode val* (.=0)
	save  "..\work\2temp_rent", replace

*---Annual imputed rent, section 5 
	use  "..\data\cs_S0_S5_Household", clear
	rename hhid hid
    replace hid = hid - 100000
	gen	valp = s5bq3a if s5bq3b == 3
	replace valp = s5bq3a*4 if s5bq3b == 2
	replace valp = s5bq3a*12 if s5bq3b == 1
	gen item= 600
	gen valt = valp 
	*Create temporary "$path0\working file
	keep hid item valp valt
	recode val* (.=0)
	save  "..\work\2temp_imputed_rent", replace

*--House extension, construction, section 5 
	use  "..\data\cs_S0_S5_Household", clear
	rename hhid hid
    replace hid = hid - 100000	
	gen valp1 = s5cq14 * 12 
	*egen valp = rsum (s5bq11 valp1)
	egen valp = rsum (valp1)
	gen item=700
	gen valt = valp 	
	*Create temporary "$path0\working file
	keep hid item valp valt	
	recode val* (.=0)
	save  "..\work\2temp_maintainance", replace

*---Annual expenditure on electric utility, section 5
	use  "..\data\cs_S0_S5_Household", clear
	rename hhid hid
    replace hid = hid - 100000
	gen valp = s5cq17*12 
	gen item= 800
	*Total consumption 
	gen valt = valp	
	*Create temporary "$path0\working file
	keep hid item valp valt	
	recode val* (.=0)
	save  "..\work\2temp_elec", replace

*---Annual expenditure on water utility, section 5
	use  "..\data\cs_S0_S5_Household", clear
	rename hhid hid
    replace hid = hid - 100000
	gen valp1 = s5cq9b/s5cq9a*12
	gen valp2 = s5cq11*52
	egen valp = rsum(valp1 valp2)
	gen item= 900
	*Total consumption 
	gen valt = valp	
	*Create temporary "$path0\working file
	keep hid item valp valt	
	save  "..\work\2temp_water", replace
	
*---Other expenditures
	use "..\data\cs_S9E_Other_Expenditure", clear
	rename hhid hid
    replace hid = hid - 100000
	rename s9eq1 item
	replace item =  item + 312
	gen valp = s9eq2
	*Total consumption 
	gen valt = valp	
	*Create temporary "$path0\working file
	keep hid item valp valt	
	save  "..\work\2temp_other2", replace

/*	

*---Transfer made to other households
	*Annual cash and food transfers received 
	use "$path0\data\cs_s9a_transfers_out", clear
	rename hhid hid
	gen item = 326
	egen valp=rsum(s9aq7 s9aq10 s9aq12 ) 
	gen valt = valp	
	keep hid item valp valt	
	save "$path0\work\2temp_other3", replace
*/

*---Master consumption file

*	Append temporary files
	use  "..\work\2temp_foods", clear         
	append using  "..\work\2temp_nondurables"
	append using  "..\work\2temp_durables"
	append using  "..\work\2temp_other1"
	append using  "..\work\2temp_educ"
	append using  "..\work\2temp_rent"
	append using "..\work\2temp_imputed_rent"
	append using  "..\work\2temp_maintainance"
	append using  "..\work\2temp_elec"
	append using  "..\work\2temp_water"
	append using  "..\work\2temp_other2"
	*append using  "$path0\work\2temp_other3"
	
*	Merge item code mapping to sam code 
	sort item
	merge m:m item using "..\dofiles\2mapcom_x104", keep(3) nogen
		
*	Scale values to millions
	replace valp = valp / 1000
	replace valh = valh / 1000
	*replace valk = valk / 1000
	replace valt = valt / 1000
	recode val* (.=0)
	
*	Label variables
	label var valp "value of purchases"
	label var valh "value of home produce"
	*label var valk "value of in-kind"
	label var valt "total value of consumption"
	label var item "item code"
	label var itemdesc "item code description"
	label var hid "household id"
	label var sam "sam code"
	label var samdesc "sam code description"

	sort item 
	save  "..\work\2consumption", replace

	*EAA
*use "..\work\2consumption"
*collapse (sum) valt, by(hid)
*rename valt cons1
*save "..\work\cons1", replace

*---Clean "$path0\working folder
	erase "..\work\2temp_foods.dta"
	erase "..\work\2temp_nondurables.dta"
	erase "..\work\2temp_durables.dta"
	erase "..\work\2temp_other1.dta"
	erase "..\work\2temp_educ.dta"
	erase "..\work\2temp_rent.dta"
	erase "..\work\2temp_imputed_rent.dta"
	erase "..\work\2temp_maintainance.dta"
	erase "..\work\2temp_elec.dta"
	erase "..\work\2temp_water.dta"
	erase "..\work\2temp_other2.dta"

