#!/bin/bash

file="./reached_ips.txt"

if [ "$#" -lt 1 ]
then
	echo "No Argument supplied!"
else
	for ip in $(seq 0 255); do
		echo "ping -c 1 $1.$ip"
		ping -c 1 $1.$ip | grep '64 bytes' | cut -d ' ' -f 4 | tr -d ':' >> $file &
	done
fi
