DROP SCHEMA IF EXISTS touhou CASCADE;
CREATE SCHEMA touhou;

CREATE TABLE touhou.games(
	iteration smallint,
	subtitle varchar(30),
	jp_subtitle varchar(30),
	release_year smallint
);

CREATE TABLE touhou.characters(
	first_name varchar(20),
	last_name varchar(20)
);

INSERT INTO touhou.games VALUES (6, 'Embodiment of Scarlet Devil', 'Koumakyou', 2002);
INSERT INTO touhou.games VALUES (7, 'Perfect Cherry Blossom', 'Youyoumu', 2003);
INSERT INTO touhou.games VALUES (8, 'Imperishable Night', 'Eiyashou', 2004);

INSERT INTO touhou.characters VALUES ('Sakuya', 'Izayoi');
INSERT INTO touhou.characters VALUES ('Remilia', 'Scarlet');
INSERT INTO touhou.characters VALUES ('Flandre', 'Scarlet');
INSERT INTO touhou.characters VALUES ('Tewi', 'Inaba');
INSERT INTO touhou.characters VALUES ('Nitori', 'Kawashiro');
INSERT INTO touhou.characters VALUES ('Marisa', 'Kirisame');
INSERT INTO touhou.characters VALUES ('Satori', 'Komeiji');
INSERT INTO touhou.characters VALUES ('Hina', 'Kagiyama');