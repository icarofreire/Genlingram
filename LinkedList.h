#ifndef INCLUDE_GUARD_54BE4DFB1B914CA0BB9CA2013131ACF8
#define INCLUDE_GUARD_54BE4DFB1B914CA0BB9CA2013131ACF8


//////////////////////
// Global constants //
//////////////////////

#define LINKEDLIST_INDEX_START -1
#define LINKEDLIST_INDEX_END -2


/////////////////////
// Data Structures //
/////////////////////

/**
 * Opaque LinkedList struct
 */
typedef struct LinkedList LinkedList;
typedef struct LinkedListIterator LinkedListIterator;


////////////////////////////////
// Constructors & Destructors //
////////////////////////////////

LinkedList *LinkedList_new();
void LinkedList_destroy(LinkedList *lst_ptr);
LinkedListIterator *LinkedListIterator_new(LinkedList *lst_ptr);
void LinkedListIterator_destroy(LinkedListIterator *itr_ptr);


/////////////////////
// Manipulate Ends //
/////////////////////

void LinkedList_push(LinkedList *lst_ptr, void *value);
void LinkedList_pushback(LinkedList *lst_ptr, void *value);
void *LinkedList_pop(LinkedList *lst_ptr);
void *LinkedList_popback(LinkedList *lst_ptr);
void *LinkedList_peek(LinkedList *lst_ptr);
void *LinkedList_peekback(LinkedList *lst_ptr);


//////////////
// Traverse //
//////////////

void LinkedListIterator_move_to_first(LinkedListIterator *itr_ptr);
void LinkedListIterator_move_to_last(LinkedListIterator *itr_ptr);
void LinkedListIterator_move_to_next(LinkedListIterator *itr_ptr);
void LinkedListIterator_move_to_previous(LinkedListIterator *itr_ptr);
void *LinkedListIterator_get_item(LinkedListIterator *itr_ptr);
int LinkedListIterator_get_index(LinkedListIterator *itr_ptr);


///////////////
// Two lists //
///////////////

void LinkedList_append(LinkedList *lst_dest_ptr, LinkedList *lst_src_ptr);
void LinkedList_prepend(LinkedList *lst_dest_ptr, LinkedList *lst_src_ptr);


///////////
// Other //
///////////

int LinkedList_get_size(LinkedList *lst_ptr);


#endif
