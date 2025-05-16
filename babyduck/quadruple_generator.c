#include "quadruple_generator.h"
#include <stdio.h>

void initQuadrupleGenerator(QuadrupleGenerator *generator) {
    initOperandStack(&generator->operands);
    initOperatorStack(&generator->operators);
    initTypeStack(&generator->types);
    initJumpStack(&generator->jumps);
    initQuadQueue(&generator->quadQueue);
    initConstantTable(&generator->constTable);
    initMemoryCounters(&generator->memCounters);
}

int getNextTemp(QuadrupleGenerator *generator, DataType type) {
    return getNextTempAddress(&generator->memCounters, type);
}

void processOperand(QuadrupleGenerator *generator, const char *name, FunctionDirectory *funcDir, const char *currentFunction) {
    Variable *var = findVariable(funcDir, currentFunction, name);

    if (var == NULL) {
        fprintf(stderr, "Error: Variable '%s' not declared\n", name);
        return;
    }

    // push to stack
    pushOperand(&generator->operands, var->address);
    pushType(&generator->types, var->type);
}

void processIntConstant(QuadrupleGenerator *generator, int value) {
    int constIdx = findIntConstant(&generator->constTable, value);
    int address;

    if  (constIdx == -1) {
        // allocate new address for constant
        address = getNextConstAddress(&generator->memCounters, TYPE_INT);
        addIntConstant(&generator->constTable, value, address);
    } else {
        // use existing addres
        address = generator->constTable.constants[constIdx].address;
    }

    // push to stack
    pushOperand(&generator->operands, address);
    pushType(&generator->types, TYPE_INT);
}

void processFloatConstant(QuadrupleGenerator *generator, float value){
    // check if already exists
    int constIndex = findFloatConstant(&generator->constTable, value);
    int address;
    
    if (constIndex == -1) {
        // allocate new address for constant
        address = getNextConstAddress(&generator->memCounters, TYPE_FLOAT);
        addFloatConstant(&generator->constTable, value, address);
    } else {
        // use existing address
        address = generator->constTable.constants[constIndex].address;
    }
    
    // push to stack
    pushOperand(&generator->operands, address);
    pushType(&generator->types, TYPE_FLOAT);
}

void processStringConstant(QuadrupleGenerator *generator, const char *value) {
    // check if already exists
    int constIndex = findStringConstant(&generator->constTable, value);
    int address;
    
    if (constIndex == -1) {
        // allocate new address for constant
        address = getNextConstAddress(&generator->memCounters, TYPE_STRING);
        addStringConstant(&generator->constTable, value, address);
    } else {
        // use existing address
        address = generator->constTable.constants[constIndex].address;
    }
    
    // push to stack
    pushOperand(&generator->operands, address);
    pushType(&generator->types, TYPE_STRING);

}

// process operators like + - *
void processOperator(QuadrupleGenerator *generator, QuadOperator op) {
    // check if there are operands
    if (isOperandStackEmpty(&generator->operands) ||
        generator->operands.top < 1) {
        fprintf(stderr, "Error: Not enough operands for operation\n");
        return;
    }
    int rightOp = popOperand(&generator->operands);
    int leftOp = popOperand(&generator->operands);
    DataType rightType = popType(&generator->types);
    DataType leftType = popType(&generator->types);

    // usamos cubo semantico
    DataType resType = getResultType(leftType, rightType, op);

    if (resType == TYPE_ERROR) {
        fprintf(stderr, "Error: Type mismatch in operation\n"); // el tan querido type mismatch
        return;
    }

    //get tmp address for res
    int resAddress = getNextTemp(generator, resType);

    addQuadruple(&generator->quadQueue, op, leftOp, rightOp, resAddress);

    //push to stack
    pushOperand(&generator->operands, resAddress);
    pushType(&generator->types, resType);
}

void generateAssignment(QuadrupleGenerator *generator, const char *varName, FunctionDirectory *funcDir, const char *currentFunction) {
    Variable *var = findVariable(funcDir, currentFunction, varName);

    if (var == NULL) {
        fprintf(stderr, "Error: Variable '%s' not declared\n", varName);
        return;
    }

    // check if there is an exp result to assign
    if (isOperandStackEmpty(&generator->operands)) {
        fprintf(stderr, "Error: No value to assign\n");
        return;
    }

    int expRes = popOperand(&generator->operands);
    DataType expType = popType(&generator->types);

    // check type
    if (var->type != expType && 
        !(var->type == TYPE_FLOAT && expType == TYPE_INT)) { // allow int to float
            const char* varTypeStr = "UNKNOWN";
        const char* expTypeStr = "UNKNOWN";
        
        switch(var->type) {
            case TYPE_INT: varTypeStr = "INT"; break;
            case TYPE_FLOAT: varTypeStr = "FLOAT"; break;
            case TYPE_BOOL: varTypeStr = "BOOL"; break;
            case TYPE_STRING: varTypeStr = "STRING"; break;
            default: break;
        }
        
        switch(expType) {
            case TYPE_INT: expTypeStr = "INT"; break;
            case TYPE_FLOAT: expTypeStr = "FLOAT"; break;
            case TYPE_BOOL: expTypeStr = "BOOL"; break;
            case TYPE_STRING: expTypeStr = "STRING"; break;
            default: break;
        }
        
        fprintf(stderr, "Error: Type mismatch in assignment - Cannot assign %s to %s (var: %s)\n", 
                expTypeStr, varTypeStr, varName);
        return;

    }

    addQuadruple(&generator->quadQueue, OP_ASSIGN, expRes, -1, var->address);
}

void generatePrint(QuadrupleGenerator *generator) {
    // check if there is something to print
    if (isOperandStackEmpty(&generator->operands)) {
        fprintf(stderr, "Error: Nothing to print\n");
        return;
    }

    int valToPrint = popOperand(&generator->operands);
    popType(&generator->types);

    addQuadruple(&generator->quadQueue, OP_PRINT, valToPrint, -1, -1);
}

// for operators < > !=
void processRelationalOperator(QuadrupleGenerator *generator, QuadOperator op) {
    if (isOperandStackEmpty(&generator->operands) || generator->operands.top < 1) {
        fprintf(stderr, "Error: Not enough operands for relational operation\n");
        return;
    }

    int rightOp = popOperand(&generator->operands);
    int leftOp = popOperand(&generator->operands);
    DataType rightType = popType(&generator->types);
    DataType leftType = popType(&generator->types);

    // use semantic cube
    DataType resType = getResultType(leftType, rightType, op);

    if (resType == TYPE_ERROR) {
        fprintf(stderr, "Error: Type mismatch in relational operation\n");
        return;
    }

    // get tmp address for res q deberia ser booleano
    int resAddress = getNextTemp(generator, TYPE_BOOL);

    addQuadruple(&generator->quadQueue, op, leftOp, rightOp, resAddress);

    pushOperand(&generator->operands, resAddress);
    pushType(&generator->types, TYPE_BOOL);
}

void printGeneratedQuadruples(QuadrupleGenerator *generator) {
    printQuadruples(&generator->quadQueue);
    printConstantTable(&generator->constTable);
}