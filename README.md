# BabyDuck bitácora

## Como correr? (MacOS)
`$ bison -d parser.y`

`$ flex scanner.l`

`$ gcc parser.tab.c lex.yy.c -o babyduck -ly`

## Después de tarea de Tarea 1 (3 de abril)
Decidí optar por el hacerlo C en vez de Haskell debido a la complejidad del lenguaje y teniendo en cuenta el tiempo que se tiene.

## Lunes 28 abril
- Corregí un pequeño error recursivo en mi gramática, específicamente en <DEC_FUN>. Este error lo pude cachar al estar haciendo la entrega 1.
- Corregí gramática de <FUNCS> tenía mal definidos los símbolos de '[]'
- No agregué los símbolos '[]' como token, ya los agregué

## Martes 29 de Abril
- Se agregaron testcases para verificar correcto funcionamiento del lenguaje
- Se corrigió un error en la gramática el cual no dejaba añadir múltiples variables
- Se creó un archivo .sh para automatizar la ejecución de los testcases
- Se entregó BabyDuck - entrega #1 (Léxico y Sintaxis) en Canvas

## Lunes 5 de mayo
- Entrega 2 Semántica de Variables
- Se agregaron puntos neurálgicos del lenguaje
- Me di cuenta que como las herramientas que estoy utilizando permiten meter código en la gramática, no necesito necesariamente un árbol AST para el parseo
- Referencias: https://stackoverflow.com/questions/79084686/error-unknown-type-name-astnode-in-bison-parser-when-integrating-with-flex-le
- Se creó el archivo make para definir las tareas a ejecutar para crear el binario ejecutable del compilador

## Miércoles 14 de mayo
- Entrega #3 (Código de Expresiones y Estatutos lineales)
- Se creó la memoria virtual
- Se crearon los cuádruplos, junto con su fila
- Se añadió el tipo de dato string

## Miércoles 21 mayo
- Entrega #4 (Código de Estatutos y uso de Dir Virtuales)
- Generación de cuádruplos para estatutos cíclicos y condicionales
- Memoria virtual funciona correctamente
- Pequeños cambios en puntos neurálgicos dentro de la gramática (archivo parser.y)