#!/bin/bash
#recognize.sh
# This file checks every pocketsphinx output if it contains the keyword, and if yes starts the voicerecord for google

path="/home/paul/Dropbox/share-client/projekte/smart-stuff"
output_file="$path/logs/pocketsphinx_output.log"
output_file_temp="$path/temp/pocketsphinx_output.log.temp"
cp /dev/null $output_file

counter=0
outputString="."

while true
do
	# get first line of output_file
	
	cp $output_file $output_file_temp
	cp /dev/null $output_file
	firstLine=$(head -1 $output_file_temp)
	
	tail -n +2 $output_file_temp | sponge $output_file_temp
	exec 3>&-
	
	if [ ${#firstLine} -eq 0 ]
	then
		outputString="\rNo Input"
		i=0
		while [ $i -lt $counter ]
		do
			outputString=$outputString" "
			i=$[$i+1]
		done
		outputString=$outputString"."
		printf "\r                            "
		printf "$outputString"
		counter=$[$counter+1]
		counter=$[$counter%20]
		sleep 0.2s
		continue
	fi
	# delete first line of log-file
	
	. $path/config.conf
	
	firstLine=$(echo $firstLine | awk '{print tolower($0)}')
	echo ""
	echo ""
	echo "Detected: $firstLine"
	echo "Keyword: $keyword"
	echo ""
	
	if echo "$firstLine" | grep -q $keyword
	then
		echo "Success!"
		output "{1}" &
		sox -r 44000 -c 1 -d $path/temp/output.wav silence 0 1 0:00:02 0.2%
		#aplay $PWD/temp/output.wav
		$path/scripts/sendToGoogle.sh
		#cat $PWD/temp/result.txt
		$path/bin/voiceControl
		sleep 2s
		cp /dev/null $output_file
	else
		echo "No Success!"
	fi
	sleep 0.2s
done

#sox -r 16000 -c 1 -d output.wav silence 0 1 0:00:02 1.3%
