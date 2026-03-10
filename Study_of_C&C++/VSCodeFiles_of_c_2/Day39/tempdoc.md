下面根据给定的算法，用 Mermaid 绘制栈的入栈（push）与出栈（pop）过程图，便于理解回文字符串判断的执行流程。

示例字符串：`"radar"`。

算法思想简述：先把字符串的每个字符依次入栈，随后再依次出栈并与原字符串相对应位置的字符比较；若全部相等则是回文。

示例 C/C++ 风格伪代码：

```cpp
// 回文字符串
int str_palindrome(string &str)
{
    Stack st;
    init(st);
    for (char c : str)
    {
        push(st, c);
    }

    for (char c : str)
    {
        if (pop(st) != c)
            return 0;
    }
    return 1;
}
```

下面的 Mermaid 图展示了对 `"radar"` 的具体入栈与出栈过程：

```mermaid
flowchart TB
    %% Push phase (每个节点是入栈后的快照)
    P0([Stack: (empty)])
    P1([push 'r' -> Stack top->bottom: r])
    P2([push 'a' -> Stack top->bottom: a, r])
    P3([push 'd' -> Stack top->bottom: d, a, r])
    P4([push 'a' -> Stack top->bottom: a, d, a, r])
    P5([push 'r' -> Stack top->bottom: r, a, d, a, r])

    P0 --> P1
    P1 --> P2
    P2 --> P3
    P3 --> P4
    P4 --> P5

    %% Pop / compare phase (每个节点为一次 pop 并比较的快照)
    Q1([pop 'r' ; compare with s[0] = 'r' => match])
    Q2([pop 'a' ; compare with s[1] = 'a' => match])
    Q3([pop 'd' ; compare with s[2] = 'd' => match])
    Q4([pop 'a' ; compare with s[3] = 'a' => match])
    Q5([pop 'r' ; compare with s[4] = 'r' => match])

    P5 --> Q1
    Q1 --> Q2
    Q2 --> Q3
    Q3 --> Q4
    Q4 --> Q5

    Q5 --> R([结果: 全部匹配 => 回文 (true)])
```

说明：
- 图中每个节点表示栈在关键步骤（每次 push 后、每次 pop 并比较时）的快照。
- 文本中用 "top→bottom" 表示栈顶在左侧（最近入栈的元素最先被 pop）。

在 VS Code 中预览：可以使用 Markdown 的 Mermaid 支持扩展（例如 "Markdown Preview Mermaid Support"）或在支持 Mermaid 的 Markdown 预览中打开此文件以查看渲染结果。

（如果需要，我可以把图示改为另一字符串示例或把每一步拆成更多细节的序列图。）
