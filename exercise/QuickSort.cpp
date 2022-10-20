#include <iostream>

using namespace std;

const int N = 1e3 + 10;

// template <typename T>
// void Print(T A[0]) {
//   for (int i = 0; i < 10; ++i)
//     cout << A[i] << " ";
//   cout << endl;
// }
// template <typename T>
// int Partition(T A[], int low, int high) {
//   T pivot = A[low];
//   while (low < high) {
//     while (low < high && A[high] >= pivot)
//       --high;
//     A[low] = A[high];
//     while (low < high && A[low] <= pivot)
//       ++low;
//     A[high] = A[low];
//   }
//   A[low] = pivot;
//   // print(A);
//   return low;
// }
// template <typename T>
// void QuickSort(T A[], int low, int high) {
//   if (low < high) {
//     int pivotpos = Partition(A, low, high);
//     QuickSort(A, low, pivotpos - 1);
//     QuickSort(A, pivotpos + 1, high);
//   }
// }

template <typename T>
void Print(T a[0]) {
  for (int i = 0; i < 10; ++i)
    cout << a[i] << " ";
  cout << endl;
}

template <typename T>
int Partition(T a[], int low, int high) {
  T pivot = a[high];
  while (low < high) {
    while (low < high && a[low] < pivot)
      ++low;
    //此处不带等号，与pivot相同的值会卡住下面的while循环
    //所以下面的high--，处理该情况
    a[high--] = a[low];

    while (low < high && a[high] > pivot)
      --high;
    a[low++] = a[high];
  }

  a[high] = pivot;
  Print(a);
  return high;
}

template <typename T>
void QuickSort(T a[], int low, int high) {
  if (low < high) {
    int pivotpos = Partition(a, low, high);
    QuickSort(a, low, pivotpos - 1);
    QuickSort(a, pivotpos + 1, high);
  }
}

int main() {
  int array[10] = {5, 45, 54, 5, 45, 4, 5, 12, 45, 66};
  QuickSort(array, 0, 9);
  Print(array);
  return 0;
}