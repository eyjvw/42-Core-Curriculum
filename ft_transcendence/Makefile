PROJECT_NAME := ft_transcendence
COMPOSE_FILE := docker-compose.yml
DC := docker compose -p $(PROJECT_NAME) -f $(COMPOSE_FILE)

.DEFAULT_GOAL := up

all: certs build up

certs:
	@bash certs/generate.sh

build:
	$(DC) build

up: certs
	$(DC) up -d --remove-orphans

down:
	$(DC) down --remove-orphans

restart: down up

rebuild: certs
	$(DC) build --no-cache
	$(DC) up -d --remove-orphans

logs:
	$(DC) logs -f

ps:
	$(DC) ps

clean:
	$(DC) down --rmi all --volumes --remove-orphans

fclean: clean
	docker system prune -af

stop:
	$(DC) stop

re: fclean build up

.PHONY: all certs build up down restart rebuild logs ps clean fclean re stop