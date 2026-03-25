# Inception

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

Inception is a system administration project that focuses on containerization using Docker.
The goal is to set up a small infrastructure composed of different services following specific rules, all running in a virtualized environment using Docker containers.

This project deepens understanding of system administration concepts by requiring the creation of a multi-service application infrastructure.
Each service runs in a dedicated Docker container, built from custom Dockerfiles (or penultimate stable versions of Alpine/Debian).
The infrastructure includes NGINX with TLSv1.2 or TLSv1.3, WordPress with php-fpm, and MariaDB, all orchestrated with docker-compose and secured with proper networking and volume management.

### Project Goals

- Understand and implement containerization with Docker
- Set up a complete web infrastructure with multiple services
- Learn about service orchestration using docker-compose
- Implement security best practices (TLS, secrets management, network isolation)
- Gain practical experience with system administration and DevOps concepts

## Instructions

### Prerequisites

- Docker Engine (version 20.10 or later recommended)
- Docker Compose (version 1.29 or later recommended)
- A domain name pointing to your server (or localhost configuration)
- Sufficient disk space for Docker images and volumes

### Installation

1. Clone the repository:
2. Configure your environment variables:
3. Add your domain to `/etc/hosts` (for local testing):

### Compilation/Build

The project uses a Makefile to simplify Docker operations:

make up
# Build and Start the infrastructure
make stop
# Stop the infrastructure
make down
# Stop and Clean containers and images
make fclean
# Full cleanup including volumes
make re
# Rebuild everything

### Accessing Services

Once the infrastructure is running:

- **WordPress**: https://your_login.42.fr
- **Adminer** (if bonus): https://your_login.42.fr/adminer

### Project Structure

```
inception/
├── Makefile
├── README.md
└── srcs/
    ├── docker-compose.yml
    ├── .env
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   └── conf/
        ├── nginx/
        │   ├── Dockerfile
        │   └── conf/
        └── wordpress/
            ├── Dockerfile
            └── conf/
```
## Project Description

### Docker Architecture

This project implements a microservices architecture using Docker containers. Each service is isolated in its own container, communicating through a dedicated Docker network. The infrastructure follows these principles:

- **One service per container**: Each container runs a single process (NGINX, MariaDB, or WordPress)
- **Custom images**: All containers are built from custom Dockerfiles using Alpine Linux or Debian Bullseye as base images
- **Persistent storage**: Data persistence is achieved through Docker volumes
- **Network isolation**: Services communicate through a custom Docker bridge network
- **Security**: TLS encryption, no passwords in Dockerfiles, environment variable management

### Main Design Choices

#### Base Images
- **Debian Bullseye**: Alternative choice for better compatibility with certain packages

#### Service Configuration
1. **NGINX**: Configured as a reverse proxy with TLSv1.2/TLSv1.3 support, serving as the sole entry point
2. **WordPress + php-fpm**: Separated web server (NGINX) from PHP processing for better performance and security
3. **MariaDB**: Database service with persistent storage and secure credential management

#### Orchestration
- **docker-compose**: Manages multi-container deployment, ensuring proper startup order with `depends_on` directives

### Technical Comparisons

#### Virtual Machines vs Docker

| Aspect | Virtual Machines | Docker Containers |
|--------|------------------|-------------------|
| **Virtualization Level** | Hardware-level (hypervisor) | OS-level (containerization) |
| **Resource Usage** | Heavy (GBs of RAM, full OS) | Lightweight (MBs, shared kernel) |
| **Startup Time** | Minutes | Seconds |
| **Isolation** | Complete (separate kernel) | Process-level (shared kernel) |
| **Portability** | Limited (large image sizes) | High (small, layered images) |
| **Use Case** | Full OS isolation, different kernels | Application isolation, microservices |
| **Performance** | Overhead from hypervisor | Near-native performance |

**Why Docker for this project**: Docker provides sufficient isolation for running multiple services while maintaining low resource overhead, fast deployment, and easy reproducibility across different environments.

#### Secrets vs Environment Variables

| Aspect | Docker Secrets | Environment Variables |
|--------|----------------|----------------------|
| **Storage** | Encrypted in Swarm, mounted as files | Stored in memory, visible in `docker inspect` |
| **Security** | More secure, not visible in logs | Can leak through logs, process lists |
| **Scope** | Docker Swarm (not in Compose standalone) | Available in Compose and Swarm |
| **Access** | Read from `/run/secrets/<secret_name>` | Accessed via `$ENV_VAR` |
| **Updates** | Requires service recreation | Can be changed without rebuild |
| **Best For** | Production credentials, API keys | Non-sensitive configuration |

**Project choice**: Environment variables are used (via `.env` file) as the project uses docker-compose without Swarm. For production, Docker Secrets would be preferred. Sensitive data is kept out of Dockerfiles and version control.

#### Docker Network vs Host Network

| Aspect | Docker Network (Bridge) | Host Network |
|--------|------------------------|--------------|
| **Isolation** | Containers have separate IP addresses | Container shares host's network stack |
| **Port Mapping** | Requires explicit mapping (-p) | Direct access to host ports |
| **Security** | Better isolation between containers | No network isolation |
| **Performance** | Slight overhead from NAT | No overhead, maximum performance |
| **DNS** | Docker provides internal DNS | Uses host's DNS |
| **Use Case** | Microservices, multi-container apps | High-performance networking needs |

**Project choice**: Custom bridge network (`inception-network`) is used to:
- Isolate services from the host and other Docker networks
- Enable service discovery by container name
- Control inter-container communication
- Maintain security through network segmentation

#### Docker Volumes vs Bind Mounts

| Aspect | Docker Volumes | Bind Mounts |
|--------|----------------|-------------|
| **Management** | Managed by Docker (`docker volume`) | Direct host filesystem path |
| **Location** | `/var/lib/docker/volumes/` | Any path on host |
| **Portability** | Platform-independent | Path must exist on host |
| **Performance** | Optimized by Docker | Dependent on host filesystem |
| **Backup** | Easier with Docker commands | Standard filesystem backup |
| **Permissions** | Docker manages ownership | Host system permissions apply |
| **Use Case** | Persistent data, production | Development, configuration files |

**Project choice**: Docker volumes are used for persistent data (MariaDB, WordPress files) because:
- They survive container deletion and recreation
- Docker manages the storage location and permissions
- They're more portable across different host systems
- They comply with project requirements for data persistence

### Sources and Containers

- **Base**: Debian Bullseye

#### NGINX Container
- **Purpose**: HTTPS-only web server and reverse proxy
- **Configuration**: Custom nginx.conf with TLS setup, FastCGI proxy to WordPress
- **Volumes**: WordPress files mounted for serving static content
- **Exposed Port**: 443 (TLS)

#### WordPress Container
- **Purpose**: WordPress installation with php-fpm
- **Configuration**: Automated WordPress CLI setup, database connection, user creation
- **Volumes**: WordPress files persisted to volume
- **Dependencies**: MariaDB must be healthy before startup

#### MariaDB Container
- **Purpose**: Database backend for WordPress
- **Configuration**: Initialized with database, users, and permissions
- **Volumes**: Database files persisted to volume
- **Security**: No root remote access, secure credential management

## Resources

### Documentation
- [Docker Official Documentation](https://docs.docker.com/)
- [Docker Compose Reference](https://docs.docker.com/compose/compose-file/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress Developer Resources](https://developer.wordpress.org/)
- [MariaDB Documentation](https://mariadb.com/kb/en/documentation/)
- [WP-CLI Documentation](https://wp-cli.org/)

### Tutorials & Articles
- [Docker for Beginners](https://docker-curriculum.com/)
- [Understanding Docker Networking](https://docs.docker.com/network/)
- [Docker Volumes Deep Dive](https://docs.docker.com/storage/volumes/)
- [Dockerfile Best Practices](https://docs.docker.com/develop/develop-images/dockerfile_best-practices/)
- [NGINX SSL/TLS Configuration](https://nginx.org/en/docs/http/configuring_https_servers.html)
- [WordPress with Docker](https://developer.wordpress.org/advanced-administration/before-install/howto-install/#installation-using-docker)

### AI Usage Declaration

**AI Tools Used**: Claude (Anthropic)

**Tasks Assisted**:
    **Documentation**: Help structuring this README and explaining technical concepts

**Author**: sbonneau  
**42 Campus**: 42 LeHavre
**Completion Date**: January 30 2026
