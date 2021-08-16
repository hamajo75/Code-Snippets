####################### Workers ################################## 
def work(file_name):
    with open(file_name, "r") as f:
       try:
          content = f.read()
       except:
          print("Couldn't read file: " + file_name)

    with open(file_name, "w") as f:              
       try:
          f.write(change(content))
       except:
           print("Couldn't write file: " + file_name)

def change(content):
    modified_text = "changed: " + content
    return modified_text

def replace(fpath):                
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
