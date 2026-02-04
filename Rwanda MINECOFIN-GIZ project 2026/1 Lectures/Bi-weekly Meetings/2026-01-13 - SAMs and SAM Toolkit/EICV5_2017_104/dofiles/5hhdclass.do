	*** Farm size
	use  "..\data\cs_s7c_parcels", clear
	rename hhid hid
    replace hid = hid -100000
	collapse (sum) s7cq4,by(hid)
	rename s7cq4 cult_area
	replace cult_area=cult_area/100
	gen fsize = 1 if cult_area <= 0.35
	replace fsize = 2 if cult_area > 0.35
	tempfile farm_size
	save `farm_size'
	
	*** Farm/Mixed/Nonfarm 
	*   ISIC definiton  	
	*   4 hhd types 

	use "..\data\cs_s1_s2_s3_s4_s6a_s6e_person", clear
	rename hhid hid
    replace hid = hid -100000
	codebook hid //14419
	*fsum weight,s(sum) f(%14.0f) //11.4 million population
	
	*merge current employment
	tostring hid pid, generate(hid1 pid1)
	replace pid1 = "0" + pid1 if pid<10
	gen pid2 = hid1 + pid1
	destring pid2, generate(pid3)
	replace pid = pid3 + 0  
  
    tempfile tempxx
    save `tempxx' 
  
  
*Determining current main activity by household
   use "..\data\cs_S6B_Employement_6C_Salaried_S6D_Business", clear
   keep hhid pid clust province district ur region weight poverty quintile s6bq3b s6bq4b 
   rename hhid  hid 
   replace hid = hid -100000

   tostring hid pid, generate(hid1 pid1)
   replace pid1 = "0" + pid1 if pid<10
   gen pid2 = hid1 + pid1
   destring pid2, generate(pid3)
   replace pid = pid3 + 0 
 
   numlabel, add
   gen ag=( s6bq4b==1)
   gen nonag=( s6bq4b >1)
   recode ag nonag (.=0)
*   collapse (max)ag nonag pid, by(hid)
    collapse (max)ag nonag pid, by(hid clust province district ur region weight poverty quintile)
   gen agonly=(ag==1 & nonag==0) 
   gen nonagonly=(ag==0 & nonag==1)
   gen mixed=(ag==1 & nonag==1)
   gen nojob=(ag==0 & nonag==0)
   
 
merge m:m hid using "..\work\2consumption"
merge m:m hid using ..\work\1weights, nogen
drop _m	

   replace nonagonly = 0 if region > 1 & ur == 2  & valh > 0 & sam <30  
  
   merge m:m pid using `tempxx'	
   drop _m	

 . collapse (sum) valh valt valp, by (hid hw pw quint  ag nonag agonly nonagonly mixed nojob ur region)
 . drop if hw ==.
   
	gen  	hhdtype = 0
	replace hhdtype = 1 if agonly == 1
	replace hhdtype = 2 if nonagonly == 1
	replace hhdtype = 3 if mixed == 1
	replace hhdtype = 4 if nojob == 1

	tempfile rural_farm
	save `rural_farm'


*	Per capita consumption
	use ..\work\2consumption, clear
	collapse (sum) valh valp valt, by(hid)
	save ..\work\hcons, replace
	
	
	
*	Quintile and rural/urban variables
	use "..\data\EICV5_poverty_file", clear
	rename hhid hid	
	sort hid
    replace hid = hid -100000
	merge m:m hid using ..\work\1weights, nogen	
	
	merge m:m hid using ..\work\hcons, nogen 
	*Per capita consumption expenditure
	*gen pcexp = cons1 / member
	*gen pcexp = cons1 / hs
	gen pcexp = (valh+valp) / hs
	xtile quint=pcexp [w=pop_wt], nq(5)
	*table quint [iw=pop_wt], row col format(%12.1gc)
	
*	Rural-urban variable	
	gen area = 0
	replace area = 3 if region == 1
	replace area = 2 if region == 2
	replace area = 1 if region >=3
	drop if area == .
	*table area [iw=pop_wt], row col format(%12.1gc)		

*	Final household classification
	keep hid quint area weight pop_wt pcexp
	merge m:m hid using `rural_farm', nogen keep(3)
	gen farm = 2 if nonagonly == 1
	recode farm (.=1)
	
	*If urban then drop farm variables
	replace farm = 2 if area > 1
 
 
	egen hhdclass0 = concat(area quint) 
	destring hhdclass0, replace
	label def hhdclass0 11 "hhd_r1" 12 "hhd_r2" 13 "hhd_r3" 14 "hhd_r4" 15 "hhd_r5" 21 "hhd_u1" 22 "hhd_u2" 23 "hhd_u3" 24 "hhd_u4" 25 "hhd_u5" 31 "hhd_k1" 32 "hhd_k2" 33 "hhd_k3" 34 "hhd_k4" 35 "hhd_k5"
	*label def hhdclass0 111 "hhd_f1" 112 "hhd_f2" 113 "hhd_f3" 114 "hhd_f4" 115 "hhd_f5" 121 "hhd_n1" 122 "hhd_n2" 123 "hhd_n3" 124 "hhd_n4" 125 "hhd_n5" 221 "hhd_u1" 222 "hhd_u2" 223 "hhd_u3" 224 "hhd_u4" 225 "hhd_u5" 321 "hhd_k1" 322 "hhd_k2" 323 "hhd_k3" 324 "hhd_k4" 325 "hhd_k5"

	label value hhdclass0 hhdclass0	
	*table hhdclass0 [iw=pop_wt], row col format(%12.1gc)		
	
	sort hid
	save ..\work\5hhdclass, replace
	
