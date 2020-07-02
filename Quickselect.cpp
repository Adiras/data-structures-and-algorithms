#include <iostream>

#define INT_MAX 2147483647
#define W_MAX 1000001

using namespace std;

int partition(int list[], int left, int right, int pivotIndex)
{
    int pivot = list[pivotIndex];
    swap(list[pivotIndex], list[right]);
    int storeIndex = left;
    for (int i = left; i < right; ++i) {
        if (list[i] < pivot) {
            swap(list[i], list[storeIndex]);
            storeIndex++;
        }
    }
    swap(list[storeIndex], list[right]);
    return storeIndex;
}

int quickselect(int list[], int left, int right, int k)
{
    if (left == right)
        return list[left];

    int pivotIndex = left + rand() % (right - left + 1);

    pivotIndex = partition(list, left, right, pivotIndex);

    if (k == pivotIndex)
        return list[k];
    else if (k < pivotIndex)
        return quickselect(list, left, pivotIndex - 1, k);
    else
        return quickselect(list, pivotIndex + 1, right, k);
}


int main()
{
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    int valueArr[n];
    int indexArr[W_MAX];
    for (int i = 0; i < W_MAX; ++i)
        indexArr[i] = INT_MAX;

    for (int i = 0; i < n; ++i) {
        int p, w;
        cin >> p >> w;

        valueArr[i] = w;

        if (indexArr[w] > p)
            indexArr[w] = p;
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int k;
        cin >> k;
        if (n == 1)
            cout << indexArr[valueArr[0]] << endl;
        else
            cout << indexArr[quickselect(valueArr, 0, n, k)] << endl;
    }

    return 0;
}
