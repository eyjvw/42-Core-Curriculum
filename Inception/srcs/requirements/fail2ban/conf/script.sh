#!/bin/bash

mkdir -p /var/run/fail2ban
mkdir -p /var/log

# Ensure nginx log files exist to prevent startup issues
mkdir -p /var/log/nginx
: > /var/log/nginx/access.log
: > /var/log/nginx/error.log

exec "$@"
