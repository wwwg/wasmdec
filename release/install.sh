#!/bin/bash

# super simple script to help install wasmdec

if [[ $EUID -ne 0 ]]; then
   echo "you must be root to install wasmdec" 
   exit 1
fi

if [ -e wasmdec ]
then
    echo "installing wasmdec"
else
    echo "no wasmdec binary exists in this directory, something is horribly wrong."
    exit 1
fi