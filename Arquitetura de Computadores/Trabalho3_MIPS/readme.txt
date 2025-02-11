Terceiro trabalho da materia de Arquitetura de Computadores
Aluno: Davi Araújo do Nascimento
Turma 03

Olá professor Calebe! Para simular o meu processador basta executar o makefile.

Eu fiz a implementação do jump, como pediu, e também mandei junto um arquivo com um programa 
que usa todas as instruções suportadas, R-Type, beq, jump, lw, sw e addi. Ele está armazenados
no arquivo codigo.mem

O arquivo .v principal é MIPSCicloUnico.v.

Esse programa cálcula a expressão a * b - c, sendo estes números armazenados, respectivamente,
nos registradores $s0, $s1, $s2. Você pode alterar os valores que são adicionados nesses
registradores nas três primeiras linhas do programa nas instruções de addi, com a restrição
que a $s0 não pode receber um número negativo, senão, pelo jeito que fiz, o programa vai rodar 
para sempre e não vai calcular nada.

Eu usei um método lá no testbench para poder ver os registradores no GTKWave, então você pode
analisar os 32 por lá, fica na abinha testbench lá naquela hierarquia do lado esquerdo.
Além disso se quiser aumentar o tempo de simulação basta mudar o #1000 que tem antes
do $finish.

Aqui vai código traduzido para assembly.

addi $s0, $zero, 20
addi $s1, $zero, 18
addi $s2, $zero, 56

beq $t0, $s0, 3
add $t1, $t1, $s1
addi $t0, $t0, 1
j 3; 

sw $t1, 1($zero) 
lw $s3, 1($zero) // Eu só jogo para a memória e depois pego para mostrar que as instruções funcionam

sub $s3, $s3, $s2
