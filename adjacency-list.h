
// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    void *value;
    int token;
    struct Node* next;
};

// Structure to represent the graph(Adjacency List)
struct AdjacencyList {
	/*\/ número de vertices pré-definido; */
    int numVertices;
    /*\/ número de vertices criados; */
    int size;
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
    
    graph->size = 0;

    return graph;
}

void addEdge(struct AdjacencyList* graph, char* value, int token) {
	int src = graph->size;
	int dest = graph->size++;
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    newNode->value = value;
    newNode->token = token;
    graph->adjLists[src] = newNode;
}

// Function to print the adjacency list representation of the graph
void printGraph(struct AdjacencyList* graph) {
    printf("Adjacency List:\n");
    for (int v = 0; v < graph->size; v++) {
        struct Node* temp = graph->adjLists[v];
        while (temp) {
            printf("[%d] -> [%s], ", temp->vertex, (char*)temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

// Function to perform Breadth First Search on a graph
// represented using adjacency list
void bfs(struct Node* adj[], int vertices, int source, int visited[]) {
    // Create a queue for BFS
    int queue[vertices];
    int front = 0, rear = 0;

    // Mark the current node as visited and enqueue it
    visited[source] = 1;
    queue[rear++] = source;

    // Iterate over the queue
    while (front != rear) {
      
        // Dequeue a vertex from queue and print it
        int curr = queue[front++];
        printf("%d ", curr);

        // Get all adjacent vertices of the dequeued vertex
        // curr If an adjacent has not been visited,
        // then mark it visited and enqueue it
        struct Node* temp = adj[curr];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
            temp = temp->next;
        }
    }
}

// Function to perform BFS for the entire graph
void BFS_TraversalStarting(struct AdjacencyList* adjList, int value)
{
	int vertices = adjList->size;
    // Mark all the vertices as not visited
    int visited[vertices];
    for (int i = 0; i < vertices; ++i)
        visited[i] = 0;

    // Perform BFS traversal starting from vertex 0
    bfs(adjList->adjLists, vertices, 0, visited);
}

void insertNodeAdjacentToAnother(struct AdjacencyList* graph, struct Node* src, struct Node* nodeInsert) {
    src->next = nodeInsert;
}

void reduceNode(struct AdjacencyList* graph, const int tokens[], int m_tokens) {
    int res = 0;
    struct Node* uniNodes[m_tokens];
	for(int i=0; i<m_tokens; i++) uniNodes[i] = NULL;

    for (int v = 0; v < graph->size; v++) {
        struct Node* temp = graph->adjLists[v];
        while (temp) {
			if( res < m_tokens && temp->token == tokens[res] ){
				uniNodes[res] = temp;
				res++;
				if(res == m_tokens){
					for (int i = res-1; i > 0; i--) {
						insertNodeAdjacentToAnother(graph, uniNodes[i-1], uniNodes[i]);
					}
					res = 0;
				}
			}else if( res < m_tokens && temp->token != tokens[res] ){
				for(int i=0; i<m_tokens; i++) uniNodes[i] = NULL;
				res = 0;
			}

			temp = temp->next;
        }
    }
}
