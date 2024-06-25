FROM nginx:alpine

EXPOSE 443

RUN apk add --no-cache openssl
RUN	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-out /etc/ssl/private/pong.crt \
	-keyout /etc/ssl/certs/pong.key \
	-subj "/C=FR/ST=FR/L=Ang/O=42/OU=42/CN=pong.42.fr/UID=pong"

COPY ./nginx.conf /etc/nginx/conf.d/default.conf
RUN sed -i 's/user  nginx;/user  root;/' /etc/nginx/nginx.conf

CMD ["nginx", "-g", "daemon off;"]
