from sympy import symbols, And, Or, Not, Implies, Equivalent, satisfiable


def is_tautology(expression_str: str):
    replacements = {
        "<->": "==",
        "->": ">>",
        "&&": "&",
        "||": "|",
        "∧": "&",
        "∨": "|",
        "¬": "~",
        "!": "~",
    }
    for old, new in replacements.items():
        expression_str = expression_str.replace(old, new)
    variables = set(expression_str) & set("PQRpqr")
    symbols_set = symbols(variables)
    expression = eval(
        expression_str,
        {
            "And": And,
            "Or": Or,
            "Not": Not,
            "Implies": Implies,
            "Equivalent": Equivalent,
        },
        dict(zip(variables, symbols_set)),
    )
    return not satisfiable(Not(expression))


print("使用&&、||、->、¬、!、~等表示逻辑符号,输入exit退出")
input_expression = input("输入命题公式:\n")
print(("" if is_tautology(input_expression) else "不") + "是重言式")