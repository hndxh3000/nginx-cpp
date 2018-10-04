create table if not exists tb_mana(
		id serial primary key,
		passwd varchar(32) not null,
		type integer not null,
		last_login varchar(32),
		try_times integer);

create table if not exists tb_user(
		id varchar(32) primary key not null,
		passwd varchar(32) not null,
		type integer not null,
		name varchar(32) not null,
		last_login varchar(32),
		try_times integer);

create table if not exists tb_pos(
		id varchar(32) primary key not null,
		name varchar(32) not null,
		type integer not null,
		uid varchar(32) not null,
		passwd varchar(32) not null,
		descr varchar(256));	
