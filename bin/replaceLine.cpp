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

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

//replaces a line in a file with argument
//Syntax: replaceLine lineNr|"keyword_to_search_for_in_lines" "content_to_replace" "file"

static int convertStringToNumber(std::string String) {
	int result=0;
	for(int x=0; x<String.size(); x++) {
		if((String[String.size()-x-1]-0x30)>9||(String[String.size()-x-1]-0x30)<0) {
			return -1;
		}
		result+=(String[String.size()-x-1]-0x30)*pow(10,x);
	}
	return result;
}

int main(int argc, char** argv) {
	ifstream readFile;
	string line;
	string newContent;
	int lineNr;
	
	if(argc!=4) {
		cout<<"Error: Falsche Anzahl an Argumenten übergeben! "<<argc<<endl;
		return 1;
	}
	//for(int x=0; x<argc; x++)
		//cout<<"Arg nr. "<<x<<": "<<argv[x]<<endl;
	
	readFile.open(argv[3], ios::in);
	newContent="";
	lineNr=1;
	
	while(getline(readFile, line)) {
		if((convertStringToNumber(argv[1])!=-1&&convertStringToNumber(argv[1])==lineNr)||(convertStringToNumber(argv[1])==-1&&line.find(argv[1])!=string::npos)) {
			newContent+=argv[2];
			newContent+="\n";
		}
		else {
			newContent+=line+"\n";
		}
		lineNr++;
	}
	
	cout<<newContent;
	return 0;
}
