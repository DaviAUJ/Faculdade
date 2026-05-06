# função de potencia

Main:	
	# Teste
	li $t0, 69

	# Lendo a base
	li $v0, 5
	syscall
	move $a0, $v0
	
	# Lendo o expoente
	li $v0, 5
	syscall
	move $a1, $v0
	
	# Executando pow
	jal Pow
	
	# Imprimindo resultado e saindo
	move $a0, $v0
	li $v0, 1
	syscall
	
	li $v0, 10
	syscall
	
Pow:
	# Salvando na memoria os registradores que serão usados
	addi $sp, $sp, -4
	sw $t0, 0($sp)

	# contador
	li $t0, 0
	
	# Iniciando saída
	li $v0, 1
	
# for(int $t0 = 0; $t0 !=
Loop:	
	beq $t0, $a1, Exit
	mul $v0, $v0, $a0
	addi $t0, $t0, 1
	j Loop
	
Exit:
	lw $t0, 0($sp)
	addi $sp, $sp, 4
	jr $ra
