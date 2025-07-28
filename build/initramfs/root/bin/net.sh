#!/bin/sh
ip link set eth0 up
/sbin/udhcpc -i eth0 -s /etc/udhcpc/default.script
