#include <stdio.h>
#define MAX_VERTICES 100
#define NO_EDGE -1

typedef struct {
	int numberOfVertices;
	int Lengths[MAX_VERTICES][MAX_VERTICES];
}Graph;

void init_graph(Graph* G, int numberOfVertices){
	int i,j;
	G->numberOfVertices = numberOfVertices;
	for( i = 1; i <= G->numberOfVertices; i++){
		for( j = 1; j <= G->numberOfVertices; j++){
			G->Lengths[i][j] = NO_EDGE;
		}
	}
}

void add_edge(Graph *G, int x, int y, int length){
	G->Lengths[x][y] = length;
}



int main(){
	return 0;
}
