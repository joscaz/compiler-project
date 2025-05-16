/*
 * semantic_cube.h - Definition for Babyduck's semantic cube
 */

#ifndef SEMANTIC_CUBE_H
#define SEMANTIC_CUBE_H

#include "datatype.h"
#include "quadruple.h"

// // Definition for Babyduck types
// typedef enum {
//     TYPE_ERROR = -1, // for invalid operations
//     TYPE_INT = 0,
//     TYPE_FLOAT = 1,
//     TYPE_BOOL = 2
// } DataType;

// Operators definition
typedef QuadOperator Operator;

#define NUM_TYPES 3
#define NUM_OPERATORS 8

// Semantic cube - result[op1][op2][operator]
// Multi-dimensional matrix which indicates resulting
// value from a operation between two types
extern DataType semanticCube[NUM_TYPES][NUM_TYPES][NUM_OPERATORS];

// Initialize semantic cube
void initSemanticCube();

DataType getResultType(DataType left, DataType right, QuadOperator op);

#endif // SEMANTIC_CUBE_H