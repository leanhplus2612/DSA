#ifndef CIRCULARQUEUE_h
#define CIRCULARQUEUE_h
#include <stdint.h>


#define QUEUE_EMPTY 0U
#define QUEUE_EMPTY_PEEK_VALUE 0
#define FALSE 0U
#define TRUE 1U

typedef struct{
	int8_t Front, Rear, Size;
	float * QueueArr;
} Queue_t;

float Queue_Pop(Queue_t * Queue);
void Queue_Push_data(Queue_t * Queue, float InputData);
uint8_t Queue_IsEmpty(Queue_t * Queue);
uint8_t Queue_IsFull(Queue_t * Queue);
void print_Queue(Queue_t * Queue);


#endif
