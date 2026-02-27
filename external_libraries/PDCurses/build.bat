@echo off
title My first batch script.
echo Changing directory to wincon
cd wincon/
echo Executing Visual Studio's X64 Native building Tools
"C:\ProgramData\Microsoft\Windows\Start Menu\Programs\Visual Studio 2022\Visual Studio Tools\VC\x64 Native Tools Command Prompt for VS 2022.lnk" & 
"nmake -f C:\users\anton\desktop\personal_projects\libraries\pdcurses\wincon\Makefile.vc PLATFORM=X64 DLL=Y"
echo Returning to Home directory
cd ..
rem cd "\"
rem dir
pause