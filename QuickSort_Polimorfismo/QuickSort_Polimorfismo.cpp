#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <windows.h>

using namespace std;

double performancecounter_diff(LARGE_INTEGER* a, LARGE_INTEGER* b)
{
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

class cmp {
public:
    virtual bool op(int, int) = 0;
};

class Cless : public cmp{
public:
    bool op(int a, int b) {
        return a < b;
    }
};

class Cgreater : public cmp {
public:
    bool op(int a, int b) {
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

void bubbleSort(int arr[], int n, cmp* p)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place  
        for (j = 0; j < n - i - 1; j++)
            if (p->op(arr[j], arr[j + 1]))
                swap(&arr[j], &arr[j + 1]);
}  

int main()
{
    //VARIABLES PARA CONTARRIEMPO DE LA FUNCION QUICKSORT
    LARGE_INTEGER t_ini, t_fin;
    double secs;
    //

    int x;
    while (1) {
        cout << "Ingrese numero de elementos: "; cin >> x;

        int* arr = new int[x];

        cmp* p;

        Cless l;
        Cgreater g;

        p = &g;

        rellenar(arr, x);

        QueryPerformanceCounter(&t_ini);
        bubbleSort(arr, x, p);
        QueryPerformanceCounter(&t_fin);

        secs = performancecounter_diff(&t_fin, &t_ini);
        cout << "La funcion quicksort con polimorfismo demora: " << secs * 1000.0 << "ms con " << x << " elementos." << endl;
    }
}