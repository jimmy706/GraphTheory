#include <stdio.h>
#define MAX_VERTICES 100
int mark[MAX_VERTICES];
int parent[MAX_VERTICES];
int j;
typedef struct {
	int numberOfVertices;
	int matrix[MAX_VERTICES][MAX_VERTICES];
}Graph;

void init_graph(Graph* G, int numberOfVertices){
	int i,j;
	G->numberOfVertices = numberOfVertices;
	for( i = 1; i <= G->numberOfVertices; i++){
		for( j = 1; j <= G->numberOfVertices; j++){
			G->matrix[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y){
	G->matrix[x][y] += 1;
	G->matrix[y][x] += 1;
}

int adjacent(Graph * G, int x, int y){
	return G->matrix[x][y] != 0 ;
}


#define MAXLENGTH 100

typedef int ElementType;
typedef struct {
	int data [MAXLENGTH];
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

ElementType length(List *L){
	return L->last;
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

void depth_first_search(Graph *G, int x){
	Stack S;
	make_null_stack(&S);
	
	// Dua dinh? 1 vao stack, bat dau duyet tu dinh? 1
	push(&S, x);
	
	while(!empty(&S)){
		int y = top(&S); pop(&S); // Lay dinh? tren cung cua stack ra
		if(mark[y]) continue; // Neu da duyet roi thi bo qua, den vong lap ke tiep
		
		mark[y] = 1; // Danh dau da duyet
		
		List list = neighbours(G, y); //Lay cac dinh? ke` cua dinh? x
		for(j = 1; j <= list.last; j++){
			int v = element_at(&list, j);
			push(&S, v);
			if(!mark[v])
				parent[v] = y;
		}
	}
}

int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, e, j;
	freopen("dt.txt", "r", stdin);
	
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G, numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v;
		scanf("%d%d",&u, &v);
//		printf("\n u = %d & v = %d", u, v);
		add_edge(&G, u, v);
	}
	
	for(j = 1; j <= numberOfVertices; j++){
		mark[j] = 0;
		parent[j] = 0;
	}
	
	depth_first_search(&G, 1);
	for(j = 1; j <= numberOfVertices; j++){
		if(mark[j] == 0)
			depth_first_search(&G, j);
	}
	
	for(j = 1; j <= numberOfVertices; j++){
		printf("%d %d\n", j, parent[j]);
	}
	return 0;
}

