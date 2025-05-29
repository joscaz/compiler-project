#ifndef VIRTUAL_MACHINE_H
#define VIRTUAL_MACHINE_H

#include "quadruple.h"
#include "constant_table.h"
#include "semantic_structures.h"
#include <stdio.h>
#include <stdlib.h>

// Variable externa para controlar verbosidad
extern int verbose_mode;

// Tamaño de la memoria de ejecución
#define MEMORY_SIZE 15000

// Estructura para el mapa de memoria de ejecución
typedef struct {
    int memory[MEMORY_SIZE];  // Memoria unificada para todos los tipos
    int stackPointer;         // Puntero de pila para llamadas a funciones
    int basePointer;          // Puntero base para el contexto actual
} ExecutionMemory;

// Pila de llamadas para funciones
#define MAX_CALL_STACK 100
typedef struct {
    int returnAddress[MAX_CALL_STACK];  // Direcciones de retorno
    int basePointers[MAX_CALL_STACK];   // Punteros base de cada contexto
    int top;                            // Tope de la pila
} CallStack;

// Estructura principal de la máquina virtual
typedef struct {
    QuadQueue *quadruples;
    ConstantTable *constants;
    ExecutionMemory memory;
    CallStack callStack;
    int instructionPointer;
    int running;                  // Flag para controlar ejecución
} VirtualMachine;

// Funciones principales de la máquina virtual
void initVirtualMachine(VirtualMachine *vm, QuadQueue *quads, ConstantTable *constants);
void executeProgram(VirtualMachine *vm);
void executeQuadruple(VirtualMachine *vm, Quadruple *quad);

// Funciones auxiliares para manejo de memoria
int getValue(VirtualMachine *vm, int address);
void setValue(VirtualMachine *vm, int address, int value);
int getMemoryIndex(int virtualAddress);

// Funciones para operaciones específicas
void executeArithmetic(VirtualMachine *vm, Quadruple *quad);
void executeRelational(VirtualMachine *vm, Quadruple *quad);
void executeAssignment(VirtualMachine *vm, Quadruple *quad);
void executeGoto(VirtualMachine *vm, Quadruple *quad);
void executeGotoF(VirtualMachine *vm, Quadruple *quad);
void executeGotoV(VirtualMachine *vm, Quadruple *quad);
void executePrint(VirtualMachine *vm, Quadruple *quad);
void executeERA(VirtualMachine *vm, Quadruple *quad);
void executeParam(VirtualMachine *vm, Quadruple *quad);
void executeGosub(VirtualMachine *vm, Quadruple *quad);
void executeReturn(VirtualMachine *vm, Quadruple *quad);
void executeEndProc(VirtualMachine *vm, Quadruple *quad);
void executeEOF(VirtualMachine *vm, Quadruple *quad);

// Funciones de debug
void printMemoryState(VirtualMachine *vm);
void printCallStack(VirtualMachine *vm);

#endif // VIRTUAL_MACHINE_H 