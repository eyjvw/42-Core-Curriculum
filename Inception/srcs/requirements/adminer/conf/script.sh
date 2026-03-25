#!/bin/bash

# Download Adminer if not present
if [ ! -f /var/www/html/index.php ]; then
    curl -L https://www.adminer.org/latest.php -o /var/www/html/index.php
fi

exec "$@"
