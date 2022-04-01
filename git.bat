@echo off
set /p commit=commit:
title auto commit
git.exe add -A
git.exe commit -m %commit%
 
git push origin master
git branch -u origin/master master
exit