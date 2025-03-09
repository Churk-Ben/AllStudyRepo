string = input()
replacements = {
    "||": "or",
    "&&": "and",
    "!": "not",
    "->": " or not",
    "<=>": "==",
}
for key, value in replacements.items():
    string = string.replace(key, value)
assignments = [
    {"p": "True", "q": "True"},
    {"p": "False", "q": "False"},
    {"p": "True", "q": "False"},
    {"p": "False", "q": "True"},
]
results = []
for assignment in assignments:
    string_use = string
    for key, value in assignment.items():
        string_use = string_use.replace(key, value)
    result = eval(string_use)
    results.append(result)
for i in results:
    print(i)
if all(results):
    print("重言式")
else:
    print("不是重言式")