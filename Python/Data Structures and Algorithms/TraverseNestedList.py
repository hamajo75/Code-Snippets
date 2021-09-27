""" This is a docstring of the module
(do: help(TraverseNestedList) in shell) """

def printAll(tree):
    """ This is a function docstring
    (do: help(TraverseNestedList.printAll) in shell) """
    if type(tree) not in [list, set, tuple]:
        print(tree)
        return
    for n in tree:
        printAll(n)

