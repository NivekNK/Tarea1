#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bombero.h"
#include "list.h"

// Imprime las opciones cuando se llama a la funcion
void printOpciones()
{
    printf("1-. Agregar bombero\n");
    printf("2-. Despedir bombero\n");
    printf("3-. Buscar bombero disponible por día\n");
    printf("4-. Buscar bombero por rut\n");
    printf("5-. Modificar disponibilidad\n");
    printf("6-. Generar horario semanal\n");
    printf("7-. Mostrar horario semanal\n");
    printf("8-. Mostrar bomberos de la estación\n");
    printf("0-. Salir\n");
}

// Carga las funciones de las solicitudes
void opciones(int solicitud, List *bomberos, Dias *semana)
{
    switch (solicitud)
    {
        case 1:
          agregarBombero(bomberos);
          break;

        case 2:
          eliminarBomberos(bomberos, semana);
          break;

        case 3:
          buscarPorDia(bomberos);
          break;

        case 4:
          buscarRut(bomberos);
          break;

        case 5:
          modificarDisponibilidad(bomberos, semana);
          break;

        case 6:
          generarHorarioSemanal(bomberos, semana);
          break;

        case 7:
          mostrarHorarioSemanal(semana);
          break;

        case 8:
          mostrarBomberos(bomberos);
          break;
        
        default:
          break;
    }
}

// gcc -g main.c list.c fireman.c -o Tarea1
// ./Tarea1.exe
int main()
{
    int solicitud = 100;
    //se crea la lista,se pide y lee archivo
    List *bomberos = createList();
    Dias *semana = crearSemana();

    // Se carga el archivo CSV
    FILE *file;
    char *filename = (char*)malloc(sizeof(char));
    printf("Ingrese nombre de archivo a cargar:\n ");
    do
    {
        fgets(filename, 50, stdin);
        filename[strcspn(filename, "\n")] = 0;
        strcat(filename, ".csv");
        file = fopen(filename, "r+");

        if (file == NULL)
        {
            filename = (char*)malloc(sizeof(char));
            printf("Archivo no encontrado!. Ingrese otro archivo:\n ");
        }

    } while (file == NULL);
    
    // Se ingresa linea por linea a una funcion que crea los bomberos y los mete a una lista
    char linea[1024];
    while (fgets (linea, 1024, file) != NULL)
    {
        linea[strcspn(linea, "\n")] = 0;
        Bombero *bombero = crearBombero(linea);
        pushBack(bomberos,bombero);
    }
    fclose(file);
    // Lectura de solicitudes (acciones a realizar)
    while( solicitud != 0 )
    {
      printf("Selecione una opcion\n");
      printOpciones();
      scanf("%d", &solicitud);
      while(solicitud < 0 || solicitud > 8 ) 
      {
          printf("Selecione una opcion correcta\n");
          printOpciones();
          scanf("%d", &solicitud);
      }
      //operaciones
      opciones(solicitud, bomberos, semana);
    }
    
    return 0;
}