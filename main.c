#include <stdio.h>
#include <string.h>

#define NAME 45






int main() {
    char nameFile[NAME];
    printf("Ingrese el nombre del archivo: ");
    gets(nameFile);

    return 0;
}