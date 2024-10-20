// 4B2G0039_2.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// 檢查括號是否對稱
bool areParenthesesBalanced(const string& expr) {
    stack<char> s;
    for (char ch : expr) {
        if (ch == '(') {
            s.push(ch); // 遇到左括號，推入堆疊
        }
        else if (ch == ')') {
            if (s.empty()) return false; // 遇到右括號但堆疊為空，表示不對稱
            s.pop(); // 遇到右括號，彈出堆疊頂端的左括號
        }
    }
    return s.empty(); // 最後檢查堆疊是否為空
}

// 計算運算子優先順序
int precedence(char op) {
    if (op == '+' || op == '-') return 1; // 加減運算的優先順序為1
    if (op == '*' || op == '/') return 2; // 乘除運算的優先順序為2
    return 0; // 其他運算子的優先順序為0
}

// 將中序表式法轉換為後序表式法
string infixToPostfix(const string& expr) {
    stack<char> s;
    string postfix;
    for (char ch : expr) {
        if (isdigit(ch)) {
            postfix += ch; // 遇到數字，直接加入後序表式法
        }
        else if (ch == '(') {
            s.push(ch); // 遇到左括號，推入堆疊
        }
        else if (ch == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top(); // 遇到右括號，彈出堆疊中的運算子直到遇到左括號
                s.pop();
            }
            s.pop(); // 彈出左括號
        }
        else {
            while (!s.empty() && precedence(s.top()) >= precedence(ch)) {
                postfix += s.top(); 
                // 遇到運算子，彈出堆疊中優先順序大於等於當前運算子的運算子
                s.pop();
            }
            s.push(ch); // 推入當前運算子
        }
    }
    while (!s.empty()) {
        postfix += s.top(); // 將剩餘的運算子加入後序表式法
        s.pop();
    }
    return postfix;
}

// 計算後序表式法的結果
int evaluatePostfix(const string& postfix) {
    stack<int> s;
    for (char ch : postfix) {
        if (isdigit(ch)) {
            s.push(ch - '0'); // 遇到數字，推入堆疊
        }
        else {
            int val2 = s.top(); s.pop(); // 彈出堆疊頂端的兩個數字
            int val1 = s.top(); s.pop();
            switch (ch) {
            case '+': s.push(val1 + val2); break; // 加法運算
            case '-': s.push(val1 - val2); break; // 減法運算
            case '*': s.push(val1 * val2); break; // 乘法運算
            case '/': s.push(val1 / val2); break; // 除法運算
            }
        }
    }
    return s.top(); // 返回堆疊頂端的結果
}

int main() {
    string expr;
    char cont = 'Y';
    while (toupper(cont) == 'Y') {
        cout << "請輸入運算式: ";
        cin >> expr;

        if (!areParenthesesBalanced(expr)) {
            cout << expr << " 運算式的括號不對稱，無法繼續運算" << endl;
        }
        else {
            cout << expr << " 運算式的左右括號對稱" << endl;
            string postfix = infixToPostfix(expr);
            cout << expr << " 運算式的後序表式法為: " << postfix << endl;
            int result = evaluatePostfix(postfix);
            cout << expr << " 運算式的運算結果為: " << result << endl;
        }

        cout << "是否繼續測試? (Y/N): ";
        cin >> cont;
    }
    return 0;
}



// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
