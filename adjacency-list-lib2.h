/* Lib Adjacency List; */
/* Graph representation of an adjacency list with a linked list for the nodes; */

struct Token
{
  // The beginning of the token, pointing directly into the source.
  const char* str;

  // The 1-based line where the token appears.
  const int line;
  
  // The parsed value if the token is a literal.
  const int tokenType;
};

struct Node {
	struct Token* token;
    int val;
    struct Node* next;
    /*\/ lista de edges do nó; */
    struct Edge* edges;
};

struct Edge {
    struct Node* dest;
    struct Edge* next;
};

struct Graph {
	/*\/ lista de nós inseridas; */
    struct Node* head;
    int size;
};

/* Prototypes */
struct Graph* createGraph();
struct Node* createNode(int val, struct Token* token);
struct Edge* createEdge(struct Graph* graph, int dest);
struct Node* getNode(struct Graph* graph, int val);
int insertNode(struct Graph* graph, int val, struct Token* token);
int insertEdge(struct Graph* graph, int src, int dest);
void printGraph(struct Graph* graph);
/* Prototypes */

struct Graph* createGraph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->size  = 0;
    graph->head  = NULL;

    return graph;
}

struct Node* createNode(int val, struct Token* token) {
    struct Node* newNode  = (struct Node*)malloc(sizeof(struct Node));
    newNode->token = (token != NULL) ? (token) : (NULL);
    newNode->val   = val;
    newNode->next  = NULL;
    newNode->edges = NULL;
    return newNode;
}

struct Edge* createEdge(struct Graph* graph, int dest) {
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->dest = getNode(graph, dest);
    newEdge->next = NULL;

    return newEdge;
}

int insertNode(struct Graph* graph, int val, struct Token* token) {
    if (getNode(graph, val) != NULL) return -1;
    struct Node* newNode  = createNode(val, token);
    struct Node* tempNode = NULL;

    if (graph->head == NULL) {
        graph->head = newNode;
    } else {
        tempNode = graph->head;
        while (tempNode->next != NULL)
            tempNode = tempNode->next;
        tempNode->next = newNode;
    }
    graph->size++;
    return 1;
}

int insertEdge(struct Graph* graph, int src, int dest) {
    struct Node* origNode = getNode(graph, src);
    struct Node* destNode = getNode(graph, dest);
    if (origNode == NULL || destNode == NULL) return -1;

    struct Edge* newEdge  = createEdge(graph, dest);
    struct Edge* tempEdge = NULL;

    if (origNode->edges == NULL) {
        origNode->edges = newEdge;
    } else {
        tempEdge = origNode->edges;
        while (tempEdge->next != NULL) tempEdge = tempEdge->next;
        tempEdge->next = newEdge;
    }
    return 1;
}

struct Node* getNode(struct Graph* graph, int val) {
    struct Node* tempNode = graph->head;
    while (tempNode != NULL) {
        if (tempNode->val == val) return tempNode;
        tempNode = tempNode->next;
    }
    return NULL;
}

void printGraph(struct Graph* graph) {
    struct Node* tempNode = graph->head;
    struct Edge* tempEdge = NULL;

    while (tempNode != NULL) {
        printf("\nNodo %d: ", tempNode->val);
        tempEdge = tempNode->edges;
        while (tempEdge) {
            printf(" -> %d", tempEdge->dest->val);
            tempEdge = tempEdge->next;
        }
        tempNode = tempNode->next;
    }
}

/* If edge (vertex1,vertex2) exists */
int isAdjacent(struct Graph* graph, int src, int dest) {
	struct Node* origNode = getNode(graph, src);
    struct Node* destNode = getNode(graph, dest);
    if (origNode == NULL || destNode == NULL) return -1;
    
    struct Edge* tempEdge = NULL;
    
	printf("\nNodo %d: ", origNode->val);
    tempEdge = origNode->edges;
	while (tempEdge) {
		printf(" -> %d", tempEdge->dest->val);
		if(tempEdge->dest->val == dest) return 1;
		tempEdge = tempEdge->next;
	}
    return -1;
}

void deleteAllGraph(struct Graph* graph) {
    struct Node* tempNode = graph->head, *tmpNode = NULL;
    struct Edge* tempEdge = NULL, *tmpEdge = NULL;

    while (tempNode != NULL) {
        tempEdge = tempNode->edges;
        while (tempEdge) {
            tmpEdge = tempEdge;
            tempEdge = tempEdge->next;
            free(tmpEdge);
        }
        tmpNode = tempNode;
        tempNode = tempNode->next;
        free(tmpNode);
    }
}

/* ***
 * example;
 * */
/*
struct Graph* G2 = createGraph();

insertNode(G2, 0);
insertNode(G2, 1);
insertNode(G2, 2);
insertNode(G2, 3);
insertNode(G2, 4);
insertNode(G2, 5);
insertNode(G2, 6);
insertNode(G2, 7);
insertNode(G2, 8);
insertNode(G2, 9);
insertNode(G2, 10);
insertNode(G2, 11);
insertNode(G2, 12);
insertNode(G2, 13);

// ***

insertEdge(G2, 3, 1);
insertEdge(G2, 1, 0);
insertEdge(G2, 3, 7);
insertEdge(G2, 7, 9);
insertEdge(G2, 3, 4);
insertEdge(G2, 3, 2);
insertEdge(G2, 4, 5);
insertEdge(G2, 4, 12);
insertEdge(G2, 4, 8);
insertEdge(G2, 12, 13);
insertEdge(G2, 2, 10);
insertEdge(G2, 2, 6);
insertEdge(G2, 10, 11);

printGraph(G2);

printf("\n***\n");

int path = isAdjacent(G2, 4, 12);
if(path == 1){
	printf("[ok];\n");
}else{
	printf("[No];\n");
}
*/
