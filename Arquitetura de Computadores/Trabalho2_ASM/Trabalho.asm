# Aluno: Davi Araújo do Nascimento

# Este programa tem como função receber nesta ordem, um inteiro N, N inteiros para formação
# de um vetor e mais um inteiro E. Dentro desse vetor será realizado a operação de exponenciação(feita
# em uma função recursiva), cada posição será elevada ao número E e seu valor será substituído pelo resultado correspondente

# Ex: [X, Y, Z]
# Depois: [X ^ E, Y ^ E, Z ^ E]

.data
	msg0: .asciiz "Digite o tamanho do vetor: "
	msg1a: .asciiz "Agora digite os "
	msg1b: .asciiz " numeros: \n"
	msg2: .asciiz "Expoente: "
	msg3: .asciiz "Apos os calculos o vetor ficou assim: \n"
.text

Main:
	# Imprimindo mensagem
	li $v0, 4
	la $a0, msg0
	syscall
	
	# Lendo inteiro N
	li $v0, 5
	syscall
	move $s0, $v0 # $s0 = N
	
	# Alocação dinâmica do vetor
	li $v0, 9
	mul $a0, $s0, 4 # em $a0 deve estar o argumento de tamanho, 4N
	syscall # O vetor é criado no heap
	move $s1, $v0 # endereço retorna em $v0 que vou salvar em $s1
	
	li $t0, 0 # $t0 servirá como contador
	move $t1, $s1 # $t1 servirá como cursor do vetor, guardarei o endereço e somarei 4 todas vezes que mudar de posição
	
	# Imprimindo mensagem
	li $v0, 4
	la $a0, msg1a
	syscall
	li $v0, 1
	move $a0, $s0 # colocando o número no meio
	syscall
	li $v0, 4
	la $a0, msg1b
	syscall
	
	# Lendo os N inteiros
	Loop0: # for(int t0 = 0; t0 < s0; t0++)
		bge $t0, $s0, SairLoop0
		li $v0, 5
		syscall
		sw $v0, 0($t1) # salva no vetor o número lido
		# Dá um passo nos contadores
		addi $t1, $t1, 4
		addi $t0, $t0, 1
		j Loop0
	
	SairLoop0:
		# Imprimindo mensagem
		li $v0, 4
		la $a0, msg2
		syscall
	
		# lendo E
		li $v0, 5
		syscall
		move $s2, $v0 #s2 = E
		
		# Passando os parametros
		move $a0, $s1
		move $a1, $s2
		move $a2, $s0
		
		jal f_ElevarVetor
		
		# Imprimindo mensagem
		li $v0, 4
		la $a0, msg3
		syscall
		
		li $t0, 0 # $t0 novamente servirá como contador
		move $t1, $s1 # $t1 também volta a servir para o seu antigo propósito 
		
	# Imprimindo o vetor depois de aplicar a função
	Loop2:	# for(int t0 = 0; t0 < s0; t0++)
		bge $t0, $s0, SairLoop2
		li $v0, 1
		lw $a0, 0($t1)
		syscall
		
		li $v0, 11
		li $a0, '\n'
		syscall
		
		# Dá um passo nos contadores
		addi $t0, $t0, 1
		addi $t1, $t1, 4
		
		j Loop2

	SairLoop2:
		# finaliza programa
		li $v0, 10
		syscall

f_Elevar: # ($a0: int base, $a1: int expoente) return $v0: int
	# Fiz uma gambiarra(acho que posso chamar assim) para não repetir desnecessariamente instruções no loop recursivo
	# basicamente é a adição de um bloco a mais para essa função e esses sw e lw que tem nesse primeiro bloco
	li $v0, 1 # configuro o retorno
	
	subi $sp, $sp, 8
	sw $a1, 0($sp) # Salvo o parâmetro original pois vou precisar alterar esse registrador durante o loop recursivo
	sw $ra, 4($sp) # E Salvo o link original pois vou dar outro jal ali em baixo como pode ver
	
	jal f_ElevarRecursao
	
	lw $a1, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, 8
	
	jr $ra # finalmente da função
	
	f_ElevarRecursao:
		# Fazendo a stack de chamada de função
		subi $sp, $sp, 4
		sw $ra, 0($sp)
	
		# Caso base (if $a0 <= 0)
		ble $a1, 0, f_SaidaElevar
		subi $a1, $a1, 1
		jal f_ElevarRecursao
	
		# Quando voltar desempilhando multiplica $v0
		mul $v0, $v0, $a0
	
	f_SaidaElevar:
		# Faz o desempilhamento da stack
		lw $ra, 0 ($sp)
		add $sp, $sp, 4
		jr $ra
	
f_ElevarVetor: # ($a0: int* vetor, $a1: int expoente, $a2: int tamanho) void
	# Salvando os registradores que vou usar
	subi $sp, $sp, 16
	sw $t0, 0($sp) # $t0 vai servir como contador para iterar o vetor passado como argumento
	sw $t1, 4($sp)  # Vou usar como cursor do vetor da mesma forma que fiz em cima
	sw $v0, 8($sp) # Acho que geralmente não se salva v0, mas vou salvar aqui pois a função não tem retorno nenhum mas usa o v0 para pegar o retorno de outra função
	sw $ra, 12($sp) # Guardo também na memória o link, sem isso ele seria perdido por causa do jal no meio desta função
	
	li $t0, 0 
	move $t1, $a0
	
	Loop1: # for(int t0 = 0; t0 < a2; t0++)
		bge $t0, $a2, SairLoop1
		# Como guardei $a0 em $t1 vou usá-lo para passar o argumento da outra função que vou chamar
		# Não fiz o mesmo com $a1 pois basicamente ele se repete nas duas funções que fiz
		# Nem vou fazer com $a2 pois f_Elevar não usa esse registrador
		lw $a0, 0($t1) # Pega o número da vez do vetor
		
		jal f_Elevar
	
		# salva de volta no vetor e dá um passo nos contadores
		sw $v0, 0($t1) 
		addi $t0, $t0, 1
		addi $t1, $t1, 4
		
		j Loop1
	
	SairLoop1:
		# Fim da função. Agora é arrumar a bagunça que fiz no registradores e sair
		lw $t0, 0($sp)
		lw $t1, 4($sp)
		lw $v0, 8($sp)
		lw $ra, 12($sp) # restauro o link original
		addi $sp, $sp, 16
		
		jr $ra
