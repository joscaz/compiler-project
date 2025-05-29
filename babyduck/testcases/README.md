# BabyDuck - Test Cases

Este folder contiene todos los casos de prueba para el compilador BabyDuck.

## Estructura de Tests

### Tests Básicos
- `test_basic.txt` - Programa mínimo válido
- `test_simple.txt` - Programa simple con variables y print
- `test_vars_int.txt` - Declaración de variables enteras
- `test_vars_float.txt` - Declaración de variables flotantes
- `test_vars_novars.txt` - Programa sin variables
- `test_vars_expanded.txt` - Variables múltiples

### Tests de Variables y Asignaciones
- `test_assign.txt` - Asignaciones básicas
- `testcase.txt` - Caso de prueba complejo con operaciones

### Tests de Control de Flujo
- `test_if.txt` - Estructuras condicionales if-else
- `test_cycle.txt` - Ciclos while básicos
- `test_while_complex.txt` - Ciclos while complejos
- `test_control_flow.txt` - Control de flujo avanzado
- `test_simple_control.txt` - Control de flujo simple

### Tests de Funciones
- `test_functions.txt` - **⭐ Test principal de funciones**
- `test_func_basic.txt` - Funciones básicas
- `test_func_multi.txt` - Múltiples funciones
- `test_func_with_vars.txt` - Funciones con variables locales
- `test_func_params.txt` - Funciones con parámetros
- `test_f_call.txt` - Llamadas a funciones
- `test_factorial.txt` - Cálculo de factorial
- `test_fibonacci.txt` - Fibonacci simple
- `test_fibonacci_functions.txt` - Fibonacci con funciones

### Tests Diversos
- `test_print.txt` - Instrucciones de impresión
- `test_comments.txt` - Manejo de comentarios

## Cómo Ejecutar los Tests

### Opción 1: Script Completo (Recomendado)
```bash
./run_all_tests.sh
```
- Ejecuta TODOS los tests con output colorido
- Muestra estadísticas completas
- Organizado por categorías
- Perfecto para verificación completa

### Opción 2: Script Rápido
```bash
# Ejecutar por categorías
./quick_test.sh basic      # Tests básicos
./quick_test.sh vars       # Tests de variables
./quick_test.sh control    # Tests de control de flujo
./quick_test.sh functions  # Tests de funciones

# Ejecutar test específico
./quick_test.sh testcases/test_functions.txt

# Ejecutar todos
./quick_test.sh all
```

### Opción 3: Manual
```bash
# Modo verbose (con debug)
./babyduck < testcases/test_functions.txt

# Modo silencioso (solo output)
./babyduck -q < testcases/test_functions.txt
```

## Test más completo: test_functions.txt

Este es el test más completo que demuestra:
- ✅ Declaración de funciones (`suma`, `multiplicacion`)
- ✅ Parámetros de funciones
- ✅ Variables globales (`x`, `y`)
- ✅ Llamadas a funciones con diferentes argumentos
- ✅ Operaciones aritméticas (+, *)
- ✅ Impresión de strings y números
- ✅ Gestión de memoria virtual
- ✅ Pila de llamadas

**Output esperado:**
```
"Suma de 5 + 3:"
8
"Multiplicacion de 4 * 6:"
24
"Suma de 10 + 20:"
30
```

## Troubleshooting

Si un test falla:
1. Ejecuta en modo verbose: `./babyduck < archivo.txt`
2. Revisa los cuádruplos generados
3. Verifica la sintaxis del archivo de test
4. Asegúrate de que `make` compiló correctamente

## Estadísticas

Actualmente tenemos **18+ test cases** que cubren:
- Variables (globales y locales)
- Operaciones aritméticas
- Control de flujo (if-else, while)
- Funciones y parámetros
- Manejo de memoria
- Casos edge

Todos los tests pasan exitosamente.