#include <stdio.h>
#define MAX_VERTICES 100

int mark[MAX_VERTICES];
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

void visit(Graph *G, int vertice){
	if(mark[vertice]) return;
	
	mark[vertice] = 1;
	for(i = 1; i <= G->numberOfVertices; i++){
		if(G->Arr[vertice][i]){
			visit(G, i);
		}
	}
}

int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, e, isAllMarked = 0;
	freopen("dt.txt", "r", stdin);
	
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	initGraph(&G, numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v;
		scanf("%d%d",&u, &v);
		printf("\n u = %d & v = %d", u, v);
		add_edge(&G, u, v);
	}
	
	for(i = 1; i <= numberOfVertices; i++){
		mark[i] = 0;
	}
	
	visit(&G, 1);
	for(i = 1; i < G.numberOfVertices; i++){
		if(!mark[i]) {
			isAllMarked = 0;
			continue;
		}
	}
	
	if(isAllMarked)
		printf("\nDo thi lien thong");
	else
		printf("\nDo thi khong lien thong");
	return 0;
}
