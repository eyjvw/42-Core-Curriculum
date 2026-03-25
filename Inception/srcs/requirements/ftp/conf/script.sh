#!/bin/bash

FTP_PASSWORD=$(cat /run/secrets/ftp_password)

if ! id -u $FTP_USER > /dev/null 2>&1; then
    adduser --disabled-password --gecos "" $FTP_USER
    echo "$FTP_USER:$FTP_PASSWORD" | chpasswd
    echo $FTP_USER >> /etc/vsftpd.userlist
fi

mkdir -p /home/$FTP_USER/ftp
chown -R $FTP_USER:$FTP_USER /home/$FTP_USER/ftp
chmod -R 755 /home/$FTP_USER/ftp

exec "$@"
