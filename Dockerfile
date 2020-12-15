FROM gcc:10.2

ENV DEBIAN_FRONTEND noninteractive

RUN mkdir -p /usr/share/man/man1
RUN apt-get update --fix-missing && apt-get install -y cmake openjdk-8-jdk yasm

RUN cmake .

RUN cmake --build ./out --target RokkitMC
