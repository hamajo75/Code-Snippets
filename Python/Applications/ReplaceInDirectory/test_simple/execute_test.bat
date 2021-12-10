@echo off

rem start /b /wait rmdir test /s /q
start /b /wait xcopy data_original data /s /e /y

python3 ../ReplaceInDirectory\replaceInDirectory.py data replace.csv
pause
