from .Configure.Filters import *
from .Configure.Workers import replace

filters = [fileFilter]
worker = replace
#########################################################################
def traverse(composite, arguments):    
    for component in composite:
        work = filterThis(component, arguments)
        if work:
            work(component, arguments)

def filterThis(component, arguments):
    if DoWeWorkOn(component, arguments):
        return worker
    else:
        return None

def DoWeWorkOn(component, arguments):
    for thisFilter in filters:
        if thisFilter(component, arguments):            
            return True
        else:
            return False
