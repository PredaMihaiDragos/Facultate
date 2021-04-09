-- users
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (1, 'predamihaidragos@gmail.com', 'Mihai-Dragos Preda', 
        '$2y$12$1zeZvb80.c4lK/BEmRa4U.lqS09WyBuKEdRT/ejUkmjyG/5qqDMPO',
        4, 0, TO_DATE('2020-03-15', 'yyyy-mm-dd'), null, '0740764496');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (2, 'mpreda@google.com', 'Mihai Preda Jrr', 
        '$2y$12$xvsMfGI.IwZHqs1AUcJeAumCefogcXmPX9a3ALtpsbs7yShI8teja',
        0, 1, TO_DATE('2019-03-15', 'yyyy-mm-dd'), 1, '0740496764');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (3, 'ionmoromete@yahoo.ro', 'Moromete Ion', 
        '$2y$12$E4bWTnn0hheeFnLTauq/Gesu3eZjyqpxEcbAyLiKzGGCQNyXH0auu',
        3, 0, TO_DATE('1930-04-26', 'yyyy-mm-dd'), null, '0754231765');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (4, 'paraschiv@hotmail.com', 'Paraschiv Moromete', 
        '$2y$12$rbsPx7bfQeC.qkvMN0EqfOosT.FndFwh3ELVb3PTrHqji00jon4Y2',
        5, 0, TO_DATE('1932-07-24', 'yyyy-mm-dd'), 3, '0740193200');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (5, 'achim@hotmail.com', 'Achim Moromete', 
        '$2y$12$rPSlFzOaVbYSFp8H09nFtec.rNMjFLA/2tbtAdSRAJs4AqEBB5p8i',
        1, 0, TO_DATE('1934-08-12', 'yyyy-mm-dd'), 3, '0757214302');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (6, 'stefan@gheorghidiu.com', 'Stefan Gheorghidiu', 
        '$2y$12$mWeeqm.wIme7zT9e3CcjSO7/Ba/KlMdW6/F3GBYz8CXFEjH9l.Wg6',
        2, 1, TO_DATE('1915-08-01', 'yyyy-mm-dd'), null, '0745123546');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (7, 'ela@gheorghidiu.com', 'Ela Gheorghidiu', 
        '$2y$12$/4mrGbr2M19If8nnNtcQpeLdj6IXGtaBzBC48s.W0VGlboIxHfFGS',
        5, 0, TO_DATE('1938-07-08', 'yyyy-mm-dd'), 6, '0745712346');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (8, 'omarculescu@pascalopol.com', 'Otilia Marculescu', 
        '$2y$12$WBHiqwGOaFOiv/tr8KG2tOkqjsSDzeWvM7ToGfxPEWq.pV54dHzXe',
        12, 0, TO_DATE('1939-08-07', 'yyyy-mm-dd'), null, '0789214579');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (9, 'fsima@pascalopol.com', 'Felix Sima', 
        '$2y$12$ZUkqlnYdk59AasbcYLecVek3.iwraN2cE9ZiGXKr.dRC0CzKb7jES',
        15, 1, TO_DATE('1938-08-15', 'yyyy-mm-dd'), 8, '0774124367');
        
INSERT INTO users(ID, EMAIL, NAME, PASSWORD, LESSONS, ACTIVE, CONFIRMED_AT, REFERRED_BY, PHONE)
VALUES (10, 'harapalb@regatulverde.com', 'Harap Alb', 
        '$2y$12$2BQa9SuoSIssj/K66z11.uYPTzvm6d7oNYj/PjfHmZwnLYd87Zgf.',
        2, 0, TO_DATE('2102-12-01', 'yyyy-mm-dd'), null, '0747854124');
        
-- roles
INSERT INTO role(ID, NAME, DESCRIPTION)
VALUES (1, 'Administrator', 'Se ocupa de buna functionare a site-ului');

INSERT INTO role(ID, NAME, DESCRIPTION)
VALUES (2, 'Moderator', 'Se ocupa de continutul de pe site.');

INSERT INTO role(ID, NAME, DESCRIPTION)
VALUES (3, 'Profesor', 'Se ocupa de tinutul lectiilor pe site.');

INSERT INTO role(ID, NAME, DESCRIPTION)
VALUES (4, 'Elev', 'Un utilizator capata statutul de elev dupa prima lectie.');

INSERT INTO role(ID, NAME, DESCRIPTION)
VALUES (5, 'Utilizator', 'Un utilizator normal.');

-- roles_users
INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(1, 1);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(2, 1);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(1, 2);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(2, 2);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(1, 3);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(3, 3);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(6, 3);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(10, 2);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(4, 4);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(5, 4);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(7, 4);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(8, 4);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(9, 4);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(10, 4);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(3, 5);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(4, 5);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(5, 5);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(6, 5);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(7, 5);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(8, 5);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(9, 5);

INSERT INTO roles_users(USERS_ID, ROLE_ID)
VALUES(10, 5);

-- persoana_juridica
INSERT INTO persoana_juridica(ID, USER_ID, NUME_FIRMA, COD_UNIC, BANCA, IBAN, ADRESA_FIRMA, REG_COM)
VALUES(1, 1, 'ITOIT MEDITATII SRL', '43192694', 'Garanti Bank', 'RO63UGBI0000632008603RON', 'Strada 1907, nr 47, Alexandria, Teleorman', 'J34/540/2020');

INSERT INTO persoana_juridica(ID, USER_ID, NUME_FIRMA, COD_UNIC, BANCA, IBAN, ADRESA_FIRMA, REG_COM)
VALUES(2, 3, 'GOOGLE BUCHAREST SRL', '23047266', 'Citi Bank', 'RO47UGBI0000247512349RON', 'Str. C. A. Rosetti 17 A, Sectorul 2, Bucuresti', 'J40/357/2008');

INSERT INTO persoana_juridica(ID, USER_ID, NUME_FIRMA, COD_UNIC, BANCA, IBAN, ADRESA_FIRMA, REG_COM)
VALUES(3, 5, 'ORACLE ROMANIA SRL', '15058256', 'Citi Bank', 'RO47UGBI0000145478568RON', 'Str. Pipera 43 B, Sectorul 2, Bucuresti', 'J40/12387/2002');

INSERT INTO persoana_juridica(ID, USER_ID, NUME_FIRMA, COD_UNIC, BANCA, IBAN, ADRESA_FIRMA, REG_COM)
VALUES(4, 6, 'AMAZON COM SRL', '14376650', 'Raifeissen Bank', 'RO47UGBI0000474231245RON', 'Str. Cpt. Mircea Vasilescu 13 C, Sectorul 4, Bucuresti', 'J40/73/2002');

INSERT INTO persoana_juridica(ID, USER_ID, NUME_FIRMA, COD_UNIC, BANCA, IBAN, ADRESA_FIRMA, REG_COM)
VALUES(5, 10, 'UIPATH SRL', '34737997', 'ING Bank', 'RO47UGBI0000457854126RON', 'Str. Vasile Alecsandri 4 Si 11 C, Sectorul 1, Bucuresti', 'J40/8216/2015');

-- persoana_fizica
INSERT INTO persoana_fizica(ID, USER_ID, ADRESA, LOCALITATE, JUDET)
VALUES(1, 1, 'Strada 1907, nr 47', 'Alexandria', 'Teleorman');

INSERT INTO persoana_fizica(ID, USER_ID, ADRESA, LOCALITATE, JUDET)
VALUES(2, 2, 'Strada Dunarii, nr 87', 'Slatina', 'Olt'); 

INSERT INTO persoana_fizica(ID, USER_ID, ADRESA, LOCALITATE, JUDET)
VALUES(3, 4, 'Strada Ceahlaul, nr 45', 'Bucuresti', 'Bucuresti'); 

INSERT INTO persoana_fizica(ID, USER_ID, ADRESA, LOCALITATE, JUDET)
VALUES(4, 7, 'Strada Lotrioara, nr 3', 'Brasov', 'Brasov'); 

INSERT INTO persoana_fizica(ID, USER_ID, ADRESA, LOCALITATE, JUDET)
VALUES(5, 8, 'Strada George Valsan, nr 48', 'Timisoara', 'Timisoara'); 
        
-- future_mail
INSERT INTO future_mail(ID, SUBJECT, RECIPENT, HTML_CONTENT, SEND_DATE)
VALUES(1, 'Nu ai inceput inca?', 'predamihaidragos@gmail.com', '<html>Incepe acum</html>', TO_DATE('2020-12-28 12:00:00', 'yyyy-mm-dd HH24:MI:SS'));

INSERT INTO future_mail(ID, SUBJECT, RECIPENT, HTML_CONTENT, SEND_DATE)
VALUES(2, 'Ai o lectie in 24h!', 'ionmoromete@yahoo.ro', '<html>Reminder</html>', TO_DATE('1930-12-12 14:00:00', 'yyyy-mm-dd HH24:MI:SS'));

INSERT INTO future_mail(ID, SUBJECT, RECIPENT, HTML_CONTENT, SEND_DATE)
VALUES(3, 'Ai o lectie in 24h!', 'stefan@gheorghidiu.com', '<html>Reminder</html>', TO_DATE('1954-09-12 18:00:00', 'yyyy-mm-dd HH24:MI:SS'));

INSERT INTO future_mail(ID, SUBJECT, RECIPENT, HTML_CONTENT, SEND_DATE)
VALUES(4, 'Ai o lectie in 24h!', 'omarculescu@pascalopol.com', '<html>Reminder</html>', TO_DATE('1939-01-11 10:00:00', 'yyyy-mm-dd HH24:MI:SS'));

INSERT INTO future_mail(ID, SUBJECT, RECIPENT, HTML_CONTENT, SEND_DATE)
VALUES(5, 'Ai o lectie in 24h!', 'harapalb@regatulverde.com', '<html>Reminder</html>', TO_DATE('2101-01-15 12:00:00', 'yyyy-mm-dd HH24:MI:SS'));

-- factura
INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 1, TO_DATE('1939-08-07', 'yyyy-mm-dd'), 459697848);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 2, TO_DATE('1945-09-02', 'yyyy-mm-dd'), 587668756);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 3, TO_DATE('1968-04-15', 'yyyy-mm-dd'), 575174752);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 4, TO_DATE('1914-02-05', 'yyyy-mm-dd'), 578578587);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 5, TO_DATE('1968-09-25', 'yyyy-mm-dd'), 657867857);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 6, TO_DATE('1924-12-06', 'yyyy-mm-dd'), 578568767);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 7, TO_DATE('2016-07-24', 'yyyy-mm-dd'), 578578785);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 8, TO_DATE('2020-11-03', 'yyyy-mm-dd'), 357445535);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 9, TO_DATE('2018-06-14', 'yyyy-mm-dd'), 213213212);

INSERT INTO factura(SERIE, ID, DATA, TRANSACTION_ID)
VALUES('IT', 10, TO_DATE('2019-09-01', 'yyyy-mm-dd'), 345425441);

-- lesson
INSERT INTO lesson(ID, START_DATE, END_DATE, SUBJECT, PROFESSOR_GRADE, STUDENT_GRADE, PROFESSOR_ID, STUDENT_ID,
                   STUDENT_FEEDBACK, PROFESSOR_FEEDBACK, REMINDER_ID)
VALUES(1, TO_DATE('2020-12-27 12:00:00', 'yyyy-mm-dd HH24:MI:SS'), TO_DATE('2020-12-27 14:00:00', 'yyyy-mm-dd HH24:MI:SS'),
      'Cautare binara', 8.6, 9.7, 1, 3, 'Totul foarte bine. Am inteles tot.', 'Elevul s-a descurcat bine.', null);
      
INSERT INTO lesson(ID, START_DATE, END_DATE, SUBJECT, PROFESSOR_GRADE, STUDENT_GRADE, PROFESSOR_ID, STUDENT_ID,
                   STUDENT_FEEDBACK, PROFESSOR_FEEDBACK, REMINDER_ID)
VALUES(2, TO_DATE('1930-12-13 14:00:00', 'yyyy-mm-dd HH24:MI:SS'), TO_DATE('1930-12-13 16:00:00', 'yyyy-mm-dd HH24:MI:SS'),
      null, null, null, 1, 3, null, null, 2);
      
INSERT INTO lesson(ID, START_DATE, END_DATE, SUBJECT, PROFESSOR_GRADE, STUDENT_GRADE, PROFESSOR_ID, STUDENT_ID,
                   STUDENT_FEEDBACK, PROFESSOR_FEEDBACK, REMINDER_ID)
VALUES(3, TO_DATE('1954-09-13 18:00:00', 'yyyy-mm-dd HH24:MI:SS'), TO_DATE('1954-09-13 20:00:00', 'yyyy-mm-dd HH24:MI:SS'),
      null, null, null, 3, 6, null, null, 3);
      
INSERT INTO lesson(ID, START_DATE, END_DATE, SUBJECT, PROFESSOR_GRADE, STUDENT_GRADE, PROFESSOR_ID, STUDENT_ID,
                   STUDENT_FEEDBACK, PROFESSOR_FEEDBACK, REMINDER_ID)
VALUES(4, TO_DATE('1939-01-12 10:00:00', 'yyyy-mm-dd HH24:MI:SS'), TO_DATE('1939-01-12 12:00:00', 'yyyy-mm-dd HH24:MI:SS'),
      null, null, null, 6, 8, null, null, 4);
      
INSERT INTO lesson(ID, START_DATE, END_DATE, SUBJECT, PROFESSOR_GRADE, STUDENT_GRADE, PROFESSOR_ID, STUDENT_ID,
                   STUDENT_FEEDBACK, PROFESSOR_FEEDBACK, REMINDER_ID)
VALUES(5, TO_DATE('2101-01-16 12:00:00', 'yyyy-mm-dd HH24:MI:SS'), TO_DATE('2101-01-16 14:00:00', 'yyyy-mm-dd HH24:MI:SS'),
      null, null, null, 1, 10, null, null, 5);
