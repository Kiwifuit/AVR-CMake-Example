# :computer: CMake + AVR Toolchain C Example :hammer_and_pick:

This repository contains boilerplate to flash an atmega32-based
microcontroller using C and CMake

## :package: Prerequisites

> [!IMPORTANT]
> *While `screen` is an optional dependency, it is highly required if you will need the `make monitor` task*

```sh
sudo apt update && sudo apt install -y \
  cmake \
  build-essential \
  avr-libc \
  gcc-avr \
  binutils-avr \
  avrdude
```

## :hammer_and_wrench: Configuration

```sh
cmake -B build -DDEVICE=<path to /dev/tty of target>
```

## :hammer_and_pick: Build

```sh
cd build
make flash # or monitor if `screen` is installed
```
