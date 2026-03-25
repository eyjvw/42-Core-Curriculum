#!/bin/sh

export DB_PASS=$(cat /run/secrets/db_pass)
export DB_ROOT_PASS=$(cat /run/secrets/db_root_pass)

envsubst < /etc/mysql/init.sql.template > /etc/mysql/init.sql
rm -f /etc/mysql/init.sql.template

mysql_install_db

exec "$@"
