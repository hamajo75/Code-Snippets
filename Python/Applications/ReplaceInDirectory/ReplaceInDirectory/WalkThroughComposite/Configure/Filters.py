import re
   
####################### Filters ################################## 
def fileFilter(file_name, arguments):
    # do some kind of filtering, e.g. *.txt, *bla*.cpp
    # TextFilePattern = ".*(\.txt)$"
    TextFilePattern = ".*"
    
    if re.search(TextFilePattern, file_name):            
        return True
    else:
        return False

def getCopy(file_name, arguments):
    TextFilePattern = "(_ilcd)$"
    
    if re.search(TextFilePattern, file_name):
        return True
    else:
        return False

def HTMLFilter(file_name, arguments):
    TextFilePattern = "(\.htm)$"
    if re.search(TextFilePattern, file_name):            
        return True
    else:
        return False    

