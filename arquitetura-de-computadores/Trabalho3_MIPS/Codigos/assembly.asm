main0:
	# Variáveis : a * b - c
	addi $a0, $zero, -20 # a
	addi $a1, $zero, -18 # b
	addi $a2, $zero, 56 # c
	
	# Checando se variável a é negativo
	slt $t0, $a0, $t0
	
	# Se for vai para o bloco tratamento
	addi $t1, $zero, 1
	beq $t0, $t1, tratamento
	
	# Se não, continua
	j main1

# transforma a multiplicação numa equivalente que funciona na lógica que estou usando
tratamento:
	# complemento de 2
	nor $a0, $a0, $zero
	nor $a1, $a1, $zero
	addi $a0, $a0, 1
	addi $a1, $a1, 1
	
main1:
	# chama a função que calcula a expressão
	jal funcao
	
	#tira de $v0 e salva em $s0
	add $s0, $v0, $zero
	
	# Preciso fazer isso aqui para terminar já que no verilog não tem syscall
	j syscall10DasRuas

# $v0 = $a0 * $a1 - $a2
funcao:
	sw $t0, 0($sp)
	add $t0, $zero, $zero
	add $v0, $zero, $zero

# Faz a multiplicação
loop:	
	beq $t0, $a0, sairLoop
	add $v0, $v0, $a1
	addi $t0, $t0, 1
	j loop

# Faz a subtração
sairLoop:
	sub $v0, $v0, $a2
	
	lw $t0, 0($sp)
	jr $ra

# finaliza o programa
syscall10DasRuas:
