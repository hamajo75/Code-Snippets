import re

# getting mathes
m = re.search("aa","aabcd")
m.group(0)

# substitution
re.sub("a", "b", "aaccdd")
