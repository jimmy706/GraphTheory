#include <stdio.h>
#define MAX_VERTICES 100

int mark[MAX_VERTICES];
int i, j;
int mark[MAX_VERTICES];


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
	if(mark[vertice] == 1)
		return;
		
	mark[vertice] = 1;
	for(i = 1; i <= G->numberOfVertices; i++){
		if(G->Arr[vertice][i])
			visit(G, i);
	}
}

int count_connected_components(Graph *G){
	int count = 0;
	int i,j;
	for(i = 1; i <= G->numberOfVertices; i++){
		mark[i] = 0;
	}
	
	for(j = 1; j <= G->numberOfVertices; j++){
		if(mark[j] == 0){
			visit(G, j);
			count++;
		}
	}
	return count;
}




int main(){
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
	
	int count = count_connected_components(&G);
	
	printf("\n So bo phan lien thong co trong do thi la: %d ", count);
	
		
	return 0;
}
