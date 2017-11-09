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
