#include <stdio.h>
#include <E:\LyThuyetDoThi\libary\list_lib.cpp>
#define MAX_VERTICES 100

typedef struct {
	int numberOfVertices;
	List adjList[MAX_VERTICES];
}Graph;

void init_graph(Graph *G, int numberOfVertices){
	G->numberOfVertices = numberOfVertices;
	for(int i = 1; i <=numberOfVertices; i++)
		make_null(&G->adjList[i]);
}

void add_edge(Graph * G, int x, int y){
	push(&G->adjList[x], y);
	push(&G->adjList[y], x);
}

int adjacent(Graph *G, int x, int y){
	for(int i = 1; i <= G->numberOfVertices; i++){
		if(element_at(&G->adjList[x], i) == y){
			return 1;
		}			
	}
	return 0;
}

int degree(Graph *G, int x){
	return length(&G->adjList[x]);
}


int main(){
	
	return 0;
}
