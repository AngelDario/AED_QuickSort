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

void rellenar(int* arr, int size) {
    srand(time(NULL));
  
    for (int* p = arr; p < arr + size; p++) {
        int n = 1 + rand() % ((size + 1) - 1);
        *p = n;
    }
}

void print(int *arr, int size) {
    cout << "[";
    for (int* p = arr; p < arr + size; p++) {
        cout << *p ;
        if (p < (arr + size-1)) {
            cout<<" , ";
        }
    }
    cout << "]";
}

bool mayor(int a, int b) {
    return a > b;
}
bool menor(int a, int b) {
    return a < b;
}

void qs(int* lista, int lim_izq, int lim_der, bool (*p)(int, int)) {
    int izq, der, temp, pivote;
    izq = lim_izq;
    der = lim_der;
    pivote = lista[(izq + der) / 2];

    do {
        while ( p(lista[izq] , pivote) && izq < lim_der) { 
            ++izq; 
        }
        while ( p(pivote, lista[der]) && der > lim_izq) { 
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

void quicksort(int* arr, int size, bool (*p)(int , int)) {
    
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

        bool (*fmayor)(int, int) = &mayor;
        bool (*fmenor)(int, int) = &menor;

        rellenar(arr, x);
        QueryPerformanceCounter(&t_ini);
        quicksort(arr, x, fmenor);
        QueryPerformanceCounter(&t_fin);

        secs = performancecounter_diff(&t_fin, &t_ini);
        cout << "La funcion quicksort con puntero a funcion demora: " << secs * 1000.0 << "ms con " << x << " elementos." << endl;
        cout << endl;
        delete[] arr;
    }
}

