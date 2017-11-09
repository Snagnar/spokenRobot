#!/bin/bash

# install.sh
# Installs dependencies and spokenRobot

echo "updating all software and install the necessary dependencies..."
sudo apt-get update && sudo apt-get upgrade --yes
sudo apt-get install g++ curl pulseaudio sed --yes

chmod -R a+rw ./*
chmod a+x scripts/*
mkdir bin/export

echo "If your g++ version is below 4.7, abort here and update first!"
echo "If you are not sure, just type 'g++ --version' to see what version you use. "
echo "At a raspberry pi this might get a bit tricky, follow the instructions at http://helloraspberrypi.blogspot.de/2014/06/install-gcc-47-on-raspberry-pi-and-set.html for help"
echo "[ENTER]"
read 

echo "installing espeak..."
sudo apt-get install espeak 
echo "espeak is installed!"
echo "espeak by now uses an english male voice, if you want to change this, in "
echo "		scripts/voice_output"
echo "you can modify the commandline options of espeak, e.g. -vde for german voice"
echo "For a full list of supported voices, look at http://espeak.sourceforge.net/languages.html"
echo "Alternatively you can also download and install other voices at http://tcts.fpms.ac.be/synthesis/mbrola.html"
echo "[ENTER]"
read

echo "Installing pocketsphinx..."
sudo apt-get install git automake libtool bison  python-dev swig make pkg-config --yes
if ls | grep -q "sphinxbase"
then
	echo "sphinxbase already installed!"
else
	git clone https://github.com/cmusphinx/sphinxbase.git
	cd sphinxbase
	./autogen.sh
	make
	sudo make install
	cd ..
fi

if ls | grep -q "pocketsphinx"
then
	echo "pocketsphinx already installed!"
else
	git clone git://github.com/cmusphinx/pocketsphinx.git
	cd pocketsphinx
	./autogen.sh
	make
	sudo make install
	cd ..
fi
echo "pocketsphinx installed!"

echo "Modify language model to precisely detect 'computer' keyword"
cp install/* /usr/local/share/pocketsphinx/model/en-us
echo "language model modified!"

echo "compile tool for replacing lines..."
make replaceLine
echo "tool compiled!"

echo "$(bin/export/replaceLine "localPath=\"\";" "const static std::string localPath=\"$PWD/\";" "bin/constants_and_libraries.h")" > bin/constants_and_libraries.h

echo "compiling binaries..."
make all
echo "All binaries are compiled!"

echo "exporting commands..."
mkdir ~/bin
cp bin/export/* ~/bin
echo "all commands are exported! (you can find them at ~/bin)"

printf "Enter your google speech api key\nIf you dont have one, follow the instructions given at http://nerdvittles.com/?page_id=21210\n\nYour key: "
read apiKey

printf "\n\nNow enter the language, you want to operate in \n(remember, the activation word will always be 'computer' \
since pocketsphinx is best at recognizing english words and the lexicon is adapted to recognize this single word \
very precisely). You can type e.g. 'en-us' for english or 'de-de' for german. For a full list of supported languages \
look at https://cloud.google.com/speech/docs/languages for more help. \n\n\
Your language: "
read langCode

printf "#!/bin/bash\n#sendToGoogle.sh\n#This File sends an audio file to googles speech api and writes the returned transcript to result.txt\n\npath=\"\"\npathToFile=\$path\"/temp/output.wav\"\ncurl -s -X POST \
--data-binary @\$pathToFile \
--header 'Content-Type: audio/l16; rate=44000;' \
'https://www.google.com/speech-api/v2/recognize?output=json&lang=$langCode&key=$apiKey' > \$path/temp/result.txt" > scripts/sendToGoogle.sh

echo "$(bin/export/replaceLine "5" "path=\"$PWD\"" "scripts/recognize.sh")" > scripts/recognize.sh
echo "$(bin/export/replaceLine "5" "path=\"$PWD\"" "scripts/autostart.sh")" > scripts/autostart.sh
echo "$(bin/export/replaceLine "5" "path=\"$PWD\"" "scripts/sendToGoogle.sh")" > scripts/sendToGoogle.sh

echo "Editing rc.local..."
path="$PWD/scripts/autostart.sh"
scripts/editRcLocal.sh "$path"

path="$PWD/scripts/recognize.sh"
scripts/editRcLocal.sh "$path"

echo "rc.local edited!"

echo "spokenRobot is now installed!!!"
echo "Do you want to start spokenRobot now <y/n>?"
read answer
if [ $answer == "y" ]
then
	scripts/autostart.sh &
	echo "Do you want to test if your microphone and pocketsphinx are working together <y/n>?"
	answer=""
	read answer
	if [ $answer == "y" ]
	then
		echo "say something (e.g. 'computer') to the microphone..."
		sleep 6s
		res=$(cat temp/result.txt)
		if [ ${#res} -eq 0 ]
		then
			echo "Something is wrong, maybe try to restart your computer?"
		else
			echo "Everything works properly and you can now start defining your own commands ;) "
		fi
	fi
	scripts/recognize.sh > /dev/null &
fi
echo "Everything is now installed and script is over!"
