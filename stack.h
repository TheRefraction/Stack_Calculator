#ifndef STACK_H
#define STACK_H

typedef struct STRUCT_STACK_NODE {
    long long value;
    struct STRUCT_STACK_NODE* next;
} StackNode;

typedef struct {
    unsigned int size;
    StackNode* top;
} Stack;

/**
 * allocate_stack - Allocate a new stack structure
 * @return Stack*
 */
Stack* allocate_stack();
/**
 * free_stack - Free the given stack
 * @param stack:Stack*
 * @return void
 */
void free_stack(Stack*);
/**
 * print_stack - Prints the given stack
 * @param stack:Stack*
 * @param verbose:char(bool) -> More detailed infos
 * @return int
 */
void print_stack(const Stack*, char);

/**
 * push_stack - Push given long long integer to current stack
 * @param stack:Stack*
 * @param value:long long
 * @return Stack*
 */
Stack* push_stack(Stack*, long long);
/**
 * pop_stack - Pop value from the top of the stack
 * @param stack:Stack*
 * @return long long
 */
long long pop_stack(Stack*);

#endif //STACK_H
