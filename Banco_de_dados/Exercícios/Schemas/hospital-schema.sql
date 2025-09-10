CREATE SCHEMA hospital;
CREATE DOMAIN hospital.tipo_cpf AS VARCHAR(11);
CREATE TABLE hospital.endereco(
idEndereco SERIAL,
rua VARCHAR(255) NOT NULL,
numero int,
cep VARCHAR(8) NOT NULL,
bairro VARCHAR(60),
complemento VARCHAR(60),
cidade VARCHAR(60) NOT NULL,
estado VARCHAR(60) NOT NULL,
pais VARCHAR(60) NOT NULL,
CONSTRAINT pk_endereco PRIMARY KEY (idEndereco),
CONSTRAINT uq_endereco UNIQUE (cep, numero, rua, cidade, estado)
);
CREATE TABLE hospital.perfil(
idPerfil SERIAL,
login VARCHAR(10) NOT NULL,
senhaCriptograda VARCHAR(60) NOT NULL,
ativo VARCHAR(1) NOT NULL,
CONSTRAINT pk_perfil PRIMARY KEY (idPerfil)
);
CREATE TABLE hospital.usuario(
cpf hospital.tipo_cpf,
primeiroNome VARCHAR(45) NOT NULL,
sobrenome VARCHAR(45) NOT NULL,
dataNasc DATE,
email VARCHAR(45),
sexo VARCHAR(1),
idPerfil int,
CONSTRAINT pk_cpf_usuario PRIMARY KEY (cpf),
CONSTRAINT fk_perfil FOREIGN KEY (idPerfil) REFERENCES
hospital.perfil(idPerfil)
ON DELETE SET NULL ON UPDATE CASCADE
-- CASCADE (Em Cascata) - Quando o campo da chave primária é atualizado,
-- registros na tabela referenciada são atualizados.
-- SET NULL - Quando um registro com a chave primária é excluído,
-- os respectivos campos na tabela relacionada são setados para NULL.
);
CREATE TABLE hospital.mora(

cpf hospital.tipo_cpf,
idEndereco int,
CONSTRAINT pk_cpf_endereco_mora PRIMARY KEY (cpf,idEndereco),
CONSTRAINT fk_endereco_mora FOREIGN KEY (idEndereco) REFERENCES
hospital.endereco(idEndereco),
CONSTRAINT fk_cpf_mora FOREIGN KEY (cpf) REFERENCES
hospital.usuario(cpf)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.fone(
fone VARCHAR(11),
cpf hospital.tipo_cpf,
CONSTRAINT pk_fone_cpf PRIMARY KEY (fone, cpf),
CONSTRAINT fk_cpf_fone FOREIGN KEY (cpf) REFERENCES hospital.usuario(cpf)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.atendente(
cpf hospital.tipo_cpf,
CONSTRAINT pk_atendente_cpf PRIMARY KEY (cpf),
CONSTRAINT fk_cpf_atendente FOREIGN KEY (cpf) REFERENCES
hospital.usuario(cpf)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.acompanhante(
cpf hospital.tipo_cpf,
CONSTRAINT pk_acompanhante_cpf PRIMARY KEY (cpf),
CONSTRAINT fk_cpf_acompanhante FOREIGN KEY (cpf) REFERENCES
hospital.usuario(cpf)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.paciente(
numProntuario VARCHAR(6) NOT NULL,
cpf hospital.tipo_cpf,
cartaoSUS VARCHAR(15),
cpfAcomp hospital.tipo_cpf,
CONSTRAINT pk_paciente_numpront PRIMARY KEY (numProntuario),
CONSTRAINT fk_cpf_paciente FOREIGN KEY (cpf) REFERENCES
hospital.usuario(cpf),
CONSTRAINT fk_cpf_acomp FOREIGN KEY (cpfAcomp) REFERENCES
hospital.acompanhante(cpf)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.historico(

idHistorico SERIAL,
dataCad DATE,
acao VARCHAR(60),
CONSTRAINT pk_idHistorico PRIMARY KEY (idHistorico)
);
CREATE TABLE hospital.acesso_hist_atend_perf (
idHistorico INT,
cpfAtendente hospital.tipo_cpf,
idPerfil INT,
CONSTRAINT pk_idhistorico_acesso_hist_atende_perf PRIMARY KEY (idHistorico),
CONSTRAINT fk_idhistorico_acesso FOREIGN KEY (idHistorico) REFERENCES
hospital.historico(idHistorico),
CONSTRAINT fk_cpf_acesso_atedente FOREIGN KEY (cpfAtendente)
REFERENCES hospital.atendente(cpf),
CONSTRAINT fk_idperfil_acesso FOREIGN KEY (idPerfil) REFERENCES
hospital.perfil(idPerfil)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.medicamento (
idMedicamento SERIAL,
nome VARCHAR(60) NOT NULL,
apresentacao VARCHAR(20) NOT NULL,
unidade VARCHAR(60) NOT NULL,
posologia VARCHAR(60) NOT NULL,
CONSTRAINT pk_medicamento PRIMARY KEY (idMedicamento)
);
CREATE TABLE hospital.medico (
cpf hospital.tipo_cpf,
idRegistro SERIAL,
numCRM VARCHAR(15) NOT NULL,
especialidade VARCHAR(30) NOT NULL,
salario REAL,
CONSTRAINT pk_medico PRIMARY KEY (idRegistro),
CONSTRAINT ck_sal_negativo CHECK(salario>0),
CONSTRAINT fk_medico_cpf FOREIGN KEY (cpf) REFERENCES
hospital.usuario(cpf)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.medico_docente (
idRegistro int,
titulacao VARCHAR(20),
CONSTRAINT pk_medico_docente PRIMARY KEY (idRegistro),
CONSTRAINT fk_medico_docente_cpf FOREIGN KEY (idRegistro) REFERENCES
hospital.medico(idRegistro)

ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.medico_residente (
idRegistro int,
anoResidencia DATE,
CONSTRAINT pk_medico_residente PRIMARY KEY (idRegistro),
CONSTRAINT fk_medico_residente FOREIGN KEY (idRegistro) REFERENCES
hospital.medico(idRegistro)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.consulta (
idConsulta SERIAL,
dataConsulta DATE NOT NULL,
horaConsulta VARCHAR(5) NOT NULL,
local VARCHAR(15) NOT NULL,
idRegistroMedico INT NOT NULL,
cpfAtendente hospital.tipo_cpf NOT NULL,
idHistorico INT NOT NULL,
numProntuario VARCHAR(15) NOT NULL,
PRIMARY KEY (idConsulta, numProntuario),
CONSTRAINT fk_consulta_registro FOREIGN KEY (idRegistroMedico)
REFERENCES hospital.medico(idRegistro),
CONSTRAINT fk_consulta_atendente FOREIGN KEY (cpfAtendente)
REFERENCES hospital.atendente(cpf),
CONSTRAINT fk_consulta_historico FOREIGN KEY (idHistorico) REFERENCES
hospital.historico(idHistorico),
CONSTRAINT fk_consulta_paciente FOREIGN KEY (numProntuario)
REFERENCES hospital.paciente(numProntuario)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.exame (
idExame SERIAL,
nome VARCHAR(20) NOT NULL,
recomendacao VARCHAR(60),
idRegistroMedicoDocente INT NOT NULL,
numProntuario VARCHAR(15) NOT NULL,
CONSTRAINT pk_exame PRIMARY KEY (idExame),
CONSTRAINT fk_exame_registro_medico_doc FOREIGN KEY
(idRegistroMedicoDocente) REFERENCES hospital.medico_docente(idRegistro),
CONSTRAINT fk_exame_paciente FOREIGN KEY (numProntuario) REFERENCES
hospital.paciente(numProntuario)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.solicitacao_exame (

idExame INT NOT NULL,
idRegistroSolicitante INT NOT NULL,
dataRealizacao DATE,
dataPrevista DATE NOT NULL,
dataHoraEmissao TIMESTAMP NOT NULL,
statusPedido VARCHAR(10),
CONSTRAINT pk_solic_exame PRIMARY KEY (idExame, idRegistroSolicitante),
CONSTRAINT fk_solic_exame FOREIGN KEY (idExame) REFERENCES
hospital.exame(idExame),
CONSTRAINT fk_solic_exame_medico FOREIGN KEY (idRegistroSolicitante)
REFERENCES hospital.medico(idRegistro)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.laudo (
idLaudo SERIAL,
descricao VARCHAR(255),
dataEmissao DATE NOT NULL,
dataRevisao DATE NOT NULL,
statusLaudo VARCHAR(15) NOT NULL,
idMedicoRevisorResidente INT NOT NULL,
idMedicoEmissorDocente INT NOT NULL,
idExame INT NOT NULL,
CONSTRAINT pk_laudo PRIMARY KEY (idLaudo),
CONSTRAINT fk_laudo_med_revisor FOREIGN KEY (idMedicoRevisorResidente)
REFERENCES hospital.medico_residente(idRegistro),
CONSTRAINT fk_laudo_med_emissor FOREIGN KEY (idMedicoEmissorDocente)
REFERENCES hospital.medico_docente(idRegistro),
CONSTRAINT fk_laudo_exame FOREIGN KEY (idExame) REFERENCES
hospital.exame(idExame)
ON DELETE SET NULL ON UPDATE CASCADE
);
CREATE TABLE hospital.prescricao (
idConsultaPrescricao INT NOT NULL,
idMedicamento INT NOT NULL,
numProntuario VARCHAR(15) NOT NULL,
PRIMARY KEY (idConsultaPrescricao, idMedicamento, numProntuario),
CONSTRAINT fk_presc_med2 FOREIGN KEY (idMedicamento) REFERENCES
hospital.medicamento(idMedicamento)
ON DELETE SET NULL ON UPDATE CASCADE
);
-- ENDEREÇOS --
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua A',15, '49100000', 'Rosa Elze', '','São Cristóvão','Sergipe','BR');

INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua B',20, '12345698', 'Centro', '','Maceió','Alagoas','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua C',16, '12457863', 'Inácio Barbosa', '','Aracaju','Sergipe','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua D',1, '12365478', 'Centro', '','Aracaju','Sergipe','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua E',200, '12456379', 'Centro', '','Aracaju','Sergipe','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Street Y',597, '12456398', 'Burbank', '','Los Angeles','Califórnia','EUA');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua J',1025, '12364489', 'Penha', '','São Paulo','São Paulo','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Street H',115, '12345678', 'Deep Ellum', '','Dallas','Texas','EUA');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua L',155, '12456379', 'Centro', '','São Paulo','São Paulo','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Street A',1497, '04561259', 'Boyle Heights', '','Los
Angeles','Califórnia','EUA');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua JK',155, '45313687', 'Inácio Barbosa', '','Aracaju','Sergipe','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua LM',155, '45789321', 'América', '','Aracaju','Sergipe','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua MN',155, '12456348', 'Farolândia', '','Aracaju','Sergipe','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua O',155, '45326178', 'Atalaia', '','Aracaju','Sergipe','BR');
INSERT INTO hospital.endereco (rua, numero, cep, bairro, complemento, cidade, estado,
pais)
VALUES ('Rua P',155, '98745635', 'Atalaia', '','Aracaju','Sergipe','BR');

-- PERFIS --
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('neymar_si','IAfXsniaoRfqeFlHsejpKsSvJtay7W', 'S');

INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('juli_cesar','t0MlSabsALBNPvIDToyCkcF0HeyaK7', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('mta-santos','RqcnaISXs7OPPEVRV6II3SaBd5pRmj', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('maria_stos','aVkB8gVsnHOBtaUQtB62iz2FHzVain', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('jord_cosa','oieAUA1zjao0VaOcmnAgSDnvWhJoAe', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('maria_st','DNaSgaUjfrhooFQnJ7gjPoOk0Qnml0', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('maria10','aGnISL4SiOfSUgD6AlhUnSviG4Phiv', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('joao67','afodaornp2voQiaiPuFVASSWjA7oNA', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('thio_silva','oiaQCCUUGuaOIaT6Yzndn8DxJjD8b1', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('david-luiz','BIHjb4DtWtiaShYAdzE4aQwOBwZ8LE', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('marc_ruim','AsoGngj2TwIjcVVmNoavkoo8dooAnK', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('hers_silva','jkaWxnHkVjSgjQWxWVZOnL2GhcoFGz', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('mart75','P6iQdRKinIqiEasBX8afSKSfIhwkda', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('jorge15','aAoKpPDZacXSazTJVoAqILaaohG3KE', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('marijose','SrLfHKn1VObQ9opM0oI8fod2oViler', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('joana','7WZtW0q6jeO0oxxQTKA7stBaZttTzJ', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('mariana','s6mS4eH3WuIrYreI94u1vwKntbA5AO', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('diana','1tAfyOofasf6Ay8zMeH5AMJuto8aAF', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('raquel','9onWZ8sAk3WytXf7eJVc5ydmnim345', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('diego','tFhoAsOeoed9TPnXJmKfbfy7K5mTig', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('lucas','7mLqMEot3jpU9e72zRDiofRAs5C9kS', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('andre','tcYodebq3KAsmQnfghiaKXp6m2othA', 'S');
INSERT INTO hospital.perfil (login, senhaCriptograda, ativo) VALUES
('antonio','9t6kvyLYmQmJesXeRtT7VW2eVSiou1', 'S');

-- usuários --

INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('23456789011','Neymar','Silva','1995/10/15','meninoney@bancodedados.com','M',1);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('32165498712','Júlio','Cesar','1992/01/02','julio@bancodedados.com','M',2);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('98765412365','Marta','Santos','1990/10/12','marta@bancodedados.com','F',3);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('14523678956','Maria','Santos','1991/09/15','maria@bancodedados.com','F',4);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('12458763459','Jordania','Costa','1988/11/15','jordania@bancodedados.com','F',5);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('24578963145','Maria','Santana','1974/06/03','mariasant@bancodedados.com','F',6);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('12457896346','Maria','Santos','1989/10/12','mariasantos@bancodedados.com','F',7);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('01236547896','Joao','Martins','1975/03/15','joaomartins@bancodedados.com','M',8);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('01245789654','Thiago','Silva','1979/05/13','thiagosilva@bancodedados.com','M',9);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('01245634489','David','Luiz','1980/10/15','davidluiz@bancodedados.com','M',10);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('01245789635','Marcelo','Costa','1990/05/20','marcelocosta@bancodedados.com','M',11);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('14524862143','Henrique','Silva','1995/06/23','henriquesilva@bancodedados.com','M',12);

INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('14526751236','Marcela','Matos','1994/08/25','marcelamatos@bancodedados.com','F',13);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('02345698726','Jorge','Pereira','1996/09/19','jorgepereira@bancodedados.com','M',14);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('06547896542','Maria','José','1997/03/28','mariajose@bancodedados.com','F',15);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('01245687525','Joana','Santos','1974/06/28','joana@bancodedados.com','F',16);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('45789621452','Mariana','Santana','1978/07/05','mariana@bancodedados.com','F',17);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('00245783650','Diana','Silva','1979/08/08','diana@bancodedados.com','F',18);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('45789654126','Raquel','Lima','1977/07/07','raquel@bancodedados.com','F',19);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('01245368792','Diego','Costa','1978/05/29','diego@bancodedados.com','M',20);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('04512457896','Lucas','Nogueira','1979/04/04','lucas@bancodedados.com','M',21);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('12454789632','André','Silva','1995/02/21','andre@bancodedados.com','M',22);
INSERT INTO hospital.usuario (cpf, primeiroNome, sobrenome, dataNasc, email, sexo,
idPerfil)
VALUES
('00012457899','Antonio','Pereira','1999/03/28','lucas@bancodedados.com','M',23);
-- MORA --
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('23456789011',1);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('32165498712',2);

INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('98765412365',3);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('14523678956',3);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('12458763459',4);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('24578963145',5);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('12457896346',6);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('01236547896',7);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('01245789654',8);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('01245634489',9);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('01245789635',10);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('14524862143',9);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('14526751236',5);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('02345698726',8);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('06547896542',4);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('01245687525',11);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('01245368792',12);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('04512457896',13);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('12454789632',14);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('00245783650',15);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('00012457899',15);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('45789654126',15);
INSERT INTO hospital.mora (cpf, idEndereco) VALUES ('45789621452',15);

-- FONE --
INSERT INTO hospital.fone (fone, cpf) VALUES ('79123456985','23456789011');
INSERT INTO hospital.fone (fone, cpf) VALUES ('78145632789','32165498712');
INSERT INTO hospital.fone (fone, cpf) VALUES ('99874562156','98765412365');
INSERT INTO hospital.fone (fone, cpf) VALUES ('12453326584','14523678956');
INSERT INTO hospital.fone (fone, cpf) VALUES ('14247856324','12458763459');
INSERT INTO hospital.fone (fone, cpf) VALUES ('15151515151','24578963145');
INSERT INTO hospital.fone (fone, cpf) VALUES ('12121411516','12457896346');
INSERT INTO hospital.fone (fone, cpf) VALUES ('14171818151','01236547896');
INSERT INTO hospital.fone (fone, cpf) VALUES ('16131514171','01245789654');
INSERT INTO hospital.fone (fone, cpf) VALUES ('01020306050','01245634489');
INSERT INTO hospital.fone (fone, cpf) VALUES ('99778855665','01245789635');
INSERT INTO hospital.fone (fone, cpf) VALUES ('88996677112','14524862143');
INSERT INTO hospital.fone (fone, cpf) VALUES ('45656367686','14526751236');
INSERT INTO hospital.fone (fone, cpf) VALUES ('12151416181','02345698726');
INSERT INTO hospital.fone (fone, cpf) VALUES ('55778899663','06547896542');
-- ATENDENTE --
INSERT INTO hospital.atendente (cpf) VALUES ('06547896542');
INSERT INTO hospital.atendente (cpf) VALUES ('32165498712');
INSERT INTO hospital.atendente (cpf) VALUES ('98765412365');

-- ACOMPANHANTE --
INSERT INTO hospital.acompanhante (cpf) VALUES ('01245687525');

INSERT INTO hospital.acompanhante (cpf) VALUES ('45789621452');
INSERT INTO hospital.acompanhante (cpf) VALUES ('00245783650');
INSERT INTO hospital.acompanhante (cpf) VALUES ('45789654126');
INSERT INTO hospital.acompanhante (cpf) VALUES ('01245368792');
INSERT INTO hospital.acompanhante (cpf) VALUES ('04512457896');
INSERT INTO hospital.acompanhante (cpf) VALUES ('12454789632');
INSERT INTO hospital.acompanhante (cpf) VALUES ('00012457899');
-- PACIENTES --
INSERT INTO hospital.paciente(numProntuario, cpf, cartaoSUS, cpfAcomp)
VALUES ('P-0001', '23456789011','SUS00001','01245687525');
INSERT INTO hospital.paciente(numProntuario, cpf, cartaoSUS, cpfAcomp)
VALUES ('P-0002', '14523678956','SUS00002','45789621452');
INSERT INTO hospital.paciente(numProntuario, cpf, cartaoSUS, cpfAcomp)
VALUES ('P-0003', '12458763459','SUS00003','00245783650');
INSERT INTO hospital.paciente(numProntuario, cpf, cartaoSUS, cpfAcomp)
VALUES ('P-0005', '24578963145','SUS00004','01245368792');
INSERT INTO hospital.paciente(numProntuario, cpf, cartaoSUS, cpfAcomp)
VALUES ('P-0006', '12457896346','SUS00005','04512457896');
INSERT INTO hospital.paciente(numProntuario, cpf, cartaoSUS, cpfAcomp)
VALUES ('P-0007', '01236547896','SUS00006','12454789632');
INSERT INTO hospital.paciente(numProntuario, cpf, cartaoSUS, cpfAcomp)
VALUES ('P-0008', '01245789654','SUS00007','00012457899');
INSERT INTO hospital.paciente(numProntuario, cpf, cartaoSUS, cpfAcomp)
VALUES ('P-0009', '01245634489','SUS00008','45789654126');
-- HISTORICO --
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/06/23','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/05/12','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/04/05','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/02/20','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/01/23','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/06/09','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/06/15','removeu');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/02/23','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/07/09','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/06/18','modificou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/02/14','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/01/06','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/01/22','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/02/08','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/02/17','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/05/18','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/06/19','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/06/18','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/04/18','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/04/18','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/02/18','cadastrou');

INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/03/19','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/03/01','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/02/03','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/05/06','cadastrou');
INSERT INTO hospital.historico (dataCad, acao) VALUES ('2018/05/06','modificou');
-- ACESSO HISTORICO ATENDENTE PERFIL --
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(1, '06547896542',1);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(2, '06547896542',2);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(3, '06547896542',3);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(4, '06547896542',4);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(5, '06547896542',5);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(6, '06547896542',6);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(7, '06547896542',7);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(8, '06547896542',8);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(9, '06547896542',9);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(10, '06547896542',10);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(11, '98765412365',11);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(12, '98765412365',12);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(13, '98765412365',13);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(14, '98765412365',14);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(15, '98765412365',15);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(16, '98765412365',16);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(17, '98765412365',17);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(18, '98765412365',18);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(19, '98765412365',19);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(20, '98765412365',20);

INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(21, '32165498712',21);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(22, '32165498712',22);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(23, '32165498712',23);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(24, '32165498712',5);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(25, '32165498712',21);
INSERT INTO hospital.acesso_hist_atend_perf (idHistorico, cpfAtendente,idPerfil) VALUES
(26, '32165498712',23);
-- MEDICAMENTO --
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Glucobay','50mg','comprimido','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Acebrofilina','500mg','capsula','3 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Brismucol','250mg','frasco 100ml','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Filinar','350mg','frasco 100ml','3 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Acebrofilina','150mg','frasco 100ml','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Aceclofenaco','50mg','comprimido','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Aceflan','150mg','comprimido','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Proflam','250mg','capsula','3 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Advantan','350mg','comprimido','5 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Amoxilina','20mg','capsula','1 vez ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Depo-Provera','50mg','frasco 100ml','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Vita E','40mg','capsula','3 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Aspirina','50mg','frasco 200ml','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Vasclin','70mg','comprimido','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Prevencor','150mg','capsula','5 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Somalgin','100mg','capsula','6 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Somalgin Cardio','260mg','comprimido','2 vezes ao dia');

INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Antifebrin','40mg','comprimido','3 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Somalgin','400mg','capsula','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('AAS','30mg','comprimido','4 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Sonrisal limao','100mg','capsula','1 vez ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Dipirona','50mg','frasco 100ml','3 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Plastenan','50mg','capsula','1 vez ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Bonalen','60mg','comprimido','1 vez ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Ipsilon','50mg','comprimido','1 vez ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Eaca balsamico xpe','250mg','comprimido','2 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('D-Stress','50mg','comprimido','3 vezes ao dia');
INSERT INTO hospital.medicamento (nome, apresentacao, unidade, posologia) VALUES
('Omeprazol','450mg','capsula','1 vez ao dia');
-- MEDICOS --
INSERT INTO hospital.medico (cpf,numCRM, especialidade, salario)
VALUES ('01245789635','CRM010','Cirurgião', 18244);
INSERT INTO hospital.medico (cpf,numCRM, especialidade, salario)
VALUES ('14524862143','CRM011','Clínico Geral', 12000);
INSERT INTO hospital.medico (cpf,numCRM, especialidade, salario)
VALUES ('14526751236','CRM012','Clínico Geral', 8000);
INSERT INTO hospital.medico (cpf,numCRM, especialidade, salario)
VALUES ('02345698726','CRM013','Cirurgião', 15000);

-- MEDICOS DOCENTES
INSERT INTO hospital.medico_docente (idRegistro, titulacao) VALUES (1,'Doutor') ;
INSERT INTO hospital.medico_docente (idRegistro, titulacao) VALUES (2,'Assistente');
-- MÉDICOS RESIDENTE
INSERT INTO hospital.medico_residente (idRegistro, anoResidencia) VALUES (3,
'2015-01-01');
INSERT INTO hospital.medico_residente (idRegistro, anoResidencia) VALUES (4,
'2018-01-01');

-- CONSULTAS
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)

VALUES ('2018/02/21', '14:00','hospital', 1 , '06547896542', 1, 'P-0001');
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/22', '14:00', 'hospital', 1 ,'06547896542', 2,'P-0001');
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2017/01/01','14:00','hospital' ,1 ,'06547896542', 3,'P-0001' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2015/01/02','14:00','hospital' ,1 ,'06547896542', 4,'P-0001' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/03/22','14:00','hospital' ,1 ,'06547896542', 5,'P-0001' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/07/14','14:00','hospital' ,1 ,'06547896542', 6,'P-0001' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/07/15','14:00','hospital' ,1 ,'06547896542', 7,'P-0002' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/16','14:00','hospital' ,1 ,'06547896542', 8,'P-0002' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/04/01','14:00','hospital' ,1 ,'06547896542', 9,'P-0002' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/06/03','14:00','hospital' ,2 ,'06547896542', 10,'P-0002' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/07/03','14:00','hospital' ,2 ,'32165498712', 11,'P-0003' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/04/05','14:00','hospital' ,2 ,'32165498712', 12,'P-0003' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/02/08','14:00','hospital' ,2 ,'32165498712', 13,'P-0003' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/04/03','14:00','hospital' ,2 ,'32165498712', 14,'P-0003' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/04/04','14:00','hospital' ,2 ,'32165498712', 15,'P-0005' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/06/04','14:00','hospital' ,2 ,'32165498712', 16, 'P-0006');
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)

VALUES ('2018/04/23','14:00','hospital' ,3 ,'32165498712', 17,'P-0006' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/04/03','14:00','hospital' ,3 ,'32165498712', 18,'P-0006' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/04/03','14:00', 'domiciliária' ,3 ,'32165498712', 19,'P-0007' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/02','14:00', 'domiciliária' ,3 ,'32165498712', 20,'P-0007' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/02','14:00', 'domiciliária' ,3 ,'98765412365', 21,'P-0007' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/02','14:00', 'domiciliária' ,3 ,'98765412365', 22,'P-0008' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/02','14:00', 'domiciliária' ,3 ,'98765412365', 23,'P-0008' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/02','14:00', 'domiciliária' ,3 ,'98765412365', 24,'P-0008');
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/02','14:00', 'domiciliária' ,3 ,'98765412365', 25,'P-0008' );
INSERT INTO hospital.consulta (dataConsulta, horaConsulta, local, idRegistroMedico,
cpfAtendente, idHistorico, numProntuario)
VALUES ('2018/05/02','14:00', 'domiciliária' ,3 ,'98765412365', 26,'P-0009');
-- EXAMES
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Abdominal Total','Beber muita água',1,'P-0001');
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Hemograma','Em jejum',2,'P-0001');
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Glicose','Em jejum',2,'P-0001');
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Colesterol','Em jejum',2,'P-0003');
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Ureia','',1,'P-0005');
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('TGP','',1,'P-0005');

INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Fezes','',2,'P-0003');
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Gravidez','Em jejum',1,'P-0009');
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Mamografia','',1,'P-0009');
INSERT INTO hospital.exame (nome, recomendacao, idRegistroMedicoDocente,
numProntuario)
VALUES ('Ultra-sonografia','',2,'P-0005');
-- SOLICITAÇÕES DE EXAMES
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataPrevista,
dataHoraEmissao, statusPedido)
VALUES (1,1,'2018/10/10','2018/02/21 15:23:54','SOLICITADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataPrevista,
dataHoraEmissao, statusPedido)
VALUES (2,1,'2018/10/09','2018/05/22 14:30:54','SOLICITADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataPrevista,
dataHoraEmissao, statusPedido)
VALUES (9,4,'2018/10/10','2018/03/22 16:23:54','SOLICITADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataPrevista,
dataHoraEmissao, statusPedido)
VALUES (10,4,'2018/10/10','2018/07/14 15:53:54','SOLICITADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataRealizacao,
dataPrevista, dataHoraEmissao, statusPedido)
VALUES (3,1,'2018/05/14','2018/10/10','2018/07/15 16:10:54','REALIZADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataRealizacao,
dataPrevista, dataHoraEmissao, statusPedido)
VALUES (4,2,'2018/10/05','2018/10/10','2018/05/16 10:19:54','REALIZADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataRealizacao,
dataPrevista, dataHoraEmissao, statusPedido)
VALUES (5,2,'2018/10/05','2018/10/10','2018/01/04 10:20:54','REALIZADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataRealizacao,
dataPrevista, dataHoraEmissao, statusPedido)
VALUES (6,2,'2018/10/05','2018/10/10','2018/03/06 10:21:54','REALIZADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataRealizacao,
dataPrevista, dataHoraEmissao, statusPedido)
VALUES (7,3,'2018/10/06','2018/10/10','2018/02/05 14:22:54','REALIZADO');
INSERT INTO hospital.solicitacao_exame (idExame, idRegistroSolicitante, dataRealizacao,
dataPrevista, dataHoraEmissao, statusPedido)
VALUES (8,3,'2018/10/03','2018/10/10','2018/02/05 15:23:54','REALIZADO');
-- LAUDO
INSERT INTO hospital.laudo (dataEmissao, dataRevisao, statusLaudo,
idMedicoRevisorResidente, idMedicoEmissorDocente, idExame)

VALUES ('2018/06/10','2018/06/15','Entregue', 3, 1, 5);
INSERT INTO hospital.laudo (dataEmissao, dataRevisao, statusLaudo,
idMedicoRevisorResidente, idMedicoEmissorDocente, idExame)
VALUES ('2018/06/11','2018/06/15','Pronto', 3, 1, 6);
INSERT INTO hospital.laudo (dataEmissao, dataRevisao, statusLaudo,
idMedicoRevisorResidente, idMedicoEmissorDocente, idExame)
VALUES ('2018/05/11','2018/05/14','Pronto', 3, 2, 7);
INSERT INTO hospital.laudo (dataEmissao, dataRevisao, statusLaudo,
idMedicoRevisorResidente, idMedicoEmissorDocente, idExame)
VALUES ('2018/06/10','2018/06/14','Pronto', 4, 2, 8);
INSERT INTO hospital.laudo (dataEmissao, dataRevisao, statusLaudo,
idMedicoRevisorResidente, idMedicoEmissorDocente, idExame)
VALUES ('2018/06/16','2018/06/25','Pronto', 4, 1, 9);
INSERT INTO hospital.laudo (dataEmissao, dataRevisao, statusLaudo,
idMedicoRevisorResidente, idMedicoEmissorDocente, idExame)
VALUES ('2018/04/10','2018/05/10','Entregue', 4, 2, 10);
-- PRESCRIÇÕES MÉDICAS
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (1,10,'P-0001');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (8,9,'P-0002');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (9,5,'P-0002');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (2,4,'P-0001');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (17,5,'P-0006');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (19,16,'P-0007');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (1,28,'P-0001');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (8,20,'P-0002');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (22,8,'P-0008');
INSERT INTO hospital.prescricao (idConsultaPrescricao, idMedicamento, numProntuario)
VALUES (26,14,'P-0009');