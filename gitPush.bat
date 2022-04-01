@echo off
set /p commit=commit:
title auto commit
git.exe add -A
git.exe commit -m "%commit%"
 
git push origin main
echo.
echo -----------gitee push ok-----------
echo.

git push github main
echo.
echo -----------github push ok-----------
echo.

pause