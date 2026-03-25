FROM debian:12

RUN apt update && apt upgrade && apt install -y nginx

RUN mkdir -p /var/www/static

COPY ./conf/nginx.conf /etc/nginx/nginx.conf
COPY ./conf/index.html /var/www/static/index.html

CMD ["nginx", "-g", "daemon off;"]
