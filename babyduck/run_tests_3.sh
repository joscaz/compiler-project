#!/bin/bash

# Colores para la salida
GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Compilar el proyecto
echo -e "${BLUE}Compilando el proyecto...${NC}"
make clean && make
if [ $? -ne 0 ]; then
    echo -e "${RED}Error al compilar el proyecto.${NC}"
    exit 1
fi
echo -e "${GREEN}Compilación exitosa.${NC}\n"

# Función para ejecutar un test
run_test() {
    local test_file=$1
    local test_name=$(basename $test_file .txt)
    
    echo -e "${BLUE}Ejecutando prueba: ${test_name}${NC}"
    echo -e "${BLUE}------------------------${NC}"
    
    ./babyduck < $test_file
    
    if [ $? -eq 0 ]; then
        echo -e "${GREEN}Prueba exitosa: ${test_name}${NC}\n"
    else
        echo -e "${RED}Prueba fallida: ${test_name}${NC}\n"
    fi
}

# Ejecutar las pruebas de la entrega 3
echo -e "${BLUE}=== Pruebas de la Entrega 3 ===${NC}\n"

# Test de expresiones aritméticas y relacionales
run_test "testcases/entrega3/test_exp.txt"

# Test de asignaciones
run_test "testcases/entrega3/test_assignment.txt"

# Test de estatuto print
run_test "testcases/entrega3/test_print.txt"

echo -e "${BLUE}=== Fin de las pruebas ===${NC}"