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

void qs(int* lista, int lim_izq, int lim_der, cmp* p) {
    int izq, der, temp, pivote;
    izq = lim_izq;
    der = lim_der;
    pivote = lista[(izq + der) / 2];

    do {
        while (p->op(lista[izq], pivote) && izq < lim_der) {
            ++izq;
        }
        while (p->op(pivote, lista[der]) && der > lim_izq) {
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
        qs(lista, lim_izq, der, p);
    }
    if (lim_der > izq) {
        qs(lista, izq, lim_der, p);
    }

}

void quicksort(int* arr, int size, cmp* p) {

    qs(arr, 0, size - 1, p);
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
        quicksort(arr, x, p);
        QueryPerformanceCounter(&t_fin);

        secs = performancecounter_diff(&t_fin, &t_ini);
        cout << "La funcion quicksort con polimorfismo demora: " << secs * 1000.0 << "ms con " << x << " elementos." << endl;
    }
}