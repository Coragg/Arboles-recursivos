#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME 60
#define L 300 

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
void escribirArchivo(ABO nodoArbol, FILE *archivo)
{
  if (nodoArbol != NULL)
  {
    escribirArchivo(nodoArbol->izquierda, archivo);
    if (nodoArbol->cantidad > 2)
      fprintf(archivo, "%i %i \n", nodoArbol->rut, nodoArbol->cantidad);
    escribirArchivo(nodoArbol->derecha, archivo);
  }
}

void generarSalida(ABO A)
{
  char fileName[60];
  printf("Ingrese el nombre del archivo de salida: ");
  gets(fileName);
  FILE *openFile;
  openFile = fopen(fileName, "w");
  escribirArchivo(A, openFile);

  fclose(openFile);
}

ABO insertarDataEnArbolBinarioOrdenado(ABO arbolOrdenado, int rut, int cantidad)
{
  if (arbolOrdenado == NULL)
    arbolOrdenado = crearNodo(rut, cantidad);
  else
  {
    if (rut < arbolOrdenado->rut)
      arbolOrdenado->izquierda = insertarDataEnArbolBinarioOrdenado(arbolOrdenado->izquierda, rut, cantidad);
    else
    {
      if (rut == arbolOrdenado->rut)
        arbolOrdenado->cantidad += cantidad;
      else
        arbolOrdenado->derecha = insertarDataEnArbolBinarioOrdenado(arbolOrdenado->derecha, rut, cantidad);
    }
  }
  return arbolOrdenado;
}

void readFile(char nameFile[NAME])
{
  FILE *openFile = fopen(nameFile, "r");
    char linea[L];
    int len;
    ABO tree;
    tree = NULL;
    
    if(openFile == NULL)
    {
        printf("el archivo no se pudo abrir, revise su ubicacion.");
        exit(1);
    }
    while (feof(openFile) == 0)
    {
        fgets(linea, L, openFile);
        printf("%s", linea);
    }
 

  fclose(openFile);

  generarSalida();
}



int main()
{
  system("color 3");
  char nameFile[NAME];
  printf("Ingrese el nombre del archivo: ");
  gets(nameFile);
  readFile(nameFile);

 /*  ABO A;
  A = NULL;

  A = insertarDataEnArbolBinarioOrdenado(A, 25833773, 10);
  A = insertarDataEnArbolBinarioOrdenado(A, 50, 2);
  A = insertarDataEnArbolBinarioOrdenado(A, 150, 5);
  A = insertarDataEnArbolBinarioOrdenado(A, 25, 2);
  A = insertarDataEnArbolBinarioOrdenado(A, 75, 1);
  A = insertarDataEnArbolBinarioOrdenado(A, 125, 2);
  A = insertarDataEnArbolBinarioOrdenado(A, 200, 2);

  A = insertarDataEnArbolBinarioOrdenado(A, 50, 1);
  A = insertarDataEnArbolBinarioOrdenado(A, 125, 2);
  A = insertarDataEnArbolBinarioOrdenado(A, 50, 1);
  A = insertarDataEnArbolBinarioOrdenado(A, 75, 4);
  A = insertarDataEnArbolBinarioOrdenado(A, 50, 2);

  generarSalida(A);
  printf("\n");
 */
  return 0;
}
