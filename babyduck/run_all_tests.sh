#!/bin/bash

# Colores para output visual
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color
BOLD='\033[1m'

# Banner
echo -e "${PURPLE}${BOLD}"
echo "╔══════════════════════════════════════════════════════════════════════╗"
echo "║                      🚀 BABYDUCK COMPILER TESTS 🚀                  ║"
echo "║                         Test Suite Runner                           ║"
echo "╚══════════════════════════════════════════════════════════════════════╝"
echo -e "${NC}"

# Verificar que el compilador existe
if [ ! -f "./babyduck" ]; then
    echo -e "${RED}❌ Error: Compilador 'babyduck' no encontrado. Ejecuta 'make' primero.${NC}"
    exit 1
fi

# Contadores
TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Función para ejecutar un test
run_test() {
    local test_file=$1
    local test_name=$(basename "$test_file" .txt)
    
    echo -e "${CYAN}${BOLD}📋 Test: ${test_name}${NC}"
    echo -e "${YELLOW}📁 Archivo: $test_file${NC}"
    
    # Mostrar contenido del test (primeras 5 líneas)
    echo -e "${BLUE}📄 Contenido:${NC}"
    head -5 "$test_file" | sed 's/^/   /'
    if [ $(wc -l < "$test_file") -gt 5 ]; then
        echo "   ..."
    fi
    
    echo -e "${GREEN}🏃 Ejecutando...${NC}"
    echo "----------------------------------------"
    
    # Ejecutar el test en modo silencioso
    if ./babyduck -q < "$test_file" 2>/dev/null; then
        echo "----------------------------------------"
        echo -e "${GREEN}✅ ÉXITO${NC}"
        ((PASSED_TESTS++))
    else
        echo "----------------------------------------"
        echo -e "${RED}❌ ERROR${NC}"
        ((FAILED_TESTS++))
    fi
    
    ((TOTAL_TESTS++))
    echo ""
}

# Función para mostrar estadísticas
show_stats() {
    echo -e "${PURPLE}${BOLD}"
    echo "╔══════════════════════════════════════════════════════════════════════╗"
    echo "║                           📊 ESTADÍSTICAS                           ║"
    echo "╚══════════════════════════════════════════════════════════════════════╝"
    echo -e "${NC}"
    
    echo -e "${BLUE}📈 Total de tests: ${BOLD}$TOTAL_TESTS${NC}"
    echo -e "${GREEN}✅ Tests exitosos: ${BOLD}$PASSED_TESTS${NC}"
    echo -e "${RED}❌ Tests fallidos: ${BOLD}$FAILED_TESTS${NC}"
    
    if [ $FAILED_TESTS -eq 0 ]; then
        echo -e "${GREEN}${BOLD}🎉 ¡TODOS LOS TESTS PASARON! 🎉${NC}"
    else
        echo -e "${YELLOW}⚠️  Algunos tests fallaron. Revisa los errores arriba.${NC}"
    fi
    
    echo ""
}

# Categorías de tests
echo -e "${YELLOW}${BOLD}🔍 Ejecutando tests por categorías...${NC}"
echo ""

# Tests básicos
echo -e "${PURPLE}${BOLD}═══ TESTS BÁSICOS ═══${NC}"
for test_file in testcases/test_basic.txt testcases/test_simple.txt testcases/test_vars*.txt; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

# Tests de variables y asignaciones
echo -e "${PURPLE}${BOLD}═══ TESTS DE VARIABLES Y ASIGNACIONES ═══${NC}"
for test_file in testcases/test_assign.txt testcases/testcase.txt; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

# Tests de control de flujo
echo -e "${PURPLE}${BOLD}═══ TESTS DE CONTROL DE FLUJO ═══${NC}"
for test_file in testcases/test_if.txt testcases/test_cycle.txt testcases/test_while*.txt testcases/test_control*.txt testcases/test_simple_control.txt; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

# Tests de funciones
echo -e "${PURPLE}${BOLD}═══ TESTS DE FUNCIONES ═══${NC}"
for test_file in testcases/test_func*.txt testcases/test_f_call.txt testcases/test_functions.txt testcases/test_factorial.txt testcases/test_fibonacci*.txt; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

# Tests de impresión y comentarios
echo -e "${PURPLE}${BOLD}═══ TESTS DIVERSOS ═══${NC}"
for test_file in testcases/test_print.txt testcases/test_comments.txt; do
    if [ -f "$test_file" ]; then
        run_test "$test_file"
    fi
done

# Mostrar estadísticas finales
show_stats

# Mensaje final
echo -e "${CYAN}${BOLD}💡 Tip: Para ver output con debug, usa './babyduck < archivo.txt'${NC}"
echo -e "${CYAN}${BOLD}💡 Para modo silencioso, usa './babyduck -q < archivo.txt'${NC}"
echo ""
echo -e "${PURPLE}${BOLD}¡Gracias por usar BabyDuck Compiler! 🦆${NC}" 