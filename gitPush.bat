@echo off
set /p commit=commit:
title auto commit
git.exe add -A
git.exe commit -m "%commit%"
 
git push origin main
color 02
echo "color 02" -----------gitee push ok-----------
git push github main
call :ColorStr 0C "-----------github push ok-----------"

pause