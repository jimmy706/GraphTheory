#include <stdio.h>
#define MAX_LENGTH 100

typedef int ElementType;
typedef struct {
	ElementType data[MAX_LENGTH];
	ElementType front, rear;	
} Queue;

void make_null_queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

void push_queue(Queue *Q, ElementType x){
	Q->rear++;
	Q->data[Q->rear] = x;
}

void pop_queue(Queue *Q){
	Q->front++;
}

ElementType top_queue(Queue *Q){
	return Q->data[Q->front];
}

int empty_queue(Queue *Q){
	return Q->front > Q->rear;
}



