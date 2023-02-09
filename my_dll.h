// =================== Support Code =================
// Doubly Linked List ( DLL ).
//
//
//
// - Implement each of the functions to create a working DLL.
// - Do not change any of the function declarations
//   - (i.e. dll_t* create_dll() should not have additional arguments)
// - You should not have any 'printf' statements in your DLL functions.
//   - (You may consider using these printf statements to debug,
//     but they should be removed from your final version)
//   - (You may write helper functions to help you debug your code such as print_list etc)
// ==================================================
#ifndef MYDLL_H
#define MYDLL_H

#include <stdlib.h>

// Create a node data structure to store data within
// our DLL. In our case, we will stores 'integers'
typedef struct node
{
    int data;
    struct node *next;
    struct node *previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL
{
    int count;    // count keeps track of how many items are in the DLL.
    node_t *head; // head points to the first node in our DLL.
    node_t *tail; // tail points to the last node in our DLL.
} dll_t;

// Creates a DLL
// Returns a pointer to a newly created DLL.
// The DLL should be initialized with data on the heap.
// (Think about what the means in terms of memory allocation)
// The DLLs fields should also be initialized to default values.
// Returns NULL if we could not allocate memory.
dll_t *create_dll()
{
    // Modify the body of this function as needed.
    dll_t *myDLL = NULL;

    // TODO: Implement me!!
    dll_t* dl = (dll_t*)malloc(sizeof(dll_t));
    if (dl == NULL) {
        return NULL;
    }

    dl->head = NULL;
    dl->tail = NULL;
    dl->count = 0;
    myDLL = dl;
    return myDLL;
}

// DLL Empty
// Check if the DLL is empty
// Returns -1 if the dll is NULL.
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
int dll_empty(dll_t *l)
{
    // TODO: Implement me!!
    if (l != NULL) {
        if (l->count == 0) {
            return 1;
        }else {
            return 0;
        }
    }
    return -1;
}

// push a new item to the front of the DLL ( before the first node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_front(dll_t *l, int item)
{
    // TODO: Implement me!!
    if (l == NULL) {
        return -1;
    }
    node_t* mynode = (node_t*)malloc(sizeof(node_t));
    mynode->data = item;
    mynode->next = l->head;
    mynode->previous = NULL;

    if (l->head != NULL) {
        l->head->previous = mynode;
    } else {
        l->tail = mynode;
    }
    l->head = mynode;
    l->count++;
    return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns -1 if DLL is NULL.
// Returns 1 on success
// Returns 0 on failure ( i.e. we couldn't allocate memory for the new node)
// (i.e. the memory allocation for a new node failed).
int dll_push_back(dll_t *l, int item)
{
    // TODO: Implement me!!
    if (l == NULL) {
        return -1;
    }
    node_t* mynode = (node_t*)malloc(sizeof(node_t));
    mynode->data = item;
    mynode->next = NULL;
    mynode->previous = l->tail;

    if (l->tail != NULL) {
        l->tail->previous = mynode;
    } else {
        l->head = mynode;
    }
    l->tail = mynode;
    l->count++;
    return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns -1 if the DLL is NULL.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_front(dll_t *t)
{
    if (t == NULL) {
        return -1;
    }
    if (t->head == NULL) {
        t->tail = NULL;
        return 0;
    }
    node_t* p = t->head;
    int pop = t->head->data;
    if (p->next != NULL) {
        t->head = p->next;
        p->next->previous = NULL;
    } else {
        t->head = NULL;
        t->tail = NULL;
    }
    free(p);
    t->count--;
    return pop;
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns a -1 if the DLL is NULL.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Assume no negative numbers in the list or the number zero.
int dll_pop_back(dll_t *t)
{
    if (t == NULL) {
        return -1;
    }

    node_t* p = t->tail;
    int pop = p->data;
    t->tail = p->previous;
    
    if (t->tail != NULL) {
        t->tail->next = NULL;
    } else {
        t->head = NULL;
    }
    if (t->head == NULL) {
        t->tail = NULL;
    }
    t->count--;
    free(p);
    return pop;
}

// Inserts a new node before the node at the specified position.
// Returns -1 if the list is NULL
// Returns 1 on success
// Retruns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
int dll_insert(dll_t *l, int pos, int item)
{
    // TODO: Implement me!!
    if (l == NULL) {
        return -1;
    }
    if (pos < 0 || pos > l->count-1) {
        return 0;
    }
    if (pos == 0) {
        dll_push_front(l,item);
    } else {
        node_t* p = l->head;
        for (int i = 0; i < pos-1; i++) {
            p = p->next;
        }
        node_t* mynode = (node_t*)malloc(sizeof(node_t));

        mynode->data = item;
        node_t* tmp = p->next;

        mynode->previous = p;
        mynode->next = tmp;
        tmp->previous = mynode;
        p->next = mynode;

        l->count++;
        return 1;
    }
    return 0;
    
}

// Returns the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Assume no negative numbers in the list or the number zero.
int dll_get(dll_t *l, int pos)
{
    // TODO: Implement me!!
    if (l == NULL) {
        return -1;
    }
    if (pos < 0 || pos > l->count) {
        return 0;
    }
    node_t* p = l->head;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }

    return p->data; // Note: This line is a 'filler' so the code compiles.
}

// Removes the item at position pos starting at 0 ( 0 being the first item )
// Returns -1 if the list is NULL
// Returns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Assume no negative numbers in the list or the number zero.
// Otherwise returns the value of the node removed.
int dll_remove(dll_t *l, int pos)
{
    // TODO: Implement me!!
    if (l == NULL) {
        return -1;
    }
    if (pos < 0 || pos > l->count-1) {
        return 0;
    }
    if (pos == 0) {
        return dll_pop_front(l);
    } 

    if (pos == l->count)
    {
        return dll_pop_back(l);
    }

    node_t* p = l->head;
    for (int i = 0; i < pos; i++) {
        p = p->next;
    }
    node_t* p2 = p->previous;

    p->previous->next = p->next;
    p->next->previous = p2;
    int pop = p->data;
    l->count--;
    free(p);
    return pop;
    // return -1;
}

// DLL Size
// Returns -1 if the DLL is NULL.
// Queries the current size of a DLL
int dll_size(dll_t *t)
{
    // TODO: Implement me!!
    if (t != NULL) {
        return t->count;
    }
    return -1; // Note: This line is a 'filler' so the code compiles.
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the program terminates.
void free_dll(dll_t *t)
{
    // TODO: Implement me!!
    if (t == NULL) {
        return;
    } 

    node_t* p = t->head;
    while(p != NULL) {
        node_t* p2 = p; 
        p = p->next;
        free(p2); 
    }
    free(t);
}

#endif