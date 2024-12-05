#include <stdio.h>
#include <stdlib.h>

#include "header.h"

int main(void) {
    FILE* data;
    usuario usuariotemp;
    size_t indice;

    indice = 1;
    data = fopen("src/proyecto-lect-arch/usuarios.dat", "rb");
    if(data == NULL) {
        printf("No se encontro la base de datos!\n");

        return -1;
    }

    while(fread(&usuariotemp, sizeof(usuario), 1, data) == 1) {
        printf("Usuario #%zu\n", indice);
        printf("Nombres: %s\n", usuariotemp.nombres);
        printf("Apellidos: %s\n", usuariotemp.apellidos);
        printf("DNI: %lld\n", usuariotemp.dni);
        printf("Saldo: %.2f\n\n", usuariotemp.saldo);

        indice += 1;
    }

    fclose(data);

    system("pause");
    return 0;
}
