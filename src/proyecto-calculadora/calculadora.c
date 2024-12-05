#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void interfaz();
void panel(float numero);

int main(void) {
    panel(0);
    interfaz();

    system("pause");
    return 0;
}

void interfaz() {
    puts(" ----------------------------------------------- ");
    puts("|\t7\t8\t9\tDEL\tAC\t|");
    puts("|\t4\t5\t6\tX\t/\t|");
    puts("|\t1\t2\t3\t+\t-\t|");
    puts("|\t\t0\t\tANS\t=\t|");
    puts(" ----------------------------------------------- ");
}
void panel(float numero) {
    puts(" ----------------------------------------------- ");
    printf("|\t\t\t\t\t%.1f\t|\n", numero);
    puts(" ----------------------------------------------- ");
}