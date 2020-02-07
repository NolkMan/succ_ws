FROM debian:latest

RUN mkdir /home/app
WORKDIR /home/app

RUN apt-get update 
RUN apt-get upgrade -y
RUN apt-get install -y apache2 build-essential libboost-all-dev cmake
RUN apt-get clean 
RUN rm -rf /var/lib/apt/lists/*

#ENV APACHE_RUN_USER www-data
#ENV APACHE_RUN_GROUP www-data
#ENV APACHE_RUN_DIR /var/www/
#ENV APACHE_LOG_DIR /var/log/apache2

COPY web/ /var/www/html/

EXPOSE 80

COPY data/ data/
COPY src/ src/
COPY script.sh ./
COPY CMakeLists.txt ./
RUN cmake . && make

EXPOSE 1337

CMD ["./script.sh"]
