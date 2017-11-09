#!/bin/bash


echo "$(bin/export/replaceLine "4" "path=\"$PWD\"" "scripts/recognize.sh")" > scripts/recognize.sh
echo "$(bin/export/replaceLine "4" "path=\"$PWD\"" "scripts/autostart.sh")" > scripts/autostart.sh
echo "$(bin/export/replaceLine "4" "path=\"$PWD\"" "scripts/sendToGoogle.sh")" > scripts/sendToGoogle.sh
echo "$(bin/export/replaceLine "localPath=\"\";" "const static string localPath=\"$PWD/\";" "bin/constants_and_libraries.h")" > bin/constants_and_libraries.h

