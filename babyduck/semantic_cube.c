/*
 * semantic_cube.c - Implementation for Babyduck's semantic cube
 */

#include "semantic_cube.h"

DataType semanticCube[NUM_TYPES][NUM_TYPES][NUM_OPERATORS];

void initSemanticCube() {
    int i, j, k;

    // Init everything with TYPE_ERROR
    for (i = 0; i < NUM_TYPES; i++) {
        for (j = 0; j < NUM_TYPES; j++) {
            for (k = 0; k < NUM_OPERATORS; k++) {
                semanticCube[i][j][k] = TYPE_ERROR;
            }
        }
    }

    // PLUS operator
    semanticCube[TYPE_INT][TYPE_INT][OP_PLUS] = TYPE_INT;
    semanticCube[TYPE_INT][TYPE_FLOAT][OP_PLUS] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_INT][OP_PLUS] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_FLOAT][OP_PLUS] = TYPE_FLOAT;
    
    // MINUS operator
    semanticCube[TYPE_INT][TYPE_INT][OP_MINUS] = TYPE_INT;
    semanticCube[TYPE_INT][TYPE_FLOAT][OP_MINUS] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_INT][OP_MINUS] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_FLOAT][OP_MINUS] = TYPE_FLOAT;
    
    // MULT operator
    semanticCube[TYPE_INT][TYPE_INT][OP_MULT] = TYPE_INT;
    semanticCube[TYPE_INT][TYPE_FLOAT][OP_MULT] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_INT][OP_MULT] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_FLOAT][OP_MULT] = TYPE_FLOAT;
    
    // DIV operator
    semanticCube[TYPE_INT][TYPE_INT][OP_DIV] = TYPE_FLOAT; // División entera produce float en BabyDuck
    semanticCube[TYPE_INT][TYPE_FLOAT][OP_DIV] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_INT][OP_DIV] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_FLOAT][OP_DIV] = TYPE_FLOAT;
    
    // LT operator
    semanticCube[TYPE_INT][TYPE_INT][OP_LT] = TYPE_BOOL;
    semanticCube[TYPE_INT][TYPE_FLOAT][OP_LT] = TYPE_BOOL;
    semanticCube[TYPE_FLOAT][TYPE_INT][OP_LT] = TYPE_BOOL;
    semanticCube[TYPE_FLOAT][TYPE_FLOAT][OP_LT] = TYPE_BOOL;
    
    // GT operator
    semanticCube[TYPE_INT][TYPE_INT][OP_GT] = TYPE_BOOL;
    semanticCube[TYPE_INT][TYPE_FLOAT][OP_GT] = TYPE_BOOL;
    semanticCube[TYPE_FLOAT][TYPE_INT][OP_GT] = TYPE_BOOL;
    semanticCube[TYPE_FLOAT][TYPE_FLOAT][OP_GT] = TYPE_BOOL;
    
    // NEQ operator
    semanticCube[TYPE_INT][TYPE_INT][OP_NEQ] = TYPE_BOOL;
    semanticCube[TYPE_INT][TYPE_FLOAT][OP_NEQ] = TYPE_BOOL;
    semanticCube[TYPE_FLOAT][TYPE_INT][OP_NEQ] = TYPE_BOOL;
    semanticCube[TYPE_FLOAT][TYPE_FLOAT][OP_NEQ] = TYPE_BOOL;
    
    // ASSIGN operator
    semanticCube[TYPE_INT][TYPE_INT][OP_ASSIGN] = TYPE_INT;
    semanticCube[TYPE_FLOAT][TYPE_FLOAT][OP_ASSIGN] = TYPE_FLOAT;
    semanticCube[TYPE_FLOAT][TYPE_INT][OP_ASSIGN] = TYPE_FLOAT; // int -> float allowed
    // float -> int not allowed in this case
}

DataType getResultType(DataType left, DataType right, QuadOperator op) {
    // Verify that types are inside the range
    if (left < 0 || left >= NUM_TYPES || right < 0 || right >= NUM_TYPES || op < 0 || op >= NUM_OPERATORS) {
        return TYPE_ERROR; // if the condition meets means that is not valid
    }

    return semanticCube[left][right][op];
}