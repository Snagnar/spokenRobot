#!/bin/bash
#editRcLocal.sh
# This file edits the rc.local file in the /etc directory

rcFile=$(sed -e '$ d' /etc/rc.local)


rcFile="$rcFile \n$1\n\nexit 0\n"

cp /etc/rc.local /etc/rc.local.saveCopy
printf "$rcFile" > /etc/rc.local
