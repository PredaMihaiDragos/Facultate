CREATE OR REPLACE PACKAGE sgbd_project AS
    -- Cerinta 6
    FUNCTION GetFacturi(an NUMBER) RETURN NUMBER;
    
    -- Cerinta 7
    FUNCTION GetProfesor RETURN users.name%type;
    
    -- Cerinta 8
    PROCEDURE SendMail(subject future_mail.subject%type, message future_mail.html_content%type);
    
    -- Cerinta 9
    PROCEDURE DeleteHistory(uid users.id%type);
END sgbd_project;
/ 

CREATE OR REPLACE PACKAGE BODY sgbd_project AS 
    FUNCTION GetFacturi(an NUMBER)
    RETURN NUMBER
    IS
        type Tablou IS TABLE OF NUMBER INDEX BY BINARY_INTEGER;
        facturi    Tablou;
        mx NUMBER;
        sfert NUMBER;
    BEGIN
        FOR i IN 1..12
        LOOP
            SELECT COUNT(*)
            INTO facturi(i)
            FROM factura f
            WHERE EXTRACT(YEAR FROM f.data) = an AND EXTRACT(MONTH FROM f.data) = i;
        END LOOP;
        
        mx := facturi(1) + facturi(2) + facturi(3);
        sfert := 1;
        
        IF facturi(4) + facturi(5) + facturi(6) > mx
        THEN
            mx := facturi(4) + facturi(5) + facturi(6);
            sfert := 2;
        END IF;
        
        IF facturi(7) + facturi(8) + facturi(9) > mx
        THEN
            mx := facturi(7) + facturi(8) + facturi(9);
            sfert := 3;
        END IF;
        
        IF facturi(10) + facturi(11) + facturi(12) > mx
        THEN
            mx := facturi(10) + facturi(11) + facturi(12);
            sfert := 4;
        END IF;
        
        return sfert;
    
        EXCEPTION
            WHEN NO_DATA_FOUND THEN
                RETURN -1;
    END GetFacturi;
    
    FUNCTION GetProfesor RETURN users.name%type IS
        CURSOR teachers is (SELECT u.id, u.name
                           FROM users u
                           JOIN roles_users rou ON rou.users_id = u.id
                           JOIN role r ON r.ID = rou.role_id
                           WHERE r.name = 'Profesor');
        teacher_id users.id%type; 
        teacher_name users.name%type;
        nr_lessons NUMBER;
        max_nr_lessons NUMBER;
        max_teacher_name users.name%type;
    BEGIN
       max_nr_lessons := -1;
       OPEN teachers; 
       LOOP 
       FETCH teachers into teacher_id, teacher_name;
          EXIT WHEN teachers%notfound; 
          SELECT COUNT(*)
          INTO nr_lessons
          FROM lesson
          WHERE professor_id = teacher_id;
          
          IF nr_lessons > max_nr_lessons
          THEN
            max_nr_lessons := nr_lessons;
            max_teacher_name := teacher_name;
          END IF;
       END LOOP; 
       CLOSE teachers; 
       
       return max_teacher_name;
       EXCEPTION
            WHEN NO_DATA_FOUND THEN
                RETURN 'No data found';
    END GetProfesor;
    
    PROCEDURE SendMail(
        subject future_mail.subject%type,
        message future_mail.html_content%type) IS
    BEGIN
        FOR usr IN (SELECT email
                    FROM users u
                    WHERE (SELECT COUNT(*)
                           FROM lesson l
                           WHERE l.student_id = u.id) = 2)
        LOOP
            INSERT INTO future_mail(ID, SUBJECT, RECIPENT, HTML_CONTENT, SEND_DATE)
            VALUES((SELECT MAX(ID) + 1 FROM future_mail), subject, usr.email, message, sysdate);
        END LOOP;
        EXCEPTION
            WHEN NO_DATA_FOUND THEN
                DBMS_OUTPUT.PUT_LINE('No data found exception.');
    END SendMail;
    
    PROCEDURE DeleteHistory(uid users.id%type) IS
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
    END DeleteHistory;
END sgbd_project;
/