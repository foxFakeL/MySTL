/*
 * @Author: foxFakeL 3196718529@qq.com
 * @Date: 2023-07-26 23:34:45
 * @LastEditors: foxFakeL 3196718529@qq.com
 * @LastEditTime: 2023-08-03 18:53:33
 * @FilePath: /MySTL/main.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>

#include "allocator.h"
#include "alogrithm.h"
#include "list.h"
// using namespace std;
using namespace mystl;
using std::cout;
using std::endl;
using std::vector;
struct Foo {
    int a;
    float b;
    Foo() : a(0), b(0) {}
};

int main() {
    // list<list<int>> l;
    // for (int i = 0; i < 10; i++) {
    //     list<int> tmp;
    //     for (int j = 0; j < 10; j++) {
    //         tmp.push_back(j);
    //     }
    //     l.push_back(tmp);
    // }
    // for (auto i = l.begin(); i != l.end(); i = i->next) {
    //     for (auto j = i->data.begin(); j != i->data.end(); j = j->next) {
    //         cout << j->data << " ";
    //     }
    //     cout << endl;
    // }
    vector<vector<double>> a = {{1, 1, 1}, {0, 1, 1}};
    a = orthogonalization(a);
    for (auto i : a) {
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
}