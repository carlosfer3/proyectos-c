#include <stdio.h>
#include <stdlib.h>

#include "usuarios.h"

int main(void) {
    FILE* data;
    nodo *cabeza = NULL;

    data = fopen("src/proyecto-cajero/usuarios.dat", "rb+");
    if(data == NULL) {
        data = fopen("src/proyecto-cajero/usuarios.dat", "wb+");
    }

    leerdatabase(data, &cabeza);

    system("pause");
    return 0;
}