start /b /wait rm -r test
start /b /wait cp -r test_original test

..\replaceInDirectory.py test replace.csv
pause
