#include <thread>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <fstream>

using namespace std;
using namespace chrono;

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


void quick_sort_parallel(vector<int>& array, int start, int end, int threads) {
    if (start < end) {
        int p = razdel(array, start, end);

        if (threads > 1) {
            int left_threads = threads / 2;
            int right_threads = threads - left_threads;

            thread left_thread(quick_sort_parallel, ref(array), start, p - 1, left_threads);
            thread right_thread(quick_sort_parallel, ref(array), p + 1, end, right_threads);

            left_thread.join();
            right_thread.join();
        }
        else {
            // если поток 1, то обычная сортировка
            quick_sort(array, start, p - 1);
            quick_sort(array, p + 1, end);
        }
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

   

    vector<int> sizes = { 100, 1000, 10000, 20000, 30000, 40000, 50000 };

    cout << "Size\tQuick\t2 threads\t4 threads\t8 threads\n";

    for (int size : sizes) {
        vector<int> base = generate_array(size);

        // обычный quick
        vector<int> q1 = base;
        auto start = high_resolution_clock::now();
        quick_sort(q1, 0, q1.size() - 1);
        auto end = high_resolution_clock::now();
        double t1 = duration<double>(end - start).count()*1000;

        // 2 потока
        vector<int> q2 = base;
        start = high_resolution_clock::now();
        quick_sort_parallel(q2, 0, q2.size() - 1, 2);
        end = high_resolution_clock::now();
        double t2 = duration<double>(end - start).count()*1000;

        // 4 потока
        vector<int> q4 = base;
        start = high_resolution_clock::now();
        quick_sort_parallel(q4, 0, q4.size() - 1, 4);
        end = high_resolution_clock::now();
        double t4 = duration<double>(end - start).count()*1000;

        // 8 потоков
        vector<int> q8 = base;
        start = high_resolution_clock::now();
        quick_sort_parallel(q8, 0, q8.size() - 1, 8);
        end = high_resolution_clock::now();
        double t8 = duration<double>(end - start).count()*1000;

        double s2 = t1 / t2;
        double s4 = t1 / t4;
        double s8 = t1 / t8;

        cout << size << "\t"
            << t1 << "\t"
            << t2 << "\t"
            << t4 << "\t"
            << t8 << "\t"
            << s2 << "\t"
            << s4 << "\t"
            << s8 << endl;
    }
   
    ofstream file("results.txt");

    file << "size normal t2 t4 t8\n";

    for (int size : sizes) {
        vector<int> base = generate_array(size);

        // обычный quick
        vector<int> q1 = base;
        auto start = high_resolution_clock::now();
        quick_sort(q1, 0, q1.size() - 1);
        auto end = high_resolution_clock::now();
        double t1 = duration<double>(end - start).count() * 1000;

        // 2 потока
        vector<int> q2 = base;
        start = high_resolution_clock::now();
        quick_sort_parallel(q2, 0, q2.size() - 1, 2);
        end = high_resolution_clock::now();
        double t2 = duration<double>(end - start).count() * 1000;

        // 4 потока
        vector<int> q4 = base;
        start = high_resolution_clock::now();
        quick_sort_parallel(q4, 0, q4.size() - 1, 4);
        end = high_resolution_clock::now();
        double t4 = duration<double>(end - start).count() * 1000;

        // 8 потоков
        vector<int> q8 = base;
        start = high_resolution_clock::now();
        quick_sort_parallel(q8, 0, q8.size() - 1, 8);
        end = high_resolution_clock::now();
        double t8 = duration<double>(end - start).count() * 1000;

        file << size << " " << t1 << " " << t2 << " " << t4 << " " << t8 << "\n";
    }

    file.close();

    return 0;
}

