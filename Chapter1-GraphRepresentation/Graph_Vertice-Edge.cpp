#include <stdio.h>
#include <E:\LyThuyetDoThi\libary\list_lib.cpp>
#define MAX_VERTICES 100
#define MAX_EDGES 500

typedef struct {
	int numberOfVertices, numberOfEdges;
	int matrix[MAX_VERTICES][MAX_EDGES];
}Graph;

void init_graph(Graph *G, int numberOfVertices, int numberOfEdges){
	G->numberOfVertices = numberOfVertices;
	G->numberOfEdges = numberOfEdges;
	
	for(int i = 1; i <= numberOfVertices; i++){
		for(int j = 1; j <= numberOfEdges; j++){
			G->matrix[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int edge, int x, int y){
	G->matrix[x][edge] = 1;
	G->matrix[y][edge] = 1;
}

int degree(Graph* G, int x){
	int deg = 0;
	for(int e = 1; e <= G->numberOfEdges; e++){
		if(G->matrix[x][e] == 1) deg++;
	}
	
	return deg;
}

int adjacent(Graph* G, int x, int y){
	int isAdjacent = 0;
	for(int e = 1; e <= G->numberOfEdges; e++){
		if(G->matrix[x][e] == 1 && G->matrix[y][e] == 1){
				isAdjacent = 1;
				return isAdjacent;
		}			
	}
	return isAdjacent;
}

void neighbours (Graph* G, int x){
	printf("Vertices which adjacent with %d are: \n", x);
	for(int y = 1; y <= G->numberOfVertices; y++){
		if(adjacent(G,x,y))
			printf("%3d",y);
	}
}

int main(int argc[]){
	Graph G;
	int numberOfVertices, numberOfEdges;	
	int x,y;
	FILE* file = fopen("E:/LyThuyetDoThi/Chapter1-GraphRepresentation/graph_vertice-edge.txt", "r");
	
	fscanf(file, "%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G,numberOfVertices,numberOfEdges);
	
	for(int e = 1; e <= numberOfEdges; e++){
		fscanf(file, "%d%d", &x, &y);
		add_edge(&G,e,x,y);
	}
	
	for(int i = 1; i <= G.numberOfVertices; i++){
		printf("deg(%d) = %d\n", i, degree(&G,i));
	}
	return 0;
}










