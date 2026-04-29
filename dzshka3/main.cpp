#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;


vector<int> bubble_sort(vector<int> array) {
    int n = array.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (array[j] > array[j + 1]) {
                swap(array[j], array[j + 1]);
            }
        }
    }
    return array;
}

void merge_sort(vector<int>& array) {
    if (array.size() > 1) {

        int mid = array.size() / 2;

        vector<int> left(array.begin(), array.begin() + mid);
        vector<int> right(array.begin() + mid, array.end());
        
        merge_sort(left);
        merge_sort(right);

        int i = 0; // левая
        int j = 0; // правая
        int k = 0; // исходный массив

        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                array[k] = left[i];
                i++;
            }
            else {
                array[k] = right[j];
                j++;
            }
            k++;
        }

        while (i < left.size()) {
            array[k] = left[i];
            i++;
            k++;
        }

        while (j < right.size()) {
            array[k] = right[j];
            j++;
            k++;
        }
    }
}

int razdel(vector<int>& array, int start, int end) {
    int pivot = array[end];
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(array[i], array[j]);
        }
    }

    swap(array[i + 1], array[end]);
    return i + 1;
}

void quick_sort(vector<int>& array, int start, int end) {
    if (start < end) {
        int p = razdel(array, start, end);
        quick_sort(array, start, p - 1);
        quick_sort(array, p + 1, end);
    }
}

vector<int> generate_array(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100000);

    for (int i = 0; i < size; i++) {
        arr[i] = dist(gen);
    }
    return arr;
}


int main() {

    vector<int> arr = { 5, 2, 9, 1, 5, 6 };
    vector<int> arr2 = { 123, 16, 15, 20, 60 };
    vector<int> arr3 = { 3, 5, 3, 7, 9, 10};
    vector<int> arr4 = { 7, 10, 100, 1000, 15 };

    vector<int> b = bubble_sort(arr);
    cout << "Bubble: ";
    for (int x : b) cout << x << " ";
    cout << endl;

    vector<int> b1 = bubble_sort(arr2);
    cout << "Bubble: ";
    for (int x : b1) cout << x << " ";
    cout << endl;

    vector<int> b2 = bubble_sort(arr3);
    cout << "Bubble: ";
    for (int x : b2) cout << x << " ";
    cout << endl;

    vector<int> b3 = bubble_sort(arr4);
    cout << "Bubble: ";
    for (int x : b3) cout << x << " ";
    cout << endl;

    vector<int> m1 = arr;
    merge_sort(m1);
    cout << "Merge: ";
    for (int x : m1) cout << x << " ";
    cout << endl;

    vector<int> m2 = arr2;
    merge_sort(m2);
    cout << "Merge: ";
    for (int x : m2) cout << x << " ";
    cout << endl;

    vector<int> m3 = arr3;
    merge_sort(m3);
    cout << "Merge: ";
    for (int x : m3) cout << x << " ";
    cout << endl;

    vector<int> m4 = arr4;
    merge_sort(m4);
    cout << "Merge: ";
    for (int x : m4) cout << x << " ";
    cout << endl;

    vector<int> q1 = arr;
    quick_sort(q1, 0, q1.size() - 1);
    cout << "Quick: ";
    for (int x : q1) cout << x << " ";
    cout << endl;

    vector<int> q2 = arr2;
    quick_sort(q2, 0, q2.size() - 1);
    cout << "Quick: ";
    for (int x : q2) cout << x << " ";
    cout << endl;

    vector<int> q3 = arr3;
    quick_sort(q3, 0, q3.size() - 1);
    cout << "Quick: ";
    for (int x : q3) cout << x << " ";
    cout << endl;

    vector<int> q4 = arr4;
    quick_sort(q4, 0, q4.size() - 1);
    cout << "Quick: ";
    for (int x : q4) cout << x << " ";
    cout << endl;

    vector<int> sizes = { 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000,100000};

    cout << "\nразмер\tbubble\tmerge\tquick\n";

    for (int size : sizes) {
        vector<int> base = generate_array(size);

        // bubble
        auto start = high_resolution_clock::now();
        bubble_sort(base);
        auto end = high_resolution_clock::now();
        double bubble_time = duration<double>(end - start).count();

        // merge
        vector<int> m_arr = base;
        start = high_resolution_clock::now();
        merge_sort(m_arr);
        end = high_resolution_clock::now();
        double merge_time = duration<double>(end - start).count();

        // quick
        vector<int> q_arr = base;
        start = high_resolution_clock::now();
        quick_sort(q_arr, 0, q_arr.size() - 1);
        end = high_resolution_clock::now();
        double quick_time = duration<double>(end - start).count();

        cout << size << "\t"
            << bubble_time << "\t"
            << merge_time << "\t"
            << quick_time << endl;
    }

    return 0;
}