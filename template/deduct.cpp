/**
 * @file deduct.cpp
 * @author your name (you@domain.com)
 * @brief 先写需要指定的模板参数，再把能推导出来的模板参数放在后面
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>

using namespace std;

template<typename DstType, typename SrcType>
DstType c_style_cast(SrcType value){
    return DstType(value);
}

int main(){

    int v = 52;
    float f = c_style_cast<float>(v);
    cout << f << endl;

    return 0;
}