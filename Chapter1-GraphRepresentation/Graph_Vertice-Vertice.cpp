#include <stdio.h>
#include <E:\LyThuyetDoThi\libary\list_lib.cpp>
#define MAX_VERTICES 100

typedef struct {
	int numberOfVertices;
	int matrix[MAX_VERTICES][MAX_VERTICES];
}Graph;

void init_graph(Graph* G, int numberOfVertices){
	G->numberOfVertices = numberOfVertices;
	for(int i = 1; i <= G->numberOfVertices; i++){
		for(int j = 1; j <= G->numberOfVertices; j++){
			G->matrix[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y){
	G->matrix[x][y] += 1;
	G->matrix[y][x] += 1;
}

int adjacent(Graph * G, int x, int y){
	return G->matrix[x][y] != 0 ;
}

int degree(Graph *G, int x){
	int deg = 0;
	for(int y = 1; y <= G->numberOfVertices; y++)
		deg += G->matrix[x][y];
	 	
	return deg;
}

//void neighbours (Graph* G, int x){
//	printf("Vertices which adjacent with %d are: \n", x);
//	for(int y = 1; y <= G->numberOfVertices; y++){
//		if(adjacent(G,x,y))
//			printf("%3d",y);
//	}
//}

List neighbours (Graph* G, int x) {
	List list;
	make_null(&list);
	for(int y = 1; y <= G->numberOfVertices; y++){
		if(adjacent(G,x,y))
			push(&list,y);
	}
	
	return list;
}

int main(){
	Graph G;
	
	
	init_graph(&G,4);	
	add_edge(&G,1,2);
	add_edge(&G,1,3);
	add_edge(&G,1,3);
	add_edge(&G,3,4);
	add_edge(&G,1,4);
	
	for(int i = 1; i <= G.numberOfVertices; i++){
		printf("deg(%d) = %d\n", i, degree(&G,i));
	}
	
	// find neighbors of vertice 1
	printf("\nVertices which adjacent with 1 are: ");
	List list = neighbours(&G,1);
	for(int i = 1; i <= list.last; i++){
		printf("%d ", element_at(&list, i));
	}
	return 0;
}
