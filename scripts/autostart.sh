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
# autostartup script
# This file starts pocketsphinx to run in background and write every recognized word into a log-file

path="/home/paul/Dropbox/share-client/projekte/smart-stuff"

pocketsphinx_continuous -hmm /usr/local/share/pocketsphinx/model/en-us/en-us -lm /usr/local/share/pocketsphinx/model/en-us/1815.lm -dict /usr/local/share/pocketsphinx/model/en-us/1815.dic -samprate 16000/8000/48000 -inmic yes -logfn /dev/null | cat > $path/logs/pocketsphinx_output.log &
