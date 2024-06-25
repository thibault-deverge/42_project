FROM python:3

RUN apt-get update && apt-get install -y \
    curl \
    && rm -rf /var/lib/apt/lists/*
RUN curl -fsSL https://deb.nodesource.com/setup_18.x | bash - && \
    apt-get update && apt-get install -y nodejs

COPY requirements.txt .
RUN pip install --upgrade pip && pip install -r requirements.txt

ADD ./entrypoint.sh .
RUN chmod +x /entrypoint.sh

CMD ["/bin/sh", "./entrypoint.sh" ]
