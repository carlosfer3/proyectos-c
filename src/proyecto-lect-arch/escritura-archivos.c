#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header.h"

int main(void) {
    FILE* data;
    usuario usuarioTemp;
    size_t indice;
    size_t cantidad;
    ll dni;

    data = fopen("src/proyecto-lect-arch/usuarios.dat", "wb");

    printf("Ingrese la cantidad de usuarios: ");
    scanf("%zu", &cantidad);
    getchar();

    for(indice = 0; indice < cantidad; indice++) {
        printf("Ingrese los nombres del usuario #%zu: ", indice+1);
        fgets(usuarioTemp.nombres, MAXNOMBRES, stdin);
        usuarioTemp.nombres[strcspn(usuarioTemp.nombres, "\n")] = '\0';

        printf("Ingrese los apellidos del usuario #%zu: ", indice+1);
        fgets(usuarioTemp.apellidos, MAXAPELLIDOS, stdin);
        usuarioTemp.apellidos[strcspn(usuarioTemp.apellidos, "\n")] = '\0';
        
        do{
            printf("Ingrese el dni del usuario #%zu: ", indice+1);
            scanf("%lld", &dni);
            getchar();
        }   while(dni < 10000000 || dni > 99999999);
        usuarioTemp.dni = dni;

        printf("Ingrese el saldo del usuario #%zu: ", indice+1);
        scanf("%f", &usuarioTemp.saldo);
        getchar();

        if(fwrite(&usuarioTemp, sizeof(usuario), 1, data) != 1) {
            printf("Hubo un error al registrar al usuario #%zu\n", indice+1);
        }
    }

    puts("Usuarios agregados correctamente!");
    fclose(data);

    return 0;
}