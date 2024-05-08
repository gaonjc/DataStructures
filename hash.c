#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define MAX_SIZE 0xF

typedef struct {
    uint8_t b0;
    uint8_t b1;
    uint8_t b2;
    uint8_t b3;
} my_int_struct;

typedef union
{
    uint32_t value;
    my_int_struct split;
} my_int_union;

typedef struct 
{
    uint32_t studentID;
    uint64_t phoneNr;
    // ...
} node_t;

node_t* create_node(uint32_t studID, uint64_t phone) {
    
    node_t* n0;
    n0 = NULL;
    n0 = (node_t*)malloc(sizeof(node_t)); 
    n0->studentID=studID;
    n0->phoneNr=phone;
    return n0;
} 
typedef struct {
    node_t* head;
    node_t* tail;
    
} queue_t;

int hash_function(uint32_t data) {
    int key = 0;

    my_int_union var;
    var.value = data;
    key = (var.split.b0 & var.split.b1) | (var.split.b2 & var.split.b3);

    //key = data % MAX_SIZE;
    key = key % MAX_SIZE;
    return key;
}

int hash_function_old(uint32_t data) {
    int key = 0;

    int b0 = data & 0xF;
    int b1 = (data >> 8) & 0xF;
    int b2 = (data >> 16) & 0xF;
    int b3 = (data >> 24) & 0xF;

    key = (b0 & b1) | (b2 & b3);

    key = key % MAX_SIZE;
    return key;
}

int addNodeFront(queue_t* myQueue, node_t* n) {
    if(myQueue->head == NULL) {
        myQueue->head = n;
        myQueue->tail = n;
    } //finish making queue later
    myQueue->head = n;
        
    return 0;
}

int addToHashTable(queue_t* myTable[], node_t* n) {
    if(n == NULL)
        return -1;

    int key = hash_function(n->studentID);
    addNodeFront(myTable[key], n);

    return 0;
}

int clearQueue(queue_t *q) {
    if(q == NULL)
        return 0;
    // dealocate all elements and the queue itself
    return 0;
}

int initializeHashTable(queue_t* myTable[], int size) {
    for(int ix = 0; ix < size; ++ix) {
        clearQueue(myTable[ix]);
        myTable[ix] = malloc(sizeof(queue_t));
        myTable[ix]->head = NULL; // redundant
        myTable[ix]->tail = NULL; // redundant
    }

    return 0;
}

node_t* createStudent(uint32_t id, uint64_t phone_no) {
    return NULL;
}


int main() {

    queue_t* myHashTable[MAX_SIZE];
    initializeHashTable(myHashTable, MAX_SIZE);
    addToHashTable(myHashTable, create_node(0x89AF5317, 9493518760));
    addToHashTable(myHashTable, create_node(0x89AF5317, 9493518760));
    addToHashTable(myHashTable, create_node(0x89AF5317, 9493518760));
    addToHashTable(myHashTable, create_node(0x89AF5317, 9493518760));
    addToHashTable(myHashTable, create_node(0x89AF5317, 9493518760));
    

    uint32_t studentID = 0x89AF5317;
    printf("the hash is %d \n", hash_function(studentID)); 

    for(int i=0; i<16; ++i)
        printf("the hash is %d \n", hash_function(i));


}