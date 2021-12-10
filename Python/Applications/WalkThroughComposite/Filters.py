import re
   
####################### Filters ################################## 
def fileFilter(file_name):
	return True


def getCopy(file_name):
    TextFilePattern = "(_ilcd)$"
    
    if re.search(TextFilePattern, file_name):
        return True
    else:
        return False



