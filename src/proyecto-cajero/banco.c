#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "usuarios.h"

int main(void) {
    FILE* data;
    nodo* cabeza;
    nodo* actual;

    size_t operacion;
    ll dni;

    usuario usuario_0;

    data = fopen("src/proyecto-cajero/usuarios.dat", "rb+");
    if(data == NULL) {
        data = fopen("src/proyecto-cajero/usuarios.dat", "wb+");
    }

    leerdatabase(data, &cabeza);

    do {
        puts("OPERACION 1: VER BASE DE DATOS.");
        puts("OPERACION 2: AGREGAR USUARIO.");
        puts("OPERACION 3: EDITAR USUARIO.");
        puts("OPERACION 4: ELIMINAR USUARIO.");
        puts("OPERACION 5: SALIR.\n");
        puts("Ingrese una de las opciones: ");
        scanf("%zu", operacion);
        getchar();

        switch(operacion) {
            case 1:
                printf("\n\n");
                verUsuarios(cabeza);
                printf("\n\n");

                break;
            case 2:
                printf("Ingrese el dni: ");
                scanf("%lld", &dni);
                getchar();

                if(convalidar_dni) {
                    printf("Ya se ingreso un usuario con ese dni\n");
                    break;
                }

                usuario_0 = crearUsuario(dni);
                registrarUsuario(data, &cabeza, usuario_0);

                break;
            case 3:
                printf("Ingrese el dni: ");
                scanf("%lld", &dni);
                getchar();

                actual = cabeza;
                buscarUsuario(&actual, dni);

                if(actual == NULL) {
                    printf("No se ha registrado a un usuario con ese dni\n");
                    break;
                }
                usuario_0 = actual->_usuario;

                printf("DATOS DEL USUARIO CON DNI %lld \n", usuario_0.dni);
                printf("1. Nombres: %s\n", usuario_0.nombres);
                printf("2. Apellidos: %s\n", usuario_0.apellidos);
                printf("3. Numero de tarjeta: %lld\n", usuario_0.nroTarjeta);
                printf("4. Clave: %d\n", usuario_0.clave);
                printf("5. Saldo: %10.2f\n", usuario_0.saldo);
                printf("6. Estado: %s\n", usuario_0.bloqueado ? "bloqueado" : "no bloqueado");
                printf("Ingrese la opcion: ");

                editarUsuario(data, &usuario_0);
                actual->_usuario = usuario_0;
                printf("Usuario editado correctamente!\n");

                break;
            case 4:
                
            case 5:
                break;
            default:
                puts("Debe de ingresar una operacion valida!");
                break;
        }
    }   while(operacion != 5);

    puts("Saliendo de banco.\n");

    return 0;
}