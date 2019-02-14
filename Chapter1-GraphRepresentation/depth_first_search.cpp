


// --------------------DUYET THEO CHIEU SAU BINH THUONG--------------------
/*
void depth_first_search(Graph *G){
	Stack S;
	make_null_stack(&S);
	int mark[MAX_VERTICES];
	
	// Khoi tao mark, chua dinh nao duoc duyet
	int j;
	for(j = 1; j <= G->numberOfVertices; j++){
		mark[j] = 0;
	}
	
	// Dua dinh? 1 vao stack, bat dau duyet tu dinh? 1
	push(&S, 1);
	
	while(!empty(&S)){
		int x = top(&S); pop(&S); // Lay dinh? tren cung cua stack ra
		if(mark[x]) continue; // Neu da duyet roi thi bo qua, den vong lap ke tiep
		
		printf("Marked: %d\n", x);
		mark[x] = 1; // Danh dau da duyet
		
		List list = neighbours(G, x); //Lay cac dinh? ke` cua dinh? x
		for(j = 1; j <= list.last; j++){
			int y = element_at(&list, j);
			push(&S, y);
		}
	}
}

*/



// --------------------DUYET THEO CHIEU SAU SU DUNG DE QUI--------------------

int mark[MAX_VERTICES];


// Duyet de qui dinh? x
void traversal(Graph *G, int x){	
	if(mark[x]) return;
	
	printf("Marked: %d\n", x);
	mark[x] = 1;
	
	List list = neighbours(G, x);
	int j;
	for(j=1; j <= list.last; j++){
		traversal(G, element_at(&list, j));
	}
}

void depth_first_search(Graph *G){
	int i;
	for(i = 1; i <= G->numberOfVertices; i++){
		mark[i] = 0;
	}
	
	traversal(G, 1);
}

