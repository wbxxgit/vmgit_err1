

#include <stdlib.h>
#include "ptz_queue.h" 


void QueueInit(Queue *q){
	q->head = q->last = NULL;
}

void QueueDestory(Queue *q){
	Node *cur,*next;
	for(cur = q->head;cur!=NULL;cur = next){
		next = cur->next;
		free(cur);
	}
	q->head = q->last = NULL;
}

void QueuePush(Queue *q,int v){
	Node *node = (Node *)malloc(sizeof(Node));
	node->value = v;
	node->next = NULL;
	if(q->head == NULL){
		q->head = node;
		q->last = node;
	}
	else
	{
		q->last->next = node;
		q->last = node;
	}
}

void QueuePop(Queue *q){
	//头删
	Node *second = q->head->next;
	free(q->head);
	q->head = second;
	if(q->head == NULL){
		q->last = NULL;
	}
}

int QueueFront(Queue *q){
	return q->head->value;
}

int QueueSize(Queue *q){
	int size = 0;	
	Node*c;
	for(c = q->head;c!=NULL;c = c->next)
	{
		size++;
	}
	return size;
}

int QueueEmpty(Queue *q){
	if(q->head == NULL)
	{
		return 1;
	}
	else	
		return 0;
}










