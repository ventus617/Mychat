# Mychat
服务端使用Mysql
Mysql数据库表创建语句为：

create table t_user(
id bigint unsigned  auto_increment primary key,
name varchar(100),
tel varchar(100),
password varchar(100),
lable varchar(100),
iconId int
);

create table t_friend(
idA bigint unsigned ,
idB bigint unsigned 
);

create table t_friend(
id_link bigint unsigned ,
id_user bigint unsigned 
);

create table t_chat
(
	id_user bigint unsigned ,
	id_friend bigint unsigned,
    time varchar(50),
    content varchar(4096)
);

create table t_groupchat
(
	id_link bigint unsigned ,
	id_user bigint unsigned,
    time varchar(50),
    content varchar(4096)
);

