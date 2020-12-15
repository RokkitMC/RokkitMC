FROM gcc:10.2

ENV DEBIAN_FRONTEND noninteractive

RUN echo deb http://ftp.us.debian.org/debian sid main >> /etc/apt/sources.list

RUN apt-get install -y cmake openjdk-8-jdk yasm

RUN cmake .

RUN cmake --build ./out --target RokkitMC
