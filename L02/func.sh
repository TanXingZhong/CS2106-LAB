#!/bin/bash
function func {
 echo "Called with $# parameters."
 sum=0
 count=1
 for param in $@; do
 sum=$(echo "$sum + $param" | bc)
 echo "Parameter $count is $param"
 let count=count+1
 done
 echo "139"
}
func $1 $2 $3
