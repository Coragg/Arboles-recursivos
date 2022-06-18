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

ABO procesarLinea(ABO arbol, char linea[L])
{
  char *trozo;
  int rut;
  char nameAndLastName[NAME];
  int cantidad;
  trozo = strtok(linea, ",");
  rut = atoi(trozo);
  trozo = strtok(NULL, ",");
  strcpy(nameAndLastName, trozo);
  trozo = strtok(NULL, ",");
  cantidad = atoi(trozo);
  arbol = insertarDataEnArbolBinarioOrdenado(arbol, rut, cantidad);
}

void readFile(char nameFile[NAME])
{
  FILE *openFile = fopen(nameFile, "r");
  char linea[L];
  int len;
  ABO tree = NULL;

  if (openFile == NULL)
  {
    printf("el archivo no se pudo abrir, revise su ubicacion.");
    exit(1);
  }
  while (feof(openFile) == 0)
  {
    fgets(linea, L, openFile);
    len = strlen(linea);
    if (linea[len - 1] == '\n')
      linea[len - 1] = '\0';

    if (strlen(linea) == 0)
      break;

    tree = procesarLinea(tree, linea);
  }
  fclose(openFile);
  generarSalida(tree);
}

int main()
{
  system("cls");
  system("color 2");
  char nameFile[NAME];
  printf("Ingrese el nombre del archivo: ");
  gets(nameFile);
  readFile(nameFile);

  return 0;
}
