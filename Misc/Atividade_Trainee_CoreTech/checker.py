import sys
from pathlib import Path

argc = len(sys.argv)

if argc > 3:
    raise Exception("Argumentos de mais")

if argc < 3:
    raise Exception("Argumentos de menos")

out_paths = (
    Path(sys.argv[1]), 
    Path(sys.argv[2])
)

if not out_paths[0].is_file():
    raise Exception("Primeiro arquivo não existe")

if not out_paths[1].is_file():
    raise Exception("Segundo arquivo não existe")

out_lines = (
    open(out_paths[0], "r").readlines(),
    open(out_paths[1], "r").readlines()
)

if len(out_lines[0]) != len(out_lines[1]):
    raise Exception("Arquivos com quantidades de linhas diferentes")

total     = len(out_lines[0])
successes = 0

for pair in zip(out_lines[0], out_lines[1]):
    if pair[0] == pair[1]:
        successes += 1

print(f"{successes / total * 100}%", end='')