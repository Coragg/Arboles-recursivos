#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FALSE false
#define NAME 45
#define RUT 12
#define NAME_SUR 100
bool True = true;
bool False = false;
struct nodo{
    char rut[RUT];
    char nameAndSurname[NAME_SUR];
    int tickets;

};

void createNodo(char rut[RUT], char nameAndSurname[NAME_SUR], int tickets){



}

bool ticketPenalty(int ticket){
  if (ticket >= 1 && ticket <= 2){
    return True;
  } else {
    return False;
  }
}

void readFile(char nameFile[]){
    FILE *openFile = fopen(nameFile, "r");





    fclose(openFile);
}





int main() {
    char nameFile[NAME];
    printf("Ingrese el nombre del archivo: ");
    gets(nameFile);
    readFile(nameFile);
    return 0;
}