## `forward`函数

不需要写两个函数,就可以通过传递通用引用模板的参数来实现一个函数同时接受右值引用和左值。

具体做法是:

定义函数模板如下:

```cpp
template <typename T>
void func(T&& arg) {
  // 函数体
}
```

这里使用 T&& 作为参数类型,其中T是通用引用,&&是右值引用。

这个通用引用参数可以绑定到左值,也可以绑定到右值:

```cpp
int x = 1; 

func(x); //传入左值
func(2); //传入右值
```

在函数体内部,可以通过 std::forward 来保持传入参数的左值属性或右值属性:

```cpp
template <typename T>
void func(T&& arg) {
  T newArg = std::forward<T>(arg);
  
  // 使用newArg
}
```

这种通用引用模板参数的写法既可以接受左值又可以接受右值,实现了一个函数同时适用于两种情况。

所以通过模板 + std::forward,我们可以实现一个既能处理右值又能处理左值的函数。
