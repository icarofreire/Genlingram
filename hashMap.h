/* min Lib HashMap; */


struct hashMap {
    int capacity;
    int size; // Current number of elements in the map
    char **keys;//[MAX_SIZE][100]; // Array to store the keys
    int *values;//[MAX_SIZE]; // Array to store the values
};

// like constructor
struct hashMap* ini_hashMap()
{
    struct hashMap* mp = (struct hashMap*)malloc(sizeof(struct hashMap));
    // Default capacity in this case
    mp->capacity = 100;
    mp->size = 0;
    mp->keys = (char**)malloc(mp->capacity * sizeof(char*));
    mp->values = (int*)malloc(mp->capacity * sizeof(int));

    return mp;
}


// Function to get the index of a key in the keys array
int getIndex(struct hashMap* mp, char key[])
{
    for (int i = 0; i < mp->size; i++) {
        if (strcmp(mp->keys[i], key) == 0) {
            return i;
        }
    }
    return -1; // Key not found
}

// Function to insert a key-value pair into the map
void insert(struct hashMap* mp, char key[], int value)
{
    int index = getIndex(mp, key);

    if(index == -1 && mp->size >= mp->capacity) {
        mp->capacity++;
        mp->keys = (char**)realloc(mp->keys, mp->capacity * sizeof(char*));
        mp->values = (int*)realloc(mp->values, mp->capacity * sizeof(int));
    }

    if (index == -1 && mp->size < mp->capacity) { // Key not found
        mp->keys[mp->size] = (char*)malloc((strlen(key)+1)* sizeof(char));
        strcpy(mp->keys[mp->size], key);
        mp->values[mp->size] = value;
        mp->size++;
    }
}

// Function to get the value of a key in the map
int get(struct hashMap* mp, char key[])
{
    int index = getIndex(mp, key);
    if (index == -1) { // Key not found
        return -1;
    }
    else { // Key found
        return mp->values[index];
    }
}

int *getValues(struct hashMap* mp, int *reftam)
{
    *reftam = mp->size;
    int *dados = (int*)malloc((mp->size) * sizeof(int));
    for (int i = 0; i < mp->size; i++) {
        dados[i] = mp->values[i];
    }
    return dados;
}

char *getKeyByValue(struct hashMap* mp, int val)
{
    for (int i = 0; i < mp->size; i++) {
        if(mp->values[i] == val){
            return mp->keys[i];
        }
    }
    return NULL;
}

// Function to print the map
void printMap(struct hashMap* mp)
{
    printf("***\n");
    for (int i = 0; i < mp->size; i++) {
        printf("%s => %d\n", mp->keys[i], mp->values[i]);
    }
    printf("***\n");
}

void deleteKey(struct hashMap* mp, char key[])
{
    int index = getIndex(mp, key);
    if (index != -1) {
        mp->keys[index] = "";
        mp->values[index] = -1;
    }
}

void free_map(struct hashMap* mp){
    // Free memory for each string
    for (int i = 0; i < mp->size; i++) {
        free(mp->keys[i]);
    }
    // Free memory for the array of pointers
    free(mp->keys);
    free(mp->values);
    free(mp);
}

/*
 struct hashMap** mp = ini_hashMap();

 insert(mp, "Yogaholic", 1);
 insert(mp, "pluto14", 3);
 insert(mp, "elite_Programmer", 4);
 insert(mp, "GFG", 55);
 insert(mp, "decentBoy", 66);
 insert(mp, "decentBoy", 63);
 insert(mp, "decentBoy", 67);
 // deleteKey(mp, "GFG");
 printf("%d\n", get(mp, "elite_Programmer"));
 printf("%d\n", get(mp, "Yogaholic"));
 printf("%d\n", get(mp, "pluto14"));
 printf("%d\n", get(mp, "decentBoy"));
 printf("%d\n", get(mp, "GFG"));
 // deleteKey(mp, "GFG");
 printMap(mp);
*/
