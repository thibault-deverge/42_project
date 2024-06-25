FROM	alpine:3.17.5

# Update the package repository and install MariaDB and its client
RUN		apk update && apk upgrade \
		&& apk add mariadb mariadb-client

# Initialize MariaDB database and update the bind-address in the MariaDB configuration
RUN		mysql_install_db --user=mysql --datadir=/var/lib/mysql \
		&& sed -i "s/.*bind-address\s*=.*/bind-address=0.0.0.0/" /etc/my.cnf.d/mariadb-server.cnf \
		&& sed -i "s/skip-networking//" /etc/my.cnf.d/mariadb-server.cnf

# Copy the start script into the image and make it executable
COPY	./tools/start_script.sh .
RUN		chmod +x ./start_script.sh

# Expose MariaDB port
EXPOSE	3306

# Execute the start script when the container starts
CMD 	./start_script.sh
