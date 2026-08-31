up:
	sudo docker-compose -f ./srcs/docker-compose.yml up --build -d

stop:
	sudo docker-compose -f ./srcs/docker-compose.yml stop

down:
	sudo docker-compose -f ./srcs/docker-compose.yml down -v
	sudo rm -rf /home/sbonneau/data/web/*
	sudo rm -rf /home/sbonneau/data/db/*

fclean: down
	sudo docker system prune --all

re: fclean up

.PHONY: up stop down fclean re
