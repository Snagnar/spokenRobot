//
//	Copyright (C) Paul Mattes 2017
//	
//	This file is part of spokenRobot.
//
//   spokenRobot is free software: you can redistribute it and/or modify
//   it under the terms of the GNU General Public License as published by
//   the Free Software Foundation, either version 3 of the License, or
//   (at your option) any later version.
//
//   spokenRobot is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with spokenRobot.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef UKISSPEAK
#define UKISSPEAK

#include "constants_and_libraries.h"

//plays or reads out the indizes in the commands/audioList.file given by parameter
static int say(std::vector<int> listOfEntries) {
	std::ifstream entryDat;
	std::string line;
	std::string signes;
	std::string tempString;
	std::vector<int> alternatives;
	
	signes="[], ";
	time(&timeVar);
	srand((unsigned int)timeVar);
	
	entryDat.open(localPath+"commands/audioList.file", std::ios::in);
	if(entryDat.good()) {
		for(int x=0; x<listOfEntries.size(); x++) {
			writeToLog("logDat.log", stdLogPrefix+"operating on entry "+std::to_string(listOfEntries[x])+" in audioList.file");
			entryDat.clear();
			entryDat.seekg(0, std::ios::beg);
			while(getline(entryDat, line)) {
				if(line[0]=='#')
					continue;
				if(convertStringToNumber(line.substr(0, line.find(":")))==listOfEntries[x])
					break;
			}
			line.erase(line.begin(), line.begin()+line.find(":")+2);
			//If selector, read the indizes and pick one randomly
			if(line[0]=='[') {
				for(int x=1; x<line.size(); x++) {
					if(signes.find(line[x])!=std::string::npos) {
						if(tempString.size())
							alternatives.push_back(convertStringToNumber(tempString));
						tempString="";
						continue;
					}
					tempString+=line[x];
				}
				//adds the new index
				listOfEntries.push_back(alternatives[rand()%alternatives.size()]);
			}
			//if audiofile, play it
			else if(line.find(".wav")!=std::string::npos){
				tempString="play -q "+localPath+"commands/audios/"+line+" -t alsa";
				system(tempString.c_str());
			}
			//if just text, pass it to scripts/voice_output to let espeak read it out
			else {
				tempString=localPath+"/scripts/voice_output.sh "+line;
				system(tempString.c_str());
			}
		}
		entryDat.close();
	}
	else {
		writeToLog("errors.log", stdLogPrefix+error(3)+"audioList.file");
		return 404;
	}
	return 200;
}

#endif //UKISSPEAK
