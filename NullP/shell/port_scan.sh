#!/bin/bash

echo "select ipv4"
read ipv4

nmap -p 1-65535 -T4 $ipv4
