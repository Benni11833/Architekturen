#!/usr/bin/python3.8

from scapy.all import *
import sys
import os

#block print output
sys.stdout = open(os.devnull, 'w')

ip="172.217.18.99"
ans= []
sport=22
eport=444

ans = sr(IP(dst=ip)/TCP(dport=(sport, eport), flags="S"), timeout=2)[0]

sys.stdout = sys.__stdout__

if(len(ans)) > 0:
    print("\nOpen Ports:")

for packet in ans:
    print(packet[0].dport)
