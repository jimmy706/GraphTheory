#include <stdio.h>
#define MAX_VERTICES 100
#define MAX_EDGES 100

int parent[MAX_VERTICES];

typedef struct {
	int x,y;
	int w; // trong so
}Edge;

typedef struct {
	int numberOfVertices, numberOfEdges;
	Edge edges[MAX_EDGES];
} Graph;

void init_graph(Graph *G, int numberOfVertices){
	G->numberOfVertices = numberOfVertices;
	G->numberOfEdges = 0;
}

void add_edge(Graph *G,int x, int y, int w){
	Edge newEdge;
	newEdge.x = x;
	newEdge.y = y;
	newEdge.w = w;
	G->edges[G->numberOfEdges] = newEdge;
	G->numberOfEdges++;
}

void sort_edges(Graph *G){
	int i, j;
	for(i = 0; i < G->numberOfEdges - 1; i++){
		for(j = i + 1; j < G->numberOfEdges; j++){
			if(G->edges[j].w < G->edges[i].w){
				Edge temp = G->edges[i];
				G->edges[i] = G->edges[j];
				G->edges[j] = temp;
			}
		}
	}
}

int find_root(int vertice){
	if(parent[vertice] = vertice) return vertice;
	else return find_root(parent[vertice]);
}

int Krusal(Graph *G, Graph *T){
	sort_edges(G);
	
	init_graph(T, G->numberOfEdges);
	int u, e = 0, sum_w = 0;
	for(u = 1; u <= G->numberOfVertices; u++){
		parent[u] = u;
	}
	
	while(T->numberOfEdges < G->numberOfVertices - 1){
		int x = G->edges[e].x;
		int y = G->edges[e].y;
		int w = G->edges[e].w;
		int root_x = find_root(x);
		int root_y = find_root(y);
		if (root_x != root_y){
			add_edge(T,x,y,w);
			parent[root_y] = root_x;
			sum_w += w;
		}	
		e++;
	}
	return sum_w;
}

int main(){
	Graph G,T;
	int numberOfVertices, numberOfEdges;
	freopen("dt.txt", "r", stdin);
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G, numberOfVertices);
	
	int e;
	for(e = 0; e < numberOfEdges; e++){
		int x, y, w;
		scanf("%d%d%d",&x, &y, &w);
		add_edge(&G,x,y,w);
	}
	
	printf("%d\n", Krusal(&G, &T));
	sort_edges(&T);
	for(e = 0; e < T.numberOfEdges; e++){
		if(T.edges[e].x < T.edges[e].y){
			printf("%d %d %d\n", G.edges[e].x, G.edges[e].y, G.edges[e].w);
		}
		else if (T.edges[e].y < T.edges[e].x){
			printf("%d %d %d\n", G.edges[e].y, G.edges[e].x, G.edges[e].w);
		}
	}
	return 0;
}
