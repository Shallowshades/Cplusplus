#include <iostream>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

typedef struct Bnode{
    int data;
    Bnode *lchild,*rchild;
    bool ltag = 0,rtag = 0;
}*BTree;

void AddBnode(Bnode *&T,const int& val){
    if(T!=nullptr){
        if(val < T->data) AddBnode(T->lchild,val);
        else AddBnode(T->rchild,val);
    }
    else{
        T = new Bnode;
        T->data = val;
        T->lchild=T->rchild = 0;
    }
}

void CreateBTree(BTree &T,const vector<int> &v){
    for(int i=0;i<v.size();++i) AddBnode(T,v[i]);
}

bool print(int elem){ cout<< elem << " "; return true; }

bool display(const BTree &T, bool (*visit)(int elem) = print){
    visit(T->data);
    if(T->ltag && T->lchild != nullptr) visit(T->lchild->data);
    if(T->rtag && T->rchild != nullptr) visit(T->rchild->data); cout<<"\n"; 
    return true;
}

bool PreOrder(const BTree &T, bool (*visit)(int elem)){
    if(T){
        display(T);
        if(!T->ltag) PreOrder(T->lchild,print);
        if(!T->rtag) PreOrder(T->rchild,print);
        return true;
    }
    return false;
}

bool InOrder(const BTree &T, bool (*visit)(int elem)){
    if(T){
        if(!T->ltag) InOrder(T->lchild,print);
        display(T);
        if(!T->rtag) InOrder(T->rchild,print);
        return true;
    }
    return false;
}

bool PostOrder(const BTree &T, bool (*visit)(int elem)){
    if(T){
        if(!T->ltag) PostOrder(T->lchild,print);
        if(!T->rtag) PostOrder(T->rchild,print);
        display(T);
        return true;
    }
    return false;
}

bool LevelOrder(const BTree &T,bool (*visit)(int elem)){
    queue<Bnode*> Q;
    Bnode *now;
    if(T!=nullptr) Q.push(T);
    while(!Q.empty()){
        now = Q.front();Q.pop();
        if(now!=nullptr){
            visit(now->data);
            Q.push(now->lchild);
            Q.push(now->rchild);
        }
    }
    return true;
}

bool Traversal(const BTree &T,bool (*traverse)(const BTree &T,bool(*visit)(int elem)) = InOrder){
    traverse(T,print);
    return true;
}

void InThread(BTree &p,BTree &pre){
    if(p!=nullptr){
        InThread(p->lchild,pre);
        if(p->lchild==nullptr){
            p->lchild = pre;
            p->ltag = 1;
        }

        if(pre!=nullptr&&pre->rchild==nullptr){
            pre->rchild = p;
            pre->rtag=1;
        }
        pre = p;
        InThread(p->rchild,pre);
    }
}

void CreateInThread(BTree& T){
    BTree pre = nullptr;
    if(T!=nullptr){
        InThread(T,pre);
        pre->rchild = nullptr;
        pre->rtag = 1;
    }
}

void PreThread(BTree p,BTree &pre){
    if(p!=nullptr){
        if(p->lchild==nullptr){
            p->lchild = pre;
            p->ltag = 1;
        }

        if(pre!=nullptr&&pre->rchild==nullptr){
            pre->rchild = p;
            pre->rtag = 1;
        }
        pre = p;

        if(!p->ltag) PreThread(p->lchild,pre); 
        if(!p->rtag) PreThread(p->rchild,pre); 
        //左右孩子都应该判断是否线索化

        //若为叶子节点
        //其左孩子将会回到其父节点

        //当前节点的父节点若无右孩子
        //将当前节点的父节点的右孩子线索化为当前节点

        //两种情况都会陷入死循环
    }
}

void CreatePreThread(BTree& T){
    BTree pre = nullptr;
    if(T!=nullptr){
        PreThread(T,pre);
        pre->rchild = nullptr;
        pre->rtag = 1;
    }
}

int main(){

    int a[] = {6,8,4,7,3,2,5,1};
    vector<int> v;
    for(int i=0;i<8;++i) v.push_back(a[i]);
    BTree T(nullptr);
    CreateBTree(T,v);
    CreatePreThread(T);
    Traversal(T,PreOrder);
    return 0;

}