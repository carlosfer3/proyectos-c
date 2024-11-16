#ifndef HEADER_H
#define HEADER_H

#define MAXNOMBRES 30
#define MAXAPELLIDOS 50

typedef long long ll;

typedef struct Usuario {
    char nombres[MAXNOMBRES];
    char apellidos[MAXAPELLIDOS];
    ll dni;
    float saldo;
}   usuario;

#endif