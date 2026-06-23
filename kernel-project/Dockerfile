FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && apt-get install -y \
    build-essential nasm grub-pc-bin grub-common xorriso \
    mtools qemu-system-x86 gcc make
WORKDIR /root/env