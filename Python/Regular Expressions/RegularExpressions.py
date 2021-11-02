import re

def basic():
    # getting mathes
    m = re.search("aa", "aabcd")
    m.group(0)

    # substitution
    re.sub("a", "b", "aaccdd")

def camel_case_split(str):
    matches = re.finditer(
        '.+?(?:(?<=[a-z])(?=[A-Z])|(?<=[A-Z])(?=[A-Z][a-z])|$)', str)
    return [m.group(0) for m in matches]

def camel_case_2_snake_case(str):
    ret = ""
    for part in camel_case_split(str):
        ret = ret + part.lower() + "_"
    if ret[-1] == "_":
        ret = ret[0:-1]
    return ret

if __name__ == "__main__":
    basic()
    print(camel_case_2_snake_case("myFunnyDataType"))
