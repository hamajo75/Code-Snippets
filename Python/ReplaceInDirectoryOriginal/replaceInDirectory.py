import os
import csv
import sys
import argparse
import re

from replace_functions import *

# this is executed only when the file is run (not when its imported)
if __name__ == "__main__":

   # set up argument parsing
   parser = argparse.ArgumentParser(description = "Perform multiple replacements in "
                               "a directory according to CSV file. By default the entries "
                               "in the csv-file are interpreted as regular expressions and "
                               "the replacements are done recursively.")

   parser.add_argument("directory", help = "DIRECTORY where to do replacements")
   parser.add_argument("csv_file", help = "CSV-file specifying the replacements")
   #parser.add_argument("-i", "--include", help = "use include list file", action="store_true")
   #parser.add_argument("-e", "--exclude", help = "use exclude list file", action="store_true")
   parser.add_argument("-l", "--literal", help = "don't use regular expressions", action="store_true")
   parser.add_argument("-nr", "--non_recursive", help = "non recursive replace", action="store_true")

   # get arguments
   args = parser.parse_args()
   #include_file = args.include
   #exclude_file = args.exclude
   directory = args.directory
   csv_replace_file = args.csv_file
   literate = args.literate
   non_recursive = args.non_recursive

   possibles = globals().copy()
   possibles.update(locals())

   # loop through include file lines
   #for entry in include_file:

   if not os.path.exists(directory):
      sys.exit("Directory " + directory + " doesn't exit!")

   # loop through directories in "directory" recursively
   for dir_name, dirs, files in os.walk(directory, topdown = True):
      # loop through files in directories
      for file_name in files:
         print("Applying changes to \"" + file_name + "\"")

         # loop through csv-file entries
         reader = csv.reader(open(csv_replace_file))
         for row in reader:
            this = row[0]
            that = row[1]
            using_method = row[2]
            replace_method = possibles.get(using_method.strip())

            print("replacing '" + this + "' with '" + that +
                  "' using method '" + using_method + "'")

            fpath = os.path.join(dir_name, file_name)
            with open(fpath) as f:
               try:
                  content = f.read()
               except:
                  print("Couldn't read file: " + fpath)

               if replace_method:
                  content = replace_method(content, this, that)
               else:
                  if literate:
                     content = content.replace(this, that)
                  else:
                     content = re.sub(this, that, content)

            with open(fpath, "w") as f:
               try:
                  f.write(content)
               except:
                   print("Couldn't write file: " + fpath)

      if non_recursive:
         break
