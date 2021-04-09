SET SERVEROUTPUT ON;

--1. a

DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curr jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curr;
                    nr_joburi NUMBER;
    v_job_title jobs.job_title%TYPE;
    v_f_name employees.first_name%TYPE;
    v_l_name employees.last_name%TYPE;
    v_salary employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    cnt NUMBER(5);
BEGIN
    SELECT COUNT(*)
    INTO nr_joburi
    FROM jobs;
    
    joburi.EXTEND(nr_joburi);
    
    SELECT j.job_id
    BULK COLLECT INTO joburi
    FROM jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO v_job_title
        FROM jobs j
        WHERE j.job_id = joburi(i);
        DBMS_OUTPUT.PUT_LINE(v_job_title);
        cnt := 0;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO v_f_name, v_l_name, v_salary;
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(v_f_name || ' ' || v_l_name || ' ' || v_salary);
            cnt := cnt + 1;
        END LOOP;
        CLOSE c;
        IF cnt = 0 THEN 
            DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat.');
        END IF;
        DBMS_OUTPUT.NEW_LINE();
    END LOOP;
END;
/
    
--1. b
DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curr jobs.job_id%TYPE)IS 
        SELECT e.last_name l_name, e.first_name f_name, e.salary salary
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curr;
                    nr_joburi NUMBER;
    v_job_title jobs.job_title%TYPE;
    v_f_name employees.first_name%TYPE;
    v_l_name employees.last_name%TYPE;
    v_salary employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    cnt NUMBER(5);
BEGIN
    SELECT COUNT(*)
    INTO nr_joburi
    FROM jobs;
    
    joburi.EXTEND(nr_joburi);
    
    SELECT j.job_id
    BULK COLLECT INTO joburi
    FROM jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO v_job_title
        FROM jobs j
        WHERE j.job_id = joburi(i);
        DBMS_OUTPUT.PUT_LINE(v_job_title);
        cnt := 0;
        
        FOR j IN c(joburi(i)) LOOP
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(j.f_name || ' ' || j.l_name || ' ' || j.salary);
            cnt := cnt + 1;
        END LOOP;
        IF cnt = 0 THEN 
            DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat.');
        END IF;
        DBMS_OUTPUT.NEW_LINE();
    END LOOP;
END;
/
    
--1. c    
    
    DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curr jobs.job_id%TYPE)IS 
        SELECT e.last_name l_name, e.first_name f_name, e.salary salary
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curr;
    nr_joburi NUMBER;
    v_job_title jobs.job_title%TYPE;
    v_f_name employees.first_name%TYPE;
    v_l_name employees.last_name%TYPE;
    v_salary employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    cnt NUMBER(5);
BEGIN
    SELECT COUNT(*)
    INTO nr_joburi
    FROM jobs;
    
    joburi.EXTEND(nr_joburi);
    
    SELECT j.job_id
    BULK COLLECT INTO joburi
    FROM jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO v_job_title
        FROM jobs j
        WHERE j.job_id = joburi(i);
        DBMS_OUTPUT.PUT_LINE(v_job_title);
        cnt := 0;
        
        FOR j IN (SELECT e.last_name l_name, e.first_name f_name, e.salary salary
                    FROM employees e, jobs j
                    WHERE j.job_id = e.job_id and
                    j.job_id = joburi(i)) 
        LOOP
            DBMS_OUTPUT.PUT_LINE(j.f_name || ' ' || j.l_name || ' ' || j.salary);
            cnt := cnt + 1;
        END LOOP;
        IF cnt = 0 THEN 
            DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat.');
        END IF;
        DBMS_OUTPUT.NEW_LINE();
    END LOOP;
END;
/


--1. d

DECLARE 
    TYPE refcursor IS REF CURSOR;
    CURSOR c IS 
        SELECT j2.job_title, CURSOR
            (SELECT e.last_name, e.first_name, e.salary
            FROM employees e, jobs j
            WHERE j.job_id = e.job_id and
                    j.job_id = j2.job_id)
        FROM jobs j2;
    v_job_title jobs.job_title%TYPE;
    v_f_name employees.first_name%TYPE;
    v_l_name employees.last_name%TYPE;
    v_salary employees.salary%TYPE;
    v_job jobs.job_title%TYPE;
    v_cursor refcursor;
    cnt NUMBER(5);
BEGIN
    OPEN c;
    LOOP
        FETCH c INTO v_job, v_cursor;
        EXIT WHEN c%NOTFOUND;
        DBMS_OUTPUT.PUT_LINE(v_job);
        LOOP 
            FETCH v_cursor INTO v_f_name, v_l_name, v_salary;
            EXIT WHEN v_cursor%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(v_f_name || ' ' || v_l_name || ' ' || v_salary);
        END LOOP;
        
        DBMS_OUTPUT.NEW_LINE();

    END LOOP;
    
END;
/


--2.

DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curr jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curr;
                    nr_joburi NUMBER;
    v_job_title jobs.job_title%TYPE;
    v_f_name employees.first_name%TYPE;
    v_l_name employees.last_name%TYPE;
    v_salary employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    v_nr_salariati NUMBER(5);
    cnt NUMBER(5);
    v_sal_tot_job NUMBER(8,2);
    v_sal_med_job NUMBER(8,2);
    v_sal_tot NUMBER(10,2) := 0;
    v_sal_med NUMBER(10,2) := 0;
    v_cnt_tot NUMBER(5) := 0;
BEGIN
    SELECT COUNT(*)
    INTO nr_joburi
    FROM jobs;
    
    joburi.EXTEND(nr_joburi);
    
    SELECT j.job_id
    BULK COLLECT INTO joburi
    FROM jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO v_job_title
        FROM jobs j
        WHERE j.job_id = joburi(i);     
        cnt := 0;
        v_sal_tot_job := 0;
        
        SELECT count(*)
        INTO v_nr_salariati
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id and
            j.job_id = joburi(i);
        
        IF v_nr_salariati = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu lucreaza niciun angajat pe postul de ' || v_job_title);
        ELSIF v_nr_salariati = 1 THEN
            DBMS_OUTPUT.PUT_LINE('Un angajat lucreaza ca ' || v_job_title);
        ELSIF v_nr_salariati < 20 THEN
            DBMS_OUTPUT.PUT_LINE(v_nr_salariati || ' angajati lucreaza ca ' || v_job_title);
        ELSE
            DBMS_OUTPUT.PUT_LINE(v_nr_salariati || ' de angajati lucreaza ca ' || v_job_title);
        END IF;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO v_f_name, v_l_name, v_salary;
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(cnt + 1 || ' ' || v_f_name || ' ' || v_l_name || ' ' || v_salary);
            cnt := cnt + 1;
            v_sal_tot_job := v_sal_tot_job + v_salary;
            v_cnt_tot := v_cnt_tot + 1;
        END LOOP;
        CLOSE c;
        
        v_sal_tot := v_sal_tot + v_sal_tot_job;
        IF cnt = 0 THEN 
            DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat.');
        ELSE
            v_sal_med_job := v_sal_tot_job / cnt;
            DBMS_OUTPUT.PUT_LINE('Salariul total al angajatilor este ' || v_sal_tot_job || ' iar cel mediu este ' || v_sal_med_job);
        END IF;
        DBMS_OUTPUT.NEW_LINE();
    END LOOP;
    v_sal_med := v_sal_tot / v_cnt_tot;
    DBMS_OUTPUT.PUT_LINE('Salariul total al tuturor angajatilor este ' || v_sal_tot || ' iar cel mediu este ' || v_sal_med);
END;
/
    
    
--3


DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curr jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary, e.commission_pct
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curr;
                    nr_joburi NUMBER;
    v_job_title jobs.job_title%TYPE;
    v_f_name employees.first_name%TYPE;
    v_l_name employees.last_name%TYPE;
    v_salary employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    v_nr_salariati NUMBER(5);
    cnt NUMBER(5);
    v_sal_tot_job NUMBER(8,2);
    v_sal_med_job NUMBER(8,2);
    v_sal_tot NUMBER(10,2) := 0;
    v_sal_med NUMBER(10,2) := 0;
    v_cnt_tot NUMBER(5) := 0;
    v_commission_pct NUMBER(5) := 0;
    v_total_cu_comision NUMBER(10,2) := 0;
BEGIN
    SELECT COUNT(*)
    INTO nr_joburi
    FROM jobs;
    
    joburi.EXTEND(nr_joburi);
    
    SELECT j.job_id
    BULK COLLECT INTO joburi
    FROM jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
    
        SELECT job_title
        INTO v_job_title
        FROM jobs j
        WHERE j.job_id = joburi(i);     
        cnt := 0;
        v_sal_tot_job := 0;
        
        SELECT count(*)
        INTO v_nr_salariati
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id and
            j.job_id = joburi(i);
            
        SELECT SUM(salary) + SUM(salary*commission_pct)
        INTO v_total_cu_comision
        FROM EMPLOYEES;
        
        IF v_nr_salariati = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu lucreaza niciun angajat pe postul de ' || v_job_title);
        ELSIF v_nr_salariati = 1 THEN
            DBMS_OUTPUT.PUT_LINE('Un angajat lucreaza ca ' || v_job_title);
        ELSIF v_nr_salariati < 20 THEN
            DBMS_OUTPUT.PUT_LINE(v_nr_salariati || ' angajati lucreaza ca ' || v_job_title);
        ELSE
            DBMS_OUTPUT.PUT_LINE(v_nr_salariati || ' de angajati lucreaza ca ' || v_job_title);
        END IF;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO v_f_name, v_l_name, v_salary, v_commission_pct;
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(cnt + 1 || ' ' || v_f_name || ' ' || v_l_name || ' ' || v_salary || ' ' || TO_CHAR(((v_salary + (v_salary * nvl(v_commission_pct, 0))) * 100 / v_total_cu_comision), '0.00'));
            
            cnt := cnt + 1;
            v_sal_tot_job := v_sal_tot_job + v_salary;
            v_cnt_tot := v_cnt_tot + 1;
        END LOOP;
        CLOSE c;
        
        v_sal_tot := v_sal_tot + v_sal_tot_job;
        IF cnt = 0 THEN 
            DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat.');
        ELSE
            v_sal_med_job := v_sal_tot_job / cnt;
            DBMS_OUTPUT.PUT_LINE('Salariul total al angajatilor este ' || v_sal_tot_job || ' iar cel mediu este ' || v_sal_med_job);
        END IF;
        DBMS_OUTPUT.NEW_LINE();
    END LOOP;
    v_sal_med := v_sal_tot / v_cnt_tot;
    DBMS_OUTPUT.PUT_LINE('Salariul total al tuturor angajatilor este ' || v_sal_tot || ' iar cel mediu este ' || v_sal_med);
END;
/
    

--4


DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curr jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary, e.commission_pct
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curr
        ORDER BY e.salary DESC; 
    nr_joburi NUMBER;
    v_job_title jobs.job_title%TYPE;
    v_f_name employees.first_name%TYPE;
    v_l_name employees.last_name%TYPE;
    v_salary employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    v_nr_salariati NUMBER(5);
    cnt NUMBER(5);
    v_sal_tot_job NUMBER(8,2);
    v_sal_med_job NUMBER(8,2);
    v_sal_tot NUMBER(10,2) := 0;
    v_sal_med NUMBER(10,2) := 0;
    v_cnt_tot NUMBER(5) := 0;
    v_commission_pct NUMBER(5) := 0;
    v_total_cu_comision NUMBER(10,2) := 0;
BEGIN  
    
    SELECT COUNT(*)
    INTO nr_joburi
    FROM jobs;
    
    joburi.EXTEND(nr_joburi);
    
    SELECT j.job_id
    BULK COLLECT INTO joburi
    FROM jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
        cnt := 0;
        SELECT job_title
        INTO v_job_title
        FROM jobs j
        WHERE j.job_id = joburi(i); 
        
        SELECT count(*)
        INTO v_nr_salariati
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id and
            j.job_id = joburi(i);

        IF v_nr_salariati < 5 THEN
            DBMS_OUTPUT.PUT_LINE('Lucreaza mai putin de 5 angajati ca  ' || v_job_title);
        ELSE
            DBMS_OUTPUT.PUT_LINE(v_job_title);
        END IF;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO v_f_name, v_l_name, v_salary, v_commission_pct;
            EXIT WHEN c%NOTFOUND or c%ROWCOUNT > 5;
            DBMS_OUTPUT.PUT_LINE(cnt + 1 || ' ' || v_f_name || ' ' || v_l_name || ' ' || v_salary);
            cnt := cnt + 1;
        END LOOP;
        CLOSE c;
         
        DBMS_OUTPUT.NEW_LINE();
    END LOOP;
END;
/


--5.

DECLARE 
    TYPE tip_joburi IS TABLE OF jobs.job_id%TYPE;
    CURSOR c (job_curr jobs.job_id%TYPE)IS 
        SELECT e.last_name, e.first_name, e.salary, e.commission_pct
        FROM employees e, jobs j
        WHERE j.job_id = e.job_id and
                j.job_id = job_curr
        ORDER BY e.salary DESC; 
    nr_joburi NUMBER;
    v_job_title jobs.job_title%TYPE;
    v_f_name employees.first_name%TYPE;
    v_l_name employees.last_name%TYPE;
    v_salary employees.salary%TYPE;
    joburi tip_joburi := tip_joburi();
    v_nr_salariati NUMBER(5);
    cnt NUMBER(5);
    v_sal_tot_job NUMBER(8,2);
    v_sal_med_job NUMBER(8,2);
    v_sal_tot NUMBER(10,2) := 0;
    v_sal_med NUMBER(10,2) := 0;
    v_cnt_tot NUMBER(5) := 0;
    v_commission_pct NUMBER(5) := 0;
    v_total_cu_comision NUMBER(10,2) := 0;
    v_last_value employees.salary%TYPE;
BEGIN  
    
    SELECT COUNT(*)
    INTO nr_joburi
    FROM jobs;
    
    joburi.EXTEND(nr_joburi);
    
    SELECT j.job_id
    BULK COLLECT INTO joburi
    FROM jobs j;
    
    FOR i IN joburi.FIRST..joburi.LAST LOOP   
        v_last_value := 0;
        cnt := 0;
        SELECT job_title
        INTO v_job_title
        FROM jobs j
        WHERE j.job_id = joburi(i); 
        
        SELECT count(*)
        INTO v_nr_salariati
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id and
            j.job_id = joburi(i);

        IF v_nr_salariati < 5 THEN
            DBMS_OUTPUT.PUT_LINE('Lucreaza mai putin de 5 angajati ca  ' || v_job_title);
        ELSE
            DBMS_OUTPUT.PUT_LINE(v_job_title);
        END IF;
        
        OPEN c(joburi(i));
        LOOP
            FETCH c INTO v_f_name, v_l_name, v_salary, v_commission_pct;
            EXIT WHEN c%NOTFOUND or c%ROWCOUNT > 5;
            IF v_last_value = 0 or v_salary <> v_last_value THEN
                v_last_value := v_salary;
                cnt := cnt + 1;
            END IF;
            DBMS_OUTPUT.PUT_LINE(cnt || ' ' || v_f_name || ' ' || v_l_name || ' ' || v_salary);
        END LOOP;
        CLOSE c;
         
        DBMS_OUTPUT.NEW_LINE();
    END LOOP;
END;
/










    
    
    
    
    
    
    
    
    
    
    