rem #	File:		group_env.bat
rem #	Purpose:	STAR group Windows NT env setup 
rem #	Author:		F.Fine (Faine)     BNL
rem #	Date:		03 Mar. 1998
rem #------------------------------------------------------------------#
rem # This script will set up the STAR enviroment.                     #
rem #------------------------------------------------------------------#
set ECHO=
if not "%1"=="-v" goto skip
set ECHO=-v
shift
@echo on
:skip
pause

IF DEFINED ECHO type %AFS_RHIC%\star\group\small-logo 

set STAR_ROOT=%AFS_RHIC%\star
echo "STAR_ROOT"="%AFS_RHIC%\\star">>Env.reg
rem                                          IF DEFINED ECHO echo   "Setting up STAR_ROOT = %STAR_ROOT%         

rem	                                     IF DEFINED ECHO type  %STAR_ROOT%\login\logo 
rem # Defined in CORE

if NOT "%GROUP_PATH%".=="". goto GroupDir
set GROUP_PATH=%STAR_ROOT%\star
echo "GROUP_PATH"="%AFS_RHIC%\\star\\group">>Env.reg)

rem # Defined by HEPiX
:GroupDir
if NOT "%GROUP_DIR%".=="". goto :StarPath
set GROUP_DIR=%STAR_ROOT%\group
echo "GROUP_DIR"="%AFS_RHIC%\\star\\group">>Env.reg

if DEFINED ECHO if exist %GROUP_DIR%\logo type %GROUP_DIR%\logo  

:StarPath
set STAR_PATH=%STAR_ROOT%\packages
echo "STAR_PATH"="%AFS_RHIC%\\star\\packages">>Env.reg
	  				      IF DEFINED ECHO echo   Setting up STAR_PATH = %STAR_PATH%       


if NOT "%LEVEL_STAR%".=="". goto :SetStar
set LEVEL_STAR=dev
echo "LEVEL_STAR"="%LEVEL_STAR%">>Env.reg

rem setenv VERSION_STAR

:SetStar
set STAR=%STAR_ROOT%\packages\%LEVEL_STAR%
echo "STAR"="%AFS_RHIC%\\star\\packages\\%LEVEL_STAR%">>Env.reg
					       if DEFINED ECHO echo   "Setting up STAR      = %STAR%

set STAR_MGR=%STAR%\mgr
echo "STAR_MGR"="%AFS_RHIC%\\star\\packages\\%LEVEL_STAR%\\mgr">>Env.reg

if "%SYS_STAR%".=="". call %STAR_MGR%\SYS_STAR.bat

set LIB_STAR=%STAR%\lib\%SYS_HOST_STAR%
echo "LIB_STAR"="%AFS_RHIC%\\star\\packages\\%LEVEL_STAR%\\lib\\%SYS_HOST_STAR%">>Env.reg
					     if DEFINED ECHO echo   Setting up LIB_STAR  = %LIB_STAR%
set BIN_STAR=%STAR%\bin\%SYS_HOST_STAR%
echo "BIN_STAR"="%AFS_RHIC%\\star\\packages\\%LEVEL_STAR%\\bin\\%SYS_HOST_STAR%">>Env.reg
                                             if DEFINED ECHO echo   Setting up BIN_STAR  = %BIN_STAR%
set PAMS_STAR=%STAR%\pams
echo "PAMS_STAR"="%AFS_RHIC%\\star\\packages\\%LEVEL_STAR%\\pams">>Env.reg
                                             if DEFINED ECHO echo   Setting up PAMS_STAR = %PAMS_STAR%
set STAR_DATA=%STAR_ROOT%\data
echo "STAR_DATA"="%AFS_RHIC%\\star\\data">>Env.reg
                                             if DEFINED ECHO echo    Setting up STAR_DATA = %STAR_DATA%
set STAR_CALB=%STAR_ROOT%\calb
echo "STAR_CALB"="%AFS_RHIC%\\star\\calb">>Env.reg
                                             if DEFINED ECHO  echo    Setting up STAR_CALB = %STAR_CALB%
set CVSROOT=%STAR_ROOT%\repository
echo "CVSROOT"="%AFS_RHIC%\\star\\packages\\repository">>Env.reg
                                             if DEFINED ECHO echo   Setting up CVSROOT   = %CVSROOT%



rem====== to define the compiler options
rem if ( -e $STAR/mgr/init_star.csh) source $STAR/mgr/init_star.csh
rem =======

set ECHO=
rem alias makes "make -f $STAR/mgr/Makefile"



