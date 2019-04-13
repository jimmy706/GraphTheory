#include <stdio.h>
#define MAX_VERTICES 100
#define NO_EDGE 0
#define INF 999


typedef struct {
	int numberOfVertics;
	int capacities[MAX_VERTICES][MAX_VERTICES];
	int flows[MAX_VERTICES][MAX_VERTICES];
} Graph;

typedef struct { // Nhan cua cac dinh
	int dir; // > 0: 1, < 0 : -1 else 0
	int pre; // Dinh truoc do
	int sigma; // Luong tang luong
} Label; Label labels[MAX_VERTICES];

void init_graph(Graph *G, int numberOfVertics){
	G->numberOfVertics = numberOfVertics;
	int i, j;
	for(i = 1; i <= G->numberOfVertics; i++){
		for(j = 1; j <= G->numberOfVertics; j++){
			G->capacities[i][j] = NO_EDGE;
		}
	}
}

void add_edge(Graph *G, int u, int v, int capacity){
	G->capacities[u][v] = capacity;
} 


// INSTALL QUEUE
typedef struct {
	int front, rear;
	int data[MAX_VERTICES];
}Queue;

void make_null_queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
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

int empty_queue(Queue *Q){
	return Q->front > Q->rear;
}

// INSTALL STACK
typedef struct {
	int data[MAX_VERTICES];
	int top;
} Stack;

void make_null_stack(Stack *S){
	S->top = 0;
}

void push_stack(Stack *S, int x){
	S->data[S->top] = x;
	S->top++;
}

void pop_stack(Stack *S){
	S->top--;
}

int top_stack(Stack *S){
	return S->data[S->top];
}

int min(int a, int b){
	if(a < b) return a;
	else return b;
}

void init_flow(Graph *G){
	int u, v;
	for(u = 1; u <= G->numberOfVertics; u++){
		for(v = 1; v <= G->numberOfVertics; v++){
			G->flows[u][v] = 0;
		}
	}
}

int FordFullKerson(Graph *G, int s, int t){
	init_flow(G);
	Queue Q;
	int sum_flow = 0;
	int u, v;
	do{
		// Buoc 1: xoa nhan cac dinh va gan nhan cho s
		for(u = 1; u <= G->numberOfVertics; u++)
			labels[u].dir = 0;
			
		labels[s].dir = 1;
		labels[s].pre = s;
		labels[s].sigma = INF;
		
		make_null_queue(&Q); push_queue(&Q, s); // Dua s vao hang doi
		
		// Buoc 2: Lap va gan nhan cho cac dinh
		int found = 0;
		while(!empty_queue(&Q)){
			int x = top_queue(&Q); pop_queue(&Q);
			for(v = 1; v <= G->numberOfVertics; v++){
				// Xet cung thuan
				if(	labels[v].dir == 0 && G->capacities[x][v] != NO_EDGE && G->flows[x][v] < G->capacities[x][v])
				{
					labels[v].dir = 1;
					labels[v].pre = x;
					labels[v].sigma = min(labels[x].sigma, G->capacities[x][v] - G->flows[x][v]);
					push_queue(&Q, v);
				}
				
				// Xet cung nghich
				if(labels[v].dir == 0 && G->capacities[v][x] != NO_EDGE && G->flows[v][x] > 0){
					labels[v].dir = -1;
					labels[v].pre = x;
					labels[v].sigma = min(labels[x].sigma, G->flows[v][x]);
					push_queue(&Q, v);
				}
			}
			
			// Buoc 3: Kiem tra xem t da duoc gan nhan chua, neu roi thi tim duoc duong tang luong
			if(labels[t].dir != 0){
				found = 1; 
				break;
			}
		}
		// Buoc 4: Kiem tra xem co tim duoc duong tang luong nua khong
		if(found){
			// Buoc 5 - 6: tang luong, giam luong
			int T = t;
			int sigma = labels[t].sigma;
			sum_flow += sigma;
			while(T != s){
				int parent = labels[T].pre;
				if(labels[T].dir > 0) { // Tang luong
					G->flows[parent][T] += sigma;
				}
				else { // Giam luong
					G->flows[T][parent] -= sigma;
				}
				T = parent;
			}
		}
		else break;
	}while(1);
	
	return sum_flow;
}

int main(){
	Graph G;
	int numberOfVertics, numberOfEdges;
	freopen("luong_cuc_dai.txt", "r", stdin);
	scanf("%d %d", &numberOfVertics, &numberOfEdges);
	init_graph(&G, numberOfVertics);
	int i;
	for(i = 1; i <= numberOfEdges; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
//		printf("%d %d %d\n", u, v, w);
		add_edge(&G, u, v, w);
	}
	
	
	int max_flow = FordFullKerson(&G, 1, G.numberOfVertics);
	printf("Max flow: %d\n", max_flow);
	int XO[numberOfVertics + 1], YO[numberOfVertics + 1];
	int u;
	printf("X0: ");
	for(u = 1; u <= G.numberOfVertics; u++){
		if(labels[u].dir != 0)
			printf("%d ", u);
	}
	printf("\nYO: ");
	for(u = 1; u <= G.numberOfVertics; u++){
		if(labels[u].dir == 0)
			printf("%d ", u);
	}
	return 0;
}
