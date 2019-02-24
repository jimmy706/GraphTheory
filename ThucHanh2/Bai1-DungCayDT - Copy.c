#include <stdio.h>
#define MAX_LENGTH 100
#define MAX_VERTICES 100
int mark[MAX_VERTICES];
int parent[MAX_VERTICES];
typedef int ElementType;
int j;

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

ElementType length(List *L){
	return L->last;
}

int mark[MAX_VERTICES];
int i, j;

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
	G->Arr[y][x] = 1;
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
	
// Duyet do thi theo chieu rong
void breath_first_search(Graph *G, int x){
	Queue queue;
	make_null_queue(&queue);
	// Dua dinh? 1 vao stack, bat dau duyet tu dinh? 1
	push_queue(&queue, x);
	mark[x] = 1;
	
	while(!empty_queue(&queue)){
		// Lay dinh? tren cung cua hang doi
		int y = top_queue(&queue); pop_queue(&queue);
		List list = neighbours(G, y); //Lay cac dinh? ke` cua dinh? x
		
		for(j = 1; j <= list.last; j++){
			int v = element_at(&list, j);
			if(mark[v] == 0){ // Neu y chua duyet thi duyet no				
				mark[v] = 1;
				parent[v] = y;
				push_queue(&queue, v);
			}
		}
	}
}


int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, e;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	initGraph(&G, numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v;
		scanf("%d%d",&u, &v);
//		printf("\n u = %d & v = %d", u, v);
		add_edge(&G, u, v);
	}
	
	for(j = 1; j <= numberOfVertices; j++){ 
		mark[j] = 0;
	}
	for(j = 1; j <= numberOfVertices; j++){
		parent[j] = 0;
	}
	breath_first_search(&G, 1);
	
	for(j = 1; j <= numberOfVertices; j++){
		if(!mark[j]){
			breath_first_search(&G, j);
		}	
	}
	
	for(j = 1; j <= numberOfVertices; j++){
		printf("%d %d\n", j, parent[j]);
	}
	return 0;
}
