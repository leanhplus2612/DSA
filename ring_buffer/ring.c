#include "ring.h"
static volatile CirQueue_t * CurrentQueue[MAX_NUMBERQUEUE];
static volatile uint32_t queue_count;
static pthread_mutex_t global_mutex = PTHREAD_MUTEX_INITIALIZER;

CirQueue_t * dynamic_init(uint32_t size){
    CirQueue_t * queue = (CirQueue_t *)malloc(sizeof(CirQueue_t));
    Init_Queue(queue, size, DYNAMIC);
    return queue;
}

status_t Init_Queue(CirQueue_t * CirQueue, uint32_t QueueSize, uint8_t init_type){
    pthread_mutex_lock(&global_mutex);
    status_t status = QUEUE_INIT_SUCCESS;
    if(queue_count >= MAX_NUMBERQUEUE){
        printf("The number of queue is maximum\n");
        pthread_mutex_unlock(&global_mutex);
        return QUEUE_ERR_MAX_NUM_QUEUE;
    }
    if(QueueSize > MAX_ELEMENT){
        printf("Queue Size is exceed\n");
        pthread_mutex_unlock(&global_mutex);
        return QUEUE_ERR_EXCEED_ELEMENT_QUEUE;
    }

    if(CirQueue == NULL){
        pthread_mutex_unlock(&global_mutex);
        return QUEUE_ERR_ALLOCATOR_FAIL;
    }
    // static
    CirQueue->Front     = NULL;
    CirQueue->Rear      = NULL;
    CirQueue->NumNode   = 0;
    CirQueue->QueueSize = QueueSize;
    CirQueue->init_type = init_type;
    CurrentQueue[queue_count] = CirQueue;
    pthread_mutex_init(&CirQueue->mutex, NULL);
    queue_count++;
    pthread_mutex_unlock(&global_mutex);
    return status;
}

status_t Queue_IsEmpty(CirQueue_t * CirQueue)
{
    status_t state = QUEUE_STATE_NOT_EMPTY;
    if(CirQueue->Front == NULL){
		state = QUEUE_STATE_EMPTY;
	}
    return state;
}


static status_t Queue_Exist(CirQueue_t * CirQueue)
{
    pthread_mutex_lock(&global_mutex);
    status_t status = QUEUE_ERR_NOT_EXIST;
    int i = 0;
    for(i = 0; i< queue_count; i++)
    {
        if(CirQueue == CurrentQueue[i]){
            status = QUEUE_EXIST;
            break;
        }
    }
    pthread_mutex_unlock(&global_mutex);
    return status;
}

status_t Queue_Clear(CirQueue_t * CirQueue){
    // checking for queue exist
    pthread_mutex_lock(&(CirQueue->mutex));
    if(Queue_Exist(CirQueue) == QUEUE_ERR_NOT_EXIST){
        printf("CANN'T CLEAR: %d\n", QUEUE_ERR_NOT_EXIST);
        return QUEUE_ERR_CLEAR;
    }
    if(Queue_IsEmpty(CirQueue) == QUEUE_STATE_EMPTY){
        printf("CANN'T CLEAR: %d\n", QUEUE_STATE_EMPTY);
        return QUEUE_ERR_CLEAR;
    }

    NodeType * DummyHead = CirQueue->Front;
    uint32_t count = 0;
    do {
        DummyHead->data = 0;
        DummyHead = DummyHead->pNext;
        count++;
    } while(DummyHead != CirQueue->Front && count < CirQueue->NumNode);
    pthread_mutex_unlock(&(CirQueue->mutex));
    return QUEUE_CLEAR_SUCCESS;
}

status_t Queue_Deinit(CirQueue_t * CirQueue){
    status_t status = QUEUE_ERR_DEINIT;
    uint8_t i;
    if(Queue_Exist(CirQueue) == QUEUE_ERR_NOT_EXIST){
        printf("CANN'T CLEAR: %d\n", QUEUE_ERR_NOT_EXIST);
        return QUEUE_ERR_DEINIT;
    }
    while(CirQueue->NumNode != 0){
        if(pop(CirQueue) != QUEUE_POP_SUCCESS){
            return status;
        }
    }
    
    for(i = 0; i < queue_count; i++){
        if(CirQueue == CurrentQueue[i]){
            if(CirQueue->init_type == DYNAMIC){
                free(CirQueue);
            }
            pthread_mutex_destroy(&(CirQueue->mutex));
            // Dịch các phần tử phía sau lên trước 1 vị trí
            for(uint32_t j = i; j < queue_count - 1; j++){
                CurrentQueue[j] = CurrentQueue[j+1];
            }
            CurrentQueue[queue_count - 1] = NULL;
            queue_count--;
            break;
        }
    }
    status = QUEUE_DEINIT_SUCCESS;
    return status;
}


uint32_t getNumQueue(){
    return queue_count;
}


status_t Queue_IsFull(CirQueue_t * CirQueue)
{
    status_t state = QUEUE_STATE_NOT_FULL;
    if(CirQueue->NumNode >= CirQueue->QueueSize){
        state = QUEUE_STATE_FULL;
    }
    return state;
}


status_t printqueue(CirQueue_t * CirQueue){
    status_t status = QUEUE_ERR_PRINT;
    if(Queue_Exist(CirQueue) == QUEUE_ERR_NOT_EXIST){
        printf("CANN'T PRINT: %d\n", QUEUE_ERR_NOT_EXIST);
        return status;
    }

    if(CirQueue->Front == NULL){
        printf("CANN'T PRINT %d\n", QUEUE_STATE_EMPTY);
        return status;
    }
    pthread_mutex_lock(&(CirQueue->mutex));
    NodeType * DummyHead = CirQueue->Front;
    uint32_t count = 0;

    printf(" Queue: ");
    do {
        printf("%d --> ", DummyHead->data);
        DummyHead = DummyHead->pNext;
        count++;
    } while(DummyHead != CirQueue->Front && count < CirQueue->NumNode);

    printf("END\n");
    pthread_mutex_unlock(&(CirQueue->mutex));
    status = QUEUE_PRINT_SUCCESS;
    return status;
}



status_t pop(CirQueue_t * CirQueue)
{
    status_t status = QUEUE_POP_FAIL;
    pthread_mutex_lock(&(CirQueue->mutex));
    // check queue empty
    if(Queue_IsEmpty(CirQueue) == QUEUE_STATE_EMPTY){
        printf("CANN'T POP: %d\n", QUEUE_STATE_EMPTY);
        pthread_mutex_unlock(&(CirQueue->mutex));
        return status;
    }
	else
    {
        //printf("Queue not empty\n");
        if(CirQueue->Front == CirQueue->Rear){
		    free(CirQueue->Front);
		    CirQueue->Front = NULL;
		    CirQueue->Rear = NULL;
		    CirQueue->NumNode = 0;
	    }
	    else{
		    NodeType * temp = CirQueue->Rear;
		    CirQueue->Rear = (CirQueue->Rear)->pPrev;
		    CirQueue->Rear->pNext = CirQueue->Front;
            CirQueue->Front->pPrev = CirQueue->Rear;
		    free(temp);
		    CirQueue->NumNode -=1;
	    }
        status = QUEUE_POP_SUCCESS;
    }
    pthread_mutex_unlock(&(CirQueue->mutex));
    return status;
}


status_t push(CirQueue_t * CirQueue, uint32_t data){
    status_t status = QUEUE_PUSH_FAIL;
    pthread_mutex_lock(&(CirQueue->mutex));
    /*check queue full*/ 
    if(Queue_IsFull(CirQueue) == QUEUE_STATE_FULL){
        // debug mask
        printf("PUSH FAIL %d\n", QUEUE_STATE_FULL);
        pthread_mutex_unlock(&(CirQueue->mutex));
        return status;
    }

	NodeType * newnode = (NodeType *)malloc(sizeof(NodeType));
    if(newnode == NULL)
    {
        status = QUEUE_ERR_ALLOCATOR_FAIL;
        printf("PUSH FAIL %d\n", QUEUE_ERR_ALLOCATOR_FAIL);
        pthread_mutex_unlock(&(CirQueue->mutex));
        return status;
    }
    newnode->data = data;
    
    // the first time --> Tail = Head = newnode
    if(CirQueue->Front == NULL){
        newnode->pNext = newnode;
        newnode->pPrev = newnode;
        CirQueue->Rear = newnode;
	}
	else{
		// the old head
		newnode->pNext = CirQueue->Front;
        newnode->pPrev = CirQueue->Rear;
        (CirQueue->Front)->pPrev = newnode;
        (CirQueue->Rear)->pNext = newnode;    
	}
    CirQueue->Front = newnode;
    CirQueue->NumNode += 1;
    status = QUEUE_PUSH_SUCCESS;
    pthread_mutex_unlock(&(CirQueue->mutex));
    return status;
}

