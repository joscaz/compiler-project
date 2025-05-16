#ifndef CONSTANT_TABLE_H
#define CONSTANT_TABLE_H

#include "datatype.h"
#include <stddef.h>

#define MAX_CONSTANTS 500
#define MAX_STRING_LENGTH 100

// representation of cte value
typedef struct {
    DataType type;
    union {
        int intVal;
        float floatVal;
        char stringVal[MAX_STRING_LENGTH];
    } value;
    int address; // virtual mem
} Constant;

typedef struct {
    Constant constants[MAX_CONSTANTS];
    int count;
} ConstantTable;

void initConstantTable(ConstantTable *table);

int addIntConstant(ConstantTable *table, int val, int address);
int addFloatConstant(ConstantTable *table, float val, int address);
int addStringConstant(ConstantTable *table, const char* val, int address);

int findIntConstant(ConstantTable *table, int val);
int findFloatConstant(ConstantTable *table, float val);
int findStringConstant(ConstantTable *table, const char* val);

Constant* getConstant(ConstantTable *table, int idx);

void printConstantTable(ConstantTable *table);

#endif // CONSTANT_TABLE_H