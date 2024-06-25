#!/bin/sh

# Change to the web directory
cd /var/www

sleep 7

if [ -f "wp-config.php" ]; then
	echo "Wordpress already installed."
else
	echo "Proceeding wordpress installation..."
	# Download WordPress core files
	wp core download --allow-root

	# Create WordPress configuration file (wp-config.php)
	wp config create 	--dbname=$DATABASE  \
						--dbuser=$MARIADB_USER \
						--dbpass=$MARIADB_PASSWORD \
						--dbhost=mariadb \
						--allow-root

	# Install WordPress with initial settings
	wp core install 	--url=$DOMAIN_NAME \
						--title=Site \
						--admin_user=$WP_ADMIN \
						--admin_password=$WP_ADMIN_PASSWORD \
						--admin_email=spv@example.com \
						--skip-email \
						--allow-root

	# Create an additional WordPress user
	wp user create 		$WP_USER \
						"hulk@avengers.fr" \
						--role=author \
						--user_pass=$WP_USER_PASSWORD \
						--allow-root

	# Create directory for PHP-FPM sockets
	mkdir -p /run/php

	echo "Installation of wordpress is finish"
fi

# Start PHP-FPM
/usr/sbin/php-fpm81 -F
