#!/bin/bash

gcc -std=c23 ../bucket/bucket.c ../array/array.c map.c maptest.c -o exec -g
