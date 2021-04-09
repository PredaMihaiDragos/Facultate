SET SERVEROUTPUT ON;

-- 1
DECLARE
    TYPE vector IS varray(5) OF emp_pmd.employee_id%type;
    coduri vector;
    salariu_vechi INTEGER;
    salariu_nou INTEGER;
BEGIN
    select employee_id bulk collect into coduri
    from (select employee_id from emp_pmd where commission_pct is null order by salary asc)
    where rownum <= 5;
    
    for i in 1..5 loop
        select salary into salariu_vechi from emp_pmd where employee_id = coduri(i);
        update emp_pmd set salary = salary * 1.05 where employee_id = coduri(i);
        select salary into salariu_nou from emp_pmd where employee_id = coduri(i);
        DBMS_OUTPUT.put_line('Salariu vechi: ' || salariu_vechi || ', Salariu nou: ' || salariu_nou);
    end loop;
    rollback;
END;

--2
CREATE OR REPLACE TYPE tip_orase_pmd IS TABLE OF VARCHAR(20); 
/ 
CREATE TABLE excursie_pmd (cod_excursie NUMBER(4), 
                            denumire VARCHAR2(20), 
                            status VARCHAR2(12));
                
ALTER TABLE excursie_pmd 
ADD (orase tip_orase_pmd) 
NESTED TABLE orase STORE AS tabel_orase_pmd;

--a
INSERT INTO excursie_pmd 
VALUES (1, 'ITALY TOUR', 'ANULAT', tip_orase_pmd('Milan', 'Verona', 'Bologna', 'Florence', 'Rome'));

INSERT INTO excursie_pmd 
VALUES (2, 'EUROPE', 'DISPONIBIL', tip_orase_pmd('Berlin', 'Prague', 'Vienna', 'Bratislava', 'Budapest'));

INSERT INTO excursie_pmd 
VALUES (3, 'SPAIN', 'DISPONIBIL', tip_orase_pmd('Madrid', 'Seville', 'Valencia', 'Granada', 'Barcelona'));

INSERT INTO excursie_pmd 
VALUES (4, 'FRANCE', 'DISPONIBIL', tip_orase_pmd('Marseille', 'Saint-Tropez', 'Cote Dazur', 'Nice'));

INSERT INTO excursie_pmd 
VALUES (5, 'GREECE', 'DISPONIBIL', tip_orase_pmd('Athens', 'Santorini', 'Mykonos'));

COMMIT;
SELECT *
FROM excursie_pmd;

--b
-- 
DECLARE  
    t tip_orase_pmd := tip_orase_pmd();
    nume_exc varchar2(20) := &exc;
BEGIN 
    SELECT orase
    INTO t
    FROM excursie_pmd
    WHERE denumire = nume_exc;
    
    t.extend;
    t(t.count):= &nume_oras;
    
    UPDATE excursie_pmd  
    SET orase = t
    WHERE denumire = nume_exc;
END;
/
ROLLBACK;

--
DECLARE  
    t1 tip_orase_pmd := tip_orase_pmd(); 
    t2 tip_orase_pmd := tip_orase_pmd();
    nume_exc varchar2(20) := &exc;
BEGIN 
    SELECT orase
    INTO t1
    FROM excursie_pmd
    WHERE denumire = nume_exc;
    
    FOR i IN 1..t1.count LOOP 
        t2.extend; 
        if i < 2 then 
            t2(i):= t1(i);
        end if;
        if i = 2 then
            t2(i) := &nume_oras;
            t2.extend;
            t2(i+1) := t1(i);
        end if;
        if i > 2 then
            t2(i+1) := t1(i);
        end if;
    END LOOP;
    
    UPDATE excursie_pmd  
    SET orase = t2
    WHERE denumire = nume_exc;
END;
/

ROLLBACK;

--
DECLARE  
    t tip_orase_pmd := tip_orase_pmd();
    nume_exc varchar2(20) := &exc;
    oras1 VARCHAR(20) := &un_oras;
    oras2 VARCHAR(20):= &alt_oras;
BEGIN 
    SELECT orase
    INTO t
    FROM excursie_pmd
    WHERE denumire = nume_exc;
    
    FOR i IN 1..t.count LOOP 
        if t(i) = oras1 then 
            t(i):= oras2;
        else
            if t(i) = oras2 then 
                t(i):= oras1;
            end if;
        end if;
    END LOOP;
    
    UPDATE excursie_pmd  
    SET orase = t
    WHERE denumire = nume_exc;
END;
/

ROLLBACK;

--
DECLARE  
    t tip_orase_pmd := tip_orase_pmd();
    t1 tip_orase_pmd := tip_orase_pmd();
    nume_exc varchar2(20) := &exc;
    oras varchar2(20) := &un_oras;
    j number := 1;
BEGIN 
    SELECT orase
    INTO t
    FROM excursie_pmd
    WHERE denumire = nume_exc;
    
    FOR i IN 1..t.count LOOP 
        if t(i) != oras then
            t1.extend;
            t1(j):= t(i);
            j := j + 1;
        end if;
    END LOOP;
    
    UPDATE excursie_pmd  
    SET orase = t1
    WHERE denumire = nume_exc;
END;
/

ROLLBACK;

-- c
DECLARE  
    t tip_orase_pmd := tip_orase_pmd();
    code number(4) := &cod_ex;
BEGIN 
    SELECT orase
    INTO t
    FROM excursie_pmd
    WHERE cod_excursie = code;
    DBMS_OUTPUT.PUT_LINE('Excursia contine urmatoarele ' || t.count || ' orase: ');
    FOR i IN 1..t.count LOOP 
        DBMS_OUTPUT.PUT_LINE(t(i) || ' ');
    END LOOP;
END;
/
--d
DECLARE  
    t tip_orase_pmd := tip_orase_pmd();
    TYPE codes IS TABLE OF NUMBER(4); 
    exc_codes codes := codes();
BEGIN 
    SELECT cod_excursie
    BULK COLLECT INTO exc_codes
    FROM excursie_pmd;
    
    FOR i IN 1..exc_codes.count LOOP
        SELECT orase
        INTO t
        FROM excursie_pmd
        WHERE cod_excursie = exc_codes(i);
        DBMS_OUTPUT.PUT_LINE('Excursia ' ||exc_codes(i) || ' contine urmatoarele ' || t.count || ' orase: ');
        FOR i IN 1..t.count LOOP 
            DBMS_OUTPUT.PUT_LINE(t(i) || ' ');
        END LOOP;
        t.delete;
    END LOOP;
END;
/

-- e
DECLARE  
    t tip_orase_pmd := tip_orase_pmd();
    TYPE codes IS TABLE OF NUMBER(4); 
    exc_codes codes := codes();
    exc_codes2 codes := codes();
    min_orase number := 1000;
    exc_code number(4);
    ind number := 1;
BEGIN
    SELECT cod_excursie
    BULK COLLECT INTO exc_codes
    FROM excursie_pmd;
    
    FOR i IN 1..exc_codes.count LOOP
        SELECT orase
        INTO t
        FROM excursie_pmd
        WHERE cod_excursie = exc_codes(i);
        if t.count < min_orase then
            min_orase := t.count;
        end if;
        t.delete;
    END LOOP;
    
    FOR i IN 1..exc_codes.count LOOP
        SELECT cod_excursie, orase
        INTO exc_code,  t
        FROM excursie_pmd
        WHERE cod_excursie = exc_codes(i);
        if t.count = min_orase then
            exc_codes2.extend;
            exc_codes2(ind) := exc_code;
            ind := ind + 1;
        end if;
        t.delete;
    END LOOP;
    
    FOR i IN 1..exc_codes2.count LOOP
        UPDATE excursie_pmd
        SET status = 'ANULAT'
        WHERE cod_excursie = exc_codes2(i);
    END LOOP;
END;
/
ROLLBACK;

select *
from excursie_pmd;

--3
CREATE OR REPLACE TYPE tip_orase2_pmd IS VARRAY(50) OF VARCHAR(20); 
/ 
CREATE TABLE excursie2_pmd (cod_excursie NUMBER(4), 
                            denumire VARCHAR2(20), 
                            status VARCHAR2(12),
                            orase tip_orase2_pmd);
-- a
INSERT INTO excursie2_pmd 
VALUES (1, 'ITALY TOUR', 'ANULAT', tip_orase2_pmd('Milan', 'Verona', 'Bologna', 'Florence', 'Rome'));

INSERT INTO excursie2_pmd 
VALUES (2, 'EUROPE', 'DISPONIBIL', tip_orase2_pmd('Berlin', 'Prague', 'Vienna', 'Bratislava', 'Budapest'));

INSERT INTO excursie2_pmd 
VALUES (3, 'SPAIN', 'DISPONIBIL', tip_orase2_pmd('Madrid', 'Seville', 'Valencia', 'Granada', 'Barcelona'));

INSERT INTO excursie2_pmd 
VALUES (4, 'FRANCE', 'DISPONIBIL', tip_orase2_pmd('Marseille', 'Saint-Tropez', 'Cote Dazur', 'Nice'));

INSERT INTO excursie2_pmd 
VALUES (5, 'GREECE', 'DISPONIBIL', tip_orase2_pmd('Athens', 'Santorini', 'Mykonos'));

COMMIT;

--b 
-- 
DECLARE  
    t tip_orase2_pmd := tip_orase2_pmd();
    nume_exc varchar2(20) := &exc;
BEGIN 
    SELECT orase
    INTO t
    FROM excursie2_pmd
    WHERE denumire = nume_exc;
    
    t.extend;
    t(t.count):= &nume_oras;
    
    UPDATE excursie2_pmd  
    SET orase = t
    WHERE denumire = nume_exc;
END;
/

ROLLBACK;

--
DECLARE  
    t1 tip_orase2_pmd := tip_orase2_pmd(); 
    t2 tip_orase2_pmd := tip_orase2_pmd();
    nume_exc varchar2(20) := &exc;
BEGIN 
    SELECT orase
    INTO t1
    FROM excursie2_pmd
    WHERE denumire = nume_exc;
    
    FOR i IN 1..t1.count LOOP 
        t2.extend; 
        if i < 2 then 
            t2(i):= t1(i);
        end if;
        if i = 2 then
            t2(i) := &nume_oras;
            t2.extend;
            t2(i+1) := t1(i);
        end if;
        if i > 2 then
            t2(i+1) := t1(i);
        end if;
    END LOOP;
    
    UPDATE excursie2_pmd  
    SET orase = t2
    WHERE denumire = nume_exc;
END;
/

ROLLBACK;

--
DECLARE  
    t tip_orase2_pmd := tip_orase2_pmd();
    nume_exc varchar2(20) := &exc;
    oras1 VARCHAR(20) := &un_oras;
    oras2 VARCHAR(20):= &alt_oras;
BEGIN 
    SELECT orase
    INTO t
    FROM excursie2_pmd
    WHERE denumire = nume_exc;
    
    FOR i IN 1..t.count LOOP 
        if t(i) = oras1 then 
            t(i):= oras2;
        else
            if t(i) = oras2 then 
                t(i):= oras1;
            end if;
        end if;
    END LOOP;
    
    UPDATE excursie2_pmd  
    SET orase = t
    WHERE denumire = nume_exc;
END;
/

ROLLBACK;

--
DECLARE  
    t tip_orase2_pmd := tip_orase2_pmd();
    t1 tip_orase2_pmd := tip_orase2_pmd();
    nume_exc varchar2(20) := &exc;
    oras varchar2(20) := &un_oras;
    j number := 1;
BEGIN 
    SELECT orase
    INTO t
    FROM excursie2_pmd
    WHERE denumire = nume_exc;
    
    FOR i IN 1..t.count LOOP 
        if t(i) != oras then
            t1.extend;
            t1(j):= t(i);
            j := j + 1;
        end if;
    END LOOP;
    
    UPDATE excursie2_pmd  
    SET orase = t1
    WHERE denumire = nume_exc;
END;
/

ROLLBACK;

-- c
DECLARE  
    t tip_orase2_pmd := tip_orase2_pmd();
    code number(4) := &cod_ex;
BEGIN 
    SELECT orase
    INTO t
    FROM excursie2_pmd
    WHERE cod_excursie = code;
    DBMS_OUTPUT.PUT_LINE('Excursia contine urmatoarele ' || t.count || ' orase: ');
    FOR i IN 1..t.count LOOP 
        DBMS_OUTPUT.PUT_LINE(t(i) || ' ');
    END LOOP;
END;
/

--d
DECLARE  
    t tip_orase2_pmd := tip_orase2_pmd();
    TYPE codes IS TABLE OF NUMBER(4); 
    exc_codes codes := codes();
BEGIN 
    SELECT cod_excursie
    BULK COLLECT INTO exc_codes
    FROM excursie2_pmd;
    
    FOR i IN 1..exc_codes.count LOOP
        SELECT orase
        INTO t
        FROM excursie2_pmd
        WHERE cod_excursie = exc_codes(i);
        DBMS_OUTPUT.PUT_LINE('Excursia ' ||exc_codes(i) || ' contine urmatoarele ' || t.count || ' orase: ');
        FOR i IN 1..t.count LOOP 
            DBMS_OUTPUT.PUT_LINE(t(i) || ' ');
        END LOOP;
        t.delete;
    END LOOP;
END;
/

-- e
DECLARE  
    t tip_orase2_pmd := tip_orase2_pmd();
    TYPE codes IS TABLE OF NUMBER(4); 
    exc_codes codes := codes();
    exc_codes2 codes := codes();
    min_orase number := 1000;
    exc_code number(4);
    ind number := 1;
BEGIN
    SELECT cod_excursie
    BULK COLLECT INTO exc_codes
    FROM excursie2_pmd;
    
    FOR i IN 1..exc_codes.count LOOP
        SELECT orase
        INTO t
        FROM excursie2_pmd
        WHERE cod_excursie = exc_codes(i);
        if t.count < min_orase then
            min_orase := t.count;
        end if;
        t.delete;
    END LOOP;
    
    FOR i IN 1..exc_codes.count LOOP
        SELECT cod_excursie, orase
        INTO exc_code,  t
        FROM excursie2_pmd
        WHERE cod_excursie = exc_codes(i);
        if t.count = min_orase then
            exc_codes2.extend;
            exc_codes2(ind) := exc_code;
            ind := ind + 1;
        end if;
        t.delete;
    END LOOP;
    
    FOR i IN 1..exc_codes2.count LOOP
        UPDATE excursie2_pmd
        SET status = 'ANULAT'
        WHERE cod_excursie = exc_codes2(i);
    END LOOP;
END;
/
ROLLBACK;

select * from excursie2_pmd;