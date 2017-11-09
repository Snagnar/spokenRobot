#!/bin/bash
#voice_output.sh
# audio output of commandline argument

export MALLOC_CHECK_=0 #if mbrola is used, this suppresses some irrelevant output
espeak -ven "$1" -s 100 > /dev/null 2>&1
