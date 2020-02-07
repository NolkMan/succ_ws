#!/bin/bash
./server 0.0.0.0 1337 ./data/ &

apachectl -D FOREGROUND
