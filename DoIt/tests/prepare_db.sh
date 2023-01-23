sudo -u postgres psql -c "ALTER USER postgres PASSWORD 'postgres';"
sudo -u postgres psql -c "DROP DATABASE IF EXISTS db_test;"
sudo -u postgres psql -c "CREATE DATABASE db_test;"

for file in data/*_data.json
do
    cat $file | jq -cr '.[]' | sed 's/\\[tn]//g' > data/$(basename "${file}" _data.json)_tmp.json
done

PGPASSWORD=postgres psql -U postgres -d db_test -h 127.0.0.1 -p 5432 -a -f fill_db.sql -v DIR="${PWD}/data"

rm -rf data/*_tmp.json