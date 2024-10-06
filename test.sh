#!/usr/bin/env bash
# Xephyr -br -ac -reset -screen 1680x1050 :1 &

export DISPLAY=:1
sleep 1s
Xephyr -br -ac -reset -screen 2256x1504 :1 &
setbg &
exec dwm
