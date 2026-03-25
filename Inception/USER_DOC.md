# User Documentation

## Services Provided

### NGINX Web Server
- Secure HTTPS web server and reverse proxy
- TLS/SSL encryption (port 443)
- Entry point for all web traffic

### WordPress
- Content Management System for creating and managing website content
- Accessible through NGINX
- Includes admin panel for site management

### MariaDB Database
- Database backend for WordPress
- Stores all content and user data
- Internal access only (not exposed externally)

### Bonus Services (if implemented)
- Redis: Performance caching
- FTP: File transfer
- Adminer: Database management interface
- Static website
- Custom service

## Starting and Stopping

### Start

make up
# Build and Start the infrastructure

### Stop the Infrastructure

make stop
# Stop the infrastructure
make down
# Stop and Clean containers and images
make fclean
# Full cleanup including volumes

### Restart Services
make re
# Rebuild everything

## Accessing Services

### WordPress Website
- URL: `https://sbonneau.42.fr`
- Accept security warning for self-signed certificates (development only)

### WordPress Admin Panel
- URL: `https://sbonneau.42.fr/wp-admin`
- Username: From `.env` file (`WP_ADMIN_USER`)
- Password: From `.env` file (`WP_ADMIN_PASSWORD`)

## Managing Credentials

### Location
All credentials are in `srcs/.env`


1. Stop services: `make down`
2. Edit `srcs/.env`
3. Clean data: `make fclean`
4. Rebuild: `make re`

## Checking Service Status

### Quick Check
```bash
sudo docker ps
```

Should show three healthy containers: nginx, wordpress, mariadb

### Health Status Indicators
- ✅ `Up X minutes (healthy)` - Service running correctly
- ⚠️ `Up X minutes (unhealthy)` - Service has issues
- ❌ `Exited (1)` - Service crashed
