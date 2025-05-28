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

// ===== NUEVAS FUNCIONES PARA ESTATUTOS CONDICIONALES Y CÍCLICOS =====

// Obtener el contador actual de cuádruplos
int getCurrentQuadCounter(QuadrupleGenerator *generator) {
    return generator->quadQueue.count;
}

// Inicia un estatuto if - genera cuadruplo GOTOF después de evaluar condición
void startIfStatement(QuadrupleGenerator *generator) {
    if (isOperandStackEmpty(&generator->operands)) {
        fprintf(stderr, "Error: Missing condition for if statement\n");
        return;
    }
    
    // Verificar que la condición sea de tipo booleano
    if (peekType(&generator->types) != TYPE_BOOL) {
        fprintf(stderr, "Error: Condition for if statement must be boolean\n");
        return;
    }
    
    // Obtener la dirección del resultado de la condición
    int condition = popOperand(&generator->operands);
    popType(&generator->types); // Ya verificamos que es booleano
    
    // Generar cuadruplo GOTOF (ir a falso) con destino pendiente
    int quadIndex = addQuadruple(&generator->quadQueue, OP_GOTOF, condition, -1, -1);
    
    // Guardar la posición del cuadruplo para actualizar después
    pushJump(&generator->jumps, quadIndex);
}

// Genera salto al final del if cuando hay un else
void processElseStatement(QuadrupleGenerator *generator) {
    // Generar GOTO al final del if-else con destino pendiente
    int gotoIndex = addQuadruple(&generator->quadQueue, OP_GOTO, -1, -1, -1);
    
    // Obtener el índice del GOTOF para actualizarlo
    int gotofIndex = popJump(&generator->jumps);
    
    // Actualizar el GOTOF para saltar al inicio del else (cuadruplo actual)
    updateQuadrupleResult(&generator->quadQueue, gotofIndex, getCurrentQuadCounter(generator));
    
    // Guardar la posición del GOTO para actualizarlo al final del if-else
    pushJump(&generator->jumps, gotoIndex);
}

// Termina un estatuto if-else y actualiza los saltos pendientes
void endIfStatement(QuadrupleGenerator *generator) {
    if (isJumpStackEmpty(&generator->jumps)) {
        fprintf(stderr, "Error: No pending jumps to resolve for if statement\n");
        return;
    }
    
    // Obtener el índice del salto pendiente (GOTOF o GOTO)
    int jumpIndex = popJump(&generator->jumps);
    
    // Actualizar el cuadruplo para saltar al final del if o if-else
    updateQuadrupleResult(&generator->quadQueue, jumpIndex, getCurrentQuadCounter(generator));
}

// Marca el inicio de un ciclo while
void startWhileLoop(QuadrupleGenerator *generator) {
    // Guardar la posición actual para regresar después de cada iteración
    pushJump(&generator->jumps, getCurrentQuadCounter(generator));
}

// Genera cuadruplo GOTOF después de evaluar condición del while
void processWhileCondition(QuadrupleGenerator *generator) {
    if (isOperandStackEmpty(&generator->operands)) {
        fprintf(stderr, "Error: Missing condition for while loop\n");
        return;
    }
    
    // Verificar que la condición sea de tipo booleano
    if (peekType(&generator->types) != TYPE_BOOL) {
        fprintf(stderr, "Error: Condition for while loop must be boolean\n");
        return;
    }
    
    // Obtener la dirección del resultado de la condición
    int condition = popOperand(&generator->operands);
    popType(&generator->types); // Ya verificamos que es booleano
    
    // Generar cuadruplo GOTOF (ir a falso) con destino pendiente
    int quadIndex = addQuadruple(&generator->quadQueue, OP_GOTOF, condition, -1, -1);
    
    // Guardar la posición del GOTOF para actualizar después
    pushJump(&generator->jumps, quadIndex);
}

// Termina un ciclo while y genera cuadruplo de salto al inicio
void endWhileLoop(QuadrupleGenerator *generator) {
    if (isJumpStackEmpty(&generator->jumps) || generator->jumps.top < 1) {
        fprintf(stderr, "Error: No pending jumps to resolve for while loop\n");
        return;
    }
    
    // Obtener el índice del GOTOF
    int gotofIndex = popJump(&generator->jumps);
    
    // Obtener el índice de inicio del ciclo
    int startIndex = popJump(&generator->jumps);
    
    // Generar cuadruplo GOTO al inicio del ciclo
    addQuadruple(&generator->quadQueue, OP_GOTO, -1, -1, startIndex);
    
    // Actualizar el GOTOF para saltar al final del ciclo (cuadruplo siguiente)
    updateQuadrupleResult(&generator->quadQueue, gotofIndex, getCurrentQuadCounter(generator));
}

void printGeneratedQuadruples(QuadrupleGenerator *generator) {
    printQuadruples(&generator->quadQueue);
    printConstantTable(&generator->constTable);
}

// ===== FUNCIONES PARA DECLARACIÓN E INVOCACIÓN DE FUNCIONES =====

// Inicia una llamada a función - genera cuadruplo ERA (Espacio de Registro de Activación)
void startFunctionCall(QuadrupleGenerator *generator, const char *funcName, FunctionDirectory *funcDir) {
    Function *func = findFunction(funcDir, funcName);
    if (func == NULL) {
        fprintf(stderr, "Error: Function '%s' not found\n", funcName);
        return;
    }
    
    // Generar cuadruplo ERA para reservar espacio para la función
    // El operando1 contiene el nombre de la función (usamos su dirección de inicio)
    // El operando2 contiene el número de parámetros
    addQuadruple(&generator->quadQueue, OP_ERA, func->startQuad, func->paramCount, -1);
}

// Procesa un parámetro de función - genera cuadruplo PARAM
void processFunctionParameter(QuadrupleGenerator *generator, int paramIndex) {
    if (isOperandStackEmpty(&generator->operands)) {
        fprintf(stderr, "Error: No value for parameter %d\n", paramIndex);
        return;
    }
    
    // Obtener el valor del parámetro de la pila
    int paramValue = popOperand(&generator->operands);
    DataType paramType = popType(&generator->types);
    
    // Generar cuadruplo PARAM
    // operando1: valor del parámetro
    // operando2: índice del parámetro (para verificación de tipos)
    // resultado: no se usa
    addQuadruple(&generator->quadQueue, OP_PARAM, paramValue, paramIndex, -1);
}

// Termina una llamada a función - genera cuadruplo GOSUB
void endFunctionCall(QuadrupleGenerator *generator, const char *funcName, FunctionDirectory *funcDir) {
    Function *func = findFunction(funcDir, funcName);
    if (func == NULL) {
        fprintf(stderr, "Error: Function '%s' not found\n", funcName);
        return;
    }
    
    // Generar cuadruplo GOSUB para saltar a la función
    // operando1: dirección de inicio de la función
    // operando2 y resultado: no se usan
    addQuadruple(&generator->quadQueue, OP_GOSUB, func->startQuad, -1, -1);
}