-- Un subprogram stocat care returneaza in care sfert al anului dat au fost cele mai multe facturi.

SET SERVEROUTPUT ON;

CREATE OR REPLACE FUNCTION GetFacturi(
    an NUMBER)
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
END;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE(GetFacturi(1968));
END;
