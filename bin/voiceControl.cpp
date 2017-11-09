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
