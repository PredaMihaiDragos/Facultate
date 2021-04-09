SET SERVEROUTPUT ON;

CREATE OR REPLACE TRIGGER LESSON_TRIGGER
  AFTER INSERT OR UPDATE OR DELETE
  ON lesson
DECLARE
  action VARCHAR(120);
BEGIN
  IF INSERTING THEN
    action := 'A lesson was reserved.';
  ELSIF UPDATING THEN
    action := 'A lesson was updated.';
  ELSIF DELETING THEN
    action := 'A lesson was canceled.';
  ELSE
    action := 'Other action';
  END IF;

  DBMS_OUTPUT.PUT_LINE(action);
END;
/

INSERT INTO lesson(ID, START_DATE, END_DATE, SUBJECT, PROFESSOR_GRADE, STUDENT_GRADE, PROFESSOR_ID, STUDENT_ID,
                   STUDENT_FEEDBACK, PROFESSOR_FEEDBACK, REMINDER_ID)
VALUES(8, TO_DATE('1930-12-13 14:00:00', 'yyyy-mm-dd HH24:MI:SS'), TO_DATE('1930-12-13 16:00:00', 'yyyy-mm-dd HH24:MI:SS'),
      null, null, null, 1, 3, null, null, 2);
      
UPDATE lesson
SET professor_grade = 10
WHERE id = 8;
      
DELETE from lesson
WHERE id = 8;
