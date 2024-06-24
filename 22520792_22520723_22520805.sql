---part 1: create table and adding constraints|	DONE
---part 2: TRIGGERS | DONE
---part 3: PROCEDURES | DONE
---part 4: FUNCTIONS |DONE
---part 5: VIEWS| DONE
-- part 6: PASSWORD ENCRYPTION|DONE
-- part 7: CURSOR
-- PART 8: ROLE,GRANT,LOGIN
 
SET DateStyle TO European;
CREATE EXTENSION pgcrypto;
CREATE TYPE user_types AS ENUM ('customer', 'employee');
CREATE TABLE USERS(
	user_id serial primary key,
	first_name varchar(30) NOT NULL,
	last_name varchar(30) NOT NULL,
	phone_number char(10) NOT NULL,
	date_of_birth date NOT NULL,
	email varchar(50) NOT NULL,
	pass_word varchar(100) NOT NULL,
	user_type user_types
);
--email check
ALTER TABLE USERS ADD CHECK(email LIKE '%@%.%');
ALTER TABLE USERS ADD CHECK(phone_number LIKE '0%');


CREATE TYPE customer_types AS ENUM ('normal', 'medium','vip');
CREATE TABLE CUSTOMERS(
	user_id INT primary key,
	customer_type customer_types,
	CONSTRAINT fk_userid FOREIGN KEY(user_id) REFERENCES USERS(user_id)
);


CREATE TABLE EMPLOYEES(
	user_id serial primary key,
	onboard_date date NOT NULL,
	salary decimal(10,2),
	CONSTRAINT fk_userid FOREIGN KEY(user_id) REFERENCES USERS(user_id) 
);
--check 18 years old on employee
ALTER TABLE EMPLOYEES ADD CHECK(EXTRACT(YEAR FROM (Now() - onboard_date))<18);
ALTER TABLE EMPLOYEES ADD CHECK(salary>=0);

CREATE TABLE ROLES(
	role_id serial primary key,
	role_name varchar(30),
	description varchar(255)
);
CREATE TABLE EMPLOYEE_ROLE(
	employee_id INT NOT NULL,
	role_id INT NOT NULL,
	date_assigned date NOT NULL,
	CONSTRAINT fk_emid FOREIGN KEY(employee_id) REFERENCES EMPLOYEES(user_id),
	CONSTRAINT fk_roleid FOREIGN KEY(role_id) REFERENCES ROLES(role_id)
);

--------------------------------------------------
CREATE TABLE PRODUCTS(
	product_id SERIAL PRIMARY KEY,
	product_name VARCHAR(50) NOT NULL,
	imported_price decimal(10,2) NOT NULL,
	selling_price decimal(10,2)NOT NULL,
	num_in_stock INT NOT NULL
);
ALTER TABLE PRODUCTS ADD CHECK(imported_price>=0);
ALTER TABLE PRODUCTS ADD CHECK(selling_price>=0);
ALTER TABLE PRODUCTS ADD CHECK(num_in_stock>=0);
ALTER TABLE PRODUCTS ADD UNIQUE(product_name);

CREATE TABLE ORDER_DETAILS(
	order_id INT NOT NULL,
	product_id INT NOT NULL,
	quantity INT NOT NULL,
	CONSTRAINT fk_order_id FOREIGN KEY(order_id) REFERENCES ORDERS(order_id),
	CONSTRAINT fk_product_id FOREIGN KEY(product_id) REFERENCES PRODUCTS(product_id)
);

CREATE TABLE ORDERS(
	order_id SERIAL PRIMARY KEY,
	created_date date NOT NULL,
	total_price decimal(10,2) NOT NULL,
	employee_id INT NOT NULL,
	CONSTRAINT fk_emid FOREIGN KEY(employee_id) REFERENCES EMPLOYEES(user_id)
);
ALTER TABLE ORDERS ADD CHECK(total_price>=0);
ALTER TABLE ORDERS ALTER COLUMN total_price set default 0;
--------------------------------------------------------
CREATE TABLE FIELDS(
	field_id SERIAL PRIMARY KEY,
	field_name VARCHAR(50) NOT NULL,
	price_per_hour DECIMAL(10,2) NOT NULL
);
ALTER TABLE FIELDS ADD CHECK(price_per_hour>=0);

CREATE TABLE SERVICES(
	service_id SERIAL PRIMARY KEY,
	service_name VARCHAR(50),
	descriptions VARCHAR(255),
	price DECIMAL(10,2) NOT NULL
);
ALTER TABLE SERVICES ADD CHECK(price>=0);
CREATE TABLE RESERVATION_SERVICE(
	reservation_id INT,
	service_id INT,
	CONSTRAINT fk_reservation_id FOREIGN KEY(reservation_id) REFERENCES RESERVATIONS(reservation_id),
	CONSTRAINT fk_service_id FOREIGN KEY(service_id) REFERENCES SERVICES(service_id)
);
CREATE TYPE reservation_status AS ENUM ('canceled', 'pending','confirmed');

CREATE TABLE RESERVATIONS(
	reservation_id SERIAL PRIMARY KEY,
	time_begin TIME NOT NULL,
	time_end TIME NOT NULL,
	reservation_date DATE NOT NULL,
	renting_price DECIMAL(10,2) NOT NULL,
	phone_contact CHAR(10) NOT NULL,
	created_date DATE NOT NULL,
	res_status reservation_status,
	is_paid bool default FALSE,
	field_id INT NOT NULL,
	user_id INT NOT NULL,
	CONSTRAINT fk_field_id FOREIGN KEY(field_id) REFERENCES FIELDS(field_id),
	CONSTRAINT fk_user_id FOREIGN KEY(user_id)REFERENCES USERS(user_id)
);
ALTER TABLE RESERVATIONS ALTER COLUMN res_status SET DEFAULT 'pending';

--INTERVAL
ALTER TABLE RESERVATIONS ADD CHECK((time_end-time_begin)>='1');
ALTER TABLE RESERVATIONS ADD CHECK(renting_price>=0);
ALTER TABLE RESERVATIONS ADD CHECK(phone_contact LIKE '0%');


CREATE TYPE payment_methods AS ENUM ('cash', 'momo','bank');
CREATE TABLE PAYMENT(
	payment_id SERIAL PRIMARY KEY,
	payment_date DATE NOT NULL,
	pay_method payment_methods,
	total_price DECIMAL(10,2) NOT NULL,
	reservation_id INT NOT NULL,
	employee_id INT NOT NULL,---employee that process the payments
	CONSTRAINT fk_reservation_id FOREIGN KEY(reservation_id) REFERENCES RESERVATIONS(reservation_id),
	CONSTRAINT fk_employee_id FOREIGN KEY(employee_id) REFERENCES EMPLOYEES(user_id)
 );
 
 
 CREATE TABLE FEEDBACKS(
 	feedback_id SERIAL PRIMARY KEY,
	created_at DATE NOT NULL,
	descriptions VARCHAR(255) NOT NULL,
	reservation_id INT NOT NULL,
	customer_id INT NOT NULL,
	CONSTRAINT fk_reservation_id FOREIGN KEY(reservation_id) REFERENCES RESERVATIONS(reservation_id),
	CONSTRAINT fk_customer_id FOREIGN KEY(customer_id) REFERENCES CUSTOMERS(user_id)
 );
 
 ---part 2: TRIGGERS
 ---1. check num_in_stock products| insert+update
CREATE OR REPLACE FUNCTION check_num_in_stock()
RETURNS TRIGGER 
AS
$insert_trigger_check_num_in_stock$
DECLARE
    current_quan INT;
	prod_price decimal(10,2);
BEGIN
	select num_in_stock,selling_price into current_quan,prod_price
	from products where product_id = new.product_id;
	
	if(current_quan-new.quantity<0) then
		raise exception'Do not have enough quantity of this product in stock';
    end if;  
	
	--update orders price
	update orders
	set total_price =total_price+new.quantity*prod_price
	where order_id = new.order_id;
	
	---updates product quantity
	update products
	set num_in_stock = num_in_stock - new.quantity
	where product_id = new.product_id;
	RETURN NEW;
END;
$insert_trigger_check_num_in_stock$ language plpgsql;

CREATE TRIGGER insert_trigger_check_num_in_stock
BEFORE INSERT
ON order_details
FOR EACH ROW
EXECUTE PROCEDURE check_num_in_stock();

---------------------------update trigger-------------------
CREATE OR REPLACE FUNCTION check_num_in_stock_update()
RETURNS TRIGGER 
AS
$update_trigger_check_num_in_stock$
DECLARE
    current_quan INT;
	prod_price decimal(10,2);
BEGIN
	select num_in_stock,selling_price into current_quan,prod_price
	from products where product_id = new.product_id;
	
	if(current_quan+old.quantity-new.quantity<0) then
		raise exception'update_fail: Do not have enough quantity of this product in stock';
    end if;  
	--update order price
	update orders
	set total_price = total_price - old.quantity*prod_price + new.quantity*prod_price
	where order_id = new.order_id;
	
	--update product num
	update products
	set num_in_stock = num_in_stock +old.quantity - new.quantity 
	where product_id = new.product_id;
	RETURN NEW;
END;
$update_trigger_check_num_in_stock$ language plpgsql;

CREATE TRIGGER update_trigger_check_num_in_stock
AFTER UPDATE OF quantity
ON order_details
FOR EACH ROW
EXECUTE PROCEDURE check_num_in_stock_update();


 ---2. auto calculation on insert+update reservation time,field_id
CREATE OR REPLACE FUNCTION insert_trigger_calculation_renting_price()
RETURNS TRIGGER 
AS
$insert_trigger_calculation_renting_price$
DECLARE
    price_one_hour decimal(10,2);
BEGIN
	--get price per hour
	select price_per_hour into price_one_hour from fields where field_id = new.field_id;
	
	new.renting_price = price_one_hour*ROUND(extract(epoch from(new.time_end - new.time_begin)/3600),1); 

	RETURN NEW;
END;
$insert_trigger_calculation_renting_price$ language plpgsql;

CREATE TRIGGER insert_trigger_calculation_renting_price
BEFORE INSERT OR UPDATE OF time_begin,time_end,field_id
ON reservations
FOR EACH ROW
EXECUTE PROCEDURE insert_trigger_calculation_renting_price();



--3.auto adding renting price on when adding services
CREATE OR REPLACE FUNCTION add_service_to_renting_price()
RETURNS TRIGGER 
AS
$trigger_update_renting_price_when_insert_new_service$
DECLARE
    service_price decimal(10,2);
	renting_price_res decimal(10,2);
BEGIN
	--GET SERVICE PRICE
	SELECT price into service_price
	FROM SERVICES
	WHERE service_id = new.service_id;
	
	--UPDATE RENTING PRICE ON INSERT
	UPDATE RESERVATIONS
	SET renting_price = renting_price + service_price
	WHERE reservation_id = new.reservation_id;
	
	RETURN NEW;
END;
$trigger_update_renting_price_when_insert_new_service$ language plpgsql;

CREATE TRIGGER trigger_update_renting_price_when_insert_new_service
AFTER INSERT
ON RESERVATION_SERVICE
FOR EACH ROW
EXECUTE PROCEDURE add_service_to_renting_price();

--4.auto get total amount when create payment

CREATE OR REPLACE FUNCTION insert_trigger_calculation_payment()
RETURNS TRIGGER 
AS
$insert_trigger_calculation_payment$
DECLARE
	renting_price_res decimal(10,2);
BEGIN
	select renting_price into renting_price_res
	from reservations
	where reservation_id = new.reservation_id;
	
	new.total_price = renting_price_res;
	RETURN NEW;
END;
$insert_trigger_calculation_payment$ language plpgsql;

CREATE TRIGGER insert_trigger_calculation_payment
BEFORE INSERT
ON payment
FOR EACH ROW
EXECUTE PROCEDURE insert_trigger_calculation_payment() 



 ---5. Trigger avoid reservation on the same time interval of the day.
CREATE OR REPLACE FUNCTION trigger_check_reservation_conflicts()
RETURNS TRIGGER 
AS
$insert_update_trigger_reservation_conflict$
DECLARE
    service_price decimal(10,2);
	renting_price_res decimal(10,2);
BEGIN
	IF EXISTS(SELECT * 
			  FROM RESERVATIONS 
			  WHERE reservation_date = new.reservation_date AND
			 	((time_begin<new.time_begin AND new.time_end<time_end) 
				OR(time_begin<new.time_begin AND new.time_end>time_end) 
				OR(time_begin>new.time_begin AND new.time_begin<time_end)
				OR(time_end>new.time_begin AND new.time_end<time_end))AND res_status = 'conformed') THEN
	raise exception'Reservation conflicts'; 
	END IF;

	RETURN NEW;
END;
$insert_update_trigger_reservation_conflict$ language plpgsql;

CREATE TRIGGER insert_update_trigger_reservation_conflict
AFTER INSERT OR UPDATE OF time_begin,time_end,reservation_date
ON reservations
FOR EACH ROW
EXECUTE PROCEDURE trigger_check_reservation_conflicts()


 
 ---part 3: PROCEDURES
 --1. Procedure add a reservation
 CREATE OR REPLACE PROCEDURE ADD_RESERVATION(
   	atime_begin TIME,
	atime_end TIME,
	areservation_date DATE,
	aphone_contact CHAR(10),
	ares_status reservation_status,
	afield_id INT,
	auser_id INT
)
language plpgsql    
as $$
begin
   	INSERT INTO RESERVATIONS(time_begin,time_end,reservation_date,phone_contact,created_date,res_status,field_id,user_id)
	VALUES(atime_begin,atime_end,areservation_date,aphone_contact,current_date,ares_status,afield_id,auser_id);
end;$$

--2. procedure add customer
CREATE OR REPLACE PROCEDURE ADD_CUSTOMER(
	afirst_name varchar(30),
	alast_name varchar(30),
	aphone_number char(10),
	adate_of_birth date,
	aemail varchar(50),
	apass_word varchar(100)
)
language plpgsql    
as $$
DECLARE
    new_user_id INT;
begin
   	--insert to user
	INSERT INTO USERS(first_name,last_name, phone_number, date_of_birth, email, pass_word,user_types)
	VALUES (afirst_name,alast_name, aphone_number, adate_of_birth, aemail, apass_word, 'customer') RETURNING user_id INTO new_user_id;
	INSERT INTO CUSTOMER(user_id,customer_type) VALUES(new_user_id,'normal');
end;$$

--3. procedure add employee
CREATE OR REPLACE PROCEDURE ADD_EMPLOYEE(
	afirst_name varchar(30),
	alast_name varchar(30),
	aphone_number char(10),
	adate_of_birth date,
	aemail varchar(50),
	apass_word varchar(100),
	aonboard_date date,
	asalary decimal(10,2)
)
language plpgsql    
as $$
DECLARE
    new_user_id INT;
begin
   	--insert to user
	INSERT INTO USERS(first_name,last_name, phone_number, date_of_birth, email, pass_word,user_types)
	VALUES (afirst_name,alast_name, aphone_number, adate_of_birth, aemail, apass_word, 'employee') RETURNING user_id INTO new_user_id;
	INSERT INTO EMPLOYEES(user_id,onboard_date,salary) VALUES(new_user_id,onboard_date,salary);
end;$$

--3. PROCEDURE ADD PAYMENT
CREATE OR REPLACE PROCEDURE ADD_PAYMENT(
	apayment_date DATE,
	apay_method payment_methods,
	areservation_id INT,
	aemployee_id INT---employee that process the payments
)
language plpgsql    
as $$
DECLARE
    new_user_id INT;
begin
   INSERT INTO PAYMENT(payment_date,pay_method,reservation_id,employee_id)
   VALUES (apayment_date,apay_method,areservation_id,aemployee_id);
end;$$
--4. PROCEDURE ADD SERVICE
CREATE OR REPLACE PROCEDURE ADD_SERVICE_IN_RESERVATION(
	areservation_id INT,
	aservice_id INT
)
language plpgsql    
as $$
DECLARE
    new_user_id INT;
begin
   INSERT INTO RESERVATION_SERVICE(reservation_id,service_id) VALUES(areservation_id,aservice_id);
end;$$
---part 4: FUNCTIONS 
--4.1.function to get top k customer booking of year
CREATE OR REPLACE FUNCTION GET_TOP_K_CUS_BOOKING_OF_YEAR(topk INT,IYEAR INT)
RETURNS TABLE(auser_id int,afirst_name VARCHAR(30),SOLUONG BIGINT) AS $$
BEGIN
	RETURN QUERY SELECT U.user_id,U.first_name,COUNT(*) AS SOLUONG
	FROM USERS U JOIN RESERVATIONS RES
	ON U.user_id = RES.user_id 
	WHERE U.user_id IN (select user_id from customers) AND EXTRACT(YEAR FROM created_date) = IYEAR
		AND RES.res_status = 'confirmed'
	GROUP BY U.user_id,U.first_name
	ORDER BY SOLUONG DESC
	LIMIT topk;
END;$$
LANGUAGE PLPGSQL;

--4.2.GET ALREADY BOOKED FIELDS BY DATE TIME
CREATE OR REPLACE FUNCTION GET_ALREADY_BOOKED_FIELD_BY_DATE(IDATE DATE)
RETURNS TABLE(field_id INT,field_name VARCHAR(50),time_begin TIME,time_end TIME) AS $$
BEGIN
	RETURN QUERY SELECT FI.field_id,FI.field_name,RES.time_begin,RES.time_end
	FROM RESERVATIONS RES JOIN FIELDS FI ON RES.field_id = FI.field_id
	WHERE RES.reservation_date=IDATE AND RES.res_status = 'confirmed'
	ORDER BY FI.field_id;
END;$$
LANGUAGE PLPGSQL;
SELECT * FROM GET_ALREADY_BOOKED_FIELD_BY_DATE('2023-02-23');

--4.3.GET CUSTOMER BOOKING HISTORY BY CUS_ID
CREATE OR REPLACE FUNCTION GET_HISTORIC_RESERVATION_CUS_BY_ID(uid INT)
RETURNS TABLE(user_id INT,first_name VARCHAR(30),time_begin TIME,time_end TIME,res_date DATE) AS $$
BEGIN
	RETURN QUERY SELECT u.user_id,u.first_name,res.time_begin,res.time_end,res.reservation_date
	FROM users u join reservations res on u.user_id = res.user_id
	where u.user_id = uid;
END;$$
LANGUAGE PLPGSQL;
drop function GET_HISTORIC_RESERVATION_CUS_BY_ID(int);

--4.4.GET FEEDBACK OF A RESERVATION
CREATE OR REPLACE FUNCTION GET_FEEDBACK_OF_A_RESERVATION(resid INT)
RETURNS TABLE(customer_id INT,descriptions VARCHAR(255)) AS $$
BEGIN
	RETURN QUERY SELECT customer_id,descriptions
	FROM FEEDBACK WHERE reservation_id= resid;
END;$$
LANGUAGE PLPGSQL;


---part 5: VIEWS
--5.1.View to see historic payment behavior
CREATE OR REPLACE VIEW VIEW_HISTORIC_PAYMENT_BEHAVIOR AS
SELECT
	CASE
		WHEN pay_method = 'cash' THEN 'Tiền mặt'
		WHEN pay_method = 'momo' THEN 'Momo'
		ELSE 'Ngân hàng'
	END AS Payment_Method,
	count(payment_id) as total
FROM PAYMENT
GROUP BY pay_method
select * from VIEW_HISTORIC_PAYMENT_BEHAVIOR;

--5.2.View to see top-5 best seller
CREATE OR REPLACE VIEW VIEW_TOP_BEST_SELLER_PRODUCTS_THIS_MONTH AS
SELECT OD.product_id,pro.product_name,sum(quantity) as total
FROM ORDERS ORD,ORDER_DETAILS OD,PRODUCTS pro
WHERE ORD.order_id = OD.order_id AND OD.product_id = pro.product_id
	AND ORD.created_date between '2024-06-01' AND '2024-06-30'
GROUP BY OD.product_id,pro.product_name
ORDER BY sum(quantity) DESC
LIMIT 5 
select * from VIEW_TOP_BEST_SELLER_PRODUCTS;

---VIEW COMPARE PRICE
CREATE OR REPLACE VIEW VIEW_COMPARE_PRICE AS
SELECT OD.product_id,pro.product_name,sum(pro.imported_price*OD.quantity) as sum_import,sum(pro.selling_price*OD.quantity) AS sum_sell
FROM ORDERS ORD,ORDER_DETAILS OD,PRODUCTS pro
WHERE ORD.order_id = OD.order_id AND OD.product_id = pro.product_id
	AND ORD.created_date between '2024-06-01' AND '2024-06-30'
GROUP BY OD.product_id,pro.product_name
ORDER BY SUM(OD.quantity) desc
LIMIT 5

--5.3.View hide password of user
CREATE OR REPLACE VIEW VIEW_HIDE_CUSTOMER_PASSWORD AS
SELECT U.user_id,
	first_name,
	last_name,
	phone_number,
	date_of_birth,
	email,
	cus.customer_type
FROM USERS U JOIN CUSTOMERS CUS ON U.user_id = CUS.user_id

--5.4.View hide password and employee salary
CREATE OR REPLACE VIEW VIEW_HIDE_EMPLOYEE_PASSWORD_SALARY AS
SELECT U.user_id,
	first_name,
	last_name,
	phone_number,
	date_of_birth,
	email,
	EM.onboard_date
FROM USERS U JOIN EMPLOYEES EM ON U.user_id = EM.user_id


--5.5.View to calculate reservation revenue 
CREATE OR REPLACE VIEW VIEW_TOTAL_RENTING_REVENUE_THIS_MONTH AS
SELECT sum(renting_price) as total_revenue
FROM RESERVATIONS
WHERE res_status = 'confirmed' 
	AND reservation_date between '2024-06-01' and '2024-06-30'

select * from VIEW_TOTAL_RENTING_REVENUE_THIS_MONTH;

--5.6.View to see top-5 customer make reservation
CREATE OR REPLACE VIEW VIEW_TOP_CUSTOMER_BOOKING_THIS_MONTH AS
SELECT CUS.user_id,CUS.last_name,CUS.first_name,count(reservation_id) as total
FROM USERS cus join RESERVATIONS RES
ON cus.user_id = RES.user_id
WHERE cus.user_id in (select user_id from customers) AND RES.res_status = 'confirmed'
	AND RES.reservation_date between '2024-06-01' and '2024-06-30'
GROUP BY CUS.user_id,CUS.first_name
ORDER BY COUNT(reservation_id) desc
LIMIT 10
DROP VIEW VIEW_TOP_CUSTOMER_BOOKING_THIS_MONTH;
select * from view_top_customer_booking_this_month;

--5.7. View monthly revenue
CREATE OR REPLACE VIEW VIEW_MONTHLY_RENTING_REVENUE AS
SELECT extract(month from reservation_date), SUM(renting_price) as total
FROM RESERVATIONS
WHERE extract(YEAR from reservation_date) = '2024'
GROUP BY extract(month from reservation_date)

-- part 6: PASSWORD ENCRYPTION
CREATE EXTENSION pgcrypto;

-- part 7: CURSOR
CREATE OR REPLACE PROCEDURE customer_type_updating(normal int,medium int)
as $$
DECLARE 
	total_times INT;
	cus_id BIGINT;
	customer_cursor cursor for select cus.user_id from CUSTOMERS cus;
begin
	-- Open the cursor
    OPEN customer_cursor;

    -- Loop through the cursor
    LOOP
        -- Fetch the next row into variables
        FETCH customer_cursor INTO cus_id;

        -- Check if no more rows to fetch
        EXIT WHEN NOT FOUND;
		
		SELECT count(RES.reservation_id) INTO total_times
		FROM RESERVATIONS RES 
		WHERE RES.user_id = cus_id AND RES.res_status = 'confirmed';

        UPDATE customers
		SET customer_type = CASE
								WHEN total_times<normal THEN 'normal'
                				WHEN total_times >= normal AND total_times<medium THEN 'medium'
								ELSE'vip'
             				END
		WHERE user_id = cus_id;
    END LOOP;

    -- Close the cursor
    CLOSE customer_cursor;
end$$
LANGUAGE plpgsql ;

-- PART 8: ROLE,GRANT,LOGIN









