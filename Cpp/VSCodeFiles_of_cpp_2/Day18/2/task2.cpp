#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "booksale.hpp"

// 按图书销售数量比较
bool compare_by_amount(const BookSale &x1, const BookSale &x2) {
    return x1.get_amount() > x2.get_amount();
}

void test() {
    using std::cin;
    using std::cout;
    using std::getline;
    using std::sort;
    using std::string;
    using std::vector;
    using std::ws;

    vector<BookSale> sales_records;         // 图书销售记录表

    int books_number;
    cout << "录入图书数量: ";
    cin >> books_number;

    cout << "录入图书销售记录\n";
    for(int i = 0; i < books_number; ++i) {
        string name, author, translator, isbn;
        double price;
        cout << string(20, '-') << "第" << i+1 << "本图书信息录入" << string(20, '-') << '\n';
        cout << "录入书名: "; getline(cin>>ws, name);
        cout << "录入作者: "; getline(cin>>ws, author);
        cout << "录入译者: "; getline(cin>>ws, translator);
        cout << "录入isbn: "; getline(cin>>ws, isbn);
        cout << "录入定价: "; cin >> price;

        Book book(name, author, translator, isbn, price);

        double sales_price;
        int sales_amount;

        cout << "录入售价: "; cin >> sales_price;
        cout << "录入销售数量: "; cin >> sales_amount;

        BookSale record(book, sales_price, sales_amount);
        sales_records.push_back(record);
    }

    // 按销售册数排序
    sort(sales_records.begin(), sales_records.end(), compare_by_amount);

    // 按销售册数降序输出图书销售信息
    cout << string(20, '=') <<  "图书销售统计" << string(20, '=') << '\n';
    for(auto &record: sales_records) {
        cout << record << '\n';
        cout << string(40, '-') << '\n';
    }
}

int main() {
    test();
}