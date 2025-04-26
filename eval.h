#ifndef EVAL_H
#define EVAL_H

/**
 * evaluate - Evaluate a proper post-fix expression using a stack
 * @param s:char* -> The string to evaluate
 * @param vars:long long[26] -> Indexed table containing values of used variables
 * @return long long
 */
long long evaluate(const char*, long long[26]);

#endif //EVAL_H
