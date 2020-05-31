--1--
SELECT S_FIRST || ' ' || S_LAST AS NUME
FROM student s
WHERE NOT EXISTS (SELECT *
                  FROM enrollment e
                  WHERE s.S_ID = e.S_ID AND GRADE IS NULL);
				  
--2--
SELECT BLDG_CODE
FROM location
GROUP BY BLDG_CODE
HAVING COUNT(CASE WHEN LOC_ID NOT IN (SELECT DISTINCT LOC_ID 
                                      FROM course_section) 
                              THEN 1 END) = 0;


--3--
SELECT F_ID, F_FIRST || ' ' || F_LAST AS NUME
FROM faculty f
WHERE EXISTS (SELECT *
              FROM student s
              WHERE s.F_ID = f.F_ID AND
              EXISTS (SELECT *
                      FROM enrollment e
                      WHERE e.s_id = s.s_id AND grade = 'A')
              ) AND EXISTS (SELECT *
                            FROM course_section cs
                            WHERE cs.F_ID = f.F_ID AND
                            EXISTS (SELECT * 
                                    FROM course c
                                    WHERE c.COURSE_NO = cs.COURSE_NO AND c.COURSE_NAME LIKE '%Database%')
                            );
	
--4--
SELECT DISTINCT F_FIRST || ' ' || F_LAST
FROM faculty f
JOIN course_section cs
ON(f.F_ID=cs.F_ID)
WHERE cs.C_SEC_ID IN (SELECT cs.C_SEC_ID
                      FROM course_section cs
                      JOIN enrollment e
                      ON(e.C_SEC_ID=cs.C_SEC_ID)
                      GROUP BY cs.C_SEC_ID
                      HAVING COUNT(e.S_ID) = (SELECT MAX(c)
                                              FROM (SELECT COUNT(e.S_ID) c
                                                    FROM course_section cs
                                                    JOIN enrollment e
                                                    ON(e.C_SEC_ID=cs.C_SEC_ID)
                                                    GROUP BY cs.C_SEC_ID
                                                    )
                                              )
                     )
UNION
SELECT DISTINCT F_FIRST || ' ' || F_LAST
FROM faculty f
JOIN course_section cs
ON(f.F_ID=cs.F_ID)
WHERE cs.C_SEC_ID IN (SELECT cs.C_SEC_ID
                      FROM course_section cs
                      JOIN location l
                      ON(l.LOC_ID=cs.LOC_ID)
                      WHERE l.CAPACITY = (SELECT MAX(CAPACITY)
                                          FROM location
                                         )
                      );
	
--5--
SELECT F_FIRST || ' ' || F_LAST AS NUME
FROM faculty f
WHERE LOC_ID IN (SELECT LOC_ID
                 FROM location
                 WHERE CAPACITY = (SELECT MIN(CAPACITY)
                                   FROM location)) AND
      EXISTS (SELECT *
              FROM course_section cs
              WHERE cs.F_ID = f.F_ID AND 
                    MAX_ENRL = (SELECT MIN(MAX_ENRL)
                                FROM course_section
                                WHERE LOC_ID IN (SELECT LOC_ID
                                                 FROM location
                                                 WHERE CAPACITY = (SELECT MAX(CAPACITY)
                                                 FROM location))
                               )
              );
			  
--6--
SELECT AVG(x)
FROM (
      SELECT DISTINCT CAPACITY as x
      FROM location
      WHERE LOC_ID IN (SELECT DISTINCT LOC_ID
                       FROM course_section
                       WHERE F_ID = (SELECT F_ID
                                     FROM faculty
                                     WHERE F_LAST = 'Marx' AND F_FIRST = 'Teresa')
                       )
      UNION ALL
      SELECT MAX_ENRL as x
      FROM course_section
      WHERE C_SEC_ID IN (SELECT C_SEC_ID
                         FROM ENROLLMENT
                         WHERE S_ID = (SELECT S_ID
                                       FROM STUDENT
                                       WHERE S_LAST = 'Jones' AND S_FIRST = 'Tammy')
                        )
     );
	 
--7--
SELECT BLDG_CODE, AVG(CAPACITY)
FROM location
WHERE BLDG_CODE IN (SELECT DISTINCT BLDG_CODE
                    FROM location l
                    WHERE EXISTS (SELECT *
                                  FROM course_section cs
                                  WHERE cs.LOC_ID = l.LOC_ID AND EXISTS (SELECT *
                                                                         FROM course c
                                                                         WHERE c.COURSE_NO = cs.COURSE_NO AND c.course_name LIKE '%Systems%')
                                 )
                    )
GROUP BY BLDG_CODE;

--8--
SELECT BLDG_CODE, AVG(CAPACITY)
FROM location
WHERE BLDG_CODE IN (SELECT DISTINCT BLDG_CODE
                    FROM location l
                    WHERE EXISTS (SELECT *
                                  FROM course_section cs
                                  WHERE cs.LOC_ID = l.LOC_ID AND EXISTS (SELECT *
                                                                         FROM course c
                                                                         WHERE c.COURSE_NO = cs.COURSE_NO AND c.course_name LIKE '%Systems%')
                                 )
                    )
GROUP BY BLDG_CODE
UNION
SELECT 'Medie', AVG(CAPACITY) 
FROM location 
WHERE BLDG_CODE IN (SELECT DISTINCT BLDG_CODE
                    FROM location l
                    WHERE EXISTS (SELECT *
                                  FROM course_section cs
                                  WHERE cs.LOC_ID = l.LOC_ID AND EXISTS (SELECT *
                                                                         FROM course c
                                                                         WHERE c.COURSE_NO = cs.COURSE_NO AND c.course_name LIKE '%Systems%')
                                 )
                    );
					
--9--     
SELECT course_name
FROM course
WHERE course_name LIKE '%JAVA%' OR (SELECT Count(*)
                                   FROM course
                                   WHERE course_name LIKE '%Java%') = 0;
                                   
--10--
SELECT course_name
FROM course c
WHERE (CASE (SELECT COUNT(*)
             FROM location l
             JOIN course_section cs
             USING(LOC_ID)
             WHERE l.CAPACITY = 42 AND cs.COURSE_NO = c.COURSE_NO
            ) WHEN 0 THEN 0 ELSE 1 END) +
      (CASE (SELECT COUNT(*) 
             FROM faculty f
             JOIN course_section cs
             USING(F_ID)
             WHERE f.F_LAST = 'Brown' AND cs.COURSE_NO = c.COURSE_NO
             ) WHEN 0 THEN 0 ELSE 1 END) +
      (CASE (SELECT COUNT(*)
             FROM student s
             JOIN enrollment e
             USING(S_ID)
             JOIN course_section cs
             USING(C_SEC_ID)
             WHERE s.S_FIRST = 'Tammy' AND s.S_LAST = 'Jones' AND cs.COURSE_NO = c.COURSE_NO
            ) WHEN 0 THEN 0 ELSE 1 END) + 
      (CASE (SELECT COUNT(*)
             FROM course c2
             WHERE c2.course_name LIKE '%Database%' AND c2.COURSE_NO = c.COURSE_NO
             ) WHEN 0 THEN 0 ELSE 1 END) +
      (CASE (SELECT COUNT(*)
             FROM course_section cs
             JOIN term t
             USING(TERM_ID)
             WHERE EXTRACT(YEAR FROM t.START_DATE) = 2007
            ) WHEN 0 THEN 0 ELSE 1 END) >= 3;
			
--11--
SELECT t.TERM_DESC, COUNT(c.COURSE_NO)
FROM term t
JOIN course_section cs
USING(TERM_ID)
JOIN course c
ON(c.COURSE_NO=cs.COURSE_NO)
WHERE c.COURSE_NAME LIKE '%Database%'
GROUP BY t.TERM_DESC
HAVING COUNT(c.COURSE_NO) = (SELECT MAX(nr)
                             FROM (SELECT t.TERM_DESC d, COUNT(c.COURSE_NO) nr
                             FROM term t
                             JOIN course_section cs
                             USING(TERM_ID)
                             JOIN course c
                             ON(c.COURSE_NO=cs.COURSE_NO)
                             WHERE c.COURSE_NAME LIKE '%Database%'
                             GROUP BY t.TERM_DESC
                                   )
                            );
							
--12--
SELECT GRADE, COUNT(S_ID)
FROM enrollment
WHERE GRADE IS NOT NULL
GROUP BY GRADE
HAVING COUNT(S_ID) = (SELECT MAX(st)
                      FROM (SELECT DISTINCT GRADE, COUNT(S_ID) st
                      FROM enrollment
                      WHERE GRADE IS NOT NULL
                      GROUP BY GRADE
                           )
                      );
                      
--13--
SELECT t.TERM_DESC, COUNT(c.COURSE_NO)
FROM term t
JOIN course_section cs
ON t.TERM_ID=cs.TERM_ID
JOIN course c
ON cs.COURSE_NO=c.COURSE_NO
WHERE c.CREDITS = 3
GROUP BY t.TERM_DESC
HAVING COUNT(c.COURSE_NO) = (SELECT MAX(courses)
                             FROM (SELECT t.TERM_DESC, COUNT(c.COURSE_NO) courses
                                   FROM term t
                                   JOIN course_section cs
                                   ON t.TERM_ID=cs.TERM_ID
                                   JOIN course c
                                   ON cs.COURSE_NO=c.COURSE_NO
                                   WHERE c.CREDITS = 3
                                   GROUP BY t.TERM_DESC
                                  )
                            );
							
--14--
SELECT DISTINCT cs.LOC_ID
FROM course_section cs
JOIN course c
ON(c.COURSE_NO=cs.COURSE_NO)
WHERE c.COURSE_NAME LIKE '%Database%' OR c.COURSE_NAME LIKE '%C++%';

--15--
SELECT DISTINCT BLDG_CODE
FROM location l
WHERE (SELECT COUNT(*)
       FROM location l2
       WHERE l.BLDG_CODE = l2.BLDG_CODE
       ) = 1;