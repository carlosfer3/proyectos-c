#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "usuarios.h"

int main(void) {
    FILE* data;
    nodo* cabeza = NULL;
    nodo* actual = NULL;

    size_t operacion;
    ll dni;

    usuario usuario_0;

    data = fopen("src/proyecto-cajero/usuarios.dat", "rb+");
    if(data == NULL) {
        data = fopen("src/proyecto-cajero/usuarios.dat", "wb+");
    }

    leerdatabase(data, &cabeza);
    srand(time(NULL));

    do {
        puts("OPERACION 1: VER BASE DE DATOS.");
        puts("OPERACION 2: AGREGAR USUARIO.");
        puts("OPERACION 3: EDITAR USUARIO.");
        puts("OPERACION 4: ELIMINAR USUARIO.");
        puts("OPERACION 5: SALIR.\n");
        printf("Ingrese una de las opciones: ");
        scanf("%zu", &operacion);
        getchar();

        switch(operacion) {
            case 1:
                printf("\n\n");
                verUsuarios(cabeza);
                printf("\n\n");

                break;
            case 2:
                dni = solicitarDNI();
                
                if(convalidar_dni(cabeza, dni)) {
                    printf("Ya se ingreso un usuario con ese dni\n");
                    break;
                }

                usuario_0 = crearUsuario(dni);
                registrarUsuario(data, &cabeza, usuario_0);

                break;
            case 3:
                dni = solicitarDNI();

                if(convalidar_dni(cabeza, dni) == false) {
                    printf("Usuario con dni %lld no encontrado\n", dni);
                    break;
                }

                editarUsuario(data, &cabeza, dni);
                break;
            case 4:
                dni = solicitarDNI();

                if(convalidar_dni(cabeza, dni) == true) {
                    eliminarUsuario(data, &cabeza, dni);
                    data = fopen("src/proyecto-cajero/usuarios.dat", "rb+");
                }   else{
                    printf("Usuario con dni %lld no encontrado\n", dni);
                }

                break;
            case 5:
                fclose(data);
                printf("VUELVA PRONTO!\n");

                break;
            default:
                puts("Debe de ingresar una operacion valida!");
                break;
        }
    }   while(operacion != 5);

    puts("Saliendo de intranet del banco.\n");

    return 0;
}