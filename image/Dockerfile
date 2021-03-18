FROM ubuntu:20.04

RUN apt-get update
RUN apt-get install -y clang wget unzip
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y make pkg-config libelf-dev gcc binutils-dev sudo jq

WORKDIR /workdir/libbpf
COPY libbpf-0.0.9.zip .
RUN unzip -q libbpf-0.0.9.zip && rm libbpf-0.0.9.zip
WORKDIR /workdir/libbpf/src
RUN make && make install

WORKDIR /workdir/linux-5.7
COPY linux-5.7.zip .
RUN unzip -q linux-5.7.zip && rm linux-5.7.zip
WORKDIR /workdir/linux-5.7/linux-5.7/tools/bpf/bpftool
RUN make && make install

WORKDIR /workdir
COPY data.bin /workdir/data.bin
COPY kern.c /workdir/kern.c
COPY run.sh /workdir/run.sh
