#include "virtual_machine.h"
#include <string.h>

// Inicializa la máquina virtual
void initVirtualMachine(VirtualMachine *vm, QuadQueue *quads, ConstantTable *constants) {
    vm->quadruples = quads;
    vm->constants = constants;
    vm->instructionPointer = 0;
    vm->running = 1;
    
    // Inicializar memoria
    memset(vm->memory.memory, 0, sizeof(vm->memory.memory));
    vm->memory.stackPointer = 0;
    vm->memory.basePointer = 0;
    
    // Inicializar pila de llamadas
    vm->callStack.top = -1;
    
    // Cargar constantes en memoria
    for (int i = 0; i < vm->constants->count; i++) {
        Constant *constant = &vm->constants->constants[i];
        int memIndex = getMemoryIndex(constant->address);
        
        if (constant->type == TYPE_INT) {
            vm->memory.memory[memIndex] = constant->value.intVal;
        } else if (constant->type == TYPE_FLOAT) {
            // Para floats, convertimos a int para simplificar (en una implementación real usaríamos union)
            vm->memory.memory[memIndex] = (int)(constant->value.floatVal * 1000); // escalamos por 1000
        }
        // Para strings, almacenamos el índice en la tabla de constantes
        else if (constant->type == TYPE_STRING) {
            vm->memory.memory[memIndex] = i; // índice en la tabla de constantes
        }
    }
}

// Convierte dirección virtual a índice de memoria física
int getMemoryIndex(int virtualAddress) {
    // Simplemente usamos la dirección virtual como índice
    // En una implementación más sofisticada, haríamos mapeo de memoria
    return virtualAddress;
}

// Obtiene valor de memoria
int getValue(VirtualMachine *vm, int address) {
    if (address == -1) return -1; // valor no válido
    
    int memIndex = getMemoryIndex(address);
    if (memIndex < 0 || memIndex >= MEMORY_SIZE) {
        fprintf(stderr, "Error: Invalid memory address %d\n", address);
        return 0;
    }
    
    return vm->memory.memory[memIndex];
}

// Establece valor en memoria
void setValue(VirtualMachine *vm, int address, int value) {
    if (address == -1) return; // dirección no válida
    
    int memIndex = getMemoryIndex(address);
    if (memIndex < 0 || memIndex >= MEMORY_SIZE) {
        fprintf(stderr, "Error: Invalid memory address %d\n", address);
        return;
    }
    
    vm->memory.memory[memIndex] = value;
}

// Ejecuta el programa completo
void executeProgram(VirtualMachine *vm) {
    printf("=== INICIANDO EJECUCIÓN DE LA MÁQUINA VIRTUAL ===\n");
    
    while (vm->running && vm->instructionPointer < vm->quadruples->count) {
        Quadruple *currentQuad = &vm->quadruples->quads[vm->instructionPointer];
        
        printf("Ejecutando cuádruplo %d: %s\n", vm->instructionPointer, 
               operatorToString(currentQuad->operador));
        
        executeQuadruple(vm, currentQuad);
        
        // Avanzar al siguiente cuádruplo (a menos que sea un salto)
        if (currentQuad->operador != OP_GOTO && 
            currentQuad->operador != OP_GOTOF && 
            currentQuad->operador != OP_GOSUB) {
            vm->instructionPointer++;
        }
    }
    
    printf("=== EJECUCIÓN COMPLETADA ===\n");
}

// Ejecuta un cuádruplo específico
void executeQuadruple(VirtualMachine *vm, Quadruple *quad) {
    switch (quad->operador) {
        case OP_PLUS:
        case OP_MINUS:
        case OP_MULT:
        case OP_DIV:
            executeArithmetic(vm, quad);
            break;
            
        case OP_LT:
        case OP_GT:
        case OP_NEQ:
            executeRelational(vm, quad);
            break;
            
        case OP_ASSIGN:
            executeAssignment(vm, quad);
            break;
            
        case OP_GOTO:
            executeGoto(vm, quad);
            break;
            
        case OP_GOTOF:
            executeGotoF(vm, quad);
            break;
            
        case OP_GOTOV:
            executeGotoV(vm, quad);
            break;
            
        case OP_PRINT:
            executePrint(vm, quad);
            break;
            
        case OP_ERA:
            executeERA(vm, quad);
            break;
            
        case OP_PARAM:
            executeParam(vm, quad);
            break;
            
        case OP_GOSUB:
            executeGosub(vm, quad);
            break;
            
        case OP_RETURN:
            executeReturn(vm, quad);
            break;
            
        case OP_ENDPROC:
            executeEndProc(vm, quad);
            break;
            
        case OP_EOF:
            executeEOF(vm, quad);
            break;
            
        default:
            fprintf(stderr, "Error: Operador no implementado: %s\n", 
                    operatorToString(quad->operador));
            break;
    }
}

// Ejecuta operaciones aritméticas
void executeArithmetic(VirtualMachine *vm, Quadruple *quad) {
    int val1 = getValue(vm, quad->operand1);
    int val2 = getValue(vm, quad->operand2);
    int result = 0;
    
    // Determinar si estamos trabajando con floats basado en las direcciones
    int isFloat1 = (quad->operand1 >= 9000 && quad->operand1 < 10000) || 
                   (quad->operand1 >= 2000 && quad->operand1 < 3000);
    int isFloat2 = (quad->operand2 >= 9000 && quad->operand2 < 10000) || 
                   (quad->operand2 >= 2000 && quad->operand2 < 3000);
    
    if (isFloat1 || isFloat2) {
        // Operación con floats (escalados por 1000)
        switch (quad->operador) {
            case OP_PLUS:
                result = val1 + val2;
                break;
            case OP_MINUS:
                result = val1 - val2;
                break;
            case OP_MULT:
                result = (val1 * val2) / 1000; // ajustar escala
                break;
            case OP_DIV:
                if (val2 == 0) {
                    fprintf(stderr, "Error: División por cero\n");
                    vm->running = 0;
                    return;
                }
                result = (val1 * 1000) / val2; // ajustar escala
                break;
            default:
                break;
        }
    } else {
        // Operación con enteros
        switch (quad->operador) {
            case OP_PLUS:
                result = val1 + val2;
                break;
            case OP_MINUS:
                result = val1 - val2;
                break;
            case OP_MULT:
                result = val1 * val2;
                break;
            case OP_DIV:
                if (val2 == 0) {
                    fprintf(stderr, "Error: División por cero\n");
                    vm->running = 0;
                    return;
                }
                result = val1 / val2;
                break;
            default:
                break;
        }
    }
    
    setValue(vm, quad->res, result);
}

// Ejecuta operaciones relacionales
void executeRelational(VirtualMachine *vm, Quadruple *quad) {
    int val1 = getValue(vm, quad->operand1);
    int val2 = getValue(vm, quad->operand2);
    int result = 0;
    
    switch (quad->operador) {
        case OP_LT:
            result = (val1 < val2) ? 1 : 0;
            break;
        case OP_GT:
            result = (val1 > val2) ? 1 : 0;
            break;
        case OP_NEQ:
            result = (val1 != val2) ? 1 : 0;
            break;
        default:
            break;
    }
    
    setValue(vm, quad->res, result);
}

// Ejecuta asignación
void executeAssignment(VirtualMachine *vm, Quadruple *quad) {
    int value = getValue(vm, quad->operand1);
    setValue(vm, quad->res, value);
}

// Ejecuta salto incondicional
void executeGoto(VirtualMachine *vm, Quadruple *quad) {
    vm->instructionPointer = quad->res;
}

// Ejecuta salto condicional (si falso)
void executeGotoF(VirtualMachine *vm, Quadruple *quad) {
    int condition = getValue(vm, quad->operand1);
    
    if (condition == 0) { // si es falso
        vm->instructionPointer = quad->res;
    } else {
        vm->instructionPointer++; // continúa con la siguiente instrucción
    }
}

// Ejecuta salto condicional (si verdadero)
void executeGotoV(VirtualMachine *vm, Quadruple *quad) {
    int condition = getValue(vm, quad->operand1);
    
    if (condition != 0) { // si es verdadero
        vm->instructionPointer = quad->res;
    } else {
        vm->instructionPointer++; // continúa con la siguiente instrucción
    }
}

// Ejecuta impresión
void executePrint(VirtualMachine *vm, Quadruple *quad) {
    int address = quad->operand1;
    int value = getValue(vm, address);
    
    // Determinar el tipo basado en la dirección virtual
    if (address >= 8000 && address < 9000) {
        // Constante entera
        printf("%d\n", value);
    } else if (address >= 9000 && address < 10000) {
        // Constante flotante (escalada por 1000)
        printf("%.3f\n", value / 1000.0);
    } else if (address >= 10000 && address < 11000) {
        // Constante string
        if (value >= 0 && value < vm->constants->count) {
            printf("%s\n", vm->constants->constants[value].value.stringVal);
        }
    } else if (address >= 1000 && address < 2000) {
        // Variable global entera
        printf("%d\n", value);
    } else if (address >= 2000 && address < 3000) {
        // Variable global flotante (escalada por 1000)
        printf("%.3f\n", value / 1000.0);
    } else if (address >= 3000 && address < 5000) {
        // Variable local (entero por defecto, pero podría ser float)
        printf("%d\n", value);
    } else if (address >= 5000 && address < 8000) {
        // Variable temporal
        printf("%d\n", value);
    } else {
        // Tipo desconocido
        printf("%d\n", value);
    }
}

void executeERA(VirtualMachine *vm, Quadruple *quad) {
    // Reservar espacio en la pila para la nueva función
    // En esta implementación simplificada, solo incrementamos el stack pointer
    vm->memory.stackPointer += 100; // espacio fijo por función
    
    printf("ERA: Reservando espacio para función\n");
}

void executeParam(VirtualMachine *vm, Quadruple *quad) {
    int paramValue = getValue(vm, quad->operand1);
    int paramIndex = quad->operand2;
    
    // DEBUG: Agregar información de debugging
    printf("DEBUG PARAM: dirección %d, valor obtenido = %d\n", quad->operand1, paramValue);
    
    // Copiar el parámetro al espacio de parámetros de la función
    // Los parámetros empiezan en la dirección 3000 (L_INT base)
    int paramAddress = 3000 + paramIndex;
    setValue(vm, paramAddress, paramValue);
    
    printf("PARAM %d: valor = %d -> dirección %d\n", paramIndex, paramValue, paramAddress);
}

void executeGosub(VirtualMachine *vm, Quadruple *quad) {
    // Guardar contexto actual en la pila de llamadas
    vm->callStack.top++;
    vm->callStack.returnAddress[vm->callStack.top] = vm->instructionPointer + 1;
    vm->callStack.basePointers[vm->callStack.top] = vm->memory.basePointer;
    
    // Saltar a la función
    vm->instructionPointer = quad->operand1;
    
    printf("GOSUB: Saltando a función en cuádruplo %d\n", quad->operand1);
}

void executeReturn(VirtualMachine *vm, Quadruple *quad) {
    // Esta operación no se usa en BabyDuck ya que no hay valores de retorno
    printf("RETURN: Función sin valor de retorno\n");
}

void executeEndProc(VirtualMachine *vm, Quadruple *quad) {
    if (vm->callStack.top >= 0) {
        // Restaurar contexto
        vm->instructionPointer = vm->callStack.returnAddress[vm->callStack.top];
        vm->memory.basePointer = vm->callStack.basePointers[vm->callStack.top];
        vm->callStack.top--;
        
        printf("ENDPROC: Retornando a cuádruplo %d\n", vm->instructionPointer);
        // No incrementar IP aquí, ya se estableció la dirección de retorno
        return;
    } else {
        // Si no hay llamadas en la pila, solo continuar (no terminar el programa)
        printf("ENDPROC: Fin de función sin llamada activa\n");
        vm->instructionPointer++;
    }
}

void executeEOF(VirtualMachine *vm, Quadruple *quad) {
    printf("EOF: Terminando ejecución del programa\n");
    vm->running = 0;
}

// Funciones de debug
void printMemoryState(VirtualMachine *vm) {
    printf("=== ESTADO DE LA MEMORIA ===\n");
    printf("Stack Pointer: %d\n", vm->memory.stackPointer);
    printf("Base Pointer: %d\n", vm->memory.basePointer);
    printf("Instruction Pointer: %d\n", vm->instructionPointer);
    
    printf("Memoria (primeras 20 posiciones con valores):\n");
    int count = 0;
    for (int i = 0; i < MEMORY_SIZE && count < 20; i++) {
        if (vm->memory.memory[i] != 0) {
            printf("  [%d] = %d\n", i, vm->memory.memory[i]);
            count++;
        }
    }
}

void printCallStack(VirtualMachine *vm) {
    printf("=== PILA DE LLAMADAS ===\n");
    printf("Top: %d\n", vm->callStack.top);
    
    for (int i = 0; i <= vm->callStack.top; i++) {
        printf("  [%d] Return: %d, Base: %d\n", 
               i, vm->callStack.returnAddress[i], vm->callStack.basePointers[i]);
    }
} 