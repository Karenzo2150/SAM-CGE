* Labor classification
set more off

/* 
s4aq1: ever been to school
	1	Yes
	2	No

s4aq2: highest class succesfully attained in school
	*flab-n
	1	Pre-primary
	10	Not complete P1
	11	Primary 1
	12	Primary 2
	13	Primary 3
	14	Primary 4
	*flab-p
	15	Primary 5
	16	Primary 6,7,8
	21	Post primary 1
	22	Post primary 2
	23	Post primary 3
	24	Post primary 4
	25	Post primary 5
	31	Secondary 1
	32	Secondary 2
	33	Secondary 3
	*flab-s
	26	Post primary 6,7,8
	34	Secondary 4
	35	Secondary 5
	36	Secondary 6
	*flab-t
	41	University 1
	42	University 2
	43	University 3
	44	University 4
	45	University 5
	46	University 6
	47	University 7
	98	Don't Know
*/


*---Education by rural, urban, Kigali ---

	use "..\data\cs_S1_S2_S3_S4_S6A_S6E_Person", clear	
	rename hhid hid 
    replace hid = hid - 100000
	rename ur urban4
	merge m:1 hid using "..\work\1weights"
	drop _m
	
*	Education variable
	*Add to eligible list if someone has attended school
	gen     educ=1 if s4aq2<=14 | s4aq2 == 98 | s4aq1 == 2
	replace educ=2 if s4aq2>=15 & s4aq2<=33
	replace educ=3 if (s4aq2>=34 & s4aq2<=42) | s4aq2 == 26
	replace educ=4 if s4aq2>=41 & s4aq2<=47
	
	
	*replace educ=2 if (s4aq2>=16 & )   
	*replace educ=3 if (s4aq2>=20 & s4aq2<=36) 
	*replace educ=4 if (s4aq2>=40 & s4aq2<=47) 
	lab def educ 1 "No schooling" 2 "Primary" 3 "Secondary"	4 "Tertiary"              
	lab val educ educ
	drop if educ==.
	*table educ [iw=hw] if s1q3y >= 16, row col format(%12.1gc) 

*	Rural-urban variable	
	gen area = 0
	replace area = 3 if region == 1
	replace area = 2 if region == 2
	replace area = 1 if region >=3
	drop if area == .
	*table area [iw=hw], row col format(%12.1gc)		

	egen labclass = concat(area educ)
	destring labclass, replace
	label def labclass 11 "flab-rn" 12 "flab-rp" 13 "flab-rs" 14 "flab-rt" 21 "flab-un" 22 "flab-up" 23 "flab-us" 24 "flab-ut" 31 "flab-kn" 32 "flab-kp" 33 "flab-ks" 34 "flab-kt"
	label value labclass labclass
	*table labclass [iw=hw], row col format(%12.1gc)	
	
	sort hid pid
	save "..\work\4labclass", replace


	
	
	
	
	
exit
	tostring hid pid, generate(hid1 pid1)
	replace pid1 = "0" + pid1 if pid<10
	gen pid2 = hid1 + pid1
	destring pid2, generate(pid3)
	replace pid = pid3 + 0
	merge 1:1 pid using "..\data\current_main_activity6", nogen
	recode ISIC 9999.00=.
	keep if ISIC>=1 & ISIC<=21 & LFS16==1
	gen family = 0 
    replace family = 1 if s6aq2==1 & ISIC==1

	bysort urban4: tab ISIC family 
	tab region urban4
	
	gen labclass ="."
	replace labclass = "flab_ru" if  urban4==2 & educ==0
	replace labclass = "flab_rp" if  urban4==2 & educ==1
	replace labclass = "flab_rs" if  urban4==2 & educ==2
	replace labclass = "flab_rt" if  urban4==2 & educ==3

	replace labclass = "flab_uu"  if urban4==1 & educ==0 
	replace labclass = "flab_up"  if urban4==1 & educ==1 
	replace labclass = "flab_us"  if urban4==1 & educ==2 
	replace labclass = "flab_ut"  if urban4==1 & educ==3 
	
	
	
	/*
	table ISIC educ [iw=hw] if LFS16 == 1, format(%12.1gc)
	collapse (sum) hw, by(ISIC educ)
	drop if educ == .
	reshape wide hw, i(ISIC) j(educ)
	*/

	
	* drop 1 observation with labclass = . 
	drop if labclass == "."
	keep hid pid hw educ urban labclass
	order hid pid educ urban labclass
	sort hid pid
	save "..\work\4labclass", replace
	
	/*
	flab_1f	Labor - Rural remote- family
	flab_1s	Labor - Rural remote- skilled
	flab_1u	Labor - Rural remote- unskilled
	flab_2f	Labor - peri, semi, urban- family
	flab_2s	Labor - peri, semi, urban- unskilled
	flab_2u	Labor - peri, semi, urban- skilled
	flab_3s	Labor - Kigali - unskilled
	flab_3u	Labor - Kigali - skilled
    */
 

 *Employment numbers for CGE model
 
 	use "..\data\current_main_activity6", clear	
	rename hhid hid
	rename ISIC sector
	sort hid pid	
	merge m:m hid pid using "..\work\4labclass", keep(3) nogen
	merge m:m hid using "..\work\1weights", nogen keep(3) 
	collapse (sum) hw, by(sector labclass)
	reshape wide hw, i(sector) j(labclass) string
 
