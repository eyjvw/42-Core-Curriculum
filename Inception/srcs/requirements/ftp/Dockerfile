FROM debian:12

RUN apt update && apt upgrade && apt install -y vsftpd

RUN mkdir -p /var/run/vsftpd/empty

COPY ./conf/vsftpd.conf /etc/vsftpd.conf
COPY ./conf/script.sh .
RUN chmod +x script.sh

ENTRYPOINT ["./script.sh"]
CMD ["vsftpd", "/etc/vsftpd.conf"]
