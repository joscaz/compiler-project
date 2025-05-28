#ifndef QUADRUPLE_H
#define QUADRUPLE_H

#include <stdlib.h>
#include "datatype.h"

// quadruple operators
typedef enum {
    OP_PLUS = 0,
    OP_MINUS = 1,
    OP_MULT = 2,
    OP_DIV = 3,
    OP_LT = 4,
    OP_GT = 5,
    OP_NEQ = 6,
    OP_ASSIGN = 7,
    OP_GOTO = 8,     // goto
    OP_GOTOF = 9,    // goto if false
    OP_GOTOV = 10,   // goto if true
    OP_PRINT = 11,
    OP_ERA = 12,     // function activation record
    OP_PARAM = 13,
    OP_GOSUB = 14,   // go to subroutine
    OP_RETURN = 15,  // return from subroutine
    OP_ENDPROC = 16, // end of procedure
    OP_EOF = 17     // halt program execution
} QuadOperator;

// quadruple struct
typedef struct {
    QuadOperator operador; // in spanish since operator it's a keyword
    int operand1;
    int operand2;
    int res;
} Quadruple;

#define MAX_QUADRUPLES 1000

// queue of quadruples
typedef struct {
    Quadruple quads[MAX_QUADRUPLES]; // TODO optimize later
    int count;
} QuadQueue;

// init quadruple queue
void initQuadQueue(QuadQueue *queue);

// add quadruple to queue
int addQuadruple(QuadQueue *queue, QuadOperator op, int op1, int op2, int res);

// get quadruple at specific idx
Quadruple* getQuadruple(QuadQueue *queue, int idx, int res);

// update the result field of a quadruple at a specific index
void updateQuadrupleResult(QuadQueue *queue, int idx, int res);

// custom print of quadruples
void printQuadruples(QuadQueue *queue);

// convert operator to string for display
const char* operatorToString(QuadOperator op);

#endif // QUADRUPLE_H