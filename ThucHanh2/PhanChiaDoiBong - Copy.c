#include <stdio.h>
#define MAX_VERTICES 100
#define MAXLENGTH 100
#define WHITE -1
#define BLUE 0
#define RED 1

int mark[MAX_VERTICES];
int i, j;
int colors[MAX_VERTICES];
int conflict;

typedef int ElementType;
typedef struct {
	int data [MAXLENGTH];
	ElementType last;
}List;

void make_null(List * L){
	L->last = 0;
}

void push_back(List *L, ElementType ele){
	L->data[L->last] = ele;
	L->last++;
}

ElementType element_at(List *L, int position){
	return L->data[position - 1];
}

ElementType length(List *L){
	return L->last;
}


// INSTALL GRAPH
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

int adjacent(Graph *G, int x, int y){
	return G->Arr[x][y];
}

List neighbours (Graph* G, int x) {
	List list;
	make_null(&list);
	int y = 1;
	for( y ; y <= G->numberOfVertices; y++){
		if(adjacent(G,x,y))
			push_back(&list,y);
	}
	
	return list;
}

void colorize(Graph *G, int x, int color){
	if(colors[x] == WHITE){
		colors[x] = color;
		List list = neighbours(G, x);
		int i;
		for(i = 1; i <= list.last; i++){
			int y = element_at(&list, i);
			colorize(G,y,!color);
		}
	}
	else if(colors[x] != color){
		conflict = 1;
		return;
	}
}

int is_bigraph(Graph *G){
	int j;
	for(j = 0; j <= G->numberOfVertices; j++){
		colors[j] = WHITE;
	}
	conflict = 0;
	colorize(G,1,BLUE);
	return !conflict;
}



int main () {
	Graph G;
	int numberOfVertices, numberOfEdges, e, isAllMarked = 0;
	freopen("bioGraph.txt", "r", stdin);
	
	scanf("%d%d", &numberOfVertices, &numberOfEdges);
	initGraph(&G, numberOfVertices);
	
	for(e = 1; e <= numberOfEdges; e++){
		int u, v;
		scanf("%d%d",&u, &v);
//		printf("\n u = %d & v = %d", u, v);
		add_edge(&G, u, v);
	}
	
	if(is_bigraph(&G)){
		int v, w;
		for(v = 1; v <= numberOfVertices; v++){
			if(colors[v] == BLUE)
				printf("%d ", v);
		}
		printf("\n");
		for(w = 1; w <= numberOfVertices; w++){
			if(colors[w] == RED)
				printf("%d ", w);
		}
	}		
	else
		printf("IMPOSSIBLE");
		
	return 0;
}
