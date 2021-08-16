import os
import re

def renamer(file_name):
    from_pattern = "_ilcd"
    to_pattern = "_javaino"
    m = re.search("(" + from_pattern + ")$", file_name)
    if m:
        print("Renaming file: " + file_name)
        # new_file_name = re.sub(m.group(0), "", file_name)
        # os.rename(new_file_name, new_file_name + to_pattern)        
        # os.rename(file_name, new_file_name)    
    else:
        to_pattern = "_ilcd"
        from_pattern = "_javaino"
        m = re.search("(" + from_pattern + ")$", file_name)
        if m:
            print("Renaming file: " + file_name)
            # new_file_name = re.sub(m.group(0), "", file_name)
            # os.rename(new_file_name, new_file_name + to_pattern)        
            # os.rename(file_name, new_file_name)    
