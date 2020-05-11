--1--
select s_id "Cod", s_last || " " || s_first "Student sau curs", "Student" "Tip"
from student
where f_id in (select f_id          
               from faculty 
               where f_last = "Brown") 
union
select course_no "Cod", course_name "Student sau curs", "Curs"
from course
where course_no in (select course_no
                    from course_section
                    where f_id in (select f_id      
                                   from faculty 
                                   where f_last = "Brown"));

--2--
  
select s.s_id, s.s_last, s.s_first
from Student s
where (select count(1)
    from Enrollment e
    where e.c_sec_id in (select * from (select c_sec_id 
										from course_section
										where upper(course_no) like "MIS%")) and e.s_id = s.s_id) > 0
  and
     (select count(1)
    from Enrollment e
    where e.c_sec_id in (select * from (select c_sec_id 
								        from course_section
									    where upper(course_no) like "CS%"))  and e.s_id = s.s_id) = 0;
										
--3--
select s.s_id, s.s_last, s.s_first
from Student s
where exists (select *
		      from enrollment
		      where ( grade = "C" or grade = null ) and s_id = s.s_id);
			  
--4--
select l.loc_id, l.bldg_code, l.capacity
from location l
where NOT exists (select *
        from location
        where capacity > l.capacity);
		
--5--
select min(id) + 1 "min"
from T
where id + 1 NOT in (select id from t);

select MAX(id) - 1 "max"
from T
where id - 1 NOT in (select id from t);

--6--
select f.f_id, f.f_last, 
    decode((select count(1) from Student s where s.f_id = f.f_id), 
           0, "NU", 
              "DA (" || (select count(1) from Student s where s.f_id = f.f_id) || ")"
          ) as "Student", 
    decode((select count(distinct course_no) from course_section c where c.f_id = f.f_id), 
            0, "NU", 
               "DA (" || (select count(distinct course_no) from course_section c where c.f_id = f.f_id) || ")" 
          ) as "Curs"
from Faculty f;

--7--
select one.term_desc, two.term_desc
from term one, term two            
where substr(one.term_desc, 0, length(one.term_desc) - 1) = substr(two.term_desc, 0, length(two.term_desc) - 1) and one.term_desc != two.term_desc;

--8--
with curs as (select s_id,s_last,s_first,course_no
from student s join enrollment e using(s_id) join course_section c1 using(c_sec_id) order by s_id asc)
select distinct c1.s_id,c1.s_last,c1.s_first,c1.course_no,c2.course_no
from curs c1 inner join curs c2 on(c1.s_id = c2.s_id)
where (substr(c1.course_no, 5, 1) != substr(c2.course_no, 5, 1)) and (c1.course_no != c2.course_no) and (c1.course_no < c2.course_no)
order by c1.s_id asc;

--9--
select one.c_sec_id, two.c_sec_id
from course_section one join course_section two on (one.term_id = two.term_id)
where one.c_sec_id > two.c_sec_id

--10--
select c_sec_id, course_no, term_desc, max_enrl
from course_section 
join term using (term_id)
where max_enrl < (select min(max_enrl) 
                  from course_section 
                  where loc_id = 1);
				  
--11--
select c.course_name, cs.c_sec_id, cs.max_enrl
from course c, course_section cs
where c.course_no = cs.course_no and
    cs.max_enrl = (select * 
	               from (select min(max_enrl) 
	                     from course_section));
						 
--12--
select f_last, (select avg(max_enrl) from course_section where f_id = f.f_id) 
as "Mediu" from faculty f;

--13--
select f.f_last, (select count(1) from student s where s.f_id = f.f_id)
from faculty f;

--14--
select distinct c.course_name, l.capacity, l.loc_id
from course c join course_section cs on (c.course_no = cs.course_no) join location l on (cs.loc_id = l.loc_id)
where l.capacity = (select max(capacity)
                    from course_section join location using (loc_id)
                    group by course_no
                    having course_no = cs.course_no)
					
--15--
select avg(max_enrl) 
from course_section 
join term 
using (term_id) 
where term_desc like '%2007%';
