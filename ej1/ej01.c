#include "ej01.h"

/*
 * Ejercicio 1: Crear programa en C que tenga un único contador y 3 hilos para modificar 
 *              su valor. Uno de los hilos, incrementa el contador en 2 en cada iteración,
 *              y muestra su valor en pantalla, mientras que los otros dos hilos, decrementan
 *              el valor del contador en 1, en cada iteración y muestran el valor actualizado
 *              por pantalla.
 *                  Agregué una versión de yapa en que los hilos compiten por acceder a
 *     /* data */
int IdHiloCompartido;
int EnteroCompartido;
int valor_inicial_competencia;

int main()
{
    int entero = 1,
                    retval;
    pthread_t hilos[N];

    for (int i = 0; i < N; i++)
    {
        IdHiloCompartido = i;
        retval = pthread_create(&hilos[i], NULL, hiloSumaAVariableCompartida, &entero);
        if(retval!=0)
        {
            exit(EXIT_FAILURE);
        }
        pthread_join(hilos[i], NULL);
    }
    printf("mi pid = %d (Proceso), y entero = %d, fin experimento: los hilos NO compiten\n"
                "Hice otra(s) versión(es): Ej1_BONUS, donde los hilos sí compiten", getpid(), entero);
    
    return EXIT_SUCCESS;
}

void *hiloSumaAVariableCompartida(void * entero_de_hilo)
{
    for(int i = 0 ; i < 100; i++)
    {
        printf("Soy el hilo %d, de id: %ld; actualizo la variable compartida a: %d\n",
                                IdHiloCompartido,pthread_self(), (*(int*) entero_de_hilo) += sumas[IdHiloCompartido]);
    }
    pthread_exit((void *)0);
}


