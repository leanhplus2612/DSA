#include "CircularQueue.h"



/*check Queue empty*/
uint8_t Queue_IsEmpty(Queue_t *Queue){
  uint8_t key = FALSE;
  if(Queue->Front == -1){
    key = TRUE;
  }
  return key;
}

/*check for full of queue*/
uint8_t Queue_IsFull(Queue_t * Queue){
  uint8_t key = FALSE;
  if((Queue->Front == Queue->Rear + 1) || (Queue->Front == 0 && Queue->Rear == Queue->Size - 1)){
    key = TRUE;
  }
  return key;
}

/*push data*/
void Queue_Push_data(Queue_t * Queue, float InputData){
  if(!Queue_IsFull(Queue)){
    if(Queue->Front == -1){
      Queue->Front = 0;
    }
    Queue->Rear = (Queue->Rear + 1)% Queue->Size;
    Queue->QueueArr[Queue->Rear] = InputData;
    }
}

/*Pop Data*/
float Queue_Pop(Queue_t * Queue){
  uint8_t count;
  float dataPoped;
  if(!Queue_IsEmpty(Queue)){
    dataPoped = Queue->QueueArr[Queue->Front];
    if(Queue->Front == Queue->Rear){
      Queue->Front = -1;
      Queue->Rear = -1;
    }
    else{
      Queue->Front = (Queue->Front + 1) % Queue->Size;
    }
  }
  return dataPoped;
}



void print_Queue(Queue_t * Queue){
  uint8_t i;
  if(Queue_IsEmpty(Queue)){
    printf("Queue is Empty\n");
  }
  else{
    printf("Queue -> Front = %d \n", Queue->Front);
    printf("Queue -> QueueArr: ");

    for(i = Queue -> Front; i != Queue -> Rear; i = (i+1)% Queue->Size ){
      printf("%f ", Queue->QueueArr[i]);
    }
    printf("%f ", Queue->QueueArr[i]);
    printf("Queue -> Rear = %d \n", Queue->Rear);
  }
}
