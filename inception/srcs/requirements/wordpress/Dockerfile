FROM 	alpine:3.17.5

# Update the package list and install essential packages
RUN 	apk update && apk upgrade \
		&& apk add --no-cache wget \
		&& apk add php php-fpm php-phar php-curl php-mysqli php-iconv php-mbstring mariadb-client


RUN		sed -i "s/skip-networking//" /etc/my.cnf.d/mariadb-server.cnf

# Download wp-cli tool and make it a global executable
RUN		wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
		&& chmod +x wp-cli.phar \
		&& mv wp-cli.phar /usr/local/bin/wp

# Copy over the WordPress initialization script
COPY 	./tools/wp_script.sh .
RUN 	chmod +x ./wp_script.sh

# Modify PHP-FPM settings to accept fast CGI connection from other container (nginx)
RUN		sed -i "s/listen = 127.0.0.1:9000/listen = 9000/" /etc/php81/php-fpm.d/www.conf

# Modify PHP-FPM settings by uncommenting the clear_env setting. 
RUN sed -i "s/;clear_env = no/clear_env = no/" /etc/php81/php-fpm.d/www.conf

# Expose the port that PHP-FPM will run on
EXPOSE	9000

# Run the WordPress initialization script
CMD		./wp_script.sh
