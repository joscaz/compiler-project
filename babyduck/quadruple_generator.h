#ifndef QUADRUPLE_GENERATOR_H
#define QUADRUPLE_GENERATOR_H

#include "stack.h"
#include "quadruple.h"
#include "constant_table.h"
#include "virtual_memory.h"
#include "semantic_structures.h"

typedef struct {
    // stacks
    OperandStack operands;
    OperatorStack operators;
    TypeStack types;
    JumpStack jumps;

    QuadQueue quadQueue;

    ConstantTable constTable;

    MemoryCounters memCounters;
} QuadrupleGenerator;

void initQuadrupleGenerator(QuadrupleGenerator *generator);

void processOperand(QuadrupleGenerator *generator, const char *name, FunctionDirectory *funcDir, const char *currentFunction);

void processIntConstant(QuadrupleGenerator *generator, int value);

void processFloatConstant(QuadrupleGenerator *generator, float value);

void processStringConstant(QuadrupleGenerator *generator, const char *value);

void processOperator(QuadrupleGenerator *generator, QuadOperator op);

void generateAssignment(QuadrupleGenerator *generator, const char *varName, FunctionDirectory *funcDir, const char *currentFunction);

void generatePrint(QuadrupleGenerator *generator);

void processRelationalOperator(QuadrupleGenerator *generator, QuadOperator op);

int getNextTemp(QuadrupleGenerator *generator, DataType type);

// Functions for conditional statements (if-else)
int getCurrentQuadCounter(QuadrupleGenerator *generator);
void startIfStatement(QuadrupleGenerator *generator);
void processElseStatement(QuadrupleGenerator *generator);
void endIfStatement(QuadrupleGenerator *generator);

// Functions for loop statements (while-do)
void startWhileLoop(QuadrupleGenerator *generator);
void processWhileCondition(QuadrupleGenerator *generator);
void endWhileLoop(QuadrupleGenerator *generator);

void printGeneratedQuadruples(QuadrupleGenerator *generator);

#endif // QUADRUPLE_GENERATOR_H 