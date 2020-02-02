#!/usr/bin/python3.8

from os import system
import subprocess
import re

cmd = ['upower', '-i', '/org/freedesktop/UPower/devices/battery_BAT0', "grep -E 'percentage'"]

upower = (subprocess.Popen(cmd, stdout=subprocess.PIPE).communicate()[0]).decode()

#print(upower)
perc = re.findall("percentage:\s*(\d+)%", upower)[0]
state = re.findall("state:\s*(charging|discharging)", upower)[0]
print("Percentage:", perc)
print("State:", state)
