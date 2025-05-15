#ifndef VIRTUAL_MEMORY_H
#define VIRTUAL_MEMORY_H

#include "datatype.h"

// memory segment range
// global vars 1000 - 2999
#define GLOBAL_INT_START 1000
#define GLOBAL_INT_END 1999
#define GLOBAL_FLOAT_START 2000
#define GLOBAL_FLOAT_END 2999

// local vars 3000 - 4999
#define LOCAL_INT_START 3000
#define LOCAL_INT_END 3999
#define LOCAL_FLOAT_START 4000
#define LOCAL_FLOAT_END 4999

// temp vars 5000 - 7999
#define TEMP_INT_START 5000
#define TEMP_INT_END 5999
#define TEMP_FLOAT_START 6000
#define TEMP_FLOAT_END 6999
#define TEMP_BOOL_START 7000
#define TEMP_BOOL_END 7999

// CTEs 8000 - 10999
#define CONST_INT_START 8000
#define CONST_INT_END 8999
#define CONST_FLOAT_START 9000
#define CONST_FLOAT_END 9999
#define CONST_STRING_START 10000
#define CONST_STRING_END 10999

// memory counters to keep track of next available address in each segment
typedef struct {
    int globalInt;
    int globalFloat;
    int localInt;
    int localFloat;
    int tempInt;
    int tempFloat;
    int tempBool;
    int constInt;
    int constFloat;
    int constString;
} MemoryCounters;

// init memory counters for init values
void initMemoryCounters(MemoryCounters *counters);

// get next avail address for var based on scope and type
int getNextAddress(MemoryCounters *counters, DataType type, int isGlobal);

// get next avail address for temp var
int getNextTempAddress(MemoryCounters *counters, DataType type);

// get next avail address for CTE
int getNextConstAddress(MemoryCounters *counters, DataType type);

// get type from address
DataType getTypeFromAddress(int address);

// check scope of address
int isGlobalAddress(int address);
int isLocalAddress(int address);
int isTempAddress(int address);
int isConstAddress(int address);

#endif // VIRTUAL_MEMORY_H