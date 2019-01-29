#include <stdio.h>
#define MAXLENGTH 100

typedef int ElementType;
typedef struct {
	ElementType data[MAXLENGTH];
	ElementType size;
}Stack;

void make_null_stack(Stack *s){
	s->size = 0;
}

void push(Stack *S, ElementType x){
	S->data[S->size] = x;
	S->size++;
}

int empty(Stack *S){
	return S->size == 0;
}

ElementType top(Stack *S){
	return S->data[S->size - 1];
}

void pop(Stack *S){
	if(!empty(S))
		S->size--;
}



