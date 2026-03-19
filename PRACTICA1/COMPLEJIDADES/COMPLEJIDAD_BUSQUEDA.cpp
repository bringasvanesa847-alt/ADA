#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>

using namespace std;
using namespace chrono;

int busquedaLineal(const vector<int>& arr, int key) {
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == key)
            return i;
    return -1;
}

int busquedaBinaria(const vector<int>& arr, int key) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int jumpSearch(const vector<int>& arr, int key) {
    int n = arr.size();
    int step = sqrt(n);
    int prev = 0;

    while (arr[min(step, n) - 1] < key) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) return -1;
    }

    while (arr[prev] < key) {
        prev++;
        if (prev == min(step, n)) return -1;
    }

    if (arr[prev] == key) return prev;
    return -1;
}

int main() {

    cout << "Tamano,Linear,Binary,Jump,Memoria_Bytes\n";

    for (int n = 1000; n <= 100000; n += 5000) {

        vector<int> arr(n);
        for (int i = 0; i < n; i++)
            arr[i] = i;

        int key = n - 1;

        auto start = high_resolution_clock::now();
        busquedaLineal(arr, key);
        auto end = high_resolution_clock::now();
        auto linearTime = duration_cast<nanoseconds>(end - start).count();

        start = high_resolution_clock::now();
        busquedaBinaria(arr, key);
        end = high_resolution_clock::now();
        auto binaryTime = duration_cast<nanoseconds>(end - start).count();

        start = high_resolution_clock::now();
        jumpSearch(arr, key);
        end = high_resolution_clock::now();
        auto jumpTime = duration_cast<nanoseconds>(end - start).count();

        long memoria = n * sizeof(int);

        cout << n << ","
             << linearTime << ","
             << binaryTime << ","
             << jumpTime << ","
             << memoria << "\n";
    }

    return 0;
}