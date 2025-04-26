#include <stdio.h>
#include <stdlib.h>

#include "eval.h"
#include "parser.h"
#include "expression.h"

/**
 * get_string - Get string from stdin
 * @param string:char*
 * @return char*
 */
char* get_string(char *string) {
    int c;

    string = malloc(sizeof(char));
    string[0] = '\0';

    unsigned int i = 0;
    while (i < 1024 && (c = getchar()) != '\n' && c != EOF) {
        string = realloc(string, (i + 2) * sizeof(char));
        if (!string) return NULL;

        string[i] = (char) c;
        string[i + 1] = '\0';

        i++;
    }

    return string;
}

int main(void) {
    char *expression = NULL;
    char *res = NULL;
    char run = 1;

    while (run) {
        printf("Please enter an arithmetic expression: ");
        expression = get_string(expression);
        fflush(stdin);

        while (!is_expression_valid(expression)) {
            free(expression);
            printf("Malformed expression!\nPlease try again:");
            expression = get_string(expression);
        }

        res = parse_expression(expression);
        printf("======================\nExpression in stack-compatible form: %s\n----------------------\n", res);

        const long long value = evaluate(res, vars);
        printf("----------------------\nThus, %s=%lld\n======================\n", expression, value);

        char c = 0;
        while (c != 'n' && c != 'y' && c != 'N' && c != 'Y') {
            printf("Would you like to evaluate another expression (Y/N): ");
            scanf("%c", &c);
            fflush(stdin);
        }

        if (expression) free(expression);
        if (res) free(res);

        expression = NULL;
        res = NULL;

        if (c == 'n' || c == 'N') run = 0;
    }

    return 0;
}