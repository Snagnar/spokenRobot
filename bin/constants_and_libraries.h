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


#ifndef CONSTANTS
#define CONSTANTS

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <algorithm>
#include <map>
#include <array>
#include <unordered_map>
#include <climits>

/*
 * This file contains some basic functions for spokenRobot.
 * The localPath is the path, where spokenRobot is installed.
*/

const static std::string localPath="/home/paul/Dropbox/share-client/projekte/smart-stuff/";

static std::string stdLogPrefix;
time_t timeVar;

//gives back the errormessage specified in list_of_errors with number
static std::string error(int errorNumber) {
	std::string error_msg;
	std::ifstream error_file(localPath+"logs/list_of_errors", std::ios::in);
	
	if(error_file.is_open()) {
		while(getline(error_file, error_msg)) {
			if(error_msg.substr(0, error_msg.find(":"))==std::to_string(errorNumber))
				break;
		}
	}
	else return "Error 0: Error at opening error_file\n";
	
	return "Error "+error_msg;
}

//converts a String (e.g. "1234") to the Int-Value (e.g. 1234)
static int convertStringToNumber(std::string String) {
	int result=0;
	//Because google transcribes a spoken "one" not as the number 1 it has to be recognized separately for every language
	if(	String=="einer"||String=="one"||String=="一"||String=="en"||String=="unu"||String=="yksi"||String=="un"||String=="ένας"||String=="एक"||String=="אחד"||String=="satu"||String=="uno"||String=="一つ"||String=="한"||String=="한"
		||String=="viens"||String=="vienas"||String=="één"||String=="ett"||String=="jeden"||String=="um"||String=="unul"||String=="один"||String=="ena"||String=="moja"||String=="หนึ่ง"||String=="bir"||String=="egy"||String=="адзін"||String=="eyodwa")
		return 1;
	for(int x=0; x<String.size(); x++) {
		if((String[String.size()-x-1]-0x30)>9||(String[String.size()-x-1]-0x30)<0) {
			return -1;
		}
		result+=(String[String.size()-x-1]-0x30)*pow(10,x);
	}
	return result;
}

//wirtes the message to the logfile
static void writeToLog(std::string logPath, std::string mesg) {
    struct tm * now;
	std::ofstream logDat;
	std::string timeStamp;
	
	timeVar=time(NULL);
    now = localtime(&timeVar);
    timeStamp="["+std::to_string(now->tm_mday)+"."+std::to_string(now->tm_mon+1)+"."+std::to_string(now->tm_year+1900)+"-"+std::to_string(now->tm_hour)+":"+std::to_string(now->tm_min)+":"+std::to_string(now->tm_sec)+"] $ ";
    mesg=timeStamp+mesg+"\n";
    
	logPath="/var/log/spokenRobot/"+logPath;
	logDat.open(logPath, std::ios::out|std::ios::app);
	logDat<<mesg;
	logDat.close();
}

//remove duplicates in a vector<string>
static std::vector<std::string> removeDuplicates(std::vector<std::string> input) {
	std::vector<std::string> returnVector;
	
	for(auto it : input)
		if(std::find(returnVector.begin(), returnVector.end(), it)==returnVector.end())
			returnVector.push_back(it);
	
	return returnVector;
}

//modifies a Flag in config.conf
static void writeFlagToConfig(std::string flag, std::string value) {
	std::ifstream configFile(localPath+"config.conf", std::ios::in);
	std::string line;
	std::map<std::string, std::string> flags;
	std::string currStr="", currName="";
	if(configFile.good()) {
		while(getline(configFile, line)) {
			currStr="";
			for(int x=0; x<line.size()-1; x++) {
				if(line[x]=='=') {
					currName=currStr;
					currStr="";
					x+=2;
					continue;
				}
				currStr+=line[x];
			}
			flags[currName]=currStr;
		}
		configFile.close();
		if(flags.find(flag)==flags.end()) {
			writeToLog("errors.log", stdLogPrefix+error(4)+value);
			flags[flag]=value;
		}
		else
			flags[flag]=value;
		std::ofstream changedConfigFile(localPath+"config.conf", std::ios::out|std::ios::trunc);
		std::string fullContent="";
		for(auto it : flags)
			fullContent+=it.first+"=\""+it.second+"\"\n";
		changedConfigFile<<fullContent;
		changedConfigFile.close();
	}
	else {
		writeToLog("errors.log", stdLogPrefix+error(3)+localPath+"config.conf");
	}
}

//reads a Flag in config.conf
static std::string getFlagFromConfig(std::string flag) {
	std::ifstream configFile(localPath+"config.conf", std::ios::in);
	std::string line;
	std::map<std::string, std::string> flags;
	std::string currStr="", currName="";
	if(configFile.good()) {
		while(getline(configFile, line)) {
			currStr="";
			for(int x=0; x<line.size()-1; x++) {
				if(line[x]=='=') {
					currName=currStr;
					currStr="";
					x+=2;
					continue;
				}
				currStr+=line[x];
			}
			flags[currName]=currStr;
		}
		configFile.close();
		if(flags.find(flag)==flags.end()) {
			writeToLog("errors.log", stdLogPrefix+error(4)+flag);
			return "";
		}
		else
			return flags[flag];
	}
	else {
		writeToLog("errors.log", stdLogPrefix+error(3)+localPath+"config.conf");
		return "";
	}
}

//sets conversationInProgress-Flag to true, so that no voiceoutputs overlap
static void lockConversation() {
	while(getFlagFromConfig("conversationInProgress")=="true")
		sleep(1);
	writeFlagToConfig("conversationInProgress", "true");
}

static void unlockConversation() {
	writeFlagToConfig("conversationInProgress", "false");
}


#endif //CONSTANTS
