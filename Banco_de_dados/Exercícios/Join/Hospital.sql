-- 2.1 - Listar o CPF e sobrenome de todos os usuários que possuem a sílaba “sa" em seu sobrenome.
-- SELECT 
-- cpf, 
-- primeiroNome AS nome,
-- sobrenome

-- FROM hospital.usuario WHERE sobrenome LIKE '%sa%'



-- 2.2 - Listar a quantidade de pessoas que possuem sobrenome com a inicial “S”.
-- SELECT
-- COUNT(sobrenome)

-- FROM hospital.usuario WHERE sobrenome LIKE 'S%'


-- 2.3 - Listar o nome e CPF de todos os pacientes. - INNER JOIN
-- SELECT
-- upac.cpf,
-- upac.primeiroNome,
-- upac.sobrenome

-- FROM         hospital.paciente AS pac
-- NATURAL JOIN hospital.usuario  AS upac



-- 2.4- Listar a soma de todos os salários dos médicos, porém apenas os que possuem cadastro ativo. - INNER JOIN
-- SELECT
-- SUM(salario)

-- FROM         hospital.medico
-- NATURAL JOIN hospital.usuario
-- NATURAL JOIN hospital.perfil

-- WHERE ativo = 'S'


-- 2.5 - Listar o nome e CPF dos pacientes, seguido do nome e CPF dos seus acompanhantes. - INNER JOIN
-- SELECT
-- upac.cpf,
-- upac.primeiroNome,
-- upac.sobrenome,
-- aco.cpf,
-- aco.primeironome,
-- aco.sobrenome

-- FROM         hospital.paciente AS pac
-- NATURAL JOIN hospital.usuario  AS upac
-- JOIN         hospital.usuario  AS aco  ON aco.cpf = pac.cpfacomp



-- 2.6 - Listar o nome e CPF de todos os pacientes que realizaram consulta. - INNER JOIN
-- SELECT DISTINCT
-- upac.cpf,
-- upac.primeiroNome,
-- upac.sobrenome

-- FROM         hospital.consulta AS con
-- NATURAL JOIN hospital.paciente AS pac
-- NATURAL JOIN hospital.usuario  AS upac



-- 2.7 - Listar o nome, CPF e número de prontuário de todos os pacientes que realizaram consulta e não houve prescrição de medicamento. - OUTER JOIN
-- SELECT DISTINCT
-- upac.cpf,
-- upac.primeiroNome,
-- upac.sobrenome,
-- pac.numProntuario

-- FROM         hospital.consulta   AS con
-- NATURAL JOIN hospital.paciente   AS pac
-- NATURAL JOIN hospital.usuario    AS upac
-- LEFT JOIN    hospital.prescricao AS pre  ON pac.numProntuario = pre.numProntuario

-- WHERE        pre.idconsultaprescricao IS NULL



-- 2.8 - Listar o nome, CPF, número de prontuário e o nome do medicamento de todos os pacientes que realizaram consulta e houve prescrição de medicamento. - OUTER JOIN
-- SELECT
-- upac.cpf,
-- upac.primeiroNome,
-- upac.sobrenome,
-- pac.numProntuario,
-- med.nome

-- FROM         hospital.consulta    AS con
-- NATURAL JOIN hospital.paciente    AS pac
-- NATURAL JOIN hospital.usuario     AS upac
-- LEFT JOIN    hospital.prescricao  AS pre  ON pac.numProntuario = pre.numProntuario
-- JOIN         hospital.medicamento AS med  ON med.idMedicamento = pre.idMedicamento