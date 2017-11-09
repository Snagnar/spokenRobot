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
#   along with spokenRobot.  If not, see <http://www.gnu.org/licenses/>.
#


#include "ukisSpeak.hpp"

//Programm gets either a string be read out by espeak
//or a list of indizes of commands/audioList.file which will
//be outputted
//Syntax: output "Text"|"{<n1>, ..., <nN>}"
//Returns nothing

using namespace std;

int main(int argc, char** argv) {
	string input(argv[1]);
	string tempString;
	string signes;
	vector<int> selectorArgs;
	
	stdLogPrefix=argv[0];
	stdLogPrefix+=": ";
	signes="{} ,";
	
	if(argc!=2) {
		writeToLog("errors.log", stdLogPrefix+error(1));
		return 1;
	}
	
	writeToLog("logDat.log", stdLogPrefix+"Received argument: "+input);
	lockConversation();
	
	if(input.find("{")==string::npos) {
		tempString=localPath+"scripts/voice_output.sh \""+input+"\"";
		system(tempString.c_str());
	}
	else if(input.find("}")!=string::npos) {
		tempString="";
		for(int x=0; x<input.size(); x++) {
			if(signes.find(input[x])!=string::npos) {
				if(tempString.size())
					selectorArgs.push_back(convertStringToNumber(tempString));
				tempString="";
				continue;
			}
			tempString+=input[x];
		}
		say(selectorArgs);
	}
	else
		writeToLog("errors.log", stdLogPrefix+error(2));
	
	unlockConversation();
	return 0;
}
