#!/bin/bash

# Script rápido para ejecutar tests específicos del compilador BabyDuck

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m'
BOLD='\033[1m'

echo -e "${BLUE}${BOLD}ß BabyDuck Quick Test Runner${NC}"
echo "=================================="

if [ $# -eq 0 ]; then
    echo "Uso: $0 [test_file.txt] o [categoria]"
    echo ""
    echo "Categorías disponibles:"
    echo "  basic     - Tests básicos"
    echo "  vars      - Tests de variables"
    echo "  control   - Tests de control de flujo"
    echo "  functions - Tests de funciones"
    echo "  all       - Todos los tests (usa run_all_tests.sh)"
    echo ""
    echo "Ejemplo: $0 testcases/test_functions.txt"
    echo "Ejemplo: $0 functions"
    exit 1
fi

# Función para ejecutar un test simple
run_single_test() {
    local test_file=$1
    echo -e "${BLUE}📋 Ejecutando: $(basename "$test_file")${NC}"
    echo "----------------------------------------"
    
    if ./babyduck -q < "$test_file"; then
        echo "----------------------------------------"
        echo -e "${GREEN}ÉXITO${NC}"
        return 0
    else
        echo "----------------------------------------"
        echo -e "${RED}ERROR${NC}"
        return 1
    fi
}

# Si es un archivo específico
if [ -f "$1" ]; then
    run_single_test "$1"
    exit $?
fi

# Si es una categoría
case "$1" in
    "basic")
        echo "Ejecutando tests básicos..."
        for file in testcases/test_basic.txt testcases/test_simple.txt testcases/test_vars_*.txt; do
            [ -f "$file" ] && run_single_test "$file"
        done
        ;;
    "vars")
        echo "Ejecutando tests de variables..."
        for file in testcases/test_assign.txt testcases/test_vars*.txt testcases/testcase.txt; do
            [ -f "$file" ] && run_single_test "$file"
        done
        ;;
    "control")
        echo "Ejecutando tests de control de flujo..."
        for file in testcases/test_if.txt testcases/test_cycle.txt testcases/test_while*.txt testcases/test_control*.txt; do
            [ -f "$file" ] && run_single_test "$file"
        done
        ;;
    "functions")
        echo "Ejecutando tests de funciones..."
        for file in testcases/test_func*.txt testcases/test_f*.txt testcases/test_functions.txt testcases/test_factorial.txt testcases/test_fibonacci*.txt; do
            [ -f "$file" ] && run_single_test "$file"
        done
        ;;
    "all")
        echo "Ejecutando TODOS los tests..."
        ./run_all_tests.sh
        ;;
    *)
        echo -e "${RED}Categoría '$1' no reconocida${NC}"
        echo "Usa: basic, vars, control, functions, o all"
        exit 1
        ;;
esac 