#ifndef USUARIOS_H
#define USUARIOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LENGTHNOMBRES 30
#define LENGTHAPELLIDOS 40

typedef long long ll;

typedef struct Usuario{
    char nombres[LENGTHNOMBRES];
    char apellidos[LENGTHAPELLIDOS];
    ll dni;
    ll nroTarjeta;
    int clave;
    float saldo;
    bool bloqueado;
}   usuario;

typedef struct Nodo{
    usuario _usuario;
    struct Nodo* siguiente;
}   nodo;

int aleatorio(int inferior, int superior);
void leerdatabase(FILE* data, nodo** cabeza);
nodo* crearNodo(usuario usser);
void verUsuarios(nodo* cabeza);
bool convalidar_dni(nodo* cabeza, ll dni);
usuario crearUsuario(ll dni);
void registrarUsuario(FILE* data, nodo**cabeza, usuario usuario_0);
void buscarUsuario(nodo** actual, ll dni);
void editarUsuario(FILE* data, usuario* usuario_0);
void eliminarUsuario(FILE* data, nodo** cabeza, usuario usuario_0);
ll generarTarjeta();

#endif