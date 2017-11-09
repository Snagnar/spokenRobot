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

//Programm looks for occurences of specific words given as an argument in
//a given string.
//Syntax: searchForParams "['arg1', ..., 'argN']" "inputString"
//Returns first found parameter

int main(int argc, char** argv) {
	string listOfParams;
	string searchString;
	size_t tempVar;
	vector<string> params;
	
	stdLogPrefix=argv[0];
	stdLogPrefix+=": ";
	
	if(argc!=3) {
		writeToLog("errors.log", stdLogPrefix+error(1));
		return 1;
	}
	listOfParams=argv[1];
	searchString=argv[2];
	tempVar=0;
	
	while(listOfParams.find("\'")!=string::npos) {
		tempVar=listOfParams.find("\'");
		params.push_back(listOfParams.substr(tempVar+1, listOfParams.find("\'", tempVar+1)-tempVar-1));
		listOfParams.erase(listOfParams.begin(), listOfParams.begin()+listOfParams.find("\'", tempVar+1)+1);
	}
	
	for(auto currParam : params) {
		if(searchString.find(currParam)!=string::npos) {
			cout<<currParam;
			return 0;
		}
	}
	
	cout<<"";
	return 0;
}
