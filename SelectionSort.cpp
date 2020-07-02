#include <iostream>
#include <string>

using namespace std;

struct Data {
    string name;
    int time;
};

void selection_sort(Data *arr, int n)
{
    int index;

    for (int i = 0; i < n-1; i++) {
        index = i;
        for (int j = i+1; j < n; j++)
            if (arr[j].time > arr[index].time)
                index = j;
            else if (arr[j].time == arr[index].time)
                if (arr[j].name < arr[index].name)
                    index = j;

        swap(arr[index], arr[i]);
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);

    short t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, p;
        cin >> n >> p;

        Data *arr = new Data[n];

        for (int j = 0; j < n; j++)
            cin >> arr[j].name >> arr[j].time;

        selection_sort(arr, n);

        long long time = 0;

        for (int j = 0; j < n; j++) {
            if (j < p) cout << arr[j].name << ' ';

            if (j == 0) time += 1;
            else time += (1 + j * arr[j].time);
        }

        cout << endl << (time % 1000003) << endl;

        delete[](arr);
    }

    return 0;
}
