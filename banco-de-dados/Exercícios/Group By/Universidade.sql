-- 1.1 - Liste a matrícula do professor (mat_professor), a maior e a menor nota dada, e a média de notas agrupado pela matrícula do professor, entre todas as suas turmas que ele leciona.
-- SELECT
-- mat_professor,
-- MAX(nota),
-- MIN(nota),
-- AVG(nota)

-- FROM         universidade.leciona   AS lec
-- NATURAL JOIN universidade.turma     AS tur
-- NATURAL JOIN universidade.cursa     AS cur

-- GROUP BY mat_professor



-- 1.2 - Liste o nome da disciplina (nome) e a média de notas das turmas, agrupado por disciplina (somente as disciplinas que tiverem notas), porém, somente daquelas disciplinas que são pré-requsito.
-- SELECT DISTINCT
-- req.cod_disc,
-- req.nome,
-- AVG(cur.nota)

-- FROM universidade.disciplina AS dis
-- JOIN universidade.disciplina AS req ON  dis.pre_req = req.cod_disc
-- JOIN universidade.turma      AS tur ON req.cod_disc = tur.cod_disc
-- JOIN universidade.cursa      AS cur ON tur.id_turma = cur.id_turma

-- WHERE cur.nota IS NOT NULL
-- GROUP BY req.cod_disc



-- 1.3 - Liste o nome da disciplina (nome), código do pré-requisito (pre_req) e número de alunos em cada turma, agrupado pela disciplina.
-- SELECT
-- dis.cod_disc,
-- dis.pre_req,
-- COUNT(cur.mat_estudante)

-- FROM universidade.disciplina AS dis
-- JOIN universidade.turma      AS tur ON dis.cod_disc = tur.cod_disc
-- JOIN universidade.cursa      AS cur ON tur.id_turma = cur.id_turma

-- GROUP BY dis.cod_disc



-- 1.4 - Liste o nome do departamento responsável (nome) e média das notas das turmas, agrupado pelo código do departamento responsável.
-- SELECT
-- dep.nome,
-- AVG(cur.nota)

-- FROM universidade.departamento AS dep
-- JOIN universidade.disciplina   AS dis ON dep.cod_depto = dis.depto_responsavel
-- JOIN universidade.turma        AS tur ON  dis.cod_disc = tur.cod_disc
-- JOIN universidade.cursa        AS cur ON  tur.id_turma = cur.id_turma

-- GROUP BY dep.cod_depto



-- 1.5 - Liste o maior e o menor salário agrupado por departamento.
SELECT
dep.nome,
MAX(car.salario),
MIN(car.salario)

FROM universidade.departamento AS dep
JOIN universidade.professor    AS pro ON dep.cod_depto = pro.departamento
JOIN universidade.cargo        AS car ON     pro.cargo = car.id_cargo

GROUP BY dep.nome

-- 1.6 - Liste a matrícula do professor (mat_professor) e código do departamento (departamento) dos professores que lecionam turmas com menos de 7 alunos.




-- 1.7 - Liste o primeiro nome, sobrenome do estudante e a média de notas, agrupado por cada estudante, porém somente das turmas de disciplinas que o departamento responsável é o DCOMP.




