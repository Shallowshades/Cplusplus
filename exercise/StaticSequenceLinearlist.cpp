
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef int ElemType;

//顺序表 静态分配
//数组下标起始为0
//顺序表位序起始为1

#define MaxSize 50
typedef struct{
    ElemType data[MaxSize];
    int length = 0;
}SqList;

bool Empty(const SqList& L){
    return L.length == 0;
}

bool Length(const SqList& L){
    return L.length;
}

bool ListInsert(SqList &L,int i,const ElemType& e){//在i处插入元素e O(n)

    if(i<1||i>L.length+1) return false;
    if(L.length>=MaxSize) return false;
    
    for(int j=L.length;j>=i;--j) L.data[j] = L.data[j-1];
    L.data[i-1] = e;
    ++L.length;

    return true;
}

bool ListDelete(SqList &L,int i,ElemType& e){//i处元素赋给e并删除 O(n)

    if(i<1||i>L.length) return false;

    e = L.data[i-1];
    for(int j=i;j<L.length;++j) L.data[j-1] = L.data[j];
    --L.length;

    return true;
}

int LocateElem(const SqList& L,ElemType e){//按值查找,返回位序

    for(int i=0;i<L.length;++i){
        if(L.data[i] == e) return i+1;
    }
    return 0;
}

int GetElem(const SqList& L,int i){
    return L.data[i-1];
}

void PrintList(const SqList& L){
    if(Empty(L)) {
        cout <<"The Lsit is Empty\n";
        return;
    }
    for(int i=0;i<L.length;++i) cout <<L.data[i]<<" ";cout<<"\n";
}

int main(){

    SqList L1;

    for(int i=0;i<10;++i) {
        ListInsert(L1,i+1,rand() % 16);
        PrintList(L1);
    }
    
    int x;
    for(int i=0;i<10;++i){
        ListDelete(L1,10-i,x);
        cout <<"x的值为" <<x <<"\n";
        PrintList(L1);
    }

    //system("pause");
    return 0;
}