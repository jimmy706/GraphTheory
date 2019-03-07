#include <stdio.h>
#define MAX_VERTICES 100
#define NO_EDGE -1
#define INFINITY 999

int mark[MAX_VERTICES];
int pi[MAX_VERTICES][MAX_VERTICES]; // pi[x][y] Chieu dai duong di ngan nhat tu x den y
int next[MAX_VERTICES][MAX_VERTICES]; //next[x][y] dinh ke tiep cua x tren duong di ngan nhat den y

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
	G->Lengths[x][y] = length;	
}

void FloydWarshall(Graph *G){
	int u,v,k;
	// Khoi tao
	for(u = 1; u <= G->numberOfVertices; u++){
		for(v = 1; v <= G->numberOfVertices; v++){
			pi[u][v] = INFINITY;
			next[u][v] = -1;
		}
	}
	
	for(u = 1; u <= G->numberOfVertices; u++)
		pi[u][u] = 0; // duong di ngan nhat tu u den u = 0
	
	for(u = 1; u <= G->numberOfVertices; u++){
		for(v = 1; v <= G->numberOfVertices; v++){
			if(G->Lengths[u][v] != NO_EDGE){
				pi[u][v] = G->Lengths[u][v];
				next[u][v] = v;
			}
		}
	}
	
	for(k = 1; k <= G->numberOfVertices; k++){
		for(u = 1; u <= G->numberOfVertices; u++){
			for(v = 1; v <= G->numberOfVertices; v++){
				if(pi[u][k] + pi[k][v] < pi[u][v]){
					pi[u][v] = pi[u][k] + pi[k][v];
					next[u][v] = next[u][k];
				}
			}
		}
	}
}


int main(){
	Graph G;
	int numberOfVertices, numberOfEdges, e;
	int i, j;
	freopen("floyd.txt", "r", stdin);
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G,numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v, l;
		scanf("%d%d%d",&u, &v, &l);
//		printf("\n u = %d & v = %d & length = %d", u, v, l);
		add_edge(&G, u, v, l);
	}
	
	FloydWarshall(&G);
//	printf("%d", pi[1][numberOfVertices]);
	for(i = 1; i <= numberOfVertices; i++){
		for(j = 1; j <= numberOfVertices; j++){
			if(pi[i][j] <= INFINITY - 100){
				printf("%d -> %d: %d\n",i,j,pi[i][j]);
			}
			else
				printf("%d -> %d: oo\n",i,j);
		}
	}
	
	return 0;
}
