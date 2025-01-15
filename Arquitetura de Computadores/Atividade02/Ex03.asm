main:
	# pegando primeiro número
	li $v0, 5
	syscall
	move $t0, $v0
	
	# pegando segundo número
	li $v0, 5
	syscall
	move $t1, $v0
	
	# if(t0 > t1)
	bgt $t0, $t1, Do
	move $a0, $t1
	j Exit
	
Do: 	move $a0, $t0
Exit:	li $v0, 1
	syscall
	
	li $v0, 10
	syscall