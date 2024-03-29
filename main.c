/* Sofia Castro (21042213-7) NRC: 8490 y Victor Camero(25833773-5) NRC: 8489, 
Profesora: Irene Zuccar, Fecha: 20/06/2022 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Constantes globales */
#define NAME 60
#define LINEA 3000

/* Aqui es donde ve el tipo de dato y genera el puntero para poder recorrer el arbol */
struct nodo
{
  int rut;
  int cantidad;
  struct nodo *izquierda;
  struct nodo *derecha;
};
typedef struct nodo tNodo;
typedef tNodo *ABO;

/* Aqui es donde se guardan los datos de rut y cantidad de boletos en el arbol*/
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

/* Aqui es  para escribir la informacion del archivo procesado recibiendo 
el tipo de archivo y el nodo donde se va a escribir la informacion*/
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

/* Aqui es donde genera el archivo de salida con los datos finales */
void generarSalida(ABO tree)
{
  char fileName[60];
  printf("Ingrese el nombre del archivo de salida: ");
  gets(fileName);
  FILE *openFile;
  openFile = fopen(fileName, "w");
  escribirArchivo(tree, openFile);
  fclose(openFile);
}

/* Aqui es donde analiza los datos entregados y los ordena */
ABO insertarDataEnArbolBinarioOrdenado(ABO arbolBinarioOrdenado, int rut, int cantidad)
{
  if (arbolBinarioOrdenado == NULL)
    arbolBinarioOrdenado = crearNodo(rut, cantidad);
  else
  {
    if (rut < arbolBinarioOrdenado->rut)
      arbolBinarioOrdenado->izquierda = insertarDataEnArbolBinarioOrdenado(arbolBinarioOrdenado->izquierda, rut, cantidad);
    else
    {
      if (rut == arbolBinarioOrdenado->rut)
        arbolBinarioOrdenado->cantidad += cantidad;
      else
        arbolBinarioOrdenado->derecha = insertarDataEnArbolBinarioOrdenado(arbolBinarioOrdenado->derecha, rut, cantidad);
    }
  }
  return arbolBinarioOrdenado;
}

/* Aqui se define los tipos de datos que hay en el archivo de lectura */
ABO procesarLinea(ABO arbol, char linea[LINEA])
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

/* Aqui lee el archivo viendo el largo y rescatando el rut y las entradas, 
como recibiendo el archivo */
void readFile(char nameFile[NAME])
{
  FILE *openFile = fopen(nameFile, "r");
  char linea[LINEA];
  int len;
  ABO tree = NULL;

  if (openFile == NULL)
  {
    printf("el archivo no se pudo abrir, revise su ubicacion.");
    exit(1);
  }
  while (fgets(linea, LINEA, openFile))
  {
    
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

/* Aqui es donde se ejecuta el programa  */
int main()
{
  char nameFile[NAME];
  printf("Ingrese el nombre del archivo: ");
  gets(nameFile);
  readFile(nameFile);

  return 0;
}

