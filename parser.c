#include "parser.h"

#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

int get_operator_precedence(const char c) {
    switch (c) {
        case '+': case '-': return 1;
        case '*': case '/': case '%': return 2;
        default: return -1;
    }
}

int is_operator(const char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

e_Operators get_operator_id(const char c) {
    switch (c) {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '%': return MOD;
        default: return -1;
    }
}

char get_operator(const e_Operators id) {
    switch (id) {
        case ADD: return '+';
        case SUB: return '-';
        case MUL: return '*';
        case DIV: return '/';
        case MOD: return '%';
        default: return 0;
    }
}

char *parse_expression(const char* s) {
    if (!s) {
        printf("Cannot parse empty expression!\n");
        return NULL;
    }

    Stack* operators = NULL;

    char* res = NULL;
    unsigned int i = 0;
    char c = *s;

    unsigned short state = 0;

    while (c != '\0') {
        switch (state) {
            case 0: { // General State
                if (c == ' ') {
                    c = *++s;
                } else if (c >= '0' && c <= '9') {
                    state = 1;
                } else if (is_operator(c)) {
                    state = 2;
                } else if (c == '(') {
                    state = 3;
                } else if (c == ')') {
                    state = 4;
                } else if (c >= 'A' && c <= 'Z') {
                    state = 5;
                } else state = 6;

                break;
            }
            case 1: { // Parse numbers
                if (c >= '0' && c <= '9') {
                    i++;

                    res = realloc(res, (i + 1) * sizeof(char));
                    if (!res) {
                        printf("Memory allocation failed!\n");
                        free_stack(operators);

                        return NULL;
                    }

                    res[i - 1] = c;

                    c = *++s;
                } else {
                    i++;

                    res = realloc(res, (i + 1) * sizeof(char));
                    if (!res) {
                        printf("Memory allocation failed!\n");
                        free_stack(operators);

                        return NULL;
                    }

                    res[i - 1] = ' ';

                    state = 0;
                }

                break;
            }
            case 2: { // Parse operators
                int precedence = get_operator_precedence(c);

                while (operators && operators->size > 0 && get_operator_precedence(get_operator(operators->top->value)) >= precedence) {
                    const e_Operators operator = pop_stack(operators);
                    const char op = get_operator(operator);

                    i += 2;

                    res = realloc(res, (i + 1) * sizeof(char));
                    if (!res) {
                        printf("Memory allocation failed!\n");
                        free_stack(operators);

                        return NULL;
                    }

                    res[i - 2] = op;
                    res[i - 1] = ' ';
                }

                operators = push_stack(operators, get_operator_id(c));

                c = *++s;
                state = 0;

                break;
            }
            case 3: { // Left parenthesis
                operators = push_stack(operators, PAR);

                c = *++s;
                state = 0;

                break;
            }
            case 4: { // Right parenthesis
                while (operators && operators->size > 0 && operators->top->value != PAR) {
                    const e_Operators operator = pop_stack(operators);
                    const char op = get_operator(operator);

                    i += 2;

                    res = realloc(res, (i + 1) * sizeof(char));
                    if (!res) {
                        printf("Memory allocation failed!\n");
                        free_stack(operators);

                        return NULL;
                    }

                    res[i - 2] = op;
                    res[i - 1] = ' ';
                }

                if (!operators || operators->size == 0) {
                    printf("Missing parenthesis!\n");

                    free_stack(operators);
                    if (res) free(res);

                    return NULL;
                }

                pop_stack(operators);

                c = *++s;
                state = 0;

                break;
            }
            case 5: { // Parse variables
                i += 2;

                res = realloc(res, (i + 1) * sizeof(char));
                if (!res) {
                    printf("Memory allocation failed!\n");
                    free_stack(operators);

                    return NULL;
                }

                res[i - 2] = c;
                res[i - 1] = ' ';

                c = *++s;
                state = 0;

                break;
            }
            case 6: { // Error state
                printf("Unknown character '%c'!\n", c);
                free_stack(operators);
                if (res) free(res);

                return NULL;
            }
            default:
                printf("Unknown state!\n");
                free_stack(operators);
                if (res) free(res);

                return NULL;
        }
    }

    while (operators && operators->size > 0) {
        const e_Operators operator = pop_stack(operators);
        c = get_operator(operator);

        i += 2;

        res = realloc(res, (i + 1) * sizeof(char));
        if (!res) {
            printf("Memory allocation failed!\n");
            free_stack(operators);

            return NULL;
        }

        res[i - 2] = ' ';
        res[i - 1] = c;
    }

    free_stack(operators);
    res[i] = '\0';

    return res;
}