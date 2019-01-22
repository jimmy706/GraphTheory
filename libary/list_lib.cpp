#include <stdio.h>
#define MAXLENGTH 100

typedef int ElementType;
typedef struct {
	int data [MAXLENGTH];
	ElementType last;
}List;

void make_null(List * L){
	L->last = 0;
}

void push(List *L, ElementType ele){
	L->data[L->last] = ele;
	L->last++;
}

ElementType element_at(List *L, int position){
	return L->data[position - 1];
}

ElementType length(List *L){
	return L->last;
}

