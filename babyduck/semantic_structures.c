/*
 * semantic_structures.c
 */

#include <stdio.h>
#include "semantic_structures.h"

void initVarTable(VarTable *table) {
    table->count = 0;
};

Variable* findVar(VarTable *table, const char *name) {
    for (int i = 0; i < table->count; i++) {
        if (strcmp(table->vars[i].name, name) == 0) {
            return &table->vars[i];
        }
    }
    return NULL;
}

int addVar(VarTable *table, const char *name, DataType type, int address) {
    // Verify if var already exists
    if (findVar(table, name) != NULL) {
        return 0; // Variable already exists
    }

    // Check space
    if (table->count >= MAX_VARIABLES) {
        return -1;
    }

    strcpy(table->vars[table->count].name, name);
    table->vars[table->count].type = type;
    table->vars[table->count].address = address;
    table->count++;

    return 1;
}

void initFunctionDirectory(FunctionDirectory *dir) {
    dir->count = 0;
    initVarTable(&dir->globalVars);

    addFunction(dir, "main");
}

Function* findFunction(FunctionDirectory *dir, const char *name) {
    for (int i = 0; i < dir->count; i++) {
        if (strcmp(dir->functions[i].name, name) == 0) {
            return &dir->functions[i];
        }
    }

    return NULL;
}

int addFunction(FunctionDirectory *dir, const char *name) {
    if (findFunction(dir, name) != NULL) {
        return 0; // already declared
    }

    // Verify space
    if (dir->count >= MAX_FUNCTIONS) {
        return -1;
    }

    strcpy(dir->functions[dir->count].name, name);
    dir->functions[dir->count].paramCount = 0;
    dir->functions[dir->count].startQuad = -1; // no es parte de esta entrega pero servirá dsps
    initVarTable(&dir->functions[dir->count].localVars);
    dir->count++;

    return 1;
}

int addParameter(Function *func, const char *name, DataType type, int address) {
    // Verify if param already exists
    for (int i = 0; i < func->paramCount; i++) {
        if (strcmp(func->params[i].name, name) == 0) {
            return 0; // param already exists
        }
    }

    // check space
    if (func->paramCount >= MAX_PARAMS) {
        return -1;
    }

    // add parameter
    strcpy(func->params[func->paramCount].name, name);
    func->params[func->paramCount].type = type;
    func->params[func->paramCount].address = address;

    // add it as local var as well
    addVar(&func->localVars, name, type, address);

    func->paramCount++;
    
    return 1;
}

Variable* findVariable(FunctionDirectory *dir, const char *funcName, const char *varName) {
    Variable *var = NULL;
    Function *func = findFunction(dir, funcName);

    if (func != NULL) {
        var = findVar(&func->localVars, varName);
        if (var != NULL) {
            return var;
        }

        var = findParam(func, varName);
        if (var != NULL) {
            return var;
        }
    }

    // search in global vars
    return findVar(&dir->globalVars, varName);
}

Variable* findParam(Function *func, const char *name) {
    for (int i = 0; i < func->paramCount; i++) {
        if (strcmp(func->params[i].name, name) == 0) {
            return &func->params[i];
        }
    }
    return NULL;
}