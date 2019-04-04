#include <stdio.h>
#define MAX_VERTICES 100
#define MAX_EDGES 100
#define INFINITY 999

int parent[MAX_VERTICES]; // dinh trong S gan voi u nhat
int pi[MAX_VERTICES]; // pi[u]: Khoang cach tu u --> S
int mark[MAX_VERTICES];

typedef struct {
	int numberOfVertices;
	int arr[MAX_VERTICES][MAX_VERTICES];
} Graph;

void init_graph(Graph *G, int numberOfVertices){
	G->numberOfVertices = numberOfVertices;
	int u, v;
	for(u = 1; u <= numberOfVertices; u++){
		for(v = 1; v <= numberOfVertices; v++)
			G->arr[u][v] = 0;
	}	
}

void add_edge(Graph *G,int x, int y, int w){
	G->arr[x][y] = w;
}

// -- INSALL LIST --
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

// PRIM ALGORYTHM
int Prim(Graph *G, Graph *T){
	init_graph(T, G->numberOfVertices);
	int sum_w = 0;
	int i;
	for(i = 1; i <= G->numberOfVertices; i++){
		mark[i] = 0;
		pi[i] = INFINITY;
	}
	
	
	for(i = 1; i <= G->numberOfVertices; i++){
		if(G->arr[1][i] != 0){
			pi[i] = G->arr[1][i];
			parent[i] = 1;
		}
	}
	pi[1] = 0;
	mark[1] = 1;
	
	
	int u,v;
	for(i = 1; i < G->numberOfVertices; i++){
		int min_pi = INFINITY, min_u;
		for(u = 1; u <= G->numberOfVertices; u++){
			if(mark[u] == 0){
				if(min_pi > pi[u]){
					min_pi = pi[u];
					min_u = u;
				}				
			}
		}
		mark[min_u] = 1;
		add_edge(T, min_u, parent[min_u], min_pi);
		sum_w += min_pi;
		for(v = 1; v <= G->numberOfVertices; v++){
			if(G->arr[min_u][v] != 0 && mark[v] == 0){
				if(pi[v] > G->arr[min_u][v]){

					pi[v] = G->arr[min_u][v];
					parent[v] = min_u;
				}
			}
		}
	}
	return sum_w;
}

int main(){
	Graph G,T;
	int numberOfVertices, numberOfEdges;
	freopen("prim.txt", "r", stdin);
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G, numberOfVertices);
	
	int e;
	for(e = 0; e < numberOfEdges; e++){
		int x, y, w;
		scanf("%d%d%d",&x, &y, &w);
		add_edge(&G,x,y,w);
	}
	
	
	int u,v;
	int sum_w = Prim(&G, &T);
	printf("%d\n", sum_w);
	for(u = 1; u <= T.numberOfVertices; u++){
		for(v = 1; v <= T.numberOfVertices; v++){
			if(T.arr[u][v] != 0){
				if(u < v)
					printf("%d %d %d\n", u, v, T.arr[u][v]);
				else
					printf("%d %d %d\n", v, u, T.arr[u][v]);
			}
		}
	}
	return 0;
}
