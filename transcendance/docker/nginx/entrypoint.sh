#!/bin/bash

cp /etc/ssl/private/pong.crt /etc/ssldata/pong.crt
cp /etc/ssl/certs/pong.key /etc/ssldata/pong.key

nginx -g 'daemon off;'
