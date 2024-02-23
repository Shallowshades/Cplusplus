#include <iostream>
#include "helper.h"

using namespace std;

/*
    extern通常用于大型项目中，其中代码被分为多个文件。
    它允许在一个文件中定义变量或函数，并在其他文件中使用它们。
    这样，我们可以更好地组织代码，并使其更易于维护。

    例如，在一个游戏项目中，
    我们可能有一个文件来处理用户输入，
    另一个文件来处理游戏逻辑，
    还有一个文件来处理图形渲染。
    使用extern，我们可以在这些文件之间共享变量和函数，从而使代码更加模块化和易于管理。
*/

extern int global_vaiable;
extern void helper_function();

int main() {

    std::cout << global_vaiable << std::endl;
    helper_function();

    return 0;
}
