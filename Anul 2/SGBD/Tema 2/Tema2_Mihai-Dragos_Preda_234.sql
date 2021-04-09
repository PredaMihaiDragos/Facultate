-- 9 --
select m.first_name, m.last_name, t.title_id, count(*) as "Nr imprumuturi"
from member m 
join rental r on m.member_id=r.member_id
join title t on r.title_id=t.title_id
group by m.first_name, m.last_name, t.title_id;

-- 10 --
select m.first_name, m.last_name, tc.copy_id, count(*) as "Nr imprumuturi"
from member m 
join rental r on m.member_id=r.member_id
join title t on r.title_id=t.title_id
join title_copy tc on t.title_id=tc.title_id
group by m.first_name, m.last_name, tc.copy_id;

-- 11 --
select title, status 
from title_copy tc
join title t on tc.title_id = t.title_id
where tc.copy_id = (
    select copy_id from
        (select copy_id from rental 
         where title_id = tc.title_id 
         group by title_id, copy_id 
         order by count(copy_id) desc)
    where rownum = 1
);

-- 12 --
-- A --
select DT, (select count(*) from rental where extract(day from book_date) = extract(day from DT) and 
                                              extract(month from book_date) = extract(month from DT) and
                                              extract(year from book_date) = extract(year from DT)) as "Nr imprumuturi"
from(select trunc (last_day(sysdate) - rownum) DT
     from DUAL connect by rownum < 32
     )
where DT >= trunc(sysdate, 'mm') and extract(day from DT) in (1, 2)
order by DT;

-- B --
select book_date, count(*) as "Nr imprumuturi"
from rental 
where extract(month from book_date) = extract(month from sysdate) 
group by book_date 
order by book_date asc;

-- C --
select DT, (select count(*) from rental where extract(day from book_date) = extract(day from DT) and 
                                              extract(month from book_date) = extract(month from DT) and
                                              extract(year from book_date) = extract(year from DT)) as "Nr imprumuturi"
from(select trunc (last_day(sysdate) - rownum) DT
     from DUAL connect by rownum < 32
     )
where DT >= trunc(sysdate,'mm')
order by DT;
