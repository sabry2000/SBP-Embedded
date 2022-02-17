#!/usr/bin/env bash

# Generate rsa keys pair
ssh-keygen -t rsa -b 4096 -f rs256.rsa

# Don't add passphrase
openssl rsa -in rs256.rsa -pubout -outform PEM -out rs256.rsa.pub

# Done
cat rs256.rsa
cat rs256.rsa.pub