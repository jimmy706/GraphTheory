#include <stdio.h>
#include <D:\GraphTheory-master\GraphTheory-master\libary\list_lib.cpp>
#include <D:\GraphTheory-master\GraphTheory-master\libary\stack_lib.cpp>
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
	int y = 1;
	for( y ; y <= G->numberOfVertices; y++){
		if(adjacent(G,x,y))
			push(&list,y);
	}
	
	return list;
}

void depth_first_search(Graph *G){
	Stack frontier;
	int mark[MAX_VERTICES];
	make_null_stack(&frontier);
	
	// khoi tao mark, chua dinh nao duoc xet
	for(int i = 1; i <= G->numberOfVertices; i++){
		mark[i] = 0;
	}
	
	// dua dinh? 1 vao frontier va danh dau no
	push(&frontier, 1);
	mark[1] = 1;
	
	// vong lap chinh dung de duyet do thi
	while(!empty(&frontier)){
		// lay phan tu dau tien trong frontier ra
		int x = top(&frontier); pop(&frontier);
		printf("duyet: %d\n", x);
		
		// Lay cac dinh ke cua x
		List list = neighbours(G, x);
		
		// Xet cac dinh ke cua x, neu chua duoc danh dau thi duyet no
		for(int j = 1; j <= list.last; j++){
			int y = element_at(&list, j);
			if(mark[y] == 0){
				mark[y] = 1;
				push(&frontier, y);
			}
		}
	}
}

int main(){
	Graph G;
	
	
	init_graph(&G,4);	
	add_edge(&G,1,2);
	add_edge(&G,1,3);
	add_edge(&G,1,3);
	add_edge(&G,3,4);
	add_edge(&G,1,4);
	
//	for(int i = 1; i <= G.numberOfVertices; i++){
//		printf("deg(%d) = %d\n", i, degree(&G,i));
//	}
	
//	// find neighbors of vertice 1
//	printf("\nVertices which adjacent with 1 are: ");
//	List list = neighbours(&G,1);
//	for(int i = 1; i <= list.last; i++){
//		printf("%d ", element_at(&list, i));
//	}
	depth_first_search(&G);
	
//	int maxDeg = 0;
//	freopen("dt.txt", "r", stdin); 
//	Graph G;
//	int n, m, u, v, w, e;
//	scanf("%d%d", &n, &m);
//	init_graph(&G, n);
//	
//	for (e = 0; e < m; e++) {
//		scanf("%d%d", &u, &v);
//		add_edge(&G, u, v);
//	}
//	
//	for(int y = 1; y <= n; y++){
//		if(degree(&G, y) > maxDeg)
//			maxDeg = degree(&G, y);
//	}
//	for(int y = 1; y <= n; y++){
//		if(degree(&G, y) == maxDeg)
//			printf("%d ", y);
//	}
//	
//	printf("%d", maxDeg);
	
	
	
	
	
	return 0;
}
