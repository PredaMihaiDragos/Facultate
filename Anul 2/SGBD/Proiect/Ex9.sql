-- Un subprogram stocat sterge tot istoricul unui utilizator (lectiile, numarul de telefon, datele persoanelor fizice, juridice, mailurile).

SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE DeleteHistory(
    uid users.id%type)
IS
    uemail users.email%type;
BEGIN
    DELETE FROM lesson
    WHERE student_id = uid;
    
    UPDATE users
    SET phone = NULL
    WHERE id = uid;
    
    DELETE FROM persoana_fizica
    WHERE user_id = uid;
    
    DELETE FROM persoana_juridica
    WHERE user_id = uid;
    
    SELECT email
    INTO uemail
    FROM users
    WHERE id = uid;
    
    DELETE FROM future_mail
    WHERE recipent = uemail;
                      
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('No user found with id ' || uid);
END;
/

BEGIN
    DeleteHistory(1);
    DeleteHistory(30);
END;
