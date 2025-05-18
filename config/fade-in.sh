#!/usr/bin/env bash
# This script is primarily useful as a wake-up alarm.
# Just call it in crontab or similar.
set -e
echo "Wake up time!"

HOST=localhost

# Make sure we dont flashbang our poor user
echo "set%brightness%0;" | nc $HOST 8252 -c
echo "start%glow;" | nc $HOST 8252 -c

echo "set%brightness%10;" | nc $HOST 8252 -c
sleep 180
echo "set%brightness%50;" | nc $HOST 8252 -c
sleep 180
echo "set%brightness%100;" | nc $HOST 8252 -c
sleep 250
echo "set%brightness%150;" | nc $HOST 8252 -c
sleep 250
echo "set%brightness%250;" | nc $HOST 8252 -c

echo "You better be awake >:|"