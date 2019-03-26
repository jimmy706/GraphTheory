#include <stdio.h>
#define MAX_VERTICES 100
#define infinity 999

int ranks[MAX_VERTICES];
int mark[MAX_VERTICES];

// Thoi gian som nhat hoan thanh cong viec u
int times[MAX_VERTICES]; 

// Thoi diem tre nhat bat dau cong viec u ma ko anh huong den tien do du an
int Times[MAX_VERTICES]; 

// Trong so dinh u
int d[MAX_VERTICES];

typedef struct{
	int numberOfVertices;
	int arr[MAX_VERTICES][MAX_VERTICES];
}Graph;


void init_graph(Graph *G, int numberOfVertices){
	int i,j;
	G->numberOfVertices = numberOfVertices;
	for( i = 1; i <= G->numberOfVertices; i++){
		for( j = 1; j <= G->numberOfVertices; j++){
			G->arr[i][j] = 0;
		}
	}
}

void add_edge(Graph *G, int x, int y){
	G->arr[x][y]++;
}

int adjacent(Graph * G, int x, int y){
	return G->arr[x][y] != 0 ;
}

int degree(Graph *G, int x){
	int deg = 0;
	int y;
	for( y = 1; y <= G->numberOfVertices; y++)
		deg += G->arr[x][y];
	 	
	return deg;
}

// -------------------------------- INSTALL LIST------------------------------
typedef struct {
	int data[MAX_VERTICES];
	int last;
}List;

void make_null_list(List *l){
	l->last = 0;
}

void push_back(List *l, int num){
	l->data[l->last] = num;
	l->last++;
}

int element_at(List *l, int position){
	return l->data[position - 1];
}

// Tao rong s1 va copy cac phan tu cua s2 vao s1
void copy_list(List *s1, List *s2){
	make_null_list(s1);
	int i;
	for(i = 1; i <= s2->last; i++){
		push_back(s1, element_at(s2, i));
	}
}

// INSTALL QUEUE
typedef struct {
	int data[MAX_VERTICES];
	int front, rear;
} Queue;

void make_null_queue(Queue *Q){
	Q->front = 0;
	Q->rear = -1;
}

int empty_queue(Queue *Q){
	return Q->front > Q->rear;
}

void push_queue(Queue *Q, int x){
	Q->rear++;
	Q->data[Q->rear] = x;
}

void pop_queue(Queue *Q){
	Q->front++;
}

int top_queue(Queue *Q){
	return Q->data[Q->front];
}



void ranking(Graph *G){
	int degreeIn[MAX_VERTICES];
	int x,u;
	
	for(x = 1; x <= G->numberOfVertices; x++){
		degreeIn[x] = 0;
	}
	
	for(x = 1; x <= G->numberOfVertices; x++){
		for(u = 1; u <= G->numberOfVertices; u++){
			if(G->arr[x][u] != 0) degreeIn[u]++;
		}
	}
	
	List S1, S2;
	make_null_list(&S1);
	int rank = 0, i;
	
	for(i = 1; i <= G->numberOfVertices; i++){
		if(degreeIn[i] == 0) push_back(&S1, i);
	}
	
	
	while(S1.last > 0){
		make_null_list(&S2);
		for(i = 1; i <= S1.last; i++){
			int u = element_at(&S1, i);
			ranks[u] = rank;
			int v;
			for(v = 1; v <= G->numberOfVertices; v++){
				if(G->arr[u][v] != 0){
					degreeIn[v]--;
					if(degreeIn[v] == 0)
						push_back(&S2, v);
				}
			}
		}
		copy_list(&S1, &S2);
		rank++;
	}
}


void topo_sort(Graph *G, List *L){
	make_null_list(L);
	int degreeIn[MAX_VERTICES];
	int x,u;
	Queue Q;
	make_null_queue(&Q);
	
	for(x = 1; x <= G->numberOfVertices; x++){
		degreeIn[x] = 0;
	}
	
	for(x = 1; x <= G->numberOfVertices; x++){
		for(u = 1; u <= G->numberOfVertices; u++){
			if(G->arr[x][u] != 0) degreeIn[u]++;
		}
	}
	
	int rank = 0, i;
	
	for(i = 1; i <= G->numberOfVertices; i++){
		if(degreeIn[i] == 0) push_queue(&Q, i);
	}
	
	while(!empty_queue(&Q)){
		int u = top_queue(&Q); pop_queue(&Q);
		push_back(L, u);
		int v;
		for(v = 1; v <= G->numberOfVertices; v++){
			if(G->arr[u][v] != 0){
				degreeIn[v]--;
				if(degreeIn[v] == 0) push_queue(&Q, v);
			}
		}
	}
}

int max(int a, int b){
	if(a > b) return a;
	else return b;
}

int min(int a, int b){
	if(a < b) return a;
	else return b;
}

int main(){
	Graph G;
	List L;
	int n, numberOfVertices, u;
	freopen("to_chuc_thi_cong.txt", "r", stdin);
	scanf("%d", &n);
	numberOfVertices = n + 2; // Tao them 2 dinh alpha & beta 
	init_graph(&G, numberOfVertices); 
	
	// 1. Doc va khoi tao do thi
	for(u = 1; u <= n; u++){
		scanf("%d", &d[u]);
		int x;
		do{
			scanf("%d", &x);
			if(x > 0) add_edge(&G, x, u);
		}
		while(x > 0);
	}
	
	// 2. Them cung alpha vao dinh co bac vao = 0
	for(u = 1; u <= n; u++){
		int degIn = 0;
		int v;
		for(v = 1; v <= n; v++){
			if(G.arr[v][u] > 0) degIn++;
		}
		
		if(degIn == 0) {
			add_edge(&G, n + 1, u); // alpha la dinh n + 1
			continue;
		}
	}
	
	// 3. Them cung beta vao dinh co bac ra = 0
	for(u = 1; u <= n; u++){
		int degOut = 0;
		int v;
		for(v = 1; v <=n; v++){
			if(G.arr[u][v] > 0) degOut++;
		}
		
		if(degOut == 0) add_edge(&G, u, n + 2); // Dinh beta la dinh n + 2
	}
	
	// 4. Xep thu tu cac dinh va luu vao trong list
	topo_sort(&G, &L);
	
	// 5. tinh times[u]
	int i, j;
	
	for(i = 1; i <= L.last; i++){
		int u = element_at(&L, i);
		times[u] = 0;
	}
	for(i = 2; i <= L.last; i++){
		int u = element_at(&L, i);
		// for cac dinh ke cua u
		for(j = 1; j <= G.numberOfVertices; j++){
			if(G.arr[u][j] > 0)
				times[j] = max(times[j], times[u] + d[u]);
		}
	}
	
	// 6. Tinh Times[u]
	for(i = L.last - 1; i >= 1; i--){
		int v = element_at(&L, i);
		Times[v] = infinity;
	}
	Times[n + 2] = times[n + 2];
	for(i = L.last; i >= 1; i--){
		int v = element_at(&L, i);
		for(j = 1; j <= G.numberOfVertices; j++){
			if(G.arr[j][v] > 0)
				Times[j] = min(Times[j], Times[v] - d[j] );
		}
	}
	int cong_viec, thoi_gian;
	scanf("%d %d", &cong_viec, &thoi_gian);
	if(thoi_gian >= times[cong_viec] && thoi_gian <= Times[cong_viec])
		printf("YES");
	else
		printf("NO");
	
	return 0;
}
