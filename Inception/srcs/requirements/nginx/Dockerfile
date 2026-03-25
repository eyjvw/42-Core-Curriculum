FROM debian:12

RUN apt update && apt upgrade && apt install -y nginx && apt install openssl
RUN mkdir /etc/nginx/ssl && mkdir /etc/nginx/ssl/certs && mkdir /etc/nginx/ssl/private

RUN openssl req -x509 -nodes -days 365 \
    -subj  "/C=/ST=/O=/CN=sbonneau.42.fr" \
    -newkey rsa:2048 -keyout /etc/nginx/ssl/private/sbonneau.42.fr.key \
    -out /etc/nginx/ssl/certs/sbonneau.42.fr.crt;

COPY ./conf/nginx.conf /etc/nginx/.

CMD ["nginx", "-g", "daemon off;"]
