/* Lib Doubly Linked List; */

#include <stdio.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev
};

// Function to create a new node
struct Node *createNode(int new_data) {
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Function to insert a new node at the front of doubly linked list
struct Node *insertAtFront(struct Node *head, int new_data) {

    // Create a new node
    struct Node *new_node = createNode(new_data);

    // Make next of new node as head
    new_node->next = head;

    // Change prev of head node to new node
    if (head != NULL) {
        head->prev = new_node;
    }

    // Return the new node as the head of the doubly linked list
    return new_node;
}

// Function to insert a new node at a given position
struct Node* insertAtPosition(struct Node *head, int pos, int new_data) {
    // Create a new node
    struct Node *new_node = createNode(new_data);

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

    struct Node *curr = head;
  
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
struct Node *insertAfter(struct Node *head, int key, int new_data) {
    struct Node *curr = head;

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
    struct Node *new_node = createNode(new_data);

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
struct Node* insertBefore(struct Node *head, int key, int new_data) {
    struct Node *curr = head;

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
    struct Node *new_node = createNode(new_data);

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
bool searchKey(struct Node* head, int key) {

    // Initialize curr with the head of linked list
    struct Node* curr = head;

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

// Function to delete a node at a specific 
//position in the doubly linked list
struct Node * delPos(struct Node * head, int pos) {

    // If the list is empty
    if (head == NULL)
        return head;

    struct Node * curr = head;

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

    // Deallocate memory for the deleted node
    free(curr);
    return head;
}

/* Function to delete a node in a Doubly Linked List. 
   head_ref --> pointer to head node pointer. 
   del  -->  pointer to node to be deleted. */
void deleteNode(struct Node** head_ref, struct Node* del) 
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
  
    /* Finally, free the memory occupied by del*/
    free(del); 
    return; 
}

// deleteAllNodes(&head)
void deleteAllNodes(Node** head_ref)
{
    Node* ptr = *head_ref;
 
    while (ptr != NULL) {
        Node* next = ptr->next;
        deleteNode(head_ref, ptr);
        ptr = next;
    }
}

// Function to print the doubly linked list
void printList(struct Node *head) {
    struct Node *curr = head;
    while (curr != NULL) {
        printf(" %d", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Function to traverse the doubly linked list 
// in forward direction
void forwardTraversal(struct Node* head) {
  
    // Start traversal from the head of the list
    struct Node* curr = head;

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
void backwardTraversal(struct Node* tail) {
  
    // Start traversal from the tail of the list
    struct Node* curr = tail;

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
