#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Created by: Ricardo Garcia*/

using std::cout;
using std::cin;
using std::endl;

/**** DECLARACION DE VARIABLES GLOBALES ****/
int tam = 0;
int * camino;
int ** matriz;
/*int matriz1[5][5] = {
    {0, 1, 5, 4, 9},
    {1, 0, 7, 10, 2},
    {5, 7, 0, 8, 6},
    {4, 10, 8, 0, 3},
    {9, 2, 6, 3, 0}
};*/

//int camino[5];
int sumatoria = 99999;
/******************************************/

void permutaciones(int s[], int);
void print(int s[], int n);
void swap(int *i, int *j);
int factorial(int);
void caminoMasCorto(int vec[], int n);
void printMasCorto();
void inicializaMatriz(int tam);

int main() {
    int n, r, num_comb;
    //    cout << "Dame tamanio de la matriz cuadrada: ";
    //    cin>>tam;
    //cin>>r;
    /**************************************************/
    std::ifstream filein("Matriz.txt");
    for (std::string line; getline(filein, line);) {
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] == 32) {
                tam++;
                break;
            }
        }
    }

    std::ifstream in("Matriz.txt");
    int mat2[tam][tam];

    for (int y = 0; y < tam; ++y) {
        for (int j = 0; j < tam; ++j) {
            in >> mat2[y][j];
        }
    }


    in.close();

    /**************************************************/
    inicializaMatriz(tam);
    /******************************************/
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            matriz[i][j] = mat2[i][j];
        }
    }

    cout << "Matriz global: \n";
    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << "\n";
    }
    /****************************************/
    n = tam;
    r = tam;
    int j, val_max;
    int s[ 6 ], i, m;
    num_comb = factorial(n) / (factorial(n - r) * factorial(r));
    for (i = 1; i <= r; i++)
        s[i] = i;
    permutaciones(s, r);

    for (i = 2; i <= num_comb; i++) {
        m = r;
        val_max = n;
        while (s [m] == val_max) {
            //	Encuentra el elemento más a la derecha
            //	que no tiene su valor máximo.
            m = m - 1;
            val_max = val_max - 1;
        }
        // Se incrementa el elemento más a la derecha

        s[m] = s [ m ] + 1;
        // el resto de los elementos son sucesores de X[m]
        for (j = m + 1; j <= r; j++)
            s [j] = s [j - 1] + 1;

        permutaciones(s, r);
    }
    printMasCorto();

    /* LIBERAMOS MEMORIA */
    for (int i = 0; i < tam; i++)
        free(matriz[i]);
    free(matriz);

    free(camino);
    return 0;
}

void inicializaMatriz(int tam) {
    camino = (int *) calloc(tam, sizeof(int));
    matriz = (int **) calloc(tam, sizeof(int *));
    for (int i = 0; i < tam; i++) {
        matriz[i] = (int *) calloc(tam,sizeof(int));
    }
}

void permutaciones(int s[], int n) {
    int i, nfact, m, k, p, q;
    // Copia el arreglo
    int x[6];
    for (i = 0; i < 6; i++) {
        x[i] = s [i];
    }

    nfact = factorial(n);

    print(s, n);

    for (i = 2; i <= nfact; i++) {
        m = n - 1;
        while (s[ m ] > s[ m + 1 ])
            m--;
        k = n;
        while (s[ m ] > s[ k ])
            k--;
        swap(&s[ m ], &s[ k ]);
        p = m + 1;
        q = n;
        while (p < q) {
            swap(&s[ p ], &s[ q ]);
            p++;
            q--;
        }
        print(s, n);
    }
    for (i = 0; i < 6; i++) {
        s[i] = x [i];
    }

}

int factorial(int n) {
    if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);

}

void print(int s[], int n) { /* Me llega la permutación y el tamaño de ella*/
    int i;
    for (i = 1; i <= n; i++)
        printf("%d ", s[ i ]);
    printf("\n");
    caminoMasCorto(s, n);
}

void printMasCorto() {
    cout << "\n\n El camino mas corto es : ";
    for (int i = 1; i <= tam; i++) {
        cout << camino[i] << " ";
    }
    cout << "\n Con un peso de: " << sumatoria << "\n\n";
}

void caminoMasCorto(int vec[], int n) {
    int suma = 0;
    int x = 0;
    int y = 0;
    for (int i = 1; i <= n - 1; i++) {
        x = (vec[i]) - 1;
        y = (vec[i + 1]) - 1;
        cout << "matriz[" << x << "][" << y << "] = " << matriz[x][y] << "\n";
        suma += matriz[x][y];
    }

    x = (vec[n] - 1);
    y = (vec[1] - 1);
    //x = (vec[0]-1);
    //y = (vec[n-1]-1);
    cout << "matriz[" << x << "][" << y << "] = " << matriz[x][y] << "\n";
    suma += matriz[x][y];
    cout << "Sumatoria: " << suma << "\n";
    if (suma < sumatoria) {
        cout << suma << " < " << sumatoria << "\n";
        sumatoria = suma;
        for (int i = 1; i <= tam; i++) {
            camino[i] = vec[i];
        }
    }
}

void swap(int *i, int *j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}
