#!/bin/bash
#

for (( i=20000 ; i<= 30000 ; i=i+1 ))
do
    echo "[$i] "$(./sum $i)""
done

