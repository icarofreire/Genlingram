/* Lib genêrica de Doubly Linked List; */


/* Node Doubly Linked List; */
struct ListDLL {
    struct ListDLL *next;
    struct ListDLL *prev;
    /*\/ ponteiro para a estrutura pai
    que utiliza a Doubly Linked List como estrutura filha; */
    void* __struct;
};

// Function to create a new node
struct ListDLL *createListDLL() {
    struct ListDLL *new_node = (struct ListDLL *)malloc(sizeof(struct ListDLL));

    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

// Function to insert a new node at the front of doubly linked list
struct ListDLL *list_insert_at_front(struct ListDLL *head, struct ListDLL *new_node) {

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
struct ListDLL* list_insert_end(struct ListDLL *head, struct ListDLL *new_node) {

    // If the linked list is empty, set the new node as the head
    if (head == NULL) {
        head = new_node;
    } else {
        struct ListDLL *curr = head;
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

void list_append(struct ListDLL **head, struct ListDLL *new_node) {
    *head = list_insert_end(*head, new_node);
}

// Function to insert a new node at a given position
struct ListDLL* list_insert_at_position(struct ListDLL *head, int pos, struct ListDLL *new_node) {

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

    struct ListDLL *curr = head;
  
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

// Function to delete a node at a specific 
//position in the doubly linked list
struct ListDLL * list_del_pos(struct ListDLL * head, int pos) {

    // If the list is empty
    if (head == NULL)
        return head;

    struct ListDLL * curr = head;

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
void list_delete_node(struct ListDLL** head_ref, struct ListDLL* del) 
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
void list_delete_all_nodes(struct ListDLL** head_ref)
{
    struct ListDLL* ptr = *head_ref;
 
    while (ptr != NULL) {
        struct ListDLL* next = ptr->next;
        list_delete_node(head_ref, ptr);
        ptr = next;
    }
}

// Function to print the doubly linked list
void list_print_list(struct ListDLL *head) {
    struct ListDLL *curr = head;
    while (curr != NULL) {
        // printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

struct ListDLL* list_get_head(struct ListDLL* curr) {

    struct ListDLL* head = NULL;
    while (curr != NULL) {

        head = curr;

        // Move to the previous node
        curr = curr->prev;
    }

    return head;
}

struct ListDLL* list_get_tail(struct ListDLL* head) {

    struct ListDLL* curr = head;
    struct ListDLL* tail = NULL;
    while (curr != NULL) {

        tail = curr;

        // Move to the next node
        curr = curr->next;
    }

    return tail;
}


/* \/ macros para loop Doubly Linked List; */

#define list_forward(el, head) \
  for(el = (head)->next; el != NULL; el = el->next)

#define list_backward(el, head) \
  for(el = (head)->prev; el != NULL; el = el->prev)
