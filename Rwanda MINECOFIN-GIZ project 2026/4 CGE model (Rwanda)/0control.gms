$TITLE IFPRI Standard CGE Model Version 2.0

*------------------------------------------------------------------
*Select model and data
*------------------------------------------------------------------

*Run which model?
$setglobal statdyn  1
*   1 = Static model
*   2 = Dynamic model


*Run which files?
$setglobal modsim   2
*   1 = Base year model only
*   2 = Simulations with standard reporting
*   3 = Simulation with user-defined reporting 


*Country data folder and files
$setglobal folder   rwa_2017
*   Subfolder within the data folder that contains the country data Excel Files
*   Excel files should include: basemod, statsim, statrep, dynsim, dynrep
$setglobal dataext  _rwa2017
*   Excel file name extension added to all data files in the country data subfolder (e.g., "basemod_xx" where "_xx" is the value of dataext)


*--------------------------------------------------------------
* Check selections and data files
*--------------------------------------------------------------

$include includes\control_checks.inc


*--------------------------------------------------------------
* Run selections
*--------------------------------------------------------------

*MODSIM = 1: Run base model (without any simulations)
$if %modsim%==1 $include 1model_base.gms


*MODSIM = 2: Run simulations and export standard results (also run base model if missing)
$ifthen.modsim %modsim%==2
*  Run base model (always)
$include 1model_base.gms
***  Run static model (if modsim = 1)
*  Run static model (if statdyn = 1)

$ifthen.statdyn %statdyn%==1
$include 2simulation_stat.gms
$endif.statdyn
****  Run dynamic model (if modsim = 2)
*  Run dynamic model (if statdyn = 2)
$ifthen.statdyn %statdyn%==2
$include 2simulation_dyn.gms
$endif.statdyn
*  End MODSIM = 2
$endif.modsim


*MODSIM = 3: Run simulations, export standard results, and run extended reporting (also run base model if missing)
$ifthen.modsim %modsim%==3
*  Run base model (always)
$include 1model_base.gms
***  Run static model and extended reporting (if modsim = 1)
*  Run static model and extended reporting (if statdyn = 1)
$ifthen.statdyn %statdyn%==1
$include 2simulation_stat.gms
$include 3report_stat.gms
$endif.statdyn
***  Run dynamic model and extended reporting (if modsim = 2)
*  Run dynamic model and extended reporting (if statdyn = 2)
$ifthen.statdyn %statdyn%==2
$include 2simulation_dyn.gms
$include 3report_dyn.gms
$endif.statdyn
*  End MODSIM = 3
$endif.modsim


