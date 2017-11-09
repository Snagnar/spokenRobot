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


#ifndef RECOGNITION
#define RECOGNITION

#include "constants_and_libraries.h"

//extract the best transcription sent by googles speech api at temp/result.txt
static std::string getTranscript() {
	std::ifstream inputFile;
	std::string line;
	std::string signes;
	std::string tempString;
	std::string bestTranscript;
	std::vector<std::string> keywords;
	std::map<std::string, double> transcripts;
	double probBestTranscript;
	
	inputFile.open(localPath+"temp/result.txt", std::ios::in);
	signes="\",{}[]:";
	bestTranscript="";
	
	if(inputFile.good()) {
		//only the second line of file contains the interesting data
		getline(inputFile, line);
		getline(inputFile, line);
		// the file contains, next to a whole bunch of other symbols, some string chains which follow the syntax:
		// "transcript", "<the_transcript>", "confidence:", "<propability_of_transcript>" so we have to search for them and then
		// choose the one with highest propability
		
		for(int x=0; x<line.size(); x++) {
			if(signes.find(line[x])!=std::string::npos) {
				if(tempString.size())
					keywords.push_back(tempString);
				tempString="";
				continue;
			}
			tempString+=line[x];
		}
		for(int x=0; x<keywords.size(); x++) {
			if(keywords[x]=="transcript") {
				if((x+3)<keywords.size()&&keywords[x+3][0]=='0')
					transcripts[keywords[x+1]]=stod(keywords[x+3]);
				else
					transcripts[keywords[x+1]]=0.0;
			}
		}
		
		//Now chose the transcript with the highest confidence
		probBestTranscript=-1.0;
		for(auto it : transcripts) {
			if(it.second>probBestTranscript) {
				bestTranscript=it.first;
				probBestTranscript=it.second;
			}
		}
		
		inputFile.close();
		std::transform(bestTranscript.begin(), bestTranscript.end(), bestTranscript.begin(), ::tolower);
		tempString="cp /dev/null "+voiceRecogInputPath;
		system(tempString.c_str());
	}
	else {
		writeToLog("errors.log", stdLogPrefix+error(3)+localPath+"temp/result.txt");
		return "Error";
	}
	
	if(!bestTranscript.size())
		writeToLog("logDat.log", stdLogPrefix+"No voice input!");
	else
		writeToLog("logDat.log", stdLogPrefix+"Received voice command: "+bestTranscript);
	return bestTranscript;
}

//copies the commandDomains given at commands/commandDomains.file into a map
static std::map<std::string, std::vector<std::vector<std::string>>> loadCommandDomains() {
	std::map<std::string, std::vector<std::vector<std::string>>> commandDomains;
	std::ifstream domainFile;
	std::string line;
	std::string tempString;
	std::string commandName;
	bool inCombinationBlock;
	
	domainFile.open(localPath+"commands/commandDomains.file", std::ios::in);
	if(domainFile.good()) {
		while(getline(domainFile, line)) {
			if(!line.size()||line[0]=='#'||line[0]==' ')
				continue;
			commandName=line.substr(0, line.find(":"));
			commandDomains[commandName].push_back({});
			line+=",";
			for(int x=line.find(":")+1; x<line.size(); x++) {
				if(line[x]==' ')
					continue;
				else if(line[x]==',') {
					if(tempString.size())
						commandDomains[commandName][0].push_back(tempString);
					tempString="";
					continue;
				}
				tempString+=line[x];
			}
			
			inCombinationBlock=false; 
			for(auto it : commandDomains[commandName][0]) {
				if(it.find("[")!=std::string::npos) {
					inCombinationBlock=true;
					it.erase(it.begin()+it.find("["));
					if(commandDomains[commandName].back().size())
						commandDomains[commandName].push_back({});
					commandDomains[commandName].back().push_back(it);
				}
				else if(it.find("]")!=std::string::npos) {
					inCombinationBlock=false;
					it.erase(it.begin()+it.find("]"));
					commandDomains[commandName].back().push_back(it);
					commandDomains[commandName].push_back({});
				}
				else
					commandDomains[commandName].back().push_back(it);
			}
			commandDomains[commandName].erase(commandDomains[commandName].begin());
		}
		
		tempString="loaded commandDomains: \n";
		for(auto it : commandDomains) {
			tempString+=it.first+"\n";
			for(auto it2 : it.second) {
				tempString+="\t";
				for(auto it3 : it2)
					tempString+=it3+",";
				tempString+="\n";
			}
		}
		writeToLog("logDat.log", stdLogPrefix+tempString);
		
		domainFile.close();
	}
	else {
		writeToLog("errors.log", stdLogPrefix+error(3)+localPath+"commands/commandDomains.file");
	}
	
	return commandDomains;
}

//checks if input matches to a commandDomain
static std::string grepCommand(std::string input, std::map<std::string, std::vector<std::vector<std::string>>> commandDomains) {
	std::string command;
	std::string tempString;
	std::vector<std::string> possibleCommands;
	int tempVar=0;
	
	if(!input.size())
		return "unspecified";
	for(auto domain : commandDomains) {
		for(auto combination : domain.second) {
			tempVar=0;
			for(; tempVar<combination.size(); tempVar++) {
				if(input.find(combination[tempVar])==std::string::npos)
					break;
			}
			if(tempVar==combination.size()&&tempVar)
				possibleCommands.push_back(domain.first);
		}
	}
	
	possibleCommands=removeDuplicates(possibleCommands);
	if(possibleCommands.size()>1)
		return "unspecified";
	else if(possibleCommands.size()==0)
		return "unknown";
	else
		return possibleCommands.back();
}

//extracts the command code from file commands/commands.file
static std::string findCommandCode(std::string commandName) {
	std::ifstream commandFile;
	std::string line;
	std::string tempString;
	std::string code;
	bool inCodeBlock;
	
	code="";
	commandFile.open(localPath+"commands/commands.file", std::ios::in);
	inCodeBlock=false;
	if(commandFile.good()) {
		while(getline(commandFile, line)) {
			if(line.find("<\""+commandName+"\">")!=std::string::npos)
				inCodeBlock=true;
			else if(line.find("</\""+commandName+"\">")!=std::string::npos) {
				break;
			}
			else if(inCodeBlock)
				code+=line+"\n";
		}
	}
	else {
		writeToLog("errors.log", stdLogPrefix+error(3)+localPath+"commands/commands.file");
	}
	
	return code;
}

#endif //RECOGNITION
