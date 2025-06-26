#ifndef OPERATOR_PRECEDENCE_H
#define OPERATOR_PRECEDENCE_H
#include <stdexcept>
enum class Operator { ADD, SUBTRACT, MULTIPLY, DIVIDE, POWER, NONE };
int getPrecedence(Operator op);
Operator getOperator(char c);
bool comparePrecedence(char op1, char op2);
#endif
