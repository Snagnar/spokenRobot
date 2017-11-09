
#					 # 
#		README		         #
#					 #

#
#	Copyright (C) Paul Mattes 2017
#	
#	This file is part of spokenRobot.
#
#   spokenRobot is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   spokenRobot is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
#

1. Introducion: <br />
	First of all I want to appologize for bad english. I'm not a native
	speaker.

	spokenRobot is a voice assistent, that combines the prefrences of two
	speech engines: pocketsphinx, which one giant prefrence is, that it 
	runs offline, and the google speech api, which is very very precise at
	transcribing an audio file. <br />
	So spokenRobot uses pocketsphinx to just recognize one single keyword,
	'computer' as default, and the google speech api, to recognize the 
	following command. <br />
	If the keyword is recognized, a voice record starts, where you can call
	a command. This record will be sent to google, which returns its 
	transcription. <br />
	This has the prefrence, that you dont have constant network traffic
	when you don't actually want Google to transcribe.
	eSpeak is used for voice output. <br />
	You can define your own commands in the commands-directory, but this 
	will be explained later.

2. What you need:
	- stable internet connection
	- fully installed and useable microphone <br />
		=> you can test it by typing <br />
		
			arecord "temp.wav" <br />
				=> speak at microphone and cancel record with ctrl+c
				
			aplay "temp.wav" <br />
				=> plays the recorded file
			
		if you dont hear anything, your microphone is not properly working
	
3. Installation: <br />
	Just download the directory and put it somewhere in your home folder.
	then cd into it and type
	
		chmod a+x install.sh
		sudo ./install.sh
	
	This will install espeak, sphinxbase and pocketsphinx next to a bunch of
	dependencies.
	You will be asked for a google speech api key. If you dont already
	have one, follow the instructions at <br />
	
		http://nerdvittles.com/?page_id=21210 <br />
		
	to create one.
	If everything worked well, you can start spokenRobot to run in background
	or test your microphone settings first.

4. Define your own commands: <br />
	To define your own command, you have to modify at least two files: <br />
	
		commands/commandDomains.file	and
		commands/commands.file
	
	In the first you have to define the so called 'Domain' of your command,
	which means some keywords, which have to be found in voice input, to 
	actually start your command.
	So for example the command domain of the tell-time-command would be 
	defined as follows:
	
		tell_time: [what, time], [says, time], time
	
	The words in brackets are word combinations. This means, they have to
	be found both at least once in one voice input to start your 
	command, so that e.g. you dont get the time by just saying "what"
	but by saying e.g. "what is the time?"
	This notation is a bit complicated, but you can find further information
	at commands/commandDomains.file <br />
	
	The second file contains the actual code, which will be executed, when
	your command has been spotted in voice input. The code has to be
	linux-bash code, since spokenRobot just copies this code into an .sh
	file and executes it.
	For more information of syntax, available functions, variables, etc.
	see commands/commands.file <br />
	
	If you add a command by modifying this two files, you dont need
	to restart any script, this commands will be automatically integrated. <br />
	
	There is one more file in the commands directory: audioList.file
	This file contains some output read out, if e.g. an error occured.
	You can change this file to e.g. translate its content into your
	language or to add some output for your own commands.
	The syntax and functionalities are however explained at 
	commands/audioList.file

5. Change language: <br />
	In install.sh you are asked for an language code for googles speech api.
	You can find a full list of languages, supported by google at <br />
	
		https://cloud.google.com/speech/docs/languages
		
	To change it after installation, edit the file scripts/sendToGoogle.sh
	and change the position of "lang=en-us" in the link to your language-code. <br />
	
	The files in the command directory have to be translated in your language,
	and new commands can of course be defined in your language as well. <br />
	
	It is not recommended to change the language of pocketsphinx, since it
	is best at recognizing english, and since you just need it to recoginze a 
	single word, it is not that hard to bear this limitation. <br />
	
	To change the voice output to a voice in your language, you have to 
	modify the flag "-ven" of the espeak command in the  <br />
		scripts/voice_output.sh <br />
	to the flag for your language, e.g. -vde for german.
	You can find a full list of supported languages at <br />
	
		http://espeak.sourceforge.net/languages.html <br />
		
	Alternatively you can download additional voices at <br />
	
		http://tcts.fpms.ac.be/synthesis/mbrola.html <br />
		

6. Changing the keyword detected by pocketsphinx: <br />
	If you want for any reason to change the keyword that activates the
	recording for google speech api, to e.g. a name like "alexa" or 
	"jasper", follow these steps: <br />
	
		1. Create a file with some random words, containing the keyword
		   you want pocketsphinx to recognize.
		   This is the new word library and the less words are in it,
		   the more it is likely pocketsphinx recognizes a single word in it.
		   For example, if this file just contains your keyword, every
		   input, even if it sound completely different, is recognized
		   as this keyword. On the other hand, if it contains a few thousand
		   words, it is very hard for pocketsphinx to recognize your keyword.
		   Look at the keyword file in the directory, for an example of how
		   to create such a file for the keyword computer.
		   
		2. Go to the sphinx knowledge base generator site:
		
			http://www.speech.cs.cmu.edu/tools/lmtool-new.html
				
		   and upload your file generated above.
		   Then click "COMPILE KNOWLEDGE BASE" and download the .tgz file <br />
		
		3. Unpack it. <br />
		
		4. Put the files at 
			
			/usr/local/share/pocketsphinx/model/en-us <br />
		
		5. Replace the two occurs of the Number '1815' in scripts/autostart.sh 
		   with the base name of your knowledge base. This will be a 
		   four-digit-number, too.
		   When you have replaced the two numbers, restart this script by
		   typing:  <br />
				killall pocketsphinx_continuous
				scripts/autostart.sh & <br />
		
		6. Now the last thing to do, is, to change the "keyword" entry at 
		   the config.conf file in the main directory from "computer"
		   to your keyword.
