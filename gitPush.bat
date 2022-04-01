@echo off
set /p commit=commit:
title auto commit
git.exe add -A
git.exe commit -m "%commit%"
 
git push origin main
:start
echo.
call :ColorText 0C "-----------gitee push ok-----------"
echo.
git push github main
call :ColorText 0C "-----------github push ok-----------"
goto :eof
pause


:ColorText
echo off
<nul set /p ".=%DEL%" > "%~2"
findstr /v /a:%1 /R "^$" "%~2" nul
del "%~2" > nul 2>&1
goto :eof