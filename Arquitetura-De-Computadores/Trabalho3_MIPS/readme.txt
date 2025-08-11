Terceiro trabalho da materia de Arquitetura de Computadores
Aluno: Davi Araújo do Nascimento
Turma 03

Olá professor Calebe!

Essa é minha implementação do MIPS ciclo único. Primeiro fiz o básico, depois adicionei o jump, seguindo o
que livro ensina. Esta é a segunda vez que eu envio, você disse na aula do dia 11/02 que 
poderia reenviar sem penalidade então estou aqui. Vou escrever o que fiz na primeira versão e
depois mostro o que adicionei e mudei, ela já funcionava 100% na primeira versão, mas quis fazer mais.

Esta minha implementação contém todas as instruções que você pediu, R-Type, addi, beq, sw, lw e j.
Eu adicionei algumas a mais, mas vou falar sobre isso depois. O código está todo modularizado,
com um modulo por arquivo .v e cada um com um nome descritivo. O arquivo principal é o MIPSCicloUnico.v,
e para executa-lo basta rodar o makefile. A implementação também é acompanhada de um programa que usa quase 
todas as instruções, ficou de fora apenas algumas R-Type, mas todo o resto tem. Esse programa é para
calcular a expressão a * b - c. O código em assembly vai vir junto na pasta Codigos.

Tudo isso eu já havia enviado antes, então vamos para o que mudou. Mudei o makefile, de lá para cá
aprendi mais sobre o makefile e fiz algo melhor, agora a regra de limpar funciona para windows e linux,
é só mudar o sistema nas variáveis, não se preocupe porque eu já vou enviar no jeito para linux. Segunda mudança,
reestruturei os arquivos para eles não ficarem numa pasta só, deixei mais organizado. Terceira mudança, 
a maior de todas, novas instruções. Eu adicionei jal e jr para poder escrever funções e a instrução nor, 
eu precisava dela para melhorar o programa. Quarta e última mudança, melhorei o programa, 
do jeito que eu havia feito anteriormente, a variável a não poderia ser negativa senão o programa não funcionava, 
ela ainda não pode ser, mas eu adapto a entrada antes que alguma coisa dê errado.

Agora vou explicar como eu adicionei as instruções novas. os componentes adicionais estão todos em suas
respectivas seções no arquivo principal.

Para o jal, eu adicionei novos multiplexadores para poder escrever o pc+4 no $ra, além disso,
adicionei um novo sinal no MainControl, o link, que vai controlar esses novos multiplexadores. 
De resto foi usar o parte da instrução j já implementada.

Para o jr, tive que fazer uma pequena gambiarra, acho que posso chama-la assim, como ela é R-Type, eu não
podia mudar os sinais que saem do MainControl, pois essa mudança iria bagunçar as outras instruções do tipo,
então tive que fazer um sinal específico sair da ALUControl, o jrEnable, que vai fazer o gerenciamento dessa 
instrução. Por ela ser R-Type, vai tentar escrever em algum registrador, sendo esse o $zero, pois no seu 
binário tem 00000 no registrador alvo, porém como existe uma restrição no banco de registradores que impede
esse em específico de ser alterado, então tudo flui bem. Também tive que adicionar mais um multiplexador, antes do
PC para controlar quem vai entrar nele. Totalizando um total de 3 atrás do PC, talvez seria melhor se fosse
um multiplexador que aceitasse mais entradas, porém queria fazer tudo em cima do que já foi feito sem mudar muito.

Para o nor foi simples, ela é R-Type, e na sua ALU já havia essa operação, tive de apenas acrecentar mais
um caso no case do ALUControl. Eu precisava dela para fazer um NOT bitwise.