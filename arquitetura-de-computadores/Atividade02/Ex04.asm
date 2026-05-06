Main:
	# pegando N
	li $v0, 5
	syscall
	move $s0, $v0

	# contador
	li $a0, 0
	
	# for(i = 1; i <= N; i++)
Loop: 	li $v0, 1
	addi $a0, $a0, 1
	syscall
	
	# printando \n
	li $v0, 11
	move $t0, $a0
	li $a0, '\n'
	syscall
	move $a0, $t0
	
	bne $a0, $s0, Loop
	j Exit
	
Exit:
	li $v0, 10
	syscall
