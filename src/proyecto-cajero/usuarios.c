#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "usuarios.h"

int aleatorio(int inferior, int superior) {
    return inferior + rand() % (superior - inferior + 1);
}
void leerdatabase(FILE* data, nodo** cabeza) {
    usuario usuariotemp;
    nodo* actual = NULL;

    while(fread(&usuariotemp, sizeof(usuario), 1, data) == 1) {
        nodo* nodo_nuevo = crearNodo(usuariotemp);
        if(*cabeza == NULL) {
            *cabeza = nodo_nuevo;
            actual = nodo_nuevo;
        }   else {
            actual->siguiente = nodo_nuevo;
            actual = actual->siguiente;
        }
    }
}
nodo* crearNodo(usuario usser) {
    nodo* nodo_nuevo = (nodo*)malloc(sizeof(nodo));
    if(nodo_nuevo == NULL) {
        printf("Error en memoria!\n");

        return NULL;
    }

    nodo_nuevo->_usuario = usser;
    nodo_nuevo->siguiente = NULL;

    return nodo_nuevo;
}
void verUsuarios(nodo* cabeza) {
    size_t indice;
    char usser[] = "Usuario";
    char nombres[] = "Nombres";
    char apellidos[] = "Apellidos";
    char dni[] = "DNI";
    char tarjeta[] = "Num. Tarjeta";
    char clave[] = "Clave";
    char saldo[] = "Saldo";
    char estado[] = "Estado";

    indice = 1;
    printf("%7s\t%20s\t%20s\t%8s\t%16s\t%5s\t%7s\t%13s\n", usser,
                                                            nombres,
                                                            apellidos,
                                                            dni,
                                                            tarjeta,
                                                            clave,
                                                            saldo,
                                                            estado);
    while(cabeza != NULL) {
        puts("-----------------------------------------------------------------------------------------------------------------------------");
        printf("%7zu\t%20s\t%20s\t%8lld\t%16lld\t%5d\t%7.2f\t%13s\n", indice,
                                                                    cabeza->_usuario.nombres,
                                                                    cabeza->_usuario.apellidos,
                                                                    cabeza->_usuario.dni,
                                                                    cabeza->_usuario.nroTarjeta,
                                                                    cabeza->_usuario.clave,
                                                                    cabeza->_usuario.saldo,
                                                                    cabeza->_usuario.bloqueado ? "bloqueado":"no bloqueado");
        indice += 1;

        cabeza = cabeza->siguiente;
    }
}
bool convalidar_dni(nodo* cabeza, ll dni) {
    while(cabeza != NULL) {
        if(cabeza->_usuario.dni == dni) {
            return true;
        }

        cabeza = cabeza->siguiente;
    }

    return false;
}
usuario crearUsuario(ll dni) {
    usuario usuariotemp;
    int longitud;
    int clave;

    printf("Ingrese los nombres: ");
    fgets(usuariotemp.nombres, LENGTHNOMBRES, stdin);

    longitud = strlen(usuariotemp.nombres);
    if(usuariotemp.nombres[longitud - 1] == '\n') {
        usuariotemp.nombres[longitud - 1] = '\0';
    }

    printf("Ingrese los apellidos: ");
    fgets(usuariotemp.apellidos, LENGTHAPELLIDOS, stdin);

    longitud = strlen(usuariotemp.apellidos);
    if(usuariotemp.apellidos[longitud - 1] == '\n') {
        usuariotemp.apellidos[longitud - 1] = '\0';
    }

    usuariotemp.dni = dni;
    usuariotemp.nroTarjeta = generarTarjeta();

    do {
        printf("Ingrese su clave (4 digitos): ");
        scanf("%d", &clave);
        getchar();
    }   while(clave < 1000 || clave > 9999);

    usuariotemp.clave = clave;
    usuariotemp.saldo = 0;
    usuariotemp.bloqueado = false;

    return usuariotemp;
}
void registrarUsuario(FILE* data, nodo** cabeza, usuario usuario_0) {
    nodo* actual = *cabeza;
    nodo* nuevo = crearNodo(usuario_0);

    fseek(data, 0, SEEK_END);

    if(fwrite(&usuario_0, sizeof(usuario), 1, data) != 1) {
        printf("Error al agregar al usuario!");
        return;
    }

    if(*cabeza != NULL) {
        while(actual->siguiente != NULL) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevo;
    }   else{
        *cabeza = nuevo;
        free(actual);
    }

    printf("Se registro correctamente!\n");
}
void buscarUsuario(nodo** actual, ll dni) {
    while(*actual != NULL) {
        if((*actual)->_usuario.dni == dni) {

            return;
        }
        *actual = (*actual)->siguiente;
    }
}
void editarUsuario(FILE* data, nodo** cabeza, ll dni) {
    size_t opcion;
    int longitud;
    int clave;
    int posicion;
    usuario usuariotemp;
    nodo* actual;

    posicion = 0;
    actual = *cabeza;
    if ((*cabeza)->_usuario.dni != dni){ 
        while(actual->_usuario.dni != dni) {
            actual = actual->siguiente;
            posicion++;
        }
    }
    usuariotemp = actual->_usuario;

    printf("DATOS DEL USUARIO CON DNI %lld \n", usuariotemp.dni);
    printf("1. Nombres              : %s\n", usuariotemp.nombres);
    printf("2. Apellidos            : %s\n", usuariotemp.apellidos);
    printf("3. Numero de tarjeta    : %lld\n", usuariotemp.nroTarjeta);
    printf("4. Clave                : %d\n", usuariotemp.clave);
    printf("5. Saldo                : %.2f\n", usuariotemp.saldo);
    printf("6. Estado               : %s\n", usuariotemp.bloqueado ? "bloqueado" : "no bloqueado");
    printf("Ingrese la opcion: ");

    scanf("%zu", &opcion);
    getchar();

    switch(opcion) {
        case 1:
            printf("Ingrese los nombres: ");
            fgets(usuariotemp.nombres, LENGTHNOMBRES, stdin);
            longitud = strlen(usuariotemp.nombres);

            if(usuariotemp.nombres[longitud - 1] == '\n') {
                usuariotemp.nombres[longitud - 1] = '\0';
            }

            break;
        case 2:
            printf("Ingrese los apellidos: ");
            fgets(usuariotemp.apellidos, LENGTHAPELLIDOS, stdin);
            longitud = strlen(usuariotemp.apellidos);

            if(usuariotemp.apellidos[longitud - 1] == '\n') {
                usuariotemp.apellidos[longitud - 1] = '\0';
            }

            break;
        case 3:
            usuariotemp.nroTarjeta = generarTarjeta();
            break;
        case 4:
            do{
                printf("Ingrese su nueva clave (4 digitos): ");
                scanf("%d", &clave);
                getchar();
            }   while(clave < 1000 || clave > 9999);

            usuariotemp.clave = clave;
            break;
        case 5:
            printf("Ingrese el nuevo saldo: ");
            scanf("%f", &(usuariotemp.saldo));
            getchar();

            break;
        case 6:
            usuariotemp.bloqueado = !(usuariotemp.bloqueado);
            break;
        default:
            printf("No ingreso una operacion disponible\n");
            return;
    }

    fseek(data, posicion*sizeof(usuario), SEEK_SET);
    if(fwrite(&usuariotemp, sizeof(usuario), 1, data) != 1) {
        perror("Hubo un error al actualizar los datos en el archivo\n");
        return;
    }

    fflush(data);
    actual->_usuario = usuariotemp;
    printf("Se actualizaron sus datos correctamente!\n");
}
void eliminarUsuario(FILE* data, nodo** cabeza, ll dni) {
    nodo* anterior = NULL;
    nodo* actual = *cabeza;

    data = freopen("src/proyecto-cajero/usuarios.dat", "wb+", data);
    if(data == NULL) {
        perror("Error!");
        return;
    }

    while(actual != NULL) {
        if(actual->_usuario.dni != dni) {
            if(fwrite(&(actual->_usuario), sizeof(usuario), 1, data) != 1) {
                perror("Error!");
                fclose(data);
                return;
            }

            anterior = actual;
            actual = actual->siguiente;
        }   else {
            if(actual == *cabeza) {
                *cabeza = (*cabeza)->siguiente;
                free(actual);
                actual = *cabeza;
            }   else {
                anterior->siguiente = actual->siguiente;
                free(actual);
                actual = anterior->siguiente;
            }
        }
    }

    printf("Usuario eliminado correctamente!\n");
    fflush(data);
    fclose(data);
}
ll generarTarjeta() {
    ll tarjeta;
    size_t indice;

    tarjeta = aleatorio(1, 9);
    for(indice = 0; indice < 15; indice++) {
        tarjeta *= 10;
        tarjeta += aleatorio(0, 9);
    }

    return tarjeta;
}
ll solicitarDNI() {
    ll dni;
    do {
        printf("Ingrese el dni: ");
        scanf("%lld", &dni);
        getchar();
    } while (dni < 10000000 || dni > 99999999);
    return dni;
}