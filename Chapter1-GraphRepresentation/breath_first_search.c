// Duyet do thi theo chieu rong
void breath_first_search(Graph *G){
	Queue queue;
	make_null_queue(&queue);
	int mark[MAX_VERTICES];
	
	// Khoi tao mark, chua dinh nao duoc duyet
	int j;
	for(j = 1; j <= G->numberOfVertices; j++){
		mark[j] = 0;
	}
	
	// Dua dinh? 1 vao stack, bat dau duyet tu dinh? 1
	push_queue(&queue, 1);
	mark[1] = 1;
	
	while(!empty_queue(&queue)){
		// Lay dinh? tren cung cua hang doi
		int x = top_queue(&queue); pop_queue(&queue);
		printf("Marked: %d\n", x);
		List list = neighbours(G, x); //Lay cac dinh? ke` cua dinh? x
		
		for(j = 1; j <= list.last; j++){
			int y = element_at(&list, j);
			if(mark[y] == 0){ // Neu y chua duyet thi duyet no				
				mark[y] = 1;
				push_queue(&queue, y);
			}
		}
	}
}
