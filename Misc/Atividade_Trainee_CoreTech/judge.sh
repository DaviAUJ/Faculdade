#!/bin/bash

DIRECTORY="$1"
BINPOW_INPUT="input"
BINPOW_EXPOUT="expected_output"
BINPOW_REALOUT="real_output"
RESULTS_FILE="results"

if [[ ! -d "$DIRECTORY" ]]; then
    echo "$DIRECTORY não existe"
    exit 1
fi

printf "" > $RESULTS_FILE

python3 pow_generator.py

for FILE in "$DIRECTORY"/*; do 
    gcc "$FILE"
    ./a.out "$BINPOW_INPUT" "$BINPOW_REALOUT"
    printf "$(basename ${FILE%.*}): " >> "$RESULTS_FILE"
    python3 checker.py "$BINPOW_REALOUT" "$BINPOW_EXPOUT" >> "$RESULTS_FILE"
    printf "\n" >> "$RESULTS_FILE"
done

# Comente essa linha abaixo para manter todas as saídas
rm ./a.out "$BINPOW_INPUT" "$BINPOW_REALOUT" "$BINPOW_EXPOUT"