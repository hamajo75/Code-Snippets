import os
import argparse

from WalkThroughComposite import WalkThroughComposite

#########################################################################
import itertools
def createDirectoryComposite(path, non_recursive=False):
    return_list = []
    for dir_path, dirs, files in os.walk(path, topdown = True):  
        for name in itertools.chain(files, dirs):
            full_path_name = os.path.join(dir_path, name);
            return_list.append(full_path_name)

        if non_recursive:
            break

    return return_list
   
#########################################################################
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
   literal = args.literal
   non_recursive = args.non_recursive

   if not os.path.exists(directory):
      sys.exit("Directory " + directory + " doesn't exit!")

   arguments = (csv_replace_file, literal)
      
   WalkThroughComposite.traverse(
                  createDirectoryComposite(directory, non_recursive), arguments) 

