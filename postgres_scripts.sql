--TEAM MEMBERS:
--NGUYEN VO TIEN LOC-22520792
--PHAN ANH KIET
--DANG TRAN LONG
------------------------------
--enter "ctrl+f" and find expected part
-- PART 1: CREATE TABLES IN DATABASE AND ADDING CONSTRAINTS
-- PART 2: CREATE TRIGGER WITHIN DATABASE
-- PART 3: CREATE PROCEDURE
------------------------------
SET DateStyle TO European;

--PART 1: CREATE TABLES IN DATABASE AND ADDING CONSTRAINTS
create table CUSTOMER(
	customer_id BIGSERIAL primary key,
	customer_name varchar(30) not null,
	gmail varchar(50) not null,
	phone_number char(10),
	date_of_birth date not null,
	pass_word varchar(15) not null--disabling this constraint
)

--constraints
ALTER TABLE CUSTOMER
ADD CONSTRAINT check_valid_phone CHECK(phone_number like '0%'),
ADD CONSTRAINT check_valid_email CHECK(gmail like '%@%.%');


CREATE TABLE EMPLOYEE(
	employee_id	BIGSERIAL primary key,
	employee_name	varchar(30)	not null,
	phone_number	char(10),
	date_of_birth	date	not null,
	gmail	varchar(30)	not null,
	pass_word	varchar(15)	not null--disabling
)
--constraints
ALTER TABLE employee
ADD CONSTRAINT check_em_valid_phone_number CHECK(phone_number like '0%'),
ADD CONSTRAINT check_em_valid_email CHECK(gmail like '%@%.%')


CREATE TABLE DRINK(
	drink_id BIGSERIAL primary key,
	import_price money,
	selling_price money not null,
	drink_name varchar(20) not null,
	number_in_stock int not null
)
--constraint
--1 drink_name unique
--2 number_in_stock >=0
ALTER TABLE drink
ADD CONSTRAINT drink_name_unique UNIQUE(drink_name),
ADD CONSTRAINT import_price_greater_than_zero CHECK(import_price > '0'),--check compare money data type
ADD CONSTRAINT selling_price_greater_than_zero CHECK(selling_price > '0'),--check_compare money data type
ADD CONSTRAINT number_in_stock_can_not_be_negative CHECK(number_in_stock >= 0)

CREATE TABLE FIELD_TYPE(
	field_type_id	BIGSERIAL	primary key,
	field_type_name	VARCHAR(15)	not null,
	price_per_hour	MONEY	
)
--constraints
ALTER TABLE FIELD_TYPE
ADD CONSTRAINT price_per_hour_must_be_greater_than_zero CHECK(price_per_hour>='0'::money)


CREATE TABLE FIELD(
	field_id	BIGSERIAL primary key,
	field_type_id	INT,
	FOREIGN KEY(field_type_id) REFERENCES FIELD_TYPE(field_type_id)
)

CREATE TABLE RESERVATION(
	reservation_id	BIGSERIAL primary key,
	match_date	date not null,
	created_date date not null,
	time_begin	time	not null,
	time_end	time	not null,
	employee_id	INT,	
	customer_id	INT	not null,
	field_id	INT	not null,
	renting_price money default 0,
	FOREIGN KEY(employee_id) REFERENCES employee(employee_id),
	FOREIGN KEY(customer_id) REFERENCES customer(customer_id),
	FOREIGN KEY(field_id) REFERENCES field(field_id)
)
--constraints
ALTER TABLE RESERVATION
ADD CONSTRAINT time_begin_must_be_ahead_time_end CHECK(time_end - time_begin >'0')



CREATE TABLE CONFORMATION(
	conformation_id	BIGSERIAL primary key,
	created_date	date not null,
	payment_status	int default 0,
	reservation_id	INT,
	FOREIGN KEY(reservation_id) REFERENCES RESERVATION(reservation_id)
)
--constraints
ALTER TABLE CONFORMATION
ADD CONSTRAINT payment_status_must_be_either_zero_one CHECK(payment_status in (0,1))

CREATE TABLE PAYMENT(
	payment_id	BIGSERIAL primary key,
	total_renting_hour	decimal(4,2) not null,
	renting_fee money default 0,
	drink_fee money default 0,
	payment_method	int,
	conformation_id	INT,
	total_price	money not null,
	foreign key(conformation_id) references CONFORMATION(conformation_id)
)

--constraints
ALTER TABLE PAYMENT
ADD CONSTRAINT total_renting_hour_must_be_greater_or_equal_to_one CHECK(total_renting_hour>=1),
ADD CONSTRAINT payment_thod_constraint CHECK(payment_method in (1,2,3)),
ADD CONSTRAINT total_price_must_be_greater_than_zero CHECK(total_price >= '0')

CREATE TABLE DRINK_ORDER(
	drink_order_id	BIGSERIAL primary key,
	total_price	money not null,
	created_date date	not null,
	conformation_id	INT	not null,
	FOREIGN KEY(conformation_id) REFERENCES CONFORMATION(conformation_id)
)
--constraints
ALTER TABLE DRINK_ORDER
ADD CONSTRAINT total_price_must_be_greater_than_zero CHECK(total_price>='0');
ALTER TABLE DRINK_ORDER 
ALTER COLUMN total_price SET DEFAULT 0;

CREATE TABLE DRINK_ITEM(
	drink_order_id	int not null,
	line_number	int not null,
	quantity	int not null,
	drink_id	int,
	iprice money,
	PRIMARY KEY(drink_order_id,line_number),
	FOREIGN KEY(drink_order_id) REFERENCES drink_order(drink_order_id),
	FOREIGN KEY(drink_id) REFERENCES DRINK(drink_id)
)
--constraints
ALTER TABLE drink_item
ADD CONSTRAINT iquantity_must_be_greater_than_zero CHECK(quantity>0)

------------------------------------------------------------------------------------------------------------
--PART 2: CREATE TRIGGER WITHIN DATABASE
--2.1 TRIGGER FOR CHECKING EMPLOYEE AGE 

create or replace function check_employee_age()
returns trigger as $check_employee_age$
begin
    if extract(year from age(current_date, new.date_of_birth)) < 18 then
        raise exception'Employee must be greater or equal to 18 years old';
    end if;  
    return new;
end;
$check_employee_age$ language plpgsql;

create trigger check_employee_age
before insert or update on employee
for each row
execute function check_employee_age();

--2.2 TRIGGER FOR CHECKING CUSTOMER AGE
CREATE OR REPLACE FUNCTION check_customer_age()
RETURNS TRIGGER AS $check_customer_age$
BEGIN
	IF EXTRACT(YEAR FROM age(CURRENT_DATE,new.date_of_birth))<10 THEN
		RAISE EXCEPTION 'Customer must be greater or equal to 10 years old';
	END IF;
	RETURN NEW;
END;
$check_customer_age$ language plpgsql;

CREATE TRIGGER check_customer_age
BEFORE INSERT OR UPDATE ON customer
FOR EACH ROW
EXECUTE FUNCTION check_customer_age();

---------------------------------handle within this trigger
--2.3 TRIGGER TO PREVENT CHOOSING OVER QUANTITY IN STOCK OF DRINK ITEM_ON INSERT
--op trigger if exists trigger_insert_protect_number_in_stock_integrety on drink_item
--drop trigger if exists trigger_insert_protect_number_in_stock_integrety on  drink_item
CREATE OR REPLACE FUNCTION check_number_in_stock()
RETURNS TRIGGER AS $trigger_insert_protect_number_in_stock_integrety$
DECLARE num_available int;
		drink_price money;
BEGIN
	--get the available of specific drink in stock,and selling price
	SELECT number_in_stock,selling_price into num_available,drink_price
	FROM drink WHERE drink_id = new.drink_id;
	
	IF new.quantity > num_available THEN
		RAISE EXCEPTION 'Do not have enough quantity in stock, number of available: % ',num_available;
	ELSE 
			--update current num_in_stock of drink
			UPDATE drink
			SET number_in_stock = number_in_stock - new.quantity
			WHERE drink.drink_id = new.drink_id;

			new.iprice = new.quantity*drink_price;
			
			--update drink_order total price
			UPDATE drink_order
			SET total_price = total_price +  new.iprice
			WHERE drink_order_id = new.drink_order_id;
	END IF;

	RETURN NEW;
END;
$trigger_insert_protect_number_in_stock_integrety$ language plpgsql;
CREATE TRIGGER trigger_insert_protect_number_in_stock_integrety
BEFORE INSERT ON drink_item
FOR EACH ROW
EXECUTE FUNCTION check_number_in_stock();

--2.4 TRIGGER ON UPDATE CREATE TRIGGER UPDATE on drink item
--DROP TRIGGER if exists trigger_update_protect_number_in_stock_integrety on drink_item;

CREATE OR REPLACE FUNCTION drink_item_update()
RETURNS TRIGGER AS $trigger_update_protect_number_in_stock_integrety$
DECLARE num_available int;
		drink_price money;
		total_price_var money;
		minus int;
BEGIN
	--get the available of specific drink in stock,and selling price
	SELECT number_in_stock,selling_price into num_available,drink_price
	FROM drink WHERE drink_id = new.drink_id;
	
	IF new.quantity > num_available THEN
		RAISE EXCEPTION 'Do not have enough quantity in stock, number of available: % ',num_available;
	ELSE
		--action 1
		new.iprice = new.quantity*drink_price;
		--action 2: update current num_in_stock of drink
		UPDATE drink
		SET number_in_stock = num_available + (old.quantity - new.quantity)
		WHERE drink_id = new.drink_id;
			
		--action 3: UPDATE DRINK ORDER TOTAL PRICE
		UPDATE drink_order
		SET total_price = total_price - (old.quantity*drink_price) + (new.quantity*drink_price)
		WHERE drink_order_id = new.drink_order_id;
		
	END IF;
	RETURN NEW;
END;
$trigger_update_protect_number_in_stock_integrety$ language plpgsql;

CREATE TRIGGER trigger_update_protect_number_in_stock_integrety
BEFORE UPDATE OF quantity ON drink_item
FOR EACH ROW
EXECUTE FUNCTION drink_item_update();



--2.5 prevent invalid reservation
--drop trigger if exists trigger_insert_update_reservation on reservation;
CREATE OR REPLACE FUNCTION check_invalid_reservation()
RETURNS TRIGGER AS $trigger_insert_reservation$
DECLARE price_for_renting money;
		renting_hour decimal(2,1);
BEGIN
	IF EXISTS(SELECT 1 
			  FROM CONFORMATION CON 
			  JOIN RESERVATION RES 
			  ON CON.reservation_id = RES.reservation_id
			  WHERE new.match_date=RES.match_date AND new.field_id = RES.field_id
			 		AND (new.time_end>=RES.time_begin and new.time_end<=RES.time_end
					OR new.time_begin>=RES.time_begin and new.time_begin<=RES.time_end
						OR new.time_begin<=RES.time_begin and new.time_end>=RES.time_end)) THEN
		RAISE EXCEPTION 'Some one has booked on this field at that time';
	ELSE
		SELECT price_per_hour into price_for_renting 
		from field_type a1,field a2 
		where a1.field_type_id = a2.field_type_id and new.field_id = a2.field_id;
		
		new.renting_price= price_for_renting*ROUND(extract(epoch from(new.time_end - new.time_begin)/3600),1); 

		RAISE NOTICE 'Successfully created the reservation';
	END IF;
	RETURN NEW;
END;
$trigger_insert_reservation$ language plpgsql;

CREATE TRIGGER trigger_insert_update_reservation
BEFORE INSERT OR UPDATE OF match_date,field_id,time_begin,time_end ON RESERVATION
FOR EACH ROW
EXECUTE FUNCTION check_invalid_reservation();

--testing
--insert into reservation(reservation_id,created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values(101, '5/1/2023',  '7/1/2023','15:00', '19:00', 20, 78, 5);

--2.6-when insert payment the relevant information about drink bill and renting fee will be updated
drop trigger if exists trigger_insert_payment on payment;
CREATE OR REPLACE FUNCTION auto_update_relevant_fee_on_creating_payment()
RETURNS TRIGGER AS $trigger_insert_payment$
BEGIN
    SELECT RES.renting_price, ROUND(EXTRACT(EPOCH FROM (RES.time_end - RES.time_begin)) / 3600, 1)
    INTO new.renting_fee, new.total_renting_hour
    FROM CONFORMATION CON
    JOIN RESERVATION RES ON CON.reservation_id = RES.reservation_id
    WHERE CON.conformation_id = NEW.conformation_id;

    IF EXISTS(SELECT * FROM DRINK_ORDER WHERE conformation_id = NEW.conformation_id) THEN
        SELECT SUM(total_price) INTO new.drink_fee FROM DRINK_ORDER WHERE conformation_id = NEW.conformation_id;
    END IF;

    new.total_price := new.renting_fee + new.drink_fee;

    RETURN NEW;
END;
$trigger_insert_payment$ LANGUAGE plpgsql;

CREATE TRIGGER trigger_insert_payment
BEFORE INSERT ON PAYMENT
FOR EACH ROW
EXECUTE FUNCTION auto_update_relevant_fee_on_creating_payment();


------------------------------------------------------------------------------------------------------
--PART 3: PROCEDURE

--1-Insert reservation given time
CREATE OR REPLACE PROCEDURE add_a_reservation(p_match_date date,p_time_begin time,p_time_end time, p_customer_id int, p_field_id int)
AS $$
BEGIN
	INSERT INTO RESERVATION(match_date,created_date,time_begin,time_end,customer_id,field_id)
	VALUES(p_match_date,current_date,p_time_begin,p_time_end,p_customer_id,p_field_id);
END$$
LANGUAGE plpgsql ;
call add_a_reservation('11-5-2024','18:00','19:00',5,3);
select * from reservation order by created_date desc;
CALL add_a_reservation();
--2-procedure insert a conformation of a given reservation
CREATE OR REPLACE PROCEDURE add_a_conformation(p_reservation_id int)
AS $$
BEGIN
	INSERT INTO CONFORMATION(created_date,reservation_id) VALUES(current_date,p_reservation_id);
END;$$
LANGUAGE plpgsql ;
call add_a_conformation(101);

--3.Procedure display message:
CREATE OR REPLACE PROCEDURE display_message(inout msg text)
as $$
begin
	RAISE NOTICE '%',msg;
end$$
LANGUAGE plpgsql ;
call display_message('Employee must be eighteen')

--PART 4: FUNCTION
--1:get top k best-seller drink by month
CREATE OR REPLACE FUNCTION get_top_k_bestseller_in_month_x(top_k INT,month_x INT,year_y INT)
RETURNS TABLE(drink_id INT,drink_name varchar(20), sum_quantity bigINT) AS $$
BEGIN
    RETURN QUERY SELECT A2.drink_id,A3.drink_name,SUM(quantity) AS so_luong
	FROM DRINK_ORDER A1,DRINK_ITEM A2,DRINK A3
	WHERE A1.drink_order_id = A2.drink_order_id 
		  AND EXTRACT(MONTH FROM A1.created_date) = month_x
		  AND EXTRACT(YEAR FROM A1.created_date) = year_y
		  AND A3.drink_id = a2.drink_id
	GROUP BY A2.drink_id,A3.drink_name
	ORDER BY so_luong DESC
	LIMIT top_k;
END;$$
LANGUAGE plpgsql ;
--testting
select * from get_top_k_bestseller_in_month_x(3,2,2023);

--2.Get top 10 customer that have higest booking history
CREATE OR REPLACE FUNCTION get_top_x_customer_year(top_x int, year_y INT)
RETURNS TABLE(customer_id INT,customer_name VARCHAR(30),booking_time BIGINT)
AS $$
BEGIN
	RETURN QUERY SELECT RES.customer_id,CUS.customer_name, COUNT(CON.conformation_id) AS SOLAN
	FROM RESERVATION RES,CONFORMATION CON,CUSTOMER CUS
	WHERE CUS.customer_id= RES.customer_id 
			AND RES.reservation_id = CON.reservation_id 
			AND EXTRACT(YEAR FROM match_date) = year_y
	GROUP BY RES.customer_id,CUS.customer_name
	ORDER BY SUM(CON.conformation_id) DESC
	LIMIT top_x;
END;$$
LANGUAGE plpgsql;
DROP FUNCTION get_top_x_customer_year

--testing
SELECT * FROM get_top_x_customer_year(10,2023);


--3-Lay thong tin cac san va gio da duoc dat theo ngay thang nam
CREATE OR REPLACE FUNCTION get_already_booked_field_by_date(p_date date)
RETURNS TABLE(field_id BIGINT, time_begin time,time_end time)
AS $$
BEGIN
	RETURN QUERY SELECT FI.field_id, R.time_begin,R.time_end
	FROM FIELD FI,FIELD_TYPE F,RESERVATION R
	WHERE FI.field_type_id = F.field_type_id 
		AND FI.field_id = R.field_id AND R.reservation_id in (select C.reservation_id FROM CONFORMATION C)
		AND R.match_date = p_date;
END;$$
LANGUAGE plpgsql;
DROP FUNCTION get_already_booked_field_by_date;
select * from field_type;
select * from field;
--TESTING
select * from get_already_booked_field_by_date('11/5/2024');

--4-Get customer list;
CREATE OR REPLACE FUNCTION get_customer_list()
RETURNS TABLE(customer_id bigint, customer_name varchar(30), phone_number char(10), date_of_birth date)
AS $$
BEGIN
    RETURN QUERY SELECT CUS.customer_id,CUS.customer_name, CUS.phone_number, CUS.date_of_birth
	FROM CUSTOMER CUS;
END;$$
LANGUAGE plpgsql;

--5-get customer by id;
CREATE OR REPLACE FUNCTION get_customer_by_id(cus_id BIGINT)
RETURNS TABLE(customer_id bigint, customer_name varchar(30), phone_number char(10), date_of_birth date)
AS $$
BEGIN
	RETURN QUERY SELECT CUS.customer_id,CUS.customer_name, CUS.phone_number, CUS.date_of_birth
	FROM CUSTOMER CUS 
	WHERE CUS.customer_id = cus_id;
END;$$
LANGUAGE plpgsql;

SELECT * FROM get_customer_by_id(22);

--3-Get employee list
DROP PROCEDURE get_employee_list;
CREATE OR REPLACE PROCEDURE get_employee_list()
LANGUAGE 'plpgsql'
AS $BODY$
DECLARE
BEGIN
	SELECT* FROM EMPLOYEE;
END;$BODY$
call public.get_employee_list();
/*--4-get customer reservation history; input: customer_id, out put: historical information
CREATE OR REPLACE PROCEDURE get_customer_booking_history_by_customer_id(p_customer_id INT)
LANGUAGE plpgsql
AS $$
BEGIN
    RETURN SELECT RES.created_date, RES.time_begin, RES.time_end, RES.field_id, RES.renting_price
	FROM CONFORMATION CON JOIN RESERVATION RES on CON.reservation_id = RES.reservation_id
	WHERE RES.customer_id = p_customer_id;
END;$$
drop procedure get_customer_booking_history_by_customer_id
CALL get_customer_booking_history_by_customer_id(1);
drop procedure get_customer_booking_history_by_customer_id*/
--1.CUSTOMER
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Carina Farrears', 'cfarrears0@spotify.com', '04/05/2004', '0736690849');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Robyn Mahody', 'rmahody1@tinypic.com', '20/02/1991', '0702066430');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Dom Wandrey', 'dwandrey2@networkadvertising.org', '08/07/1996', '0871561535');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Kipp Axleby', 'kaxleby3@surveymonkey.com', '18/09/2003', '0406685975');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Coretta Jehu', 'cjehu4@ebay.co.uk', '12/10/2001', '0924338810');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Washington Ashbey', 'washbey5@ucoz.ru', '21/09/1990', '0272797780');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Ermina Tefft', 'etefft6@businessweek.com', '08/02/2005', '0277658862');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Hartwell Farguhar', 'hfarguhar7@discuz.net', '18/04/2001', '0191523679');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Aurelie Mossom', 'amossom8@facebook.com', '27/10/1997', '0669828057');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Manfred Prestage', 'mprestage9@mashable.com', '09/06/1993', '0453085602');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Darsie Twelftree', 'dtwelftreea@msu.edu', '24/02/1997', '0108810541');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Leonard Aldin', 'laldinb@hao123.com', '05/11/1997', '0933421235');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Crystie Ellett', 'cellettc@marketwatch.com', '28/03/1998', '0234091519');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Abbot Thrower', 'athrowerd@harvard.edu', '15/05/2005', '0515397093');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Mignonne Matthiae', 'mmatthiaee@ucoz.com', '23/03/1993', '0582922258');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Em Sodo', 'esodof@pinterest.com', '26/11/2002', '0806851357');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Talbert Bottoner', 'tbottonerg@amazon.co.jp', '14/05/1992', '0476074808');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Sylas Boddymead', 'sboddymeadh@wunderground.com', '26/09/2003', '0353007370');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Greggory Frankton', 'gfranktoni@elpais.com', '08/09/1996', '0769558596');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Arie Douthwaite', 'adouthwaitej@php.net', '04/01/1994', '0864482377');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Alaine Stanmer', 'astanmerk@plala.or.jp', '11/10/2005', '0621428938');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Juline Stood', 'jstoodl@ucoz.com', '25/01/2005', '0897250956');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Giles Gobbet', 'ggobbetm@google.nl', '15/06/2000', '0254573750');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Jori Pagden', 'jpagdenn@sciencedaily.com', '31/08/1991', '0912263477');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Aggi Duerdin', 'aduerdino@answers.com', '14/03/2004', '0397898756');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Anetta Nijs', 'anijsp@elegantthemes.com', '17/08/2006', '0467808391');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Winonah Downham', 'wdownhamq@t.co', '03/10/2000', '0318436056');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Maje Egle of Germany', 'megler@ehow.com', '03/06/1998', '0276245144');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Homerus Elsmere', 'helsmeres@army.mil', '10/01/2000', '0379585473');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Sandro Hardman', 'shardmant@123-reg.co.uk', '29/05/1992', '0404986812');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Mischa Figgen', 'mfiggenu@vk.com', '28/07/1991', '0512118685');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Evyn Mackness', 'emacknessv@home.pl', '02/10/1998', '0533249246');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Daphna Phair', 'dphairw@feedburner.com', '24/10/1997', '0915448520');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Ximenez Ambrosetti', 'xambrosettix@china.com.cn', '10/07/2002', '0197829064');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Roxana Agnolo', 'ragnoloy@ifeng.com', '27/01/1993', '0354976468');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Ruy McKim', 'rmckimz@com.com', '25/07/1999', '0414898579');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Reina Puzey', 'rpuzey10@cnet.com', '18/07/1998', '0629224827');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Othello Armin', 'oarmin11@wsj.com', '02/11/1999', '0696698659');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Findley Thurstance', 'fthurstance12@vinaora.com', '16/12/1990', '0485796697');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Michele Stambridge', 'mstambridge13@cafepress.com', '07/07/1994', '0651798544');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Maressa Pirouet', 'mpirouet14@cloudflare.com', '31/12/1992', '0989947304');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Armand Cowl', 'acowl15@cafepress.com', '12/07/1993', '0631373543');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Tremayne Dyer', 'tdyer16@desdev.cn', '22/03/2000', '0145259751');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Eustace Stannas', 'estannas17@apache.org', '08/01/2003', '0087880907');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Edin Penbarthy', 'epenbarthy18@chron.com', '02/08/2002', '0566800701');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Delcine Hancock', 'dhancock19@cisco.com', '03/12/1993', '0629254317');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Mavra Crumby', 'mcrumby1a@surveymonkey.com', '02/07/1999', '0472879864');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Henry Thaine', 'hthaine1b@elegantthemes.com', '16/06/2004', '0729820594');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Raye Southern', 'rsouthern1c@spiegel.de', '01/12/2005', '0139829210');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Wilhelmine Colquhoun', 'wcolquhoun1d@cpanel.net', '17/02/1998', '0192683657');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Arny Crawcour', 'acrawcour1e@usgs.gov', '10/12/2004', '0231925155');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Rawley Rice', 'rrice1f@yellowpages.com', '04/09/1994', '0208626626');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Ainslee Simonassi', 'asimonassi1g@sina.com.cn', '10/09/1990', '0658460943');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Giustina Habbal', 'ghabbal1h@icio.us', '03/01/2000', '0323131198');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Mersey Finby', 'mfinby1i@wordpress.org', '03/01/2004', '0378304158');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Reggi Winders', 'rwinders1j@walmart.com', '28/12/1994', '0509551004');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Caroljean Sussams', 'csussams1k@people.com.cn', '08/03/1996', '0589187970');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Ophelia Sturgis', 'osturgis1l@linkedin.com', '03/10/2005', '0323601827');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Brod Ranklin', 'branklin1m@barnesandnoble.com', '20/11/1993', '0411039228');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Vanya Haldane', 'vhaldane1n@cnet.com', '03/11/1993', '0266172087');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Sean Ingre', 'singre1o@comcast.net', '25/06/1999', '0271915346');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Wilton Stonnell', 'wstonnell1p@liveinternet.ru', '24/06/2000', '0565712100');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Benni Ede', 'bede1q@mtv.com', '12/02/1997', '0982669283');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Edyth Daykin', 'edaykin1r@gizmodo.com', '08/07/1992', '0541428163');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Guglielma Pearne', 'gpearne1s@wsj.com', '19/10/2004', '0366643900');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Orv Egiloff', 'oegiloff1t@about.me', '05/12/1994', '0584960405');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Terry Scandrite', 'tscandrite1u@yellowpages.com', '02/02/1997', '0112246719');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Tome Esselen', 'tesselen1v@merriam-webster.com', '04/11/2003', '0937995916');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Riccardo MacClay', 'rmacclay1w@nytimes.com', '19/12/2004', '0201151628');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Lilli Storks', 'lstorks1x@smugmug.com', '25/08/2002', '0968891752');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Babette Hofner', 'bhofner1y@baidu.com', '10/06/2002', '0865965679');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Lula Outibridge', 'loutibridge1z@hugedomains.com', '05/03/1991', '0224128307');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Linet Aynsley', 'laynsley20@bandcamp.com', '12/06/2000', '0903202621');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Pammi Earthfield', 'pearthfield21@amazonaws.com', '29/05/2006', '0368379474');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Rube Goldthorpe', 'rgoldthorpe22@hexun.com', '23/02/2006', '0275788052');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Ros Fransoni', 'rfransoni23@e-recht24.de', '16/06/1997', '0904604254');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Chen Shavel', 'cshavel24@ocn.ne.jp', '10/12/2003', '0629061721');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Joyan Ingray', 'jingray25@netlog.com', '23/01/1999', '0508181200');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Cooper Radish', 'cradish26@state.gov', '08/11/2005', '0965390731');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Whitaker Redolfi', 'wredolfi27@paginegialle.it', '02/11/2005', '0372884338');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Salli Chinge', 'schinge28@rakuten.co.jp', '06/10/1997', '0971783024');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Gregg Dumbar', 'gdumbar29@hhs.gov', '17/02/1992', '0573130212');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Zachary Handrek', 'zhandrek2a@nytimes.com', '01/12/1995', '0781161470');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Virgina Gawn', 'vgawn2b@1688.com', '22/10/2000', '0411550079');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Aleen Trenchard', 'atrenchard2c@zimbio.com', '21/01/1998', '0176704862');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Bernette Hallgath', 'bhallgath2d@elegantthemes.com', '10/04/1990', '0355063902');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Shep Lindeman', 'slindeman2e@bandcamp.com', '19/01/1996', '0655861505');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Wally Anmore', 'wanmore2f@usnews.com', '01/01/1992', '0901881407');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Carey Harnwell', 'charnwell2g@rakuten.co.jp', '04/03/1990', '0977464860');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Nelle Slocket', 'nslocket2h@indiatimes.com', '18/01/1995', '0766331966');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Jesus Sommerville', 'jsommerville2i@furl.net', '05/12/1998', '0017661388');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Siusan Dungey', 'sdungey2j@reuters.com', '15/06/1996', '0615733014');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Halley Ivain', 'hivain2k@github.com', '02/03/1996', '0267434128');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Cornall Hutable', 'chutable2l@xinhuanet.com', '25/09/2004', '0631476676');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Fay MacTague', 'fmactague2m@goo.ne.jp', '05/12/1993', '0332815326');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Adria Trice', 'atrice2n@csmonitor.com', '02/04/2002', '0245383769');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Farris Shepland', 'fshepland2o@blogs.com', '24/10/1995', '0191217910');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('El Clough', 'eclough2p@howstuffworks.com', '03/05/2000', '0224427625');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Johan Hazeldene', 'jhazeldene2q@eventbrite.com', '19/11/1997', '0226089071');
insert into customer(customer_name,gmail,date_of_birth,phone_number) values('Ileane Kingsnode', 'ikingsnode2r@over-blog.com', '07/11/2005', '0614987082');

--2.EMPLOYEE
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Salim Castelijn', 'scastelijn0@ocn.ne.jp', '20/01/2002', '0933065217');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Audrye Doby', 'adoby1@ifeng.com', '04/02/1991', '0585477017');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Constanta Honniebal', 'chonniebal2@over-blog.com', '24/04/1998', '0376875025');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Rhody Flood', 'rflood3@reuters.com', '29/05/1998', '0161009303');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Jemie Sowter', 'jsowter4@comsenz.com', '05/07/1999', '0154633140');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Burlie Morilla', 'bmorilla5@cpanel.net', '15/02/1998', '0733050389');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Anabelle Iacobo', 'aiacobo6@ftc.gov', '11/11/2005', '0482123927');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Allister McCoughan', 'amccoughan7@symantec.com', '28/12/1997', '0313190464');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Phelia Cordero', 'pcordero8@jalbum.net', '02/09/1999', '0054483714');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Emmalynne Hamsson', 'ehamsson9@ehow.com', '05/09/2003', '0896256572');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Genia MacRonald', 'gmacronalda@lycos.com', '24/04/1994', '0117538333');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Neddy Clint', 'nclintb@a8.net', '10/09/2003', '0773635855');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Vanya Elsie', 'velsiec@comsenz.com', '09/02/1991', '0649463663');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Eda Vogele', 'evogeled@netvibes.com', '26/01/2005', '0646950422');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Peterus Van der Son', 'pvane@bbc.co.uk', '20/10/1997', '0499668529');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Korry Nolli', 'knollif@accuweather.com', '16/07/1995', '0657102522');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Lydie Abrahamian', 'labrahamiang@japanpost.jp', '10/05/1991', '0187849210');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Lissa Moy', 'lmoyh@google.ru', '18/10/2001', '0228613979');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Cary Orwin', 'corwini@pcworld.com', '08/09/2004', '0464565087');
insert into employee(employee_name,gmail,date_of_birth,phone_number) values('Anthea Juan', 'ajuanj@list-manage.com', '11/12/1994', '0544695194');

--3.FIELD_TYPE
insert into field_type(field_type_name,price_per_hour) values('Sân 5', 120000);
insert into field_type(field_type_name,price_per_hour) values('Sân 7', 180000);

--4.FIELD
insert into FIELD(field_type_id) values(2);
insert into FIELD(field_type_id) values(1);
insert into FIELD(field_type_id) values(1);
insert into FIELD(field_type_id) values(1);
insert into FIELD(field_type_id) values(2);
insert into FIELD(field_type_id) values(2);

--5.DRINK
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('C2', 7000, 10000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('Sting', 7000, 10000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('Pepsi', 6600, 9000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('Cola', 7200, 10000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('Revise', 8000, 12000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('7up', 6000, 10000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('Mirinda', 6000, 11000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('Monster', 10000, 15000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('Trà bí đao', 6000, 10000, 100);
insert into DRINK(drink_name,import_price,selling_price,number_in_stock) values('Nước suối', 3000, 5000, 100);

--6.RESERVATION
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('5/1/2023',  '6/1/2023','17:00', '18:00', 20, 78, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('12/1/2023',  '14/1/2023','18:00', '19:00', 6, 22, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('13/1/2023',  '15/1/2023','7:00', '9:00', 20, 86, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('17/1/2023',  '18/1/2023','8:00', '9:00', 6, 99, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('20/1/2023',  '21/1/2023','11:00', '13:00', 15, 92, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('23/1/2023',  '24/1/2023','18:00', '20:00', 20, 62, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('28/1/2023',  '29/1/2023','15:00', '16:00', 7, 61, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('2/2/2023',  '4/2/2023','11:00', '13:00', 18, 83, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('18/2/2023',  '20/2/2023','9:00', '10:00', 7, 32, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('21/2/2023',  '23/2/2023','12:00', '13:00', 16, 24, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('22/2/2023',  '23/2/2023','8:00', '10:00', 14, 94, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('24/2/2023',  '25/2/2023','17:00', '18:00', 3, 61, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('1/3/2023',  '2/3/2023','18:00', '20:00', 1, 17, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('13/3/2023',  '14/3/2023','14:00', '16:00', 20, 71, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('19/3/2023',  '20/3/2023','19:00', '20:00', 11, 10, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('22/3/2023',  '24/3/2023','11:00', '12:00', 9, 33, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('22/3/2023',  '24/3/2023','12:00', '14:00', 2, 89, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('5/4/2023',  '6/4/2023','20:00', '21:00', 15, 82, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('14/4/2023',  '15/4/2023','17:00', '19:00', 3, 76, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('15/4/2023',  '16/4/2023','18:00', '19:00', 11, 19, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('16/4/2023',  '17/4/2023','7:00', '9:00', 11, 27, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('22/4/2023',  '23/4/2023','8:00', '9:00', 4, 4, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('29/4/2023',  '30/4/2023','11:00', '12:00', 17, 89, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('30/4/2023',  '2/5/2023','18:00', '19:00', 10, 42, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('6/5/2023',  '7/5/2023','15:00', '16:00', 8, 69, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('24/5/2023',  '25/5/2023','11:00', '13:00', 12, 72, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('26/5/2023',  '27/5/2023','9:00', '10:00', 5, 67, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('28/5/2023',  '29/5/2023','12:00', '14:00', 16, 98, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('28/5/2023',  '30/5/2023','8:00', '9:00', 16, 100, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('29/5/2023',  '30/5/2023','17:00', '18:00', 16, 6, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('29/5/2023',  '31/5/2023','18:00', '19:00', 15, 74, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('29/5/2023',  '31/5/2023','14:00', '15:00', 2, 3, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('7/6/2023',  '8/6/2023','19:00', '20:00', 9, 77, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('11/6/2023',  '12/6/2023','11:00', '12:00', 9, 7, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('20/6/2023',  '22/6/2023','18:00', '19:00', 7, 3, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('26/6/2023',  '28/6/2023','15:00', '16:00', 5, 93, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('1/7/2023',  '3/7/2023','11:00', '12:00', 13, 41, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('1/7/2023',  '2/7/2023','9:00', '10:00', 4, 84, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('7/7/2023',  '9/7/2023','12:00', '13:00', 15, 88, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('11/7/2023',  '13/7/2023','8:00', '9:00', 12, 53, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('12/7/2023',  '13/7/2023','17:00', '18:00', 5, 89, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('14/7/2023',  '16/7/2023','18:00', '20:00', 17, 24, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('21/7/2023',  '22/7/2023','14:00', '15:00', 6, 39, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('27/7/2023',  '28/7/2023','19:00', '21:00', 5, 93, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('28/7/2023',  '30/7/2023','14:00', '16:00', 20, 61, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('29/7/2023',  '30/7/2023','19:00', '20:00', 2, 3, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('1/8/2023',  '3/8/2023','11:00', '13:00', 2, 63, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('1/8/2023',  '3/8/2023','18:00', '19:00', 5, 22, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('7/8/2023',  '9/8/2023','15:00', '16:00', 13, 21, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('16/8/2023',  '17/8/2023','11:00', '13:00', 13, 9, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('28/8/2023',  '30/8/2023','9:00', '10:00', 13, 4, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('1/9/2023',  '2/9/2023','12:00', '14:00', 13, 14, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('3/9/2023',  '5/9/2023','8:00', '10:00', 14, 6, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('10/9/2023',  '11/9/2023','17:00', '18:00', 5, 87, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('10/9/2023',  '12/9/2023','17:00', '18:00', 12, 30, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('17/9/2023',  '19/9/2023','18:00', '20:00', 17, 93, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('18/9/2023',  '20/9/2023','7:00', '8:00', 13, 5, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('20/9/2023',  '22/9/2023','20:00', '22:00', 2, 40, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('29/9/2023',  '30/9/2023','11:00', '12:00', 13, 58, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('4/10/2023',  '6/10/2023','18:00', '20:00', 4, 38, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('12/10/2023',  '14/10/2023','15:00', '16:00', 6, 97, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('14/10/2023',  '15/10/2023','11:00', '12:00', 5, 90, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('21/10/2023',  '23/10/2023','9:00', '10:00', 17, 45, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('27/10/2023',  '28/10/2023','12:00', '13:00', 16, 12, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('28/10/2023',  '29/10/2023','8:00', '10:00', 17, 42, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('1/11/2023',  '3/11/2023','17:00', '18:00', 8, 7, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('4/11/2023',  '6/11/2023','18:00', '20:00', 3, 4, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('10/11/2023',  '12/11/2023','14:00', '15:00', 4, 99, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('14/11/2023',  '15/11/2023','19:00', '20:00', 5, 83, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('14/11/2023',  '15/11/2023','11:00', '12:00', 6, 18, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('19/11/2023',  '20/11/2023','12:00', '13:00', 6, 84, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('30/11/2023',  '1/12/2023','10:00', '11:00', 16, 55, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('3/12/2023',  '4/12/2023','17:00', '18:00', 15, 30, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('14/12/2023',  '15/12/2023','18:00', '19:00', 3, 92, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('17/12/2023',  '18/12/2023','7:00', '8:00', 7, 10, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('23/12/2023',  '25/12/2023','8:00', '10:00', 12, 87, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('27/12/2023',  '28/12/2023','11:00', '12:00', 5, 32, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('29/12/2023',  '31/12/2023','18:00', '20:00', 4, 35, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('5/1/2024',  '7/1/2024','15:00', '17:00', 11, 77, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('6/1/2024',  '8/1/2024','11:00', '12:00', 5, 92, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('8/1/2024',  '10/1/2024','9:00', '11:00', 20, 79, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('12/1/2024',  '13/1/2024','12:00', '13:00', 1, 31, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('16/1/2024',  '17/1/2024','8:00', '9:00', 19, 22, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('18/1/2024',  '19/1/2024','17:00', '19:00', 7, 90, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('25/1/2024',  '27/1/2024','18:00', '19:00', 7, 12, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('10/2/2024',  '11/2/2024','14:00', '16:00', 18, 78, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('11/2/2024',  '12/2/2024','19:00', '21:00', 13, 84, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('13/2/2024',  '14/2/2024','11:00', '12:00', 14, 36, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('27/2/2024',  '28/2/2024','18:00', '19:00', 4, 62, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('27/2/2024',  '29/2/2024','15:00', '17:00', 20, 13, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('5/3/2024',  '6/3/2024','11:00', '12:00', 16, 87, 6);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('11/3/2024',  '12/3/2024','9:00', '11:00', 10, 85, 1);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('12/3/2024',  '13/3/2024','12:00', '13:00', 3, 42, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('12/3/2024',  '14/3/2024','8:00', '10:00', 19, 83, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('7/4/2024',  '9/4/2024','17:00', '18:00', 18, 34, 3);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('8/4/2024',  '10/4/2024','18:00', '19:00', 5, 40, 2);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('15/4/2024',  '17/4/2024','14:00', '15:00', 19, 94, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('16/4/2024',  '18/4/2024','20:00', '21:00', 1, 76, 5);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('26/4/2024',  '28/4/2024','20:00', '22:00', 5, 100, 4);
insert into reservation(created_date,match_date,time_begin,time_end,employee_id,customer_id,field_id) values('29/4/2024',  '30/4/2024','21:00', '22:00', 11, 24, 4);


--7.CONFORMATION
insert into conformation(payment_status,reservation_id,created_date) values( 1, 1,'5/1/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 2,'12/1/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 3,'13/1/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 4,'17/1/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 5,'20/1/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 6,'23/1/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 7,'28/1/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 8,'2/2/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 9,'18/2/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 10,'21/2/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 11,'22/2/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 12,'24/2/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 13,'1/3/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 14,'13/3/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 15,'19/3/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 16,'22/3/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 17,'22/3/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 18,'5/4/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 19,'14/4/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 20,'15/4/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 21,'16/4/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 22,'22/4/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 23,'29/4/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 24,'30/4/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 25,'6/5/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 26,'24/5/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 27,'26/5/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 28,'28/5/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 29,'28/5/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 30,'29/5/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 31,'29/5/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 32,'29/5/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 33,'7/6/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 34,'11/6/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 35,'20/6/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 36,'26/6/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 37,'1/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 38,'1/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 39,'7/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 40,'11/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 41,'12/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 42,'14/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 43,'21/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 44,'27/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 45,'28/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 46,'29/7/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 47,'1/8/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 48,'1/8/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 49,'7/8/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 50,'16/8/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 51,'28/8/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 52,'1/9/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 53,'3/9/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 54,'10/9/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 55,'10/9/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 56,'17/9/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 57,'18/9/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 58,'20/9/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 59,'29/9/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 60,'4/10/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 61,'12/10/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 62,'14/10/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 63,'21/10/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 64,'27/10/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 65,'28/10/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 66,'1/11/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 67,'4/11/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 68,'10/11/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 69,'14/11/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 70,'14/11/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 71,'19/11/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 72,'30/11/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 73,'3/12/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 74,'14/12/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 75,'17/12/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 76,'23/12/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 77,'27/12/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 78,'29/12/2023');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 79,'5/1/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 80,'6/1/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 81,'8/1/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 82,'12/1/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 83,'16/1/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 84,'18/1/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 85,'25/1/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 86,'10/2/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 87,'11/2/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 88,'13/2/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 89,'27/2/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 90,'27/2/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 91,'5/3/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 92,'11/3/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 93,'12/3/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 94,'12/3/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 95,'7/4/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 96,'8/4/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 97,'15/4/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 98,'16/4/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 0, 99,'26/4/2024');
insert into conformation(payment_status,reservation_id,created_date) values( 1, 100,'29/4/2024');

--8.DRINK_ORDER
insert into drink_order(created_date,conformation_id) values('6/1/2023', 1);
insert into drink_order(created_date,conformation_id) values('14/1/2023', 2);
insert into drink_order(created_date,conformation_id) values('15/1/2023', 3);
insert into drink_order(created_date,conformation_id) values('18/1/2023', 4);
insert into drink_order(created_date,conformation_id) values('21/1/2023', 5);
insert into drink_order(created_date,conformation_id) values('24/1/2023', 6);
insert into drink_order(created_date,conformation_id) values('29/1/2023', 7);
insert into drink_order(created_date,conformation_id) values('4/2/2023', 8);
insert into drink_order(created_date,conformation_id) values('20/2/2023', 9);
insert into drink_order(created_date,conformation_id) values('23/2/2023', 10);
insert into drink_order(created_date,conformation_id) values('23/2/2023', 11);
insert into drink_order(created_date,conformation_id) values('25/2/2023', 12);
insert into drink_order(created_date,conformation_id) values('2/3/2023', 13);
insert into drink_order(created_date,conformation_id) values('14/3/2023', 14);
insert into drink_order(created_date,conformation_id) values('20/3/2023', 15);
insert into drink_order(created_date,conformation_id) values('24/3/2023', 16);
insert into drink_order(created_date,conformation_id) values('24/3/2023', 17);
insert into drink_order(created_date,conformation_id) values('6/4/2023', 18);
insert into drink_order(created_date,conformation_id) values('15/4/2023', 19);
insert into drink_order(created_date,conformation_id) values('16/4/2023', 20);
insert into drink_order(created_date,conformation_id) values('17/4/2023', 21);
insert into drink_order(created_date,conformation_id) values('23/4/2023', 22);
insert into drink_order(created_date,conformation_id) values('30/4/2023', 23);
insert into drink_order(created_date,conformation_id) values('2/5/2023', 24);

select * from drink_item;
select * from drink_order;
--9.DRINK_ITEM
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(1, 1, 8, 7);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(1, 2, 4, 4);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(1, 3, 3, 7);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(2, 1, 5, 2);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(2, 2, 9, 10);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(2, 3, 5, 10);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(3, 1, 5, 10);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(3, 2, 1, 5);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(3, 3, 2, 9);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(3, 4, 8, 1);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(4, 1, 9, 5);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(5, 1, 9, 1);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(6, 1, 5, 10);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(6, 2, 3, 9);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(6, 3, 3, 5);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(6, 4, 4, 5);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(6, 5, 10, 2);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(7, 1, 10, 3);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(7, 2, 6, 8);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(7, 3, 3, 10);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(8, 1, 7, 1);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(8, 2, 5, 7);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(8, 3, 6, 9);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(8, 4, 6, 6);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(8, 5, 3, 6);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(9, 1, 6, 1);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(9, 2, 10, 9);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(9, 3, 1, 5);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(10, 1, 1, 8);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(10, 2, 9, 5);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(10, 3, 1, 3);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(10, 4, 4, 6);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(10, 5, 3, 8);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(11, 1, 1, 6);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(11, 2, 10, 4);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(11, 3, 8, 9);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(12, 1, 3, 1);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(12, 2, 7, 3);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(12, 3, 3, 5);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(13, 1, 1, 5);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(13, 2, 4, 3);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(13, 3, 8, 5);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(13, 4, 8, 2);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(14, 1, 3, 9);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(15, 1, 10, 2);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(15, 2, 4, 2);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(15, 3, 9, 6);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(15, 4, 10, 5);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(15, 5, 1, 7);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(16, 1, 4, 1);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(16, 2, 7, 1);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(16, 3, 3, 10);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(16, 4, 4, 2);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(16, 5, 3, 3);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(17, 1, 3, 10);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(18, 1, 1, 3);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(18, 2, 10, 1);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(18, 3, 4, 2);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(18, 4, 9, 1);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(19, 1, 3, 8);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(19, 2, 8, 9);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(20, 1, 9, 7);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(20, 2, 2, 4);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(20, 3, 2, 1);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(21, 1, 2, 2);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(22, 1, 1, 8);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(22, 2, 6, 2);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(22, 3, 2, 8);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(22, 4, 6, 6);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(23, 1, 1, 7);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(23, 2, 2, 4);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(23, 3, 10, 8);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(23, 4, 4, 1);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(23, 5, 2, 5);

insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(24, 1, 7, 9);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(24, 2, 9, 1);
insert into drink_item(drink_order_id,line_number,quantity,drink_id) values(24, 3, 9, 5);

--9.DRINK_ORDER;
--insert into payment(payment_method,conformation_id) values(2,1);
--insert into payment(payment_method,conformation_id) values(3,2);
insert into payment(payment_method,conformation_id) values(1,3);
insert into payment(payment_method,conformation_id) values(2,4);
insert into payment(payment_method,conformation_id) values(2,5);
insert into payment(payment_method,conformation_id) values(2,6);
insert into payment(payment_method,conformation_id) values(2,7);
insert into payment(payment_method,conformation_id) values(3,8);
insert into payment(payment_method,conformation_id) values(2,9);
insert into payment(payment_method,conformation_id) values(1,10);
insert into payment(payment_method,conformation_id) values(2,11);
insert into payment(payment_method,conformation_id) values(2,12);
insert into payment(payment_method,conformation_id) values(2,13);
insert into payment(payment_method,conformation_id) values(2,14);
insert into payment(payment_method,conformation_id) values(1,15);
insert into payment(payment_method,conformation_id) values(2,16);
insert into payment(payment_method,conformation_id) values(1,17);
insert into payment(payment_method,conformation_id) values(3,18);
insert into payment(payment_method,conformation_id) values(1,19);
insert into payment(payment_method,conformation_id) values(3,20);
insert into payment(payment_method,conformation_id) values(2,21);
insert into payment(payment_method,conformation_id) values(1,22);
insert into payment(payment_method,conformation_id) values(3,23);
insert into payment(payment_method,conformation_id) values(1,24);
--insert into payment(payment_method,conformation_id) values(2,25);
insert into payment(payment_method,conformation_id) values(1,26);
insert into payment(payment_method,conformation_id) values(3,27);
insert into payment(payment_method,conformation_id) values(1,28);
insert into payment(payment_method,conformation_id) values(1,29);
insert into payment(payment_method,conformation_id) values(2,30);
insert into payment(payment_method,conformation_id) values(3,31);
insert into payment(payment_method,conformation_id) values(3,32);
insert into payment(payment_method,conformation_id) values(3,33);
insert into payment(payment_method,conformation_id) values(3,34);
insert into payment(payment_method,conformation_id) values(3,35);
insert into payment(payment_method,conformation_id) values(1,36);
insert into payment(payment_method,conformation_id) values(2,37);
insert into payment(payment_method,conformation_id) values(2,38);
insert into payment(payment_method,conformation_id) values(2,39);
insert into payment(payment_method,conformation_id) values(2,40);
insert into payment(payment_method,conformation_id) values(1,41);
insert into payment(payment_method,conformation_id) values(3,42);
insert into payment(payment_method,conformation_id) values(2,43);
insert into payment(payment_method,conformation_id) values(3,44);
insert into payment(payment_method,conformation_id) values(3,45);
insert into payment(payment_method,conformation_id) values(1,46);
insert into payment(payment_method,conformation_id) values(1,47);
insert into payment(payment_method,conformation_id) values(1,48);
insert into payment(payment_method,conformation_id) values(3,49);
insert into payment(payment_method,conformation_id) values(2,50);
insert into payment(payment_method,conformation_id) values(3,51);
insert into payment(payment_method,conformation_id) values(3,52);
insert into payment(payment_method,conformation_id) values(3,53);
insert into payment(payment_method,conformation_id) values(1,54);
insert into payment(payment_method,conformation_id) values(3,55);
insert into payment(payment_method,conformation_id) values(3,56);
insert into payment(payment_method,conformation_id) values(1,57);
insert into payment(payment_method,conformation_id) values(2,58);
insert into payment(payment_method,conformation_id) values(3,59);
insert into payment(payment_method,conformation_id) values(1,60);
insert into payment(payment_method,conformation_id) values(3,61);
insert into payment(payment_method,conformation_id) values(1,62);
insert into payment(payment_method,conformation_id) values(1,63);
insert into payment(payment_method,conformation_id) values(2,64);
insert into payment(payment_method,conformation_id) values(3,65);
insert into payment(payment_method,conformation_id) values(2,66);
insert into payment(payment_method,conformation_id) values(3,67);
insert into payment(payment_method,conformation_id) values(3,68);
insert into payment(payment_method,conformation_id) values(2,69);
insert into payment(payment_method,conformation_id) values(2,70);
insert into payment(payment_method,conformation_id) values(3,71);
insert into payment(payment_method,conformation_id) values(3,72);
insert into payment(payment_method,conformation_id) values(3,73);
insert into payment(payment_method,conformation_id) values(1,74);
insert into payment(payment_method,conformation_id) values(1,75);
insert into payment(payment_method,conformation_id) values(3,76);
insert into payment(payment_method,conformation_id) values(3,77);
insert into payment(payment_method,conformation_id) values(1,78);
insert into payment(payment_method,conformation_id) values(1,79);
insert into payment(payment_method,conformation_id) values(1,80);
insert into payment(payment_method,conformation_id) values(3,81);
insert into payment(payment_method,conformation_id) values(3,82);
insert into payment(payment_method,conformation_id) values(1,83);
insert into payment(payment_method,conformation_id) values(1,84);
insert into payment(payment_method,conformation_id) values(3,85);
insert into payment(payment_method,conformation_id) values(1,86);
insert into payment(payment_method,conformation_id) values(2,87);
insert into payment(payment_method,conformation_id) values(1,88);
insert into payment(payment_method,conformation_id) values(1,89);
insert into payment(payment_method,conformation_id) values(3,90);
insert into payment(payment_method,conformation_id) values(1,91);
insert into payment(payment_method,conformation_id) values(1,92);
insert into payment(payment_method,conformation_id) values(2,93);
insert into payment(payment_method,conformation_id) values(3,94);
insert into payment(payment_method,conformation_id) values(1,95);
insert into payment(payment_method,conformation_id) values(3,96);
insert into payment(payment_method,conformation_id) values(2,97);
insert into payment(payment_method,conformation_id) values(2,98);
insert into payment(payment_method,conformation_id) values(2,99);
insert into payment(payment_method,conformation_id) values(3,100);
