#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<errno.h>

#define N 1024

void iniciarMatriz(double mat[][N], int len, double valorInicial);
void multiplicarMatrices(void);
void iniciarMatrices(void);
void *worker(void* arg);
int checkMatrizResultanteValorCorrecto(double mat[][N], int len, double finVal);
void imprimirMatriz(double matriz[][N], int len);
void hiloMultiplicaColumna(int columna);
