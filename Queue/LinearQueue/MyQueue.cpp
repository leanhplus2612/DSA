#include "MyQueue.h"
#include <Wire.h>


uint8_t Queue_IsEmpty(Queue_t *Queue){
  uint8_t key = FALSE;
  if(Queue->Capacity == QUEUE_EMPTY){
    key = TRUE;
  }
  return key;
}

/*check for full of queue*/
uint8_t Queue_IsFull(Queue_t * Queue){
  uint8_t key = FALSE;
  if(Queue->Capacity == Queue->Size){
    key = TRUE;
  }
  return key;
}

/*push data*/
void Queue_Push_data(Queue_t * Queue, float InputData){
  if(!Queue_IsFull(Queue)){
    Queue->QueueArr[Queue->Rear + 1] = InputData;
    Queue->Rear++;
    Queue->Capacity++;
    }
}

/*Pop Data*/
void Queue_Pop(Queue_t * Queue){
  uint8_t count;
  if(!Queue_IsEmpty(Queue)){
    /*Shift data*/
    for(count = Queue->Front; count<= Queue->Rear;count++){
      Queue->QueueArr[(count-Queue->Front)] = Queue -> QueueArr[count];
    }
    Queue->Front = 0;
    Queue->Rear = Queue->Capacity - 1;
    /*update the empty element is equal to 0*/
    for(count = Queue->Capacity; count < Queue->Size; count++){
      Queue->QueueArr[count]  = 0;
    } 
  }
}

float Queue_PeekData(Queue_t * Queue){
  float Peek_Data = QUEUE_EMPTY_PEEK_VALUE;
  if(!Queue_IsEmpty(Queue)){
    Peek_Data = Queue->QueueArr[Queue->Front];
    Queue->Front++;
    Queue->Capacity--;
  }
  else{
    
  }
  return Peek_Data;
}

void print_Queue(float *data,uint8_t len){
  for(int i = 0; i<len;i++){
    printf("%f  ",data[i]);
  }
}
