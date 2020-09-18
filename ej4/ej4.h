#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<unistd.h>

void *producir(void* bufferVoid);
void *consumir(void* bufferVoid);
