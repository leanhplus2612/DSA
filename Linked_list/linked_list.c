#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "linked_list.h"


static uint32_t countNode;
static NodeType * pHEAD = NULL;

inline uint32_t getNumNode(){
	return countNode;
}

NodeType* get_HeadPointer(){
	return pHEAD;
}

void makeNode(uint32_t data){
	NodeType * newNode = (NodeType*)malloc(sizeof(NodeType));
	newNode->data = data;
	newNode->pNext = pHEAD;
	pHEAD = newNode;
	countNode+=1;
}



void deleteNode(uint32_t position){
	NodeType * saveNode = pHEAD;
	NodeType * preNode = pHEAD;
	uint8_t idx = 0;
	if(position>countNode || position<1){
		printf("error\n");
		return;
	}
	else{
		if(position == 1){
			pHEAD = pHEAD->pNext;
		}
		else{
			for(idx = 0; idx < position-2; idx++){
				saveNode = saveNode->pNext;
				preNode = preNode->pNext;
			}
			saveNode = saveNode->pNext;
			preNode->pNext = saveNode->pNext;
		}
	}
	countNode--;
	free(saveNode);
}

void printList(){
	NodeType * dummypHEAD = pHEAD;
	printf("HEAD->");
	while(dummypHEAD != NULL){
		printf("%d->",dummypHEAD->data);
		dummypHEAD = dummypHEAD->pNext;
	}
	printf("NULL");
}

