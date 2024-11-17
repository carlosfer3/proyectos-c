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

    indice = 1;
    while(cabeza != NULL) {
        printf("Usuario #%zu\n", indice);
        printf("Nombres: %s\n", cabeza->_usuario.nombres);
        printf("Apellidos: %s\n", cabeza->_usuario.apellidos);
        printf("DNI: %lld\n", cabeza->_usuario.dni);
        printf("Numero de tarjeta: %lld\n", cabeza->_usuario.nroTarjeta);
        printf("Clave: %d\n", cabeza->_usuario.clave);
        printf("Saldo: %10.2f\n", cabeza->_usuario.saldo);
        printf("Estado: %s\n\n", cabeza->_usuario.bloqueado ? "bloqueado":"no bloqueado");
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
void editarUsuario(FILE* data, usuario* usuario_0) {
    size_t opcion;
    int longitud;
    int clave;
    int posicion;
    usuario usuariotemp;

    scanf("%zu", &opcion);
    getchar();

    switch(opcion) {
        case 1:
            printf("Ingrese los nombres: ");
            fgets(usuario_0->nombres, LENGTHNOMBRES, stdin);
            longitud = strlen(usuario_0->nombres);

            if(usuario_0->nombres[longitud - 1] == '\n') {
                usuario_0->nombres[longitud - 1] = '\0';
            }

            break;
        case 2:
            printf("Ingrese los apellidos: ");
            fgets(usuario_0->apellidos, LENGTHAPELLIDOS, stdin);
            longitud = strlen(usuario_0->apellidos);

            if(usuario_0->apellidos[longitud - 1] == '\n') {
                usuario_0->apellidos[longitud - 1] = '\0';
            }

            break;
        case 3:
            usuario_0->nroTarjeta = generarTarjeta();
            break;
        case 4:
            do{
                printf("Ingrese su nueva clave (4 digitos): ");
                scanf("%d", &clave);
                getchar();
            }   while(clave < 1000 || clave > 9999);

            usuario_0->clave = clave;
            break;
        case 5:
            printf("Ingrese el nuevo saldo: ");
            scanf("%f", &(usuario_0->saldo));
            getchar();

            break;
        case 6:
            usuario_0->bloqueado = !(usuario_0->bloqueado);
            break;
        default:
            printf("No ingreso una operacion disponible\n");
            return;
    }

    while(fread(&usuariotemp, sizeof(usuario), 1, data) == 1) {
        if(usuariotemp.dni == usuario_0->dni) {
            posicion = ftell(data) - sizeof(usuario);
            break;
        }
    }

    fseek(data, posicion, SEEK_SET);
    if(fwrite(&(*usuario_0), sizeof(usuario), 1, data) != 1) {
        printf("No se pudo actualizar al usuario en la base de datos\n");

        return;
    }
}
void eliminarUsuario(FILE* data, nodo** cabeza, usuario usuario_0) {
    nodo* anterior = NULL;
    nodo* actual = *cabeza;
    data = freopen("src/proyecto-cajero/usuarios.dat", "wb+", data);

    while(actual != NULL) {
        if(actual->_usuario.dni != usuario_0.dni) {
            if(fwrite(&(actual->_usuario), sizeof(usuario), 1, data) != 1) {
                printf("Error al eliminar usuario\n");

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