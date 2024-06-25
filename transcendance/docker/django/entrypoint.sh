#!/bin/bash

tail -n +2 /django/single_page/static/scripts/utils/constants.js > /file.tmp
sed -i '1 i\export let address = "'$ALLOWED_HOST'"' /file.tmp
cat /file.tmp > /django/single_page/static/scripts/utils/constants.js
rm -rf file.tmp

cd /django/

python3 manage.py makemigrations
python3 manage.py migrate
python3 manage.py collectstatic --noinput

rm -rf /django/single_page/lib/node_modules/npm
npm install --prefix ./single_page -g npm@10.8.1
npm run watch-scss --prefix ./single_page &

python3 manage.py runserver 0.0.0.0:8000