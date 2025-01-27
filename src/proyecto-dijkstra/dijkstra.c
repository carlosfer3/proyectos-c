#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define max(x, y) ((x) > (y) ? (x) : (y))
#define MAX 100

typedef struct Grafo {
    int matriz[MAX][MAX];
    int cantidad;
}   Grafo;
typedef struct Nodo {
    int valor;
    int peso;
    struct Nodo* siguiente;
}   Nodo;

void representar(Grafo grafo);
Grafo iniciarGrafo(int cantidad);
Grafo agregarNodos(Grafo grafo, int peso, int i, int j);
Nodo* crearNodoRecursivo(Nodo* nodo, int valor, int peso);
Nodo* dijkstra(Grafo grafo, Nodo* nodo, int actual, int fin);
void representarNodos(Nodo* nodo);

int main(void) {
    int cantidad = 10;
    Nodo* caminoMinimo = NULL;
    Grafo grafo = iniciarGrafo(cantidad);

    // representar(grafo);

    grafo = agregarNodos(grafo, 3, 10, 2);
    grafo = agregarNodos(grafo, 7, 5, 2);
    grafo = agregarNodos(grafo, 1, 2, 3);
    grafo = agregarNodos(grafo, 1, 1, 1);
    grafo = agregarNodos(grafo, 5, 2, 1);
    grafo = agregarNodos(grafo, 1, 0, 2);
    grafo = agregarNodos(grafo, 8, 0, 0);
    grafo = agregarNodos(grafo, 7, 2, 3);
    grafo = agregarNodos(grafo, 1, 1, 2);

    representar(grafo);
    caminoMinimo = dijkstra(grafo, caminoMinimo, 1, 8);
    if(caminoMinimo == NULL) {
        printf("No existe un camino para los nodos 1 y 8\n");
    }   else {
        representarNodos(caminoMinimo);
    }
    caminoMinimo = NULL;
    caminoMinimo = dijkstra(grafo, caminoMinimo, 1, 3);
    if(caminoMinimo == NULL) {
        printf("No existe un camino para los nodos 1 y 3\n");
    }   else{
        representarNodos(caminoMinimo);
    }

    return 0;
}

void representar(Grafo grafo) {
    size_t i;
    size_t j;

    printf("\\\t");
    for(i = 0; i < grafo.cantidad; i++) {
        printf("%d\t", i);
    }

    printf("\n");
    for(i = 0; i < grafo.cantidad; i++) {
        printf("%d\t", i);
        for(j = 0; j < grafo.cantidad; j++) {
            printf("%d\t", grafo.matriz[i][j]);
        }
        printf("\n");
    }
}
Grafo iniciarGrafo(int cantidad) {
    Grafo grafo;
    size_t i;
    size_t j;

    grafo.cantidad = cantidad;
    for(i = 0; i < cantidad; i++) {
        for(j = 0; j < cantidad; j++) {
            grafo.matriz[i][j] = 0;
        }
    }

    return grafo;
}
Grafo agregarNodos(Grafo grafo, int peso, int i, int j) {
    if(i >= grafo.cantidad || j >= grafo.cantidad) {
        printf("Coloco una posicion superior a la cantidad de nodos\n");
    }   else if (i == j) {
        printf("Las posiciones no pueden tener el mismo valor\n");
    }   else{
        grafo.matriz[i][j] = peso;
        grafo.matriz[j][i] = peso;
    }

    return grafo;
}
Nodo* crearNodoRecursivo(Nodo* nodo, int valor, int peso) {
    if(nodo == NULL) {
        nodo = (Nodo*)malloc(sizeof(Nodo));

        nodo->valor = valor;
        nodo->peso = peso;
        nodo->siguiente = NULL;
    }   else{
        nodo->siguiente = crearNodoRecursivo(nodo->siguiente, valor, peso);
    }

    return nodo;
}
Nodo* dijkstra(Grafo grafo, Nodo* nodo, int actual, int fin) {
    size_t i;
    int nvopeso;
    int valor;
    int minimo;
    Nodo* auxiliar;

    if(fin < 0 || actual < 0 || fin >= grafo.cantidad || actual >= grafo.cantidad) {
        printf("No ha ingresado datos correctos!\n");
        exit(1);
    }

    if(actual == fin) {
        return nodo;
    }
    if(nodo == NULL) {
        nodo = crearNodoRecursivo(nodo, actual, 0);
    }

    valor = -1;
    minimo = INT_MAX;
    for(i = 0; i < grafo.cantidad; i++) {
        if(grafo.matriz[actual][i] != 0) {
            auxiliar = nodo;
            while(auxiliar->siguiente != NULL && auxiliar->valor != i) {
                auxiliar = auxiliar->siguiente;
            }

            if(auxiliar->valor == i) {
                continue;
            }

            nvopeso = grafo.matriz[actual][i] + auxiliar->peso;
            if(minimo > nvopeso) {
                minimo = nvopeso;
                valor = i;
            }
        }
    }

    if(valor == -1) {
        return NULL;
    }
    nodo = crearNodoRecursivo(nodo, valor, nvopeso);

    return dijkstra(grafo, nodo, valor, fin);
}
void representarNodos(Nodo* nodo) {
    while(nodo != NULL) {
        printf(" %d", nodo->valor);
        if(nodo->siguiente == NULL) {
            printf("\nY el peso es: %d", nodo->peso);
        }
        nodo = nodo->siguiente;
    }
}
