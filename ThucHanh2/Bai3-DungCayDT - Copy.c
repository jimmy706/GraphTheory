#include <stdio.h>
#define MAX_VERTICES 100
int mark[MAX_VERTICES];
int parent[MAX_VERTICES];
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

void visit(Graph *G, int vertice, int p){
	if(mark[vertice]) return;
	parent[vertice] = p;
	
	mark[vertice] = 1;
	int i;
	for(i = 1; i <= G->numberOfVertices; i++){
		if(G->Arr[vertice][i]){
			visit(G, i, vertice);
		}
	}
}

void depth_first_search(Graph *G, int x){
	visit(G, x, 0);
}

int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, e, v;
	freopen("dt.txt", "r", stdin);
	
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	initGraph(&G, numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v;
		scanf("%d%d",&u, &v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= numberOfVertices; i++){
		mark[i] = 0;
	}
	for(i = 1; i <= numberOfVertices; i++){
		parent[i] = 0;
	}
		
	
	for(j = 1; j <= G.numberOfVertices; j++){
		if(mark[j] == 0){
			depth_first_search(&G, j);
		}
	}
	
	
	for(j = 1; j <= numberOfVertices; j++){
		printf("%d %d\n", j, parent[j]);
	}
	
	return 0;
}
