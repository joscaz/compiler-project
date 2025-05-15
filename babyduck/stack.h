#ifndef STACK_H
#define STACK_H

#include "datatype.h"
#include "quadruple.h"

#define MAX_STACK_SIZE 100

typedef struct {
    QuadOperator elements[MAX_STACK_SIZE];
    int top;
} OperatorStack;

// stores mem addresses
typedef struct {
    int elements[MAX_STACK_SIZE];
    int top;
} OperandStack;

typedef struct {
    DataType elements[MAX_STACK_SIZE];
    int top;
} TypeStack;

// pila de saltos
typedef struct {
    int elements[MAX_STACK_SIZE];
    int top;
} JumpStack;

void initOperatorStack(OperatorStack *stack);
int pushOperator(OperatorStack *stack, QuadOperator op);
QuadOperator popOperator(OperatorStack *stack);
QuadOperator peekOperator(OperatorStack *stack);
int isOperatorStackEmpty(OperatorStack *stack);

void initOperandStack(OperandStack *stack);
int pushOperand(OperandStack *stack, int operand);
int popOperand(OperandStack *stack);
int peekOperand(OperandStack *stack);
int isOperandStackEmpty(OperandStack *stack);

void initTypeStack(TypeStack *stack);
int pushType(TypeStack *stack, DataType type);
DataType popType(TypeStack *stack);
DataType peekType(TypeStack *stack);
int isTypeStackEmpty(TypeStack *stack);

void initJumpStack(JumpStack *stack);
int pushJump(JumpStack *stack, int jump);
int popJump(JumpStack *stack);
int peekJump(JumpStack *stack);
int isJumpStackEmpty(JumpStack *stack);

#endif // STACK_H