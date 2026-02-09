PARAMETER CTRL_ERROR    UNDF if incorrect simulation or model selection or if one of more data files are missing;

*--- Part A: Check selections are within range ---

*Check A1: Choice of files to run (MODSIM)
$ifthene.modsim (%modsim%<1)or(%modsim%>3)
DISPLAY "MODSIM = %modsim%  |  Choice is out of range (select 1 2 or 3 in control file)", "1 = Base model", "2 = Simulations and standard reporting", "3 = Simulation with user-defined reporting";
CTRL_ERROR = 1/0;
$exit
$endif.modsim

*Check A2: Choice of model to run (STATDYN)
$ifthene.statdyn (%statdyn%<1)or(%statdyn%>2)
DISPLAY "STATDYN = %statdyn%  |  Choice is out of range (select 1 or 2 in control file)", "1 = Run static model", "2 = Run dynamic model";
CTRL_ERROR = 1/0;
$exit
$endif.statdyn

*--- Part B: Check if data files exist ---

*Check B1: If base model Excel file does not exist (basemod)
$ifthen.data not exist data\\%folder%\basemod%dataext%.xlsx
DISPLAY "FOLDER = %folder% EXTENSION = %dataext%  |  Base model file does not exist", "Check files in data subfolder:", "  basemod%dataext%.xlsx";
CTRL_ERROR = 1/0;
$exit
$endif.data

*Check B2: If running simulations (not just base model)...
$ifthene.modsim (%modsim%=2)or(%modsim%=3)
*---
*  If running static simulations...
$ifthen.statdyn %statdyn%==1
*    If static simulation file does not exist (statsim)
$ifthen.simdata not exist data\\%folder%\statsim%dataext%.xlsx 
DISPLAY "FOLDER = %folder% EXTENSION = %dataext%  |  Static model files are missing", "Check files in data subfolder:", "  statsim%dataext%.xlsx", "  statrep%dataext%.xlsx";
CTRL_ERROR = 1/0;  
$exit
$endif.simdata
*    If static reporting file does not exist (statrep)
$ifthen.repdata not exist data\\%folder%\statrep%dataext%.xlsx
DISPLAY "FOLDER = %folder% EXTENSION = %dataext%  |  Static model files are missing", "Check files in data subfolder:", "  statsim%dataext%.xlsx", "  statrep%dataext%.xlsx";
CTRL_ERROR = 1/0;
$exit
$endif.repdata
$endif.statdyn
*---
*  If running dynamic simulations...
$ifthen.statdyn %statdyn%==2
*    If dynamic simulation file does not exist (statsim)
$ifthen.simdata not exist data\\%folder%\dynsim%dataext%.xlsx
DISPLAY "FOLDER = %folder% EXTENSION = %dataext%  |  Dynamic model files are missing", "Check files in data subfolder:", "  dynsim%dataext%.xlsx", "  dynrep%dataext%.xlsx";
CTRL_ERROR = 1/0;
$exit
$endif.simdata
*    If dynamic reporting file does not exist (statrep)
$ifthen.repdata not exist data\\%folder%\dynrep%dataext%.xlsx
DISPLAY "FOLDER = %folder% EXTENSION = %dataext%  |  Dynamic model files are missing", "Check files in data subfolder:", "  dynsim%dataext%.xlsx", "  dynrep%dataext%.xlsx";
CTRL_ERROR = 1/0;
$exit
$endif.repdata
$endif.statdyn
*---
$endif.modsim