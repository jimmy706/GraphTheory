#include <stdio.h>
#define MAX_VERTICES 100
#define WHITE 0 // Not marked yet
#define GRAY 1 // marked but not mark all of its adjacents
#define BLACK 2 // marked and also marked all of its adjacents

int mark[MAX_VERTICES];
int i, j;
int colors[MAX_VERTICES];
int cycle;


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
	// Graph directed
	G->Arr[x][y] = 1;
}

int adjacent(Graph *G, int x, int y){
	return G->Arr[x][y];
}

void visit(Graph *G, int vertice){
	colors[vertice] = GRAY; // marking
	for(i = 1; i <= G->numberOfVertices; i++){
		if(adjacent(G, vertice, i)){
			if(colors[i] == GRAY){
				cycle = 1;
				return;
			}
			else if(colors[i] == WHITE){
				visit(G, i);
			}				
		}
	}
	colors[vertice] = BLACK;
}

int contains_cycle(Graph *G){
	int i,j;
	cycle = 0;
	
	for(j = 1; j <= G->numberOfVertices; j++){
		colors[j] = WHITE;
	}
	
	for(j = 1; j <= G->numberOfVertices; j++){
		if(colors[j] == WHITE)
			visit(G, j);
	}
	return cycle;
}




int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, e, isAllMarked = 0;
	freopen("E:/LyThuyetDoThi/cyle_graph.txt", "r", stdin);
	
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	initGraph(&G, numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v;
		scanf("%d%d",&u, &v);
		printf("\n u = %d & v = %d", u, v);
		add_edge(&G, u, v);
	}		
	
	if(contains_cycle(&G))
		printf("\n Do thi ton tai chu trinh");
	else
		printf("\n Do thi ko ton tai chu trinh");
		
	return 0;
}
