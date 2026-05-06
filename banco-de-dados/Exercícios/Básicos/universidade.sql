-- 1.1 - Liste o cpf dos professores do departamento ‘DMA”.
-- SELECT cpf FROM universidade.professor WHERE departamento = 'DMA';



-- 1.2 - Liste o id de todas as turmas que o aluno de matrícula ‘E101’ está cursando.
-- SELECT id_turma FROM universidade.cursa WHERE mat_estudante = 'E101';



-- 1.3 - Liste o nome, sobrenome e cpf de todas as pessoas que têm telefone.
-- SELECT primeiro_nome, sobrenome, cpf FROM universidade.usuario WHERE telefone IS NOT NULL;



-- 1.4 - Liste o nome e código de todas as disciplinas que tenham pré-requisito e tenham mais de 2 créditos.
-- SELECT nome, cod_disc FROM universidade.disciplina WHERE creditos > 2 AND pre_req IS NOT NULL; 



-- 1.5 - Calcule a média de notas de todos os alunos.
-- SELECT AVG(nota) AS nota_media FROM universidade.cursa



-- 1.6 - Listar o número de professores que orientam algum aluno - Um professor orienta um aluno se ambos estão associados na tabela plano
-- SELECT COUNT(DISTINCT mat_professor) FROM universidade.plano WHERE mat_professor IS NOT NULL AND mat_estudante IS NOT NULL;



-- 1.7 - Listar a matrícula de todos os professores que orientam algum aluno ou que são chefes de algum departamento.
-- SELECT DISTINCT mat_professor FROM universidade.plano WHERE mat_professor IS NOT NULL
-- UNION 
-- SELECT DISTINCT chefe FROM universidade.departamento WHERE chefe IS NOT NULL;



-- 1.8 - Listar a matrícula de todos os professores que orientam algum aluno e que são chefes de algum departamento.
-- SELECT mat_professor FROM universidade.plano WHERE mat_professor IS NOT NULL
-- INTERSECT 
-- SELECT chefe FROM universidade.departamento WHERE chefe IS NOT NULL;



-- 1.9 Listar a matrícula de todos os professores que orientam algum aluno e que não são chefes de algum departamento.
-- SELECT mat_professor FROM universidade.plano WHERE mat_professor IS NOT NULL
-- EXCEPT
-- SELECT chefe FROM universidade.departamento WHERE chefe IS NOT NULL;