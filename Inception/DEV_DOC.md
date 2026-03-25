# Developer Documentation

## Environment Setup from Scratch

### Prerequisites

**Install Docker and Docker Compose**
- Linux: Follow official Docker documentation for your distribution
- macOS: Install Docker Desktop
- Windows: Install Docker Desktop with WSL2

**Additional Tools**
- make
- Text editor (vim, nano, or VSCode)
- git

### Project Setup

1. **Clone the repository**
2. **Configure environment**: Copy `srcs/.env.example` to `srcs/.env` and edit values
3. **Configure domain**: Add domain to `/etc/hosts` for local testing
4. **Setup SSL**: Self-signed certificates generated automatically by NGINX container

### Environment Variables

Edit `srcs/.env` with:
- `DOMAIN_NAME`: Your domain (e.g., your_login.42.fr)
- `MYSQL_ROOT_PASSWORD`, `MYSQL_DATABASE`, `MYSQL_USER`, `MYSQL_PASSWORD`: Database credentials
- `WP_ADMIN_USER`, `WP_ADMIN_PASSWORD`, `WP_ADMIN_EMAIL`: WordPress admin
- `WP_USER`, `WP_USER_PASSWORD`, `WP_USER_EMAIL`: WordPress regular user

**Security**: Use strong passwords, never commit `.env` to version control.

## Project Architecture

### Service Dependencies
MariaDB → WordPress → NGINX

Each service depends on the previous one being healthy.

### Network
Custom bridge network `inception-network` enables:
- Service discovery by container name
- Network isolation
- Controlled inter-container communication

### Volumes
- `inception_wordpress`: WordPress files
- `inception_mariadb`: Database files

Volumes persist data even when containers are removed.

## Building and Launching

### Makefile Commands

```bash
make up         # Start all services
make down       # Stop all services
make fclean     # Remove containers, images, and volumes
make re         # Full rebuild (fclean + build + up)
```

### Build Process

**Step 1: Build images**
```bash
make build
```
Builds MariaDB, WordPress, and NGINX images from Dockerfiles.

**Step 2: Start services**
```bash
make up
```
Creates volumes, network, and starts containers in correct order.

**Step 3: Verify**
```bash
docker ps
```
All three containers should show "healthy" status.

### Service Startup Order

1. MariaDB starts and initializes database
2. WordPress waits for MariaDB health check, then installs WordPress
3. NGINX waits for WordPress health check, then starts serving traffic

Health checks ensure each service is ready before dependent services start.

## Container Management

### Viewing Containers

```bash
docker ps                    # List running containers
docker ps -a                 # List all containers
docker inspect <container>   # Detailed information
docker stats                 # Resource usage
docker top <container>       # Container processes
```

### Accessing Containers

```bash
docker exec -it nginx /bin/sh
docker exec -it wordpress /bin/bash
docker exec -it mariadb /bin/sh
```

### Managing Individual Services

```bash
docker-compose start <service>      # Start
docker-compose stop <service>       # Stop
docker-compose restart <service>    # Restart
docker-compose logs <service>       # View logs
docker-compose logs -f <service>    # Follow logs
```

## Volume and Data Management

### Volume Locations

Docker volumes are stored in `/var/lib/docker/volumes/` (Linux) or inside Docker Desktop VM (macOS/Windows).

### Volume Commands

```bash
docker volume ls                          # List volumes
docker volume inspect inception_wordpress # Inspect volume
docker volume rm inception_wordpress      # Remove volume (⚠️ deletes data)
```

### Accessing Volume Data

Use temporary container to access volume contents:
```bash
docker run --rm -v inception_wordpress:/data alpine ls -la /data
```

### Data Persistence

Data in volumes persists when:
- Containers are stopped
- Containers are removed
- Images are rebuilt

Data is only deleted when:
- Volumes are explicitly removed
- `make fclean` is run

## Data Storage

### Where Data is Stored

**WordPress Files**
- Volume: `inception_wordpress`
- Container path: `/var/www/html`
- Contents: WordPress installation, themes, plugins, uploads

**Database Files**
- Volume: `inception_mariadb`
- Container path: `/var/lib/mysql`
- Contents: Database files, system tables, WordPress data

### How Data Persists

1. **Volumes are separate from containers**: Removing containers doesn't delete volumes
2. **Managed by Docker**: Docker handles storage location and permissions
3. **Survives rebuilds**: Data persists through container recreation
4. **Explicit removal only**: Must use `docker volume rm` or `make fclean` to delete

### Verifying Persistence

Test data persistence:
1. Create test file in WordPress container
2. Stop and remove containers
3. Restart containers
4. Verify test file still exists

### Volume Inspection

Check what's in volumes:
```bash
docker volume inspect inception_wordpress
docker volume inspect inception_mariadb
```

View volume size:
```bash
docker system df -v
```
