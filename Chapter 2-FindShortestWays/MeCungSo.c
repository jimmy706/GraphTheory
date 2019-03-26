#include <stdio.h>
#define MAX_VERTICES 100
#define NO_EDGE -1
#define INFINITY 999

int mark[MAX_VERTICES];
int pi[MAX_VERTICES]; // Do dai duong di ngan nhat cua pi[i]
int parent[MAX_VERTICES]; // Dinh? lien truoc cua parent[i] tren duong di ngan nhat
int matrix[MAX_VERTICES][MAX_VERTICES];
int w[MAX_VERTICES]; // chua trong so cua ma tran

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
	int numberOfVertices, i, j, k, row, column, count = 0;
	freopen("matrix.txt", "r", stdin);
	scanf("%d%d", &row, &column);
	numberOfVertices = row * column;
	init_graph(&G,numberOfVertices);
	
	for(i = 0; i < row; i++){
		for(j = 0; j < column; j++){
			int length;
			scanf("%d", &length);
			matrix[i][j] = length;
		}
	}
	
	for(i = 0; i < row; i++){
		for(j = 0; j < column; j++){
			int u = (i*column + j) + 1;
			w[u] = matrix[i][j];
		}
	}
	
	int di[] = {-1, 1, 0, 0};
	int dj[] = {0, 0, 1, -1};
	int u;
	for(u = 1; u <= G.numberOfVertices; u++){
		int i = (u-1)/column;
		int j = (u-1)%column;
		for(k = 0; k < 4; k++){
			int ii = i + di[k];
			int jj = j + dj[k];
			if(ii >= 0 && i < row && jj >= 0 && jj < column){
				int v = (ii*column + jj) + 1;
				add_edge(&G,u,v,w[v]);
			}
		}
	}
	Dijkstra(&G, 1);
	for(i = 1; i <= numberOfVertices; i++){
		printf("\npi[%d] = %d, parent[%d] = %d",i, pi[i], i, parent[i]);
	}
//	for(i = 1; i <= G.numberOfVertices; i++){
//		printf("\n w[%d] = %d", i, w[i]);
//	}
//	printf("%d",pi[numberOfVertices]);
	
	return 0;
}
