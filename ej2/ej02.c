#include "ej02.h"

/* Ejercicio 2
 *              Crear programa en C cuyo proceso principal imprima los valores 
 *              de forma secuencial, de un arreglo (cuya longitud se pasa por parámetro)
 *              cargado (con valores aleatorios)
 *              por un hilo de dicho proceso. Al finalizar, el proceso principal debe
 *              mostrar los valores de dicho arreglo. 
 */

int elems;

int main(int argc, char* argv[])
{
    if(argc > 1)
    {
        elems = atoi(argv[1]);
        int *arr = malloc(elems* sizeof(int));
        pthread_t thr;
        int retval = pthread_create(&thr, NULL, setArrInThread, arr);
        if(retval != 0)
            exit(EXIT_FAILURE);
        pthread_join(thr, NULL);
        free(arr);
    }
    else
    {
        printf("Si no me decís el tamaño del arreglo, no puedo hacer "
                    "nada, cra... Nos vemos!\n");
    }
    
    return EXIT_SUCCESS;
}

void printArray(int* arr, int len)
{
    for (int i = 0; i < elems; i++)
    {
        //Accedo al arreglo con aritmética de punteros
        printf("arr[%d]\t=%d\n", i, *(arr+i));
    }
}

void setArr(int elems, void* vec)
{
    time_t t;
    srand((unsigned) time(&t));
    int* arr = (int*)vec;
    for (int i = 0; i < elems; i++)
    {
        arr[i] = rand()%1000;
        /*Uncomment para ver cuáles son los valores aleatorios generados y en qué posición se guardan
         *esto puede servir para comprobar que los mismos no son fruta, o sí, pero que sabemos de dónde vienen.
         *accedo al arreglo con el subíndice
        printf("Estoy guardando: arr[%d]=%d\n", i, arr[i]);*/
    }
}

void *setArrInThread(void* vec){
    int* arr = (int*)vec;
    setArr(elems, arr);
    printArray(arr, elems);
    pthread_exit((void*)0);
}
