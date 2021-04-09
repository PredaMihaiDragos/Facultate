-- Un subprogram stocat care returneaza numele profesorului cu cele mai multe lectii.

SET SERVEROUTPUT ON;

CREATE OR REPLACE FUNCTION GetProfesor
    RETURN users.name%type IS
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
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE(GetProfesor());
END;
