#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int maxCruce(vector<int>& arr, int izq, int mid, int der) {
    int suma = 0;
    int sumaIzq = INT_MIN;

    for (int i = mid; i >= izq; i--) {
        suma += arr[i];
        sumaIzq = max(sumaIzq, suma);
    }

    suma = 0;
    int sumaDer = INT_MIN;

    for (int i = mid + 1; i <= der; i++) {
        suma += arr[i];
        sumaDer = max(sumaDer, suma);
    }

    return sumaIzq + sumaDer;
}

int maxSubarreglo(vector<int>& arr, int izq, int der) {
    if (izq == der)
        return arr[izq];

    int mid = (izq + der) / 2;

    int izqSuma = maxSubarreglo(arr, izq, mid);
    int derSuma = maxSubarreglo(arr, mid + 1, der);
    int cruceSuma = maxCruce(arr, izq, mid, der);

    return max({izqSuma, derSuma, cruceSuma});
}