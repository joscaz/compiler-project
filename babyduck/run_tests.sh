#!/bin/bash

# Contadores
passed=0
failed=0

for file in testcases/*.txt; do
  echo "🔵 Running $file"
  ./babyduck < "$file"
  if [ $? -ne 0 ]; then
    echo "❌ Error in $file"
    ((failed++))
  else
    echo "✅ Passed $file"
    ((passed++))
  fi
done

echo ""
echo "==== Test Summary ===="
echo "✅ Passed: $passed"
echo "❌ Failed: $failed"
