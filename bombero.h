#include "list.h"

typedef struct Bombero Bombero;
typedef struct Dias Dias;

Bombero *crearBombero(char *linea);

void mostrarBomberos(List* bomberos);

Dias *crearSemana();

List *retornarLista(Dias *semana, char *dia);

void mostrarBomberos(List* bomberos);

void agregarBombero(List *bomberos);

void eliminarBomberos (List* bomberos, Dias *semana);

void buscarRut(List* bomberos);

void buscarPorDia(List *bomberos);

void modificarDisponibilidad(List *bomberos, Dias *semana);

void generarHorarioSemanal(List *bomberos, Dias *dias);

void mostrarHorarioSemanal(Dias *dias);