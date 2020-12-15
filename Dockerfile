FROM gcc:10.2

ENV DEBIAN_FRONTEND noninteractive

WORKDIR /app
COPY ./ /app

RUN apt update && apt install -y software-properties-common

RUN apt-add-repository 'deb http://security.debian.org/debian-security stretch/updates main'

RUN apt-get update && apt-get install -y cmake openjdk-8-jdk yasm

RUN cmake .

RUN cmake --build ./out --target RokkitMC
