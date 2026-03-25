FROM debian:12

RUN apt update && apt upgrade && apt install -y redis-server

RUN mkdir -p /var/lib/redis

COPY ./conf/redis.conf /etc/redis/redis.conf
COPY ./conf/script.sh .
RUN chmod +x script.sh

ENTRYPOINT ["./script.sh"]
CMD ["redis-server", "/etc/redis/redis.conf"]
