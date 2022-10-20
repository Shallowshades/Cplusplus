#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>

using namespace std;

typedef int ElemType;
const ElemType MaxSize = 50;
const ElemType MinInf = -0x3f3f3f3f;
struct node {
    node& operator = (const node& L) {
        this->length = L.length;
        for(int i = 0; i < L.length; ++i) 
            this->data[i] = L.data[i];
        return *this;
    }

    ElemType data[MaxSize];
    int length;
};
typedef struct node Sequlist;

void InitList(Sequlist& L) { L.length = 0; memset(L.data, 0, sizeof(L.data)); }
bool Empty(const Sequlist& L) { return L.length == 0; }
int Length(const Sequlist& L) { return L.length; }
bool CreateLsit(Sequlist& L, int n) {
    if (n > MaxSize) return false;
    //for(int i=0;i<n;++i) L.data[i] = rand() % 64;
    int a[10] = { 3,3,54,34,54,5,54,36,36,56 };
    for (int i = 0; i < n; ++i) L.data[i] = a[i];
    L.length = n;
    return true;
}
//malloc或new的数组存在堆中 
//不带static前缀的局部数组在栈中 
//带static前缀的局部数组和全局数组在全局数据区中
void DestoryList(Sequlist& L) { L.length = 0; } //静态无法释放

bool InsertElem(Sequlist& L, int k, const ElemType& e) {
    if (k < 1 || k > L.length) return false;
    if (L.length + 1 >= MaxSize) return false;

    for (int i = L.length - 1; i >= k; --i) L.data[i] = L.data[i - 1];
    L.data[k - 1] = e;
    ++L.length;
    return true;
}

bool DeleteElem(Sequlist& L, int k, ElemType& e) {
    if (k<1 || k>L.length) return false;
    e = L.data[k - 1];
    for (int i = k; i < L.length; ++i) L.data[i - 1] = L.data[i];
    --L.length;
    return true;
}

void PrintList(const Sequlist& L) {
    if (Empty(L)) { cout << "The list is empty!\n"; return; }
    cout << "L.length = " << L.length << " --- ";
    for (int i = 0; i < L.length; ++i) cout << L.data[i] << " "; cout << "\n";
}

//2.2.3
//1
int DeleteListMinNum(Sequlist& L) {
    int dex = 0, num;
    for (int i = 1; i < L.length; ++i)
        if (L.data[i] < L.data[dex])
            dex = i;
    num = L.data[dex];
    L.data[dex] = L.data[L.length - 1];
    --L.length;
    return num;
}

//2
void Swap(ElemType& x, ElemType& y) { int t = x; x = y; y = t; }
void ReverseList(Sequlist& L) {
    int i = 0, j = L.length - 1;
    while (i < j) Swap(L.data[i++], L.data[j--]);
}

//3
void DeleteListElemX(Sequlist& L, const ElemType& x) {
    int i = 0, j = 0, k = 0;
    while (i + k < L.length) {
        while (L.data[i + k] == x) ++k;
        L.data[j++] = L.data[i++ + k];
    }
    L.length -= k;
}

//4
void DeleteListBetweenST(Sequlist& L, const ElemType& s, const ElemType& t) {
    if (t <= s || Empty(L)) { cout << "errors!\n" << "\n"; exit(0); }
    sort(L.data, L.data + L.length, less<ElemType>());
    int i = 0, j = 0, k = 0;
    while (i + k < L.length) {
        while (L.data[i + k] > s && L.data[i + k] < t) ++k;
        L.data[j++] = L.data[i++ + k];
    }
    L.length -= k;
}

//5 同4 已考虑

//6
void DeleteRepeatElem(Sequlist& L) {
    sort(L.data, L.data + L.length, less<ElemType>());
    int i = 0, j = 0;
    while (j < L.length) {
        L.data[i++] = L.data[j++];
        while (j < L.length && L.data[j] == L.data[i - 1]) ++j;
    }
    L.length = i;
}

//7
Sequlist MergeList(Sequlist& L1,Sequlist& L2) {
    sort(L1.data, L1.data + L1.length, less<ElemType>());
    sort(L2.data, L2.data + L2.length, less<ElemType>());
    if (L1.length + L2.length > MaxSize) { cout << "Too large!\n"; exit(0); }
    Sequlist L3;
    int i = 0, j = 0, k = 0;
    while(i<L1.length&&j<L2.length){
        if (L1.data[i] <= L2.data[j]) L3.data[k++] = L1.data[i++];
        else L3.data[k++] = L2.data[j++];
    }
    while(i<L1.length) L3.data[k++] = L1.data[i++];
    while(j<L2.length) L3.data[k++] = L2.data[j++];
    L3.length = L1.length + L2.length;
    return L3;
}

int main() {

    Sequlist L1;
    InitList(L1);
    CreateLsit(L1, 10);
    PrintList(L1);

    int Case = 0;
    //1
    cout << "Case :" << ++Case << "\n";
    cout << DeleteListMinNum(L1) << "\n";
    PrintList(L1);

    //2
    cout << "Case :" << ++Case << "\n";
    ReverseList(L1);
    PrintList(L1);

    //3
    cout << "Case :" << ++Case << "\n";
    DeleteListElemX(L1, 54);
    PrintList(L1);

    //4
    cout << "Case :" << ++Case << "\n";
    DeleteListBetweenST(L1, 10, 40);
    PrintList(L1);

    //5
    cout << "Case :" << ++Case << "\n";
    DeleteListBetweenST(L1, 1, 10);
    PrintList(L1);

    cout << "New list\n";
    CreateLsit(L1, 10);
    PrintList(L1);
    //6
    cout << "Case :" << ++Case << "\n";
    DeleteRepeatElem(L1);
    PrintList(L1);

    Sequlist L2;
    InitList(L2);
    CreateLsit(L2, 5);
    PrintList(L2);

    //7
    cout << "Case :" << ++Case << "\n";
    Sequlist L3 = MergeList(L1, L2);
    PrintList(L3);

    cout << "-------------------------------------------------------------------\n";

    return 0;
}