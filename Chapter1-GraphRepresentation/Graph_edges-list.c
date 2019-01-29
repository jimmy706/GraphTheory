#include <stdio.h>
#include <D:\GraphTheory-master\GraphTheory-master\libary\list_lib.cpp>
#include <D:\GraphTheory-master\GraphTheory-master\libary\stack_lib.cpp>
#define MAX_EDGES 100

typedef struct {
	int x, y;
}Edge;

typedef struct {
	int numberOfVertices, numberOfEdges;
	Edge edges[MAX_EDGES];
}Graph;

void init_graph(Graph* G, int numberOfVertices){
	G->numberOfVertices = numberOfVertices;
	G->numberOfEdges = 0;
}

void add_edge(Graph *G, int x, int y){
	Edge edge;
	edge.x = x;
	edge.y = y;
	
	G->edges[G->numberOfEdges] = edge;
	G->numberOfEdges++;
}

int degree(Graph *G, int x){
	int deg = 0;
	int e = 0;
	for(e; e < G->numberOfEdges; e++){
		if(G->edges[e].x == x || G->edges[e].y == x)
			deg++;
	}
	return deg;
}

int adjacent(Graph *G, int x, int y){
	int e = 0;
	while(e < G->numberOfEdges){
		if(
			(G->edges[e].x == x && G->edges[e].y == y) ||
			(G->edges[e].y == x && G->edges[e].x == y)
		){
			return 1;
		}	
		e++;
	}
	
	return 0;
}


void neighbours (Graph* G, int x){
	printf("Vertices which adjacent with %d are: \n", x);
	int y = 1;
	for(y; y <= G->numberOfVertices; y++){
		if(adjacent(G,x,y))
			printf("%3d",y);
	}
}



int main(){
	Graph G;
	init_graph(&G, 4);
	
	add_edge(&G, 1, 2);
	add_edge(&G, 1, 3);
	add_edge(&G, 1, 4);
	add_edge(&G, 3, 1);
	add_edge(&G, 3, 4);
	int i = 1;
	for(i; i <= G.numberOfVertices; i++){
		printf("deg(%d) = %d\n", i, degree(&G,i));
	}
	
	neighbours(&G, 1);
	return 0;
}
