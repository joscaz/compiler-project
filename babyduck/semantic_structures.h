/*
 * semantic_structures.h - Structures definition for semantic analysis of BabyDuck
 */

#ifndef SEMANTIC_STRUCTURES_H
#define SEMANTIC_STRUCTURES_H

#include <stdlib.h>
#include <string.h>
#include "semantic_cube.h"

// I put these lengths just because I think it's logic
#define MAX_FUNC_NAME 50
#define MAX_VAR_NAME 50
#define MAX_VARIABLES 100
#define MAX_FUNCTIONS 50
#define MAX_PARAMS 10

// Struct to represent a variable
typedef struct {
    char name[MAX_VAR_NAME];
    DataType type; // float or int
    int address; // virtual memory
} Variable;

// Struct for the variables table
typedef struct {
    Variable vars[MAX_VARIABLES];
    int count; // var count
} VarTable;

// Function struct
typedef struct {
    char name[MAX_FUNC_NAME];
    Variable params[MAX_PARAMS];
    int paramCount; // count parameters of function
    VarTable localVars; // table of local vars
    int startQuad; // doing some investigation, I'll need the starting quadruple for functions later
} Function;

// Function directory struct
typedef struct {
    Function functions[MAX_FUNCTIONS];
    int count; // function counter
    VarTable globalVars; // global vars table
} FunctionDirectory;

// init func dir
void initFunctionDirectory(FunctionDirectory *dir);

// Search function within func dir
Function* findFunction(FunctionDirectory *dir, const char *name);

// Add function to func dir
int addFunction(FunctionDirectory *dir, const char *name);

// Add param to a function
int addParameter(Function *func, const char *name, DataType type, int address);

// Init variables table
void initVarTable(VarTable *table);

// Search variables in table
Variable* findVar(VarTable *table, const char *name);

// Add variable to table
int addVar(VarTable *table, const char *name, DataType type, int address);

// Search for variable
Variable* findVariable(FunctionDirectory *dir, const char *funcName, const char *varName);

// Search for param in function
Variable* findParam(Function *func, const char *name);

#endif // SEMANTIC_STRUCTURES_H