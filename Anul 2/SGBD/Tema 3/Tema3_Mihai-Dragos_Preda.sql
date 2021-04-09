-- 1 --
-- a) 2
-- b) text 2
-- c) text 3 adaugat in sub-bloc
-- d) 101
-- e) text 1 adaugat un blocul principal
-- f) text 2 adaugat in blocul principal

-- 2 --
-- a)
select DT, (select count(*) from rental where extract(day from book_date) = extract(day from DT) and 
                                              extract(month from book_date) = extract(month from DT) and
                                              extract(year from book_date) = extract(year from DT)) as "Nr imprumuturi"
from(select trunc (last_day(sysdate) - rownum) DT
     from DUAL connect by rownum < 32
     )
where DT >= trunc(sysdate,'mm')
order by DT;
-- b)
create table octombrie_pmd as select * from octombrie_ati;
declare
    rentals number(3) := 0;
    mx number(3) := extract(day from last_day(sysdate));
begin
    for i in 1..mx loop
        select count(*) 
		into rentals 
		from rental 
        where extract(day from book_date) = i and
		      extract(month from book_date) = extract(month from sysdate);
        insert into octombrie_pmd values (i, to_date(i || '-10' || '-2020', 'DD-MM-YYYY'));
    end loop;
end;

-- 3 --
declare
    r number(3) := 0;
    nname varchar(101) := '&name';
begin
    select count(title)
	into r
    from rental rr
	join member mm on (rr.member_id=mm.member_id)
	join title tt on (tt.title_id=rr.title_id) 
    where (lower(last_name) like '%' || lower(nname) || '%' or 
	       lower(first_name) like '%' || lower(nname) || '%') and 
		  rownum=1;
    dbms_output.put_line(nname || ': ' || r);
end;

-- 4 -- 
declare
    r number(3) := 0;
    t number(3) := 0;
    pp number(3) := 0;
    name varchar(101) := '&name';
begin
    select count(title) into t
    from rental join title using (title_id);
    
    select count(title) into r
    from rental rr join member mm on (rr.member_id=mm.member_id) join title tt on (tt.title_id=rr.title_id) 
    where lower(last_name) like '%'||lower(name)||'%' or lower(first_name) like '%'||lower(name)||'%' 
    and rownum = 1;
    
    dbms_output.put_line(name || ': '||r);
    
    pp := (r/t) * 100;
    if pp > 75 then
        dbms_output.put_line('Categoria 1');
    elsif pp > 50 then
        dbms_output.put_line('Categoria 2');
    elsif pp > 25 then
        dbms_output.put_line('Categoria 3');
    else
        dbms_output.put_line('Categoria 4');
    end if;
end;

-- 5 --
select *
from member_pmd;

create table member_pmd
as (select * from member);

alter table member_pmd
add constraint PK_member_pmd primary key (member_id);

alter table member_pmd
add discount number;

set VERIFY off
declare
    cod_membru member_pmd.member_id%type:=&cod;
    nr_titles_b number;
    nr_titles_t number;
begin
    select count(*)
    into nr_titles_t
    from title;
    
    select count(distinct title_id)
    into nr_titles_b
    from rental r join member_pmd m using (member_id)
    group by member_id
    having member_id = cod_membru;
    
    case when nr_titles_b * 100 / nr_titles_t >= 75 then 
            update member_pmd
            set discount = 10
            where member_ID = cod_membru;
            commit;
            dbms_output.put_line('1 rand modificat');
        when nr_titles_b * 100 / nr_titles_t >= 50 then 
            update member_pmd
            set discount = 5
            where member_ID = cod_membru;
            commit;
            dbms_output.put_line('1 rand modificat');
        when nr_titles_b * 100 / nr_titles_t >= 25 then
            update member_pmd
            set discount = 3
            where member_ID = cod_membru;
            commit;
            dbms_output.put_line('1 rand modificat');
        else dbms_output.put_line('Nicio modificare facuta');
    end case;        
exception
    when NO_DATA_FOUND then
     dbms_output.put_line('Nicio modificare facuta');
end;
/
set VERIFY on;