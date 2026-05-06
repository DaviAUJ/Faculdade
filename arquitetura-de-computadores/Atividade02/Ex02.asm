main:
	# Pegando a
	li $v0, 5
	syscall
	move $t0, $v0
	
	# Pegando b
	li $v0, 5
	syscall
	move $t1, $v0
	
	# Pegando c
	li $v0, 5
	syscall
	move $t2, $v0
	
	# b^2 - 4ac
	mul $t1, $t1, $t1 # $t1 = b^2
	mul $t2, $t0, $t2 # $t2 = ac
	li $t0, 4 # $t0 = 4
	mul $t2, $t0, $t2 # $t2 = 4ac
	sub $a0, $t1, $t2 # $a0 = b^2 - 4ac
	
	# printando
	li $v0, 1
	syscall
	
	# saindo
	li $v0, 10
	syscall
	