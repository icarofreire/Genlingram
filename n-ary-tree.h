/* Lib n-ary-tree; */


typedef struct Leaf Leaf;
struct Leaf
{
	int data;
    /*\/ (prev/next) para percorrer cada children de um nó;
    utilizados para navegar entre os filhos do nó; */
	Leaf	*next;
	Leaf	*prev;
    /*\/ pai do nó; */
	Leaf	*parent;
    /*\/ filho(s); */
	Leaf	*children;
};

/* Creates a new Leaf containing the given data */
/** Returns NULL on error **/
Leaf*	leafNew(int data);

/* Inserts a Leaf as the first child of the given parent */
/** Returns NULL on error **/
#define	leafPrepend(parent, leaf)	leafInsertBefore((Leaf*)parent, (Leaf*)parent->children, (Leaf*)leaf)

/* Inserts a Leaf as the last child of the given parent */
/** Returns NULL on error **/
#define	leafAppend(parent, leaf)	leafInsertBefore((Leaf*)parent, NULL, (Leaf*)leaf)

/* Inserts a Leaf beneath the parent at the given position */
/** Returns NULL on error **/
Leaf*	leafInsert(Leaf *parent, int position, Leaf *leaf);

/* Inserts a Leaf beneath the parent after the given sibling */
Leaf*	leafInsertAfter(Leaf *parent, Leaf *sibling, Leaf *leaf);

/* Inserts a Leaf beneath the parent before the given sibling */
/** If sibling is NULL, the leaf is inserted as the last child of parent **/
/** Returns NULL on error **/
Leaf*	leafInsertBefore(Leaf *parent, Leaf *sibling, Leaf *leaf);

/* Returns a positive value if a Leaf is the root of a tree else 0 */
#define	leafIsRoot(leaf)	(! ((Leaf*)(leaf))->parent && ! ((Leaf*)(leaf))->next)

/* Gets the root of a tree */
/** Returns NULL on error **/
Leaf*	leafRoot(Leaf *leaf);

/* Finds a Leaf in a tree */
Leaf*	leafFind(Leaf *leaf, int data);

/* Gets a child of a Leaf, using the given index */
/** Returns NULL if the index is too big **/
Leaf*	leafNthChild(Leaf *leaf, int n);

/* Gets the number of leafs in a tree */
int	leafTotal(Leaf	*root);

/* Unlinks a Leaf from a tree, resulting in two separate trees */
void	leafUnlink(Leaf *leaf);

/* Removes root and its children from the tree, freeing any memory allocated */
void	leafDestroy(Leaf *root);


/* *** */

Leaf*	leafNew(int data)
{
	Leaf *n;
	
	n = (Leaf*)malloc(sizeof(Leaf));
	if (! n)
		return n;
	n->data = data;
	n->next = NULL;
	n->prev = NULL;
	n->parent = NULL;
	n->children = NULL;
	return n;
}

Leaf*	leafInsert(Leaf *parent, int position, Leaf *leaf)
{
	if (! (parent && leaf))
		return NULL;
	if (position < 0)
		return leafAppend(parent, leaf);
	else if (position == 0)
		return leafPrepend(parent, leaf);
	else
		return leafInsertBefore(parent, leafNthChild(parent, position), leaf);
}

/* Inserts a Leaf beneath the parent after the given sibling */
Leaf*	leafInsertAfter(Leaf *parent, Leaf *sibling, Leaf *leaf)
{
	if (! (parent && leaf) || (sibling && sibling->parent == parent))
		return NULL;
	leaf->parent = parent;
	if (sibling)
	{
		if (sibling->next)
			sibling->next->prev = leaf;
		leaf->next = sibling->next;
		leaf->prev = sibling;
		sibling->next = leaf;
	}
	else
	{
		if (parent->children)
		{
			leaf->next = parent->children;
			parent->children->prev = leaf;
		}
		parent->children = leaf;
	}
	return leaf;
}

Leaf*	leafInsertBefore(Leaf *parent, Leaf *sibling, Leaf *leaf)
{
	if (! (parent && leaf) || (sibling && sibling->parent == parent))
		return NULL;
	leaf->parent = parent;
	if (sibling)
	{
        /* Insere uma folha abaixo do pai antes do irmão fornecido */
		if (sibling->prev)
		{
			leaf->prev = sibling->prev;
			leaf->prev->next = leaf;
		}
		else
			leaf->parent->children = leaf;
		leaf->next = sibling;
		sibling->prev = leaf;
	}
	else
	{
        /** Se o irmão for NULL, a folha é inserida como o último filho do pai **/
		if (parent->children)
		{
			sibling = parent->children;
			while (sibling->next)
				sibling = sibling->next;
			leaf->prev = sibling;
			sibling->next = leaf;
		}
		else
			leaf->parent->children = leaf;
	}
	return leaf;
}

Leaf*	leafRoot(Leaf *leaf)
{
	if (! leaf)
		return NULL;
	if (leaf->parent)
		return leafRoot(leaf->parent);
	return leaf;
}

/* Compare 2 data elements (char*) */
int compareStr(void const *a, void const *b)
{
	return strcmp((char const*)a, (char const*)b);
}

int compareInts(int a, int b)
{
	return (a == b);
}

Leaf*	leafFind(Leaf *leaf, int data)
{
	if (! leaf)
		return leaf;
	// if (! compareStr(data, leaf->data))
		// return leaf;
    if (compareInts(data, leaf->data))
		return leaf;
    if (leaf->children)
		return leafFind(leaf->children, data);
	if (leaf->next)
		return leafFind(leaf->next, data);
	return NULL;
}

Leaf*	findLeafFromRoot(Leaf *leaf, int data)
{
    Leaf* root = leafRoot(leaf);
    return leafFind(root, data);
}

Leaf*	findLeafFromRootIterative(Leaf *leaf, int data)
{
    Leaf* child = NULL;
    Leaf* root = leafRoot(leaf);
    while(root){
        child = root->children;
        while (child){
            if(child->data == data){
                return child;
            }
            child = child->next;
        }
        root = (root->children) ? (root->children->next) : (NULL);
    }
    return NULL;
}

Leaf*	findLastLeafFromRootIterative(Leaf *leaf, int data)
{
    Leaf* last_child = NULL;
    Leaf* child = NULL;
    Leaf* root = leafRoot(leaf);
    while(root){
        child = root->children;
        while (child){
            if(child->data == data){
                last_child = child;
            }
            child = child->next;
        }
        root = (root->children) ? (root->children->next) : (NULL);
    }
    return last_child;
}

Leaf*	leafNthChild(Leaf *leaf, int n)
{
	if (! leaf)
		return NULL;
	leaf = leaf->children;
	while (leaf && (n-- > 0))
		leaf = leaf->next;
	return leaf;
}

int	leafTotal(Leaf	*root)
{
	if (! root)
		return 0;
	int t;
	
	t = 1;
	if (root->children)
		t += leafTotal(root->children);
	if (root->next)
		t += leafTotal(root->next);
	return t;
}

void	leafUnlink(Leaf *leaf)
{
	if (! leaf)
		return;
	if (leaf->prev)
		leaf->prev->next = leaf->next;
	else if (leaf->parent)
		leaf->parent->children = leaf->next;
	if (leaf->next)
	{
		leaf->next->prev = leaf->prev;
		leaf->next = NULL;
	}
	leaf->prev = NULL;
	leaf->parent = NULL;
}

void	leafFree(Leaf *leaf)
{
	if (! leaf)
		return;
	if (leaf->children)
		leafFree(leaf->children);
	if (leaf->next)
		leafFree(leaf->next);
	free(leaf);
}

void	leafDestroy(Leaf *root)
{
	if (! root)
		return;
	if (! leafIsRoot(root))
		leafUnlink(root);
	leafFree(root);
}

void printLeafs(Leaf *leaf){
    printf("[%d]:\n", leaf->data);
    leaf = leaf->children;
	while (leaf){
        printf(" -> [%d]", leaf->data );
        leaf = leaf->next;
    }
    printf("\n");
}

void printTree(Leaf *leaf){
    Leaf* root = leafRoot(leaf);
    while(root){
	    printLeafs(root);
        root = (root->children) ? (root->children->next) : (NULL);
    }
}

void leafAppendFromData(Leaf *leaf, int data, int data_new_leaf){
    Leaf* root = leafRoot(leaf);
    leafAppend(findLeafFromRootIterative(root, data), leafNew(data_new_leaf));
}

bool ifLeafIsChildren(Leaf *leaf, int data_leaf_pai, int data_children){
    Leaf* root = leafRoot(leaf);
    Leaf* child = findLastLeafFromRootIterative(root, data_children);
    return (child && child->parent && child->parent->data == data_leaf_pai);
}
