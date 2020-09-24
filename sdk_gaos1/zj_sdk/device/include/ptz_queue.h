#ifndef PTZ_QUEUE_H_
#define PTZ_QUEUE_H_

typedef struct Node{
	int value;
	struct Node *next;
} Node;
 
typedef struct Queue{
	Node *head;
	Node *last;
}Queue;


void QueueInit(Queue *q);
void QueueDestory(Queue *q);
//void QueuePush(Queue *q,int v);
int QueuePush(Queue *q,int v);


void QueuePop(Queue *q);
int QueueFront(Queue *q);
int QueueSize(Queue *q)	;
int QueueEmpty(Queue *q);
#endif




