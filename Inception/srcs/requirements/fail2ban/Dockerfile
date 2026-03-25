FROM debian:12

RUN apt update && apt upgrade && apt install -y fail2ban iptables

COPY ./conf/fail2ban.local /etc/fail2ban/fail2ban.local
COPY ./conf/jail.local /etc/fail2ban/jail.local
COPY ./conf/script.sh /script.sh
RUN chmod +x /script.sh

ENTRYPOINT ["/script.sh"]
CMD ["fail2ban-server", "-f", "-x", "-v"]
