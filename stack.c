#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

Stack* allocate_stack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->top = NULL;

    return stack;
}

void free_stack(Stack* stack) {
    if (stack) {
        while (stack->size > 0) {
            pop_stack(stack);
        }

        free(stack);
    }
}

void print_stack(const Stack* stack, const char verbose) {
    if (stack) {
        if (verbose) printf("Stack<%p>: %lu elements.\n", stack, stack->size);

        printf("->");
        const StackNode* It = stack->top;
        while (It) {
            printf("|%lld", It->value);
            It = It->next;
        }
        printf("|\n");
    } else {
        printf("Stack does not exist!\n");
    }
}

Stack* push_stack(Stack* stack, const long long value) {
    if (!stack) {
        stack = allocate_stack();
    }

    StackNode* node = malloc(sizeof(StackNode));
    node->next = stack->top;
    node->value = value;

    stack->size++;
    stack->top = node;

    return stack;
}

long long pop_stack(Stack* stack) {
    long long res = 0;

    if (stack && stack->top) {
        StackNode* tmp = stack->top;
        stack->top = tmp->next;
        res = tmp->value;

        free(tmp);

        stack->size--;
    }

    return res;
}
