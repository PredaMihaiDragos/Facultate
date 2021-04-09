DROP TABLE users;
CREATE TABLE users
(
    id integer NOT NULL,
    email varchar(120) NOT NULL,
    name varchar(35) NOT NULL,
    password varchar(60),
    lessons integer,
    active integer,
    confirmed_at date,
    referred_by integer,
    phone varchar(15),
    CONSTRAINT users_pkey PRIMARY KEY (id),
    CONSTRAINT users_referred_fkey
    FOREIGN KEY (referred_by)
    REFERENCES users(id)
);

DROP TABLE role;
CREATE TABLE role
(
    id integer NOT NULL,
    name varchar(80),
    description varchar(255),
    CONSTRAINT role_pkey PRIMARY KEY (id),
    CONSTRAINT "uniqueName" UNIQUE (name)
);

DROP TABLE roles_users;
CREATE TABLE roles_users
(
    users_id integer,
    role_id integer,
    CONSTRAINT "roleIdFK" FOREIGN KEY (role_id)
        REFERENCES role (id)
        ON DELETE SET NULL,
    CONSTRAINT "userIdFK" FOREIGN KEY (users_id)
        REFERENCES users (id)
        ON DELETE SET NULL
);

DROP TABLE future_mail;
CREATE TABLE future_mail
(
    id integer NOT NULL,
    subject varchar(120),
    recipent varchar(120),
    html_content varchar(4000),
    send_date date,
    CONSTRAINT future_mail_pkey PRIMARY KEY (id)
);

DROP TABLE lesson;
CREATE TABLE lesson
(
    id integer NOT NULL,
    start_date date,
    end_date date,
    subject varchar(75),
    professor_grade real,
    student_grade real,
    professor_id integer,
    student_id integer,
    student_feedback varchar(4000),
    professor_feedback varchar(4000),
    reminder_id integer, -- daca lectia se anuleaza, trebuie sa stergem si reminder-ul
    CONSTRAINT lesson_pkey PRIMARY KEY (id),
    CONSTRAINT lesson_professor_id_fkey FOREIGN KEY (professor_id)
        REFERENCES users (id)
        ON DELETE SET NULL,
    CONSTRAINT lesson_student_id_fkey FOREIGN KEY (student_id)
        REFERENCES users (id)
        ON DELETE SET NULL,
    CONSTRAINT lesson_reminder_fkey FOREIGN KEY (reminder_id)
        REFERENCES future_mail (id)
        ON DELETE SET NULL
);

DROP TABLE factura;
CREATE TABLE factura
(
    serie varchar(6),
    id integer NOT NULL,
    data date,
    transaction_id integer,
    CONSTRAINT factura_pkey PRIMARY KEY (serie, id)
)

DROP TABLE persoana_juridica;
CREATE TABLE persoana_juridica
(
    id integer NOT NULL,
    user_id integer,
    nume_firma varchar(50),
    cod_unic varchar(20),
    banca varchar(50),
    IBAN varchar(30),
    adresa_firma varchar(100),
    reg_com varchar(50),
    CONSTRAINT persoana_juridica_pkey PRIMARY KEY (id),
    CONSTRAINT persoana_juridica_user_id_fkey FOREIGN KEY (user_id)
        REFERENCES users (id)
        ON DELETE CASCADE
)

DROP TABLE persoana_fizica;
CREATE TABLE persoana_fizica
(
    id integer NOT NULL,
    user_id integer,
    adresa varchar(100),
    localitate varchar(20),
    judet varchar(20),
    CONSTRAINT persoana_fizica_pkey PRIMARY KEY (id),
    CONSTRAINT persoana_fizica_user_id_fkey FOREIGN KEY (user_id)
        REFERENCES users (id)
        ON DELETE CASCADE
)
