#!/bin/bash

echo "🔧 Compiling all task executables..."

# List of task sources (must match names in your initTasks[])
TASKS=(
  Calculator
  tictactoe
  binarysearch
  banking
  guessgame
  messagebox
  createfile
  deletefile
  Calender
  time
  factorial
  stopwatch
  stringlength
  primecheck
  hangman
)

for task in "${TASKS[@]}"
do
  if [ -f "$task.c" ]; then
    gcc "$task.c" -o "$task" && echo "✅ Compiled: $task"
  else
    echo "⚠️  Missing source: $task.c (skipped)"
  fi
done

echo "🛠️ Compiling OS simulator (main.c)..."
if gcc main.c -o os -lpthread; then
  echo "✅ OS simulator compiled as ./os"
else
  echo "❌ Failed to compile OS simulator"
fi


echo "✅ Build process complete."
