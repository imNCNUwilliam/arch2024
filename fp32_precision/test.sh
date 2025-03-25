#!/bin/bash
#

unittests=(10000 20000 25000)

#for i in {10000..10005};
for i in "${unittests[@]}";
do
    echo "[$i] "$(./sum $i)""
done

