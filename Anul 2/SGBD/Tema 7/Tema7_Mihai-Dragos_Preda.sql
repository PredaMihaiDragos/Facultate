-- 3

CREATE OR REPLACE FUNCTION f3_pmd (oras locations.city%TYPE DEFAULT 'Seattle') RETURN Number IS v_num Number;

v_2jobs NUMBER;

BEGIN
SELECT count(*) INTO v_num
FROM locations
WHERE lower(city) like lower(oras);

if(v_num = 0) THEN
INSERT INTO info_pmd
VALUES(USER,SYSDATE,'select count(*)',v_num,'NU EXISTA ORAS');

ELSE
SELECT count(employee_id) INTO v_num
FROM emp_pmd
JOIN departments USING(department_id)
JOIN locations USING(location_id)
WHERE lower(city) like lower(oras);

if(v_num = 0) THEN
INSERT INTO info_pmd
VALUES(USER,SYSDATE,'select count(employee_id)',v_num,'NU EXISTA ANGAJATI IN ORAS');

ELSE
SELECT count(count(*)) INTO v_2jobs
FROM emp_pmd
JOIN departments USING(department_id)
JOIN locations USING(location_id)
JOIN job_history USING(employee_id)
WHERE lower(city) like lower(oras)
GROUP BY employee_id
HAVING count(job_history.job_id) >= 2;


INSERT INTO info_pmd
VALUES(USER,SYSDATE,'select count(count(*))',v_2jobs,'SUCCESS');

END IF;

END IF;

RETURN v_2jobs;

END f3_pmd;

-- 4

CREATE TABLE info_pmd(UTILIZATOR Varchar(25),
                                 DATA DATE, COMANDA varchar(25),
                                                    NR_LINII NUMBER(5, 0),
                                                             EROARE VARCHAR(25));


ALTER TABLE info_pmd MODIFY UTILIZATOR VARCHAR(25);


CREATE OR REPLACE PROCEDURE pb4 (p_cod employees.employee_id%TYPE DEFAULT 100) IS v_nr number(5);

v_nr_linii number;

BEGIN
SELECT COUNT (*) INTO v_nr
FROM emp_pmd
WHERE employee_id = p_cod;

IF v_nr = 0 THEN
INSERT INTO info_pmd
VALUES(USER, sysdate, 'nothing', v_nr, 'Nu exista manager cu codul dat!');

ELSE
UPDATE emp_pmd
SET salary = salary* 1.1
WHERE manager_id in
    (SELECT employee_id
     FROM employees START WITH employee_id = p_cod CONNECT BY
     PRIOR employee_id = manager_id);

v_nr_linii := SQL%ROWCOUNT;


ROLLBACK;


INSERT INTO info_pmd
VALUES(USER, sysdate, 'update', v_nr_linii, 'no error');

END IF;

END pb4;

/ BEGIN pb4;

END;

/
SELECT *
FROM info_pmd;

-- 5

CREATE OR REPLACE PROCEDURE informatii_pmd
IS
    v_utilizator    info_ari.utilizator%TYPE;
    v_ans           NUMBER;
    v_err           VARCHAR2(100);
    v_nr_linii      NUMBER;
    v_zi            NUMBER;
BEGIN
    SELECT user INTO v_utilizator from dual;
    
    FOR dep IN (SELECT *
                FROM departments) LOOP
        DBMS_OUTPUT.PUT_LINE('Depertament ' || dep.department_name || ':');
        
        SELECT COUNT(*)
            INTO v_nr_linii
            FROM employees
            WHERE department_id = dep.department_id;
        
        SELECT zi
            INTO v_zi
            FROM (SELECT EXTRACT (DAY FROM hire_date) zi, COUNT(*)
                  FROM employees e
                  WHERE e.department_id = dep.department_id
                  GROUP BY EXTRACT(DAY FROM hire_date)
                  ORDER BY COUNT(*) DESC)
            WHERE rownum = 1;
        
        DBMS_OUTPUT.PUT_LINE('Zi maxima: ' || v_zi);
        
        FOR e IN (SELECT * 
                  FROM employees
                  WHERE department_id = dep.department_id) LOOP
            DBMS_OUTPUT.PUT_LINE('Nume: ' || e.first_name || ', salariu: ' || e.salary);
        END LOOP;
    END LOOP;
END;
/

EXECUTE informatii_pmd;