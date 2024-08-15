#include <stdlib.h>

#include "LinkedList.h"


/////////////////////
// Data Structures //
/////////////////////

typedef struct Node Node;
struct Node{
	void *value;
	Node *next;
	Node *previous;
};

typedef struct LinkedList{
	int size;
	Node *first;
	Node *last;
}LinkedList;

typedef struct LinkedListIterator{
	Node *current;
	int index;
	LinkedList *lst_ptr;
}LinkedListIterator;


////////////////////////////////
// Constructors & Destructors //
////////////////////////////////

LinkedList *LinkedList_new(){
	LinkedList *lst_ptr = malloc( sizeof(LinkedList) );

	lst_ptr->size = 0;
	lst_ptr->first = NULL;
	lst_ptr->last = NULL;

	return lst_ptr;
}

void LinkedList_destroy(LinkedList *lst_ptr){
	Node *current = lst_ptr->first;
	Node *next = NULL;

	while(current != NULL){
		next = current->next;
		free(current);
		current = next;
	}

	free(lst_ptr);
}

LinkedListIterator *LinkedListIterator_new(LinkedList *lst_ptr){
	LinkedListIterator *itr_ptr = malloc( sizeof(LinkedListIterator) );
	itr_ptr->lst_ptr = lst_ptr;
	itr_ptr->current = NULL;
	itr_ptr->index = LINKEDLIST_INDEX_START;

	return itr_ptr;
}

void LinkedListIterator_destroy(LinkedListIterator *itr_ptr){
	free(itr_ptr);
}



/////////////////////
// Manipulate Ends //
/////////////////////

void LinkedList_push(LinkedList *lst_ptr, void *value){
	Node *new = malloc( sizeof(Node) );
	new->value = value;
	
	if(lst_ptr->first ==  NULL){
		new->next = NULL;
		new->previous = NULL;
		lst_ptr->first = new;
		lst_ptr->last = new;
	}
	else{
		new->next = lst_ptr->first;
		new->previous = NULL;
		lst_ptr->first = new;
		new->next->previous = new;
	}

	lst_ptr->size++;
}

void LinkedList_pushback(LinkedList *lst_ptr, void *value){
	Node *new = malloc( sizeof(Node) );
	new->value = value;
	
	if(lst_ptr->last ==  NULL){
		new->next = NULL;
		new->previous = NULL;
		lst_ptr->first = new;
		lst_ptr->last = new;
	}
	else{
		new->next = NULL;
		new->previous = lst_ptr->last;
		lst_ptr->last = new;
		new->previous->next = new;
	}

	lst_ptr->size++;
}

void *LinkedList_pop(LinkedList *lst_ptr){
	Node *node = lst_ptr->first;
	void *value;

	if(node == NULL){
		return NULL;
	}

	else if(node->next == NULL){
		lst_ptr->first = NULL;
		lst_ptr->last = NULL;
		value = node->value;
		free(node);
	}

	else{
		lst_ptr->first = node->next;
		node->next->previous = NULL;
		value = node->value;
		free(node);
	}

	lst_ptr->size--;

	return value;
}

void *LinkedList_popback(LinkedList *lst_ptr){
	Node *node = lst_ptr->last;
	void *value;

	if(node == NULL){
		return NULL;
	}

	else if(node->previous == NULL){
		lst_ptr->first = NULL;
		lst_ptr->last = NULL;
		value = node->value;
		free(node);
	}

	else{
		lst_ptr->last = node->previous;
		node->previous->next = NULL;
		value = node->value;
		free(node);
	}

	lst_ptr->size--;

	return value;
}

void *LinkedList_peek(LinkedList *lst_ptr){
	Node *node = lst_ptr->first;

	if(node == NULL){
		return NULL;
	}
	else{
		return node->value;
	}
}

void *LinkedList_peekback(LinkedList *lst_ptr){
	Node *node = lst_ptr->last;

	if(node == NULL){
		return NULL;
	}
	else{
		return node->value;
	}
}


///////////////
// Two lists //
///////////////

void LinkedList_append(LinkedList *lst_dest_ptr, LinkedList *lst_src_ptr){
	if(lst_src_ptr->size == 0)
		return;

	if(lst_dest_ptr->size == 0){
		lst_dest_ptr->first = lst_src_ptr->first;
		lst_dest_ptr->last = lst_src_ptr->last;
		lst_dest_ptr->size = lst_src_ptr->size;

		lst_src_ptr->first = NULL;
		lst_src_ptr->last = NULL;
		lst_src_ptr->size = 0;
	}

	else{
		lst_dest_ptr->last->next = lst_src_ptr->first;
		lst_src_ptr->first->previous = lst_dest_ptr->last;

		lst_dest_ptr->last = lst_src_ptr->last;
		lst_src_ptr->first = NULL;
		lst_src_ptr->last = NULL;

		lst_dest_ptr->size += lst_src_ptr->size;
		lst_src_ptr->size = 0;
	}
}

void LinkedList_prepend(LinkedList *lst_dest_ptr, LinkedList *lst_src_ptr){
	if(lst_src_ptr == 0)
		return;

	if(lst_dest_ptr->size == 0){
		lst_dest_ptr->first = lst_src_ptr->first;
		lst_dest_ptr->last = lst_src_ptr->last;
		lst_dest_ptr->size = lst_src_ptr->size;

		lst_src_ptr->first = NULL;
		lst_src_ptr->last = NULL;
		lst_src_ptr->size = 0;
	}

	else{
		lst_dest_ptr->first->previous = lst_src_ptr->last;
		lst_src_ptr->last->next = lst_dest_ptr->first;

		lst_dest_ptr->first = lst_src_ptr->first;
		lst_src_ptr->first = NULL;
		lst_dest_ptr->first = NULL;

		lst_dest_ptr->size += lst_src_ptr->size;
		lst_src_ptr->size = 0;
	}
}



//////////////
// Traverse //
//////////////

void LinkedListIterator_move_to_first(LinkedListIterator *itr_ptr){
	itr_ptr->current = itr_ptr->lst_ptr->first;
	itr_ptr->index = 0;
}

void LinkedListIterator_move_to_last(LinkedListIterator *itr_ptr){
	itr_ptr->current = itr_ptr->lst_ptr->last;
	itr_ptr->index = itr_ptr->lst_ptr->size - 1;
}

void LinkedListIterator_move_to_next(LinkedListIterator *itr_ptr){
	if(itr_ptr->current != NULL){
		itr_ptr->current = itr_ptr->current->next;

		if(itr_ptr->current != NULL){
			itr_ptr->index++;
		}

		else{
			itr_ptr->index = LINKEDLIST_INDEX_END;
		}
	}

	else if(itr_ptr->index == LINKEDLIST_INDEX_START){
		if(itr_ptr->lst_ptr->first != NULL){
			itr_ptr->current = itr_ptr->lst_ptr->first;
			itr_ptr->index = 0;
		}
		else{
			itr_ptr->index = LINKEDLIST_INDEX_END;
		}

	}
}

void LinkedListIterator_move_to_previous(LinkedListIterator *itr_ptr){
	if(itr_ptr->current != NULL){
		itr_ptr->current = itr_ptr->current->previous;
		
		if(itr_ptr->current != NULL){
			itr_ptr->index--;
		}

		else{
			itr_ptr->index = LINKEDLIST_INDEX_START;
		}
	}

	else if(itr_ptr->index == LINKEDLIST_INDEX_END){
		if(itr_ptr->lst_ptr->last != NULL){
			itr_ptr->current = itr_ptr->lst_ptr->last;
			itr_ptr->index = itr_ptr->lst_ptr->size - 1;
		}
		else{
			itr_ptr->index = LINKEDLIST_INDEX_START;
		}

	}
}

void *LinkedListIterator_get_item(LinkedListIterator *itr_ptr){
	if (itr_ptr->current != NULL){
		return itr_ptr->current->value;
	}
	else{
		return NULL;
	}
}

int LinkedListIterator_get_index(LinkedListIterator *itr_ptr){
	return itr_ptr->index;
}


///////////
// Other //
///////////

int LinkedList_get_size(LinkedList *lst_ptr){
	return lst_ptr->size;
}
