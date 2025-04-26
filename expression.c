#include "expression.h"

#include <stdio.h>

char *input;
char set[26];
long long vars[26];

void skip_spaces() {
    while (*input == ' ') input++;
}

char match(const char c) {
    skip_spaces();

    // Consume character if valid
    if (*input == c) {
        input++;
        return 1;
    }

    return 0;
}

char parse_nested() {
    skip_spaces();

    if (match('(')) {
        if (!parse_add()) return 0;
        if (!match(')')) return 0;

        return 1;
    }

    if (*input >= '0' && *input <= '9') return parse_number();
    if ((*input >= 'a' && *input <= 'z') || (*input >= 'A' && *input <= 'Z')) return parse_variable();

    return 0;
}

char parse_number() {
    skip_spaces();

    if (*input < '0' || *input > '9') return 0;
    while (*input >= '0' && *input <= '9') input++;

    return 1;
}

char parse_variable() {
    skip_spaces();

    // Consume character if valid
    char c = *input;
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        if (c >= 'a' && c <= 'z') c -= 32;
        *input = c;

        if (!set[c - 65]) {
            long long tmp;

            printf("Enter value for '%c': ", c);
            scanf("%lld", &tmp);
            fflush(stdin);

            set[c - 65] = 1;
            vars[c - 65] = tmp;
        }

        input++;
        return 1;
    }

    return 0;
}

char parse_mul() {
    if (!parse_nested()) return 0;

    while (1) {
        skip_spaces();

        if (*input == '*' || *input == '/' || *input == '%') {
            // Consume operator
            *input++;
            if (!parse_nested()) return 0;
        } else break;
    }

    return 1;
}

char parse_add() {
    if (!parse_mul()) return 0;

    while (1) {
        skip_spaces();
        if (*input == '+' || *input == '-') {
            // Consume operator
            *input++;
            if (!parse_mul()) return 0;
        } else break;
    }

    return 1;
}

int is_expression_valid(char *expr) {
    for (char i = 0; i < 26; i++) {
        set[i] = 0;
    }

    input = expr;

    if (parse_add()) {
        skip_spaces();

        // Accept if and only if input is fully consumed
        return *input == 0;
    }

    return 0;
}
