#include "eval.h"

#include "stack.h"
#include "parser.h"

#include <stdio.h>

long long evaluate(const char* s, long long vars[26]) {
    if (!s) {
        printf("Cannot evaluate empty string!\n");
        return 0;
    }

    Stack *stack = NULL;

    char c = *s;

    while (c != '\0') {
        if (c == ' ') {
            c = *++s;
        } else if (c >= 'A' && c <= 'Z') {
            stack = push_stack(stack, vars[c - 65]);

            print_stack(stack, 0);

            c = *++s;
        } else if (c >= '0' && c <= '9') {
            long long val = 0;
            while (c != ' ' && c != '\0') {
                val *= 10;
                val += c - '0';

                c = *++s;
            }

            stack = push_stack(stack, val);

            print_stack(stack, 0);
        } else if (is_operator(c)) {
            const long long b = pop_stack(stack);
            const long long a = pop_stack(stack);
            long long res;

            switch (get_operator_id(c)) {
                case ADD: res = a + b; break;
                case SUB: res = a - b; break;
                case MUL: res = a * b; break;
                case DIV: {
                    if (b == 0) {
                        printf("Division by 0!\n");
                        free_stack(stack);
                        return 0;
                    }

                    res = a / b;
                    break;
                }
                case MOD: res = a % b; break;
                default: {
                    printf("Unknown operator!\n");
                    free_stack(stack);
                    return 0;
                }
            }

            printf("(%c) ", c);
            stack = push_stack(stack, res);
            c = *++s;

            print_stack(stack, 0);
        } else {
            printf("Unknown character '%c'!\n", c);
            free_stack(stack);
            return 0;
        }
    }

    const long long res = pop_stack(stack);
    free_stack(stack);

    return res;
}
