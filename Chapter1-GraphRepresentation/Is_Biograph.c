#include <stdio.h>
#define MAX_VERTICES 100
#define WHITE -1
#define BLUE 0
#define RED 1

int mark[MAX_VERTICES];
int i, j;
int colors[MAX_VERTICES];
int conflict;

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

void colorize(Graph *G, int vertice,int color){
	colors[vertice] = color;
	for(i = 1; i <= G->numberOfVertices; i++){
		if(colors[i] == WHITE){
			colorize(G,i,!color);
		}
		else if(colors[i] != color){
			conflict = 1;
			return;
		}
	}
}

int is_bigraph(Graph *G){
	conflict = 0;
	int j;
	for(j = 1; j <= G->numberOfVertices; j++){
		colors[j] = WHITE;
	}
	
	colorize(G, 1, BLUE);
	return !conflict;
}


int main () {
	Graph G;
	int numberOfVertices, numberOfEdges, e, isAllMarked = 0;
	freopen("E:/tony/truong dai hoc/GraphTheory/dt.txt", "r", stdin);
	
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	initGraph(&G, numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v;
		scanf("%d%d",&u, &v);
		printf("\n u = %d & v = %d", u, v);
		add_edge(&G, u, v);
	}
	
	int isBigraph = is_bigraph(&G);
	
	if(isBigraph)	
		printf("\n Do thi phan doi");
	else
		printf("\n Do thi ko phan doi");0
		
	
	
	
	return 0;
}
