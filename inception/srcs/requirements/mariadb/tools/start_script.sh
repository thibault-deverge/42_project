#!/bin/sh

# Start MariaDB in safe mode
mysqld_safe & sleep 5

# Check if the specified database already exists
if mysql -e "SHOW DATABASES LIKE '${DATABASE}';" | grep -q "${DATABASE}"; then
	echo "Database already exists. Starting it..."
else
    # If the database doesn't exist, create database and user
	echo "Database does not exist. Creation of it..."
	mysql -e "CREATE DATABASE IF NOT EXISTS ${DATABASE};"
	mysql -e "CREATE USER IF NOT EXISTS '${MARIADB_USER}'@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';"
	mysql -e "GRANT ALL PRIVILEGES ON ${DATABASE}.* TO '${MARIADB_USER}'@'%' IDENTIFIED BY '${MARIADB_PASSWORD}';"
	mysql -e "FLUSH PRIVILEGES;"
fi

# Shutdown the MariaDB server and start a new one with initialized database
mysqladmin -u root shutdown
exec mysqld_safe
