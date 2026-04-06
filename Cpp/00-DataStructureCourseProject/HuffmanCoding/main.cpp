#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <map>

using namespace std;

struct HTNode
{
    char data;
    int weight;
    int parent, lchild, rchild;

    HTNode() : data('\0'), weight(0), parent(0), lchild(0), rchild(0) {}
};

class HuffmanSystem
{
private:
    vector<HTNode> HT;
    map<char, string> HC;
    int n;

    // 选择两个权重最小的节点
    void Select(int k, int &s1, int &s2)
    {
        int min1 = 0x7FFFFFFF, min2 = 0x7FFFFFFF;
        s1 = s2 = 0;

        for (int i = 1; i <= k; ++i)
        {
            if (HT[i].parent == 0)
            {
                if (HT[i].weight < min1)
                {
                    min2 = min1;
                    s2 = s1;
                    min1 = HT[i].weight;
                    s1 = i;
                }
                else if (HT[i].weight < min2)
                {
                    min2 = HT[i].weight;
                    s2 = i;
                }
            }
        }
    }

    // 为每个字符生成 Huffman 编码
    void GenerateCodes()
    {
        HC.clear();
        for (int i = 1; i <= n; ++i)
        {
            string code = "";
            int c = i;
            int f = HT[i].parent;
            while (f != 0)
            {
                if (HT[f].lchild == c)
                    code = "0" + code;
                else
                    code = "1" + code;
                c = f;
                f = HT[f].parent;
            }
            HC[HT[i].data] = code;
        }
    }

public:
    HuffmanSystem() : n(0) {}

    // I: Initialization
    void Init()
    {
        cout << "Enter number of characters (n): ";
        if (!(cin >> n))
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input.\n";
            return;
        }

        int m = 2 * n - 1;
        HT.resize(m + 1);

        cout << "Enter " << n << " characters and their weights (e.g., 'a 5'):\n";
        for (int i = 1; i <= n; ++i)
        {
            cin >> HT[i].data >> HT[i].weight;
        }

        // Build Tree
        for (int i = n + 1; i <= m; ++i)
        {
            int s1, s2;
            Select(i - 1, s1, s2);
            HT[s1].parent = i;
            HT[s2].parent = i;
            HT[i].lchild = s1;
            HT[i].rchild = s2;
            HT[i].weight = HT[s1].weight + HT[s2].weight;
        }

        // Save to hfmTree
        ofstream outFile("hfmTree.txt");
        if (outFile.is_open())
        {
            outFile << n << endl;
            for (int i = 1; i <= m; ++i)
            {
                outFile << i << " " << (HT[i].data == '\0' ? '#' : HT[i].data) << " "
                        << HT[i].weight << " " << HT[i].parent << " "
                        << HT[i].lchild << " " << HT[i].rchild << endl;
            }
            outFile.close();
            cout << "Huffman Tree saved to hfmTree.txt\n";
        }
        else
        {
            cout << "Error opening hfmTree.txt\n";
        }

        GenerateCodes();
    }

    void LoadTree()
    {
        ifstream inFile("hfmTree.txt");
        if (!inFile.is_open())
        {
            cout << "hfmTree.txt not found. Please Initialize first.\n";
            return;
        }

        inFile >> n;
        int m = 2 * n - 1;
        HT.resize(m + 1);

        for (int i = 1; i <= m; ++i)
        {
            int idx;
            char d;
            inFile >> idx >> d >> HT[i].weight >> HT[i].parent >> HT[i].lchild >> HT[i].rchild;
            HT[i].data = (d == '#' ? '\0' : d);
        }
        inFile.close();
        GenerateCodes();
        cout << "Huffman Tree loaded from hfmTree.txt\n";
    }

    // E: Encoding
    void Encode()
    {
        if (n == 0)
            LoadTree();
        if (n == 0)
            return;

        ifstream inFile("ToBeTran.txt");
        if (!inFile.is_open())
        {
            cout << "Error: ToBeTran.txt not found.\n";
            return;
        }

        string text((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();

        ofstream outFile("CodeFile.txt");
        if (!outFile.is_open())
        {
            cout << "Error: Cannot open CodeFile.txt\n";
            return;
        }

        for (char c : text)
        {
            if (HC.find(c) != HC.end())
            {
                outFile << HC[c];
            }
            else if (c != '\n' && c != '\r')
            {
                // Ignore newlines or handle unknown chars?
                // Assignment says input is ASCII char set, let's assume valid.
                // Or maybe simple ignoring.
                cout << "Warning: Character '" << c << "' not in Huffman Tree. Skipped.\n";
            }
        }
        outFile.close();
        cout << "Encoding complete. Saved to CodeFile.txt\n";
    }

    // D: Decoding
    void Decode()
    {
        if (n == 0)
            LoadTree();
        if (n == 0)
            return;

        ifstream inFile("CodeFile.txt");
        if (!inFile.is_open())
        {
            cout << "Error: CodeFile.txt not found.\n";
            return;
        }

        string code((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
        inFile.close();

        ofstream outFile("TextFile.txt");
        if (!outFile.is_open())
        {
            cout << "Error: Cannot open TextFile.txt\n";
            return;
        }

        int m = 2 * n - 1;
        int p = m; // Root
        for (char c : code)
        {
            if (c == '0')
                p = HT[p].lchild;
            else if (c == '1')
                p = HT[p].rchild;

            if (HT[p].lchild == 0 && HT[p].rchild == 0)
            {
                outFile << HT[p].data;
                p = m; // Reset to root
            }
        }
        outFile.close();
        cout << "Decoding complete. Saved to TextFile.txt\n";
    }

    // P: Print Code File
    void PrintCode()
    {
        ifstream inFile("CodeFile.txt");
        if (!inFile.is_open())
        {
            cout << "Error: CodeFile.txt not found.\n";
            return;
        }

        char c;
        int count = 0;
        cout << "\nCodeFile Content:\n";
        while (inFile.get(c))
        {
            cout << c;
            count++;
            if (count % 50 == 0)
                cout << endl;
        }
        if (count % 50 != 0)
            cout << endl;
        inFile.close();
    }

    // T: Print Tree
    void PrintTreeHelper(int node, int level, ofstream &outFile)
    {
        if (node == 0)
            return;

        PrintTreeHelper(HT[node].rchild, level + 1, outFile);

        for (int i = 0; i < level; ++i)
        {
            cout << "    ";
            outFile << "    ";
        }

        string display = "";
        if (HT[node].lchild == 0 && HT[node].rchild == 0)
        {
            display = string(1, HT[node].data) + "(" + to_string(HT[node].weight) + ")";
        }
        else
        {
            display = to_string(HT[node].weight);
        }

        cout << display << endl;
        outFile << display << endl;

        PrintTreeHelper(HT[node].lchild, level + 1, outFile);
    }

    void PrintTree()
    {
        if (n == 0)
            LoadTree();
        if (n == 0)
            return;

        ofstream outFile("TreePrint.txt");
        if (!outFile.is_open())
        {
            cout << "Error: Cannot open TreePrint.txt\n";
            return;
        }

        cout << "\nHuffman Tree (Right-rotated 90 degrees):\n";
        PrintTreeHelper(2 * n - 1, 0, outFile); // Root is at 2*n-1

        outFile.close();
        cout << "\nHuffman Tree saved to TreePrint.txt\n";
    }
};

int main()
{
    HuffmanSystem hfm;
    char choice;

    // Create dummy test file
    ofstream dummy("ToBeTran.txt");
    dummy << "abbcccdddd";
    dummy.close();

    do
    {
        cout << "\n----------------------------\n";
        cout << "   Huffman Coding System    \n";
        cout << "----------------------------\n";
        cout << "I: Initialization\n";
        cout << "E: Encoding\n";
        cout << "D: Decoding\n";
        cout << "P: Print Code File\n";
        cout << "T: Print Huffman Tree\n";
        cout << "Q: Quit\n";
        cout << "Enter choice: ";
        cin >> choice;
        choice = toupper(choice);

        switch (choice)
        {
        case 'I':
            hfm.Init();
            break;
        case 'E':
            hfm.Encode();
            break;
        case 'D':
            hfm.Decode();
            break;
        case 'P':
            hfm.PrintCode();
            break;
        case 'T':
            hfm.PrintTree();
            break;
        case 'Q':
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 'Q');

    return 0;
}
