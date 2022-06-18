#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME 60

struct nodo
{
  int rut;
  int cantidad;
  struct nodo *izquierda;
  struct nodo *derecha;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

ABO crearNodo(int rut, int cantidad)
{
  ABO data;

  data = (ABO)malloc(sizeof(tNodo));
  if (data != NULL)
  {
    data->rut = rut;
    data->cantidad = cantidad;
    data->izquierda = NULL;
    data->derecha = NULL;
  }
  else
  {
    printf("\nNo hay memoria suficiente. Este programa se cerrara.");
    exit(1);
  }
  return data;
}
void escribeArchivo(ABO nodoArbol, FILE *archivo)
{
  if (nodoArbol != NULL)
  {
    escribeArchivo(nodoArbol->izquierda, archivo);
    if (nodoArbol->cantidad > 2)
      fprintf(archivo, "%i %i \n", nodoArbol->rut, nodoArbol->cantidad);
    escribeArchivo(nodoArbol->derecha, archivo);
  }
}

void generarSalida(ABO A)
{
  char fileName[60];
  printf("Ingrese el nombre del archivo de salida: ");
  gets(fileName);
  FILE *openFile;
  openFile = fopen(fileName, "w");
  escribeArchivo(A, openFile);

  fclose(openFile);
}

ABO insertaABO(ABO arbolOrdenado, int rut, int cantidad)
{
  if (arbolOrdenado == NULL)
    arbolOrdenado = crearNodo(rut, cantidad);
  else
  {
    if (rut < arbolOrdenado->rut)
      arbolOrdenado->izquierda = insertaABO(arbolOrdenado->izquierda, rut, cantidad);
    else
    {
      if (rut == arbolOrdenado->rut)
        arbolOrdenado->cantidad += cantidad;
      else
        arbolOrdenado->derecha = insertaABO(arbolOrdenado->derecha, rut, cantidad);
    }
  }
  return arbolOrdenado;
}

void readFile(char nameFile[])
{
  FILE *openFile = fopen(nameFile, "r");

  fclose(openFile);
}

int main()
{
  system("color 3");
  char nameFile[NAME];
  printf("Ingrese el nombre del archivo: ");
  gets(nameFile);
  readFile(nameFile);

  ABO A;
  A = NULL;

  A = insertaABO(A, 100, 10);
  A = insertaABO(A, 50, 2);
  A = insertaABO(A, 150, 5);
  A = insertaABO(A, 25, 2);
  A = insertaABO(A, 75, 1);
  A = insertaABO(A, 125, 2);
  A = insertaABO(A, 200, 2);

  A = insertaABO(A, 50, 1);
  A = insertaABO(A, 125, 2);
  A = insertaABO(A, 50, 1);
  A = insertaABO(A, 75, 4);
  A = insertaABO(A, 50, 2);

  generarSalida(A);
  printf("\n");

  return 0;
}
