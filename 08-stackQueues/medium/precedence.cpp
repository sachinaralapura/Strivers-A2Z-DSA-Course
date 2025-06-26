#include "precedence.h"
int getPrecedence(Operator op) {
    switch (op) {
    case Operator::ADD:
    case Operator::SUBTRACT:
        return 1;
    case Operator::MULTIPLY:
    case Operator::DIVIDE:
        return 2;
    case Operator::POWER:
        return 3;
    case Operator::NONE:
        return -1;
    }
    return -1;
}

Operator getOperator(char c) {
    switch (c) {
    case '+':
        return Operator::ADD;
    case '-':
        return Operator::SUBTRACT;
    case '*':
        return Operator::MULTIPLY;
    case '/':
        return Operator::DIVIDE;
    case '^':
        return Operator::POWER;
    default:
        return Operator::NONE;
    }
}

bool comparePrecedence(char op1, char op2) {
    Operator operator1 = getOperator(op1);
    Operator operator2 = getOperator(op2);
    return getPrecedence(operator1) >= getPrecedence(operator2);
}
