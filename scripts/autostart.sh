#!/bin/bash
# autostartup script
# This file starts pocketsphinx to run in background and write every recognized word into a log-file

path="/home/paul/Dropbox/share-client/projekte/smart-stuff"

pocketsphinx_continuous -hmm /usr/local/share/pocketsphinx/model/en-us/en-us -lm /usr/local/share/pocketsphinx/model/en-us/1815.lm -dict /usr/local/share/pocketsphinx/model/en-us/1815.dic -samprate 16000/8000/48000 -inmic yes -logfn /dev/null | cat > $path/logs/pocketsphinx_output.log &
