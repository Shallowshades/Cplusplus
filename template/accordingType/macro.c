/**
 * @file macro.c
 * @author your name (you@domain.com)
 * @brief c通过宏实现不同类型不同运算
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define BIN_OP(type,a,op,b,result) \
(*(type*)(result)) = (*(const type*)(a)) op (*(const type*)(b))

typedef enum DATA_TYPE{
    TYPE_INT,
    TYPE_FLOAT
}DATA_TYPE;

void doDiv(void* out, const void* data0,const void* data1, DATA_TYPE type){
    if(type == TYPE_INT){
        BIN_OP(int,data0,*,data1,out);
    }else if(type == TYPE_FLOAT){
        BIN_OP(float,data0,+,data1,out);
    }
}

int main(){

    int a1 = 11,b1 = 12,c1 = 0;
    doDiv(&c1,&a1,&b1,TYPE_INT);
    printf("%d\n",c1);

    float a2 = 1.2,b2 = 3.4,c2 = 0.0;
    doDiv(&c2,&a2,&b2,TYPE_FLOAT);
    printf("%f\n",c2);
    
    return 0;
}