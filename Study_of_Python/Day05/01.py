from sympy.parsing.sympy_parser import parse_expr
from sympy.logic.boolalg import Equivalent, Implies
from sympy import SympifyError

def is_tautology(formula_str):
    # 替换常见的逻辑符号为SymPy可识别的形式
    replacements = {
        '→': '>>',
        '->': '>>',
        '∧': '&',
        '∨': '|',
        '¬': '~',
        '↔': 'Equivalent',
        '<->': 'Equivalent',
        '~': '~',
        '&&': '&',
        '||': '|'
    }
    
    # 执行替换
    formula = formula_str
    for old, new in replacements.items():
        formula = formula.replace(old, new)
    
    try:
        # 解析逻辑表达式
        expr = parse_expr(
            formula,
            evaluate=False,
            local_dict={'Equivalent': Equivalent, 'Implies': Implies}
        )
        # 判断是否为重言式
        return expr.is_tautology()
    except SympifyError:
        raise ValueError("错误：输入的命题公式无效，请检查语法。")

if __name__ == "__main__":
    formula = input("请输入命题公式（可使用→, ->, ∧, &, ∨, |, ¬, ~, ↔, <->等符号）: ")
    try:
        result = is_tautology(formula)
        print("该公式是重言式。" if result else "该公式不是重言式。")
    except ValueError as e:
        print(e)