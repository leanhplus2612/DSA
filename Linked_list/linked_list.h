#ifndef LINKED_LIST_h
#define LINKED_LIST_h

#include <stdint.h>


typedef struct Node_t
{
	uint32_t data;
	struct Node_t* pNext;
}NodeType;

NodeType* get_HeadPointer();
void makeNode(uint32_t data);
void deleteNode(uint32_t position);
void printList(void);

#endif