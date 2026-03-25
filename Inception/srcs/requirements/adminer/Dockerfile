FROM debian:12

RUN apt update && apt upgrade && apt install -y php php-mysqli curl

RUN mkdir -p /var/www/html

COPY ./conf/script.sh .
RUN chmod +x script.sh

ENTRYPOINT ["./script.sh"]
CMD ["php", "-S", "0.0.0.0:8080", "-t", "/var/www/html"]
