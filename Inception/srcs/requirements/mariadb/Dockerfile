FROM debian:12

RUN apt update && apt upgrade && apt install -y mariadb-server && apt install -y gettext-base

COPY ./conf/50-server.cnf /etc/mysql/mariadb.conf.d/.
COPY ./conf/init.sql.template /etc/mysql/init.sql.template
COPY ./conf/script.sh .

RUN mkdir /run/mysqld && chmod +x script.sh

ENTRYPOINT ["/script.sh"]
CMD ["mysqld"]
