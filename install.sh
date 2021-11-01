#!/bin/bash

echo Building and installing application...
mkdir -p build
cd build
cmake ..
make install

echo Application built!

echo Stopping service...
systemctl stop matrix

sleep 10

echo Restarting service...
systemctl daemon-reload
systemctl start matrix

echo
echo Matrix service installed!

