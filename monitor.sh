#!/bin/bash
port="$1"
[[ -c "$port" ]] || exit 1
stty -F "$port" raw 115200
cat "$port"
