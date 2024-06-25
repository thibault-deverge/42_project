
##### VARIABLES
COMPOSE_PATH = ./srcs/docker-compose.yml
VOLUMES_PATH = /home/tdeverge/data

##### GENERAL RULES
all : up

up :
	mkdir -p $(VOLUMES_PATH)/wordpress 
	mkdir -p $(VOLUMES_PATH)/mariadb
	docker compose -f $(COMPOSE_PATH) up --build -d

down :
	docker compose -f $(COMPOSE_PATH) down -v

stop :
	docker compose -f $(COMPOSE_PATH) stop

start :
	mkdir -p $(VOLUMES_PATH)/wordpress 
	mkdir -p $(VOLUMES_PATH)/mariadb
	docker compose -f $(COMPOSE_PATH) start

##### EXEC INSIDE CONTAINER
nginx:
	docker exec -it nginx /bin/sh

mariadb:
	docker exec -it mariadb /bin/sh

wordpress:
	docker exec -it wordpress /bin/sh

##### LOGS
nginx_logs:
	docker logs nginx

mariadb_logs:
	docker logs mariadb

wordpress_logs:
	docker logs wordpress

##### CLEANING
clean: 
	docker image rm nginx:inception mariadb:inception wordpress:inception
	sudo rm -rf $(VOLUMES_PATH)/wordpress/* $(VOLUMES_PATH)/mariadb/*

re: clean up
