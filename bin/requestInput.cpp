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

#include "constants_and_libraries.h"
#include "recognition_tools.hpp"

using namespace std;

//Starts a record, which will be transcribed by googles speech api
//Return transcript.
//Syntax: requestInput

int main(int argc, char** argv) {
	string tempString;
	
	tempString="sox -r 44000 -c 1 -d "+localPath+"temp/output.wav silence 0 1 0:00:02 0.5%";
	system(tempString.c_str());
	
	tempString=localPath+"scripts/aufnahme.sh";
	system(tempString.c_str());
	
	cout<<getTranscript();
	return 0;
}
