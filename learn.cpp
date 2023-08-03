/*
 * @Author: foxFakeL 3196718529@qq.com
 * @Date: 2023-07-28 18:44:38
 * @LastEditors: foxFakeL 3196718529@qq.com
 * @LastEditTime: 2023-08-03 19:01:08
 * @FilePath: /MySTL/learn.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
//
// Created by foxfake on 23-7-28.
//

#include <iostream>
#include <utility>
using namespace std;
class Foo {
   public:
    int a;
    Foo(int a) : a(a) { cout << "constructor" << endl; }
    Foo() { cout << "default constructor" << endl; }
    Foo(const Foo& foo) { cout << "copy constructor" << endl; }
};
template <class T>
void fun(T&& t) {
    T t2 = std::forward<T>(t);
}
int main() {
    char c = '8';
    int a = c ^ 48;
    cout << a << endl;
    a = 9;
    c = a ^ 48;
    cout << a << endl;
}