#ifndef DATATYPE_H
#define DATATYPE_H

// Definition for Babyduck types
typedef enum {
    TYPE_ERROR = -1, // for invalid operations
    TYPE_INT = 0,
    TYPE_FLOAT = 1,
    TYPE_BOOL = 2,
    TYPE_STRING = 3
} DataType;

#endif // DATATYPE_H