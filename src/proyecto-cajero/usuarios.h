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

//funciones generales
int aleatorio(int inferior, int superior);
void leerdatabase(FILE* data, nodo** cabeza);
nodo* crearNodo(usuario usser);
ll generarTarjeta();
ll solicitarDNI();
void buscarUsuario(nodo** actual, ll dni);
bool convalidar_dni(nodo* cabeza, ll dni);
usuario crearUsuario(ll dni);

//funciones de intranet
void verUsuarios(nodo* cabeza);
void registrarUsuario(FILE* data, nodo**cabeza, usuario usuario_0);
void editarUsuario(FILE* data, nodo** cabeza, ll dni);
void eliminarUsuario(FILE* data, nodo** cabeza, ll dni);

//funciones de banco


//funciones de cajero
void buscarUsuarioT(nodo** actual, ll tarjeta);

#endif