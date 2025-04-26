#ifndef PARSER_H
#define PARSER_H

typedef enum ENUM_OPERATORS {
    ADD = 0,
    SUB,
    MUL,
    DIV,
    MOD,
    PAR     // Token for parenthesis
} e_Operators;

/**
 * get_operator_precedence - Get priority of given character
 * @param c:char
 * @return int
 */
int get_operator_precedence(char);
/**
 * is_operator - Return whether the given character is an operator or not
 * @param c:char
 * @return int(bool)
 */
int is_operator(char);
/**
 * get_operator_id - Get id (in enum) of given operator
 * @param c:char
 * @return e_Operators(int)
 */
e_Operators get_operator_id(char);
/**
 * get_operator - Get operator from given id
 * @param id:e_Operators(int)
 * @return char
 */
char get_operator(e_Operators);

/**
 * parse_expression - Parse given expression and return a string containing its post-fix form
 * @param s:char*
 * @return char*
 */
char *parse_expression(const char*);

#endif //PARSER_H