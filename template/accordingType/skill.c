/**
 * @file skill.c
 * @author your name (you@domain.com)
 * @brief c通过技法实现不同类型不同运算
 * @version 0.1
 * @date 2023-01-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define TYPE_INT 0
#define TYPE_FLOAT 1

typedef struct Variant{
    union {
        int x;
        float y;
    }data;
    unsigned typeId;
}Variant;

Variant* addFloatOrMulInt(const Variant * a, const Variant* b){
    Variant* ret = (Variant*)malloc(sizeof(Variant));
    assert(a->typeId == b->typeId);
    if(a->typeId == TYPE_INT){
        ret->data.x = a->data.x * b->data.x;
        ret->typeId = TYPE_INT;
    }else if(a->typeId == TYPE_FLOAT){
        ret->data.y = a->data.y + b->data.y;
        ret->typeId = TYPE_FLOAT;
    }
    return ret;
}

void print(const Variant* v){
    if(v->typeId == TYPE_INT){
        printf("%d %u\n", v->data.x,v->typeId);
    }else if(v->typeId == TYPE_FLOAT){
        printf("%f %u\n", v->data.y,v->typeId);
    }
}

int main(){

    Variant a,b;
    a.data.y = 12.3;
    a.typeId = TYPE_FLOAT;
    b.data.y = 13.2;
    b.typeId = TYPE_FLOAT;
    Variant* c = addFloatOrMulInt(&a,&b);
    print(c);
    return 0;
}