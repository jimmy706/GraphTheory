#include <stdio.h>
#define MAX_VERTICES 100
#define MAX_LENGTH 100

int mark[MAX_VERTICES];
int i, j, k;
int mark[MAX_VERTICES];
int num[MAX_LENGTH];
int min_num[MAX_LENGTH];
int on_stack[MAX_LENGTH];
int count = 0;
int countVertice;

typedef int ElementType;


// KHAI BAO LIST
typedef struct {
	int data [MAX_LENGTH];
	ElementType last;
}List;

void make_null(List * L){
	L->last = 0;
}

void push_back(List *L, ElementType ele){
	L->data[L->last] = ele;
	L->last++;
}

ElementType element_at(List *L, int position){
	return L->data[position - 1];
}

// KHAI BAO STACK
typedef struct {
	ElementType data[MAX_LENGTH];
	ElementType size;
}Stack;

Stack S; // KHAI BAO STACK

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

// KHAI BAO GRAPH
typedef struct {
	int numberOfVertices;
	int Arr[MAX_VERTICES][MAX_VERTICES];
}Graph;

int initGraph(Graph *G, int numberOfVertices){
	G->numberOfVertices = numberOfVertices;
	for(i = 1; i <= numberOfVertices; i++){
		for(j = 1; j <= G->numberOfVertices; j++){
			G->Arr[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y){
	G->Arr[x][y] = 1;
}

int adjacent(Graph * G, int x, int y){
	return G->Arr[x][y] != 0 ;
}

List neighbours (Graph* G, int x) {
	List list;
	make_null(&list);
	int y = 1;
	for( y ; y <= G->numberOfVertices; y++){
		if(adjacent(G,x,y))
			push_back(&list,y);
	}
	
	return list;
}

int min(int a, int b){
	if(a < b) return a;
	else return b;
}

void strong_connect(Graph *G, int x){
	num[x] = min_num[x] = k; k++;
	push(&S, x);
	on_stack[x] = 1;
	
	List list = neighbours(G, x);
	int j;
	for(j = 1; j <= list.last; j++){
		int y = element_at(&list, j);
		if(num[y] < 0){
			strong_connect(G, y);
			min_num[x] = min(min_num[x], min_num[y]);
		}
		else if(on_stack[y]){
			min_num[x] = min(min_num[x], num[y]);
		}
	}
//	printf("min_num[%d] = %d\n", x, min_num[x]);
	
	if(num[x] == min_num[x]){
		countVertice = 0;
//		printf("\n%d la dinh khop\n", x);		
		int w;
		do{			
			w = top(&S);
			pop(&S);
			on_stack[w] = 0;
			countVertice++;			
		}
		while(w != x);		
	}
}





int main(){
	Graph G;			
	int numberOfVertices, numberOfEdges, e;
	make_null_stack(&S);
	freopen("strong_connect.txt", "r", stdin);
	
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	initGraph(&G, numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v;
		scanf("%d%d",&u, &v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= numberOfVertices; i++){
		num[i] = -1;
		on_stack[i] = 0;
	}	
	k = 1;
	for(i = 1; i <= numberOfVertices; i++){
		if(num[i] < 0)
			strong_connect(&G, i);
	}
	
	if(countVertice == numberOfVertices)
		printf("strong connected");
	else
		printf("unconnected");
		
	return 0;
}
