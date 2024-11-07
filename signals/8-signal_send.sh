#!/bin/bash

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <pid>"
    exit 1

fi

PID=$1

kill -QUIT "$PID"