#include <iostream>
#include <vector>
using namespace std;

typedef uint8_t ElemType;

//带头结点的单链表
//头结点的data为长度
typedef struct LNode{
    ElemType data;
    struct LNode *next;
    ElemType& operator[] (const int &dex) const {
        LNode *p = this->next;
        for(int i=0;i<dex-1;++i) p=p->next;
        return p->data;
    }
}LNode, *LinkList;

bool GetLNode(const LinkList &L,int k,LNode *&p){//取得第k个元素
    if(k<1||k>L->data) return false; //下标越界
    p = L->next;
    int i = 1;
    while(p&&i<k) ++i,p=p->next;
    if(!p||i>k) return false;
    return true;
}
ElemType GetElem(LinkList &L,int k){//取得第k个元素的数据
    LNode *p = NULL; 
    GetLNode(L,k,p);
    if(p == NULL) return false;
    return p->data;
}
bool GetElem(LinkList &L,int k,ElemType &e){//取得第k个元素的数据
    LNode *p = NULL; 
    GetLNode(L,k,p);
    if(p == NULL) return false;
    e = p->data;
    return true;
}

bool ListInsert(LinkList &L,int k,const ElemType& e){//在第k个位置插入
    LNode *p = NULL; 
    GetLNode(L,k - 1,p);
    if(p == NULL) return false;
    LNode *q = new LNode;
    q->data = e;
    q->next = p->next;
    p->next = q;
    ++L->data;
    return true;
}

bool ListDelete(LinkList &L,int k,ElemType &e){
    if(k < 1 || k > L->data) return false;
    LNode *p = NULL;
    if(k == 1) p = L;
    else GetLNode(L,k-1,p);
    if(L == NULL) return false;
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    delete q;
    --L->data;
    return true;
}

void CreatList(LinkList &L,int n){//头插法建立linklist
    L = new LNode;
    L->data = 0;
    L->next = NULL;
    for(int i=n;i>0;--i){
        LNode *p = new LNode;
        p->data = i;
        p->next = L->next;
        L->next = p;
        ++L->data;
    }
}

void PrintList(const LinkList &L){
    if(!L->data) cout<<"The List is empty!\n";
    LNode *p = L->next;
    cout<<"len = "<<L->data<<": ";
    while(p) cout<<p->data<<" ",p=p->next; cout<<"\n";
}

void MergeList(LinkList& L1,LinkList &L2,LinkList &L3){//1,2合并到3 重新连线即可
    LNode *p1 = L1->next;
    LNode *p2 = L2->next;
    LNode *p3 = L1; 
    L3 = L1; L3->data = L1->data + L2->data;
    while(p1&&p2){
        if(p1->data < p2->data) p3->next = p1, p1=p1->next,p3=p3->next;
        else p3->next = p2,p2=p2->next,p3=p3->next;
    }
    p3->next = p1?p1:p2;
    delete L2;
}

void add(uint8_t data){
    
}


int main(){
    
    return 0;
}