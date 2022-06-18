//INCLUYE LIBRERIAS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// DEFINIR VARIABLES O CONSTANTES
#define A 45
#define Rut 12
#define Nom 60
#define Linea 300000
//GUARDADO DE INFORMACIÓN EN EL NODO USANDO LISTA DINÁMICA
struct LollaPalooza{
  char rut[Rut];
  char nameAndLastName[Nom];
  int tickets;
  struct LollaPalooza *sig;
};
typedef struct LollaPalooza tNodo;
typedef tNodo *ListaParticipantes;
// FUNCION CREA NODO CON LOS DATOS NECESARIOS QUE DEBE RECIBIR COMO PARAMETRO
ListaParticipantes createNodo(char rut[Rut], char nameAndLastName[Nom], unsigned short tickets){
  ListaParticipantes auxiliary;
  auxiliary = malloc(sizeof(tNodo));
  if(auxiliary != NULL) {
    strcpy(auxiliary->rut, rut);
    strcpy(auxiliary->nameAndLastName, nameAndLastName);
    auxiliary->tickets = tickets;
    auxiliary->sig = NULL;
  } else {
    printf("\n\tERROR: No hay memoria suficiente para generar un nuevo Nodo.");
    printf("\n\tEste programa se cerrar%c.", 160);
    exit(1);
  }
  return auxiliary;
}
//INSERTAR DATOS EN EL NODO
ListaParticipantes insertFinal(ListaParticipantes Large, char rut[Rut], char nameAndLastName[Nom], int tickets){
  ListaParticipantes pNodo, auxiliary;
  pNodo = createNodo(rut, nameAndLastName, tickets);
  if(Large == NULL) {
    Large = pNodo;
  } else {
    auxiliary = Large;
    while(auxiliary->sig != NULL)
      auxiliary = auxiliary->sig;
    auxiliary->sig = pNodo;
    auxiliary = NULL;
  }
  pNodo = NULL;
  return Large;
}
// Penalizar en base de la cantidad de entradas que se pidieron
short ticketPenalty(int ticket){
  if (ticket >= 1 && ticket <= 2){
    return ticket;
  } else if(ticket >= 3 && ticket <= 7){
    return 2;
  } else if(ticket >= 8 && ticket <= 15) {
    return 1;
  } else {
    return 0;
  }
}
// ACTUALIZA LOS DATOS PARA QUE TENGAN LA PENALIZACION APLICADA
ListaParticipantes updateData(ListaParticipantes L){
  ListaParticipantes aux;
  aux = L;
  while(aux != NULL){
    aux->tickets = ticketPenalty(aux->tickets);
    aux = aux->sig;
  }
  return L;
}
// BUSCA LOS RUTS DUPLICADOS
int localizarElemento(ListaParticipantes L, char rut_search[Rut]){
  ListaParticipantes aux;
  int i;
  aux = L;
  i = 1;
  while (aux != NULL) {
    if (strcmp(aux->rut, rut_search) == 0) {
      return i; //Dato encontrado
    }
    aux = aux->sig;
    i++;
  }
  return -1; //Dato no encontrado
}
// BUSCA UN RUT DUPLICADO EN LA LISTA Y LE SUMA LOS TICKETS QUE TENGA EL USUARIO
ListaParticipantes actualizaPosicion(ListaParticipantes L, int posicion, int ticket) {
    ListaParticipantes aux;
    int i;
    aux = L;
    i = 1;
    while (i < posicion) {
        aux = aux->sig;
        i = i+1;
    }
    aux->tickets = aux->tickets + ticket;
    aux = NULL;
    return L;
}
// procesamos los datos en el archivo para generar los datos que seran enviados al nodo
ListaParticipantes procesarLinea(ListaParticipantes L, char linea[Linea]){
  char *trozo;
  char rut[Rut];
  char nameAndLastName[Nom];
  unsigned short ticket;
  int posicion;
  trozo = strtok(linea, ",");
  strcpy(rut, trozo);
  trozo = strtok(NULL, ",");
  strcpy(nameAndLastName, trozo);
  trozo = strtok(NULL, ",");
  ticket = atoi(trozo);
  posicion = localizarElemento(L, rut);
  if(posicion == -1){  
    L = insertFinal(L, rut, nameAndLastName, ticket);
  } else if(posicion != -1) {
    L = actualizaPosicion(L, posicion, ticket);
  } 
  return L;
}
/* // CAMBIA EL FORMATO DE ARCHIVO A .SAL
void cambiarSal(char nameFile[A], char newName[A]){
  char *token = strtok(nameFile, ".");
  strcpy(newName, token);
  strcat(newName, ".sal");
}
//CREA Y ESCRIBE EL ARCHIVO.SAL
void createFile(ListaParticipantes L,char name[A]){
    ListaParticipantes auxiliar;
    FILE *abrirArchivo;
    int asignados = 0;
    int pendientes;
    abrirArchivo = fopen(name, "w");
    if(abrirArchivo == NULL){
        printf("No se puede abrir el archivo %s", name);
        exit(1);
    }
    auxiliar = L;
    while(auxiliar != NULL)    {
        if(auxiliar->tickets > 0){
          fprintf(abrirArchivo, "%s,%s,%i",auxiliar->rut, auxiliar->nameAndLastName, auxiliar->tickets);
          fprintf(abrirArchivo, "\n");
          asignados = asignados + auxiliar->tickets;
        } 
        auxiliar = auxiliar->sig;
    }
  fprintf(abrirArchivo, "Asignadas: %i ", asignados );
  pendientes = 200 - asignados;
  fprintf(abrirArchivo, "\nPendientes: %i", pendientes);
  fclose(abrirArchivo);
} */
/*
Esta funcion nos genera  la lectura del archivo buscado
mas la impresion y creacion del archivo sal
*/
void readFile(char nameFile[A]){
  FILE *file;
  char line[Linea];
  int len;
  char newName[A];
  ListaParticipantes L = NULL;
  file = fopen(nameFile, "r");
  if(file == NULL){
    printf("No se puede abrir el archivo %s", nameFile);
    exit(1);
  }
  while(feof(file) == 0){
    fgets(line, Linea, file);
    len = strlen(line);
    if (line[len-1] == '\n'){
      line[len-1] = '\0';
    }
    if (strlen(line) == 0){
      break;
    }
    L = procesarLinea(L, line);
  }
  fclose(file);
  L = updateData(L);
  cambiarSal(nameFile, newName);
  createFile(L, newName);
}
//SALIDA DEL PROGRAMA
int main(){
  char nameFile[A];
  printf("Ingrese el nombre del archivo: ");
  gets(nameFile);
  readFile(nameFile);
  return 0;
}