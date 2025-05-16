#include "virtual_memory.h"
#include <stdio.h>

// init memory counters to start of each segment
void initMemoryCounters(MemoryCounters *counters) {
    counters->globalInt = GLOBAL_INT_START;
    counters->globalFloat = GLOBAL_FLOAT_START;
    counters->localInt = LOCAL_INT_START;
    counters->localFloat = LOCAL_FLOAT_START;
    counters->tempInt = TEMP_INT_START;
    counters->tempFloat = TEMP_FLOAT_START;
    counters->tempBool = TEMP_BOOL_START;
    counters->constInt = CONST_INT_START;
    counters->constFloat = CONST_FLOAT_START;
    counters->constString = CONST_STRING_START;
}

// get next avail address for var based on scope and type
int getNextAddress(MemoryCounters *counters, DataType type, int isGlobal) {
    int address = -1;

    if (isGlobal) {
        if (type == TYPE_INT) {
            if (counters->globalInt <= GLOBAL_INT_END){
                address = counters->globalInt++;
            }
        } else if (type == TYPE_FLOAT) {
            if (counters->globalFloat <= GLOBAL_FLOAT_END) {
                address = counters->globalFloat++;
            }
        }
    } else {
        // local var
        if (type == TYPE_INT) {
            if (counters->localInt <= LOCAL_INT_END) {
                address = counters->localInt++;
            }
        } else if (type == TYPE_FLOAT) {
            if (counters->localFloat <= LOCAL_FLOAT_END) {
                address = counters->localFloat++;
            }
        }
    }

    if (address == -1) {
        fprintf(stderr, "Error: Memory overflow in var allocation\n");
    }

    return address;
}

// get next avail address for temp var
int getNextTempAddress(MemoryCounters *counters, DataType type) {
    int address = -1;

    if (type == TYPE_INT) {
        if (counters->tempInt <= TEMP_INT_END) {
            address = counters->tempInt++;
        }
    } else if (type == TYPE_FLOAT) {
        if (counters->tempFloat <= TEMP_FLOAT_END) {
            address = counters->tempFloat++;
        }
    } else if (counters->tempBool <= TEMP_BOOL_END) {
        address = counters->tempBool++;
    }

    if (address == -1) {
        fprintf(stderr, "Error: Memory overflow in temporary var allocation\n");
    }

    return address;
}

// get next avail address for CTE
int getNextConstAddress(MemoryCounters *counters, DataType type) {
    int address = -1;
    
    if (type == TYPE_INT) {
        if (counters->constInt <= CONST_INT_END) {
            address = counters->constInt++;
        }
    } else if (type == TYPE_FLOAT) {
        if (counters->constFloat <= CONST_FLOAT_END) {
            address = counters->constFloat++;
        }
    } else if (type == TYPE_STRING) {
        if (counters-> constString <= CONST_STRING_END) {
            address = counters->constString++;
        }
    }

    if (address == -1) {
        fprintf(stderr, "Error: Memory overflow in constants var allocation\n");
    }

    return address;
}

// get type from address
DataType getTypeFromAddress(int address) {
    if ((address >= GLOBAL_INT_START && address <= GLOBAL_INT_END) ||
        (address >= LOCAL_INT_START && address <= LOCAL_INT_END) || 
        (address >= TEMP_INT_START && address <= TEMP_INT_END) ||
        (address >= CONST_INT_START && address <= CONST_INT_END)) {
        return TYPE_INT;
    } else if ((address >= GLOBAL_FLOAT_START && address <= GLOBAL_FLOAT_END) ||
        (address >= LOCAL_FLOAT_START && address <= LOCAL_FLOAT_END) || 
        (address >= TEMP_FLOAT_START && address <= TEMP_FLOAT_END) ||
        (address >= CONST_FLOAT_START && address <= CONST_FLOAT_END)) {
        return TYPE_FLOAT;
    } else if (address >= TEMP_BOOL_START && address <= TEMP_BOOL_END) {
        return TYPE_BOOL;
    } else if (address >= CONST_STRING_START && address <= CONST_STRING_END) {
        return TYPE_STRING;
    }
    return TYPE_ERROR;
}

// check scope of address
int isGlobalAddress(int address) {
    return (address >= GLOBAL_INT_START && address <= GLOBAL_FLOAT_END);
}

int isLocalAddress(int address) {
    return (address >= LOCAL_INT_START && address <= LOCAL_FLOAT_END);
}

int isTempAddress(int address) {
    return (address >= TEMP_INT_START && address <= TEMP_BOOL_END);
}

int isConstAddress(int address) {
    return (address >= CONST_INT_START && address <= CONST_STRING_END);
}