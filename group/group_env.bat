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
subst w: %STAR_PATH%
w:


if NOT "%STAR_LEVEL%".=="". goto :SetStar
set STAR_LEVEL=dev
echo "STAR_LEVEL"="%STAR_LEVEL%">>Env.reg

rem setenv STAR_VERSION

:SetStar
rem set STAR=%STAR_PATH%\%STAR_LEVEL%
set STAR=w:\%STAR_LEVEL%
echo "STAR"="%AFS_RHIC%\\star\\packages\\%STAR_LEVEL%">>Env.reg
					       if DEFINED ECHO echo   "Setting up STAR      = %STAR%

set STAR_MGR=%STAR%\mgr
echo "STAR_MGR"="%AFS_RHIC%\\star\\packages\\%STAR_LEVEL%\\mgr">>Env.reg

set STAR_LIB=%STAR%\lib\%STAR_HOST_SYS%
echo "STAR_LIB"="%AFS_RHIC%\\star\\packages\\%STAR_LEVEL%\\lib\\%STAR_HOST_SYS%">>Env.reg
					     if DEFINED ECHO @echo   Setting up STAR_LIB  = %STAR_LIB%
set STAR_BIN=%STAR%\bin\%STAR_HOST_SYS%
echo "STAR_BIN"="%AFS_RHIC%\\star\\packages\\%STAR_LEVEL%\\bin\\%STAR_HOST_SYS%">>Env.reg
                                             if DEFINED ECHO @echo   Setting up STAR_BIN  = %STAR_BIN%
set STAR_PAMS=%STAR%\pams
echo "STAR_PAMS"="%AFS_RHIC%\\star\\packages\\%STAR_LEVEL%\\pams">>Env.reg
                                             if DEFINED ECHO @echo   Setting up STAR_PAMS = %STAR_PAMS%
set STAR_DATA=%STAR_ROOT%\data
echo "STAR_DATA"="%AFS_RHIC%\\star\\data">>Env.reg
                                             if DEFINED ECHO @echo    Setting up STAR_DATA = %STAR_DATA%
set STAR_CALB=%STAR_ROOT%\calb
echo "STAR_CALB"="%AFS_RHIC%\\star\\calb">>Env.reg
                                             if DEFINED ECHO @echo    Setting up STAR_CALB = %STAR_CALB%
set CVSROOT=%STAR_ROOT%\repository
echo "CVSROOT"="%AFS_RHIC%\\star\\packages\\repository">>Env.reg
                                             if DEFINED ECHO @echo   Setting up CVSROOT   = %CVSROOT%

set CERN_LEVEL=98a
echo "CERN_LEVEL"="98a">>Env.reg
                                             if DEFINED ECHO @echo   Setting up  CERN_LEVEL   = %CERN_LEVEL%

set CERN_ROOT=\\hepburn\common\p32\cern
echo "CERN_ROOT"="\\\\hepburn\\common\\p32\\cern">>Env.reg
                                             if DEFINED ECHO @echo   Setting up  CERN_ROOT   = %CERN_ROOT%
set include=%STAR%\inc;%CERN_ROOT%\include;%include%
set lib=%CERN_ROOT%\lib;%lib%

set SunRPC=\\hepburn\common\p32\Staf\SunRPC
echo "SunRPC"="\\\\hepburn\\common\\p32\\Staf\\SunRPC">>Env.reg
                                             if DEFINED ECHO @echo   Setting up  SunRPC   = %SunRPC%
set include=%SunRPC%;%include%
set ROOT_LEVEL=2.13
if "%STAR_LEVEL%" == "dev" set ROOT_LEVEL=2.20
set ROOTSYS=%AFS_RHIC%\star\ROOT\%ROOT_LEVEL%\.intel_wnt\root
path %STAR_PATH%\.%STAR_SYS%\gnu\bin;%path%;%ROOTSYS%\bin
set ECHO=
rem alias makes "make -f $STAR/mgr/Makefile"



