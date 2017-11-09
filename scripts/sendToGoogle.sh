#!/bin/bash
#sendToGoogle.sh
#This File sends an audio file to googles speech api and writes the returned transcript to result.txt

path="."
pathToFile=$path"/temp/output.wav"
curl -s -X POST --data-binary @$pathToFile --header 'Content-Type: audio/l16; rate=44000;' 'https://www.google.com/speech-api/v2/recognize?output=json&lang=en-us&key=AIzaSyCgLAzPoc6TFXvCuCnqJymI7J-ycUuWcR4' > $path/temp/result.txt
