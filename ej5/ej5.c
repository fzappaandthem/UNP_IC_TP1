#include "ej5.h"

/*Ejercicio 5
 *              Crear la versión 3 de multiplicación de matrices
 *              basada en la versión 2 vista en clase.
 *              Esta versión debe repartir el trabajo en H hilos,
 *              el valor H es ingresado como parámetro en
 *              la invocación del programa.
 *              H debe dividir exactamente a N (N>=1024).
 *              Cada hilo creado, debe encargarse de multiplicar N/H 
 *              filas de la matriz A por toda la matriz B, y
 *              guardar los resultados en las N/H filas de la matriz C.
 */ 

double a[N][N];
double b[N][N];
double c[N][N];


int cantidadDeHilosParametro;

pthread_t hilos[N];

int main(int argc,char* argv[])
{
    if(argc > 0 )
    {
        int hilos = atoi(argv[1]);
        int cociente = N / hilos;
        if((cociente * hilos) == N)
        {
            cantidadDeHilosParametro = hilos;
            printf("Comienzo... \n");
            iniciarMatrices();
            printf("Multiplicando... \n");

            multiplicarMatrices();

            if((checkMatrizResultanteValorCorrecto(c, N, N))==0)
            {
                printf("Fin multiplicación: Resultado OK!\n");
            }else{
                printf("Fin multiplicación: ERROR\n");
            }
            
        } else {
            printf("La cantidad de hilos ingresada no me sirve\n");
            return EXIT_FAILURE;
        }
        
        // printf("Matriz A:\n");
        // imprimirMatriz(a, N);
        // printf("Matriz B:\n");
        // imprimirMatriz(b, N);
        // printf("Matriz C:\n");
        // imprimirMatriz(c, N);

        printf("Fin del programa\n");

    }
    else
    {
        printf("Cantidad de hilos no ingresadas. Adios.\n");
    }
    return EXIT_SUCCESS;
}

void imprimirMatriz(double matriz[N][N], int len){
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            printf("%.1f ", matriz[i][j]);
        }
        puts("");
    }
    
}

int checkMatrizResultanteValorCorrecto(double mat[N][N], int len, double finVal)
{
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if(mat[i][j] != finVal )
                return EXIT_FAILURE;
        }
        
    }
    return EXIT_SUCCESS;
}

void iniciarMatrices(){
    iniciarMatriz(a, N, 1.0);
    iniciarMatriz(b, N, 1.0);
    iniciarMatriz(c, N, 0.0);
}

void iniciarMatriz(double mat[N][N], int len, double valorInicial){
    for (int i = 0 ; i < len; i++)
    {
        for(int j = 0 ; j < len; j++)
        {
            mat[i][j] = valorInicial;
        }
    }
}

void *worker(void *arg){
    int hilo=*(int*) arg;
    int cociente = N/cantidadDeHilosParametro;
    int columnaFin;
    columnaFin = ((hilo+1)*cociente);
    
    for (int i = hilo*cociente; i < columnaFin; i++)
    {
        for(int j = 0 ; j < N; j++)
        {
            for(int k = 0 ; k < N; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void multiplicarMatrices(void)
{
    int i, retVal;
    int hilosEnArr [cantidadDeHilosParametro];
    for(int i = 0 ; i < cantidadDeHilosParametro; i++)
    {
        hilosEnArr[i] = i;
    }

    for(int i = 0 ; i < cantidadDeHilosParametro; i++){
        retVal = pthread_create(&hilos[i], NULL, worker, (void*) &hilosEnArr[i]);
        if(retVal != 0)
        {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < N; i++)
    {
        pthread_join(hilos[i], NULL);
    }

}