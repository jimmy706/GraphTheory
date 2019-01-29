#include <stdio.h>
#include <D:\GraphTheory-master\GraphTheory-master\libary\list_lib.cpp>
#define MAX_VERTICES 100
#define MAX_EDGES 500

typedef struct {
	int numberOfVertices, numberOfEdges;
	int matrix[MAX_VERTICES][MAX_EDGES];
}Graph;


void init_graph(Graph *G, int numberOfVertices, int numberOfEdges){
	G->numberOfVertices = numberOfVertices;
	G->numberOfEdges = numberOfEdges;
	
	for(int i = 1; i <= numberOfVertices; i++){
		for(int j = 1; j <= numberOfEdges; j++){
			G->matrix[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int edge, int x, int y){
	G->matrix[x][edge] = 1;
	G->matrix[y][edge] = 1;
}

int degree(Graph* G, int x){
	int deg = 0;
	for(int e = 1; e <= G->numberOfEdges; e++){
		if(G->matrix[x][e] == 1) deg++;
	}
	
	return deg;
}

int adjacent(Graph* G, int x, int y){
	for(int e = 1; e <= G->numberOfEdges; e++){
		if(G->matrix[x][e] == 1 && G->matrix[y][e] == 1 && x != y /* dong nay check khi dinh? ko phai khuyen */)
			return 1;
	}
	return 0;
}

//void neighbours (Graph* G, int x){
//	printf("Vertices which adjacent with %d are: \n", x);
//	for(int y = 1; y <= G->numberOfVertices; y++){
//		if(adjacent(G,x,y))
//			printf("%3d",y);
//	}
//}

List neighbors(Graph* G, int x){
    List list;
    make_null(&list);
    for(int y = 1; y <= G->numberOfVertices; y++){
        if(adjacent(G,x,y))
            push(&list, y);
    }
    
    return list;
}


int main(int argc[]){
	Graph G;
	int numberOfVertices, numberOfEdges;	
	int x,y;
	FILE* file = fopen("D:/GraphTheory-master/GraphTheory-master/Chapter1-GraphRepresentation/graph_vertice-edge.txt", "r");
	
	fscanf(file, "%d%d", &numberOfVertices, &numberOfEdges);
	init_graph(&G,numberOfVertices,numberOfEdges);
	
	for(int e = 1; e <= numberOfEdges; e++){
		fscanf(file, "%d%d", &x, &y);
		add_edge(&G,e,x,y);
	}
	
	for(int x = 1; x <= numberOfVertices; x++){
		for(int y = 1; y <= numberOfVertices; y++){
			printf("%d ", adjacent(&G,x,y));
		}
		printf("\n");
	}


//	init_graph(&G, 4, 5);	
//	add_edge(&G,1,1,2);
//	add_edge(&G,2,1,3);
//	add_edge(&G,3,1,3);
//	add_edge(&G,4,3,4);
//	add_edge(&G,5,1,4);
//	
//	for(int i = 1; i <= G.numberOfVertices; i++){
//		printf("deg(%d) = %d\n", i, degree(&G,i));
//	}
//	
//	// find neighbors of vertice 1
//	printf("\nVertices which adjacent with 1 are: ");
//	List list = neighbors(&G,1);
//	for(int i = 1; i <= list.last; i++){
//		printf("%d ", element_at(&list, i));
//	}

	

	return 0;
}










