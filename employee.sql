insert into USERS(last_name,first_name,phone_number,date_of_birth,email,pass_word,user_type) VALUES('Nguyễn','Văn A','0959953164','24/04/1935','nguyenvana854@example.com',crypt('nguyenvana',gen_salt('md5')),'employee');
insert into USERS(last_name,first_name,phone_number,date_of_birth,email,pass_word,user_type) VALUES('Trần','Thị B','0949933127','01/04/1974','tranthib162@example.com',crypt('tranthib',gen_salt('md5')),'employee');
insert into USERS(last_name,first_name,phone_number,date_of_birth,email,pass_word,user_type) VALUES('Lê','Văn C','0916276397','26/04/1990','levanc211@example.com',crypt('levanc',gen_salt('md5')),'employee');
insert into USERS(last_name,first_name,phone_number,date_of_birth,email,pass_word,user_type) VALUES('Phạm','Thị D','0956031744','02/01/1945','phamthid412@example.com',crypt('phamthid',gen_salt('md5')),'employee');
insert into USERS(last_name,first_name,phone_number,date_of_birth,email,pass_word,user_type) VALUES('Hoàng','Văn E','0936583377','15/01/1935','hoangvane935@example.com',crypt('hoangvane',gen_salt('md5')),'employee');
insert into USERS(last_name,first_name,phone_number,date_of_birth,email,pass_word,user_type) VALUES('Vũ','Thị F','0928936370','13/01/1965','vuthif172@example.com',crypt('vuthif',gen_salt('md5')),'employee');
INSERT INTO EMPLOYEES(user_id,onboard_date,salary) VALUES('4','26/05/2021','9000000');
INSERT INTO EMPLOYEES(user_id,onboard_date,salary) VALUES('3','13/04/2020','15000000');
INSERT INTO EMPLOYEES(user_id,onboard_date,salary) VALUES('1','02/09/2020','8500000');
INSERT INTO EMPLOYEES(user_id,onboard_date,salary) VALUES('6','17/10/2021','5000000');
INSERT INTO EMPLOYEES(user_id,onboard_date,salary) VALUES('5','04/10/2022','9500000');
INSERT INTO EMPLOYEES(user_id,onboard_date,salary) VALUES('2','02/05/2022','6000000');

insert into EMPLOYEE_ROLE(employee_id, role_id, date_assigned) values('4', '2', '26/5/2021');
insert into EMPLOYEE_ROLE(employee_id, role_id, date_assigned) values('3', '1', '14/3/2020');
insert into EMPLOYEE_ROLE(employee_id, role_id, date_assigned) values('1', '2', '2/9/2020');
insert into EMPLOYEE_ROLE(employee_id, role_id, date_assigned) values('6', '3', '17/10/2021');
insert into EMPLOYEE_ROLE(employee_id, role_id, date_assigned) values('5', '2', '04/10/2022');
insert into EMPLOYEE_ROLE(employee_id, role_id, date_assigned) values('2', '3', '2/5/2022');


insert into ROLES(role_id, role_name, description) values('1', 'Quản lí', 'Manager role');
insert into ROLES(role_id, role_name, description) values('2', 'Nhân viên', 'Employee role');
insert into ROLES(role_id, role_name, description) values('3', 'Bảo vệ', 'Security role');