@echo off
REM  Copyright (C) FineSoft 1998  Valery Fine (Faine)
rem
rem  Last correction:           Creation date:
rem      3/03/98                    3/03/98
rem  This batch file sets the user's Environamnet variables 
rem  and "Environment" registry entry to access the STAR software from
rem  Windows NT workstation
rem  ============================

set ECHO=
if not "%1"=="-v" goto skip
set ECHO=-v
shift
@echo on
:skip

if "%AFS_RHIC%".=="". set AFS_RHIC=\\sol\afs_rhic

echo REGEDIT4 >Env.reg
echo. >>Env.reg
echo [HKEY_CURRENT_USER\Environment]>>Env.reg
set StarDrive=s:
rem echo "StarDrive"="%%j">>Env.reg

rem Check the network connections
rem for /F " " %%i in ('net use') DO if "%%k".=="\\Sol\afs_rhic" set STAR_Drive=%%j
rem SET StarDrive=s:
rem net use %StarDrive% \\Sol\afs_rhic\star

set STAR_LEVEL=.dev
echo "STAR_LEVEL"="%STAR_LEVEL%">>Env.reg

set STAR_DIR=%StarDrive%\packages
echo "STAR_DIR"="%StarDrive%\\packages">>Env.reg

set GROUP_DIR=%AFS_RHIC%\star\group
echo "GROUP_DIR"="%AFS_RHIC%\\star\\group">>Env.reg
rem if "%STAR_SYS%".=="". if exist %GROUP_DIR%\STAR_SYS.bat call %GROUP_DIR%\STAR_SYS.bat
if exist %GROUP_DIR%\STAR_SYS.bat call %GROUP_DIR%\STAR_SYS.bat
if exist %GROUP_DIR%\group_env.bat call %GROUP_DIR%\group_env.bat %ECHO%
path %path%;%STAR%\mgr;%STAR%\bin