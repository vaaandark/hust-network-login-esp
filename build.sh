#!/bin/bash
python encrypt.py > config.h
arduino-cli core install esp8266:esp8266
arduino-cli compile -b esp8266:esp8266:nodemcu || exit 1
port="$1"
[[ -c "$port" ]] || exit 0
arduino-cli upload -p "$port" -b esp8266:esp8266:nodemcu
