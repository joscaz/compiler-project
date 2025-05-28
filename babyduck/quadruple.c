#include "quadruple.h"
#include <stdio.h>
#include <string.h>
#include "virtual_memory.h"

// init quadruple queue
void initQuadQueue(QuadQueue *queue) {
    queue->count = 0;
}

// add quadruple to queue
int addQuadruple(QuadQueue *queue, QuadOperator op, int op1, int op2, int res) {
    if (queue->count >= MAX_QUADRUPLES) {
        fprintf(stderr, "Error: Max number of quadruples exceeded\n");
        return -1;
    }
    queue->quads[queue->count].operador = op;
    queue->quads[queue->count].operand1 = op1;
    queue->quads[queue->count].operand2 = op2;
    queue->quads[queue->count].res = res;

    return queue->count++;
}

// get quadruple at specific idx
Quadruple* getQuadruple(QuadQueue *queue, int idx, int res) {
    if (idx < 0 || idx >= queue->count) {
        return NULL;
    }

    return &(queue->quads[idx]);
}

// this function will be useful to return to a specific
// quadruple and update the res, for example, when we have a GOTOF or GOTOV
void updateQuadrupleResult(QuadQueue *queue, int idx, int res) {
    if (idx > 0 && idx < queue->count) {
        queue->quads[idx].res = res;
    }
}

char* formatAddress(int address, char *buffer) {
    if (address == -1) {
        strcpy(buffer, "NULL");
    } else {
        DataType type = getTypeFromAddress(address);
        const char *typeStr = "UNK";

        if (type == TYPE_INT) typeStr = "INT";
        else if (type == TYPE_FLOAT) typeStr = "FLOAT";
        else if (type == TYPE_BOOL) typeStr = "BOOL";
        else if (type == TYPE_STRING) typeStr = "STR";

        if (isGlobalAddress(address)) {
            sprintf(buffer, "G_%s[%d]", typeStr, address);
        } else if (isLocalAddress(address)) {
            sprintf(buffer, "L_%s[%d]", typeStr, address);
        } else if (isTempAddress(address)) {
            sprintf(buffer, "T_%s[%d]", typeStr, address);
        } else if (isConstAddress(address)) {
            sprintf(buffer, "C_%s[%d]", typeStr, address);
        } else {
            sprintf(buffer, "%d", address); // para los saltos
        }
    }

    return buffer;
}

// custom print of quadruples
void printQuadruples(QuadQueue *queue) {
    printf("\n===== QUADRUPLES =====\n");
    printf("No.\tOperator\tOperand1\tOperand2\tResult\n");
    printf("---------------------------------------------------------\n");

    char buffer1[20], buffer2[20], buffer3[20];

    for (int i = 0; i < queue->count; i++) {
        Quadruple *q = &(queue->quads[i]);

        printf("%d\t%s\t\t%s\t%s\t%s\n", 
                i,
                operatorToString(q->operador),
                formatAddress(q->operand1, buffer1),
                formatAddress(q->operand2, buffer2),
                formatAddress(q->res, buffer3));
    }

    printf("==================\n");
}

// convert operator to string for display
const char* operatorToString(QuadOperator op) {
    switch (op) {
        case OP_PLUS:    return "+";
        case OP_MINUS:   return "-";
        case OP_MULT:    return "*";
        case OP_DIV:     return "/";
        case OP_LT:      return "<";
        case OP_GT:      return ">";
        case OP_NEQ:     return "!=";
        case OP_ASSIGN:  return "=";
        case OP_GOTO:    return "GOTO";
        case OP_GOTOF:   return "GOTOF";
        case OP_GOTOV:   return "GOTOV";
        case OP_PRINT:   return "PRINT";
        case OP_ERA:     return "ERA";
        case OP_PARAM:   return "PARAM";
        case OP_GOSUB:   return "GOSUB";
        case OP_RETURN:  return "RETURN";
        case OP_ENDPROC: return "ENDPROC";
        case OP_EOF:    return "EOF";
        default:         return "UNKNOWN";
    }
}