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
void qs(int* lista, int lim_izq, int lim_der) {
    Ox o;
    int izq, der, temp, pivote;
    izq = lim_izq;
    der = lim_der;
    pivote = lista[(izq + der) / 2];

    do {
        while (o(lista[izq], pivote) && izq < lim_der) {
            ++izq;
        }
        while (o(pivote, lista[der]) && der > lim_izq) {
            --der;
        }
        if (izq <= der)
        {
            temp = lista[izq];
            lista[izq] = lista[der];
            lista[der] = temp;
            ++izq;
            --der;
        }

    } while (izq <= der);

    if (lim_izq < der) {
        qs<Ox>(lista, lim_izq, der);
    }
    if (lim_der > izq) {
        qs<Ox>(lista, izq, lim_der);
    }

}
template <class Ox>
void quicksort(int* arr, int size) {

    qs<Ox>(arr, 0, size - 1);
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
    quicksort<Cless>(arr, x);
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