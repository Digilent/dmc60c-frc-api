@echo off
echo 8888888b. 888b     d888 .d8888b.  .d8888b.  .d8888b.  .d8888b.           d88888888888b.8888888
echo 888  "Y88b8888b   d8888d88P  Y88bd88P  Y88bd88P  Y88bd88P  Y88b         d88888888   Y88b 888  
echo 888    88888888b.d88888888    888888       888    888888    888        d88P888888    888 888  
echo 888    888888Y88888P888888       888d888b. 888    888888              d88P 888888   d88P 888  
echo 888    888888 Y888P 888888       888P "Y88b888    888888             d88P  8888888888P"  888  
echo 888    888888  Y8P  888888    888888    888888    888888    888     d88P   888888        888  
echo 888  .d88P888   "   888Y88b  d88PY88b  d88PY88b  d88PY88b  d88P    d8888888888888        888  
echo 8888888P" 888       888 "Y8888P"  "Y8888P"  "Y8888P"  "Y8888P"    d88P     888888      8888888
echo ------------------------------------------------------------------------
echo 1 = Setup using roboRIO IP Address
echo 2 = Setup using FRC Team Number
echo 3 = Only copy local files (VendorDeps ^& Labview VI Lib)
set USER=admin
:PROMPT
set /p SETUP="Select Setup Option:"
echo "%SETUP%"
if "%SETUP%"=="1" goto IP
if "%SETUP%"=="2" goto TEAM
if "%SETUP%"=="3" goto LOCAL
echo Invalid selection, please enter 1,2, or 3.
goto :PROMPT
:TEAM
set /p TEAMNUM="Enter FRC Team Number:"
set IPADDR=roborio-%TEAMNUM%-FRC.local
goto :GETUSER
:IP
set /p IPADDR="Enter roboRIO's IP Address:"
:GETUSER
set /p USER="Enter username(or press enter for default):"
set return=:START
goto :GetPassword
:START
if "!Password!"=="" (set PASSOPT=
) ELSE (
set PASSOPT=-pw !Password!
)
.\Install\pscp.exe %PASSOPT% -r "Install\dmc60c-config-utility-release" %USER%@%IPADDR%:/home/admin
if %ERRORLEVEL% NEQ 0 exit
.\Install\pscp.exe %PASSOPT% -r "Install\Labview\so\libDMC60CDriver.so" %USER%@%IPADDR%:/usr/local/frc/third-party/lib
.\Install\pscp.exe %PASSOPT% -r "Install\Labview\so\libwpi*" %USER%@%IPADDR%:/usr/lib
.\Install\plink.exe -batch -l %USER% %PASSOPT% %IPADDR% chmod +x /home/admin/dmc60c-config-utility-release/install.sh
.\Install\plink.exe -batch -l %USER% %PASSOPT% %IPADDR% chmod +x /home/admin/dmc60c-config-utility-release/uninstall.sh
.\Install\plink.exe -batch -l %USER% %PASSOPT% %IPADDR% /home/admin/dmc60c-config-utility-release/install.sh

:LOCAL
XCOPY /I /Y "Install\*DMC60C.json" "%PUBLIC%\frc2019\vendordeps"
XCOPY /I /Y /E "Install\maven\*" "%PUBLIC%\frc2019\maven"
cmd /C "%PUBLIC%\frc2019\maven\MavenMetaDataFixer.bat"
set KEY_NAME="HKLM\SOFTWARE\WOW6432Node\National Instruments\LabVIEW\18.0"
set VALUE_NAME=Path
FOR /F "usebackq tokens=3*" %%A IN (`REG QUERY %KEY_NAME% /v %VALUE_NAME% 2^>nul`) DO (
	set LVdir=%%A %%B
)
if defined LVdir (
	XCOPY /S /Y "Install\LabVIEW\lvlib\*" "%LVdir%\vi.lib\Rock Robotics\WPI\ThirdParty\TopLevel"
	XCOPY /S /Y "Examples\LabVIEW\*" "%LVdir%\examples"
) else (
	@echo Labview installation not found.
)
set /p done="Press enter to close..."
exit

:GetPassword
::Code by Carlos on AMBNT 2013-03-10
SetLocal DisableDelayedExpansion
Echo Enter your password for %USER% below (or press enter for default):
   Set "Password="
   Rem Save 0x08 character in BS variable
   For /F %%# In (
   '"Prompt;$H&For %%# in (1) Do Rem"'
   ) Do Set "BS=%%#"
   
   :HILoop
   Set "Key="
   For /F "delims=" %%# In (
   'Xcopy /W "%~f0" "%~f0" 2^>Nul'
   ) Do If Not Defined Key Set "Key=%%#"
   Set "Key=%Key:~-1%"
   SetLocal EnableDelayedExpansion
   If Not Defined Key Goto :HIEnd 
   If %BS%==^%Key% (Set /P "=%BS% %BS%" <Nul
   Set "Key="
   If Defined Password Set "Password=!Password:~0,-1!"
   ) Else Set /P "=*" <Nul
   If Not Defined Password (EndLocal &Set "Password=%Key%"
   ) Else For /F delims^=^ eol^= %%# In (
   "!Password!") Do EndLocal &Set "Password=%%#%Key%" 
   Goto :HILoop
   
   :HIEnd
echo.
Goto %return%