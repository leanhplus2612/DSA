#ifndef MYQUEUE_h
#define MYQUEUE_h
#include <stdint.h>


#define QUEUE_EMPTY 0U
#define QUEUE_EMPTY_PEEK_VALUE 0
#define FALSE 0U
#define TRUE 1U

typedef struct{
  int8_t Front, Rear, Size;
  uint8_t Capacity;
  float * QueueArr;
} Queue_t;

void Queue_Push();
void Queue_Pop(Queue_t * Queue);
void Queue_Push_data(Queue_t * Queue, float InputData);
uint8_t Queue_IsEmpty(Queue_t * Queue);
uint8_t Queue_IsFull(Queue_t * Queue);
float Queue_PeekData(Queue_t * Queue);
void print_Queue(float *data,uint8_t len);


#endif
