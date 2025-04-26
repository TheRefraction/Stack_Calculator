#ifndef EXPRESSION_H
#define EXPRESSION_H

/**
 * Indexed table which contains the values of used variables. The rest is undefined.
 */
extern long long vars[];

/**
 * skip_spaces - Consume all whitespaces in current buffer
 * @return void
 */
void skip_spaces();
/**
 * match - Consume given character if valid transition
 * and return whether the character has been consumed or not
 * @param c:char -> Character to check
 * @return char(bool)
 */
char match(char);

/**
 * parse_add - Parse additions and substractions of subexpressions
 * and return whether it was successful or not
 * @return char(bool)
 */
char parse_add();
/**
 * parse_mul - Parse multiplications, divisions and modulos of subexpressions
 * and return whether it was successful or not
 * @return char(bool)
 */
char parse_mul();
/**
 * parse_nested - Parse nested expressions as well as identifiers
 * and return whether it was successful or not
 * @return char(bool)
 */
char parse_nested();
/**
 * parse_number - Parse numbers
 * and return whether it was successful or not
 * @return char(bool)
 */
char parse_number();
/**
 * parse_variable - Parse variables, store their value in an indexed table
 * and return whether it was successful or not
 * @return char(bool)
 */
char parse_variable();

/**
 * is_expression_valid - Return whether an arithmetic expression is valid using a top-down recursion
 * and store new variables into an array
 * @param expr:char* -> Expression to check
 * @return int(bool)
 */
int is_expression_valid(char*);

#endif //EXPRESSION_H
