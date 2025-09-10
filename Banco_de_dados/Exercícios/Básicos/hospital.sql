-- 2.1 - Listar todos os usuários.
-- SELECT * FROM hospital.usuario;



-- 2.2 - Listar o primeiro nome e sobrenome de todos os usuários.
-- SELECT primeironome, sobrenome FROM hospital.usuario;


-- 2.3 - Listar todas as pessoas do sexo masculino.
-- SELECT * FROM hospital.usuario WHERE sexo = 'M';



-- 2.4 - Listar todos os logins dos perfis que estão ativos.
-- SELECT login FROM hospital.perfil WHERE ativo = 'S';



-- 2.5 - Listar as cidades de todos os endereços cadastrados, mas sem repeti-los.
-- SELECT DISTINCT cidade FROM hospital.endereco;



-- 2.6 - Listar os bairros de todos os endereços cadastrados da cidade de Aracaju, mas sem repeti-los
-- SELECT DISTINCT bairro FROM hospital.endereco WHERE UPPER(cidade) = 'ARACAJU';



-- 2.7 - Listar o primeiro nome e sobrenome de todos os usuários em ordem alfabética.
-- SELECT primeironome, sobrenome FROM hospital.usuario ORDER BY primeironome, sobrenome



-- 2.8 - Listar somente os sobrenomes de todas os usuários que são do sexo feminino em ordem alfabética (obs: sem repetir os sobrenomes).
-- SELECT DISTINCT sobrenome FROM hospital.usuario WHERE sexo = 'F' ORDER BY sobrenome



-- 2.9 - Listar o maior e menor salário dos médicos cadastrados no sistema.
-- SELECT MIN(salario), MAX(salario) FROM hospital.medico;



-- 2.10 - Listar o maior salário entre os médicos que possuem especialidade como Clínico Geral.
-- SELECT MAX(salario) FROM hospital.medico WHERE especialidade = 'Clínico Geral';



-- 2.11 - Listar a média de salário de todos os médicos que são Cirurgião.
-- SELECT AVG(salario) FROM hospital.medico WHERE especialidade = 'Cirurgião';



-- 2.12 - Listar a quantidade de pessoas que são do sexo masculino.
-- SELECT COUNT(*) FROM hospital.usuario WHERE sexo = 'M';



-- 2.13 - Listar somente a quantidade de pessoas que são do sexo masculino e que nasceram a partir de 1980.
-- SELECT COUNT(*) FROM hospital.usuario WHERE sexo = 'M' AND dataNasc >= '1980/01/01'