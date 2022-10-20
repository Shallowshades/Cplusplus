#include <iostream>
#include <cstdlib>
#include <cstring>
#include <math.h>

using namespace std;

typedef long long ll;

const int LIST_INIT_SIZE = 100;
const int LISTINCREASEMENT = 10;

//顺序表 动态分配

struct StList {
	int* elem;
	int length;
	int listsize;
};
///动态分配
// #define InitSize 100
// typedef struct{
//     ElemType *data;
//     int MaxSize,length;
// }SqList;

bool InitList(StList& L) {
	L.elem = (int*)malloc(LIST_INIT_SIZE * sizeof(int));
	if (!L.elem) exit(0);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return true;
}

bool ListEmpty(const StList& L) {
	return !L.length ? true : false;
}

bool IncreaseListSize(StList& L) {
	int* newbase = (int*)realloc(L.elem, (L.listsize + LIST_INIT_SIZE) * sizeof(int));
	if (!newbase) exit(0);
	L.elem = newbase;
	L.listsize += LIST_INIT_SIZE;
	return true;
}

bool DestoryList(StList& L) {
	if (L.elem) free(L.elem);
	L.elem = NULL;
    L.length = L.listsize = 0;
	return true;
}

bool ListInsert(StList& L, int i, int e) {//1 - length
	if (i<1 || i>L.length + 1) return false;
	if (L.length >= L.listsize) IncreaseListSize(L);
	++L.length;
	for (int j = L.length; j >= i; --j) L.elem[j] = L.elem[j - 1];
	L.elem[i - 1] = e;
	return true;
}

int ListFindElem(StList& L, int e) {
	for (int i = 0; i < L.listsize; ++i) {
		if (L.elem[i] == e) return i + 1;
	}
	return 0;
}

bool ListDelete(StList& L, int i, int e) {
	if (i<1 || i>L.length) return false;
	for (int j = i - 1; j < L.length - 1; ++j) L.elem[j] = L.elem[j + 1];
	--L.length;
	return false;
}

bool ListDelete(StList& L, int e) {
	int k = ListFindElem(L, e);
	if (!k) return false;
	ListDelete(L, k, e);
	return true;
}

bool ListModifyElem(StList& L, int i, int e) {
	if (i < 1 || i>L.length) return false;
	L.elem[i - 1] = e;
	return true;
}

void MergeList(StList& L1, StList& L2, StList& L3) {
	L3.length = L3.listsize = L2.length + L1.length;
	L3.elem = (int*)malloc(L3.listsize * sizeof(int));
	if (!L3.elem) exit(0);
	for (int i = 0, j = 0, k = 0; i < L1.length || j < L2.length;) {
		if (i < L1.length && j < L2.length) {
			if (L1.elem[i] < L2.elem[j]) L3.elem[k++] = L1.elem[i++];
			else L3.elem[k++] = L2.elem[j++];
		}
		if (i < L1.length) L3.elem[k++] = L1.elem[i++];
		if (j < L2.length) L3.elem[k++] = L2.elem[j++];
	}
}

void PrintList(const StList& L) {
	if (ListEmpty(L)) { cout << "StList is empty!\n"; return; }
	for (int i = 0; i < L.length; ++i) cout << *(L.elem + i) << " "; cout << "\n";
}

int main() {

	StList L1;
	InitList(L1);
	PrintList(L1);
	for (int i = 5; i > 0; --i) ListInsert(L1, 1, i);
	PrintList(L1);
	for (int i = 3; i > 1; --i) ListDelete(L1, i);
	PrintList(L1);
	DestoryList(L1);
	PrintList(L1);
	StList L2, L3;
	InitList(L2);
	for (int i = 9; i > 0; i -= 2) ListInsert(L2, 1, i);
	PrintList(L2);
	MergeList(L1, L2, L3);
	PrintList(L3);

	return 0;
}