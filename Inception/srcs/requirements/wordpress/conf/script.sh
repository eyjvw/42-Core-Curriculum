#!/bin/bash
cd /var/www/html

export DB_PASS=$(cat /run/secrets/db_pass)
export DB_ROOT_PASS=$(cat /run/secrets/db_root_pass)
export REDIS_PASS=$(cat /run/secrets/db_redis_pass)

curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar

chmod +x wp-cli.phar

./wp-cli.phar core download --allow-root
./wp-cli.phar config create --dbname=${DB_NAME} --dbuser=${DB_USER} --dbpass=${DB_PASS} --dbhost=${DB_HOST} --allow-root
./wp-cli.phar core install --url=localhost --title=inception --admin_user=${DB_ROOT_USER} --admin_password=${DB_ROOT_PASS} --admin_email=${DB_ROOT_MAIL} --allow-root
./wp-cli.phar user create ${WP_USER} ${WP_MAIL} --allow-root

./wp-cli.phar plugin install redis-cache --activate --allow-root
./wp-cli.phar config set WP_REDIS_HOST "${REDIS_HOST}" --type=constant --allow-root
./wp-cli.phar config set WP_REDIS_PORT "${REDIS_PORT}" --type=constant --allow-root
./wp-cli.phar config set WP_REDIS_PASSWORD "${REDIS_PASS}" --type=constant --allow-root
./wp-cli.phar redis enable --allow-root

exec "$@"
