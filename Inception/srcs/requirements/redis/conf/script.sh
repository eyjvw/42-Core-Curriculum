#!/bin/bash

REDIS_PASS=$(cat /run/secrets/db_redis_pass)

# Ensure requirepass is set to the secret value
if grep -q "^requirepass" /etc/redis/redis.conf; then
    sed -i "s/^requirepass.*/requirepass ${REDIS_PASS}/" /etc/redis/redis.conf
else
    echo "requirepass ${REDIS_PASS}" >> /etc/redis/redis.conf
fi

exec "$@"
