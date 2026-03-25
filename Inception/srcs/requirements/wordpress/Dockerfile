FROM debian:12

RUN apt update && apt upgrade && apt install -y \
        php-fpm \
	php-mysqli \
	curl

COPY ./conf/www.conf /etc/php/8.2/fpm/pool.d/.
COPY ./conf/script.sh .
RUN chmod +x script.sh


ENTRYPOINT ["./script.sh"]
CMD ["php-fpm8.2", "-F"]
