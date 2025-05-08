/*
 * semantic_cube.h - Definition for Babyduck's semantic cube
 */

#ifndef SEMANTIC_CUBE_H
#define SEMANTIC_CUBE_H

#include "datatype.h"

// // Definition for Babyduck types
// typedef enum {
//     TYPE_ERROR = -1, // for invalid operations
//     TYPE_INT = 0,
//     TYPE_FLOAT = 1,
//     TYPE_BOOL = 2
// } DataType;

// Operators definition
typedef enum {
    OP_PLUS = 0,
    OP_MINUS = 1,
    OP_MULT = 2,
    OP_DIV = 3,
    OP_LT = 4,
    OP_GT = 5,
    OP_NEQ = 6,
    OP_ASSIGN = 7
} Operator;

#define NUM_TYPES 3
#define NUM_OPERATORS 8

// Semantic cube - result[op1][op2][operator]
// Multi-dimensional matrix which indicates resulting
// value from a operation between two types
extern DataType semanticCube[NUM_TYPES][NUM_TYPES][NUM_OPERATORS];

// Initialize semantic cube
void initSemanticCube();

DataType getResultType(DataType left, DataType right, Operator op);

#endif // SEMANTIC_CUBE_H