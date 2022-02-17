
FROM ubuntu:20.04

RUN apt-get update
RUN apt-get install -y git
RUN apt-get install -y gcc
RUN apt-get install -y make
RUN apt-get install -y autoconf
RUN apt-get install -y libtool


RUN git clone https://github.com/vlm/asn1c.git
WORKDIR asn1c

COPY ./build.sh .
RUN ./build.sh; rm build.sh

WORKDIR /

