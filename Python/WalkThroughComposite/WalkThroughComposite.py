from Filters import *
from Workers import *
import DemmelWorkers

filters = [fileFilter]
worker = DemmelWorkers.renamer
#########################################################################
def traverse(composite):
	print("traverse")
	for component in composite:
		work = filterThis(component)
		if work:
			work(component)

def filterThis(component):
    if DoWeWorkOn(component):
        return worker
    else:
        return None

def DoWeWorkOn(component):
    for thisFilter in filters:
        if thisFilter(component):            
            return True
        else:
            return False
