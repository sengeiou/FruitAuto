@echo off
set /p commit=commit:
title auto commit
git.exe add -A
git.exe commit -m "%commit%"
 
git push origin main
call :ColorText 0C "-----------gitee push ok-----------"
git push github main
call :ColorText 0C "-----------github push ok-----------"

pause