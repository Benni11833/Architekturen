#!/usr/bin/python3.8

import argparse
from socket import *
from ipaddress import IPv4Address, AddressValueError
from tqdm import tqdm

def check_IPv4(val):
    try:
        IPv4Address(val)
        return str(val)
    except AddressValueError:
        parser.error(f'IP-Address \'{args.ip}\' is not a valid IPv4-Address')

parser = argparse.ArgumentParser()
parser.add_argument('ip', metavar='IP Address', type=check_IPv4)

args = parser.parse_args()

reached_ports = []

for port in tqdm(range(1, 65536), desc='Scanning Ports', unit='Ports', bar_format='{l_bar}{bar}remaining: {remaining_s:.2f} s'):
    s = socket(AF_INET, SOCK_STREAM)
    setdefaulttimeout(1)
    if s.connect_ex((args.ip, port)) == 0:
        reached_ports.append(port)

print(f'Reached Ports: {[port for port in reached_ports]}')
