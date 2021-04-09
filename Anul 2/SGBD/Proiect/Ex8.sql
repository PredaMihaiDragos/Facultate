-- Un subprogram stocat care insereaza un mail de trimis astazi userilor care au avut exact 2 lectii.

SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE SendMail(
    subject future_mail.subject%type,
    message future_mail.html_content%type)
IS
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
END;
/

BEGIN
    SendMail('Test subject', 'TestMail');
END;
