// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    void *value;
    int token;
    struct Node* next;
};

// Structure to represent the graph(Adjacency List)
struct AdjacencyList {
    int numVertices;
    int indice;
    struct Node** adjLists;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->token = 0;
    newNode->next = NULL;
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
    }
    
    graph->indice = 0;//indice interator;

    return graph;
}

void addEdge(struct AdjacencyList* graph, char* value, int token) {
	int src = graph->indice;
	int dest = graph->indice++;
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    newNode->value = value;
    newNode->token = token;
    graph->adjLists[src] = newNode;
}

void addEdgeNNodes(struct AdjacencyList* graph, int nNodesAnterior) {
	int src = graph->indice;
	if(nNodesAnterior){
		int dest = graph->indice-1;
		
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

void reduceNode(struct AdjacencyList* graph, int tokens[], int m_tokens) {
    int res = 0;
    struct Node* uniNodes[m_tokens];
	for(int i=0; i<m_tokens; i++) uniNodes[i] = NULL;

    for (int v = 0; v < graph->numVertices; v++) {
        struct Node* temp = graph->adjLists[v];
        while (temp) {
            printf("[%d] -> [%s] t:%d == %d; \n", temp->vertex, (char*)temp->value, temp->token, tokens[res]);

			if( res < m_tokens && temp->token == tokens[res] ){
				uniNodes[res] = temp;
				res++;
				if(res == m_tokens){
					for (int i = res; i > 0; i--) {
						if(i-1 >= 0){
							insertNodeAdjacentToAnother(graph, uniNodes[i-1], uniNodes[i]);
						}
					}
					res = 0;
				}
			}else if( res < m_tokens && temp->token != tokens[res] ){
				uniNodes[res-1] = NULL;
				res = 0;
			}

			temp = temp->next;
        }
    }
}

void insertNodeAdjacentToAnother(struct AdjacencyList* graph, struct Node* src, struct Node* nodeInsert) {
    src->next = nodeInsert;
}
