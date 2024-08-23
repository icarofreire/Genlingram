/* Lib Doubly Linked List; */

#include <stdio.h>

/* Node Doubly Linked List; */
struct NodeDLL {
    char* data;
    struct NodeDLL *next;
    struct NodeDLL *prev;
};

// Function to create a new node
struct NodeDLL *createNodeDLL(char* new_data) {
    struct NodeDLL *new_node = (struct NodeDLL *)malloc(sizeof(struct NodeDLL));
    //~ new_node->data = new_data;
    new_node->data = (char*)malloc((strlen(new_data)) * sizeof(char));
	strcpy(new_node->data, new_data);
	
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Function to insert a new node at the front of doubly linked list
struct NodeDLL *insertAtFront(struct NodeDLL *head, char* new_data) {

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
struct NodeDLL* insertEnd(struct NodeDLL *head, char* new_data) {
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

// Function to insert a new node at a given position
struct NodeDLL* insertAtPosition(struct NodeDLL *head, int pos, char* new_data) {
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
struct NodeDLL *insertAfter(struct NodeDLL *head, char* key, char* new_data) {
    struct NodeDLL *curr = head;

    // Iterate over Linked List to find the key
    while (curr != NULL) {
        if (strcmp(curr->data, key) == 0)
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
struct NodeDLL* insertBefore(struct NodeDLL *head, char* key, char* new_data) {
    struct NodeDLL *curr = head;

    // Iterate over Linked List to find the key
    while (curr != NULL) {
        if (strcmp(curr->data, key) == 0)
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
bool searchKey(struct NodeDLL* head, char* key) {

    // Initialize curr with the head of linked list
    struct NodeDLL* curr = head;

    // Iterate over all the nodes
    while (curr != NULL) {

        // If the current node's value is equal to key,
        // return true
        if (strcmp(curr->data, key) == 0)
            return true;

        // Move to the next node
        curr = curr->next;
    }

    // If there is no node with value as key, return false
    return false;
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

	free(curr->data);
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
  
	free(del->data);
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
        printf(" %s", curr->data);
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
        printf("%s -> ", curr->data);
      
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
        printf("%s <- ", curr->data);
      
        // Move to the previous node
        curr = curr->prev;
    }

    // Print newline after traversal
    printf("\n");
}
