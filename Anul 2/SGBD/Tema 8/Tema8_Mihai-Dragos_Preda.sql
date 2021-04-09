CREATE OR replace PACKAGE EmployerPackage_pmd 
AS 
  PROCEDURE AddEmployer( 
    last_name     emp_pmd.last_name%TYPE, 
    first_name     emp_pmd.first_name%TYPE, 
    phone_number     emp_pmd.phone_number_number%TYPE, 
    email     emp_pmd.email%TYPE, 
    dep_name  dept_pmd.department_name%TYPE, 
    man_last_name emp_pmd.last_name%TYPE, 
    man_first_name emp_pmd.first_name%TYPE, 
    job_name  jobs_pmd.job_title%TYPE ); 
  FUNCTION GetEmployerId( 
    last_name emp_pmd.last_name%TYPE, 
    first_name emp_pmd.first_name%TYPE ) 
  RETURN emp_pmd.employee_id%TYPE; 
  FUNCTION GetDepartmentId( 
    department_name dept_pmd.department_name%TYPE ) 
  RETURN dept_pmd.department_id%TYPE; 
  FUNCTION GetJobId( 
    job_name jobs_pmd.job_title%TYPE ) 
  RETURN jobs_pmd.job_id%TYPE; 
  FUNCTION GetSalary( 
    department_id emp_pmd.department_id%TYPE, 
    job_id   jobs_pmd.job_id%TYPE ) 
  RETURN emp_pmd.salary%TYPE; 
  PROCEDURE MoveEmployer( 
    last_name     emp_pmd.last_name%TYPE, 
    first_name     emp_pmd.first_name%TYPE, 
    dep_name  dept_pmd.department_name%TYPE, 
    job_title   jobs_pmd.job_title%TYPE, 
    man_last_name emp_pmd.last_name%TYPE, 
    man_first_name emp_pmd.first_name%TYPE ); 
END EmployerPackage_pmd; 

CREATE OR replace PACKAGE BODY EmployerPackage_pmd 
AS 
  PROCEDURE AddEmployer(last_name     emp_pmd.last_name%TYPE, 
                       first_name     emp_pmd.first_name%TYPE, 
                       phone_number     emp_pmd.phone_number_number%TYPE, 
                       email     emp_pmd.email%TYPE, 
                       dep_name  dept_pmd.department_name%TYPE, 
                       man_last_name emp_pmd.last_name%TYPE, 
                       man_first_name emp_pmd.first_name%TYPE, 
                       job_name  jobs_pmd.job_title%TYPE) 
  IS 
    salary emp_pmd.salary%TYPE; 
    man_id   emp_pmd.employee_id%TYPE; 
    department_id   dept_pmd.department_id%TYPE; 
    job_id   emp_pmd.job_id%TYPE; 
  BEGIN 
      man_id := GetEmployerId(man_last_name, man_first_name); 

      department_id := GetDepartmentId(dep_name); 

      job_id := GetJobId(job_name); 

      salary := GetSalary(department_id, job_id); 

      INSERT INTO emp_pmd 
      VALUES     ( sec_pmd.NEXTVAL, 
                  first_name, 
                  last_name, 
                  email, 
                  phone_number, 
                  SYSDATE, 
                  job_id, 
                  salary, 
                  NULL,
                  man_id, 
                  department_id ); 

      COMMIT; 
  END AddEmployer; 
  FUNCTION GetEmployerId(last_name emp_pmd.last_name%TYPE, 
                      first_name emp_pmd.first_name%TYPE) 
  RETURN emp_pmd.employee_id%TYPE 
  IS 
    v_id emp_pmd.employee_id%TYPE; 
  BEGIN 
      SELECT employee_id 
      INTO   v_id 
      FROM   emp_pmd 
      WHERE  last_name = last_name 
             AND first_name = first_name; 

      RETURN v_id; 
  EXCEPTION 
    WHEN no_data_found THEN 
               Raise_application_error(-20010, 
               'Nume gresit' 
               ); WHEN too_many_rows THEN 
               Raise_application_error(-20011, 
               'Nume gresit2'); WHEN 
  OTHERS THEN 
               Raise_application_error(-20012, 
               'Alta eroare') 
               ; 
  END GetEmployerId; 
  FUNCTION GetDepartmentId(department_name dept_pmd.department_name%TYPE) 
  RETURN dept_pmd.department_id%TYPE 
  IS 
    v_id dept_pmd.department_id%TYPE; 
  BEGIN 
      SELECT department_id 
      INTO   v_id 
      FROM   dept_pmd 
      WHERE  department_name = department_name; 

      RETURN v_id; 
  EXCEPTION 
    WHEN no_data_found THEN 
               Raise_application_error(-20013, 
               'Nume departament gresit' 
               ); WHEN too_many_rows THEN 
               Raise_application_error(-20014, 
               'Nume departament gresit2') 
               ; WHEN OTHERS THEN 
               Raise_application_error(-20015, 
               'Alta eroare'); 
  END GetDepartmentId; 
  FUNCTION GetJobId(job_name jobs_pmd.job_title%TYPE) 
  RETURN jobs_pmd.job_id%TYPE 
  IS 
    v_id jobs_pmd.job_id%TYPE; 
  BEGIN 
      SELECT job_id 
      INTO   v_id 
      FROM   jobs_pmd 
      WHERE  job_title = job_name; 

      RETURN v_id; 
  EXCEPTION 
    WHEN no_data_found THEN 
               Raise_application_error(-20016, 'Nume gresit') 
               ; WHEN too_many_rows THEN 
               Raise_application_error(-20017, 
               'Nume gresit2'); WHEN OTHERS THEN 
               Raise_application_error(-20018, 'Alta eroare' 
               ); 
  END GetJobId; 
  FUNCTION GetSalary(department_id emp_pmd.department_id%TYPE, 
                      job_id   jobs_pmd.job_id%TYPE) 
  RETURN emp_pmd.salary%TYPE 
  IS 
    salary emp_pmd.salary%TYPE; 
  BEGIN 
      SELECT Min(salary) 
      INTO   salary 
      FROM   emp_pmd 
      WHERE  job_id = job_id 
             AND department_id = department_id; 

      RETURN salary; 
  EXCEPTION 
    WHEN no_data_found THEN 
               Raise_application_error(-20019, 
               'Nume gresit'); WHEN 
  OTHERS THEN 
               Raise_application_error(-20020, 
               'Alta eroare') 
               ; 
  END GetSalary; 

  PROCEDURE MoveEmployer(last_name     emp_pmd.last_name%TYPE, 
                     first_name     emp_pmd.first_name%TYPE, 
                     dep_name  dept_pmd.department_name%TYPE, 
                     job_title   jobs_pmd.job_title%TYPE, 
                     man_last_name emp_pmd.last_name%TYPE, 
                     man_first_name emp_pmd.first_name%TYPE) 
  IS 
    employer_id     emp_pmd.employee_id%TYPE; 
    department_id     dept_pmd.department_id%TYPE; 
    job_id       jobs_pmd.job_id%TYPE; 
    man_id     emp_pmd.employee_id%TYPE; 
    salary   emp_pmd.salary%TYPE; 
    current_salary emp_pmd.salary%TYPE; 
    v_emp      emp_pmd%ROWTYPE; 
  BEGIN 
      employer_id := GetEmployerId(last_name, first_name); 

      department_id := GetDepartmentId(dep_name); 

      job_id := GetJobId(job_title); 

      man_id := GetEmployerId(man_last_name, man_first_name); 

      SELECT * 
      INTO   v_emp 
      FROM   emp_pmd 
      WHERE  employee_id = employer_id; 

      IF v_emp.salary > salary THEN 
        salary := v_emp.salary; 
      END IF; 

      INSERT INTO job_history_pmd 
      VALUES     ( employer_id, 
                  v_emp.hire_date, 
                  SYSDATE, 
                  v_emp.job_id, 
                  v_emp.department_id ); 

      UPDATE emp_pmd 
      SET    department_id = department_id, 
             job_id = job_id, 
             manager_id = man_id, 
             salary = salary, 
             commission_pct = (SELECT Min(commission_pct) 
                               FROM   emp_pmd 
                               WHERE  department_id = department_id 
                                      AND job_id = job_id), 
             hire_date = SYSDATE 
      WHERE  employee_id = employer_id; 

      COMMIT; 
  END MoveEmployer; 
END EmployerPackage_pmd; 