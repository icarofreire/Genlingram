/* Lib Doubly Linked List; */


/* Node Doubly Linked List; */
struct NodeDLL {
    /*\/ dado representativo do nó,
    ou um indice para a nó da Doubly Linked List;*/
    int data;

    /*\/ array de dados dinâmico para simular os filhos deste nó; */
    int *children_datas;
    /*\/ tamanho do array; */
    int len_children_datas;

    struct NodeDLL *next;
    struct NodeDLL *prev;
};

// Function to create a new node
struct NodeDLL *createNodeDLL(int new_data) {
    struct NodeDLL *new_node = (struct NodeDLL *)malloc(sizeof(struct NodeDLL));
    new_node->data = new_data;

    /*\/ inicialização do array inicial de cada nó; */
    new_node->len_children_datas = 1;
	new_node->children_datas = (int*)malloc((new_node->len_children_datas) * sizeof(int));
    for(int i=0; i<new_node->len_children_datas; i++){
        new_node->children_datas[i] = -1;
    }

    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

/*\/ aumentar a capacidade de um array dinamicamente; */
void array_plus_size(int **items, int *capacity, int plus) {
	if(plus > 0){
		*capacity += plus;
		*items = (int*)realloc(*items, (*capacity) * sizeof(int));
	}
}

// Function to insert a new node at the front of doubly linked list
struct NodeDLL *insertAtFront(struct NodeDLL *head, int new_data) {

    // Create a new node
    struct NodeDLL *new_node = createNodeDLL(new_data);

    // Make next of new node as head
    new_node->next = head;

    // Change prev of head node to new node
    if (head != NULL) {
        head->prev = new_node;
    }

    // Return the new node as the head of the doubly linked list
    return new_node;
}

// Function to insert a new node at the end of the doubly linked list
struct NodeDLL* insertEnd(struct NodeDLL *head, int new_data) {
    struct NodeDLL *new_node = createNodeDLL(new_data);

    // If the linked list is empty, set the new node as the head
    if (head == NULL) {
        head = new_node;
    } else {
        struct NodeDLL *curr = head;
        while (curr->next != NULL) {
            curr = curr->next;
        }

        // Set the next of last node to new node
        curr->next = new_node;
        // Set prev of new node to last node
        new_node->prev = curr;
    }

    return head;
}

void append(struct NodeDLL **head, int new_data) {
    *head = insertEnd(*head, new_data);
}

// Function to insert a new node at a given position
struct NodeDLL* insertAtPosition(struct NodeDLL *head, int pos, int new_data) {
    // Create a new node
    struct NodeDLL *new_node = createNodeDLL(new_data);

    // Insertion at the beginning
    if (pos == 1) {
        new_node->next = head;

        // If the linked list is not empty, set the prev of head to new node
        if (head != NULL) {
            head->prev = new_node;
        }

        // Set the new node as the head of linked list
        head = new_node;
        return head;
    }

    struct NodeDLL *curr = head;
  
    // Traverse the list to find the node before the insertion point
    for (int i = 1; i < pos - 1 && curr != NULL; ++i) {
        curr = curr->next;
    }

    // If the position is out of bounds
    if (curr == NULL) {
        printf("Position is out of bounds.\n");
        free(new_node);
        return head;
    }

    // Set the prev of new node to curr
    new_node->prev = curr;

    // Set the next of new node to next of curr
    new_node->next = curr->next;

    // Update the next of current node to new node
    curr->next = new_node;

    // If the new node is not the last node, update the prev of next node to new node
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }

    // Return the head of the doubly linked list
    return head;
}

// Function to insert a new node after a given node in doubly linked list
struct NodeDLL *insertAfter(struct NodeDLL *head, int key, int new_data) {
    struct NodeDLL *curr = head;

    // Iterate over Linked List to find the key
    while (curr != NULL) {
        if (curr->data == key)
            break;
        curr = curr->next;
    }

    // If curr becomes NULL, the given key
    // is not found in linked list
    if (curr == NULL)
        return head;

    // Create a new node
    struct NodeDLL *new_node = createNodeDLL(new_data);

    // Set prev of new node to the given node
    new_node->prev = curr;

    // Set next of new node to the next of given node
    new_node->next = curr->next;

    // Update next of given node to new node
    curr->next = new_node;

    // Update the prev of new node's next with new node
    if (new_node->next != NULL)
        new_node->next->prev = new_node;

    return head;
}

// Function to insert a new node before a given node
struct NodeDLL* insertBefore(struct NodeDLL *head, int key, int new_data) {
    struct NodeDLL *curr = head;

    // Iterate over Linked List to find the key
    while (curr != NULL) {
        if (curr->data == key)
            break;
        curr = curr->next;
    }

    // If curr becomes NULL, the given key is not found in the linked list
    if (curr == NULL)
        return head;

    // Create a new node
    struct NodeDLL *new_node = createNodeDLL(new_data);

    // Set prev of new node to prev of given node
    new_node->prev = curr->prev;

    // Set next of new node to given node
    new_node->next = curr;

    // Update next of given node's prev to new node
    if (curr->prev != NULL) {
        curr->prev->next = new_node;
    } else {
        // If the current node is the head, update the head
        head = new_node;
    }

    // Update prev of given node to new node
    curr->prev = new_node;

    return head;
}

// Checks whether key is present in linked list
bool searchKey(struct NodeDLL* head, int key) {

    // Initialize curr with the head of linked list
    struct NodeDLL* curr = head;

    // Iterate over all the nodes
    while (curr != NULL) {

        // If the current node's value is equal to key,
        // return true
        if (curr->data == key)
            return true;

        // Move to the next node
        curr = curr->next;
    }

    // If there is no node with value as key, return false
    return false;
}

// Checks whether key is present in linked list
struct NodeDLL* searchNodeByKey(struct NodeDLL* head, int key) {

    // Initialize curr with the head of linked list
    struct NodeDLL* curr = head;

    // Iterate over all the nodes
    while (curr != NULL) {

        // If the current node's value is equal to key,
        // return true
        if (curr->data == key)
            return curr;

        // Move to the next node
        curr = curr->next;
    }

    // If there is no node with value as key, return false
    return NULL;
}

struct NodeDLL* searchBackwardNodeByKey(struct NodeDLL* tail, int key) {

    // Start traversal from the tail of the list
    struct NodeDLL* curr = tail;

    // Continue until the current node is not
    // null (end of list)
    while (curr != NULL) {

        if (curr->data == key)
            return curr;

        // Move to the previous node
        curr = curr->prev;
    }

    return NULL;
}

// Function to delete a node at a specific 
//position in the doubly linked list
struct NodeDLL * delPos(struct NodeDLL * head, int pos) {

    // If the list is empty
    if (head == NULL)
        return head;

    struct NodeDLL * curr = head;

    // Traverse to the node at the given position
    for (int i = 1; curr && i < pos; ++i) {
        curr = curr -> next;
    }

    // If the position is out of range
    if (curr == NULL)
        return head;

    // Update the previous node's next pointer
    if (curr -> prev)
        curr -> prev -> next = curr -> next;

    // Update the next node's prev pointer
    if (curr -> next)
        curr -> next -> prev = curr -> prev;

    // If the node to be deleted is the head node
       if (head == curr)
               head = curr -> next;

    //    free(curr->data);
    // Deallocate memory for the deleted node
    free(curr);
    return head;
}

/* Function to delete a node in a Doubly Linked List. 
   head_ref --> pointer to head node pointer. 
   del  -->  pointer to node to be deleted. */
void deleteNode(struct NodeDLL** head_ref, struct NodeDLL* del) 
{ 
    /* base case */
    if (*head_ref == NULL || del == NULL) 
        return; 
  
    /* If node to be deleted is head node */
    if (*head_ref == del) 
        *head_ref = del->next; 
  
    /* Change next only if node to be deleted is NOT the last node */
    if (del->next != NULL) 
        del->next->prev = del->prev; 
  
    /* Change prev only if node to be deleted is NOT the first node */
       if (del->prev != NULL) 
               del->prev->next = del->next; 
  
    //    free(del->data);
    /* Finally, free the memory occupied by del*/
    free(del);
}

// deleteAllNodes(&head)
void deleteAllNodes(struct NodeDLL** head_ref)
{
    struct NodeDLL* ptr = *head_ref;
 
    while (ptr != NULL) {
        struct NodeDLL* next = ptr->next;
        deleteNode(head_ref, ptr);
        ptr = next;
    }
}

// Function to print the doubly linked list
void printList(struct NodeDLL *head) {
    struct NodeDLL *curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Function to traverse the doubly linked list 
// in forward direction
void forwardTraversal(struct NodeDLL* head) {
  
    // Start traversal from the head of the list
    struct NodeDLL* curr = head;

    // Continue until the current node is not
    // null (end of list)
    while (curr != NULL) {
      
        // Output data of the current node
        printf("%d -> ", curr->data);
      
        // Move to the next node
        curr = curr->next;
    }

    // Print newline after traversal
    printf("\n");
}

// Function to traverse the doubly linked list 
// in backward direction
void backwardTraversal(struct NodeDLL* tail) {
  
    // Start traversal from the tail of the list
    struct NodeDLL* curr = tail;

    // Continue until the current node is not 
    // null (end of list)
    while (curr != NULL) {
      
        // Output data of the current node
        printf("%d <- ", curr->data);
      
        // Move to the previous node
        curr = curr->prev;
    }

    // Print newline after traversal
    printf("\n");
}

struct NodeDLL* getHead(struct NodeDLL* curr) {

    struct NodeDLL* head = NULL;
    while (curr != NULL) {

        head = curr;

        // Move to the previous node
        curr = curr->prev;
    }

    return head;
}

struct NodeDLL* getTail(struct NodeDLL* head) {

    struct NodeDLL* curr = head;
    struct NodeDLL* tail = NULL;
    while (curr != NULL) {

        tail = curr;

        // Move to the next node
        curr = curr->next;
    }

    return tail;
}


/*\/ *** implementações customizadas; *** \/
* implementações que estão além das realizações
propícias de uma Doubly Linked List;
*/


void printListAndChildrens(struct NodeDLL *head) {
    struct NodeDLL *curr = head;
    while (curr != NULL) {
        printf("[%d]:\n", curr->data);
        if(curr->len_children_datas > 0){
            for(int i=0; i<curr->len_children_datas; i++){
                if(curr->children_datas[i] != -1) printf("%d -> ", curr->children_datas[i]);
            }printf("\n");
        }
        curr = curr->next;
    }
    printf("\n");
}

void add_date_for_array(struct NodeDLL *nodeDLL, int new_data){
    int idx_vago = -1;
    for(int i=0; i<nodeDLL->len_children_datas; i++){
        if(nodeDLL->children_datas[i] == new_data){
            return;
        }else if(nodeDLL->children_datas[i] == -1){
            idx_vago = i; break;
        }
    }

    if(idx_vago != -1){
        /*\/ add se existir indice vago; */
        nodeDLL->children_datas[idx_vago] = new_data;
    }else{
        /*\/ adicionar mais 1 capacidade ao array; */
        array_plus_size(&nodeDLL->children_datas, &nodeDLL->len_children_datas, 1);
        /*\/ add o dado como o ultimo; */
        nodeDLL->children_datas[nodeDLL->len_children_datas-1] = new_data;
    }
}

void add_date_in_array_node(struct NodeDLL* head, int key, int new_data){
    struct NodeDLL* node = searchNodeByKey(head, key);
    if(node){
        add_date_for_array(node, new_data);
    }
}

/*\/ detectar caminho por busca em largura(BFS); */
int isPathInDLL(struct NodeDLL* head, int src, int dest) {
    struct NodeDLL* origNode = searchNodeByKey(head, src);
    struct NodeDLL* destNode = searchNodeByKey(head, dest);
    if (origNode == NULL || destNode == NULL) return -1;

    int max = 1000;
    int visited[max];
    for(int i=0; i<max; i++){
        visited[i] = 0;
    }

    int nthp = 0;
    visited[nthp] = src;
    nthp++;

    for(int i=0; i<nthp; i++){
        if(visited[i] > 0){

            origNode = searchNodeByKey(head, visited[i]);
            for(int k=0; k<origNode->len_children_datas; k++){
                int filho = origNode->children_datas[k];
                if(filho != -1){

                    if(filho == destNode->data){
                        return 1;
                    }else{
                        /*\/ verificar presença na pilha de visitados; */
                        int rep = 0;
                        for(int v=0; v<nthp; v++){
                            if(visited[v] == filho){
                                rep = 1; break;
                            }
                        }

                        /*\/ adiciona o valor não-visitado na pilha; */
                        if(rep == 0){
                            visited[nthp] = filho;
                            nthp++;
                        }
                    }
                }
            }// fim for;
        }
    }

    return -1;
}

/*\/ verificar se todos os tokens de entrada são alcançáveis por algum nó da arvore; */
struct NodeDLL *reduce_tree(struct NodeDLL *head, int *pTokenTypes, int sizePtokenTypes) {
    struct NodeDLL *reduceTree = createNodeDLL(0);
    struct NodeDLL *curr = head;
    while (curr != NULL) {
        int pai = curr->data;
        if(curr->len_children_datas > 0){
            int npath = 0;
            for(int k=0; k<sizePtokenTypes; k++){
                int is_path = isPathInDLL(head, pai, pTokenTypes[k]);
                if(is_path == 1){
                    npath++;
                }
            }
            // printf("path [%d, %d]\n", npath, sizePtokenTypes );
            if(npath == sizePtokenTypes){
                for(int k=0; k<sizePtokenTypes; k++){
                    int token = pTokenTypes[k];
                    if(!searchNodeByKey(reduceTree, pai)){
                        append(&reduceTree, pai);
                    }
                    if(!searchNodeByKey(reduceTree, token)){
                        append(&reduceTree, token);
                    }
                    add_date_in_array_node(reduceTree, pai, token);
                }
            }
        }
        curr = curr->next;
    }
    return reduceTree;
}

/*\/ criar uma arvore com nós cujos filhos possuem caminhos com terminais; */
struct NodeDLL *reduce_tree_term(struct NodeDLL *head, int *pTokenTypes, int sizePtokenTypes) {
    struct NodeDLL *reduceTree = createNodeDLL(0);
    struct NodeDLL *curr = head;
    while (curr != NULL) {
        int pai = curr->data;
        if(curr->len_children_datas > 0){
            for(int k=0; k<sizePtokenTypes; k++){
                int token = pTokenTypes[k];
                int is_path = isPathInDLL(head, pai, token);
                if(is_path == 1){
                    if(!searchNodeByKey(reduceTree, pai)){
                        append(&reduceTree, pai);
                    }
                    if(!searchNodeByKey(reduceTree, token)){
                        append(&reduceTree, token);
                    }
                    add_date_in_array_node(reduceTree, pai, token);
                }
            }
        }
        curr = curr->next;
    }
    return reduceTree;
}

struct NodeDLL* searchNodeByChildren(struct NodeDLL *head, int child) {
    struct NodeDLL *curr = head;
    while (curr != NULL) {
        if(curr->len_children_datas > 0){
            for(int i=0; i<curr->len_children_datas; i++){
                if(curr->children_datas[i] != -1 && curr->children_datas[i] == child){
                    return curr;
                }
            }
        }
        curr = curr->next;
    }
    return NULL;
}