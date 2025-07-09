#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include <pthread.h>

// debug mask
#define DEBUG_MASK          0xFFFF
#define MAX_NUMBERQUEUE     8
#define MAX_ELEMENT         100
#define DYNAMIC             0
#define STATIC              1

typedef struct Node_t
{
	uint32_t data;
	struct Node_t* pNext;
	struct Node_t* pPrev;
}NodeType;

typedef struct{
    NodeType * Front;
    NodeType * Rear;
    uint32_t QueueSize;
    uint32_t NumNode;
    uint8_t init_type;
    pthread_mutex_t mutex;
}CirQueue_t;
      

typedef enum{
    QUEUE_PUSH_SUCCESS                  = 0U,
    QUEUE_PUSH_FAIL                     = 1U,
    QUEUE_POP_SUCCESS                   = 2U,
    QUEUE_POP_FAIL                      = 3U,
    QUEUE_STATE_EMPTY                   = 4U,
    QUEUE_STATE_NOT_EMPTY               = 5U,
    QUEUE_STATE_FULL                    = 6U,
    QUEUE_STATE_NOT_FULL                = 7U,
    QUEUE_INIT_SUCCESS                  = 8U,
    QUEUE_CLEAR_SUCCESS                 = 9U,
    QUEUE_DEINIT_SUCCESS                = 10U,
    QUEUE_ERR_MAX_NUM_QUEUE             = 11U,
    QUEUE_ERR_EXCEED_ELEMENT_QUEUE      = 12U,
    QUEUE_ERR_NOT_EXIST                 = 13U,
    QUEUE_ERR_CLEAR                     = 14U,
    QUEUE_ERR_DEINIT                    = 15U,
    QUEUE_ERR_ALLOCATOR_FAIL            = 16U,
    QUEUE_ERR_PRINT                     = 17U,
    QUEUE_EXIST                         = 18U,
    QUEUE_PRINT_SUCCESS                 = 19U
} status_t;

status_t Queue_IsFull(CirQueue_t * CirQueue);
status_t Queue_IsEmpty(CirQueue_t * CirQueue);
status_t push(CirQueue_t * CirQueue, uint32_t data);
status_t pop(CirQueue_t * CirQueue);
status_t printqueue(CirQueue_t * CirQueue);
uint32_t getNumQueue();
status_t Init_Queue(CirQueue_t * CirQueue, uint32_t QueueSize , uint8_t init_type);
status_t Queue_Clear(CirQueue_t * CirQueue);
status_t Queue_Deinit(CirQueue_t * CirQueue);
CirQueue_t * dynamic_init(uint32_t size);
#define STATIC_INIT(Q, X)       Init_Queue(&Q, X, STATIC)
#define DYNAMIC_INIT(X)         dynamic_init(X)


