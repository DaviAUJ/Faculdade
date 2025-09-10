-- 1.1 - Liste o nome das disciplinas que possuem turmas. - INNER JOIN
-- SELECT DISTINCT nome FROM universidade.disciplina AS dsc
-- INNER JOIN universidade.turma AS trm 
-- ON dsc.cod_disc = trm.cod_disc;



-- 1.2 - Liste o primeiro nome e sobrenome do estudante e o nome de cada disciplina das turmas que ele está cursando. - INNER JOIN
-- SELECT primeiro_nome, sobrenome, dsc.nome AS nome_disciplina 
-- FROM universidade.usuario AS usu
-- JOIN universidade.estudante AS std
-- ON std.cpf = usu.cpf
-- JOIN universidade.cursa AS crs
-- ON std.mat_estudante = crs.mat_estudante
-- JOIN universidade.turma AS trm
-- ON trm.id_turma = crs.id_turma
-- JOIN universidade.disciplina AS dsc
-- ON dsc.cod_disc = trm.cod_disc;



-- 1.3 - Liste o primeiro nome e sobrenome do aluno e o primeiro nome e sobrenome de seu orientador. - INNER JOIN
-- SELECT uest.primeiro_nome, uest.sobrenome, upro.primeiro_nome, upro.sobrenome
-- FROM   universidade.plano     AS pla 
-- JOIN   universidade.estudante AS est  ON est.mat_estudante = pla.mat_estudante 
-- JOIN   universidade.professor AS pro  ON pro.mat_professor = pla.mat_professor
-- JOIN   universidade.usuario   AS uest ON          uest.cpf = est.cpf            
-- JOIN   universidade.usuario   AS upro ON          upro.cpf = pro.cpf;
 

-- 1.4 - Considerando todas as turmas, liste o primeiro nome e sobrenome do professor, o nome da disciplina que ele está lecionando, além disso liste o primeiro nome e sobrenome de todos os alunos cursando essas turmas. - INNER JOIN
-- SELECT upro.primeiro_nome  AS nome_professor, 
-- 	   upro.sobrenome      AS sobrenome_professor,
-- 	   dis.nome            AS disciplina,
-- 	   uest.primeiro_nome  AS nome_aluno,
-- 	   uest.sobrenome      AS sobrenome_aluno
	   
-- FROM universidade.turma      AS tur
-- JOIN universidade.leciona    AS lec  ON      lec.id_turma = tur.id_turma
-- JOIN universidade.cursa      AS cur  ON      cur.id_turma = tur.id_turma
-- JOIN universidade.disciplina AS dis  ON      dis.cod_disc = tur.cod_disc
-- JOIN universidade.professor  AS pro  ON pro.mat_professor = lec.mat_professor
-- JOIN universidade.estudante  AS est  ON est.mat_estudante = cur.mat_estudante
-- JOIN universidade.usuario    AS upro ON          upro.cpf = pro.cpf   
-- JOIN universidade.usuario    AS uest ON          uest.cpf = est.cpf

-- ORDER BY nome_professor, sobrenome_professor, disciplina, nome_aluno, sobrenome_aluno



-- 1.5 - Liste o nome da disciplina e o nome do seu pré-requisito. - INNER JOIN
-- SELECT 
-- dis.nome AS Disciplina,
-- pre.nome AS PreRequisito

-- FROM universidade.disciplina AS dis
-- JOIN universidade.disciplina AS pre ON dis.pre_req = pre.cod_disc



-- 1.6 - Liste o primeiro nome e sobrenome do professor e o primeiro nome e sobrenome do seu chefe. - INNER JOIN
-- SELECT
-- uche.cpf           AS cpf_chefe,
-- uche.primeiro_nome AS nome_chefe,
-- uche.sobrenome     AS sobrenome_chefe,
-- upro.cpf           AS cpf_professor,
-- upro.primeiro_nome AS nome_professor,
-- upro.sobrenome     AS sobrenome_professor

-- FROM universidade.departamento AS dep
-- JOIN universidade.professor    AS che  ON che.mat_professor = dep.chefe
-- JOIN universidade.usuario      AS uche ON          uche.cpf = che.cpf
-- JOIN universidade.professor    AS pro  ON  pro.departamento = dep.cod_depto  
-- JOIN universidade.usuario      AS upro ON          upro.cpf = pro.cpf       AND upro.cpf != uche.cpf

-- ORDER BY nome_chefe, sobrenome_chefe, cpf_chefe, nome_professor, sobrenome_professor, cpf_professor



-- 1.7 - Liste o nome da disciplina, turma e primeiro nome e sobrenome do professor, das disciplinas que não são pré-requisito - OUTER JOIN
-- SELECT
-- tur.id_turma       AS id_turma,
-- pre.nome           AS disciplina,
-- pre.cod_disc       AS codigo,
-- tur.numero         AS turma,
-- upro.primeiro_nome AS nome_professor,
-- upro.sobrenome     AS sobrenome_professor

-- FROM       universidade.disciplina AS dis
-- RIGHT JOIN universidade.disciplina AS pre  ON       dis.pre_req = pre.cod_disc
-- JOIN       universidade.turma      AS tur  ON      pre.cod_disc = tur.cod_disc 
-- JOIN       universidade.leciona    AS lec  ON      tur.id_turma = lec.id_turma
-- JOIN       universidade.professor  AS pro  ON lec.mat_professor = pro.mat_professor
-- JOIN       universidade.usuario    AS upro ON           pro.cpf = upro.cpf
-- WHERE      dis.cod_disc IS NULL

-- ORDER BY disciplina, turma, sobrenome_professor



-- 1.8 - Liste o primeiro nome e sobrenome de todos os alunos e primeiro nome e sobrenome do orientador, inclusive os alunos sem orientador. - OUTER JOIN
-- SELECT
-- uest.primeiro_nome AS nome_aluno,
-- uest.sobrenome     AS sobrenome_aluno,
-- upro.primeiro_nome AS nome_professor,
-- upro.sobrenome     AS sobrenome_professor


-- FROM      universidade.estudante AS est
-- LEFT JOIN universidade.plano     AS pla  USING(mat_estudante)
-- LEFT JOIN universidade.professor AS pro  USING(mat_professor)
-- JOIN      universidade.usuario   AS uest ON est.cpf = uest.cpf
-- LEFT JOIN universidade.usuario   AS upro ON pro.cpf = upro.cpf



-- 1.9 - Liste o primeiro nome e sobrenome de todos os professores e o primeiro nome e sobrenome de seus orientandos (alunos que são orientados), inclusive os professores sem orientandos. - OUTER JOIN
-- SELECT
-- upro.cpf           AS cpf_professor,
-- upro.primeiro_nome AS nome_professor,
-- upro.sobrenome     AS sobrenome_professor,
-- uest.cpf           AS cpf_orientando,
-- uest.primeiro_nome AS nome_orientando,
-- uest.sobrenome     AS sobrenome_orientando

-- FROM      universidade.professor AS pro
-- LEFT JOIN universidade.plano     AS pla  USING(mat_professor)
-- LEFT JOIN universidade.estudante AS est  USING(mat_estudante)
-- JOIN      universidade.usuario   AS upro ON pro.cpf = upro.cpf
-- LEFT JOIN universidade.usuario   AS uest ON est.cpf = uest.cpf

-- ORDER BY nome_professor, sobrenome_professor, nome_orientando, sobrenome_orientando



-- 1.10 - Liste o primeiro nome e sobrenome de todos alunos e o primeiro nome e sobrenome dos professores, independente da orientação. - OUTER JOIN
-- SELECT
-- upro.cpf           AS cpf_professor,
-- upro.primeiro_nome AS nome_professor,
-- upro.sobrenome     AS sobrenome_professor,
-- uest.cpf           AS cpf_orientando,
-- uest.primeiro_nome AS nome_orientando,
-- uest.sobrenome     AS sobrenome_orientando

-- FROM      universidade.plano     AS pla
-- FULL JOIN universidade.professor AS pro  USING(mat_professor)
-- FULL JOIN universidade.estudante AS est  USING(mat_estudante)
-- LEFT JOIN universidade.usuario   AS upro ON pro.cpf = upro.cpf
-- LEFT JOIN universidade.usuario   AS uest ON est.cpf = uest.cpf



-- 1.11 - Liste o primeiro nome e sobrenome dos professores que não lecionam turmas. - OUTER JOIN
-- SELECT 
-- upro.cpf           AS cpf_professor,
-- upro.primeiro_nome AS nome_professor,
-- upro.sobrenome     AS sobrenome_professor

-- FROM       universidade.leciona   AS lec
-- RIGHT JOIN universidade.professor AS pro  USING(mat_professor)
-- JOIN       universidade.usuario   AS upro ON pro.cpf = upro.cpf

-- WHERE lec.id_turma IS NULL



-- 1.12 - Liste o nome das disciplinas das turmas que não tem alunos cursando. - OUTER JOIN
-- SELECT
-- dis.nome   AS disciplina, 
-- tur.numero AS turma

-- FROM       universidade.cursa      AS cur
-- RIGHT JOIN universidade.turma      AS tur USING(id_turma)
-- JOIN       universidade.disciplina AS dis USING(cod_disc)

-- WHERE mat_estudante IS NULL


-- 1.13 - Refaça a consulta 1.7 da atividade 4, usando OUTER JOIN - OUTER JOIN
-- SELECT DISTINCT
-- pro.mat_professor AS matricula

-- FROM      universidade.professor    AS pro
-- LEFT JOIN universidade.plano        AS pla USING(mat_professor)
-- LEFT JOIN universidade.departamento AS dep ON pro.mat_professor = dep.chefe

-- WHERE pla.mat_estudante IS NOT NULL OR dep.chefe IS NOT NULL
-- ORDER BY matricula



-- 1.14 - Refaça a consulta 1.8 da atividade 4, usando JOIN - INNER JOIN
-- SELECT DISTINCT
-- pro.mat_professor AS matricula

-- FROM      universidade.professor    AS pro
-- LEFT JOIN universidade.plano        AS pla USING(mat_professor)
-- LEFT JOIN universidade.departamento AS dep ON pro.mat_professor = dep.chefe

-- WHERE pla.mat_estudante IS NOT NULL AND dep.chefe IS NOT NULL
-- ORDER BY matricula



-- 1.15 - Refaça a consulta 1.9 da atividade 4, usando OUTER JOIN - OUTER JOIN
-- SELECT DISTINCT
-- pro.mat_professor AS matricula

-- FROM      universidade.professor    AS pro
-- LEFT JOIN universidade.plano        AS pla USING(mat_professor)
-- LEFT JOIN universidade.departamento AS dep ON pro.mat_professor = dep.chefe

-- WHERE pla.mat_estudante IS NOT NULL AND dep.chefe IS NULL
-- ORDER BY matricula