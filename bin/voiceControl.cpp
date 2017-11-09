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
#include "recognition_tools.hpp"

using namespace std;

//Programm reads transcript from google and executes the called command
//Syntax: voiceControl
//Returns nothing

void executeCommand(string input) {
	string tempString;
	auto commandDomains=loadCommandDomains();
	string command;
	ofstream tempCodeFile;
	
	command=grepCommand(input, commandDomains);
	cout<<"command: "<<command<<endl;
	
	if(command=="unspecified") {
		//more than one command domain matches
		writeToLog("logDat.log", stdLogPrefix+"Could not delimit command");
		lockConversation();
		say({10});
		unlockConversation();
	}
	else if(command=="unknown") {
		//no command domain matches
		writeToLog("logDat.log", stdLogPrefix+"No known command found in voice input!");
		lockConversation();
		say({2});
		unlockConversation();
	}
	else {
		//one command domain matches
		//its code will be extracted from commands/commands.file, copied to a .sh file
		//and executed
		writeToLog("logDat.log", stdLogPrefix+"Found command: "+command+" - now executing...");
		tempString=findCommandCode(command);
		tempCodeFile.open(localPath+"temp/commandCode.sh", ios::out|ios::trunc);
		tempString="#!/bin/bash\n\ninput=$1\n\n"+tempString;
		tempCodeFile<<tempString;
		tempCodeFile.close();
		system(("chmod a+x "+localPath+"temp/commandCode.sh").c_str());
		system((localPath+"temp/commandCode.sh \""+input+"\"").c_str());
		writeToLog("logDat.log", stdLogPrefix+"Command: "+command+" is now fully executed!");
	}
}

int main(int argc, char** argv) {
	
	//log prefix, so that the name of programm is public
	stdLogPrefix=argv[0];
	stdLogPrefix+=": ";

	executeCommand(getTranscript());
	
	return 0;
}
