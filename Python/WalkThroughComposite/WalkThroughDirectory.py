import os
import itertools

import WalkThroughComposite

root_dir = "JavaLib"
#########################################################################
def createDirectoryComposite(path):
    return_list = []
    for dir_path, dirs, files in os.walk(path, topdown = True):  
        for name in itertools.chain(files, dirs):
            full_path_name = os.path.join(dir_path, name);
            return_list.append(full_path_name)

    return return_list

#########################################################################
if __name__ == "__main__":
	print("Walk through directory: " + root_dir)
	WalkThroughComposite.traverse(createDirectoryComposite(root_dir))


'''
What can you do in a directory?
- modify file contents
- modify file/directory names
- extract information from files
'''
