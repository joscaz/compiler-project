#!/bin/bash

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Contadores
passed=0
semantic_errors=0
syntax_errors=0
total=0

for file in testcases/*.txt; do
  echo -e "${BLUE}🔵 Testing ${file}${NC}"
  ((total++))
  
  # Ejecutar babyduck y capturar salida y código de retorno
  output=$(./babyduck < "$file" 2>&1)
  exit_code=$?
  
  # Mostrar la salida completa para diagnóstico
  echo "$output"
  
  # Buscar errores semánticos específicos en la salida
  if echo "$output" | grep -q "Error Semantic\|Error Sematinc\|Semantic error\|Sematinc error"; then
    echo -e "${YELLOW}⚠️ Semantic Error in $file${NC}"
    ((semantic_errors++))
  elif [ $exit_code -ne 0 ]; then
    echo -e "${RED}❌ Syntax Error in $file${NC}"
    ((syntax_errors++))
  else
    echo -e "${GREEN}✅ Passed $file${NC}"
    ((passed++))
  fi
  
  echo "-------------------------------------"
done

echo ""
echo "==== Test Summary ===="
echo -e "${GREEN}✅ Passed: $passed${NC}"
echo -e "${YELLOW}⚠️ Semantic Errors: $semantic_errors${NC}"
echo -e "${RED}❌ Syntax Errors: $syntax_errors${NC}"
echo "Total tests: $total"

# Verificar si hay errores sintácticos, que son los que deberían fallar el script
if [ $syntax_errors -gt 0 ]; then
  exit 1
fi

# Los errores semánticos son esperados en algunos casos de prueba
exit 0