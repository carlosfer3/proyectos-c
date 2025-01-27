#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define LONGITUD sizeof(palabras) / sizeof(palabras[0])
#define MAX 100

const char* palabras[] = {
    "algoritmo", "javascript", "java", "listas", 
    "variable", "bucle", "funcion", "arreglo",
    "puntero", "clase", "objeto", "compilacion", 
    "error", "base", "servidor", "programa", "depuracion",
    "estructura", "libreria", "conexion", "test"
};

typedef struct {
    char palabra[MAX];
    char secreto[MAX];
    size_t intentos;
}   Consola;

int aleatorio();
Consola iniciarConsola();
void mostrarConsola(Consola consola);
void jugar();
void carga();

int main(void) {
    size_t i;
    bool seguir;
    char caracter[1];

    srand(time(NULL));
    printf("Bienvenido al juego de ahorcados en C!\n");
    do{
        carga();
        jugar();
        printf("Desea volver a jugar?(S/all): ");
        scanf("%c", &caracter);
        getchar();

        if(toupper(caracter[0]) == 'S') {
            seguir = true;
        }   else{
            seguir = false;
        }
        
    }   while(seguir);
    printf("Gracias por jugar!\n");
    system("pause");

    return 0;
}

int aleatorio() {
    return rand() % LONGITUD;
}
Consola iniciarConsola() {
    Consola consola;
    size_t i;

    strcpy(consola.secreto, palabras[aleatorio()]);
    for(i = 0; i < strlen(consola.secreto); i++) {
        consola.palabra[i] = '_';
    }
    consola.intentos = strlen(consola.secreto);

    return consola;
}
void mostrarConsola(Consola consola) {
    size_t i;
    size_t j;

    printf("\n\n");
    for(i = 0; i < strlen(consola.secreto); i++) {
        printf("%c ", consola.palabra[i]);
    }
    printf("\tIntentos: %zu\n", consola.intentos);
}
void jugar() {
    Consola consola = iniciarConsola();
    char caracter[1];
    size_t i;
    bool correcto;

    while(consola.intentos != 0 && strcmp(consola.palabra, consola.secreto) != 0) {
        correcto = false;
        mostrarConsola(consola);
        printf("Ingrese un caracter: ");
        scanf("%c", &caracter);
        getchar();

        for(i = 0; i < strlen(consola.secreto); i++) {
            if(consola.secreto[i] == caracter[0]) {
                consola.palabra[i] = caracter[0];
                correcto = true;
            }
        }

        if(!correcto) {
            consola.intentos -= 1;
        }
    }

    if(consola.intentos == 0) {
        printf("Perdiste!, mejor suerte para la proxima:)\n");
    }   else{
        printf("Ganaste!, FELICIDADES:D\n");
    }
}
void carga() {
    size_t i;
    clock_t inicio;
    clock_t espera;

    printf("Cargando");
    for(i = 0; i < 4; i++) {
        inicio = clock();
        clock_t espera = 1.5 * CLOCKS_PER_SEC;

        while(clock() - inicio < espera);
        if(i != 3) {
            printf(". ");
        }
    }
    printf("\n");
}