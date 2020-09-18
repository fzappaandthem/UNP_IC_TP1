#include "ej4.h"

/* Ejercicio 4:
 *              Crear dos hilos: productor y consumidor. El hilo
 *              productor debe generar valores aleatorios y guardarlos
 *              en un buffer, será un arreglo de longitud tamanioDeBuffer.
 *              Cuando el consumidor consuma los caracteres guardados
 *              en el buffer por el productor, mostrará dicho caracter
 *              por pantalla. 
 */

#define tamanioDeBuffer 99
#define TRUE 1

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int ultimoConsumido = 0;
int ultimoProducido = 0;
int elementosAConsumir = 0;
int espaciosParaGuardar = tamanioDeBuffer;

int main()
{
    pthread_t productor;
    pthread_t consumidor;
    int buffer[tamanioDeBuffer];
    pthread_create(&productor,NULL, producir, &buffer);
    pthread_create(&consumidor, NULL, consumir, &buffer);

    pthread_join(productor, NULL);
    pthread_join(consumidor, NULL);
    return EXIT_SUCCESS;
}


void * consumir (void* bufferVoid)
{
    int *buffer = (int*) bufferVoid;
    while(TRUE){
        if(elementosAConsumir > 0){
            int elemento = *(buffer + ultimoConsumido);
            printf("Consumo el elemento: %c\n", elemento);

            //inicio región crítica
            pthread_mutex_lock(&mutex);
            ++ultimoConsumido;            
            --elementosAConsumir;
            ++espaciosParaGuardar;
            //voy al inicio del buffer si ya se guardó en la ultima posición dle mismo.
            if (ultimoConsumido >= tamanioDeBuffer - 1){
                ultimoConsumido = 0;
            }
            pthread_mutex_unlock(&mutex);
            //fin región crítica
        } else {
            printf("Soy el consumidor: el buffer está vacío, espero...\n");
            sleep(2);
        }
    }

}

void * producir(void* bufferVoid){
    int *buffer = (int*) bufferVoid;
    time_t t;
    srand((unsigned) time(&t));
    while(TRUE){
        if((espaciosParaGuardar) > 0 )
        {
            int elemento = rand()%94+33;
            //uncomment linea inferior para mostrar lo producido
            // printf("produzco: %c, y lo guardo en la posición %d\n", elemento, ultimoProducido);


            //inicio región crítica
            pthread_mutex_lock(&mutex);            
            *(buffer+ultimoProducido) = elemento;
            ++ultimoProducido;
            ++elementosAConsumir;
            --espaciosParaGuardar;
            //voy al inicio del buffer si ya se guardó en la ultima posición dle mismo.
            if (ultimoProducido >= tamanioDeBuffer - 1){
                ultimoProducido = 0;
            }
            pthread_mutex_unlock(&mutex);
            //fin región crítica

        }
        else
        {
            printf("Soy el productor: el buffer está lleno, espero...\n");
            sleep(2);
        }
    }
    return NULL;
}