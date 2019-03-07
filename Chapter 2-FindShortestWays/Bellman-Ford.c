#include <stdio.h>
#define MAX_EDGES 100
#define MAX_VERTICES 100
#define INFINITY 999

int mark[MAX_VERTICES];
int pi[MAX_VERTICES]; 
int parent[MAX_VERTICES]; 

typedef struct {
	int x, y;
	int length;
}Edge;

typedef struct {
	int numberOfVertices, numberOfEdges;
	Edge edges[MAX_EDGES];
}Graph;

void init_graph(Graph* G, int numberOfVertices){
	G->numberOfVertices = numberOfVertices;
	G->numberOfEdges = 0;
}

void add_edge(Graph *G, int x, int y, int length){
	Edge edge;
	edge.x = x;
	edge.y = y;
	edge.length = length;
	
	G->edges[G->numberOfEdges] = edge;
	G->numberOfEdges++;
}

void BellmanFord(Graph *G, int s){
	int i, e, it;
	for(i = 1; i <= G->numberOfVertices; i++){
		pi[i] = INFINITY;
	}
	pi[s] = 0;
	parent[s] = -1;
	
	for(it = 1; it < G->numberOfVertices; it++){
		for(e = 0; e < G->numberOfEdges; e++){
			int x = G->edges[e].x;
			int y = G->edges[e].y;
			int length = G->edges[e].length;
			if(pi[x] + length < pi[y]){
				parent[y] = x;
				pi[y] = pi[x] + length;
			}
		}
	}
}

int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, e;
	int i;
	freopen("bellman.txt", "r", stdin);
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G,numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v, l;
		scanf("%d%d%d",&u, &v, &l);
//		printf("\n u = %d & v = %d & length = %d", u, v, l);
		add_edge(&G, u, v, l);
	}	
	
	BellmanFord(&G, 1);
	for(i = 1; i <= numberOfVertices; i++){
		printf("pi[%d] = %d, p[%d] = %d\n",i, pi[i], i, parent[i]);
	}
		
	
	return 0;
}
