import json

""" Conversion
Python	JSON
dict	  object
list,   tuple	array
str	s   tring
int,    long, float	number
True	  true
False	  false
None	  null
"""

# serialization
data = {
  "president": {
      "name": "Zaphod Beeblebrox",
      "species": "Betelgeusian"
  }
}

with open("data_file.json", "w") as write_file:
  json.dump(data, write_file)

json_string = json.dumps(data)
print(json_string)

# deserialization
with open("data_file.json", "r") as read_file:
  data = json.load(read_file)
print(data["president"])

fpath = "file.json"
with open(fpath, encoding="utf-8") as f:
  try:
      content = f.read()
  except:
      print("Couldn't read file: " + fpath)

object = json.loads(content)
print(json.dumps(object))
