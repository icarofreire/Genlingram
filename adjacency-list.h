// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    void *value;
    int token;
    struct Node* next;
    //~ struct Node* previous;
};

// Structure to represent the graph(Adjacency List)
struct AdjacencyList {
    int numVertices;
    int idx;
    struct Node** adjLists;
    int visi[100];
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->token = 0;
    newNode->next = NULL;
    //~ newNode->previous = NULL;
    return newNode;
}

// Function to create a graph
struct AdjacencyList* createGraph(int vertices) {
    struct AdjacencyList* graph = malloc(sizeof(struct AdjacencyList));
    graph->numVertices = vertices;

    // Create an array of adjacency lists
    graph->adjLists = malloc(vertices * sizeof(struct Node*));

    // Initialize each adjacency list as empty
    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        //~ graph->visi[i][] = -1;
    }
    
    graph->idx = 0;//indice interator;

    return graph;
}

// Function to add an edge to the graph
//~ void addEdge(struct Graph* graph, int src, int dest) {
    //~ // Add edge from src to dest
    //~ struct Node* newNode = createNode(dest);
    //~ newNode->next = graph->adjLists[src];
    //~ graph->adjLists[src] = newNode;

    //~ // If the graph is undirected, add an edge from dest to src as well
    //~ if (!graph->isDirected) {
        //~ newNode = createNode(src);
        //~ newNode->next = graph->adjLists[dest];
        //~ graph->adjLists[dest] = newNode;
    //~ }
//~ }

void addEdge(struct AdjacencyList* graph, char* value, int token) {
	//~ graph->idx++;
	int src = graph->idx;
	int dest = graph->idx++;
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    newNode->value = value;
    newNode->token = token;
    graph->adjLists[src] = newNode;
}

void addEdgeNNodes(struct AdjacencyList* graph, int nNodesAnterior) {
	int src = graph->idx;
	if(nNodesAnterior){
		int dest = graph->idx-1;
		
		struct Node* newNode = graph->adjLists[dest];
		newNode->next = graph->adjLists[src];
		graph->adjLists[src] = newNode;
	}
}

// Function to print the adjacency list representation of the graph
void printGraph(struct AdjacencyList* graph) {
    printf("Vertex:  Adjacency List\n");
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        //~ printf("%d --->", v);
        while (temp) {
            printf("[%d] -> [%s], ", temp->vertex, (char*)temp->value);
            temp = temp->next;
        }
        printf("\n");  
    }
}
void insertNodeAdjacentToAnother(struct AdjacencyList*, struct Node*, struct Node*);

void balanceGraph(struct AdjacencyList* graph) {
    //~ printf("Vertex:  Adjacency List\n");
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        //~ printf("%d --->", v);
        while (temp) {
            printf("[%d] -> [%s], ", temp->vertex, (char*)temp->value);
            
            if( temp->token == Identifier && temp->next->token == TOKEN_OPERADOR /*&& temp->next->next->token == Literal*/ ){
				//~ insertNodeAdjacentToAnother(graph, temp->next, temp->next->next);
				//~ insertNodeAdjacentToAnother(graph, temp, temp->next);
			}
            
            //~ if(v > 0){
				//~ struct Node* anterior = graph->adjLists[v-1];
				//~ if(temp->token == TOKEN_OPERADOR && anterior->token == Identifier ){

					//~ insertNodeAdjacentToAnother(graph, temp, anterior);
				//~ }
			//~ }
			temp = temp->next;
        }
        printf("\n");  
    }
}

void reduceNode(struct AdjacencyList* graph, int tokens[], int m_tokens) {
    int res = 0, ok = 0;
    struct Node* uniNodes[m_tokens+1];
    //~ printf("Vertex:  Adjacency List\n");
    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        //~ printf("%d --->", v);
        //~ int nextT = 0;
        while (temp) {
            printf("[%d] -> [%s] t:%d == %d, ", temp->vertex, (char*)temp->value, temp->token, tokens[res]);
				
				uniNodes[res] = NULL;
				if( ok == 0 && temp->token == tokens[res] ){
					uniNodes[res] = temp;
					res++;
					//~ nextT++;
					if(res == m_tokens){
						ok=1;
					}
				}else if( ok == 0 && temp->token != tokens[res] ){
					uniNodes[res-1] = NULL;
					res = 0;
				}
            
			temp = temp->next;
        }
        printf("\n");  
    }
    printf("res [%d]\n", res);
    if(ok == 1 && res == m_tokens){
		for (int i = res; i > 0; i--) {
			if(i-1 >= 0)insertNodeAdjacentToAnother(graph, uniNodes[i-1], uniNodes[i]);
			//~ printf("[%d, %d]", i-1, i);
		}
	}
}

void insertNodeAdjacentToAnother(struct AdjacencyList* graph, struct Node* src, struct Node* nodeInsert) {
    src->next = nodeInsert;
}
