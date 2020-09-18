#include "ej1.h"

int IdHiloCompartido;
int EnteroCompartido;
int valor_inicial_competencia;

int main()
{

    int entero = 1,
                    retval;
    pthread_t hilos[N];

    competenciaConPuntero_t estructurasDeHiloConPuntero[N];
    for (int i = 0; i < N; i++)
    {
        //los hilos trabajan de manera simultánea
        estructurasDeHiloConPuntero[i].hiloACtual = i;
        estructurasDeHiloConPuntero[i].enteroCompartido = &entero;
        retval = pthread_create(&hilos[i], NULL, hiloSumaAVariableCompartidaConStructYPunteroAEntero, &estructurasDeHiloConPuntero[i]);
        if(retval!=0)
        {
            exit(EXIT_FAILURE);
        }
    }

    for ( int i = 0 ; i < N; i++)
    {
        pthread_join(hilos[i], NULL);
    }
    printf("mi pid = %d (Proceso), y entero = %d, fin de experimento en que los hilos COMPITEN.\n", 
                                getpid(), entero);
       
    competencia_t estructurasDeHilo[N];
    EnteroCompartido = entero;
    valor_inicial_competencia = EnteroCompartido;
    for (int i = 0; i < N; i++)
    {
        //los hilos trabajan de manera simultánea
        estructurasDeHilo[i].hiloActual = i;
        retval = pthread_create(&hilos[i], NULL, hiloSumaAVariableCompartidaConStruct, &estructurasDeHilo[i]);
        if(retval!=0)
        {
            exit(EXIT_FAILURE);
        }
    }

    int resultado = valor_inicial_competencia ;
    for ( int i = 0 ; i < N; i++)
    {
        pthread_join(hilos[i], NULL);
    }

    for ( int i = 0 ; i < N; i++)
    {
        competencia_t estructuraDeHiloActual = estructurasDeHilo[i];
        printf("EnteroDeHilo[%d]:%d\n", estructuraDeHiloActual.hiloActual,estructuraDeHiloActual.enteroDeHilo);
        int finalAcumuladorDeHilo = estructuraDeHiloActual.enteroDeHilo;
        resultado += finalAcumuladorDeHilo;
    }
    printf("mi pid = %d (Proceso), y entero = %d, fin de experimento en que los hilos COMPITEN.\n", 
                                getpid(), entero);

    printf("El resultado de la suma de las variables locales de cada uno de los hilos, es: %d\n", resultado);
    for ( int i = 0 ; i < N; i++)
    {
        pthread_join(hilos[i], NULL);
    }
    printf("mi pid = %d (Proceso), y entero = %d, fin de experimento en que los hilos COMPITEN.\n", 
                                getpid(), entero);
    
    return EXIT_SUCCESS;
}

    

void *hiloSumaAVariableCompartidaConStruct(void * voidPunteroAEstructuraDeHilo)
{
    competencia_t* punteroAEstructuraDeHilo = (competencia_t*) voidPunteroAEstructuraDeHilo;
    competencia_t estructuraDeHilo = *punteroAEstructuraDeHilo;
    int hilo = estructuraDeHilo.hiloActual;
    estructuraDeHilo.enteroDeHilo = 0 ;
    int variable_local = estructuraDeHilo.enteroDeHilo;
    for(int i = 0 ; i < 100; i++)
    {
        printf("Soy el hilo %d, de id: %ld; actualizo mi copia local a: %d\n",hilo,pthread_self(), variable_local += sumas[hilo]);
        estructuraDeHilo.enteroDeHilo+=sumas[hilo];
        EnteroCompartido += sumas[hilo];
        printf("Soy el hilo %d, de id: %ld; actualizo la variable compartida a: %d\n",hilo,pthread_self(), EnteroCompartido);
    }
    pthread_exit((void *)0);
}

void *hiloSumaAVariableCompartidaConStructYPunteroAEntero(void* punteroAEstructura)
{
    competenciaConPuntero_t *punteroACompetencia = punteroAEstructura;
    competenciaConPuntero_t competenciaEstructura = *punteroACompetencia;
    int hilo = competenciaEstructura.hiloACtual;
    int *punteroAEntero = competenciaEstructura.enteroCompartido;
    for(int i = 0 ; i < 100; i++)
    {
        printf("Soy el hilo %d, de id: %ld; actualizo mi copia local a: %d\n",hilo,pthread_self(), *punteroAEntero += sumas[hilo]);
        printf("Soy el hilo %d, de id: %ld; actualizo la variable compartida a: %d\n",hilo,pthread_self(), *punteroAEntero);
    }
    pthread_exit((void *)0);
}