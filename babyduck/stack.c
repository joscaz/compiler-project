#include "stack.h"
#include <stdio.h>

// OPERATORS
void initOperatorStack(OperatorStack *stack) {
    stack->top = -1;
}

int pushOperator(OperatorStack *stack, QuadOperator op) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Error: Operator stack overflow\n");
        return 0;
    }

    stack->elements[++stack->top] = op;
    return 1;
}

QuadOperator popOperator(OperatorStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Operator stack underflow\n");
        return -1;
    }
    return stack->elements[stack->top--];
}

QuadOperator peekOperator(OperatorStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Operator stack is empty\n");
        return -1;
    }

    return stack->elements[stack->top];
}

int isOperatorStackEmpty(OperatorStack *stack) {
    return stack->top < 0;
}

// OPERANDOS
void initOperandStack(OperandStack *stack) {
    stack->top = -1;
}

int pushOperand(OperandStack *stack, int operand) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Error: Operand stack overflow\n");
        return 0;
    }

    stack->elements[++stack->top] = operand;
    return 1;
}

int popOperand(OperandStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Operand stack underflow\n");
        return -1;
    }

    return stack->elements[stack->top--];
}

int peekOperand(OperandStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Operand stack is empty\n");
        return -1;
    }

    return stack->elements[stack->top];
}

int isOperandStackEmpty(OperandStack *stack) {
    return stack->top < 0;
}

// TYPES
void initTypeStack(TypeStack *stack) {
    stack->top = -1;
}

int pushType(TypeStack *stack, DataType type) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Error: Type stack overflow\n");
        return 0;
    }

    stack->elements[++stack->top] = type;
    return 1;
}

DataType popType(TypeStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Type stack underflow\n");
        return TYPE_ERROR;
    }

    return stack->elements[stack->top--];
}

DataType peekType(TypeStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Type stack is empty\n");
        return TYPE_ERROR;
    }

    return stack->elements[stack->top];
}

int isTypeStackEmpty(TypeStack *stack) {
    return stack->top < 0;
}

// JUMPS
void initJumpStack(JumpStack *stack) {
    stack->top = -1;
}

int pushJump(JumpStack *stack, int jump) {
    if (stack->top >= MAX_STACK_SIZE - 1) {
        fprintf(stderr, "Error: Jump stack overflow\n");
        return 0;
    }

    stack->elements[++stack->top] = jump;
    return 1;
}

int popJump(JumpStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Jump stack underflow\n");
        return -1;
    }

    return stack->elements[stack->top--];
}

int peekJump(JumpStack *stack) {
    if (stack->top < 0) {
        fprintf(stderr, "Error: Jump stack is empty\n");
        return -1;
    }

    return stack->elements[stack->top];
}

int isJumpStackEmpty(JumpStack *stack) {
    return stack->top < 0;
}