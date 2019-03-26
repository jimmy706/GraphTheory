#include <stdio.h>
#define MAX_VERTICES 100

int ranks[MAX_VERTICES];

int mark[MAX_VERTICES];
int candyWanted[MAX_VERTICES];

typedef struct{
	int numberOfVertices;
	int arr[MAX_VERTICES][MAX_VERTICES];
}Graph;


void init_graph(Graph *G, int numberOfVertices){
	int i,j;
	G->numberOfVertices = numberOfVertices;
	for( i = 1; i <= G->numberOfVertices; i++){
		for( j = 1; j <= G->numberOfVertices; j++){
			G->arr[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y){
	G->arr[x][y]++;
}

int adjacent(Graph * G, int x, int y){
	return G->arr[x][y] != 0 ;
}

int degree(Graph *G, int x){
	int deg = 0;
	int y;
	for( y = 1; y <= G->numberOfVertices; y++)
		deg += G->arr[x][y];
	 	
	return deg;
}

// -------------------------------- INSTALL LIST------------------------------
typedef struct {
	int data[MAX_VERTICES];
	int last;
}List;

void make_null_list(List *l){
	l->last = 0;
}

void push_back(List *l, int num){
	l->data[l->last] = num;
	l->last++;
}

int element_at(List *l, int position){
	return l->data[position - 1];
}

// Tao rong s1 va copy cac phan tu cua s2 vao s1
void copy_list(List *s1, List *s2){
	make_null_list(s1);
	int i;
	for(i = 1; i <= s2->last; i++){
		push_back(s1, element_at(s2, i));
	}
}

// INSTALL QUEUE
typedef struct {
	int data[MAX_VERTICES];
	int front, rear;
} Queue;

void make_null_queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

int empty_queue(Queue *Q){
	return Q->front > Q->rear;
}

void push_queue(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear] = x;
}

void pop_queue(Queue *Q){
	Q->front++;
}

int top_queue(Queue *Q){
	return Q->data[Q->front];
}



void ranking_reverse(Graph *G){
	int deegreeOut[MAX_VERTICES];
	int x,u;
	
	for(x = 1; x <= G->numberOfVertices; x++){
		deegreeOut[x] = 0;
	}
	
	for(x = 1; x <= G->numberOfVertices; x++){
		for(u = 1; u <= G->numberOfVertices; u++){
			if(G->arr[x][u] != 0) deegreeOut[x]++;
		}
	}
	
	List S1, S2;
	make_null_list(&S1);
	int i;
	int rank = 1;
	
	for(i = 1; i <= G->numberOfVertices; i++){
		if(deegreeOut[i] == 0) push_back(&S1, i);
	}
	
	
	while(S1.last > 0){
		make_null_list(&S2);
		for(i = 1; i <= S1.last; i++){
			int u = element_at(&S1, i);
			ranks[u] = rank;
			int v;
			for(v = 1; v <= G->numberOfVertices; v++){
				if(G->arr[v][u] != 0){
					deegreeOut[v]--;
					if(deegreeOut[v] == 0)
						push_back(&S2, v);
				}
			}
		}
		copy_list(&S1, &S2);
		rank++;
	}
}


int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, i, j;
	freopen("chia_keo.txt", "r", stdin);
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G, numberOfVertices);
	
	for(i = 1; i <= numberOfEdges; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		add_edge(&G, u, v);
	}
	ranking_reverse(&G);
	
	int candyNeeded = 0;
	
	for(i = 1; i <= numberOfVertices; i++){
		printf("%d\n", ranks[i]);
		candyNeeded += ranks[i];
	}
	
	printf("%d", candyNeeded);
	
	return 0;
}
