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

struct nodo
{
  int rut;
  int cantidad;
  struct nodo *izq;
  struct nodo *der;
};
typedef struct nodo tNodo;
typedef tNodo *ArborBinarioOrdenado;
ArborBinarioOrdenado createNodo(int rut, int cantidad)
{
  ArborBinarioOrdenado auxiliar;

  auxiliar = (ArborBinarioOrdenado)malloc(sizeof(tNodo));
  if (auxiliar != NULL)
  {
    auxiliar->rut = rut;
    auxiliar->cantidad = cantidad;
    auxiliar->izq = NULL;
    auxiliar->der = NULL;
  }
  else
  {
    printf("\nNo hay memoria suficiente. Este programa se cerrara.");
    exit(1);
  }
  return auxiliar;
}

void inOrden(ArborBinarioOrdenado Arbol)
{
  if (Arbol != NULL)
  {
    inOrden(Arbol->izq);
    printf("%i(%i) ", Arbol->rut, Arbol->cantidad);
    inOrden(Arbol->der);
  }
}

ArborBinarioOrdenado insertarABO(ArborBinarioOrdenado Arbol, int rut, int cantidad)
{
  if (Arbol == NULL)
    Arbol == createNodo(rut, cantidad);

  else
  {
    if (rut < Arbol->rut)
    {
      Arbol->izq = insertarABO(Arbol->izq, rut, cantidad);
    }
    else if (rut > Arbol)
    {
      if (rut == Arbol->rut)
      {
        Arbol->cantidad = Arbol->cantidad + cantidad;
      }
      Arbol->der = insertarABO(Arbol->der, rut, cantidad);
    }
    return Arbol;
  }
}

void readFile(char nameFile[])
{
  FILE *openFile = fopen(nameFile, "r");

  fclose(openFile);
}

int main()
{
  system("color 3");
/*   char nameFile[NAME];
  printf("Ingrese el nombre del archivo: ");
  gets(nameFile);
  readFile(nameFile); */

  ArborBinarioOrdenado Arbol;

  Arbol = NULL;

  Arbol = insertarABO(Arbol, 100, 1);
  inOrden(Arbol);
  printf("\n\n");

  Arbol = insertarABO(Arbol, 50, 2);
  inOrden(Arbol);
  printf("\n\n");

  Arbol = insertarABO(Arbol, 150, 3);
  inOrden(Arbol);
  printf("\n\n");

  Arbol = insertarABO(Arbol, 25, 4);
  inOrden(Arbol);
  printf("\n\n");

  Arbol = insertarABO(Arbol, 75, 5);
  inOrden(Arbol);
  printf("\n\n");

  Arbol = insertarABO(Arbol, 110, 6);
  inOrden(Arbol);
  printf("\n\n");

  Arbol = insertarABO(Arbol, 30, 7);
  inOrden(Arbol);
  printf("\n\n");

  Arbol = insertarABO(Arbol, 50, 10);
  inOrden(Arbol);
  printf("\n\n");

  return 0;
}
