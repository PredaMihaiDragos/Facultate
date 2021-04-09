-- Un trigger LDD care, atunci cand se modifica un tabel, creaza si o versiune de backup a vechiului tabel nemodificat in caz ca ceva merge prost si va fi necesara revenirea la o versiune anterioara.
SET SERVEROUTPUT ON;

CREATE OR REPLACE TRIGGER BACKUP_TRIGGER_ALTER BEFORE ALTER ON SCHEMA 
DECLARE
    table_backup VARCHAR(50);
BEGIN
    IF ORA_DICT_OBJ_TYPE='TABLE'
    THEN
        table_backup := ORA_DICT_OBJ_NAME || '_BACKUP';
        EXECUTE IMMEDIATE 'CREATE TABLE ' || table_backup || ' AS SELECT * FROM ' || ORA_DICT_OBJ_NAME;
    END IF;
    EXCEPTION
        WHEN OTHERS THEN
            IF SQLCODE = -955 THEN
                RAISE_APPLICATION_ERROR(-20001,'Please drop ' || table_backup || ' first.');
            ELSE
                RAISE;
            END IF;
END;
/

DROP TABLE users_backup;

ALTER TABLE users
ADD test_column VARCHAR2(20);

ALTER TABLE users
DROP COLUMN test_column;
