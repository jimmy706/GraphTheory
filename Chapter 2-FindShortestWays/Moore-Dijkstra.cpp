#include <stdio.h>
#define MAX_VERTICES 100
#define NO_EDGE -1
#define INFINITY 999

int mark[MAX_VERTICES];
int pi[MAX_VERTICES]; // Do dai duong di ngan nhat cua pi[i]
int parent[MAX_VERTICES]; // Dinh? lien truoc cua parent[i] tren duong di ngan nhat

typedef struct {
	int numberOfVertices;
	int Lengths[MAX_VERTICES][MAX_VERTICES];
}Graph;

void init_graph(Graph* G, int numberOfVertices){
	int i,j;
	if(numberOfVertices < 100){
		G->numberOfVertices = numberOfVertices;
		for( i = 1; i <= G->numberOfVertices; i++){
			for( j = 1; j <= G->numberOfVertices; j++){
				G->Lengths[i][j] = NO_EDGE;
			}
		}
	}
}

void add_edge(Graph *G, int x, int y, int length){
	if(length > 0 && length <= 100){
		G->Lengths[x][y] = length;
		G->Lengths[y][x] = length;
	}
}

void Dijkstra(Graph* G, int s) {
	int i, j, it;
	for(i = 1; i <= G->numberOfVertices; i++){
		mark[i] = 0;
		pi[i] = INFINITY;
	}
	pi[s] = 0;
	parent[s] = -1;
	for(it = 1; it <= G->numberOfVertices; it++){
		int min_pi = INFINITY;
		for(j = 1; j <= G->numberOfVertices; j++){
			if(mark[j] == 0 && pi[j] < min_pi){
				min_pi = pi[j];
				i = j;
			}
		}
		mark[i] = 1;
		for(j = 1; j <= G->numberOfVertices; j++){
			if(G->Lengths[i][j] != NO_EDGE && mark[j] == 0){
				if(pi[i] + G->Lengths[i][j] < pi[j]){
					pi[j] = pi[i] + G->Lengths[i][j];
					parent[j] = i;
				}
			}
		}
	}
}

int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, e;
	int i;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G,numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v, l;
		scanf("%d%d%d",&u, &v, &l);
//		printf("\n u = %d & v = %d & length = %d", u, v, l);
		add_edge(&G, u, v, l);
	}	
	
	Dijkstra(&G, 1);
//	for(i = 1; i <= numberOfVertices; i++){
//		printf("\npi[%d] = %d, parent[%d] = %d",i, pi[i], i, parent[i]);
//	}
	if(pi[numberOfVertices] == INFINITY)
		printf("-1");
	else
		printf("%d", pi[numberOfVertices]);
	
	return 0;
}
