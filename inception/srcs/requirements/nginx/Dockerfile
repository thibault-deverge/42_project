FROM	alpine:3.17.5

# Install ngind and openssl (TLS connection)
RUN		apk update && apk upgrade \
		&& apk add --no-cache nginx \
		&& apk add --no-cache openssl

# Create directorie for certificates and nginx config
RUN		mkdir -p /etc/nginx/ssl \
		&& mkdir -p /run/nginx

# Generate SSL certificate and key
RUN	openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
	-out /etc/nginx/ssl/inception.crt \
	-keyout /etc/nginx/ssl/inception.key \
	-subj "/C=FR/ST=FR/L=Ang/O=42/OU=42/CN=tdeverge.42.fr/UID=tdeverge"

# Copy custom configuration file inside nginx
COPY ./conf/nginx.conf /etc/nginx/http.d/nginx.conf

# Expose port 443 (https)
EXPOSE 443

# Start nginx and keep running it in background
CMD ["nginx", "-g", "daemon off;"]