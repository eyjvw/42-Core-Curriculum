#!/bin/bash
set -e

CERT_DIR="$(cd "$(dirname "$0")" && pwd)"
CERT_FILE="$CERT_DIR/cert.pem"
KEY_FILE="$CERT_DIR/key.pem"

if [ -f "$CERT_FILE" ] && [ -f "$KEY_FILE" ]; then
	echo "[certs] Certificates already exist. To regenerate, delete certs/*.pem first."
	exit 0
fi

FQDN=$(hostname -f 2>/dev/null || hostname 2>/dev/null || echo "localhost")
SHORT=$(hostname -s 2>/dev/null || echo "localhost")
LAN_IP=$(hostname -I 2>/dev/null | awk '{print $1}')

SAN="DNS:localhost,DNS:$FQDN,IP:127.0.0.1"
[ "$SHORT" != "$FQDN" ] && [ -n "$SHORT" ] && SAN="$SAN,DNS:$SHORT"
[ -n "$LAN_IP" ] && SAN="$SAN,IP:$LAN_IP"

echo "[certs] Generating self-signed TLS certificate..."
openssl req -x509 -newkey rsa:2048 \
	-keyout "$KEY_FILE" \
	-out "$CERT_FILE" \
	-days 365 -nodes \
	-subj "/CN=ft_transcendence" \
	-addext "subjectAltName=$SAN" \
	-addext "basicConstraints=critical,CA:FALSE" \
	-addext "keyUsage=digitalSignature,keyEncipherment" \
	-addext "extendedKeyUsage=serverAuth"

chmod 644 "$CERT_FILE"
chmod 644 "$KEY_FILE"

echo "[certs] Certificate generated with SANs: $SAN"
echo "        cert: $CERT_FILE"
echo "        key:  $KEY_FILE"
