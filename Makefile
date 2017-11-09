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

all: output voiceControl searchForParams searchForNumber requestInput

output: bin/output.cpp bin/ukisSpeak.hpp bin/constants_and_libraries.h
	g++ bin/output.cpp -o bin/export/output -std=c++11
	
voiceControl: bin/voiceControl.cpp bin/ukisSpeak.hpp bin/constants_and_libraries.h bin/recognition_tools.hpp
	g++ bin/voiceControl.cpp -o bin/voiceControl -std=c++11
	
searchForParams: bin/searchForParams.cpp bin/constants_and_libraries.h
	g++ bin/searchForParams.cpp -o bin/export/searchForParams -std=c++11
	
searchForNumber: bin/searchForNumber.cpp bin/constants_and_libraries.h
	g++ bin/searchForNumber.cpp -o bin/export/searchForNumber -std=c++11
	
requestInput: bin/requestInput.cpp bin/constants_and_libraries.h bin/recognition_tools.hpp
	g++ bin/requestInput.cpp -o bin/export/requestInput -std=c++11
	
replaceLine: bin/replaceLine.cpp
	g++ bin/replaceLine.cpp -o bin/export/replaceLine -std=c++11
