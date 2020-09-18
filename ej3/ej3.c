#include "ej3.h"

/*Ejercicio 3:
 *              Programa en C que genera N cantidades de hilos,
 *              siendo N una constante > 10. Crea arreglo de enteros de N posiciones,
 *              el cual se inicializa con valores aleatorios. El proceso principal
 *              dispone de una variable global. Cada hilo tiene que sumarle a esa variable
 *              global el valor correspondiente de su posición del arreglo. Por ejemplo si
 *              se está ejecutando el hilo número 3, usará el valor del arreglo que está en 
 *              la posición 3. 
*/

#define N 87

int contador;
int arreglo[N];

int main()
{
    contador = 0 ;
    pthread_t hilos[N];
    int indices[N];

    setValoresAleatoriosEnArreglo();
    // int copia;

    for (int i = 0; i < N; i++)
    {
        indices[i] = i;
        // copia = i;
        int retval = pthread_create(&hilos[i], NULL, sumarIndiceEnArreglo,(void*)&indices[i]);
        if(retval!=EXIT_SUCCESS)
        {
            return EXIT_FAILURE;
        }
    }
    /*Hago el join acá para usar distintos procesos(?), si lo dejaba dentro del for, pthread_self()
     *devolvía siempre lo mismo*/
    for(int i = 0; i < N; i++)
    {
        pthread_join(hilos[i], NULL);
    }
    printf("mi pid = %d (Hilo), var_local = %d\n", getpid(), contador);
}

void setValoresAleatoriosEnArreglo()
{
    time_t t;
    srand((unsigned) time(&t));

    for ( int i = 0 ; i < N; i++)
    {
        int r = rand()%1000;
        printf("Guardo en arreglo[%d], el valor: %d\n", i, r);
        arreglo[i] = r;
    }
}


void *sumarIndiceEnArreglo(void *index)
{
    int index_local = *(int*) index;
    int increment = arreglo[index_local];
    printf("soy el hilo #%d para los amigos (%ld para el system), "
        "y al contador le sumo %d\n", index_local, pthread_self(), increment);
    contador += increment;
    pthread_exit((void *)0);
}