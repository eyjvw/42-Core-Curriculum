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
2. **Configure environment**: Edit `srcs/.env` (versioned, contains no password)
3. **Create the secrets**: see [Secrets](#secrets) below
4. **Configure domain**: Add domain to `/etc/hosts` for local testing
5. **Setup SSL**: Self-signed certificates generated automatically by NGINX container

### Environment Variables

Edit `srcs/.env` with:
- `DOMAIN_NAME`: Your domain (e.g., your_login.42.fr), used as the WordPress site URL
- `DB_HOST`, `DB_NAME`, `DB_USER`: MariaDB host (service name), database and WordPress database user
- `DB_ROOT_USER`, `DB_ROOT_MAIL`: WordPress administrator login (must not contain "admin") and email
- `WP_USER`, `WP_MAIL`: WordPress regular user
- `FTP_USER`: FTP login (it reads and writes the WordPress volume)
- `REDIS_HOST`, `REDIS_PORT`: Redis cache used by WordPress

### Secrets

Passwords are never stored in `srcs/.env`. They are Docker secrets read from the git-ignored
`secrets/` folder at the root of the project and mounted in `/run/secrets/` inside the containers:

```bash
mkdir -p secrets
openssl rand -hex 16 > secrets/db_pass.txt        # MariaDB password of DB_USER (used by WordPress)
openssl rand -hex 16 > secrets/db_root_pass.txt   # WordPress administrator (DB_ROOT_USER) password
openssl rand -hex 16 > secrets/db_ftp_pass.txt    # FTP_USER password
openssl rand -hex 16 > secrets/db_redis_pass.txt  # Redis requirepass
```

Use hexadecimal passwords (as above): they are passed to shell commands and SQL without escaping.
MariaDB `root` has no password and is only reachable from inside the `mariadb` container (unix socket).

**Security**: Use strong passwords, never commit the `secrets/` folder to version control.

## Project Architecture

### Service Dependencies
MariaDB → WordPress → NGINX

WordPress waits for the MariaDB healthcheck (`mysqladmin ping`); NGINX starts once WordPress is up.

### Network
Custom bridge network `inception` enables:
- Service discovery by container name
- Network isolation
- Controlled inter-container communication

### Volumes
- `srcs_web`: WordPress files (bind to `/home/sbonneau/data/web`)
- `srcs_db`: Database files (bind to `/home/sbonneau/data/db`)

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

**Step 1: Build images and start services**
```bash
make up
```
Creates the data folders, builds every image from its Dockerfile (each image is named after its service,
e.g. `nginx:inception`), then creates volumes, network, and starts containers in correct order.

**Step 2: Verify**
```bash
docker ps
```
All containers should be `Up`; `mariadb` should show `(healthy)`.

### Service Startup Order

1. MariaDB starts and initializes database
2. WordPress waits for MariaDB health check, then installs WordPress
3. NGINX starts once the WordPress container is up, then starts serving traffic

The MariaDB health check ensures the database is ready before WordPress installs itself.

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
docker exec -it wp-php /bin/bash
docker exec -it mariadb /bin/sh
```

### Managing Individual Services

```bash
docker compose -f srcs/docker-compose.yml start <service>      # Start
docker compose -f srcs/docker-compose.yml stop <service>       # Stop
docker compose -f srcs/docker-compose.yml restart <service>    # Restart
docker compose -f srcs/docker-compose.yml logs <service>       # View logs
docker compose -f srcs/docker-compose.yml logs -f <service>    # Follow logs
```

## Volume and Data Management

### Volume Locations

Docker volumes are stored in `/var/lib/docker/volumes/` (Linux) or inside Docker Desktop VM (macOS/Windows).

### Volume Commands

```bash
docker volume ls                          # List volumes
docker volume inspect srcs_web # Inspect volume
docker volume rm srcs_web      # Remove volume (⚠️ deletes data)
```

### Accessing Volume Data

Use temporary container to access volume contents:
```bash
docker run --rm -v srcs_web:/data alpine ls -la /data
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
- Volume: `srcs_web`
- Container path: `/var/www/html`
- Contents: WordPress installation, themes, plugins, uploads

**Database Files**
- Volume: `srcs_db`
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
docker volume inspect srcs_web
docker volume inspect srcs_db
```

View volume size:
```bash
docker system df -v
```
