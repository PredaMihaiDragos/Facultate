------ I ------

--1--
select count() from employees where last_name like 'K%';

--2--
select employee_id, first_name, last_name
from employees
order by salary 
limit 1;

--3--
select distinct employee_id, first_name
from employees
where employee_id in(select manager_id 
                     from employees
                     where department_id = 30)
order by first_name;

--4--
select employee_id, last_name, first_name, (select count()
                                            from employees
                                            where manager_id = e.employee_id) as "subalterni"
from employees e;

--5--
select employee_id, last_name, first_name
from employees e
where (select count(1)
       from employees
       where last_name = e.last_name) >= 2;

--6--
select department_id, department_name
from departments d
where (select count(distinct job_id)
       from employees
       where department_id = d.department_id) >= 2;

------ II ------

--7--
select qty, o.prod_id, prod_desc
from orders_tbl o, products_tbl p
where o.prod_id = p.prod_id
      and p.prod_desc like '%plastic%';

--8--
select first_name, 'angajat'
from employee_tbl union
select cust_name, 'client'
from customer_tbl;

--9--
select distinct prod_desc
from products_tbl p, orders_tbl o
where p.prod_id = o.prod_id and (select count()
                                 from orders_tbl ot
                                 where sales_rep = o.sales_rep
                                 and (select prod_desc
                                 from products_tbl
                                 where prod_id = ot.prod_id) like '% p%') > 0;

--10--
select cust_name
from customer_tbl c
where (select count()
       from orders_tbl
       where cust_id = c.cust_id
       and to_char(ord_date, 'dd') = 17) > 0;

--11--
select first_name, last_name, salary, bonus
from employee_pay_tbl p, employee_tbl e
where e.emp_id = p.emp_id and salary < 32000 and bonus*17 < 32000;

--12--
select first_name, nvl(sum(o.qty), 0)
from employee_tbl e left join orders_tbl o
on o.sales_rep = e.emp_id
group by e.emp_id, e.first_name
having sum(o.qty) > 50 or nvl(sum(o.qty), 0) = 0;

--13--
select first_name, salary, max(ord_date) from (employee_tbl e1
join employee_pay_tbl e2 on e1.emp_id = e2.emp_id)
join orders_tbl o on e1.emp_id = o.sales_rep
group by first_name, salary, o.sales_rep;

--14--
select prod_desc
from products_tbl
where cost > (select avg(cost) from products_tbl);

--15--
select first_name, last_name, salary, bonus, 
        (select sum(salary) from employee_pay_tbl),
        (select sum(bonus) from employee_pay_tbl)
from employee_tbl e, employee_pay_tbl p
where e.emp_id = p.emp_id;

--16--
select distinct city
from employee_Tbl e
where (select count() from orders_tbl
       where sales_rep = e.emp_id) = (select max(count())
                                       from orders_tbl
                                       group by sales_rep);

--17--
select emp_id, first_name, count(DECODE(to_char(ord_date, 'mm'), 9, 1)) "sept",
    count(DECODE(to_char(ord_date, 'mm'), 10, 1)) "oct"
from employee_tbl e left join orders_tbl on emp_id = sales_rep
group by emp_id, first_name;

--18--
select cust_name, cust_city
from customer_tbl c
where cust_address like '[0-9]%'
  and cust_id not in (select cust_id from orders_tbl);

--19--

select distinct e.emp_id, first_name, city, c.cust_id, cust_name, cust_city
from employee_tbl e, customer_tbl c
where (select count()
       from orders_tbl
       where sales_rep = e.emp_id and cust_id = c.cust_id) > 0
and cust_city != city;

--20--

select AVG(NVL(salary, 0))
from employee_pay_tbl;

-- 21

--a. DA
--b. NU

-- 22

select first_name, last_name, pay_rate
from employee_tbl e, employee_pay_tbl p
where e.emp_id = p.emp_id
and pay_rate > (select max(pay_rate)
                from employee_tbl ee, employee_pay_tbl pp
                where ee.emp_id = pp.emp_id
                and last_name like '%LL%');