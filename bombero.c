#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bombero.h"

typedef struct Bombero Bombero;
typedef struct Dias Dias;

struct Bombero
{
    char *rut;
    char *nombre;
    int disponible[7];
    int diasDeTrabajo;
};
// 0 = lunes; 1 = martes; 2 = miercoles; 3 = jueves; 4 = viernes; 5 = sabado; 6 = domingo

struct Dias
{
    List *lunes;
    List *martes;
    List *miercoles;
    List *jueves;
    List *viernes;
    List *sabado;
    List *domingo;
};

int retornarDisponibleToInt(char *sino)
{
    if (strcmp(sino, "SI") == 0) return 1;
    else return 0;
}

Dias *crearSemana()
{
  Dias *dias = (Dias*)malloc(sizeof(Dias));
  dias->lunes = createList();
  dias->martes = createList();
  dias->miercoles = createList();
  dias->jueves = createList();
  dias->viernes = createList();
  dias->sabado = createList();
  dias->domingo = createList();
  return dias;
}

//Funcion para leer el k-esimo elemento de un string (separado por comas)
const char *get_csv_field (char * tmp, int k) 
{
  int open_mark = 0;
  char* ret=(char*) malloc (100*sizeof(char));
  int ini_i=0, i=0;
  int j=0;
  while(tmp[i+1]!='\0') {
    if(tmp[i] == '\"') {
      open_mark = 1-open_mark;
      if(open_mark) ini_i = i+1;
        i++;
        continue;
      }
      if(open_mark || tmp[i]!= ',') {
          if(k==j) ret[i-ini_i] = tmp[i];
            i++;
          continue;
      }
        if(tmp[i]== ',') {
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }
      i++;
    }
    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }

  return NULL;
}

Bombero *crearBombero(char *linea)
{
  Bombero *bombero = (Bombero*)malloc(sizeof(Bombero));
  bombero->rut = (char*) malloc(sizeof(char) * 11);
  bombero->nombre = (char*) malloc(sizeof(char) * 20);
  bombero->diasDeTrabajo = 0;
//traspaso de datos a bombero
  for (int i = 0; i < 9; i++) 
  {
    if ( i == 0 ) 
      strcpy(bombero->rut, (char*)get_csv_field(linea, i));
    if ( i == 1 )
       strcpy(bombero->nombre, (char*)get_csv_field(linea, i));
    if ( i > 1 ) 
      bombero->disponible[i - 2] = retornarDisponibleToInt((char*)get_csv_field(linea, i));
  }
  return bombero;
}
//Comprueba respuesta de diponibilidad
char* comprobarSINO(char *dia)
{ 
  char* res = (char*) malloc(sizeof(char) * 3); 
  printf("%s: ", dia);
  scanf("%s", res);
  while (1) 
  {
    if ( strcmp(res, "SI") == 0 || strcmp(res, "NO") ==0) break;
    else printf("Responda con un SI o un NO\n");
    scanf("%s", res);
  }
  return res;
}

char *diaToPrint(int i)
{
  if (i == 0) return "LUNES";
  if (i == 1) return "MARTES";
  if (i == 2) return "MIERCOLES";
  if (i == 3) return "JUEVES";
  if (i == 4) return "VIERNES";
  if (i == 5) return "SABADO";
  if (i == 6) return "DOMINGO";
  return NULL;
}

void agregarBombero(List *bomberos)
{
  char* nuevaLinea = (char*) malloc(sizeof(char) * 65); 
  char* nombre = (char*) malloc(sizeof(char) * 20);
  char* apellido = (char*) malloc(sizeof(char) * 20);
  char* rut = (char*) malloc(sizeof(char)* 11);
  char* respuesta;

//para agregar el bombero se va creando una linea que contenga sus datos
  printf("Ingrese rut:");
  scanf("%s", rut);
  strcpy(nuevaLinea, rut);
  strcat(nuevaLinea, ",");

  printf("Ingrese nombre:");
  scanf("%s%s", nombre, apellido);
  strcat(nuevaLinea, nombre);
  strcat(nuevaLinea, " ");
  strcat(nuevaLinea, apellido);
  strcat(nuevaLinea, ",");

//se usa un linea para retornar los datos de la disponibilidad
  printf("Ingrese disponibilidad:\n");
  for (int i = 0; i < 7; i++)
  {
    respuesta = comprobarSINO(diaToPrint(i));
    strcat(nuevaLinea, respuesta);
    strcat(nuevaLinea, ",");
  }
  pushBack(bomberos, crearBombero(nuevaLinea));
}

void mostrarBomberos(List* bomberos) 
{
  Bombero* temp = firstList(bomberos);
  printf("%3cRUT",32);
  printf("%15cNOMBRE", 32);
  printf("%8cDISPONIBILIDAD\n",32);
  do { 
    if ( strlen(temp->rut) == 9 ) printf(" %s",temp->rut);
      else printf("%s", temp->rut);
    printf("%20s    ", temp->nombre);
    
    
    printf("[");
    for ( int i = 0 ; i < 7 ; i++ ) {
      printf("%i ", temp->disponible[i]);
    }
    printf("]\n");
    
    temp = nextList(bomberos);
  } while( temp != NULL );
}

Bombero *returnEnListaConRut(List *bomberos, char *rut)
{
  Bombero *aux = firstList(bomberos);
  if (aux == NULL) return NULL;

  while (aux != NULL) 
  {
    if (strcmp(aux->rut, rut) == 0) return aux;
    aux = nextList(bomberos);
  }

  return NULL;
}

void eliminarDeListaDeDias(Dias *dias, int i, Bombero *bomberoAEliminar)
{
  List *diaAEliminar;
    
  if (i == 0) diaAEliminar = dias->lunes;
  if (i == 1) diaAEliminar = dias->martes;
  if (i == 2) diaAEliminar = dias->miercoles;
  if (i == 3) diaAEliminar = dias->jueves;
  if (i == 4) diaAEliminar = dias->viernes;
  if (i == 5) diaAEliminar = dias->sabado;
  if (i == 6) diaAEliminar = dias->domingo;

  Bombero *aux = returnEnListaConRut(diaAEliminar, bomberoAEliminar->rut);
  if (aux == NULL) return;
  popCurrent(diaAEliminar);
}

void eliminarBomberos(List* bomberos, Dias* semana) 
{
  char rut[11];

  printf("Ingrese rut:");
  scanf("%s", rut);

  Bombero *aux = returnEnListaConRut(bomberos, rut);
  if (aux == NULL)
  {
    printf("RUT ingresado no existente!. Por favor intente nuevamente.\n");
    return;
  }

  if (strcmp(aux->rut, rut) == 0) 
  {
    for (int i = 0 ; i < 7 ; i++)
    {
        eliminarDeListaDeDias(semana, i, aux);
    }

    popCurrent(bomberos);

    printf("----------------------------------------\n");
    printf("%10c BOMBERO ELIMINADO\n", 32);
    printf("----------------------------------------\n");
  }
  else printf("Bombero no encontrado, intente nuevamente");

  printf("Por favor, si ya generó el horario, regenere para que los cambios surtan efecto.\n");
  printf(" \n");;
}

Bombero *retornaBomberoPorRutScanf(List *bomberos)
{
  char* rut = (char*) malloc(sizeof(char));
  Bombero* aux = firstList(bomberos);

  scanf("%s", rut);
  while (aux != NULL) 
  {
    if (strcmp(aux->rut, rut) == 0) return aux;
    aux = nextList(bomberos);
  }

  return NULL;
}

void buscarRut(List* bomberos)
{
  printf("Ingrese el rut del bombero a desplegar: ");
  Bombero* aux = retornaBomberoPorRutScanf(bomberos);
  if (aux == NULL)
  {
    printf("RUT ingresado no existente!. Por favor intente nuevamente.\n");
    return;
  }

  printf("%3CRUT",32);
  printf("%12CNOMBRE",32);
  printf("%12cDISPONIBILIDAD\n",32);
   if ( strlen(aux->rut) == 9 ) printf(" %s",aux->rut);
      else printf("%s", aux->rut);
  printf("      %s    ", aux->nombre);
  printf("[");
  for ( int i = 0 ; i < 7 ; i++ ) {
    printf("%i ", aux->disponible[i]);
  }
  printf("]\n");
}

int retornarDiaActualInt(char *dia)
{
  if (strcmp(dia, "LUNES") == 0) return 0;
  if (strcmp(dia, "MARTES") == 0) return 1;
  if (strcmp(dia, "MIERCOLES") == 0) return 2;
  if (strcmp(dia, "JUEVES") == 0) return 3;
  if (strcmp(dia, "VIERNES") == 0) return 4;
  if (strcmp(dia, "SABADO") == 0) return 5;
  if (strcmp(dia, "DOMINGO") == 0) return 6;

  return -1;
}
//encuentra los bomberos por dia
void buscarPorDia(List *bomberos)
{
  char* dia = (char*) malloc(sizeof(char) * 10);
  printf("--------------------------------------------------\n");
  printf("Ingrese el dia para buscar bomberos disponibles\n");
  printf("--------------------------------------------------\n");
  printf("%14cINGRESAR EN MAYUSCULAS\n",32);
  printf("--------------------------------------------------\n");
  //se encuentran y retornan los datos del dia leido
  scanf("%s", dia);
  int diaActual = retornarDiaActualInt(dia);

  Bombero *aux = firstList(bomberos);
  printf("%3CRUT",32);
  printf("%12CNOMBRE",32);
  printf("\n");
  while (aux != NULL)
  {
    if (aux->disponible[diaActual] == 1)
    {
      if ( strlen(aux->rut) == 9 ) printf(" %s",aux->rut);
        else printf("%s", aux->rut);
      printf("%s    \n", aux->nombre);
    }
    aux = nextList(bomberos);
  }
  printf(" \n");
}

void modificarDisponibilidad(List *bomberos, Dias *semana)
{
  printf("Ingrese RUT de bombero a modificar: ");
  Bombero *bomberoAModificar = retornaBomberoPorRutScanf(bomberos);
  if (bomberoAModificar == NULL)
  {
    printf("RUT ingresado no existente!. Por favor intente nuevamente.\n");
    return;
  }

  char* respuesta;
  printf("Ingrese nueva disponibilidad:\n");
  for (int i = 0; i < 7; i++)
  {
    // Lee la nueva disponibilidad con la Funcion comprobarSINO y comprueba que sea SI o NO
    respuesta = comprobarSINO(diaToPrint(i));

    // Cambia la disponibilidad del bombero a modificar
    if (strcmp(respuesta, "SI") == 0) bomberoAModificar->disponible[i] = 1;
    else
    {
      eliminarDeListaDeDias(semana, i, bomberoAModificar);
      bomberoAModificar->disponible[i] = 0;
    }
  }

  printf("Por favor, si ya generó el horario, regenere para que los cambios surtan efecto.\n");
}

void comprobarSiEstaEnLista(List *dia, Bombero *bombero)
{
  // Retorna un dato si el bombero ingresado esta en la lista y NULL si no.
  Bombero *aux = returnEnListaConRut(dia, bombero->rut);
  // Si no esta en la lista lo agrega y comprueba que la lista del dia sea menor a 5
  if (aux == NULL && listSize(dia) < 5)
  {
    // Si los dias trabajados del bombero son menores a 5 se agregan a la lista
    if (bombero->diasDeTrabajo < 5)
    {
      pushBack(dia, bombero);
      bombero->diasDeTrabajo += 1;
    }
  }
}

void agregarADia(Bombero *bombero, int i, Dias *dias)
{
  // i es el dia de 0 a 6, lunes a domingo
  if (i == 0) comprobarSiEstaEnLista(dias->lunes, bombero);
  if (i == 1) comprobarSiEstaEnLista(dias->martes, bombero);
  if (i == 2) comprobarSiEstaEnLista(dias->miercoles, bombero);
  if (i == 3) comprobarSiEstaEnLista(dias->jueves, bombero);
  if (i == 4) comprobarSiEstaEnLista(dias->viernes, bombero);
  if (i == 5) comprobarSiEstaEnLista(dias->sabado, bombero);
  if (i == 6) comprobarSiEstaEnLista(dias->domingo, bombero);
}

void generarHorarioSemanal(List *bomberos, Dias *dias)
{
  Bombero *bombero = firstList(bomberos);
  // Se recorre la lista de bomberos
  while (bombero != NULL)
  {
    for (int i = 0; i < 7; i++) // Y dia por dia
    {
      // si esta disponible, se intenta agregar a la lista
      if (bombero->disponible[i] == 1) agregarADia(bombero, i, dias);
    }
    bombero = nextList(bomberos);
  }
  printf("Horario semanal generado!\n");
}

List *retornarDias(int i, Dias *dias)
{
  if (i == 0) return dias->lunes;
  if (i == 1) return dias->martes;
  if (i == 2) return dias->miercoles;
  if (i == 3) return dias->jueves;
  if (i == 4) return dias->viernes;
  if (i == 5) return dias->sabado;
  if (i == 6) return dias->domingo;
  return NULL;
}

void mostrarHorarioSemanal(Dias *dias)
{
  if (firstList(dias->lunes) == NULL)
  {
    printf("--------------------------------------------------\n");
    printf("    El horario semanal aun no esta generado!\n");
    printf("--------------------------------------------------\n");
    return;
  }

  List *diaActual;
  Bombero *aux;

  printf("----------------------------------------\n");
  printf("%15cHORARIO\n",32);

  for (int i = 0; i < 7; i++)
  {
    diaActual = retornarDias(i, dias);

    printf("----------------------------------------\n");
    printf("%20s\n", diaToPrint(i));
    printf("----------------------------------------\n");
    printf("%3cRUT", 32);
    printf("%12CNOMBRE\n",32);

    aux = firstList(diaActual);
    while (aux != NULL)
    {
      if ( strlen(aux->rut) == 9 ) printf(" %s",aux->rut);
        else printf("%s", aux->rut);
      printf("      %s    \n", aux->nombre);
      aux = nextList(diaActual);
    }
  }
  printf("----------------------------------------\n");
}