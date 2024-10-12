#!/bin/bash
echo -n "Enter x: "
read -r x
echo -n "Enter y: "
read -r y
z=$(($x-$y))
echo "x - y = $z"
