// Compile this assignment with: clang -g -Wall main.c -o main.out
// Use this file to implement testing for your
// doubly linked list implementation

#include <stdio.h>  // For IO operations
#include <stdlib.h> // for malloc/free

#include "my_dll.h"




// ====================================================
// ================== Program Entry ===================
// ====================================================
int unitTest1(int status)
{
    int passed = 0;
    dll_t *test = create_dll();
    dll_push_back(test,123);
    dll_push_front(test,321);
    dll_insert(test,0,99);
    if (dll_size(test)==3 && test->head->data == 99)
    {
        passed = 1;
    }
    free_dll(test);

    return passed;
}

int unitTest2(int status)
{
    int passed = 0;
    dll_t *test = create_dll();
    dll_push_back(test,123);
    dll_push_front(test,321);
    dll_insert(test,1,99);
    if (dll_size(test)==3 && test->head->next->data == 99)
    {
        passed = 1;
    }
    free_dll(test);

    return passed;
}

int unitTest3(int status)
{
    int passed = 0;
    dll_t *test = create_dll();
    dll_push_back(test,123);
    dll_push_front(test,321);
    dll_insert(test,2,99);
    if (dll_size(test)==2)
    {
        passed = 1;
    }
    free_dll(test);

    return passed;
}

int unitTest4(int status)
{
    int passed = 0;
    dll_t *test = create_dll();
    dll_push_back(test,123);
    dll_push_front(test,321);
    dll_insert(test,0,99);
    if (dll_size(test)==3 && test->head->data == 99 && test->head->next->data== 321 && test->head->next->next->data == 123)
    {
        passed = 1;
    }
    free_dll(test);

    return passed;
}

int unitTest5(int status)
{
    int passed = 0;
    dll_t *test = create_dll();
    dll_push_back(test,123);
    dll_push_front(test,321);
    dll_insert(test,0,99);
    // 99, 321, 123
    int pop = dll_remove(test,1);
    if (dll_size(test)==2 && pop ==321 )
    {
        passed = 1;
    }
    free_dll(test);

    return passed;
}

int (*unitTests[])(int) = {
   unitTest1,
   unitTest2,
   unitTest3,
   unitTest4,
   unitTest5,
    NULL};

int main()
{
    unsigned int testsPassed = 0;
    // List of Unit Tests to test your data structure
    int counter = 0;
    while (unitTests[counter] != NULL)
    {
        printf("========unitTest %d========\n", counter);
        if (1 == unitTests[counter](1))
        {
            printf("passed test\n");
            testsPassed++;
        }
        else
        {
            printf("failed test, missing functionality, or incorrect test\n");
        }
        counter++;
    }

    printf("%d of %d tests passed\n", testsPassed, counter);

    return 0;
}