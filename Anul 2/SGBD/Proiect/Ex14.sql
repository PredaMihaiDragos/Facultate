-- Un pachet care actioneaza ca un heap cu useri: poti adauga un user, poti sterge un user, poti gasi userul cu cele mai multe lectii.

CREATE OR REPLACE PACKAGE users_heap AS
    TYPE Tablou IS TABLE OF users%ROWTYPE;
    users_table Tablou := Tablou();
    
    -- Adauga un user.
    PROCEDURE push(usr users%ROWTYPE);
    
    -- Returneaza userul cu cele mai multe lectii.
    FUNCTION top RETURN users%ROWTYPE;
    
    -- Sterge userul cu cele mai multe lectii.
    PROCEDURE pop;

    FUNCTION get_size RETURN NUMBER;
    PROCEDURE clear;
END users_heap;
/ 

CREATE OR REPLACE PACKAGE BODY users_heap AS    
    PROCEDURE push(usr users%ROWTYPE) IS
        nr NUMBER;
    BEGIN
        users_table.extend;
        nr := users_table.COUNT;
        users_table(nr) := usr;
    END push; 
    
    FUNCTION top RETURN users%ROWTYPE IS
        max_lessons NUMBER;
        ret users%ROWTYPE;
    BEGIN
        ret := users_table(1);
        max_lessons := ret.lessons;
        FOR i IN 2..users_table.COUNT 
        LOOP
            IF users_table(i).lessons > max_lessons
            THEN
                ret := users_table(i);
                max_lessons := ret.lessons;
            END IF;
        END LOOP;
        return ret;
    END top;
    
    PROCEDURE pop IS
        id_to_delete NUMBER;
        found BOOLEAN;
        aux users%ROWTYPE;
    BEGIN
        id_to_delete := top().id;
        found := false;
        
        -- Ducem la final userul cu cele mai multe lectii.
        FOR i IN 1..(users_table.COUNT-1)
        LOOP
            IF users_table(i).id = id_to_delete
            THEN
                found := true;
            END IF;
            
            IF found = true
            THEN
                aux := users_table(i);
                users_table(i) := users_table(i+1);
                users_table(i+1) := aux;
            END IF;
        END LOOP;
        
        -- Il stergem pentru ca acum e la final.
        users_table.TRIM;
    END pop;
    
    FUNCTION get_size RETURN NUMBER IS
    BEGIN
        return users_table.COUNT;
    END get_size;
    
    PROCEDURE clear IS
    BEGIN
       users_table := Tablou();
    END clear;
END users_heap;
/ 

SET SERVEROUTPUT ON;

DECLARE
    CURSOR users_cursor IS (SELECT * FROM users);
    usr users%ROWTYPE;
BEGIN
    users_heap.clear;
    OPEN users_cursor;
    LOOP
    FETCH users_cursor into usr;
      EXIT WHEN users_cursor%notfound; 
      users_heap.push(usr);
    END LOOP; 
    CLOSE users_cursor; 
    
    FOR i IN 1..10 LOOP
        DBMS_OUTPUT.PUT_LINE('Size: ' || users_heap.get_size);
        DBMS_OUTPUT.PUT_LINE('Top: ' || users_heap.top().id);
        users_heap.pop;
    END LOOP;
END;
/
