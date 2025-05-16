#include "constant_table.h"
#include <stdio.h>
#include <string.h>
#include "virtual_memory.h"

void initConstantTable(ConstantTable *table) {
    table->count = 0;
}

int addIntConstant(ConstantTable *table, int val, int address) {
    if (table->count >= MAX_CONSTANTS) {
        fprintf(stderr, "Error: Constant table overflow\n");
        return -1;
    }

    // check if cte exists
    for (int i = 0; i < table->count; i++) {
        if (table->constants[i].type == TYPE_INT &&
            table->constants[i].value.intVal == val) {
            return i; // return idx of existing cte
        }
    }

    // add it if doesn't exists yet
    table->constants[table->count].type = TYPE_INT;
    table->constants[table->count].value.intVal = val;
    table->constants[table->count].address = address;

    return table->count++;
}

int addFloatConstant(ConstantTable *table, float val, int address) {
    if (table->count >= MAX_CONSTANTS) {
        fprintf(stderr, "Error: Constant table overflow\n");
        return -1;
    }

    // same as int, check if it exists
    for (int i = 0; i < table->count; i++) {
        if (table->constants[i].type == TYPE_FLOAT &&
            table->constants[i].value.floatVal == val) {
            return i;
        }
    }

    table->constants[table->count].type = TYPE_FLOAT;
    table->constants[table->count].value.floatVal = val;
    table->constants[table->count].address = address;

    return table->count++;
}

int addStringConstant(ConstantTable *table, const char *val, int address) {
    if (table->count >= MAX_CONSTANTS) {
        fprintf(stderr, "Error: Constant table overflow\n");
        return -1;
    }

    // check if it exists
    for (int i = 0; i < table->count; i++) {
        if (table->constants[i].type == TYPE_STRING &&
            strcmp(table->constants[i].value.stringVal, val) == 0) {
            return i;
        }
    }

    // add it
    table->constants[table->count].type = TYPE_STRING;
    strncpy(table->constants[table->count].value.stringVal, val, MAX_STRING_LENGTH - 1);
    table->constants[table->count].value.stringVal[MAX_STRING_LENGTH-1] = '\0';
    table->constants[table->count].address = address;

    return table->count;
}

int findIntConstant(ConstantTable *table, int val) {
    for (int i = 0; i < table->count; i++) {
        if (table->constants[i].type == TYPE_INT && 
            table->constants[i].value.intVal == val) {
            return i;
        }
    }
    return -1;
}

int findFloatConstant(ConstantTable *table, float value) {
    for (int i = 0; i < table->count; i++) {
        if (table->constants[i].type == TYPE_FLOAT && 
            table->constants[i].value.floatVal == value) {
            return i;
        }
    }
    return -1;
}

int findStringConstant(ConstantTable *table, const char *val) {
    for (int i = 0; i < table->count; i++) {
        if (table->constants[i].type == TYPE_STRING && 
            strcmp(table->constants[i].value.stringVal, val) == 0) {
            return i;
        }
    }
    return -1;
}

Constant* getConstant(ConstantTable *table, int idx) {
    if (idx < 0 || idx >= table->count) {
        return NULL;
    }

    return &(table->constants[idx]);
}

void printConstantTable(ConstantTable *table) {
    printf("\n===== CONSTANT TABLE =====\n");
    printf("Index\tType\tValue\t\tAddress\n");
    printf("------------------------------------------\n");

    for (int i = 0; i < table->count; i++) {
        Constant *c = &(table->constants[i]);

        printf("%d\t", i);

        switch(c->type) {
            case TYPE_INT:
                printf("INT\t%d\t\t", c->value.intVal);
                break;
            case TYPE_FLOAT:
                printf("FLOAT\t%f\t", c->value.floatVal);
                break;
            case TYPE_STRING:
                printf("STRING\t\"%s\"\t", c->value.stringVal);
                break;
            default:
                printf("UNKNOWN\t???\t\t");
        }
        printf("%d\n", c->address);
    }

    printf("==========================\n");
}