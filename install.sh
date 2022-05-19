#!/usr/bin/env bash

export MAXMIND_LICENSE_KEY=K46gDa9xlhpBzRZi

cd tools
./get-ip-database.py

cd ..
make install

