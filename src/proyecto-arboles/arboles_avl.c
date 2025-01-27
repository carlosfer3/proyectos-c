#include <stdio.h>
#include <stdlib.h>

#define max(x, y) ((x) > (y) ? (x) : (y))

typedef struct Nodo {
    struct Nodo* izquierdo;
    int valor;
    struct Nodo* derecho;
}   Nodo;
typedef struct ArbolBinario {
    struct Nodo* raiz;
}   ArbolBinario;

Nodo* crearNodo(int valor);
Nodo* agregarNodo(Nodo* nodo, int valor);
void imprimirArbol(Nodo* nodo, int longitud);
void inOrden(Nodo* nodo);
void preOrden(Nodo* nodo);
void postOrden(Nodo* nodo);
int altura(Nodo* nodo);
Nodo* buscarNodo(Nodo* nodo, int valor);
int valorMinimo(Nodo* nodo);
int valorMaximo(Nodo* nodo);
Nodo* equilibrarArbol(Nodo* nodo);

int main(void) {
    ArbolBinario arbol1;
    arbol1.raiz = NULL;

    arbol1.raiz = agregarNodo(arbol1.raiz, 5);
    arbol1.raiz = agregarNodo(arbol1.raiz, 5);
    arbol1.raiz = agregarNodo(arbol1.raiz, 6);
    arbol1.raiz = agregarNodo(arbol1.raiz, 3);
    arbol1.raiz = agregarNodo(arbol1.raiz, 4);
    arbol1.raiz = agregarNodo(arbol1.raiz, 9);
    arbol1.raiz = agregarNodo(arbol1.raiz, 8);
    arbol1.raiz = agregarNodo(arbol1.raiz, 10);
    arbol1.raiz = agregarNodo(arbol1.raiz, 1);
    imprimirArbol(arbol1.raiz, 1);

    printf("La altura del arbol es: %d\n", altura(arbol1.raiz));
    printf("El recorrido en preOrden es: ");
    preOrden(arbol1.raiz);
    printf("\nEl recorrido en postOrden es: ");
    postOrden(arbol1.raiz);
    printf("\nEl recorrido inOrden es: ");
    inOrden(arbol1.raiz);
    printf("\nEl valor maximo es: %d\n", valorMaximo(arbol1.raiz));
    printf("El valor minimo es: %d\n", valorMinimo(arbol1.raiz));

    Nodo* nodo_buscar = buscarNodo(arbol1.raiz, 10);
    printf("\n%d\n", nodo_buscar->valor);

    return 0;
}

Nodo* crearNodo(int valor) {
    Nodo* nodo = (Nodo*)malloc(sizeof(Nodo));

    if(nodo == NULL ){
        perror("Hubo un error al asociar memoria\n");
        exit(1);
    }

    nodo->valor = valor;
    nodo->derecho = NULL;
    nodo->izquierdo = NULL;

    return nodo;
}
Nodo* agregarNodo(Nodo* nodo, int valor) {
    if (nodo == NULL) {
        nodo = crearNodo(valor);
    } else {
        if (valor > nodo->valor) {
            nodo->derecho = agregarNodo(nodo->derecho, valor);
        } else if (valor < nodo->valor) {
            nodo->izquierdo = agregarNodo(nodo->izquierdo, valor);
        } else {
            printf("Ya se agregó el valor de %d\n", valor);
        }
    }
    nodo = equilibrarArbol(nodo);

    return nodo;
}
void imprimirArbol(Nodo* nodo, int longitud) {
    size_t indice;
    
    if(nodo == NULL) {
        return;
    }

    imprimirArbol(nodo->derecho, longitud + 1);
    for(indice = 0; indice < longitud; indice++) {
        printf("    ");
    }
    printf("--|%d\n", nodo->valor);
    imprimirArbol(nodo->izquierdo, longitud + 1);
}
void inOrden(Nodo* nodo) {
    if(nodo == NULL) {
        return;
    }
    inOrden(nodo->izquierdo);
    printf(" %d", nodo->valor);
    inOrden(nodo->derecho);
}
void preOrden(Nodo* nodo) {
    if(nodo == NULL) {
        return;
    }
    printf(" %d", nodo->valor);
    preOrden(nodo->izquierdo);
    preOrden(nodo->derecho);
}
void postOrden(Nodo* nodo) {
    if(nodo == NULL) {
        return;
    }
    postOrden(nodo->izquierdo);
    postOrden(nodo->derecho);
    printf(" %d", nodo->valor);
}
int altura(Nodo* nodo) {
    if(nodo == NULL) {
        return -1;
    }

    return max(altura(nodo->derecho), altura(nodo->izquierdo)) + 1;
}
Nodo* buscarNodo(Nodo* nodo, int valor) {
    if(nodo == NULL) {
        return NULL;
    }   else {
        if(nodo->valor == valor) {
            return nodo;
        }   else if(nodo->valor < valor) {
            return buscarNodo(nodo->derecho, valor);
        }   else {
            return buscarNodo(nodo->izquierdo, valor);
        }
    }
}
int valorMinimo(Nodo* nodo) {
    if(nodo->izquierdo == NULL) {
        return nodo->valor;
    }
    return valorMinimo(nodo->izquierdo);
}
int valorMaximo(Nodo* nodo) {
    if(nodo->derecho == NULL) {
        return nodo->valor;
    }
    return valorMaximo(nodo->derecho);
}
Nodo* equilibrarArbol(Nodo* nodo) {
    int alt_izq;
    int alt_der;

    alt_izq = altura(nodo->izquierdo);
    alt_der = altura(nodo->derecho);

    if(abs(alt_izq - alt_der) > 1) {
        if(alt_der > alt_izq) {
            nodo = rotacionIzq(nodo);
        }   else{
            nodo = rotacionDer(nodo);
        }
    }

    return nodo;
}
Nodo* rotacionIzq(Nodo* nodo) {
    Nodo* nodo_izquierdo = nodo->izquierdo;
    Nodo* nodo_derecho = nodo->derecho;
    Nodo* menor = buscarNodo(nodo_derecho, valorMinimo(nodo_derecho));
    int valor;
    
    valor = nodo->valor;
    nodo = nodo->derecho;
}
Nodo* rotacionDer(Nodo* nodo) {
    Nodo* nodo_izquierdo = nodo->izquierdo;
    Nodo* nodo_derecho = nodo->derecho;
    Nodo* mayor = buscarNodo(nodo_izquierdo, valorMinimo(nodo_izquierdo));
}