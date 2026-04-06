#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool IsLeft(char c)
{
    return c == '(' || c == '[' || c == '{';
}

bool IsRight(char c)
{
    return c == ')' || c == ']' || c == '}';
}

bool Match(char left, char right)
{
    if (left == '(' && right == ')')
        return true;
    if (left == '[' && right == ']')
        return true;
    if (left == '{' && right == '}')
        return true;
    return false;
}

void CheckParenthesis(const string &str)
{
    stack<char> s;
    bool valid = true;

    cout << "Testing: " << str << endl;

    for (size_t i = 0; i < str.length(); ++i)
    {
        char c = str[i];

        if (IsLeft(c))
        {
            s.push(c);
        }
        else if (IsRight(c))
        {
            if (s.empty())
            {
                valid = false;
                break;
            }
            char top = s.top();
            s.pop();
            if (!Match(top, c))
            {
                valid = false;
                break;
            }
        }
        // Ignore other characters
    }

    if (valid && s.empty())
    {
        cout << "Result: Match (匹配)" << endl;
    }
    else
    {
        cout << "Result: Illegal (此串括号匹配不合法)" << endl;
    }
    cout << "-----------------------------" << endl;
}

int main()
{
    string input;

    // Built-in test cases
    CheckParenthesis("([][])");
    CheckParenthesis("[()]");
    CheckParenthesis("([)]");
    CheckParenthesis("(([])");
    CheckParenthesis(")");

    cout << "Enter a string to check (or 'q' to quit): ";
    while (getline(cin, input) && input != "q")
    {
        CheckParenthesis(input);
        cout << "Enter a string to check (or 'q' to quit): ";
    }

    return 0;
}
