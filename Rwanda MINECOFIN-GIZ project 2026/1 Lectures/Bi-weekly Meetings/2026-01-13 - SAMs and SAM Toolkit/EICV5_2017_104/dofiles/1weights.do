	use "..\data\EICV5_Poverty_file", clear		
	rename ur urban
	rename weight hw
	rename pop_wt pw
	rename member hs
	keep hhid hw pw hs urban
	merge 1:1 hhid using "..\data\cs_s0_s5_household", nogen
	rename hhid hid
    replace hid = hid - 100000
    gen urban3 = ur
	keep hid hw pw hs urban urban3
	label var hw  "household weight"
	label var pw  "person weight"
	label var hs  "household size"
	label var hid "household identification"
	order hid hw pw hs
	sort hid
	save "..\work\1weights", replace	

