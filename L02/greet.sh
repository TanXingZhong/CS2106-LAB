#!/bin/bash
name=$(whoami)
machine=$(uname -m)
platform=$(uname -n)
version=$(uname -r)
echo "Hello $name, you are using a $machine machine running kernel version $version on $platform"
