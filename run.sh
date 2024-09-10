#!/usr/bin/env bash

Xephyr -br -ac -reset -screen 1680x1050 :1 &
sleep 1s
export DISPLAY=:1
./dwm &
~/.fehbg &

