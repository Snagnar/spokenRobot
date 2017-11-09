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

#include "constants_and_libraries.h"

using namespace std;

//Programm searches for occurence of a number in argument
//Syntax: searchForNumber "content_to_search_in"
//Returns a number if found

int main(int argc, char** argv) {
	string searchString;
	string tempString;
	vector<string> singleWords;
	
	stdLogPrefix=argv[0];
	stdLogPrefix+=": ";
	
	if(argc!=2) {
		writeToLog("errors.log", stdLogPrefix+error(1));
		return 1;
	}
	searchString=argv[1];
	
	for(int x=0; x<searchString.size(); x++) {
		if(searchString[x]==' ') {
			singleWords.push_back(tempString);
			tempString="";
			continue;
		}
		tempString+=searchString[x];
	}
	for(auto it : singleWords)
		if(convertStringToNumber(it)!=-1) {
			cout<<convertStringToNumber(it);
			return 0;
		}
	
	cout<<"";
	return 0;
}
