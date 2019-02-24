#include <stdio.h>
#define MAX_VERTICES 100
#define MAXLENGTH 100
#define WHITE 0 // Not marked yet
#define GRAY 1 // marked but not mark all of its adjacents
#define BLACK 2 // marked and also marked all of its adjacents

int mark[MAX_VERTICES];
int i, j;
int colors[MAX_VERTICES];
int cycle;

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


void dfs(Graph *G, int x, int parent){
	colors[x] = GRAY;
	int j;
	List list = neighbours(G, x);
	for(j = 1; j <= list.last; j++){
		int y = element_at(&list, j);
		if(y == parent) continue;
		if(colors[y] == GRAY){
			cycle = 1;
			return;
		}
		if(colors[y] == WHITE){
			dfs(G,y,x);
		}
	}
	colors[x] = BLACK;
}

int contains_cycle(Graph *G){
	int i,j;
	cycle = 0;
	
	for(j = 1; j <= G->numberOfVertices; j++){
		colors[j] = WHITE;
	}
	
	for(j = 1; j <= G->numberOfVertices; j++){
		if(colors[j] == WHITE)
			dfs(G, j, 0);
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
		add_edge(&G, u, v);
	}		
	
	if(contains_cycle(&G))
		printf("YES");
	else
		printf("NO");
		
	return 0;
}
