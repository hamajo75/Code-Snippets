import csv
import re
import os

####################### Workers ################################## 
def replace(fpath, arguments):

    possibles = globals().copy()     # needed for getting the replace function from a string
    possibles.update(locals())

    if os.path.isdir(fpath):
        return

    print("Working on: " + fpath)

    csv_replace_file, literal = arguments
   
    # loop through csv-file entries
    csv_reader = csv.reader(filter(lambda row: row[0] != '#', open(csv_replace_file)))
                            
    for row in csv_reader:
        this = row[0]
        that = row[1]
        replace_method = row[2]
        file_filter = row[3]

        print("replacing '" + this + "' with '" + that +
              "' using method '" + replace_method +
              "' applying filter '" + file_filter + "'")

        replace_method = possibles.get(replace_method.strip())
        file_filter = possibles.get(file_filter.strip())

        with open(fpath, encoding="utf-8") as f:
            try:
                content = f.read()
            except:
                print("Couldn't read file: " + fpath)

        if replace_method:
            content = replace_method(content, this, that)
        else:
            if literal:
                content = content.replace(this, that)
            else:
                content = re.sub(this, that, content)

        with open(fpath, "w", encoding="utf-8") as f:
            try:
                f.write(content)
            except:
                print("Couldn't write file: " + fpath)

