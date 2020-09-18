#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void setArr(int elems, void* arr);
void *setArrInThread(void* vec);
void printArray(int* arr, int len);