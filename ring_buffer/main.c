#include <stdio.h>
#include "ring.h"
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


int main() {
    CirQueue_t Queue1;
    printqueue(&Queue1);
    // // init queue
    STATIC_INIT(Queue1, 5);
    //Init_Queue(&Queue1, 5);
    printqueue(&Queue1);
    push(&Queue1, 30);
    push(&Queue1, 40);
    push(&Queue1, 50);
    printqueue(&Queue1);
    printf("num queue now: %d\n", getNumQueue());
    pop(&Queue1);
    printf("num queue now: %d\n", getNumQueue());
    pop(&Queue1);
    printqueue(&Queue1);
    push(&Queue1, 80);
    printf("num queue now: %d\n", getNumQueue());
    push(&Queue1, 70);
    printf("num queue now: %d\n", getNumQueue());
    push(&Queue1, 90);
    printf("num queue now: %d\n", getNumQueue());
    push(&Queue1, 60);
    printf("num queue now: %d\n", getNumQueue());
    push(&Queue1, 50);
    printf("num queue now: %d\n", getNumQueue());
    push(&Queue1, 10);
    printf("num queue now: %d\n", getNumQueue());
    printqueue(&Queue1);
    Queue_Deinit(&Queue1);
    printqueue(&Queue1);
    printf("num queue now: %d\n", getNumQueue());

    int i = 0;
    CirQueue_t Queue[10];
    for(i = 0; i< 10; i++){
        STATIC_INIT(Queue[i], 30);
        printf("num queue now: %d\n", getNumQueue());
    }

    for(i = 0; i < 31; i++){
        push(&Queue[1], i);
    }
    printqueue(&Queue[1]);
    Queue_Clear(&Queue[1]);
    printqueue(&Queue[1]);
    printf("num node: %d\n", Queue[1].NumNode);
    for(i = 0; i < 32; i++){
        pop(&Queue[1]);
    }
    printqueue(&Queue[1]);
    printf("num node: %d\n", Queue[1].NumNode);
    Queue_Clear(&Queue[1]);
    for(i = 0; i< 3; i++){
        Queue_Deinit(&Queue[i]);
    }
    printf("num queue now: %d\n", getNumQueue());
    // dynamic
    CirQueue_t * DQueue = DYNAMIC_INIT(30);
    printf("num queue now: %d\n", getNumQueue());
    printqueue(DQueue);
    Queue_Deinit(DQueue);
    printf("num queue now: %d\n", getNumQueue());
    return 0;
}
