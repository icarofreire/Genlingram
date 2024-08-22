/* Lib Adjacency List; */

// Structure to represent a node in the adjacency list
struct Node {
    int vertex;
    struct Node* next;
};

// Structure to represent the adjList
struct AdjacencyList {
	/*\/ número de vertices pré-definido; */
    int numVertices;
    /*\/ número de vertices criados; */
    int numEdges;
    struct Node** adjLists;
};

// Function to create a new node
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create a adjList
struct AdjacencyList* createAdjacencyList(int vertices) {
    struct AdjacencyList* adjList = malloc(sizeof(struct AdjacencyList));
    adjList->numVertices = vertices;

    // Create an array of adjacency lists
    adjList->adjLists = malloc(vertices * sizeof(struct Node*));

    // Initialize each adjacency list as empty
    for (int i = 0; i < vertices; i++) {
        adjList->adjLists[i] = NULL;
    }
    
    adjList->numEdges = 0;

    return adjList;
}

// Function to add an edge to the adjList
void addEdge(struct AdjacencyList* adjList, int src, int dest) {
    // Add edge from src to dest
    struct Node* newNode = createNode(dest);
    newNode->next = adjList->adjLists[src];
    adjList->adjLists[src] = newNode;
    adjList->numEdges++;
    
    if(adjList->numVertices < adjList->numEdges){
		// realocar para mais 1;
		adjList->adjLists = malloc((adjList->numVertices+1) * sizeof(struct Node*));
		adjList->numVertices++;
	}
}

// Function to print the adjacency list representation of the adjList
void printAdjacencyList(struct AdjacencyList* adjList) {
    printf("Vertex:  Adjacency List\n");
    for (int v = 0; v < adjList->numVertices; v++) {
        struct Node* temp = adjList->adjLists[v];
        printf("%d --->", v);
        while (temp) {
            printf(" %d ->", temp->vertex);
            temp = temp->next;
        }
        printf(" NULL\n");  
    }
}

// Function to perform Breadth First Search on a graph
// represented using adjacency list
int bfs(struct Node* adj[], int vertices, int source, int visited[], int value) {
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
        printf("%d >> ", curr);

        // Get all adjacent vertices of the dequeued vertex
        // curr If an adjacent has not been visited,
        // then mark it visited and enqueue it
        struct Node* temp = adj[curr];
        while (temp != NULL) {
            int neighbor = temp->vertex;
            
            if(neighbor == value){
				return 1;
			}
            
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
            temp = temp->next;
        }
    }
    return -1;
}

// Function to perform BFS for the entire graph
int BFS_TraversalStarting(struct AdjacencyList* adjList, int vertex_ini, int value)
{
	int vertices = adjList->numEdges;
    // Mark all the vertices as not visited
    int visited[vertices+1];
    for (int i = 0; i < vertices; ++i)
        visited[i] = 0;

    // Perform BFS traversal starting from vertex 0
    return bfs(adjList->adjLists, vertices, vertex_ini, visited, value);
}

// Perform BFS traversal for the entire graph
void BFS_TraversalStartingEntireGraph(struct AdjacencyList* adjList, int value)
{
	int vertices = adjList->numEdges;
    int visited[vertices];
    for (int i = 0; i < vertices; ++i)
        visited[i] = 0;

    for (int i = 0; i < vertices; ++i) {
        if (!visited[i]) {
            bfs(adjList->adjLists, vertices, i, visited, value);
        }
    }
}

/*
// examples;
int main() {
    // Create an undirected adjList with 3 vertices
    struct AdjacencyList* undirectedAdjacencyList = createAdjacencyList(3);

    // Add edges to the undirected adjList
    addEdge(undirectedAdjacencyList, 0, 1);
    addEdge(undirectedAdjacencyList, 0, 2);
    addEdge(undirectedAdjacencyList, 1, 2);

    printf("Adjacecncy List for Undirected AdjacencyList:\n");
    printAdjacencyList(undirectedAdjacencyList);

    // Create a directed adjList with 3 vertices
    struct AdjacencyList* directedAdjacencyList = createAdjacencyList(3);

    // Add edges to the directed adjList
    addEdge(directedAdjacencyList, 1, 0);
    addEdge(directedAdjacencyList, 1, 2);
    addEdge(directedAdjacencyList, 2, 0);

    printf("\nAdjacecncy List for Directed AdjacencyList:\n");
    printAdjacencyList(directedAdjacencyList);

    return 0;
}
*/
