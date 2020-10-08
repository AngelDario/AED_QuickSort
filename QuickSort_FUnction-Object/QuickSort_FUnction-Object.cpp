#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

using namespace std;

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


double performancecounter_diff(LARGE_INTEGER* a, LARGE_INTEGER* b)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

struct Cless {
    bool operator() (int a, int b) {
        return a < b;
    }
};

struct Cgreater {
    bool operator() (int a, int b) {
        return a > b;
    }
};

void rellenar(int* arr, int size) {
    srand(time(NULL));

    for (int* p = arr; p < arr + size; p++) {
        int n = 1 + rand() % ((size + 1) - 1);
        *p = n;
    }
}

void print(int* arr, int size) {
    cout << "[";
    for (int* p = arr; p < arr + size; p++) {
        cout << *p;
        if (p < (arr + size - 1)) {
            cout << " , ";
        }
    }
    cout << "]";
}

template <class Ox>
void bubbleSort(int arr[], int n)
{
    Ox ordenar;

    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place  
        for (j = 0; j < n - i - 1; j++)
            if (ordenar(arr[j], arr[j + 1]))
                swap(&arr[j], &arr[j + 1]);
}

int main()
{

    //VARIABLES PARA CONTARRIEMPO DE LA FUNCION QUICKSORT
    LARGE_INTEGER t_ini, t_fin;
    double secs;
    //

    int x;
    while(1){
    cout << "Ingrese numero de elementos: "; cin >> x;

    int* arr = new int[x];

    rellenar(arr, x);

    /*print(arr, x);
    cout << endl;*/

    QueryPerformanceCounter(&t_ini);
    bubbleSort<Cless>(arr, x);
    QueryPerformanceCounter(&t_fin);

    /*cout << endl;
    print(arr, x);
    cout << endl;*/

    secs = performancecounter_diff(&t_fin, &t_ini);
    cout << "La funcion quicksort con Function-Object demora: " << secs * 1000.0 << "ms con " << x << " elementos." << endl;
    cout << endl;
    }
    return 0;
}