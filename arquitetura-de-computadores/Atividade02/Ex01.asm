main:
	li $v0, 5
	syscall
	add $t0, $v0, $zero
	
	li $v0, 5
	syscall
	add $t1, $v0, $zero
	
	add $a0, $t0, $t1
	
	li $v0, 1
	syscall
	
	li $a0, '\n'
	li $v0, 11
	syscall
	
	li, $v0, 1
	sub $a0, $t0, $t1
	syscall
	