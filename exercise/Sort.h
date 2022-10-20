#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void print(T A[], int n = 10) {
	for (int i = 0; i < n; ++i) {
		cout << A[i] << " ";
	}cout << endl;
}

template<typename T>
int Partition(T A[], int low, int high) {
	T pivot = A[low];
	while (low < high) {
		while (low < high && A[high] >= pivot) --high;
		A[low] = A[high];
		while (low < high && A[low] <= pivot) ++low;
		A[high] = A[low];
	}

	A[low] = pivot;
	//print(A);
	return low;
}

template<typename T>
void QuickSort(T A[], int low, int high) {
	if (low < high) {
		int pivotpos = Partition(A, low, high);
		QuickSort(A, low, pivotpos - 1);
		QuickSort(A, pivotpos + 1, high);
	}
}

int* B; //��������

template<typename T>
void Merge(T A[], int low, int mid, int high) {
	//��A[low, high] ���Ƶ�B[k]��
	for (int k = low; k <= high; ++k) B[k] = A[k];
	//memcpy(B + low, A + low, (high - low + 1) * sizeof(T));

	//B�����е�δ��������� i[low, mid] j[mid + 1, high] 
	//A����������������� k[low, high]
	int i, j, k;
	for (i = low, j = mid + 1, k = low; i <= mid && j <= high; ++k) {
		if (B[i] <= B[j]) {
			A[k] = B[i++];
		}
		else {
			A[k] = B[j++];
		}
	}

	//��δ���������ݷ���A��
	while (i <= mid) A[k++] = B[i++];
	while (j <= high) A[k++] = B[j++];
}

template<typename T>
void MergeSort(T A[], int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2; //���м仮������������
		MergeSort(A, low, mid);     //����������������
		MergeSort(A, mid + 1, high);//���Ҳ������������
		Merge(A, low, mid, high);   //�ϲ�
		print(A);
	}
}

vector<vector<int>> v(10, vector<int>());

template<typename T>
void BaseSort(T A[], int n, int base) {
	//����
	for (int i = 0; i < n; ++i) {
		v[A[i] / base % 10].push_back(A[i]);
	}
	//�ռ�
	int k = 0;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < v[i].size(); ++j) {
			A[k++] = v[i][j];
		}
		v[i].clear();
	}
}

//template<typename T>
//void InsertSort(T A[], int n) {
//    int i, j;
//    for (i = 1; i < n; ++i) {
//        if (A[i] < A[i - 1]) {
//            T tmp = A[i];
//            for (j = i - 1; tmp < A[j]; --j) {
//                A[j + 1] = A[j];
//            }
//            A[j + 1] = tmp;
//        }
//        print(A);
//    }
//}

template<typename T>
void InsertSort(T A[], int n) {
	int low, high, mid;
	for (int i = 1; i < n; ++i) {
		if (A[i] < A[i - 1]) {
			T tmp = A[i];
			low = 0, high = i - 1;
			while (low <= high) {
				mid = (low + high) / 2;
				if (A[mid] > tmp) high = mid - 1;
				else low = mid + 1;
			}
			for (int j = i - 1; j >= high + 1; --j) {
				A[j + 1] = A[j];
			}
			A[high + 1] = tmp;
		}
		print(A);
	}
}

template<typename T>
void ShellSort(T A[], int n) {
	int j;
	for (int dk = n / 2; dk > 0; dk /= 2) {
		for (int i = dk; i < n; ++i) {
			if (A[i] < A[i - dk]) {
				T tmp = A[i];
				for (j = i - dk; j >= 0 && tmp < A[j]; j -= dk) {
					A[j + dk] = A[j];
				}
				A[j + dk] = tmp;
			}
		}
		print(A);
	}
}

template<typename T>
void BubbleSort(T A[], int n) {
	for (int i = 0; i < n; ++i) {
		bool flag = false;
		for (int j = i + 1; j < n; ++j) {
			if (A[i] > A[j]) {
				swap(A[i], A[j]);
				flag = true;
			}
		}
		print(A);
		if (!flag) return;
	}
}

template<typename T>
void SelectSort(T A[], int n) {
	for (int i = 0; i < n - 1; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < n; ++j) {
			if (A[j] < A[minIndex]) {
				minIndex = j;
			}
		}
		if (minIndex != i) swap(A[i], A[minIndex]);

		print(A);
	}
}

//A[1]Ϊ��һ��Ԫ��
//����
template<typename T>
void HeapAdjust(T A[], int k, int n) {
	for (int i = 2 * k; i <= n; i *= 2) {
		if (i < n && (A[i] > A[k] || A[i + 1] > A[k])) {//�������ӽڵ�
			if (A[i] > A[i + 1]) swap(A[i], A[k]);
			else swap(A[++i], A[k]);
		}
		else if (A[i] > A[k]) {//ֻ��һ���ӽڵ�
			swap(A[i], A[k]);
		}
		else {//������ѽṹ
			break;
		}
		k = i;//�������ڵ���±�
	}
}
//����
template<typename T>
void BuildMaxHeap(T A[], int n) {
	for (int i = n / 2; i > 0; --i) {
		HeapAdjust(A, i, n);
	}
}

template<typename T>
void HeapSort(T A[], int n) {
	BuildMaxHeap(A, n);//��ʼ���󶥶�
	print(A, 11);
	for (int i = n; i > 1; --i) {
		swap(A[i], A[1]);//����Ѷ�Ԫ��
		HeapAdjust(A, 1, i - 1);//����
		print(A, 11);
	}
}