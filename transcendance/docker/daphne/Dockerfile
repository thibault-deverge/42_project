FROM python:3

#disable write to disk with python and disable buffering for output (for docker its better)
ENV PYTHONDONTWRITEBYTECODE 1
ENV PYTHONUNBUFFERED 1
ENV DJANGO_SETTINGS_MODULE=django_project.settings

EXPOSE 9000

COPY requirements.txt .
RUN pip install --upgrade pip && pip install -r requirements.txt
RUN pip install daphne==4.1.0

WORKDIR /django

CMD ["daphne", "-b", "0.0.0.0", "-p", "9000", "django_project.asgi:application"]
