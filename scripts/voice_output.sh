#!/bin/bash
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
# voice_output.sh
# audio output of commandline argument

export MALLOC_CHECK_=0 #if mbrola is used, this suppresses some irrelevant output
espeak -ven "$1" -s 100 > /dev/null 2>&1
