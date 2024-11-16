#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 15
#define MAXCARACTERES sizeof(caracteres)/sizeof(caracteres[0])

const char caracteres[] = {'a','b','c', 'd', 'e', 'f', 'g', 'h', 'i',
                            'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                            's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '1',
                            '2', '3', '4', '5', '6', '7', '8', '9', '_', 
                            '-', '&', '<', '>', '+', '*', '/', '@'};

char* generar(int longitud);
int aleatorio(int inferior, int superior);

int main(void) {
    int cantidad;
    size_t indice;

    srand((unsigned int)time(NULL));
    printf("Una contrasenia segura tiene por lo menos 10 caracteres\n");
    printf("Ingrese la cantidad de contrasenias: ");
    scanf("%d", &cantidad);
    getchar();

    for(indice = 0; indice < cantidad; indice++) {
        char* password = generar(aleatorio(10, MAX));
        printf("Contrasenia #%zu: %s\n", indice+1, password);

        free(password);
    }

    return 0;
}

char* generar(int longitud) {
    char *contrasenia = (char*)malloc((longitud+1) * sizeof(char));
    size_t indice;

    for(indice = 0; indice < longitud; indice++) {
        contrasenia[indice] = caracteres[aleatorio(0,MAXCARACTERES-1)];
    }
    contrasenia[longitud] = '\0';
    
    return contrasenia;
}
int aleatorio(int inferior, int superior) {

    return inferior + rand() % (superior - inferior -1);
}