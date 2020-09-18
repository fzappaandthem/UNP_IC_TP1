#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define     N   3
const int sumas[] = {2, -1, -1};

typedef struct
{
    int enteroDeHilo;
    int hiloActual;
}competencia_t;

typedef struct
{
    int* enteroCompartido;
    int hiloACtual;
}competenciaConPuntero_t;


void *hiloSumaAVariableCompartida(void *varLocal);
void *hiloSumaAVariableCompartidaConStruct(void *punteroAStructDeHilo);
void *hiloSumaAVariableCompartidaConStructYPunteroAEntero(void *punteroAEntero);